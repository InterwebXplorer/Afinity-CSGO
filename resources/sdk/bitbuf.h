#pragma once

class bf_write
{
public:
	bf_write() = default;

	unsigned long *pData;
	int nDataBytes;
	int nDataBits;

	int iCurrentBit;
};

class bf_read
{
public:
	std::uintptr_t uBaseAddress;
	std::uintptr_t uCurrentOffset;

	bf_read(std::uintptr_t uAddress) : uBaseAddress(uAddress), uCurrentOffset(0U) {}

	void SetOffset(std::uintptr_t uOffset)
	{
		uCurrentOffset = uOffset;
	}

	void Skip(std::uintptr_t uLength)
	{
		uCurrentOffset += uLength;
	}

	int ReadByte()
	{
		char dValue = *reinterpret_cast<char *>(uBaseAddress + uCurrentOffset);
		++uCurrentOffset;
		return dValue;
	}

	bool ReadBool()
	{
		bool bValue = *reinterpret_cast<bool *>(uBaseAddress + uCurrentOffset);
		++uCurrentOffset;
		return bValue;
	}

	const char *ReadString()
	{
		char szBuffer[256];
		char chLength = *reinterpret_cast<char *>(uBaseAddress + uCurrentOffset);
		++uCurrentOffset;
		memcpy(szBuffer, reinterpret_cast<void *>(uBaseAddress + uCurrentOffset), chLength > 255 ? 255 : chLength);
		szBuffer[chLength > 255 ? 255 : chLength] = '\0';
		uCurrentOffset += chLength + 1;
		return szBuffer;
	}
};
