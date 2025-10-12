# NiceTop Language Support for VS Code

NiceTop 프로그래밍 언어를 위한 VS Code 확장입니다.

## 기능

- 문법 하이라이팅 (Syntax Highlighting)
- 자동 괄호 닫기
- 주석 지원
- 코드 포맷팅

## 설치 방법

### 방법 1: 로컬 설치

1. 이 폴더를 VS Code 확장 디렉토리로 복사:
   ```bash
   cp -r vscode-nicetop ~/.vscode/extensions/
   ```

2. VS Code 재시작

### 방법 2: VSIX 패키지 설치

1. VSIX 패키지 생성:
   ```bash
   cd vscode-nicetop
   npm install -g vsce
   vsce package
   ```

2. VS Code에서 설치:
   - `Ctrl+Shift+P` (Mac: `Cmd+Shift+P`)
   - "Extensions: Install from VSIX..." 선택
   - 생성된 `.vsix` 파일 선택

## 지원하는 키워드

### 타입
- `nint`, `nfloat`, `nstring`, `nbool`, `narray`

### 제어문
- `nif`, `nelse`, `nloop`, `nfor`, `nbreak`, `ncontinue`

### 함수
- `nfunc`, `nret`

### 입출력
- `nout`, `ninput`

### 파일 I/O
- `nopen`, `nread`, `nwrite`, `nclose`

### 상수
- `ntrue`, `nfalse`

## 예제

```nicetop
# Hello World
nout("Hello, NiceTop!")

# 변수
nint x = 10
nstring name = "철수"

# 배열
narray nums = [1, 2, 3, 4, 5]

# 반복문
nfor (nint i = 0; i < 5; i = i + 1) {
    nout(nums[i])
}

# 함수
nfunc add(a, b) {
    nret a + b
}
```

## 라이선스

MIT
