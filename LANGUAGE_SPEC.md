# NiceTop 언어 명세서

## 개요
**NiceTop**은 절차지향 프로그래밍 패러다임을 따르는 동적 타입 언어입니다.
- C 언어로 구현된 네이티브 인터프리터
- 모든 키워드에 `n` 접두사 사용
- 세미콜론 불필요

## 파일 확장자
`.nt` (NiceTop)

## 기본 문법

### 주석
```c
# 한 줄 주석
```

### 데이터 타입
- **숫자 (Number)**: 정수 및 실수
  - 예: `10`, `3.14`, `-5`
- **문자열 (String)**: 큰따옴표 또는 작은따옴표
  - 예: `"Hello"`, `'World'`
- **불린 (Boolean)**: `ntrue`, `nfalse`
- **Null**: `null` (반환값이 없을 때)

### 변수 선언 (C 스타일)
NiceTop은 C 언어처럼 타입을 먼저 선언합니다.

```c
nint 변수명 = 값      # 정수형
nfloat 변수명 = 값    # 실수형
nstring 변수명 = 값   # 문자열
nbool 변수명 = 값     # 불린형
```

변수 재할당:
```c
변수명 = 새로운값
```

예제:
```c
nint age = 25
nfloat pi = 3.14
nstring name = "철수"
nbool isReady = ntrue
```

### 연산자

#### 산술 연산자
- `+` : 덧셈 (문자열 연결도 가능)
- `-` : 뺄셈
- `*` : 곱셈
- `/` : 나눗셈
- `%` : 나머지

#### 비교 연산자
- `==` : 같음
- `!=` : 다름
- `<` : 작음
- `>` : 큼
- `<=` : 작거나 같음
- `>=` : 크거나 같음

#### 논리 연산자
- `and` : 논리 AND
- `or` : 논리 OR
- `not` : 논리 NOT

### 제어 구조

#### 조건문
```c
nif (조건) {
    # 참일 때 실행
} nelse {
    # 거짓일 때 실행
}
```

예제:
```c
nint age = 25
nif (age >= 20) {
    nout("성인입니다")
} nelse {
    nout("미성년자입니다")
}
```

#### 반복문

**while 루프 (nloop)**
```c
nloop (조건) {
    # 반복 실행
}
```

예제:
```c
nint i = 1
nloop (i <= 5) {
    nout(i)
    i = i + 1
}
```

**for 루프 (nfor)**
```c
nfor (초기화; 조건; 증가) {
    # 반복 실행
}
```

예제:
```c
nfor (nint i = 1; i <= 5; i = i + 1) {
    nout(i)
}
```

**중첩 루프**
```c
nfor (nint x = 1; x <= 3; x = x + 1) {
    nfor (nint y = 1; y <= 3; y = y + 1) {
        nout(x * y)
    }
}
```

### 함수
```c
nfunc 함수명(매개변수1, 매개변수2) {
    # 함수 본문
    nret 반환값  # 선택사항
}
```

함수 호출:
```c
함수명(인자1, 인자2)
```

예제:
```c
nfunc add(a, b) {
    nret a + b
}

nint result = add(10, 20)
nout(result)  # 30
```

### 출력
```c
nout(값)  # 자동으로 개행 추가
```

예제:
```c
nout("Hello, World!")
nout(42)
nout(3.14)
```

### 사용자 입력
```c
ninput(프롬프트)  # 사용자로부터 문자열 입력 받기
```

예제:
```c
nstring name = ninput("이름을 입력하세요: ")
nout("안녕하세요, " + name + "님!")

nstring age = ninput("나이: ")
nout("당신은 " + age + "살입니다")
```

### 제어문
```c
nbreak      # 루프 즉시 종료
ncontinue   # 다음 반복으로 건너뛰기
```

예제:
```c
# break 예제
nfor (nint i = 1; i <= 10; i = i + 1) {
    nif (i == 5) {
        nbreak  # 5에서 루프 종료
    }
    nout(i)  # 1, 2, 3, 4 출력
}

# continue 예제
nfor (nint i = 1; i <= 10; i = i + 1) {
    nif (i == 5) {
        ncontinue  # 5 건너뛰기
    }
    nout(i)  # 1, 2, 3, 4, 6, 7, 8, 9, 10 출력
}
```

### 배열
```c
narray 배열명 = [요소1, 요소2, ...]  # 배열 생성
배열명[인덱스]                        # 요소 접근
배열명[인덱스] = 값                   # 요소 수정
```

예제:
```c
# 배열 생성
narray nums = [1, 2, 3, 4, 5]
nout(nums)  # [1, 2, 3, 4, 5]

# 요소 접근
nout(nums[0])  # 1
nout(nums[2])  # 3

# 요소 수정
nums[1] = 100
nout(nums)  # [1, 100, 3, 4, 5]

# 문자열 배열
narray names = ["철수", "영희", "민수"]
nout(names[1])  # 영희
```

### 파일 I/O
```c
nopen(파일명, 모드)    # 파일 열기 ("r", "w", "a")
nread(파일)           # 파일 읽기
nwrite(파일, 내용)    # 파일 쓰기
nclose(파일)          # 파일 닫기
```

예제:
```c
# 파일 쓰기
nstring f = nopen("data.txt", "w")
nwrite(f, "Hello, World!\n")
nwrite(f, "NiceTop is awesome!")
nclose(f)

# 파일 읽기
nstring f2 = nopen("data.txt", "r")
nstring content = nread(f2)
nclose(f2)
nout(content)
```

## 프로그램 구조

NiceTop 프로그램은 순차적으로 실행되는 문장들의 집합입니다.

```c
# 1. 변수 선언
nint x = 10

# 2. 함수 정의
nfunc process(n) {
    nret n * 2
}

# 3. 실행
nint result = process(x)
nout(result)
```

## 스코프 규칙

- **전역 스코프**: 최상위에서 선언된 변수
- **함수 스코프**: 함수 내부에서 선언된 변수
- 내부 스코프에서 외부 스코프의 변수에 접근 가능
- 클로저 지원

## 타입 변환

동적 타입 언어로, 자동 타입 변환이 일어납니다:
- 숫자 + 문자열 = 문자열
- 논리 연산에서 자동으로 truthy/falsy 판단

## 예제

### 구구단 프로그램
```c
# 9단 출력
nint dan = 9
nfor (nint i = 1; i <= 9; i = i + 1) {
    nout(dan + " * " + i + " = " + dan * i)
}
```

출력:
```
9 * 1 = 9
9 * 2 = 18
9 * 3 = 27
...
9 * 9 = 81
```

### 팩토리얼 계산
```c
nfunc factorial(n) {
    nif (n <= 1) {
        nret 1
    } nelse {
        nret n * factorial(n - 1)
    }
}

nout("5! = ")
nout(factorial(5))  # 120
```

### 절차지향 스타일 프로그램
```c
# 데이터 정의
nint balance = 1000

# 함수 정의
nfunc deposit(amount) {
    balance = balance + amount
    nout("입금: " + amount)
}

nfunc withdraw(amount) {
    nif (balance >= amount) {
        balance = balance - amount
        nout("출금: " + amount)
    } nelse {
        nout("잔액 부족")
    }
}

nfunc show_balance() {
    nout("현재 잔액: " + balance)
}

# 실행
show_balance()
deposit(500)
withdraw(300)
show_balance()
```

## NiceTop 키워드 목록

| 키워드 | 의미 | 예제 |
|--------|------|------|
| `nint` | 정수형 타입 | `nint x = 10` |
| `nfloat` | 실수형 타입 | `nfloat pi = 3.14` |
| `nstring` | 문자열 타입 | `nstring name = "철수"` |
| `nbool` | 불린 타입 | `nbool flag = ntrue` |
| `narray` | 배열 타입 | `narray nums = [1, 2, 3]` |
| `nif` | 조건문 if | `nif (x > 0) { }` |
| `nelse` | 조건문 else | `nelse { }` |
| `nloop` | while 반복문 | `nloop (i < 10) { }` |
| `nfor` | for 반복문 | `nfor (nint i=0; i<10; i=i+1) { }` |
| `nbreak` | 루프 탈출 | `nbreak` |
| `ncontinue` | 다음 반복 | `ncontinue` |
| `nfunc` | 함수 정의 | `nfunc add(a, b) { }` |
| `nret` | 반환 | `nret a + b` |
| `nout` | 출력 | `nout("Hello")` |
| `ninput` | 사용자 입력 | `ninput("이름: ")` |
| `nopen` | 파일 열기 | `nopen("file.txt", "r")` |
| `nread` | 파일 읽기 | `nread(file)` |
| `nwrite` | 파일 쓰기 | `nwrite(file, "text")` |
| `nclose` | 파일 닫기 | `nclose(file)` |
| `ntrue` | 참 | `nbool flag = ntrue` |
| `nfalse` | 거짓 | `nbool flag = nfalse` |

## 이스케이프 문자

| 이스케이프 | 의미 |
|-----------|------|
| `\n` | 개행 |
| `\t` | 탭 |
| `\r` | 캐리지 리턴 |
| `\\` | 백슬래시 |
| `\"` | 큰따옴표 |
| `\'` | 작은따옴표 |

## 제한사항

현재 버전에서 지원하지 않는 기능:
- 딕셔너리/맵
- 클래스/객체
- 예외 처리
- 모듈 시스템
- 다차원 배열

## 향후 계획

- [ ] 배열 메서드 (push, pop, length 등)
- [ ] 문자열 메서드 (split, join 등)
- [ ] 표준 라이브러리 확장
- [ ] 모듈 시스템
- [ ] 예외 처리
