// nonBlocking_fileIOErr.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <stdio.h>
#include <tchar.h>
#include <windows.h> 

TCHAR strData1[] = _T("Nobody was farther off base than the pundits who said \n");
TCHAR strData2[] = _T("Royal Liverpool was outdated and not worthy of hosting the Open again \n");
TCHAR strData3[] = _T("for the first time since 1967. The Hoylake track held up beautifully. \n");

VOID WINAPI
FileIOCompletionRoutine(DWORD, DWORD, LPOVERLAPPED);

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR fileName[] = _T("data.txt");

	HANDLE hFile = CreateFile(
		fileName, GENERIC_WRITE, FILE_SHARE_WRITE, 0, CREATE_ALWAYS, FILE_FLAG_OVERLAPPED, 0
	);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		_tprintf(_T("File creation fault! \n"));
		return -1;
	}

	OVERLAPPED overlappedInstOne;
	memset(&overlappedInstOne, 0, sizeof(overlappedInstOne));
	overlappedInstOne.hEvent = (HANDLE)1234;
	WriteFileEx(hFile, strData1, sizeof(strData1), &overlappedInstOne, FileIOCompletionRoutine);

	OVERLAPPED overlappedInstTwo;
	memset(&overlappedInstTwo, 0, sizeof(overlappedInstTwo));
	overlappedInstTwo.hEvent = (HANDLE)1234;	
	WriteFileEx(hFile, strData2, sizeof(strData2), &overlappedInstTwo, FileIOCompletionRoutine);

	OVERLAPPED overlappedInstThree;
	memset(&overlappedInstThree, 0, sizeof(overlappedInstThree));
	overlappedInstThree.hEvent = (HANDLE)1234;	
	WriteFileEx(hFile, strData3, sizeof(strData3), &overlappedInstThree, FileIOCompletionRoutine);

	SleepEx(INFINITE, TRUE);
	CloseHandle(hFile);

	return 1;
}

VOID WINAPI
FileIOCompletionRoutine(DWORD errorCode, DWORD numOfBytesTransfered, LPOVERLAPPED overlapped)
{
	_tprintf(_T("**********File write result ************\n"));
	_tprintf(_T("Error code: %u \n"), errorCode);
	_tprintf(_T("Transferred bytes len: %u \n"), numOfBytesTransfered);
	_tprintf(_T("The other info: %u \n"), (DWORD)overlapped->hEvent);
}
