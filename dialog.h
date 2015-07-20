/* Created by John Åkerblom 10/26/2014 */

#ifndef __DIALOG_H_DEF__
#define __DIALOG_H_DEF__

#include <windows.h>

int update_dialog_cb(int read_bytes, int total_bytes);

BOOL CALLBACK DownloadDlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

#endif
