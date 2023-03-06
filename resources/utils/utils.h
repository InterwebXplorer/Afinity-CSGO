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

namespace U {
	std::uintptr_t *FindHudElement(const char *szName);
	void ForceFullUpdate();
	bool LineGoesThroughSmoke(const Vector &vecStart, const Vector &vecEnd, const bool bGrenadeBloat = true);
	void SetLocalPlayerReady();
	void SendName(const char *szName);
	void SendClanTag(const char *szClanTag, const char *szIdentifier);
	bool PrecacheModel(const char *szModelName);
	IClientNetworkable *CreateDLLEntity(int iEntity, EClassIndex nClassID, int nSerial);
	const char8_t *GetWeaponIcon(short nItemDefinitionIndex);
	void FlashWindow(HWND pWindow);
	std::string UnicodeToMultiByte(const std::wstring_view wszUnicode);
	std::wstring MultiByteToUnicode(const std::string_view szAscii);
	inline CEventListener EventListener;
	inline CEntityListener EntityListener;

	/*----------------------Extra Shit----------------------*/

	void U::ColorConvertRGBAtoHSV(float r, float g, float b, float a, float& h, float& s, float& v);
	void U::ColorConvertHSVtoRGBA(float h, float s, float v, float& r, float& g, float& b, float& a);
}