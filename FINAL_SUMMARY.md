# NiceTop 프로그래밍 언어 - 최종 요약

## ✅ 완성된 기능

### 핵심 기능
- **C 스타일 타입 선언**: `nint`, `nfloat`, `nstring`, `nbool`
- **변수와 연산**: 산술, 비교, 논리 연산
- **함수**: `nfunc`, `nret`
- **조건문**: `nif`, `nelse`
- **반복문**: `nloop` (while 루프) ✅ 작동 확인
- **출력**: `nout` (자동 개행)
- **이스케이프 문자**: `\n`, `\t`, `\\`, `\"`, `\'` 등
- **주석**: `#`

### 사용 예제

```c
# 변수
nint x = 10
nstring name = "NiceTop"

# 출력
nout("Hello, " + name)

# 함수
nfunc square(n) {
    nret n * n
}
nout(square(5))  // 25

# while 루프
nint i = 1
nloop (i <= 5) {
    nout(i)
    i = i + 1
}

# 조건문
nif (x > 5) {
    nout("크다")
} nelse {
    nout("작다")
}
```

## 🚀 실행 방법

```bash
nicetop yourfile.nt
```

## 📦 설치

```bash
cd NiceTop_L
make
sudo make install
```

## 🎯 특징

1. **C로 구현**: 빠른 실행 속도
2. **독립 실행**: Python 불필요
3. **고유한 문법**: 모든 키워드에 `n` 접두사
4. **절차지향**: 간단하고 명확한 프로그래밍

## 📚 GitHub

https://github.com/NiceTop1027/NiceTop_PL.git

## 🔄 다음 단계

- [ ] for 루프 (`nfor`)
- [ ] break/continue
- [ ] 배열 자료구조
- [ ] 입력 함수 (`ninput`)
- [ ] 표준 라이브러리 확장
