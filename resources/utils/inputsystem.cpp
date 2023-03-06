#include <thread>
#include "inputsystem.h"
#include "../../hooks.h"
#include "../../options.h"
#include "../../global.h"

bool InputSystem::Setup() {
	D3DDEVICE_CREATION_PARAMETERS CreationParameters = { };
	while (FAILED(I::DirectDevice->GetCreationParameters(&CreationParameters)))
		std::this_thread::sleep_for(200ms);

	Window = creationParameters.hFocusWindow;

	if (Window == nullptr)
		return false;

	OldWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(Window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(Hooks::WndProc)));

	if (OldWndProc == nullptr)
		return false;

	return true;
}

void InputSystem::Restore() {
	if (OldWndProc != nullptr) {
		SetWindowLongPtrW(Window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(OldWndProc));
		OldWndProc = nullptr;
	}

	I::InputSystem->EnableInput(true);
}

bool InputSystem::Process(UINT Msg, WPARAM WideParam, LPARAM LongParam) {
	if (Global::MenuOpen || Options.misc_general_unload)
		return false;

	int ActiveKey = 0;
	KeyState ActiveKeyState = KeyState::NONE;

	switch (Msg) {
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		if (WideParam < 256U) {
			ActiveKey = WideParam;
			ActiveKeyState = KeyState::DOWN;
		}
		break;
	case WM_KEYUP:
	case WM_SYSKEYUP:
		if (WideParam < 256U) {
			ActiveKey = WideParam;
			ActiveKeyState = KeyState::UP;
		}
		break;
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_LBUTTONDBLCLK:
		ActiveKey = VK_LBUTTON;
		ActiveKeyState = Msg == WM_LBUTTONUP ? KeyState::UP : KeyState::DOWN;
		break;
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_RBUTTONDBLCLK:
		ActiveKey = VK_RBUTTON;
		ActiveKeyState = Msg == WM_RBUTTONUP ? KeyState::UP : KeyState::DOWN;
		break;
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MBUTTONDBLCLK:
		ActiveKey = VK_MBUTTON;
		ActiveKeyState = Msg == WM_MBUTTONUP ? KeyState::UP : KeyState::DOWN;
		break;
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	case WM_XBUTTONDBLCLK:
		ActiveKey = (GET_XBUTTON_WPARAM(WideParam) == XBUTTON1 ? VK_XBUTTON1 : VK_XBUTTON2);
		ActiveKeyState = Msg == WM_XBUTTONUP ? KeyState::UP : KeyState::DOWN;
		break;
	default:
		return false;
	}

	if (ActiveKeyState == KeyState::UP && KeyState.at(ActiveKey) == KeyState::DOWN)
		LastKeyState.at(ActiveKey) = KeyState::RELEASED;
	else
		LastKeyState.at(ActiveKey) = ActiveKeyState;

	return true;
}

/*--------------------Extra Input Shit--------------------*/

bool InputSystem::UpdateTargetOptionState(Options& TargetOption, Options TargetOptionKey, Options TargetOptionMode) {
	if (!TargetOption)
		return false;
	
	if (!TargetOptionKey && TargetOptionMode != ALWAYS)
		return false;

	if (!TargetOptionMode)
		return false;

	Switch(TargetOptionMode) {
		case ALWAYS:
			TargetOption = true;
			break;

		case TOGGLE:
			if (IPT::IsKeyDown(TargetOptionKey))
				TargetOption = !TargetOption;
			break;

		case ONHOLD:
			if (IPT::IsKeyDown(TargetOptionKey))
				TargetOption = true;
			else
				TargetOption = false;
			break;

		case OFFHOLD:
			if (IPT::IsKeyDown(TargetOptionKey))
				TargetOption = false;
			else 
				TargetOption = true;
			break;
	}

	return TargetOption;
}