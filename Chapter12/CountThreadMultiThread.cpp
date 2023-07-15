// CountThreadMultiThread.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <Windows.h>
#include <process.h>
#include <tchar.h>

#define MAX_THREADS (1024*10)

unsigned int WINAPI ThreadProc(LPVOID lpParam) // LPVOID란 void*를 뜻한다.
{
	DWORD threadNum = (DWORD)lpParam;

	while (1) {
		_tprintf(_T("thread num: %d \n"), threadNum);
		Sleep(5000);
	}
	return 0;
}

DWORD cntOfThread = 0;

int _tmain(int argc, TCHAR* argv[]) {
	DWORD dwThreadID[MAX_THREADS];
	HANDLE hThread[MAX_THREADS];

	while (1) {
		hThread[cntOfThread] =
			(HANDLE) _beginthreadex(
				NULL, 0,
				ThreadProc, (LPVOID)cntOfThread,
				0, (unsigned*)& dwThreadID[cntOfThread]
			);

		if (hThread[cntOfThread] == NULL) {
			_tprintf(_T("MAXIMUM THREAD NUMBER: %d \n"), cntOfThread);
			break;
		}
		cntOfThread++;
	}

	for (DWORD i = 0; i < cntOfThread; i++) {
		CloseHandle(hThread[i]);
	}

	return 0;
}
