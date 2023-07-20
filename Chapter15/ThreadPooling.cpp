// ThreadPooling.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <tchar.h>
#include <windows.h>

#define WORK_MAX 10000
#define THREAD_MAX 50

typedef void (*WORK) (void);

DWORD AddWorkToPool(WORK work);
WORK GetWorkFromPool(void);
DWORD MakeThreadToPool(DWORD numOfTHread);
void WorkerThreadFunction(LPVOID pParam);

typedef struct __WorkerThread
{
	HANDLE hThread;
	DWORD idThread;
} WorkerThread;

struct __ThreadPool
{
	// WORK를 등록하기 위한 배열
	WORK workList[WORK_MAX];

	// Thread 정보와 각 Thread별 Event 오브젝트
	WorkerThread workerThreadList[THREAD_MAX];
	HANDLE workerEventList[THREAD_MAX];

	// Work에 대한 정보
	DWORD idxOfCurremtWork;
	DWORD idsOfLastAddedWork;

	// Number of Thread
	DWORD threadIdx;
} gThreadPool;

// Mutex 관련 함수들
// gThreadPool에 대한 접근을 보호하기 위해 정의

static HANDLE mutex = NULL;

void InitMutex(void) {
	mutex = CreateMutex(NULL, FALSE, NULL);
}

void DeInitMutex(void) {
	BOOL ret = CloseHandle(mutex);
}

void AcquireMutex(void) {
	DWORD ret = WaitForSingleObject(mutex, INFINITE);

	if (ret == WAIT_FAILED)
		_tprintf(_T("Error Occur! \n"));
}

void ReleaseMutex(void) {
	BOOL ret = ReleaseMutex(mutex);

	if (ret == 0)
		_tprintf(_T("Error Occur! \n"));
}

// Thread Pool에 Work를 등록시키기 위한 함수

DWORD AddWorkToPool(WORK work) {
	AcquireMutex();
	if (gThreadPool.idsOfLastAddedWork >= WORK_MAX) {
		_tprintf(_T("AddWorkToPool fail! \n"));
		return NULL;
	}

	gThreadPool.workList[gThreadPool.idsOfLastAddedWork++] = work;

	// Work 등록 후, 대기 중인 쓰레드들을 모두 깨워 일을 시작하도록 함
	// 모두 깨울 필요가 없으므로 정교함이 떨어지는 부분이다
	for (DWORD i = 0; i < gThreadPool.threadIdx; i++)
		SetEvent(gThreadPool.workerEventList[i]);

	ReleaseMutex();
	return 1;
}

// Thread에서 Work을 가져올 때 호출되는 함수
// gTHreadPool에 대한 접근을 보호하기 위해 정의
WORK GetWorkFromPool(void) {
	WORK work = NULL;

	AcquireMutex();
	if (!(gThreadPool.idxOfCurremtWork < gThreadPool.idsOfLastAddedWork))
	{
		ReleaseMutex();
		return NULL;
	}

	work = gThreadPool.workList[gThreadPool.idxOfCurremtWork++];
	ReleaseMutex();

	return work;
}

// Thread Pool 생성
// 전달되는 인자값에 따라 Thread 생성
DWORD MakeThreadToPool(DWORD numOfThread) {
	InitMutex();
	DWORD capacity = WORK_MAX - (gThreadPool.threadIdx);

	if (capacity < numOfThread)
		numOfThread = capacity;

	for (DWORD i = 0; i < numOfThread; i++) {
		DWORD idThread;
		HANDLE hThread;

		gThreadPool.workerEventList[gThreadPool.threadIdx]
			= CreateEvent(NULL, FALSE, FALSE, NULL);

		hThread = CreateThread(
			NULL, 0,
			(LPTHREAD_START_ROUTINE)WorkerThreadFunction,
			(LPVOID)gThreadPool.threadIdx,
			0, &idThread
		);

		gThreadPool.workerThreadList[gThreadPool.threadIdx].hThread = hThread;
		gThreadPool.workerThreadList[gThreadPool.threadIdx].idThread = idThread;

		gThreadPool.threadIdx++;
	}
	return numOfThread;
}

void WorkerThreadFunction(LPVOID pParam) {
	WORK workFunction;
	HANDLE event = gThreadPool.workerEventList[(DWORD)pParam];

	while (1) {
		workFunction = GetWorkFromPool();
		if (workFunction == NULL) {
			WaitForSingleObject(event, INFINITE);
			continue;
		}
		workFunction();
	}
}

void TestFunction() {
	static int i = 0;
	i++;

	_tprintf(_T("Good Test --%d : Processing thread: %d--\n\n"), i, GetCurrentThreadId());
}

int _tmain(int argc, TCHAR* argv[]) {
	MakeThreadToPool(3);

	for (DWORD i = 0; i < 100; i++)
		AddWorkToPool(TestFunction);

	Sleep(50000);
	return 0;
}
