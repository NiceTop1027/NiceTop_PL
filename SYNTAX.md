# NiceTop 언어 문법 가이드

## NiceTop만의 특별한 키워드

모든 키워드는 **`n`** 접두사로 시작합니다! (NiceTop의 N)

### 타입 선언 (C 스타일)

```c
nint x = 10        // 정수형
nfloat pi = 3.14   // 실수형
nstring name = "철수"  // 문자열
nbool flag = ntrue     // 불린형
```

### 제어 구조

```c
// 조건문
nif (x > 10) {
    nout("크다")
} nelse {
    nout("작다")
}

// 반복문
nloop (count > 0) {
    nout(count)
    count = count - 1
}
```

### 함수

```c
// 함수 정의
nfunc add(a, b) {
    nret a + b
}

// 함수 호출
nint result = add(10, 20)
```

### 입출력

```c
nout("Hello, World!")  // 출력
nout(x)                // 변수 출력
```

### 불린 값

```c
nbool isReady = ntrue
nbool isFinished = nfalse
```

## 전체 키워드 목록

| 키워드 | 의미 | C/Python 대응 |
|--------|------|---------------|
| `nint` | 정수형 타입 | `int` |
| `nfloat` | 실수형 타입 | `float` |
| `nstring` | 문자열 타입 | `char*` / `str` |
| `nbool` | 불린 타입 | `bool` |
| `nif` | 조건문 | `if` |
| `nelse` | 조건문 else | `else` |
| `nloop` | 반복문 | `while` |
| `nfunc` | 함수 정의 | `function` / `def` |
| `nret` | 반환 | `return` |
| `nout` | 출력 | `printf` / `print` |
| `ntrue` | 참 | `true` |
| `nfalse` | 거짓 | `false` |

## 예제 프로그램

### Hello World
```c
nout("Hello, NiceTop!")
```

### 변수와 연산
```c
nint x = 10
nint y = 20
nint sum = x + y
nout("합계: ")
nout(sum)
```

### 함수
```c
nfunc factorial(n) {
    nif (n <= 1) {
        nret 1
    } nelse {
        nret n * factorial(n - 1)
    }
}

nout(factorial(5))  # 120
```

### 반복문
```c
nint i = 1
nloop (i <= 10) {
    nout(i)
    i = i + 1
}
```

## 연산자

### 산술 연산자
- `+` : 덧셈
- `-` : 뺄셈
- `*` : 곱셈
- `/` : 나눗셈
- `%` : 나머지

### 비교 연산자
- `==` : 같음
- `!=` : 다름
- `<` : 작음
- `>` : 큼
- `<=` : 작거나 같음
- `>=` : 크거나 같음

### 논리 연산자
- `and` : 논리 AND
- `or` : 논리 OR
- `not` : 논리 NOT

## 이스케이프 문자

NiceTop은 C 언어와 동일한 이스케이프 문자를 지원합니다:

| 이스케이프 | 의미 | 설명 |
|-----------|------|------|
| `\n` | 개행 (newline) | 새 줄로 이동 |
| `\t` | 탭 (tab) | 탭 간격 |
| `\r` | 캐리지 리턴 | 줄의 시작으로 |
| `\\` | 백슬래시 | 백슬래시 문자 |
| `\"` | 큰따옴표 | 큰따옴표 문자 |
| `\'` | 작은따옴표 | 작은따옴표 문자 |
| `\0` | NULL | NULL 문자 |
| `\a` | 벨 (alert) | 경고음 |
| `\b` | 백스페이스 | 한 칸 뒤로 |
| `\f` | 폼피드 | 페이지 넘김 |
| `\v` | 수직탭 | 수직 탭 |

### 예제
```c
nout("첫 번째 줄\n두 번째 줄")
nout("이름:\t철수")
nout("그는 \"안녕\"이라고 말했다")
nout("경로: C:\\Users\\nicetop")
```

## 주석
```c
# 한 줄 주석
nint x = 10  # 변수 선언
```

## 특징

✨ **C 언어 스타일의 타입 선언**
- 변수 선언 시 타입을 먼저 명시
- `nint x = 10` (C의 `int x = 10`과 유사)

🎯 **NiceTop만의 고유한 키워드**
- 모든 키워드에 `n` 접두사
- 다른 언어와 차별화된 독특한 문법

⚡ **간결하고 직관적**
- `nout` = output
- `nloop` = loop
- `nret` = return
