// UNICODE_BASE_FILE_IO.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	const TCHAR fileName[] = _T("data.txt");
	const TCHAR fileData[] = _T("Just test string.");

	HANDLE hFile = CreateFile(
		fileName, GENERIC_WRITE, FILE_SHARE_WRITE, 0,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0
	);
	if (hFile == INVALID_HANDLE_VALUE) {
		_tprintf(_T("File creation fault! \n"));
		return -1;
	}

	DWORD numOfBytesWritten = 0;
	WriteFile(hFile, fileData, sizeof(fileData), &numOfBytesWritten, NULL);
	_tprintf(_T("Written data size: %u \n"), numOfBytesWritten);
	CloseHandle(hFile);
	return 0;
}
