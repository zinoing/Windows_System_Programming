## Windows에서의 유니코드(UNICODE)

### 문자셋의 종류와 특성

* SBCS(Single Byte Character Set)
  * 문자를 표현하는데 1바이트 사용
  * 아스키 코드
    
* MBCS(Multi Byte Character Set)
  * 한글은 2바이트, 영문은 1바이트 사용
  * 기본적으로 WBCS와 상당히 유사하다, 차이는 WBCS에서 표현하는 문자는 2바이트 이상을 차지하지만 MBCS는 1바이트 이상을 차지한다.
  * MBCS는 SBCS을 포함하기에 유니코드는 MBCS에 속하지 않는다.

* WBCS(Wide Byte Character Set)
  * 문자열을 동등하게 2bytes로 처리하는 방식
  * 문자를 표현하는데 2바이트 사용
  
> MBCS가 WBCS 보다 효율적으로 보이는데 왜 WBCS를 사용할까?

요즘 시대에 1바이트를 절약하는 것이 의미가 없다. 오히려 안전성 측면에서 WBCS가 더 우수하다.

### WBCS기반의 프로그래밍

* WBCS를 위한 두가지
  * 첫째: char을 대신하는 wchar_t
  * 둘째: "ABC"를 대신하는 L"ABC"

* WBCS 기반 문자열 선언 예
  * wchar_tstr[] = L"ABC";
  
### 문자열 조작함수
  ![](https://velog.velcdn.com/images/zinoing/post/2d5d13e2-4056-4f5e-bbdd-f3cf44b0eebb/image.png)
  
### 문자열 입출력 함수
![](https://velog.velcdn.com/images/zinoing/post/954e58f7-254e-4c5c-b898-0e4898433946/image.png)

## MBCS와 WBCS 동시지원

### MBCS와 WBCS 동시 지원 매크로

```c
#ifdef UNICODE
	typedef WCHAR		TCHAR;
    typedef LPWSTR		LPSTR;
    typedef LPCWSTR		LPCTSTR;
#else
	typedef CHAR		TCHAR;
    typedef LPSTR		LPSTR;
    typedef LPCSTR		LPCTSTR;
#endif
```

```c
#ifdef _UNICODE
	#define __T(x)		L##x
#else
	#define __T(x)		x
#endif

	#define _T(x)		__T(x)
	#define _TEXT(x)	__T(x)
```
  
```c
#ifdef _UNICODE
  #define _tprintf wprintf
#else
  #define _tprintf printf
#endif 
```

* UNICODE와 _UNICODE의 차이점은?
  
  https://devblogs.microsoft.com/oldnewthing/20040212-00/?p=40643
