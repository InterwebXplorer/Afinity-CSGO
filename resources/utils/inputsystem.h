#pragma once
#include <array>
#include <Windows.h>

enum class KeyState : int {
	NONE,
	DOWN,
	UP,
	RELEASED
}

namespace InputSystem {
	inline HWND	Window = nullptr;
	inline WNDPROC OldWndProc = nullptr;
	inline std::array<KeyState, 256U> LastKeyState = { };

	bool Setup();
	void Restore();
	bool Process(UINT Msg, WPARAM WideParam, LPARAM LongParam);

	inline bool IsKeyDown(const std::uint32_t ButtonCode) {
		return LastKeyState.at(ButtonCode) == KeyState::DOWN;
	}

	inline bool IsKeyReleased(const std::uint32_t ButtonCode) {
		if (LastKeyState.at(ButtonCode) == KeyState::RELEASED) {
			LastKeyState.at(ButtonCode) = KeyState::UP;
			return true;
		}
		return false;
	}

	/*--------------------Extra Input Shit--------------------*/

	bool UpdateTargetOptionState(Options& TargetOption, Options TargetOptionKey, Options TargetOptionMode);
}