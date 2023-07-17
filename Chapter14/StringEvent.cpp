// StringEvent.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <process.h>
#include <Windows.h>
#include <tchar.h>

unsigned int WINAPI OutputThreadFunction(LPVOID lpParam);

TCHAR string[100];
HANDLE hEvent;

int _tmain(int argc, TCHAR* argv[]) {
	HANDLE hThread;
	DWORD dwThreadID;

	hEvent = CreateEvent(
		NULL,
		TRUE, // manual-reset mode로 생성
		FALSE, // non-signaled 상태로 생성
		NULL
	);
	if (hEvent == NULL) {
		_fputts(_T("Event object creation error! \n"), stdout);
		return -1;
	}

	hThread = (HANDLE)_beginthreadex(
		NULL, 0,
		OutputThreadFunction, NULL, 0,
		(unsigned*)&dwThreadID
	);

	if (hThread == 0) {
		_fputts(_T("Thread creation error \n"), stdout);
		return -1;
	}

	_fputts(_T("Insert String: "), stdout);
	_fgetts(string, 30, stdin);

	SetEvent(hEvent);

	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hEvent);
	CloseHandle(hThread);

	return 0;
}

unsigned int WINAPI OutputThreadFunction(LPVOID lpParam)
{
	WaitForSingleObject(hEvent, INFINITE);

	_fputts(_T("Output string: "), stdout);
	_fputts(string, stdout);

	return 0;
}
