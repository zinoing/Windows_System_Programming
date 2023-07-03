// AdderProcess.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <tchar.h>

int _tmain(int argc, TCHAR* argv[])
{
    DWORD val1, val2;
    val1 = _ttoi(argv[1]);
    val2 = _ttoi(argv[2]);

    _tprintf(_T("%d + %d = %d \n"), val1, val2, val1 + val2);

    _gettchar();
    return 0;
}
