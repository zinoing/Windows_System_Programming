// FileTimeInformation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define STRING_LEN 100

int _tmain(int argc, TCHAR* argv[]) {
	TCHAR fileName[] = _T("RealScaleViewer.exe");

	TCHAR fileCreateTimeInfo[STRING_LEN];
	TCHAR fileAccessTimeInfo[STRING_LEN];
	TCHAR fileWriteTimeInfo[STRING_LEN];

	FILETIME ftCreate, ftAccess, ftWrite;

	SYSTEMTIME stCreateUTC, stCreateLocal;
	SYSTEMTIME stAccessUTC, stAccessLocal;
	SYSTEMTIME stWriteUTC, stWriteLocal;

	HANDLE hFile = CreateFile(
		fileName, GENERIC_READ, 0, 0,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0
	);

	if (hFile == INVALID_HANDLE_VALUE) {
		_tprintf(_T("FILE open fault! \n"));
		return -1;
	}

	if (!GetFileTime(hFile, &ftCreate, &ftAccess, &ftWrite)) {
		_tprintf(_T("GetFileTime function call fault! \n"));
		return FALSE;
	}

	FileTimeToSystemTime(&ftCreate, &stCreateUTC);
	SystemTimeToTzSpecificLocalTime(
		NULL, &stCreateUTC, &stCreateLocal
	);

	FileTimeToSystemTime(&ftAccess, &stAccessUTC);
	SystemTimeToTzSpecificLocalTime(
		NULL, &stAccessUTC, &stAccessLocal
	);

	FileTimeToSystemTime(&ftWrite, &stWriteUTC);
	SystemTimeToTzSpecificLocalTime(
		NULL, &stWriteUTC, &stWriteLocal
	);

	_stprintf(
		fileCreateTimeInfo, _T("%02d/%02d/%d %02d:%02d"),
		stAccessLocal.wMonth, stAccessLocal.wDay,
		stAccessLocal.wYear, stAccessLocal.wHour,
		stAccessLocal.wMinute
	);

	_stprintf(
		fileAccessTimeInfo, _T("%02d/%02d/%d %02d:%02d"),
		stCreateLocal.wMonth, stCreateLocal.wDay,
		stCreateLocal.wYear, stCreateLocal.wHour,
		stCreateLocal.wMinute
	);

	_stprintf(
		fileWriteTimeInfo, _T("%02d/%02d/%d %02d:%02d"),
		stWriteLocal.wMonth, stWriteLocal.wDay,
		stWriteLocal.wYear, stWriteLocal.wHour,
		stWriteLocal.wMinute
	);

	return 0;
}
