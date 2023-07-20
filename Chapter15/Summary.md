```cpp
typedef void (*WORK) (void);

// WORK와 Thread 관리를 위한 구조체
typedef struct __WorkerThread
{
  HANDLE hThread;
  DWORD iThread;
} WorkerThread;

struct __ThreadPool
{
  // WORK를 등록하기 위한 배열
  WORK workList[WORK_MAX];

  // Thread 정보와 각 Thread별 Event 오브젝트
  WorkThread workerThreadList[THREAD_MAX];
  HANDLE workerEventList[THREAD_MAX];

  // Work에 대한 정보
  DWORD idxOfCurremtWork;
  DWORD idsOfLastAddedWork;

  // Number of Thread
  DWORD threadIdx;
} gThreadPool;
```
