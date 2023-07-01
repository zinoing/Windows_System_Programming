## 프로세스간 통신(IPC)

* 하나의 프로그램은 여러 개의 프로세스를 생성할 수 있다. 이때, 여러 프로세스들 간의 통신이 필요하다.

### IPC(Inter-Process Communication)

* 프로세스간 통신
  * 프로세스간 데이터 송 수신 -> 메모리 공유
  
![](https://velog.velcdn.com/images/zinoing/post/1dab82b6-2c3b-4465-a0f6-eb34ce1f7113/image.png)

* 위 두 프로세스는 안전성을 목적으로 운영체제에 의해 완전히 분리되어 있다.

### 메일슬롯

* 동작원리

![](https://velog.velcdn.com/images/zinoing/post/66ba41e9-5d7e-46a0-ba4e-20cd3fd0178e/image.png)

  * OS에서 함수를 통해 Receiver의 우체통을 생성한다. Receiver 프로세스는 우체통 주소를 생성한다.
  * Sender는 보낼 수만 있고 받을 수는 없는 단방향의 특성을 지닌다.
  * Receiver들끼리 같은 주소를 가질 수 있다. - **브로캐스팅의 특징**

* 프로그래밍 모델

![](https://velog.velcdn.com/images/zinoing/post/3d4b06f4-8044-4204-854e-39135cef6dad/image.png)

## Signaled vs Non-Signaled

* 커널 오브젝트의 상태
  * 상태: 리소스의 현재 상황을 알리기 위함

![](https://velog.velcdn.com/images/zinoing/post/5b33fddc-3bc7-421e-aa3d-f19673516ff4/image.png)

> 커널 오브젝트의 상태는 무엇이며, 언제 변경되는가?

부모 프로젝트가 자식 프로세스를 생성하면 커널 오브젝트가 생성되고 핸들이 반환된다. 커널 오브젝트는 생성과 동시에 non-signaled 상태라고 가정한다. **non-signaled**는 프로세스가 현재 실행 중임을 의미한다. 따라서 프로세스가 종료되면 커널 오브젝트는 **signaled** 상태, 즉, 프로세스가 현재 종료되었을 때의 상태로 변경된다.

* 상태관찰 시나리오

![](https://velog.velcdn.com/images/zinoing/post/c5a451b4-0078-4100-a81f-a068cbeb6d97/image.png)

  * 부모 프로세스가 자식 프로세스의 실행 유무를 파악하기 위해서 호출하는 함수가 'WaitForSingleObject()'이다.
  * WaitForSingleObject() 함수는 해당 커널 오브젝트가 signaled인지 non-signaled인지 파악하는 함수가 아니라 해당 커널 오브젝트가 signaled될 때까지 기다리는 함수로 이해하여야 한다.
