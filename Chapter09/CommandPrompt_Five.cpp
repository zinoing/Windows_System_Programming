// CommandPrompt_Five.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tchar.h>
#include <locale.h>
#include <tlhelp32.h>

#define STR_LEN 256
#define CMD_TOKEN_NUM 10
#define MAX_STRING_NUM 100

TCHAR ERROR_CMD[] = _T("'%s'는 실행할 수 있는 프로그램이 아닙니다. \n");

void SortString(void);
int CmdReadTokenize(void);
int CmdProcessing(int);
void ListProcessInfo(void);
void KillProcess(void);
TCHAR* StrLower(TCHAR*);

TCHAR cmdString[STR_LEN];
TCHAR cmdTokenList[CMD_TOKEN_NUM][STR_LEN];
TCHAR seps[] = _T(" ,\t\n");

int _tmain(int argc, TCHAR* argv[]) {
	// 한글 입력을 가능케 하기 위해
	_tsetlocale(LC_ALL, _T("Korean"));

	if (argc > 2) {
		for (int i = 1; i < argc; i++)
			_tcscpy(cmdTokenList[i - 1], argv[i]);
		CmdProcessing(argc - 1);
	}

	DWORD isExit = NULL;
	while (1)
	{
		int tokenNum = CmdReadTokenize();

		if (tokenNum == 0) /* Enter 입력 처리를 위한 부분 */
			continue;

		isExit = CmdProcessing(tokenNum);
		if (isExit == TRUE) {
			_fputts(_T("명령어 처리를 종료합니다. \n"), stdout);
			break;
		}
	}
	return 0;
}

void SortString(void) {
	TCHAR stringArr[MAX_STRING_NUM][STR_LEN];

	int nStr;
	for (nStr = 0; nStr < MAX_STRING_NUM; nStr++) {
		TCHAR* isEOF = _fgetts(stringArr[nStr], MAX_STRING_NUM, stdin);

		if (isEOF == NULL)
			break;
	}

	TCHAR strTemp[STR_LEN];

	for (int i = 0; i < nStr; i++) {
		for (int j = i + 1; j < nStr; j++) {
			if (_tcscmp(stringArr[i], stringArr[j]) > 0) {
				_tccpy(strTemp, stringArr[i]);
				_tccpy(stringArr[i], stringArr[j]);
				_tccpy(stringArr[j], strTemp);
			}
			else
				continue;
		}
	}

	for (int i = 0; i < nStr; i++) {
		_fputts(stringArr[i], stdout);
	}
	return;
}

int CmdReadTokenize(void) {
	TCHAR* token;
	_fputts(_T("Best command prompt>> "), stdout);
	_fgetts(cmdString, STR_LEN, stdin);

	token = _tcstok(cmdString, seps);

	int tokenNum = 0;

	while (token != NULL) {
		_tcscpy(cmdTokenList[tokenNum++], StrLower(token));
		token = _tcstok(NULL, seps);
	}

	return tokenNum;
}

int CmdProcessing(int tokenNum) {
	BOOL isRun;
	STARTUPINFO si = { 0, };
	PROCESS_INFORMATION pi;

	TCHAR cmdStringWithOptions[STR_LEN] = { 0, };
	TCHAR optString[STR_LEN] = { 0, };

	si.cb = sizeof(si);
	if (!_tcscmp(cmdTokenList[0], _T("exit")))
	{
		return TRUE;
	}
	else if (!_tcscmp(cmdTokenList[0], _T("start")))
	{
		if (tokenNum > 1)
		{
			for (int i = 1; i < tokenNum; i++)
				_stprintf(optString, _T("%s %s"), optString, cmdTokenList[i]);
			_stprintf(cmdStringWithOptions, _T("%s %s"), _T("CommandPrompt_Five.exe"), optString);
		}
		else {
			_stprintf(cmdStringWithOptions, _T("%s"), _T("CommandPrompt_Five.exe"));
		}

		isRun = CreateProcess(
			NULL, cmdStringWithOptions,
			NULL, NULL, TRUE,
			CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi
		);

		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);

		if (isRun == FALSE) {
			_tprintf(ERROR_CMD, cmdTokenList[0]);
		}
	}
	else if (!_tcscmp(cmdTokenList[0], _T("echo")))
	{
		for (int i = 1; i < tokenNum; i++)
			_stprintf(optString, _T("%s %s"), optString, cmdTokenList[i]);
		_tprintf(_T("echo message: %s \n"), optString);
	}
	else if (!_tcscmp(cmdTokenList[0], _T("lp")))
	{
		ListProcessInfo();
	}
	else if (!_tcscmp(cmdTokenList[0], _T("kp")))
	{
		if (tokenNum < 2)
		{
			_tprintf(_T("usage: kp <process name> \n"));
			return 0;
		}
		KillProcess();
	}
	else if (!_tcscmp(cmdTokenList[0], _T("sort")))
	{
		if (!_tcscmp(cmdTokenList[1], _T(">"))) {
			SECURITY_ATTRIBUTES fileSec = {
				sizeof(SECURITY_ATTRIBUTES), NULL, TRUE
			};

			HANDLE hFile = CreateFile(
				cmdTokenList[2], GENERIC_WRITE, FILE_SHARE_READ,
				&fileSec, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL
			);

			si.hStdOutput = hFile;
			si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
			si.hStdError = GetStdHandle(STD_ERROR_HANDLE);
			si.dwFlags |= STARTF_USESTDHANDLES;

			isRun = CreateProcess(
				NULL, cmdTokenList[0], NULL, NULL,
				TRUE, 0, NULL, NULL, &si, &pi);

			WaitForSingleObject(pi.hProcess, INFINITE);

			CloseHandle(hFile);
		}
		else {
			isRun = CreateProcess(
				NULL, cmdTokenList[0], NULL, NULL,
				TRUE, 0, NULL, NULL, &si, &pi);

			WaitForSingleObject(pi.hProcess, INFINITE);
		}

		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
	else
	{
		_tcscpy(cmdStringWithOptions, cmdTokenList[0]);
		for (int i = 1; i < tokenNum; i++)
			_stprintf(cmdStringWithOptions, _T("%s %s"), cmdStringWithOptions, cmdTokenList[i]);
		isRun = CreateProcess(
			NULL, cmdStringWithOptions,
			NULL, NULL, TRUE,
			CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi
		);

		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);

		if (isRun == FALSE) {
			_tprintf(ERROR_CMD, cmdTokenList[0]);
		}

	}
	return 0;
}


void ListProcessInfo(void) {
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(
		TH32CS_SNAPPROCESS, 0
	);

	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		_tprintf(_T("CreatrToolhelp32Snapshot Error! \n"));
		return;
	}

	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (!Process32First(hProcessSnap, &pe32)) {
		_tprintf(_T("Process32First Error! \n"));
		CloseHandle(hProcessSnap);
		return;
	}

	do {
		_tprintf(_T("%25s %5d \n"), pe32.szExeFile, pe32.th32ParentProcessID);
	} while (Process32Next(hProcessSnap, &pe32));
}

void KillProcess(void) {
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(
		TH32CS_SNAPPROCESS, 0
	);

	if (hProcessSnap == INVALID_HANDLE_VALUE) {
		_tprintf(_T("CreatrToolhelp32Snapshot (of processes)"));
		return;
	}

	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (!Process32First(hProcessSnap, &pe32)) {
		_tprintf(_T("Process32First"));
		CloseHandle(hProcessSnap);
		return;
	}

	HANDLE hProcess;
	BOOL isKill = FALSE;

	do {
		if (_tcscmp(pe32.szExeFile, cmdTokenList[1]) == 0) {
			hProcess = OpenProcess(
				PROCESS_ALL_ACCESS,
				FALSE,
				pe32.th32ProcessID
			);

			if (hProcess != NULL) {
				TerminateProcess(hProcess, -1);
				isKill = TRUE;
			}

			CloseHandle(hProcess);
			break;
		}
	} while (Process32Next(hProcessSnap, &pe32));

	CloseHandle(hProcessSnap);
	if (isKill == FALSE) {
		_tprintf(_T("Kill process fail, Try again! \n"));
	}
}


TCHAR* StrLower(TCHAR* pStr) {
	TCHAR* ret = pStr;

	while (*pStr) {
		if (_istupper(*pStr))
			*pStr = _totlower(*pStr);
		pStr++;
	}

	return ret;
}

int _tmain_sortmain(int argc, TCHAR* argv[])
{
	SortString();

	return 0;
}
