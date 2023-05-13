#pragma once
#include <vector>
#include <format>
#include <windows.h>
#include "filelogging.h"
#include "../imgui/freetype/imgui_freetype.h"

#pragma region memory_modules_definitions
#define ENGINE_DLL				"engine.dll"
#define CLIENT_DLL				"client.dll"
#define LOCALIZE_DLL			"localize.dll"
#define MATERIALSYSTEM_DLL		"materialsystem.dll"
#define VGUI_DLL				"vguimatsurface.dll"
#define VGUI2_DLL				"vgui2.dll"
#define SHADERPIDX9_DLL			"shaderapidx9.dll"
#define GAMEOVERLAYRENDERER_DLL "gameoverlayrenderer.dll"
#define PHYSICS_DLL				"vphysics.dll"
#define VSTDLIB_DLL				"vstdlib.dll"
#define TIER0_DLL				"tier0.dll"
#define INPUTSYSTEM_DLL			"inputsystem.dll"
#define STUDIORENDER_DLL		"studiorender.dll"
#define DATACACHE_DLL			"datacache.dll"
#define STEAM_API_DLL			"steam_api.dll"
#define MATCHMAKING_DLL			"matchmaking.dll"
#define SERVER_DLL				"server.dll"
#define SERVERBROWSER_DLL		"serverbrowser.dll"
#pragma endregion


template <typename T>
class Singleton {
	protected:
		Singleton() {}
		~Singleton() {}

		Singleton(const Singleton&) = delete;
		Singleton& operator=(const Singleton&) = delete;

		Singleton(Singleton&&) = delete;
		Singleton& operator=(Singleton&&) = delete;

	public:
		static T& Get() {
			static T Instance{};
			return Instance;
		}
};


class WrappedProtect {
	public:
		WrappedProtect(void* BaseAddress, const std::size_t Length, const DWORD Flags) : BaseAddress(BaseAddress), Length(Length) {
			if (!VirtualProtect(BaseAddress, Length, Flags, &OldFlags)) {
				WriteToLog(std::format("[Error] Failed to protect region <ErrCode -> {}, SysCategory -> {}>", GetLastError(), std::system_category().message()))
				OldFlags = 0;
			}
		}

		~WrappedProtect() {
			VirtualProtect(BaseAddress, Length, OldFlags, &OldFlags);
		}

	private:
		void* BaseAddress;
		std::size_t	Length;
		DWORD OldFlags;
};


namespace Memory {
	std::uintptr_t FindPattern(const std::string_view ModuleName, const std::string_view Pattern);
	std::uintptr_t FindPattern(const std::uint8_t* RegionStart, const std::uintptr_t RegionSize, const std::string_view Pattern);
	void* GetModuleBaseHandle(const std::string_view ModuleName);
	void* GetExportAddress(const void* ModuleBase, const std::string_view ProcedureName);
	std::vector<std::uintptr_t> GetCrossReferences(const std::uintptr_t Address, std::uintptr_t RegionStart, const std::size_t RegionSize);
	bool GetSectionInfo(const std::uintptr_t BaseAddress, const std::string_view SectionName, std::uintptr_t* SectionStart, std::uintptr_t* SectionSize);
	std::uintptr_t GetVTableTypeDescriptor(const std::string_view ModuleName, const std::string_view TableName);
	std::uintptr_t* GetVTablePointer(const std::string_view ModuleName, const std::string_view TableName);
	
	template <typename T, std::size_t S>
	std::vector<T> GetFilledVector(const T& fill) {
		std::vector<T> Temp(S);
		std::fill(Temp.begin(), Temp.begin() + S, fill);
		return Temp;
	}
	
	inline std::uintptr_t GetAbsoluteAddress(const std::uintptr_t RelativeAddress) {
		return RelativeAddress + 0x4 + *reinterpret_cast<std::int32_t*>(RelativeAddress);
	}

	template <typename T = void*>
	constexpr T GetVFunc(void* thisptr, std::size_t Index) {
		return (*static_cast<T**>(thisptr))[Index];
	}
	
	template <typename T, typename ... Args_t>
	constexpr T CallVFunc(void* thisptr, std::size_t Index, Args_t... List) {
		using VirtualFn = T(__thiscall*)(void*, decltype(List)...);
		return (*static_cast<VirtualFn**>(thisptr))[Index](thisptr, List...);
	}

	std::vector<std::optional<std::uint8_t>> PatternToBytes(const std::string_view Pattern);
	std::string BytesToPattern(const std::uint8_t* Bytes, const std::size_t Size);
	bool IsValidCodePtr(const void* Pointer);
}
