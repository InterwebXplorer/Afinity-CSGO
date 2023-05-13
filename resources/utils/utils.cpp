#include <fstream>
#include "utils.h"
#include "filelogging.h"
#include "../sdk/interfaces.h"
#include "../../options.h"

std::uintptr_t* Utils::FindHudElement(const char* Name) {
	static auto Hud = *reinterpret_cast<void **>(MEM::FindPattern(CLIENT_DLL, "B9 ? ? ? ? 68 ? ? ? ? E8 ? ? ? ? 89") + 0x1);

	using FindHudElementFn = std::uintptr_t *(__thiscall *)(void *, const char *);
	static auto FindHudElement = reinterpret_cast<FindHudElementFn>(MEM::FindPattern(CLIENT_DLL, "55 8B EC 53 8B 5D 08 56 57 8B F9 33 F6 39 77 28"));
	assert(FindHudElement != nullptr);

	return FindHudElement(Hud, Name);
}

void Utils::ForceFullUpdate() {
	using ClearHudWeaponIconFn = int(__thiscall *)(void *, int);
	static auto FindHudElement = reinterpret_cast<ClearHudWeaponIconFn>(MEM::FindPattern(CLIENT_DLL, "55 8B EC 51 53 56 8B 75 08 8B D9 57 6B"));
	assert(FindHudElement != nullptr);

	if (const auto HudWeapons = FindHudElement("CCSGO_HudWeaponSelection") - 0x28; HudWeapons != nullptr) {

		for (std::size_t i = 0; i < *(HudWeapons + 0x20); i++)
			i = oClearHudWeaponIcon(HudWeapons, i);
	}

	I::ClientState->iDeltaTick = -1;
}

bool Utils::LineGoesThroughSmoke(const Vector &Start, const Vector &End, const bool GrenadeBloat) {
	using LineGoesThroughSmokeFn = bool(__cdecl *)(Vector, Vector, bool);
	static auto LineGoesThroughSmoke = reinterpret_cast<LineGoesThroughSmokeFn>(MEM::FindPattern(CLIENT_DLL, "55 8B EC 83 EC 08 8B 15 ? ? ? ? 0F 57 C0"));
	assert(LineGoesThroughSmoke != nullptr);

	return LineGoesThroughSmoke(Start, End, GrenadeBloat);
}

void Utils::SetLocalPlayerReady() {
	using SetLocalPlayerReadyFn = void(__stdcall *)(const char *);
	static auto SetLocalPlayerReady = reinterpret_cast<SetLocalPlayerReadyFn>(MEM::FindPattern(CLIENT_DLL, "55 8B EC 83 E4 F8 8B 4D 08 BA ? ? ? ? E8 ? ? ? ? 85 C0 75 12"));
	assert(SetLocalPlayerReady != nullptr);

	SetLocalPlayerReady("");
}

void Utils::SendName(const char* Name) {
	static CConVar *name = I::ConVar->FindVar("name");
	name->fnChangeCallbacks.Size() = NULL;

	if (name != nullptr)
		name->SetValue(Name);
}

void Utils::SendClanTag(const char* ClanTag, const char* Identifier) {
	using SendClanTagFn = void(__fastcall *)(const char *, const char *);
	static auto SendClanTag = reinterpret_cast<SendClanTagFn>(MEM::FindPattern(ENGINE_DLL, "53 56 57 8B DA 8B F9 FF 15"));
	assert(SendClanTag != nullptr);

	SendClanTag(ClanTag, Identifier);
}

bool Utils::PrecacheModel(const char* ModelName) {
	if (auto ModelPrecache = I::NetworkContainer->FindTable("modelprecache"); ModelPrecache != nullptr) {
		if (I::ModelInfo->FindOrLoadModel(ModelName) == nullptr)
			return false;

		if (ModelPrecache->AddString(false, ModelName) == INVALID_STRING_INDEX)
			return false;
	}

	return true;
}

IClientNetworkable* Utils::CreateDLLEntity(int Entity, EClassIndex ClassID, int Serial) {
	for (auto Class = I::Client->GetAllClasses(); Class != nullptr; Class = Class->Next) {
		if (Class->ClassID == ClassID)
			return Class->pCreateFn(Entity, Serial);
	}

	return nullptr;
}

std::string Utils::UnicodeToMultiByte(const std::wstring_view Unicode) {
	const int Length = WideCharToMultiByte(CP_UTF8, 0UL, Unicode.data(), Unicode.length(), nullptr, 0, nullptr, nullptr);
	std::string Output = {};

	if (Length > 0) {
		Output.resize(Length);
		WideCharToMultiByte(CP_UTF8, 0UL, Unicode.data(), Unicode.length(), &Output[0], Length, nullptr, nullptr);
	}

	return Output;
}

std::wstring Utils::MultiByteToUnicode(const std::string_view Ascii) {
	const int Length = MultiByteToWideChar(CP_UTF8, 0UL, Ascii.data(), Ascii.length(), nullptr, 0);
	std::wstring Output = {};

	if (Length > 0) {
		Output.resize(Length);
		MultiByteToWideChar(CP_UTF8, 0UL, Ascii.data(), Ascii.length(), &Output[0], Length);
	}

	return Output;
}

void Utils::ColorConvertRGBAtoHSV(float r, float g, float b, float a, float& h, float& s, float& v) {
	if (a == 0)
		return;

	float r = r / 255 / a;
	float g = g / 255 / a;
	float b = b / 255 / a;

	float MaxValue = std::fmax(r, std::fmax(g, b));
	float MinValue = std::fmin(r, std::fmin(g, b));

	if (MaxValue == MinValue) {
        h = 0;
        s = 0;
        v = static_cast<int>(std::round(MaxValue * 100));
        return;
    }

	if (MaxValue == r) {
        h = static_cast<int>(std::round(60 * ((g - b) / (MaxValue - MinValue))));
    } else if (MaxValue == g) {
        h = static_cast<int>(std::round(60 * ((b - r) / (MaxValue - MinValue)) + 120));
    } else {
        h = static_cast<int>(std::round(60 * ((r - g) / (MaxValue - MinValue)) + 240));
    }

	h = (h + 360) % 360;
	s = static_cast<int>(std::round(100 * (MaxValue - MinValue) / MaxValue));
    v = static_cast<int>(std::round(MaxValue * 100));
}

void Utils::ColorConvertHSVtoRGBA(float h, float s, float v, float& r, float& g, float& b, float& a) {
	if (s < 0 || s > 100 || v < 0 || v > 100)
		return;

	float NormalizedHue = std::fmod(h, 360) / 60;
	float Chroma = v / 100 * s / 100;
	float x = Chroma * (1 - std::fabs(std::fmod(NormalizedHue, 2) - 1));

	if (NormalizedHue < 1) {
        r = Chroma;
        g = x;
        b = 0;
    } else if (NormalizedHue < 2) {
        r = x;
        g = Chroma;
        b = 0;
    } else if (NormalizedHue < 3) {
        r = 0;
        g = Chroma;
        b = x;
    } else if (NormalizedHue < 4) {
        r = 0;
        g = x;
        b = Chroma;
    } else if (NormalizedHue < 5) {
        r = x;
        g = 0;
        b = Chroma;
    } else if (NormalizedHue < 6) {
        r = Chroma;
        g = 0;
        b = x;
    } else {
        r = 0;
        g = 0;
        b = 0;
    }

	float m = v / 100 - Chroma;
	
	r = (r + m) * a;
    g = (g + m) * a;
    b = (b + m) * a;
}

const char* Utils::GetChamsMaterialFromOption(Options TargetOption) {
	switch (TargetOption) {
		case FLAT:
			return "";
		case GLASS:
			return "models/inventory_items/cologne_prediction/cologne_prediction_glass";
		case CRYSTAL:
			return "models/inventory_items/trophy_majors/crystal_clear";
		case PLATINUM:
			return "models/player/ct_fbi/ct_fbi_glass";
		case GOLD:
			return "models/inventory_items/trophy_majors/gold";
		case GLOSS:
			return "models/inventory_items/trophy_majors/gloss";
		default:
			return "";
	}
}