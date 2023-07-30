// SEH_Calculator_ContinueExecution.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include <tchar.h>

enum { DIV = 1, MUL, ADD, MIN, ELSE, EXIT };

DWORD ShowMenu();
BOOL Calculator();
DWORD FilterFunction(DWORD exptType);

int _tmain(int argc, TCHAR* argv[]) {
	BOOL state;

	do {
		state = Calculator();
	} while (state == TRUE);

	return 0;
}

DWORD ShowMenu() {
	DWORD sel;

	_fputts(_T("-----Menu-----\n"), stdout);
	_fputts(_T("num1: Divide \n"), stdout);
	_fputts(_T("num2: Multiple \n"), stdout);
	_fputts(_T("num3: Add \n"), stdout);
	_fputts(_T("num4: Minus \n"), stdout);
	_fputts(_T("num5: Any other operations. \n"), stdout);
	_fputts(_T("num6: Exit \n"), stdout);
	_fputts(_T("Selection >>"), stdout);
	_tscanf(_T("%d"), &sel);

	return sel;
}

int num1, num2, result;

BOOL Calculator() {
	DWORD sel;

	sel = ShowMenu();
	if (sel == EXIT)
		return FALSE;

	_fputts(_T("Input Num1 Num2: "), stdout);
	_tscanf(_T("%d %d"), &num1, &num2);

	__try {
		switch (sel)
		{
		case DIV:
			result = num1 / num2;
			_tprintf(_T("%d/%d=%d \n\n"), num1, num2, result);
			break;
		case MUL:
			result = num1 * num2;
			_tprintf(_T("%d*%d=%d \n\n"), num1, num2, result);
			break;
		case ADD:
			result = num1 + num2;
			_tprintf(_T("%d+%d=%d \n\n"), num1, num2, result);
			break;
		case MIN:
			result = num1 - num2;
			_tprintf(_T("%d-%d=%d \n\n"), num1, num2, result);
			break;
		}
	}
	__except (FilterFunction(GetExceptionCode()))
	{
		_tprintf(_T("Wrong number inserted. Try again! \n\n"));
	}
	return TRUE;
}

DWORD FilterFunction(DWORD exptType)
{
	switch (exptType)
	{
	case EXCEPTION_ACCESS_VIOLATION:
		_tprintf(_T("Access violation \n\n"));
		return EXCEPTION_EXECUTE_HANDLER;

	case EXCEPTION_INT_DIVIDE_BY_ZERO:
		_tprintf(_T("Wrong number inserted. \n"));
		_tprintf(_T("Input second number again: \n"));
		_tscanf(_T("%d"), &num2);
		return EXCEPTION_CONTINUE_EXECUTION;
	default:
		return EXCEPTION_EXECUTE_HANDLER;
	}
}
