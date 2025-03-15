#pragma once

// https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-and-3-c4793?view=msvc-170
// varargs are not supported by the '/clr' compiler option
// Native functions cannot call managed functions that have 
// variable argument lists(varargs) because the functions 
// have different stack layout requirements.However, if you 
// specify the / clr:pure compiler option, variable argument 
// lists are supported because the assembly can contain 
// only managed functions.For more information, see Pure
// and Verifiable Code(C++ / CLI).
#pragma unmanaged

#include <Windows.h>

class Logging
{
public:
    inline static void DebugMsg(char* fmt, ...)
    {
#ifndef _DEBUG
        UNREFERENCED_PARAMETER(fmt);
#else
        va_list marker;
        char szBuf[1024] = { 0 };

        va_start(marker, fmt);
        wvsprintfA(szBuf, fmt, marker);
        va_end(marker);

        strcat_s(szBuf, _countof(szBuf) - 1, "\r\n");
        OutputDebugStringA(szBuf);
#endif
    }
};