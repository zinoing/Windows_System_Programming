#include <stdio.h>
#include <Windows.h>
#include <tchar.h>

#define SLOT_NAME _T("\\\\.\\mailslot\\mailbox")

int _tmain(int argc, TCHAR* argv[]) {
	HANDLE hProcess;
	TCHAR cmdString[1024];
	
	DuplicateHandle(
		GetCurrentProcess(),
		GetCurrentProcess(),
		GetCurrentProcess(),
		&hProcess,
		0,
		TRUE,
		DUPLICATE_SAME_ACCESS
	);

	_stprintf(
		cmdString, _T("%s %u"), _T("ChildProcess.exe"),
		(unsigned)hProcess);

	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi = { 0, };
	si.cb = sizeof(si);

	BOOL isSuccess =
		CreateProcess(
			NULL, cmdString, NULL, NULL, TRUE,
			CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi
		);

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	_tprintf(_T("[Parent Process]\n"));
	_tprintf(_T("Oooooooops\n"));

	return 0;
}
