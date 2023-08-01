// SetFilePointer_32BIT_VERSION.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define STRING_LEN 100
TCHAR fileData[] = _T("abcdefghijklmnopqrstuvwxyz");

int _tmain(int argc, TCHAR* argv[]) {
	TCHAR fileName[] = _T("abcd.dat");
	TCHAR readBuf[STRING_LEN];

	HANDLE hFile;
	DWORD numOfByteWritten = 0;
	DWORD dwPtr = 0;

	/* file write */
	hFile = CreateFile(
		fileName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
	WriteFile(hFile, fileData, sizeof(fileData), &numOfByteWritten, NULL);

	CloseHandle(hFile);

	/* file read */
	hFile = CreateFile(
		fileName, GENERIC_READ, 0, 0, CREATE_ALWAYS, 0, 0);
	ReadFile(hFile, readBuf, sizeof(fileData), &numOfByteWritten, NULL);

	CloseHandle(hFile);

	_tprintf(_T("%s \n"), readBuf);

	/* 파일 포인터를 맨 앞으로 이동 */
	dwPtr =
		SetFilePointer(hFile, sizeof(TCHAR) * 4, NULL, FILE_BEGIN);

	if (dwPtr == INVALID_SET_FILE_POINTER)
	{
		_tprintf(_T("SetFilePointer Error \n"));
		return -1;
	}

	ReadFile(hFile, readBuf, sizeof(readBuf), &numOfByteWritten, NULL);
	_tprintf(_T("%s \n"), readBuf);

	/* 파일 포인터를 맨 뒤로 이동 */
	dwPtr =
		SetFilePointer(hFile, sizeof(TCHAR) * 4, NULL, FILE_END);

	if (dwPtr == INVALID_SET_FILE_POINTER)
	{
		_tprintf(_T("SetFilePointer Error \n"));
		return -1;
	}

	ReadFile(hFile, readBuf, sizeof(readBuf), &numOfByteWritten, NULL);
	_tprintf(_T("%s \n"), readBuf);

	CloseHandle(hFile);
	return 0;
}

