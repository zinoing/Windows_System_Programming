// EXCEPTION_NONCONTINUABLE.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _CRT_SECURE_NO_WARNINGS
#define BEST_TEST_EXCEPTION ((DWORD) 0xE0000008L)

#include <stdio.h>
#include <Windows.h>
#include <tchar.h>

void SoftwareException(void);

int _tmain(int argc, TCHAR* argv[]) {
	SoftwareException();
	_tprintf(_T("End of _tmain \n"));

	return 0;
}

void SoftwareExcept(void) {
	__try
	{
		RaiseException(BEST_TEST_EXCEPTION, 0, NULL, NULL);
		_tprintf(_T("It's work! \n"));
	}
	__except(EXCEPTION_CONTINUE_EXECUTION)
	{
		DWORD exptType = GetExceptionCode();

		if(exptType == BEST_TEST_EXCEPTION)
			_tprintf(_T("BEST_TEST_EXCEPTION exception occured\n"));
	}
}
