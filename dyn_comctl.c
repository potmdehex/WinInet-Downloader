/* Created by John Åkerblom 10/26/2014 */

#include <windows.h>
#include <commctrl.h>

typedef BOOL (WINAPI *InitCommonControlsEx_t)(
    const LPINITCOMMONCONTROLSEX lpInitCtrls
    );

void comctl_init(void)
{ 
    INITCOMMONCONTROLSEX icc;
    HMODULE h = LoadLibraryA("comctl32.dll");
    InitCommonControlsEx_t __InitCommonControlsEx 
        = (InitCommonControlsEx_t)GetProcAddress(h, "InitCommonControlsEx");

    icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icc.dwICC = ICC_PROGRESS_CLASS | ICC_WIN95_CLASSES;
    __InitCommonControlsEx(&icc);
}
