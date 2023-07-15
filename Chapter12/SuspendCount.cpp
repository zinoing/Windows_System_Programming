// SuspendCount.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <Windows.h>
#include <process.h>
#include <tchar.h>

#define MAX_THREADS (1024*10)

unsigned int WINAPI ThreadProc(LPVOID lpParam)
{
	while (1) {
		_tprintf(_T("Running state! \n"));
		Sleep(10000);
	}
	return 0;
}

int _tmain(int argc, TCHAR* argv[]) {
	DWORD dwThreadID;
	HANDLE hThread;
	DWORD susCnt;

	hThread =
		(HANDLE)_beginthreadex(
			NULL, 0,
			ThreadProc, NULL,
			CREATE_SUSPENDED, (unsigned*)&dwThreadID
		);

	if (hThread == NULL) {
		_tprintf(_T("Thread Creation fault! \n"));
	}

	susCnt = ResumeThread(hThread);
	_tprintf(_T("suspend count: %d \n"), susCnt);
	Sleep(10000);

	susCnt = SuspendThread(hThread);
	_tprintf(_T("suspend count: %d \n"), susCnt);
	Sleep(10000);

	susCnt = ResumeThread(hThread);
	_tprintf(_T("suspend count: %d \n"), susCnt);
	Sleep(10000);

	susCnt = ResumeThread(hThread);
	_tprintf(_T("suspend count: %d \n"), susCnt);
	Sleep(10000);

	susCnt = ResumeThread(hThread);
	_tprintf(_T("suspend count: %d \n"), susCnt);
	

	WaitForSingleObject(hThread, INFINITE);
	return 0;
}
