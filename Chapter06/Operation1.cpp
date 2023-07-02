// Operation1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include <tchar.h>

int _tmain(int argc, TCHAR* argv[]) {
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	si.cb = sizeof(si);
	TCHAR command[] = _T("Operatio2.exe");

	CreateProcess(
		NULL, command, NULL, NULL,
		TRUE, 0, NULL, NULL, &si, &pi
	);

	while (1) {
		for (DWORD i = 0; i < 10000; i++)
		{
			for (DWORD i = 0; i < 10000; i++)

				_fputts(_T("Operation1.exe \n"), stdout);
		}
	}
	return 0;
}
