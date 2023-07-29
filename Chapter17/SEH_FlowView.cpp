// SEH_FlowView.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <windows.h>

int _tmain(int argc, TCHAR* argv[]) {
	_tprintf(_T("startpoint! \n"));

	int* p = NULL;

	__try
	{
		*p = 100;
		_tprintf(_T("value: %d \n"), *p);
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		_tprintf(_T("execption occured! \n"));
	}

	_tprintf(_T("end point! \n"));
	return 0;
}
