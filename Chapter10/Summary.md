## 컴퓨터 구조에 대한 세 번째 이야기

### 스택 프레임이란?
![image](https://github.com/zinoing/Windows_System_Programming/assets/77779979/0572d1ad-ecd0-496b-84fe-41305b60a050)
* 다음 위치 지정 정보는 레지스터가 가지고 있다.

### sp레지스터
![image](https://github.com/zinoing/Windows_System_Programming/assets/77779979/26d914bc-f850-4075-9f84-cf3282f9c407)
> 반환을 어떻게 할 것인가?

레지스터는 주소값 하나 밖에 저장하지 않았기 때문에 추가적인 정보가 없다. 따라서 기억하기 위한 용도의 레지스터를 하나 더 만들어 준다.
그리고 이 레지스터는 **fp레지스터**이다.

### fp레지스터
![image](https://github.com/zinoing/Windows_System_Programming/assets/77779979/947044c7-a23d-4edb-89aa-3ffd695f5f91)
* fp레지스터는 sp레지스터의 백업이다.

### fp레지스터 문제점
* 반환해야 할 함수의 주소는 많지만 fp레지스터의 크기가 그만큼 크지않아 문제가 발생한다.

### fp레지스터 해결책
![image](https://github.com/zinoing/Windows_System_Programming/assets/77779979/41e27559-056a-4a2b-8b87-cf4ea9000c0d)

## PUSH & POP - 함수호출 인자의 전달과 PUSH&POP 명령어 디자인

###  함수 호출 인자의 전달 방식
![image](https://github.com/zinoing/Windows_System_Programming/assets/77779979/f6acf998-025c-4566-a323-56d59dc6bf0e)

### 함수 호출 인자의 전달방식(문제점은?)
![image](https://github.com/zinoing/Windows_System_Programming/assets/77779979/78967d3c-5fd1-4080-a029-eb30f7457507)

### 문제점 해결
![image](https://github.com/zinoing/Windows_System_Programming/assets/77779979/2c54b3ba-2352-4dee-a962-b0c2be836180)

### POP의 기능
![image](https://github.com/zinoing/Windows_System_Programming/assets/77779979/1adf88fb-4ff0-4df5-aba9-edb28efe3f1d)

## 호출규약과 실행의 이동

### 함수 호출에 의한 실행의 이동과 pc
![image](https://github.com/zinoing/Windows_System_Programming/assets/77779979/7c59e8bf-91de-4512-9b1f-30335fdc1788)

* 프로그램 카운터는 실행을 이동시킨다.
* SP는 호출 스택을 추적하는 게 목적인 CPU레지스터인 반면, 프로그램 카운터는 컴퓨터가 프로그램 순서 중 어디에 위치해 있는지를 나타내는 CPU 레지스터이다.

### 함수호출규약
![image](https://github.com/zinoing/Windows_System_Programming/assets/77779979/f13a4ff0-3ec8-44ed-a5ac-82e9000db895)
