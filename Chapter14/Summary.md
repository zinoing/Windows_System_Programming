## 쓰레드 동기화 기법2

### 생산자/소비자 모델
![image](https://github.com/zinoing/Windows_System_Programming/assets/77779979/ef803a62-fd05-445c-a098-b014b9091921)

### 이벤트(Event)기반 동기화
![image](https://github.com/zinoing/Windows_System_Programming/assets/77779979/6d71cee5-86a4-4294-9b51-bb1898b4c84b)
*  쓰레드나 프로세스가 종료될 경우, 해당 커널 오브젝트는 Signaled상태로 자동변경된다. 그러나 이벤트 오브젝트는 자동으로 Signaled 상태가 되지 않는다.
* WaitForSingleObject 함수 호출 완료 이후, Signaled 상태 그대로라면, 수동 리셋 모드 이벤트 오브젝트이고, Non-Signaled 상태로 자동 변경된다면 자동 리셋 모드 이벤트 오브젝트이다.
