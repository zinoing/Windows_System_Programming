// RaiseExceptionParam.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _CRT_SECURE_NO_WARNINGS
#define STATUS_DEFAULT_USER_DEFINED_EXPT ((DWORD) 0xE0000008L)

#include <stdio.h>
#include <Windows.h>
#include <tchar.h>

void SoftwareException(void);
DWORD FilterFunction(LPEXCEPTION_POINTERS exptPtr);

int _tmain(int argc, TCHAR* argv[]) {
	SoftwareException();
	_tprintf(_T("End of _tmain \n"));

	return 0;
}

void SoftwareExcept(void) {
	CONST TCHAR* exptString[] = {
		_T("exception String One!"),
		_T("exception String Two!"),
		_T("exception String Three!")
	};

	__try
	{
		RaiseException(STATUS_DEFAULT_USER_DEFINED_EXPT, 0, 3, (ULONG_PTR *)exptString);
	}
	__except(FilterFunction(GetExceptionInformation()))
	{
		DWORD exptType = GetExceptionCode();
		_tprintf(_T("Recv: exception code: 0x%x \n"), exptType);
	}
}

DWORD FilterFunction(LPEXCEPTION_POINTERS exptPtr)
{
	PEXCEPTION_RECORD exptRecord = exptPtr->ExceptionRecord;

	switch (exptRecord->ExceptionCode)
	{
		case STATUS_DEFAULT_USER_DEFINED_EXPT:
			_tprintf(_T("STATUS_DEFAULT_USER_DEFINED_EXPT exception \n"));
			_tprintf(_T("Exception code: 0x%x \n"), exptRecord->ExceptionCode);
			_tprintf(_T("Exception flags: %d \n"), exptRecord->ExceptionFlags);
			_tprintf(_T("Exception param num: %d \n"), exptRecord->NumberParameters);
			_tprintf(_T("String One: %s \n"), exptRecord->ExceptionInformation[0]);
			_tprintf(_T("String Two: %s \n"), exptRecord->ExceptionInformation[1]);
			_tprintf(_T("String Three: %s \n"), exptRecord->ExceptionInformation[2]);
			break;
		default:
			break;
	}
	return EXCEPTION_EXECUTE_HANDLER;
}
