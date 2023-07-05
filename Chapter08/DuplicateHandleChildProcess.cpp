#include <stdio.h>
#include <Windows.h>
#include <tchar.h>

#define SLOT_NAME _T("\\\\.\\mailslot\\mailbox")

int _tmain(int argc, TCHAR* argv[]) {
	HANDLE hParent = (HANDLE)_ttoi(argv[1]);
	DWORD isSuccess = WaitForSingleObject(hParent, INFINITE);

	_tprintf(_T("[Child Process] \n"));
	
	if (isSuccess == WAIT_FAILED) {
		_tprintf(_T("WAIT_FAILED returned"));
		Sleep(10000);
		return -1;
	}
	else {
		_tprintf(_T("General Lee siad, \"Don't inform ") _T("the enemy my death\""));
		Sleep(10000);
		return 0;
	}

	return 0;
}
