// System_Windows_Dir.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[]) {
	TCHAR sysPathBuf[MAX_PATH];
	TCHAR winPathBuf[MAX_PATH];

	GetSystemDirectory(sysPathBuf, MAX_PATH);
	GetSystemDirectory(winPathBuf, MAX_PATH);

	_tprintf(_T("System dir: %s \n"), sysPathBuf);
	_tprintf(_T("Windows dir: %s \n"), winPathBuf);
	return 0;
}
