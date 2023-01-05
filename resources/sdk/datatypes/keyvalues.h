#pragma once
#include <cstddef>
#include <cstdint>
#include "../interfaces/ikeyvaluessystem.h"

using GetSymbolProcFn = bool(__cdecl *)(const char *);

class CKeyValues
{
public:
	enum EKeyType : int {
		TYPE_NONE = 0,
		TYPE_STRING,
		TYPE_INT,
		TYPE_FLOAT,
		TYPE_PTR,
		TYPE_WSTRING,
		TYPE_COLOR,
		TYPE_UINT64,
		TYPE_COMPILED_INT_BYTE,
		TYPE_COMPILED_INT_0,
		TYPE_COMPILED_INT_1,
		TYPE_NUMTYPES
	};

	CKeyValues(const char *szKeyName, void *pUnknown1 = nullptr, HKeySymbol hCaseInsensitiveKeyName = INVALID_KEY_SYMBOL);
	~CKeyValues();

	void *operator new(std::size_t nAllocSize);
	void operator delete(void *pMemory);

	const char *GetName();

	static CKeyValues *FromString(const char *szName, const char *szValue);
	void LoadFromBuffer(char const *szResourceName, const char *szBuffer, void *pFileSystem = nullptr, const char *szPathID = nullptr, GetSymbolProcFn pfnEvaluateSymbolProc = nullptr);
	bool LoadFromFile(void *pFileSystem, const char *szResourceName, const char *szPathID = nullptr, GetSymbolProcFn pfnEvaluateSymbolProc = nullptr);

	CKeyValues *FindKey(const char *szKeyName, const bool bCreate);

	int GetInt(const char *szKeyName, const int iDefaultValue);
	float GetFloat(const char *szKeyName, const float flDefaultValue);
	const char *GetString(const char *szKeyName, const char *szDefaultValue);

	void SetString(const char *szKeyName, const char *szStringValue);
	void SetInt(const char *szKeyName, const int iValue);
	void SetUint64(const char *szKeyName, const int nLowValue, const int nHighValue);

	inline void SetBool(const char *szKeyName, const bool bValue) {
		SetInt(szKeyName, bValue ? 1 : 0);
	}

private:
	std::uint32_t uKeyName : 24;
	std::uint32_t uKeyNameCaseSensitive1 : 8;
	char *szValue;
	wchar_t *wszValue;

	union {
		int iValue;
		float flValue;
		void *pValue;
		unsigned char arrColor[4];
	};

	std::int8_t iDataType;
	bool bHasEscapeSequences;
	std::uint16_t uKeyNameCaseSensitive2;
	void *pUnknown14;
	bool bHasCaseInsensitiveKeySymbol;
	CKeyValues *pPeer;
	CKeyValues *pSub;
	CKeyValues *pChain;
	GetSymbolProcFn pExpressionGetSymbolProc;
};
static_assert(sizeof(CKeyValues) == 0x2C);
