#pragma once
#include <windows.h>
#include "datatypes/color.h"
#include "datatypes/utlvector.h"

using FnCommandCallbackV1_t = void(__cdecl *)();
using FnChangeCallback_t = void(__cdecl *)(void *, const char *, float);
class CConVar
{
public:
	const char *GetName()
	{
		return MEM::CallVFunc<const char *>(this, 5);
	}

	float GetFloat()
	{
		std::uint32_t uXored = *reinterpret_cast<std::uint32_t *>(&pParent->flValue) ^ reinterpret_cast<std::uint32_t>(this);
		return *reinterpret_cast<float *>(&uXored);
	}

	int GetInt()
	{
		return static_cast<int>(pParent->iValue ^ reinterpret_cast<int>(this));
	}

	bool GetBool()
	{
		return !!GetInt();
	}

	const char *GetString() const
	{
		char const *szValue = pParent->szString;
		return szValue ? szValue : "";
	}

	void SetValue(const char *szValue)
	{
		return MEM::CallVFunc<void>(this, 14, szValue);
	}

	void SetValue(float flValue)
	{
		return MEM::CallVFunc<void>(this, 15, flValue);
	}

	void SetValue(int iValue)
	{
		return MEM::CallVFunc<void>(this, 16, iValue);
	}

	void SetValue(Color colValue)
	{
		return MEM::CallVFunc<void>(this, 17, colValue);
	}

public:
	std::byte pad0[0x4];
	CConVar *pNext;
	bool bRegistered;
	const char *szName;
	const char *szHelpString;
	int nFlags;
	FnCommandCallbackV1_t pCallback;
	CConVar *pParent;
	const char *szDefaultValue;
	char *szString;
	int iStringLength;
	float flValue;
	int iValue;
	bool bHasMin;
	float flMinValue;
	bool bHasMax;
	float flMaxValue;
	CUtlVector<FnChangeCallback_t> fnChangeCallbacks;
};

class CSpoofedConVar
{
public:
	CSpoofedConVar() = default;
	CSpoofedConVar(const char *szCVar);
	CSpoofedConVar(CConVar *pCVar);
	~CSpoofedConVar();

	bool IsSpoofed() const;
	void Spoof();

	void SetFlags(int iFlags) const;
	int GetFlags() const;

	void SetBool(bool bValue) const;
	void SetInt(int iValue) const;
	void SetFloat(float flValue) const;
	void SetString(const char *szValue) const;

private:
	CConVar *pOriginalCVar = nullptr;
	CConVar *pDummyCVar = nullptr;
	char szDummyName[128] = {};
	char szDummyValue[128] = {};
	char szOriginalName[128] = {};
	char szOriginalValue[128] = {};
	int iOriginalFlags = 0;
};
