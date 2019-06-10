#include "Adjust_Privileges.h"

ULONG adjust_privileges()
{
	if (ImpersonateSelf(SecurityImpersonation))
	{
		HANDLE h_token;
		if (OpenThreadToken(GetCurrentThread(), TOKEN_ADJUST_PRIVILEGES, TRUE, &h_token))
		{
			BEGIN_PRIVILEGES(tp, 1) LAA(SE_BACKUP_PRIVILEGE), END_PRIVILEGES
				AdjustTokenPrivileges(h_token, FALSE, (PTOKEN_PRIVILEGES)& tp, 0, 0, 0);
			CloseHandle(h_token);
		}
	}

	return GetLastError();
}