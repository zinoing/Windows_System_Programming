// // Set_Get_FileAttributes.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

void ShowAttributes(DWORD attrib);

int _tmain(int argc, TCHAR* argv[]) {
	TCHAR fileName[] = _T("RealScaleViewer.exe");

	_tprintf(_T("Origianl file attributes \n"));
	DWORD attrib = GetFileAttributes(_T("RealScaleViewer.exe"));
	ShowAttributes(attrib);

	attrib |= (FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_HIDDEN);
	SetFileAttributes(_T("RealScaleViewer.exe"), attrib);

	_tprintf(_T("Changed file attributes \n"));
	attrib = GetFileAttributes(_T("RealScaleViewer.exe"));
	ShowAttributes(attrib);

	return 0;
}

void ShowAttribute(DWORD attrib) {
	if (attrib & FILE_ATTRIBUTE_NORMAL)
	{
		_tprintf(_T("Normal \n"));
	}
	else {
		if (attrib & FILE_ATTRIBUTE_READONLY)
			_tprintf(_T("Read Only \n"));

		if (attrib & FILE_ATTRIBUTE_HIDDEN)
			_tprintf(_T("Hidden \n"));
		_tprintf(_T("\n"));
	}
//

#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

void ShowAttributes(DWORD attrib);

int _tmain(int argc, TCHAR* argv[]) {
	TCHAR fileName[] = _T("RealScaleViewer.exe");

	_tprintf(_T("Origianl file attributes \n"));
	DWORD attrib = GetFileAttributes(_T("RealScaleViewer.exe"));
	ShowAttributes(attrib);

	attrib |= (FILE_ATTRIBUTE_READONLY | FILE_ATTRIBUTE_HIDDEN);
	SetFileAttributes(_T("RealScaleViewer.exe"), attrib);

	_tprintf(_T("Changed file attributes \n"));
	attrib = GetFileAttributes(_T("RealScaleViewer.exe"));
	ShowAttributes(attrib);

	return 0;
}

void ShowAttribute(DWORD attrib) {
	if (attrib & FILE_ATTRIBUTE_NORMAL)
	{
		_tprintf(_T("Normal \n"));
	}
	else {
		if (attrib & FILE_ATTRIBUTE_READONLY)
			_tprintf(_T("Read Only \n"));

		if (attrib & FILE_ATTRIBUTE_HIDDEN)
			_tprintf(_T("Hidden \n"));
		_tprintf(_T("\n"));
	}
}
