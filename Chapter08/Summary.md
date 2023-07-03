## 프로세스 환경변수

* 환경변수란 데이터 블럭을 부모 프로세스가 자식 프로세스로 상속이 가능하다. 어떠한 관점에서 이는 '통신'이라고 해석될 수 있다.
그러나 환경 변수는 프로세스가 자신만의 고유한 정보의 저장을 위해 만들어진 것으로 통신과는 그 결을 달리하고 있다.

### 프로세스 환경변수의 구성

* 환경변수는 메모리 블럭에 할당이 된다.
* 문자열로 'Key'와 'Value'를 쌍으로 저장하여야 한다.
* SetEnvironmentVariable(), GetEnvironmentVariable()이 환경변수의 getter, setter 함수이다.
* 부모 프로세스는 자신의 환경변수 테이블 정보를 자식 프로세스에게 넘겨줄 수 있다.(통신 가능)
![image](https://github.com/zinoing/Windows_System_Programming/assets/77779979/0f15cb58-d6cb-41ed-a80c-0681406b93d6)

## 프로세스간 통신(IPC)2

### 핸들테이블의 이해
* 프로세스가 메일슬롯을 생성
* 메일슬롯은 커널 오브젝트의 생성을 동반하여 커널 오브젝트 또한 non-signaled 상태 함께 생성된다.
* 메일슬롯의 핸들값과 커널 오브젝트의 주소기 환경 테이블에 등록된다.
![image](https://github.com/zinoing/Windows_System_Programming/assets/77779979/2f72450d-11a5-45cb-939d-d470e6ea6dc0)

* 조건에 맞는다면 부모 프로세스는 자식 프로세스에게 핸들 테이블을 상속할 수 있다.
* 핸들의 상속여부가 "Yes"인 것들만 상속이 된다.

> 어떠한 경우에 핸들의 상속여부가 "Yes"인가? / 상속을 하기 위한 조건은 무엇인가?

CreateProcess() 함수의 다섯 번째 매개변수인 "BOOL bInheritHandles"는 핸들테이블의 상속 여부를 의미한다.  
이 매개변수가 true면 상속이 전달되고, false면 상속이 전달되지 않는다. - **상속을 하기 위한 조건**

```c
.....
SECURITY_ATTRIBUTES sa;
sa.nLength=sizeof(sa);
sa.lpSecurityDescriptor=NULL;
sa.bInheritHandle=TRUE;
.....
CreateMailslot(...&sa); // &sa는 4번째 전달인자.
.....
```
* 모든 대부분의 리소스의 생성 과정에서 "SECURITY_ATTRIBUTES"(보안설정) 구조체를 초기화한다.

### 핸들의 상속과 UC
