#ifndef FORCES_H
#define FORCES_H
#include "Common Files/CommonFiles.h"
#include "Mapping Core/MappingCore.h"
#include "Windows UI/WindowsUI.h"

class ForcesWindow : public ClassWindow
{
	public:
		ForcesWindow();
		bool CreateThis(HWND hParent);

	private:
		LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		UINT WM_DRAGNOTIFY;
		u8 playerBeingDragged;
};

#endif