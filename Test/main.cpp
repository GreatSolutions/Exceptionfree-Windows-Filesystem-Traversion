//filesystem Exceptionsolution to traverse systemfiles on Windows

#include <iostream>
#include <filesystem>
#include <windows.h>
namespace fs = std::filesystem;
#define LAA(se) {{se},SE_PRIVILEGE_ENABLED|SE_PRIVILEGE_ENABLED_BY_DEFAULT}
#define BEGIN_PRIVILEGES(tp, n) static const struct {ULONG PrivilegeCount;LUID_AND_ATTRIBUTES Privileges[n];} tp = {n,{
#define END_PRIVILEGES }};
// in case you not include wdm.h, where this defined
#define SE_BACKUP_PRIVILEGE (17L)
ULONG adjust_privileges()
{
	if (ImpersonateSelf(SecurityImpersonation))
	{
		HANDLE h_token;
		if (OpenThreadToken(GetCurrentThread(), TOKEN_ADJUST_PRIVILEGES, TRUE, &h_token))
		{
			BEGIN_PRIVILEGES(tp, 1) LAA(SE_BACKUP_PRIVILEGE), END_PRIVILEGES
				AdjustTokenPrivileges(h_token, FALSE, (PTOKEN_PRIVILEGES)&tp, 0, 0, 0);
			CloseHandle(h_token);
		}
	}

	return GetLastError();
}
void demo()
{
	adjust_privileges();

	fs::recursive_directory_iterator item(L"c:\\", fs::directory_options::skip_permission_denied);
	const fs::recursive_directory_iterator end;

	while (item != end)
	{
		printf("%S\n", item->path().c_str());
		++item;
	}
}
int main(void)
{
	demo();
	return 0;
}