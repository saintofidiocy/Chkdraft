#include "ClassDialog.h"
#include <CommCtrl.h>

ClassDialog::ClassDialog() : allowEditNotify(true)
{
    WindowClassName().clear();
}

ClassDialog::~ClassDialog()
{
    if ( getHandle() != NULL )
        DestroyDialog();
}

bool ClassDialog::CreateModelessDialog(LPCSTR lpTemplateName, HWND hWndParent)
{
    if ( getHandle() == NULL )
        setHandle(CreateDialogParam(GetModuleHandle(NULL), lpTemplateName, hWndParent, SetupDialogProc, (LPARAM)this));

    if ( getHandle() != NULL )
        return true;

    return false;
}

INT_PTR ClassDialog::CreateDialogBox(LPCSTR lpTemplateName, HWND hWndParent)
{
    return DialogBoxParam(GetModuleHandle(NULL), lpTemplateName, hWndParent, SetupDialogProc, (LPARAM)this);
}

bool ClassDialog::DestroyDialog()
{
    if ( getHandle() != NULL && EndDialog(getHandle(), IDCLOSE) != 0 )
    {
        setHandle(NULL);
        allowEditNotify = true;
        return true;
    }
    else
        return false;
}

BOOL ClassDialog::DlgNotify(HWND, WPARAM, NMHDR*)
{
    return FALSE;
}

void ClassDialog::NotifyTreeSelChanged(LPARAM)
{

}

void ClassDialog::NotifyButtonClicked(int, HWND)
{

}

void ClassDialog::NotifyEditUpdated(int, HWND)
{

}

void ClassDialog::NotifyEditFocusLost(int, HWND)
{

}

void ClassDialog::NotifyWindowHidden()
{

}

void ClassDialog::NotifyWindowShown()
{

}

BOOL ClassDialog::DlgCommand(HWND, WPARAM, LPARAM)
{
    return FALSE;
}

BOOL ClassDialog::DlgProc(HWND, UINT, WPARAM, LPARAM)
{
    return FALSE;
}

void ClassDialog::SendNotifyEditUpdated(int idFrom, HWND hWndFrom)
{
    if ( allowEditNotify )
    {
        allowEditNotify = false;
        NotifyEditUpdated(idFrom, hWndFrom);
        allowEditNotify = true;
    }
}

BOOL CALLBACK ClassDialog::SetupDialogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if ( msg == WM_INITDIALOG )
    {
        LONG classPtr = lParam;
        SetWindowLong(hWnd, DWL_USER, classPtr);
        if ( GetWindowLong(hWnd, DWL_USER) == classPtr && classPtr != 0 && SetWindowLong(hWnd, DWL_DLGPROC, (LONG)ForwardDlgProc) != 0 )
        {
            ((ClassDialog*)classPtr)->setHandle(hWnd); // Preload the window handle
            return ((ClassDialog*)classPtr)->DlgProc(hWnd, msg, wParam, lParam);
        }
        else
            return FALSE;
    }
    else
        return FALSE;
}

BOOL CALLBACK ClassDialog::ForwardDlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    ClassDialog* classDialog = (ClassDialog*)GetWindowLong(hWnd, DWL_USER);
    switch ( msg )
    {
        case WM_SHOWWINDOW:
        {
            if ( (BOOL)wParam == TRUE )
                classDialog->NotifyWindowShown();
            else
            {
                classDialog->NotifyWindowHidden();
                classDialog->NotifyEditFocusLost(0, NULL);
            }
        }
        break;

        case WM_NOTIFY:
        {
            switch ( ((NMHDR*)lParam)->code )
            {
                case TVN_SELCHANGED: classDialog->NotifyTreeSelChanged(((NMTREEVIEW*)lParam)->itemNew.lParam); break;
            }
            return classDialog->DlgNotify(hWnd, wParam, (NMHDR*)lParam);
        }
        break;

        case WM_COMMAND:
        {
            switch ( HIWORD(wParam) )
            {
                case BN_CLICKED: classDialog->NotifyButtonClicked(LOWORD(wParam), (HWND)lParam); break;
                case EN_UPDATE: classDialog->SendNotifyEditUpdated(LOWORD(wParam), (HWND)lParam); break;
                case EN_KILLFOCUS: classDialog->NotifyEditFocusLost(LOWORD(wParam), (HWND)lParam); break;
            }
            return classDialog->DlgCommand(hWnd, wParam, lParam);
        }
        break;
    }
    return classDialog->DlgProc(hWnd, msg, wParam, lParam);
}
