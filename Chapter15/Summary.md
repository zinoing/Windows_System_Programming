## 쓰레드 풀링

### 쓰레드 풀이란?
![image](https://github.com/zinoing/Windows_System_Programming/assets/77779979/7651b7ea-7cb6-4abb-92fb-e5348922bbaa)
* 쓰레드를 생성과 소멸을 하는 대신에 기존에 있던 쓰레드를 재활용하여 성능향상에 기여한다.

### 쓰레드 풀의 구현 원리
```cpp
typedef void (*WORK) (void);

// WORK와 Thread 관리를 위한 구조체
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
```
