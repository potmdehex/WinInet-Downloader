/* Created by John Åkerblom 10/26/2014 */

#include <windows.h>
#include <wininet.h>

typedef HINTERNET (WINAPI *InternetOpenA_t)(
    _In_  LPCSTR lpszAgent,
    _In_  DWORD dwAccessType,
    _In_  LPCSTR lpszProxyName,
    _In_  LPCSTR lpszProxyBypass,
    _In_  DWORD dwFlags
    );

typedef BOOL (WINAPI *InternetSetOptionA_t)(
    _In_  HINTERNET hInternet,
    _In_  DWORD dwOption,
    _In_  LPVOID lpBuffer,
    _In_  DWORD dwBufferLength
    );

typedef HINTERNET (WINAPI *InternetConnectA_t)(
    _In_  HINTERNET hInternet,
    _In_  LPCSTR lpszServerName,
    _In_  INTERNET_PORT nServerPort,
    _In_  LPCSTR lpszUsername,
    _In_  LPCSTR lpszPassword,
    _In_  DWORD dwService,
    _In_  DWORD dwFlags,
    _In_  DWORD_PTR dwContext
    );

typedef HINTERNET (WINAPI *HttpOpenRequestA_t)(
    _In_  HINTERNET hConnect,
    _In_  LPCSTR lpszVerb,
    _In_  LPCSTR lpszObjectName,
    _In_  LPCSTR lpszVersion,
    _In_  LPCSTR lpszReferer,
    _In_  LPCSTR *lplpszAcceptTypes,
    _In_  DWORD dwFlags,
    _In_  DWORD_PTR dwContext
    );

typedef HINTERNET(WINAPI *InternetOpenUrlA_t)(
    _In_  HINTERNET hInternet,
    _In_  LPCSTR lpszUrl,
    _In_  LPCSTR lpszHeaders,
    _In_  DWORD dwHeadersLength,
    _In_  DWORD dwFlags,
    _In_  DWORD_PTR dwContext
    );

typedef BOOL(WINAPI *HttpQueryInfoA_t)(
    _In_     HINTERNET hRequest,
    _In_     DWORD dwInfoLevel,
    _Inout_  LPVOID lpvBuffer,
    _Inout_  LPDWORD lpdwBufferLength,
    _Inout_  LPDWORD lpdwIndex
    );

typedef BOOL (WINAPI *InternetQueryOptionA_t)(
    _In_     HINTERNET hInternet,
    _In_     DWORD dwOption,
    _Out_    LPVOID lpBuffer,
    _Inout_  LPDWORD lpdwBufferLength
    );

typedef BOOL(WINAPI *HttpSendRequestA_t)(
    _In_  HINTERNET hRequest,
    _In_  LPCSTR lpszHeaders,
    _In_  DWORD dwHeadersLength,
    _In_  LPVOID lpOptional,
    _In_  DWORD dwOptionalLength
    );

typedef BOOL (WINAPI *InternetReadFile_t)(
    _In_   HINTERNET hFile,
    _Out_  LPVOID lpBuffer,
    _In_   DWORD dwNumberOfBytesToRead,
    _Out_  LPDWORD lpdwNumberOfBytesRead
    );

typedef BOOL(WINAPI *InternetCloseHandle_t)(
    _In_  HINTERNET hInternet
    );

