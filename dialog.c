/* Created by John Åkerblom 10/26/2014 */

#include "downscrt.h"

#include <windows.h>
#include <commctrl.h>

#define WM_USER_PROGRESS WM_USER + 1
static HWND g_hwndDialog;
static DWORD g_dwMainThreadId;

static volatile int g_read_bytes;
static volatile int g_total_bytes;

static BOOL _CenterWindow(HWND hwnd, HWND hwnd_parent)
{
    RECT rect, rectP;
    int width, height;
    int x, y;

    GetWindowRect(hwnd, &rect);
    GetWindowRect(hwnd_parent, &rectP);

    width = rect.right - rect.left;
    height = rect.bottom - rect.top;

    x = ((rectP.right - rectP.left) - width) / 2 + rectP.left;
    y = ((rectP.bottom - rectP.top) - height) / 2 + rectP.top;

    MoveWindow(hwnd, x, y, width, height, FALSE);

    return TRUE;
}

DWORD WINAPI SignalUpdateThreadProc(LPVOID lpParameter)
{
    int read_bytes = 0;
    int total_bytes = 0;

    for (;;) {
        InterlockedExchange(&read_bytes, g_read_bytes);
        InterlockedExchange(&total_bytes, g_total_bytes);

        if (read_bytes != 0) {
            SendMessage(g_hwndDialog, WM_USER_PROGRESS, (WPARAM)read_bytes, (LPARAM)total_bytes);
        }

        if (read_bytes != 0 && read_bytes == total_bytes) {
            break;
        }

        Sleep(100);
    }

    ExitThread(0);
}

BOOL CALLBACK DownloadDlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CLOSE:
        DestroyWindow(hwnd);
        PostThreadMessage(g_dwMainThreadId, WM_QUIT, 0, 0);
        ExitProcess(0);
        break;
    case WM_INITDIALOG:
        {
            HWND progress_bar;
            g_hwndDialog = hwnd;
            g_dwMainThreadId = (DWORD)lParam;
            progress_bar = FindWindowEx(hwnd, 0, PROGRESS_CLASS, NULL);
            /* SendMessage(progress_bar, PBM_SETBARCOLOR, 0, RGB(0x8C, 0x17, 0x17)); */

            _CenterWindow(hwnd, GetDesktopWindow());
            ShowWindow(hwnd, SW_SHOW);

            CloseHandle(CreateThread(NULL, 0, SignalUpdateThreadProc, NULL, 0, NULL));
            /* SendMessage(FindWindowEx(hwnd, 0, PROGRESS_CLASS, NULL), PBM_SETMARQUEE, 1, 0); */
        }
        break;
    case WM_USER_PROGRESS:
        {
            char new_title[128];
            char new_static[128];
            char read_str[128];
            char total_str[128];
            char percent_str[128];
            int read_bytes = (int)wParam;
            int total_bytes = (int)lParam;
            unsigned int percent = -1;
            static unsigned int old_percent;
            static BOOL has_set_marquee;
            LONG_PTR style = 0;
            /* If we have a total byte count we can calculate percent */
            if (total_bytes > 0) {
                percent = downs_fltoui((((float)read_bytes / (float)total_bytes) * (float)100));
            }

            downs_memset(new_title, 0, sizeof(new_title));
            downs_memset(new_static, 0, sizeof(new_static));
            downs_memset(percent_str, 0, sizeof(percent_str));
            downs_memset(read_str, 0, sizeof(read_str));
            downs_memset(total_str, 0, sizeof(total_str));
            
            downs_itoa(percent, percent_str, 10);
            downs_itoa(read_bytes / 1000, read_str, 10);
            if (total_bytes > 0) {
                downs_itoa(total_bytes / 1000, total_str, 10);
            }
            else {
                lstrcpyA(total_str, "? ");
            }
            
            lstrcpyA(new_title, percent_str);
            lstrcatA(new_title, "%");

            lstrcpyA(new_static, read_str);
            lstrcatA(new_static, "/");
            lstrcatA(new_static, total_str);
            lstrcatA(new_static, " KB");

            SetWindowTextA(FindWindowExA(hwnd, 0, "STATIC", NULL), new_static);

            HWND hwndPB = FindWindowExA(hwnd, 0, PROGRESS_CLASSA, NULL);
            if (read_bytes != 0 && total_bytes == read_bytes) { /* Complete */
                SetDlgItemTextW(hwnd, IDCANCEL, L"Close");
                SetWindowTextA(hwnd, "100%");
                SetWindowLongPtr(GetDlgItem(hwnd, IDCANCEL), IDCANCEL, IDCLOSE);

                style = GetWindowLongPtr(hwndPB, GWL_STYLE);
                style &= ~PBS_MARQUEE;
                SetWindowLongPtr(hwndPB, GWL_STYLE, style);

                SendMessage(hwndPB, PBM_SETPOS, 100, 0);
            }
            else if (percent != -1 && percent != 0 && percent != old_percent) { /* Percentage bar */
                old_percent = percent;

                SendMessage(hwndPB, PBM_SETPOS, percent, 0);
                SetWindowTextA(hwnd, new_title);
            }
            else if (percent == -1) { /* Marquee bar */
                /* First time we are here, set marquee style now */
                if (has_set_marquee == FALSE) {
                    style = GetWindowLongPtr(hwndPB, GWL_STYLE);
                    style |= PBS_MARQUEE;
                    SetWindowLongPtr(hwndPB, GWL_STYLE, style);
                    has_set_marquee = FALSE;
                }

                SendMessage(FindWindowEx(hwnd, 0, PROGRESS_CLASS, NULL), PBM_DELTAPOS, 1, 0);
            }
        }
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDCANCEL:
        case IDCLOSE:
            PostThreadMessage(g_dwMainThreadId, WM_QUIT, 0, 0);
            ExitProcess(0);
            break;
        }
        break;
    default:
        return FALSE;
    }

    return TRUE;
}

int update_dialog_cb(int read_bytes, int total_bytes)
{
    InterlockedExchange(&g_read_bytes, read_bytes);
    InterlockedExchange(&g_total_bytes, total_bytes);

    return 0;
}

