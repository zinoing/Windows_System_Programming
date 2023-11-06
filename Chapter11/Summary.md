## 쓰레드의 이해

### 프로세스 vs 쓰레드
* 둘 이상의 프로그램을 실행하는 것, **멀티프로세스**
* 하나의 코드를 실행하는데 있어서 둘 이상의 프로그램을 실행하는 것, **멀티쓰레드**
> 실행의 흐름이 2개가 되기 위해서 필요한 요소는 무엇일까?

* 쓰레드는 프로세스와 마찬가지로 독립적으로 스택을 할당한다.
* 프로세스의 경우, 완전히 독립적인 구조이기 때문에 코드 영역의 공유가 힘들다. 그러나 쓰레드는 자신을 생성한 프로세스가 가지고 있는 함수를 호출할 수 있다.
* 프로세스의 경우, IPC를 통해 프로세스 간 연결이 이루어지지만 쓰레드는 힙과 데이터 영역을 공유할 수 있다. 따라서, 전역변수와 malloc 함수만을 통해서 동적 할당된 메모리 공간은 공유가 가능하다.
![image](https://github.com/zinoing/Windows_System_Programming/assets/77779979/0d8bb558-0a3a-40eb-b422-174b67ec9ebf)

### 프로세스와 쓰레드의 관계
![image](https://github.com/zinoing/Windows_System_Programming/assets/77779979/07aab894-293e-4616-9fc4-e0a1beb22b7f)

### Windows에서의 프로세스와 쓰레드
* Windows 운영체제에 있어서 프로세스는 상태(Running, Ready, Blocked)를 지니지 않는다.
상태를 지니는 것은 프로세스가 아닌 **쓰레드**이다. 뿐만 아니라, 스케줄러가 실행의 단위로 선택하는 것도 쓰레드이다.

## 쓰레드 구현 모델에 따른 구분

### 커널 레벨 쓰레드 vs 유저 레벨 쓰레드
![image](https://github.com/zinoing/Windows_System_Programming/assets/77779979/488f1b47-330b-423f-b9b4-a338c220cca4)

### 커널 모드 vs 유저 모드
![image](https://github.com/zinoing/Windows_System_Programming/assets/77779979/7bf187f0-399b-4d1b-8f4d-afc860a7e349)

### 장점과 단점
* 커널 레벨 쓰레드의 장점 및 단점
  * 장점: 커널에서 직접 제공해 주기 때문에 안전성과 다양한 기능성 제공
  * 단점: 유저 모드에서 커널 모드로의 전환이 빈번
* 유저 레벨 쓰레드의 장점 및 단점
  * 장점: 유저 모드에서 커널 모드로의 전환이 필요 없다.
  * 단점: 프로세스 단위 블로킹 
