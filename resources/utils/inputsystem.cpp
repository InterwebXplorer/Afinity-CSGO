#include <thread>
#include "inputsystem.h"
#include "../../hooks.h"
#include "variables.h"
#include "../../config.h"
#include "../../menu.h"

bool IPT::Setup()
{
	D3DDEVICE_CREATION_PARAMETERS creationParameters = {};
	while (FAILED(I::DirectDevice->GetCreationParameters(&creationParameters)))
		std::this_thread::sleep_for(200ms);

	hWindow = creationParameters.hFocusWindow;

	if (hWindow == nullptr)
		return false;

	pOldWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(hWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(H::hkWndProc)));

	if (pOldWndProc == nullptr)
		return false;

	return true;
}

void IPT::Restore()
{
	if (pOldWndProc != nullptr)
	{
		SetWindowLongPtrW(hWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(pOldWndProc));
		pOldWndProc = nullptr;
	}

	I::InputSystem->EnableInput(true);
}

bool IPT::Process(UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	if (W::bMainOpened && wParam != C::Get<int>(Vars.iMenuKey) && wParam != C::Get<int>(Vars.iPanicKey))
		return false;

	int nKey = 0;

	EKeyState state = EKeyState::NONE;

	switch (uMsg)
	{
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		if (wParam < 256U)
		{
			nKey = wParam;
			state = EKeyState::DOWN;
		}
		break;
	case WM_KEYUP:
	case WM_SYSKEYUP:
		if (wParam < 256U)
		{
			nKey = wParam;
			state = EKeyState::UP;
		}
		break;
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_LBUTTONDBLCLK:
		nKey = VK_LBUTTON;
		state = uMsg == WM_LBUTTONUP ? EKeyState::UP : EKeyState::DOWN;
		break;
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_RBUTTONDBLCLK:
		nKey = VK_RBUTTON;
		state = uMsg == WM_RBUTTONUP ? EKeyState::UP : EKeyState::DOWN;
		break;
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MBUTTONDBLCLK:
		nKey = VK_MBUTTON;
		state = uMsg == WM_MBUTTONUP ? EKeyState::UP : EKeyState::DOWN;
		break;
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	case WM_XBUTTONDBLCLK:
		nKey = (GET_XBUTTON_WPARAM(wParam) == XBUTTON1 ? VK_XBUTTON1 : VK_XBUTTON2);
		state = uMsg == WM_XBUTTONUP ? EKeyState::UP : EKeyState::DOWN;
		break;
	default:
		return false;
	}

	if (state == EKeyState::UP && arrKeyState.at(nKey) == EKeyState::DOWN)
		arrKeyState.at(nKey) = EKeyState::RELEASED;
	else
		arrKeyState.at(nKey) = state;

	return true;
}
