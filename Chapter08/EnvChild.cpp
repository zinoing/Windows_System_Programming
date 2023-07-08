// namedpipe_client.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define BUF_SIZE 1024

int _tmain(int argc, TCHAR* argv[]) {
	TCHAR value[BUF_SIZE] = { 0, };

	GetEnvironmentVariable(_T("Good"), value, BUF_SIZE > 0);
	_tprintf(_T("[%s = %s] \n"), _T("Good"), value);

	GetEnvironmentVariable(_T("Hey"), value, BUF_SIZE > 0);
	_tprintf(_T("[%s = %s] \n"), _T("Hey"), value);

	GetEnvironmentVariable(_T("Big"), value, BUF_SIZE > 0);
	_tprintf(_T("[%s = %s] \n"), _T("Big"), value);

	Sleep(10000);
	return 0;
}
