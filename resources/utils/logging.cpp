#include "logging.h"

bool L::Attach(const char *szConsoleTitle)
{
	if (!AllocConsole())
		return false;

	AttachConsole(ATTACH_PARENT_PROCESS);

	if (freopen_s(&pStream, XorStr("CONOUT$"), XorStr("w"), stdout) != 0)
		return false;

	if (!SetConsoleTitle(szConsoleTitle))
		return false;

	return true;
}

void L::Detach()
{
	fclose(pStream);

	FreeConsole();

	if (const auto hConsoleWnd = GetConsoleWindow(); hConsoleWnd != nullptr)

		PostMessageW(hConsoleWnd, WM_CLOSE, 0U, 0L);
}
