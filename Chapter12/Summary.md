# 쓰레드의 생성과 소멸

## Windows에서의 쓰레드의 생성과 소멸

### 쓰레드의 생성
``` c
HANDLE CreateThread(
  LPSECURITY_ATTRIBUTES lpThreadAttributes, // 핸들의 상속 여부 결정
  SIZE_T dwStackSize, // initial stack size
  LPTHREAD_START_ROUTINE lpStartAddress, // thread function
  LPVOID lpParameter, // thread argument
  DWROD dwCreationFlags, // creation option
  LPDWORD lpThreadId // thread identifier
);
```
* If the function fails, the return value is NULL.
* thread의 ID는 각 thead 별로 고유하다.

> 생성 가능한 쓰레드의 개수는?

* 32bit 프로세스 기준으로 메모리는 4GB, 2GB는 운영체제가 관리 => 실제 운용가능한 메모리 2GB
* 2GB 내에서 스택을 할당할 수 없을 때까지 쓰레드 생성이 가능하다.

### 쓰레드의 소멸 case1:
* 쓰레드 종료 시 return 을 이용하면 좋은 경우(거의 모든 경우)

### 쓰레드의 소멸 case2:
* 쓰레드 종료 시 ExitThread 함수 호출이 유용한 경우
* 특정 위치에서 쓰레드의 실행을 종료시키고자 하는 경우
  
### 쓰레드의 소멸 case3:
* 쓰레드 종료 시 TerminateThread 함수 호출이 유용한 경우
* 외부에서 쓰레드를 종료시키고자 하는 경우 => 가능하면 사용 자제

## 쓰레드의 성격과 특성

### 동시 접근의 문제점
![image](https://github.com/zinoing/Windows_System_Programming/assets/77779979/32f3f925-24cc-46fc-9a1d-024f992fd66a)

### 프로세스로부터의 쓰레드 분리
![image](https://github.com/zinoing/Windows_System_Programming/assets/77779979/f5a5b78b-bd5f-452d-aabf-51f5dd886496)

### ANSI 표준 C라이브러리와 쓰레드
![image](https://github.com/zinoing/Windows_System_Programming/assets/77779979/0d727685-8652-4600-95af-6db9b80270c7)

### 쓰레드의 상태 컨트롤
![image](https://github.com/zinoing/Windows_System_Programming/assets/77779979/ff18a1c7-bc14-49e6-81a9-0cc31ef7b458)

```c
DWORD SuspenThread (
  HANDLE hThread;
);
```
* If the function succeds, the return value is the thread's previous suspend count otherwise, it is (DWORD) -1

```c
DWORD ResumeThread (
  HANDLE hThread;
);
```
* If the function succeds, the return value is the thread's previous suspend count otherwise, it is (DWORD) -1

### 쓰레드의 우선순위 결정 요소
![image](https://github.com/zinoing/Windows_System_Programming/assets/77779979/1ec43fa6-5e37-43fd-bd29-839346badc09)

### 쓰레드의 우선순위 컨트롤 함수
```c
DWORD SetThreadPriority (
  HANDLE hThread;
int nPriority;
);
```
* If the function fails, the return value is zero.


```c
DWORD GetThreadPriority (
  HANDLE hThread;
);
```
* If the function fails, the return value THREAD_PRIORITY_RETURN
