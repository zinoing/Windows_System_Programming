// SearchPath.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[]) {
	TCHAR fileName[MAX_PATH];
	TCHAR bufFilePath[MAX_PATH];
	LPTSTR lpFilePath;
	DWORD result;

	_tprintf(_T("Insert name of the file to find: "));
	_tscanf(_T("%s"), fileName);

	result = SearchPath(NULL, fileName, NULL, MAX_PATH, bufFilePath, &lpFilePath);

	if (result == 0)
	{
		_tprintf(_T("File not found! \n"));
	}
	else
	{
		_tprintf(_T("File path: %s \n"), bufFilePath);
		_tprintf(_T("File name only: %s \n"), lpFilePath);
	}
	return 0;
}
