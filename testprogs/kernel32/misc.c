#include <stdio.h>
#include <windows.h>

#include "format_msg.h"

int main()
{
    CPINFOEXW cpinfo;

    GetCPInfoExW(CP_UTF8, 0, &cpinfo);
    fprintf(stdout, "%ls\n", cpinfo.CodePageName);

    return 0;
}
