# NiceTop 언어 명세서

## 개요
**NiceTop**은 절차지향 프로그래밍 패러다임을 따르는 동적 타입 언어입니다.

## 파일 확장자
`.nt` (NiceTop)

## 기본 문법

### 주석
```
# 한 줄 주석
```

### 데이터 타입
- **숫자 (Number)**: 정수 및 실수
  - 예: `10`, `3.14`, `-5`
- **문자열 (String)**: 큰따옴표 또는 작은따옴표
  - 예: `"Hello"`, `'World'`
- **불린 (Boolean)**: `true`, `false`
- **Null**: `null` (반환값이 없을 때)

### 변수
```javascript
let 변수명 = 값
```

변수 재할당:
```javascript
변수명 = 새로운값
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
```javascript
if (조건) {
    # 참일 때 실행
} else {
    # 거짓일 때 실행
}
```

#### 반복문
```javascript
while (조건) {
    # 반복 실행
}
```

### 프로시저 (함수)
```javascript
function 함수명(매개변수1, 매개변수2) {
    # 함수 본문
    return 반환값  # 선택사항
}
```

함수 호출:
```javascript
함수명(인자1, 인자2)
```

### 출력
```javascript
print(값)
```

## 프로그램 구조

NiceTop 프로그램은 순차적으로 실행되는 문장들의 집합입니다.

```javascript
# 1. 변수 선언
let x = 10

# 2. 프로시저 정의
function process(n) {
    return n * 2
}

# 3. 실행
let result = process(x)
print(result)
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

### 절차지향 스타일 프로그램
```javascript
# 데이터 정의
let balance = 1000

# 프로시저 정의
function deposit(amount) {
    balance = balance + amount
    print("입금: ")
    print(amount)
}

function withdraw(amount) {
    if (balance >= amount) {
        balance = balance - amount
        print("출금: ")
        print(amount)
    } else {
        print("잔액 부족")
    }
}

function show_balance() {
    print("현재 잔액: ")
    print(balance)
}

# 프로시저 실행
show_balance()
deposit(500)
withdraw(300)
show_balance()
```

## 제한사항

현재 버전에서 지원하지 않는 기능:
- 배열/리스트
- 딕셔너리/맵
- 클래스/객체
- for 루프
- break/continue
- 예외 처리
- 모듈 시스템
- 파일 I/O

## 향후 계획

- 배열 자료구조
- for 루프
- break/continue 문
- 표준 라이브러리
- 모듈 시스템
