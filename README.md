# NiceTop 프로그래밍 언어 (.nt)

**절차지향 프로그래밍 언어** - 간단하고 배우기 쉬운 절차지향 언어입니다.

## 특징

- ✨ 절차지향 프로그래밍 패러다임
- 🔢 동적 타입 시스템
- 🎯 변수, 프로시저(함수), 조건문, 반복문 지원
- ⚡ **C 언어로 구현된 네이티브 인터프리터**
- 📝 한글 주석 및 문자열 지원
- 📄 파일 확장자: `.nt` (NiceTop)
- 🚀 독립 실행 파일 - Python 불필요!

## 설치 및 실행

### 요구사항
- GCC 또는 Clang 컴파일러
- Make

### 빌드
```bash
# 컴파일
make

# 또는 테스트와 함께
make test
```

### 설치 (선택사항)
```bash
# 시스템 전역 설치
sudo make install
```

### 파일 실행
```bash
# 직접 실행
./nicetop examples/hello.nt

# 또는 설치 후
nicetop examples/hello.nt
```

### REPL 모드
```bash
./nicetop
# 또는
nicetop
```

## 문법 가이드

### 1. 변수 선언 (C 스타일)
NiceTop은 C 언어처럼 타입을 먼저 선언합니다!

```c
nint age = 25          // 정수형
nfloat pi = 3.14       // 실수형
nstring name = "철수"   // 문자열
nbool flag = ntrue     // 불린형
```

### 2. 산술 연산
```javascript
let a = 10 + 5    # 덧셈
let b = 10 - 5    # 뺄셈
let c = 10 * 5    # 곱셈
let d = 10 / 5    # 나눗셈
let e = 10 % 3    # 나머지
```

### 3. 비교 연산
```javascript
let result1 = 10 == 10   # 같음
let result2 = 10 != 5    # 다름
let result3 = 10 > 5     # 크다
let result4 = 10 < 20    # 작다
let result5 = 10 >= 10   # 크거나 같다
let result6 = 10 <= 20   # 작거나 같다
```

### 4. 논리 연산
```javascript
let result1 = true and false   # AND
let result2 = true or false    # OR
let result3 = not true         # NOT
```

### 5. 조건문
```c
nif (age >= 18) {
    nout("성인입니다")
} nelse {
    nout("미성년자입니다")
}
```

### 6. 반복문
```c
nint i = 1
nloop (i <= 10) {
    nout(i)
    i = i + 1
}
```

### 7. 함수
```c
nfunc greet(name) {
    nout("안녕하세요, " + name + "님!")
}

greet("철수")

nfunc add(a, b) {
    nret a + b
}

nint sum = add(10, 20)
```

### 8. 출력
```c
nout("Hello, World!")
nout(42)
nout(3.14)
```

### 9. NiceTop 키워드
모든 키워드는 **`n`** 접두사로 시작합니다!
- `nint`, `nfloat`, `nstring`, `nbool` - 타입
- `nif`, `nelse` - 조건문
- `nloop` - 반복문
- `nfunc`, `nret` - 함수
- `nout` - 출력
- `ntrue`, `nfalse` - 불린 값

### 9. 주석
```javascript
# 한 줄 주석
let x = 10  # 변수 선언
```

## 예제 프로그램

### Hello World
```javascript
print("안녕하세요, NiceTop입니다!")
print("절차지향 프로그래밍 언어")
```

### 팩토리얼 계산
```javascript
function factorial(n) {
    if (n <= 1) {
        return 1
    } else {
        return n * factorial(n - 1)
    }
}

print(factorial(5))  # 120
```

### FizzBuzz
```javascript
let n = 1
while (n <= 30) {
    if (n % 15 == 0) {
        print("FizzBuzz")
    } else {
        if (n % 3 == 0) {
            print("Fizz")
        } else {
            if (n % 5 == 0) {
                print("Buzz")
            } else {
                print(n)
            }
        }
    }
    n = n + 1
}
```

## 프로젝트 구조

```
NiceTop_L/
├── src/               # C 소스 코드
│   ├── nicetop.h      # 헤더 파일
│   ├── lexer.c        # 렉서 (토크나이저)
│   ├── value.c        # 값 및 환경 관리
│   ├── interpreter.c  # 인터프리터
│   └── main.c         # 메인 진입점
├── Makefile           # 빌드 스크립트
├── nicetop            # 컴파일된 실행 파일
├── README.md          # 문서
├── LANGUAGE_SPEC.md   # 언어 명세서
└── examples/          # 예제 프로그램 (.nt)
    ├── hello.nt
    ├── variables.nt
    ├── procedures.nt
    ├── control_flow.nt
    ├── calculator.nt
    └── array_simulation.nt
```

## 언어 구현 세부사항

### C 언어로 구현
NiceTop은 **순수 C 언어**로 작성되어 빠른 실행 속도를 자랑합니다.

### 렉서 (Lexer)
- 소스 코드를 토큰으로 변환
- 키워드, 식별자, 리터럴, 연산자 인식
- 주석 처리

### 인터프리터 (Interpreter)
- 토큰을 직접 실행 (트리워킹 인터프리터)
- 재귀 하강 파싱 방식
- 환경(Environment)을 통한 스코프 관리
- 함수 클로저 지원

### 성능
- C로 구현되어 Python 구현보다 **10-100배 빠름**
- 네이티브 바이너리로 컴파일
- 외부 의존성 없음

## 향후 개선 사항

- [ ] 배열/리스트 자료구조
- [ ] 딕셔너리/맵 자료구조
- [ ] for 루프
- [ ] break/continue 문
- [ ] 파일 입출력
- [ ] 표준 라이브러리
- [ ] 에러 메시지 개선
- [ ] 디버거

## 라이선스

MIT License

## 기여

버그 리포트나 기능 제안은 언제든지 환영합니다!
