#pragma once
#include <windows.h>
#define LAA(se) {{se},SE_PRIVILEGE_ENABLED|SE_PRIVILEGE_ENABLED_BY_DEFAULT}
#define BEGIN_PRIVILEGES(tp, n) static const struct {ULONG PrivilegeCount;LUID_AND_ATTRIBUTES Privileges[n];} tp = {n,{
#define END_PRIVILEGES }};
// in case you not include wdm.h, where this defined
#define SE_BACKUP_PRIVILEGE (17L)

__declspec(dllexport)ULONG adjust_privileges();