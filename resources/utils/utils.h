#pragma once
#include <windows.h>
#include "../imgui/freetype/imgui_freetype.h"
#include "../sdk/datatypes/vector.h"
#include "../sdk/interfaces/imaterialsystem.h"
#include "eventlistener.h"
#include "entitylistener.h"

class CTimer {
public:
	CTimer(const bool bStart = false) {
		if (bStart)
			Reset();
	}

	void Reset() {
		timePoint = std::chrono::high_resolution_clock::now();
	}

	template <class C = std::chrono::milliseconds>
	[[nodiscard]] auto Elapsed() const {
		return std::chrono::duration_cast<C>(std::chrono::high_resolution_clock::now() - timePoint).count();
	}

private:
	std::chrono::high_resolution_clock::time_point timePoint = {};
};

namespace Utils {
	std::uintptr_t* FindHudElement(const char* Name);
	void ForceFullUpdate();
	bool LineGoesThroughSmoke(const Vector &Start, const Vector &End, const bool GrenadeBloat);
	void SetLocalPlayerReady();
	void SendName(const char* Name);
	void SendClanTag(const char* ClanTag, const char* Identifier);
	bool PrecacheModel(const char* ModelName);
	IClientNetworkable* CreateDLLEntity(int Entity, EClassIndex ClassID, int Serial);
	std::string UnicodeToMultiByte(const std::wstring_view Unicode);
	std::wstring MultiByteToUnicode(const std::string_view Ascii);
	void ColorConvertRGBAtoHSV(float r, float g, float b, float a, float& h, float& s, float& v);
	void ColorConvertHSVtoRGBA(float h, float s, float v, float& r, float& g, float& b, float& a);
	const char* GetChamsMaterialFromOption(Options TargetOption);
}