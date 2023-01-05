#include "convar.h"
#include "interfaces.h"

CSpoofedConVar::CSpoofedConVar(const char *szCVar) {
	pOriginalCVar = I::ConVar->FindVar(szCVar);
	Spoof();
}

CSpoofedConVar::CSpoofedConVar(CConVar *pCVar) {
	pOriginalCVar = pCVar;
	Spoof();
}

CSpoofedConVar::~CSpoofedConVar() {
	if (IsSpoofed()) {
		SetFlags(iOriginalFlags);
		SetString(szOriginalValue);

		CWrappedProtect protection = CWrappedProtect{(LPVOID)pOriginalCVar->szName, 128UL, PAGE_READWRITE};
		strcpy_s(const_cast<char *>(pOriginalCVar->szName), sizeof(szOriginalName), szOriginalName);

		I::ConVar->UnregisterConCommand(pDummyCVar);
		free(pDummyCVar);
		pDummyCVar = nullptr;
	}
}

bool CSpoofedConVar::IsSpoofed() const {
	return pDummyCVar != nullptr;
}

void CSpoofedConVar::Spoof() {
	if (!IsSpoofed() && pOriginalCVar != nullptr) {
		iOriginalFlags = pOriginalCVar->nFlags;
		strcpy_s(szOriginalName, pOriginalCVar->szName);
		strcpy_s(szOriginalValue, pOriginalCVar->szDefaultValue);
		sprintf_s(szDummyName, 128U, XorStr("qo0_%s"), szOriginalName);

		pDummyCVar = static_cast<CConVar *>(malloc(sizeof(CConVar)));

		if (pDummyCVar == nullptr)
			return;

		memcpy(pDummyCVar, pOriginalCVar, sizeof(CConVar));
		pDummyCVar->pNext = nullptr;

		I::ConVar->RegisterConCommand(pDummyCVar);

		CWrappedProtect protection = CWrappedProtect{(LPVOID)pOriginalCVar->szName, 128UL, PAGE_READWRITE};

		strcpy_s(const_cast<char *>(pOriginalCVar->szName), sizeof(szDummyName), szDummyName);

		SetFlags(FCVAR_NONE);
	}
}

void CSpoofedConVar::SetFlags(int nFlags) const {
	if (IsSpoofed())
		pOriginalCVar->nFlags = nFlags;
}

int CSpoofedConVar::GetFlags() const {
	return pOriginalCVar->nFlags;
}

void CSpoofedConVar::SetInt(int iValue) const {
	if (IsSpoofed())
		pOriginalCVar->SetValue(iValue);
}

void CSpoofedConVar::SetBool(bool bValue) const {
	if (IsSpoofed())
		pOriginalCVar->SetValue(bValue);
}

void CSpoofedConVar::SetFloat(float flValue) const {
	if (IsSpoofed())
		pOriginalCVar->SetValue(flValue);
}

void CSpoofedConVar::SetString(const char *szValue) const {
	if (IsSpoofed())
		pOriginalCVar->SetValue(szValue);
}