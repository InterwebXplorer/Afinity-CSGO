#include <fstream>
#include "utils.h"
#include "logging.h"
#include "../sdk/interfaces.h"

#pragma region utilities_get
std::uintptr_t *U::FindHudElement(const char *szName)
{

	static auto pHud = *reinterpret_cast<void **>(MEM::FindPattern(CLIENT_DLL, XorStr("B9 ? ? ? ? 68 ? ? ? ? E8 ? ? ? ? 89")) + 0x1);

	using FindHudElementFn = std::uintptr_t *(__thiscall *)(void *, const char *);
	static auto oFindHudElement = reinterpret_cast<FindHudElementFn>(MEM::FindPattern(CLIENT_DLL, XorStr("55 8B EC 53 8B 5D 08 56 57 8B F9 33 F6 39 77 28")));
	assert(oFindHudElement != nullptr);

	return oFindHudElement(pHud, szName);
}
#pragma endregion

#pragma region utilities_game
void U::ForceFullUpdate()
{
	using ClearHudWeaponIconFn = int(__thiscall *)(void *, int);
	static auto oClearHudWeaponIcon = reinterpret_cast<ClearHudWeaponIconFn>(MEM::FindPattern(CLIENT_DLL, XorStr("55 8B EC 51 53 56 8B 75 08 8B D9 57 6B")));
	assert(oClearHudWeaponIcon != nullptr);

	if (const auto pHudWeapons = FindHudElement(XorStr("CCSGO_HudWeaponSelection")) - 0x28; pHudWeapons != nullptr)
	{

		for (std::size_t i = 0; i < *(pHudWeapons + 0x20); i++)
			i = oClearHudWeaponIcon(pHudWeapons, i);
	}

	I::ClientState->iDeltaTick = -1;
}

bool U::LineGoesThroughSmoke(const Vector &vecStart, const Vector &vecEnd, const bool bGrenadeBloat)
{
	using LineGoesThroughSmokeFn = bool(__cdecl *)(Vector, Vector, bool);
	static auto oLineGoesThroughSmoke = reinterpret_cast<LineGoesThroughSmokeFn>(MEM::FindPattern(CLIENT_DLL, XorStr("55 8B EC 83 EC 08 8B 15 ? ? ? ? 0F 57 C0")));
	assert(oLineGoesThroughSmoke != nullptr);

	return oLineGoesThroughSmoke(vecStart, vecEnd, bGrenadeBloat);
}

void U::SetLocalPlayerReady()
{
	using SetLocalPlayerReadyFn = void(__stdcall *)(const char *);
	static auto oSetLocalPlayerReady = reinterpret_cast<SetLocalPlayerReadyFn>(MEM::FindPattern(CLIENT_DLL, XorStr("55 8B EC 83 E4 F8 8B 4D 08 BA ? ? ? ? E8 ? ? ? ? 85 C0 75 12")));
	assert(oSetLocalPlayerReady != nullptr);

	oSetLocalPlayerReady("");
}

void U::SendName(const char *szName)
{
	static CConVar *name = I::ConVar->FindVar(XorStr("name"));
	name->fnChangeCallbacks.Size() = NULL;

	if (name != nullptr)
		name->SetValue(szName);
}

void U::SendClanTag(const char *szClanTag, const char *szIdentifier)
{
	using SendClanTagFn = void(__fastcall *)(const char *, const char *);
	static auto oSendClanTag = reinterpret_cast<SendClanTagFn>(MEM::FindPattern(ENGINE_DLL, XorStr("53 56 57 8B DA 8B F9 FF 15")));
	assert(oSendClanTag != nullptr);

	oSendClanTag(szClanTag, szIdentifier);
}

bool U::PrecacheModel(const char *szModelName)
{
	if (auto pModelPrecache = I::NetworkContainer->FindTable(XorStr("modelprecache")); pModelPrecache != nullptr)
	{
		if (I::ModelInfo->FindOrLoadModel(szModelName) == nullptr)
			return false;

		if (pModelPrecache->AddString(false, szModelName) == INVALID_STRING_INDEX)
			return false;
	}

	return true;
}

IClientNetworkable *U::CreateDLLEntity(int iEntity, EClassIndex nClassID, int nSerial)
{
	for (auto pClass = I::Client->GetAllClasses(); pClass != nullptr; pClass = pClass->pNext)
	{
		if (pClass->nClassID == nClassID)
			return pClass->pCreateFn(iEntity, nSerial);
	}

	return nullptr;
}

const char8_t *U::GetWeaponIcon(short nItemDefinitionIndex)
{

	switch (nItemDefinitionIndex)
	{
	case WEAPON_DEAGLE:
		return u8"\uE001";
	case WEAPON_ELITE:
		return u8"\uE002";
	case WEAPON_FIVESEVEN:
		return u8"\uE003";
	case WEAPON_GLOCK:
		return u8"\uE004";
	case WEAPON_AK47:
		return u8"\uE007";
	case WEAPON_AUG:
		return u8"\uE008";
	case WEAPON_AWP:
		return u8"\uE009";
	case WEAPON_FAMAS:
		return u8"\uE00A";
	case WEAPON_G3SG1:
		return u8"\uE00B";
	case WEAPON_GALILAR:
		return u8"\uE00D";
	case WEAPON_M249:
		return u8"\uE00E";
	case WEAPON_M4A1:
		return u8"\uE010";
	case WEAPON_MAC10:
		return u8"\uE011";
	case WEAPON_P90:
		return u8"\uE013";
	case WEAPON_MP5SD:
		return u8"\uE017";
	case WEAPON_UMP45:
		return u8"\uE018";
	case WEAPON_XM1014:
		return u8"\uE019";
	case WEAPON_BIZON:
		return u8"\uE01A";
	case WEAPON_MAG7:
		return u8"\uE01B";
	case WEAPON_NEGEV:
		return u8"\uE01C";
	case WEAPON_SAWEDOFF:
		return u8"\uE01D";
	case WEAPON_TEC9:
		return u8"\uE01E";
	case WEAPON_TASER:
		return u8"\uE01F";
	case WEAPON_HKP2000:
		return u8"\uE020";
	case WEAPON_MP7:
		return u8"\uE021";
	case WEAPON_MP9:
		return u8"\uE022";
	case WEAPON_NOVA:
		return u8"\uE023";
	case WEAPON_P250:
		return u8"\uE024";
	case WEAPON_SCAR20:
		return u8"\uE026";
	case WEAPON_SG556:
		return u8"\uE027";
	case WEAPON_SSG08:
		return u8"\uE028";
	case WEAPON_KNIFE:
		return u8"\uE02A";
	case WEAPON_FLASHBANG:
		return u8"\uE02B";
	case WEAPON_HEGRENADE:
		return u8"\uE02C";
	case WEAPON_SMOKEGRENADE:
		return u8"\uE02D";
	case WEAPON_MOLOTOV:
		[[fallthrough]];
	case WEAPON_FIREBOMB:
		return u8"\uE02E";
	case WEAPON_DECOY:
		[[fallthrough]];
	case WEAPON_DIVERSION:
		return u8"\uE02F";
	case WEAPON_INCGRENADE:
		return u8"\uE030";
	case WEAPON_C4:
		return u8"\uE031";
	case WEAPON_HEALTHSHOT:
		return u8"\uE039";
	case WEAPON_KNIFE_GG:
		[[fallthrough]];
	case WEAPON_KNIFE_T:
		return u8"\uE03B";
	case WEAPON_M4A1_SILENCER:
		return u8"\uE03C";
	case WEAPON_USP_SILENCER:
		return u8"\uE03D";
	case WEAPON_CZ75A:
		return u8"\uE03F";
	case WEAPON_REVOLVER:
		return u8"\uE040";
	case WEAPON_TAGRENADE:
		return u8"\uE044";
	case WEAPON_FISTS:
		return u8"\uE045";
	case WEAPON_TABLET:
		return u8"\uE048";
	case WEAPON_MELEE:
		return u8"\uE04A";
	case WEAPON_AXE:
		return u8"\uE04B";
	case WEAPON_HAMMER:
		return u8"\uE04C";
	case WEAPON_SPANNER:
		return u8"\uE04E";
	case WEAPON_KNIFE_BAYONET:
		return u8"\uE1F4";
	case WEAPON_KNIFE_CSS:
		return u8"\uE1F7";
	case WEAPON_KNIFE_FLIP:
		return u8"\uE1F9";
	case WEAPON_KNIFE_GUT:
		return u8"\uE1FA";
	case WEAPON_KNIFE_KARAMBIT:
		return u8"\uE1FB";
	case WEAPON_KNIFE_M9_BAYONET:
		return u8"\uE1FC";
	case WEAPON_KNIFE_TACTICAL:
		return u8"\uE1FD";
	case WEAPON_KNIFE_FALCHION:
		return u8"\uE200";
	case WEAPON_KNIFE_SURVIVAL_BOWIE:
		return u8"\uE202";
	case WEAPON_KNIFE_BUTTERFLY:
		return u8"\uE203";
	case WEAPON_KNIFE_PUSH:
		return u8"\uE204";
	case WEAPON_KNIFE_CORD:
		return u8"\uE205";
	case WEAPON_KNIFE_CANIS:
		return u8"\uE206";
	case WEAPON_KNIFE_URSUS:
		return u8"\uE207";
	case WEAPON_KNIFE_GYPSY_JACKKNIFE:
		return u8"\uE208";
	case WEAPON_KNIFE_OUTDOOR:
		return u8"\uE209";
	case WEAPON_KNIFE_STILETTO:
		return u8"\uE20A";
	case WEAPON_KNIFE_WIDOWMAKER:
		return u8"\uE20B";
	case WEAPON_KNIFE_SKELETON:
		return u8"\uE20D";
	default:
		return u8"\u003F";
	}
}
#pragma endregion

#pragma region utilities_extra
void U::FlashWindow(HWND pWindow)
{
	FLASHWINFO fwInfo = {};
	fwInfo.cbSize = sizeof(FLASHWINFO);
	fwInfo.hwnd = pWindow;
	fwInfo.dwFlags = FLASHW_ALL | FLASHW_TIMERNOFG;
	fwInfo.uCount = 0;
	fwInfo.dwTimeout = 0;
	FlashWindowEx(&fwInfo);
}
#pragma endregion

#pragma region utilities_string
std::string U::UnicodeToMultiByte(const std::wstring_view wszUnicode)
{
	const int nLength = WideCharToMultiByte(CP_UTF8, 0UL, wszUnicode.data(), wszUnicode.length(), nullptr, 0, nullptr, nullptr);
	std::string szOutput = {};

	if (nLength > 0)
	{
		szOutput.resize(nLength);
		WideCharToMultiByte(CP_UTF8, 0UL, wszUnicode.data(), wszUnicode.length(), &szOutput[0], nLength, nullptr, nullptr);
	}

	return szOutput;
}

std::wstring U::MultiByteToUnicode(const std::string_view szAscii)
{
	const int nLength = MultiByteToWideChar(CP_UTF8, 0UL, szAscii.data(), szAscii.length(), nullptr, 0);
	std::wstring wszOutput = {};

	if (nLength > 0)
	{
		wszOutput.resize(nLength);
		MultiByteToWideChar(CP_UTF8, 0UL, szAscii.data(), szAscii.length(), &wszOutput[0], nLength);
	}

	return wszOutput;
}
#pragma endregion

/*---------------------Extra Shit---------------------*/

void U::ColorConvertRGBAtoHSV(float r, float g, float b, float a, float& h, float& s, float& v) {
	if (a == 0)
		return;

	float r = r / 255 / a;
	float g = g / 255 / a;
	float b = b / 255 / a;

	float maxvalue = std::fmax(r, std::fmax(g, b));
	float minvalue = std::fmin(r, std::fmin(g, b));

	if (maxValue == minValue) {
        h = 0;
        s = 0;
        v = static_cast<int>(std::round(maxValue * 100));
        return;
    }

	if (maxValue == r) {
        h = static_cast<int>(std::round(60 * ((g - b) / (maxValue - minValue))));
    } else if (maxValue == g) {
        h = static_cast<int>(std::round(60 * ((b - r) / (maxValue - minValue)) + 120));
    } else {
        h = static_cast<int>(std::round(60 * ((r - g) / (maxValue - minValue)) + 240));
    }

	h = (h + 360) % 360;
	s = static_cast<int>(std::round(100 * (maxValue - minValue) / maxValue));
    v = static_cast<int>(std::round(maxValue * 100));
}

void U::ColorConvertHSVtoRGBA(float h, float s, float v, float& r, float& g, float& b, float& a) {
	if (s < 0 || s > 100 || v < 0 || v > 100)
		return;

	float normalizedHue = std::fmod(h, 360) / 60;
	float chroma = v / 100 * s / 100;
	float x = chroma * (1 - std::fabs(std::fmod(normalizedHue, 2) - 1));

	if (normalizedHue < 1) {
        r = chroma;
        g = x;
        b = 0;
    } else if (normalizedHue < 2) {
        r = x;
        g = chroma;
        b = 0;
    } else if (normalizedHue < 3) {
        r = 0;
        g = chroma;
        b = x;
    } else if (normalizedHue < 4) {
        r = 0;
        g = x;
        b = chroma;
    } else if (normalizedHue < 5) {
        r = x;
        g = 0;
        b = chroma;
    } else if (normalizedHue < 6) {
        r = chroma;
        g = 0;
        b = x;
    } else {
        r = 0;
        g = 0;
        b = 0;
    }

	float m = v / 100 - chroma;
	
	r = (r + m) * a;
    g = (g + m) * a;
    b = (b + m) * a;
}