// Calculator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include <tchar.h>

enum{DIV = 1, MUL, ADD, MIN, ELSE, EXIT};

DWORD ShowMenu();
void Divide(double, double); // 이렇게 자료형만 적어도 괜찮은건가?
void Multiple(double, double);
void Add(double, double);
void Min(double, double);

int _tmain(int argc, TCHAR* argv[]) {
	STARTUPINFO si = { 0, }; // 생성 시 프로세스에 대한 주 창의 창 스테이션, 데스크톱, 표준 핸들 및 모양을 지정한다.
	PROCESS_INFORMATION pi; // 새로 생성된 프로세스와 스레드에 대한 정보들이 담겨있다.
	si.cb = sizeof(si); // si의 바이트 단위 크기로 멤버변수 cb를 초기화, 확장성을 고려

	TCHAR command[] = _T("clac.exe");
	SetCurrentDirectory(_T("C:\\WINDOWS||system32"));

	DWORD sel;
	double num1, num2;
	while (true) {
		sel = ShowMenu();
		if (sel == EXIT)
			return 0;

		if (sel != ELSE) {
			_fputts(_T("Input Num1 Num2: "), stdout);
			_tscanf(_T("%lf %lf"), &num1, &num2);
		}

		switch (sel)
		{
		case DIV:
			Divide(num1, num2);
			break;
		case MUL:
			Multiple(num1, num2);
			break;
		case ADD:
			Add(num1, num2);
			break;
		case MIN:
			Min(num1, num2);
			break;
		case ELSE:
			ZeroMemory(&pi, sizeof(pi)); // 해당 메모리를 비우는 매크로, 내부적으로 memset 호출
			CreateProcess(
				NULL, command, NULL, NULL,
				TRUE, 0, NULL, NULL, &si, &pi);
			break;
		}
	}
	return 0;
}

DWORD ShowMenu() {
	DWORD sel;

	_fputts(_T("-----Menu-----\n"), stdout);
	_fputts(_T("num1: Divide \n"), stdout);
	_fputts(_T("num2: Multiple \n"), stdout);
	_fputts(_T("num3: Add \n"), stdout);
	_fputts(_T("num4: Minus \n"), stdout);
	_fputts(_T("num5: Any other operations. \n"), stdout);
	_fputts(_T("num6: Exit \n"), stdout);
	_fputts(_T("Selection >>"), stdout);
	_tscanf(_T("%d"), &sel);

	return sel;
}

void Divide(double a, double b) {
	_tprintf(_T("%f/%f = %f \n\n"), a, b, a / b);
}

void Multiple(double a, double b) {
	_tprintf(_T("%f*%f = %f \n\n"), a, b, a * b);
}

void Add(double a, double b) {
	_tprintf(_T("%f+%f = %f \n\n"), a, b, a + b);
}

void Min(double a, double b) {
	_tprintf(_T("%f-%f = %f \n\n"), a, b, a - b);
}
