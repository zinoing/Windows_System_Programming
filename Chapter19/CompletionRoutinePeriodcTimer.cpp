// CompletionRoutinePeriodcTimer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _WIN32_WINNT0x0400

#include <stdio.h>
#include <tchar.h>
#include <windows.h> 

VOID CALLBACK TimerAPCProc(LPVOID, DWORD, DWORD);

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hTimer = NULL;
	LARGE_INTEGER liDueTime;

	liDueTime.QuadPart = -100000000;

	hTimer =
		CreateWaitableTimer(NULL, FALSE, _T("WaitableTimer"));
	if (!hTimer)
	{
		_tprintf(_T("CreateWaitableTimer failed (%d)\n"), GetLastError());
		return 1;
	}

	_tprintf(_T("Wiating for 10 seconds...\n"));

	SetWaitableTimer(
		hTimer, &liDueTime, 5000,
		TimerAPCProc, _T("Timer was signaled. \n"), FALSE
	);

	while (1)
		SleepEx(INFINITE, TRUE);

	return 0;
}

VOID CALLBACK TimerAPCProc(LPVOID lpArg, DWORD timerLowVal, DWORD timerHighVal)
{
	_tprintf(_T("%s"), (TCHAR*)lpArg);
	MessageBeep(MB_ICONEXCLAMATION);
}
