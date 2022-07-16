#pragma once
#include <array>
#include <windows.h>

enum class EKeyState : int
{
	NONE,
	DOWN,
	UP,
	RELEASED
};

namespace IPT
{
	inline HWND hWindow = nullptr;

	inline WNDPROC pOldWndProc = nullptr;

	inline std::array<EKeyState, 256U> arrKeyState = {};

	bool Setup();

	void Restore();

	bool Process(UINT uMsg, WPARAM wParam, LPARAM lParam);

	inline bool IsKeyDown(const std::uint32_t uButtonCode)
	{
		return arrKeyState.at(uButtonCode) == EKeyState::DOWN;
	}

	inline bool IsKeyReleased(const std::uint32_t uButtonCode)
	{
		if (arrKeyState.at(uButtonCode) == EKeyState::RELEASED)
		{
			arrKeyState.at(uButtonCode) = EKeyState::UP;
			return true;
		}

		return false;
	}
}
