#ifndef WINDOWSITEM_H
#define WINDOWSITEM_H
#include <Windows.h>
#include <string>
#include <list>

/**
    A class encapsulating an 'HWND' and various
    windows functions that act on such items
*/
class WindowsItem
{
    public:
        WindowsItem();

        void DestroyThis();

        bool operator==(HWND hWnd); // Tests whether the encapsulated handle equals this handle
        HWND getHandle();
        HWND getParent();

        std::string GetTitle();
        bool getWindowRect(RECT &rect);
        int Width();
        int Height();
        int Left();
        int Top();
        int Right();
        int Bottom();
        bool getClientRect(RECT &rect);
        LONG cliWidth();
        LONG cliHeight();
        HDC getDC(); // Gets the current device context
        bool isEnabled();

        LONG GetWinLong(int index);
        void SetWinLong(int index, LONG newLong);

        void SetFont(HFONT font, bool redrawImmediately);
        void ReplaceChildFonts(HFONT hFont);
        void LockCursor(); // Prevents cursor from leaving this window
        void UnlockCursor(); // Globally unlocks the cursor
        void TrackMouse(DWORD hoverTime); // Causes mouse tracking messages to be sent to this window
        bool SetParent(HWND hParent);
        void SetRedraw(bool autoRedraw);
        virtual void RedrawThis();
        void RefreshFrame();

        void MoveTo(int x, int y);
        void SetPos(int x, int y, int width, int height);
        void ShowNormal();
        void Show();
        void Hide();
        void SetSmallIcon(HANDLE hIcon);
        void SetMedIcon(HANDLE hIcon);
        bool SetTitle(const std::string& newTitle);
        bool AddTooltip(const char* text);

        bool ReleaseDC(HDC hDC);
        void FocusThis();
        void UpdateWindow();
        void DisableThis();
        void EnableThis();
        void SetWidth(int newWidth);
        void SetHeight(int newHeight);
        void SetSize(int newWidth, int newHeight);

    protected:
        virtual void setHandle(HWND hWnd);

        /** Attempts to register a class for creating the window
        If the class has been registered before this returns false
        Do not register different classes with the same name */
        bool RegisterWindowClass(UINT style, HICON hIcon, HCURSOR hCursor, HBRUSH hbrBackground,
            LPCTSTR lpszMenuName, LPCTSTR lpszClassName, HICON hIconSm, WNDPROC wndProc);

        /** Returns whether the window class given by lpszClassName is registered,
        if it is, then this class name will be set to create the window with */
        bool WindowClassIsRegistered(LPCTSTR lpszClassName);

        /** This method is used to compare list view items for windows sort functions
            ForwardCompareLvItems must be set as the function and the class pointer as LPARAM */
        virtual int CompareLvItems(LPARAM index1, LPARAM index2);

        /** This method returns the value given by CompareLvItems with the same parameters
            This should be passed as the proc to window's built in sort items functions */
        static int CALLBACK ForwardCompareLvItems(LPARAM index1, LPARAM index2, LPARAM lParam);

        std::string &WindowClassName();

        HDC StartSimplePaint();
        HDC StartBufferedPaint();
        HDC GetPaintDc();
        void EndPaint();

        int PaintWidth();
        int PaintHeight();

        void FillPaintArea(HBRUSH hBrush);
        void FrameRect(HBRUSH hBrush, RECT &rect);

    private:
        HWND windowsItemHandle; // Handle to the window this class encapsulates
        HWND tooltipHandle; // Handle to any tooltip created for this class
        std::string windowClassName; // May contain the window class title before the window is created
        static std::list<std::string> registeredClasses; // Contains the names of all window classes registered by this class

        RECT paintRect;
        int paintWidth;
        int paintHeight;
        HDC paintDc;
        HDC paintFinalDc;
        HBITMAP paintMemBitmap;
        enum class PaintStatus { NotPainting, SimplePaint, BufferedPaint };
        PaintStatus paintStatus;
};

#endif
