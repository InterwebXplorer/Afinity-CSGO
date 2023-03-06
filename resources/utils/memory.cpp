#include <intrin.h>
#include <format>
#include "memory.h"
#include "pe32.h"
#include "filelogging.h"

std::uintptr_t Memory::FindPattern(const std::string_view ModuleName, const std::string_view Pattern) {
	void* Module = GetModuleBaseHandle(ModuleName);

	if (!Module) {
		WriteToLog(std::format("[Error] Failed to get handle for <{}>", ModuleName))
		return 0;
	}

	const std::uint8_t* ModuleAddress = static_cast<std::uint8_t*>(Module);
	const IMAGE_DOS_HEADER* DosHeader = static_cast<IMAGE_DOS_HEADER*>(Module);
	const IMAGE_NT_HEADERS* NtHeaders = reinterpret_cast<const IMAGE_NT_HEADERS*>(ModuleAddress + DosHeader->e_lfanew);

	return FindPattern(ModuleAddress, NtHeaders->OptionalHeader.SizeOfImage, Pattern);
}

std::uintptr_t Memory::FindPattern(const std::uint8_t* RegionStart, const std::uintptr_t RegionSize, const std::string_view Pattern) {
	const std::vector<std::optional<std::uint8_t>> Bytes = PatternToBytes(Pattern);

	for (std::uintptr_t i = 0U; i < RegionSize - Bytes.size(); ++i) {
		bool ByteFound = true;
		
		for (std::uintptr_t j = 0U; j < Bytes.size(); ++j) {

			if (Bytes[j].has_value() && RegionStart[i + j] != Bytes[j].value()) {
				ByteFound = false;
				break;
			}
		}

		if (ByteFound)
			return reinterpret_cast<std::uintptr_t>(&RegionStart[i]);
	}

	WriteToLog(std::format("[Error] Pattern not found <{}>", Pattern))
	return 0U;
}

void* Memory::GetModuleBaseHandle(const std::string_view ModuleName) {
	const _PEB32* PEB = reinterpret_cast<_PEB32*>(__readfsdword(0x30));

	if (ModuleName.empty())
		return PEB->ImageBaseAddress;

	const std::wstring ModuleNameW(ModuleName.begin(), ModuleName.end());

	for (LIST_ENTRY* ListEntry = PEB->Ldr->InLoadOrderModuleList.Flink; ListEntry != &PEB->Ldr->InLoadOrderModuleList; ListEntry = ListEntry->Flink) {
		const _LDR_DATA_TABLE_ENTRY* Entry = CONTAINING_RECORD(ListEntry, _LDR_DATA_TABLE_ENTRY, InLoadOrderLinks);

		if (Entry->BaseDllName.Buffer && ModuleNameW.compare(Entry->BaseDllName.Buffer) == 0)
			return Entry->DllBase;
	}

	WriteToLog(std::format("[Error] Module base not found <{}>", ModuleName))
	return nullptr;
}

void* Memory::GetExportAddress(const void* ModuleBase, const std::string_view ProcedureName)
{
	const std::uint8_t* Address = static_cast<const std::uint8_t*>(ModuleBase);
	const IMAGE_DOS_HEADER* DosHeader = static_cast<const IMAGE_DOS_HEADER*>(ModuleBase);
	const IMAGE_NT_HEADERS* NtHeaders = reinterpret_cast<const IMAGE_NT_HEADERS*>(Address + DosHeader->e_lfanew);
	const IMAGE_OPTIONAL_HEADER* OptionalHeader = &NtHeaders->OptionalHeader;

	const std::uintptr_t ExportSize = OptionalHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size;
	const std::uintptr_t ExportAddress = OptionalHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;

	if (ExportSize <= 0U)
		return nullptr;

	const IMAGE_EXPORT_DIRECTORY* ExportDirectory = reinterpret_cast<const IMAGE_EXPORT_DIRECTORY*>(Address + ExportAddress);
	const std::uintptr_t* NamesRVA = reinterpret_cast<const std::uintptr_t*>(Address + ExportDirectory->AddressOfNames);
	const std::uintptr_t* FunctionsRVA = reinterpret_cast<const std::uintptr_t*>(Address + ExportDirectory->AddressOfFunctions);
	const std::uint16_t* NameOrdinals = reinterpret_cast<const std::uint16_t*>(Address + ExportDirectory->AddressOfNameOrdinals);

	std::uintptr_t Right = ExportDirectory->NumberOfNames;
	std::uintptr_t Left = 0;

	while (Right != Left) {
		const std::uintptr_t Middle = Left + ((Right - Left) >> 1U);
		const int Result = ProcedureName.compare(reinterpret_cast<const char*>(Address + NamesRVA[Middle]));

		if (Result == 0)
			return const_cast<void*>(static_cast<const void*>(Address + FunctionsRVA[NameOrdinals[Middle]]));

		if (Result > 0)
			Left = Middle;
		else
			Right = Middle;
	}

	WriteToLog(std::format("[Error] Export not found <{}>", ProcedureName));
	return nullptr;
}

std::vector<std::uintptr_t> Memory::GetCrossReferences(const std::uintptr_t Address, std::uintptr_t RegionStart, const std::size_t RegionSize) {
	std::vector<std::uintptr_t> CrossReferences = {};
	const std::string Pattern = BytesToPattern(reinterpret_cast<const std::uint8_t*>(&Address), sizeof(std::uintptr_t));
	const std::uintptr_t RegionEnd = RegionStart + RegionSize;

	while (RegionStart > 0U && RegionStart < RegionEnd) {
		std::uintptr_t ReferenceAddress = FindPattern(reinterpret_cast<std::uint8_t*>(RegionStart), RegionSize, Pattern.c_str());

		if (ReferenceAddress == 0U)
			break;

		CrossReferences.push_back(ReferenceAddress);

		RegionStart = ReferenceAddress + sizeof(std::uintptr_t);
	}

	return CrossReferences;
}

bool Memory::GetSectionInfo(const std::uintptr_t BaseAddress, const std::string_view SectionName, std::uintptr_t* SectionStart, std::uintptr_t* SectionSize) {
	const IMAGE_DOS_HEADER* DosHeader = reinterpret_cast<IMAGE_DOS_HEADER*>(BaseAddress);
	
	if (DosHeader->e_magic != IMAGE_DOS_SIGNATURE)
		return false;

	const IMAGE_NT_HEADERS* NtHeaders = reinterpret_cast<IMAGE_NT_HEADERS*>(BaseAddress + DosHeader->e_lfanew);
	
	if (NtHeaders->Signature != IMAGE_NT_SIGNATURE)
		return false;

	IMAGE_SECTION_HEADER* SectionHeader = IMAGE_FIRST_SECTION(NtHeaders);
	std::uint16_t NumberOfSections = NtHeaders->FileHeader.NumberOfSections;

	while (NumberOfSections > 0U) {
		if (SectionName.starts_with(reinterpret_cast<const char*>(SectionHeader->Name))) {
			if (SectionStart != nullptr)
				*SectionStart = BaseAddress + SectionHeader->VirtualAddress;

			if (SectionSize != nullptr)
				*SectionSize = SectionHeader->SizeOfRawData;

			return true;
		}

		SectionHeader++;
		NumberOfSections--;
	}

	return false;
}

std::uintptr_t Memory::GetVTableTypeDescriptor(const std::string_view ModuleName, const std::string_view TableName) {
	const std::string TypeDescriptorName = std::string(".?AV").append(TableName).append("@@");
	const std::string Pattern = BytesToPattern(reinterpret_cast<const std::uint8_t*>(TypeDescriptorName.data()), TypeDescriptorName.size());

	if (const std::uintptr_t TypeDescriptor = FindPattern(ModuleName, Pattern); TypeDescriptor != 0U)
		return TypeDescriptor - 0x8;

	WriteToLog(std::format("[Error] Virtual table type descriptor not found <Module -> {}, Table -> {}>", ModuleName, TableName))
	return 0U;
}

std::uintptr_t* Memory::GetVTablePointer(const std::string_view ModuleName, const std::string_view TableName) {
	const std::uintptr_t BaseAddress = reinterpret_cast<std::uintptr_t>(GetModuleBaseHandle(ModuleName));

	if (BaseAddress == 0U)
		return nullptr;

	const std::uintptr_t TypeDescriptor = GetVTableTypeDescriptor(ModuleName, TableName);

	if (TypeDescriptor == 0U)
		return nullptr;

	std::uintptr_t RDataStart = 0U, RDataSize = 0U;
	
	if (!GetSectionInfo(BaseAddress, XorStr(".rdata"), &RDataStart, &RDataSize))
		return nullptr;

	for (const auto &CrossReference : GetCrossReferences(TypeDescriptor, RDataStart, RDataSize)) {

		if (const int VTableOffset = *reinterpret_cast<int*>(CrossReference - 0x8); VTableOffset != 0)
			continue;

		const std::uintptr_t ObjectLocator = CrossReference - 0xC;

		std::string Pattern = BytesToPattern(reinterpret_cast<const std::uint8_t*>(&ObjectLocator), sizeof(std::uintptr_t));
		const std::uintptr_t VTableAddress = FindPattern(reinterpret_cast<std::uint8_t*>(RDataStart), RDataSize, Pattern.c_str()) + 0x4;

		if (VTableAddress <= sizeof(std::uintptr_t))
			return nullptr;

		std::uintptr_t TextStart = 0U, TextSize = 0U;

		if (!GetSectionInfo(BaseAddress, XorStr(".text"), &TextStart, &TextSize))
			return nullptr;

		Pattern = BytesToPattern(reinterpret_cast<const std::uint8_t*>(&VTableAddress), sizeof(std::uintptr_t));
		return reinterpret_cast<std::uintptr_t *>(FindPattern(reinterpret_cast<std::uint8_t*>(TextStart), TextSize, szPattern.c_str()));
	}

	WriteToLog(std::format("[Error] Virtual table pointer not found <Module -> {}, Table -> {}>", ModuleName, TableName))
	return nullptr;
}

bool Memory::IsValidCodePtr(const void* Pointer) {
	if (Pointer == nullptr)
		return false;

	MEMORY_BASIC_INFORMATION MemoryInfo = {};

	if (VirtualQuery(Pointer, &MemoryInfo, sizeof(MEMORY_BASIC_INFORMATION)) == 0U)
		return false;

	if (!(MemoryInfo.Protect & PAGE_EXECUTE_READWRITE || MemoryInfo.Protect & PAGE_EXECUTE_READ))
		return false;

	return true;
}

std::vector<std::optional<std::uint8_t>> Memory::PatternToBytes(const std::string_view Pattern) {
	std::vector<std::optional<std::uint8_t>> Bytes = {};
	auto Begin = Pattern.cbegin();
	const auto End = Pattern.cend();

	while (Begin < End) {
		if (*Begin == '?') {
			if (++Begin; *Begin == '?')
				++Begin;

			Bytes.emplace_back(std::nullopt);
		}

		else if (*Begin != ' ') {
			std::uint8_t Byte = static_cast<std::uint8_t>(((*Begin >= 'A' ? (((*Begin - 'A') & (~('a' ^ 'A'))) + 10) : (*Begin <= '9' ? *Begin - '0' : 0x0)) | 0xF0) << 4);

			if (++Begin; *Begin != ' ')
				Byte |= static_cast<std::uint8_t>(*Begin >= 'A' ? (((*Begin - 'A') & (~('a' ^ 'A'))) + 10) : (*Begin <= '9' ? *Begin - '0' : 0x0));

			Bytes.emplace_back(Byte);
		}

		++Begin;
	}

	return Bytes;
}

std::string Memory::BytesToPattern(const std::uint8_t* Bytes, const std::size_t Size) {
	constexpr const char* HexDigits = "0123456789ABCDEF";
	const std::size_t HexLength = (Size << 1U) + Size;

	std::string Pattern(HexLength - 1U, ' ');

	for (std::size_t i = 0U, j = 0U; i < HexLength; j++, i += 3U) {
		const std::uint8_t CurrentByte = Bytes[j];

		Pattern[i] = HexDigits[((CurrentByte & 0xF0) >> 4)];
		Pattern[i + 1U] = HexDigits[(CurrentByte & 0x0F)];
	}

	return Pattern;
}
