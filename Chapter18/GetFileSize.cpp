// GetFileSize.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[]) {
	TCHAR fileName[] = _T("RealScaleViwer.exe");

	HANDLE hFile = CreateFile(
		fileName, GENERIC_READ, 0, 0,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0
	);

	if (hFile == INVALID_HANDLE_VALUE) {
		_tprintf(_T("File open failt! \n"));
		return -1;
	}

	DWORD high4ByteFileSize = 0;
	DWORD low4ByteFileSize = GetFileSize(hFile, &high4ByteFileSize);

	_tprintf(_T("High 4byte file size: %u byte\n"), high4ByteFileSize);
	_tprintf(_T("Los 4byte file size: %u byte\n"), low4ByteFileSize);

	LARGE_INTEGER fileSize;
	GetFileSizeEx(hFile, &fileSize);
	_tprintf(_T("Total file size: %u byte \n"), fileSize);

	CloseHandle(hFile);
	return 0;
}
