// namedpipe_client.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define BUF_SIZE 1024

int _tmain(int argc, TCHAR* argv[]) {
	HANDLE hPipe;
	TCHAR readDataBuf[BUF_SIZE + 1];
	LPCTSTR pipeName = _T("\\\\.\\pipe\\simple_pipe");

	while (1) {
		hPipe = CreateFile(
			pipeName,
			GENERIC_READ |
			GENERIC_WRITE,
			0,
			NULL,
			OPEN_EXISTING,
			0,
			NULL
		);

		if (hPipe != INVALID_HANDLE_VALUE)
			break;

		if (GetLastError() != ERROR_PIPE_BUSY) {
			_tprintf(_T("Could not open pipe \n"));
			return 0;
		}

		if (WaitNamedPipe(pipeName, 20000)) {
			_tprintf(_T("Could not open pipe \n"));
			return 0;
		}
	}

	DWORD pipeMode = PIPE_READMODE_MESSAGE | PIPE_WAIT;
	BOOL isSuccess = SetNamedPipeHandleState(
		hPipe,
		&pipeMode,
		NULL,
		NULL
	);

	if (!isSuccess) {
		_tprintf(_T("SetNaedPipeHandleState failed \n"));
		return 0;
	}

	LPCTSTR fileName = _T("news.txt");
	DWORD bytesWritten = 0;

	isSuccess = WriteFile(
		hPipe,
		fileName,
		(_tcslen(fileName) + 1) * sizeof(TCHAR),
		&bytesWritten,
		NULL);

	if (!isSuccess) {
		_tprintf(_T("WriteFile failed"));
		return 0;
	}

	DWORD bytesRead = 0;
	while (1)
	{
		isSuccess = ReadFile(
			hPipe,
			readDataBuf,
			BUF_SIZE * sizeof(TCHAR),
			&bytesRead,
			NULL
		);
		if (!isSuccess && GetLastError() != ERROR_MORE_DATA)
			break;

		readDataBuf[bytesRead] = 0;
		_tprintf(_T("%s \n"), readDataBuf);
	}

	CloseHandle(hPipe);
	return 0;

}
