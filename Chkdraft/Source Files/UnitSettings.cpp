#include "UnitSettings.h"
#include "GuiAccel.h"

bool UnitSettingsWindow::CreateThis(HWND hParent)
{
	if ( ClassWindow::RegisterWindowClass(NULL, NULL, NULL, NULL, NULL, "UnitSettings", NULL, false) &&
		 ClassWindow::CreateClassWindow(NULL, "UnitSettings", WS_VISIBLE|WS_CHILD, 4, 22, 592, 524, hParent, (HMENU)ID_UNITSETTINGS) )
	{
		CreateStaticText(getHandle(), 5, 5, 100, 20, "Unit Settings...");
		return true;
	}
	else
		return false;
}

LRESULT UnitSettingsWindow::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch ( msg )
	{
		case REFRESH_WINDOW:
			break;

		default:
			return DefWindowProc(hWnd, msg, wParam, lParam);
			break;
	}
	return 0;
}