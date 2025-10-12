# NiceTop v1.0.0 - 첫 공식 릴리즈 🎉

## 개요

NiceTop은 C 언어로 구현된 절차지향 프로그래밍 언어입니다. 모든 키워드에 `n` 접두사를 사용하는 독특한 문법을 가지고 있으며, Python이나 Node.js처럼 쉽게 설치하고 사용할 수 있습니다.

## 주요 기능

### ✨ 언어 기능
- **C 스타일 타입 선언**: `nint`, `nfloat`, `nstring`, `nbool`
- **제어 구조**: `nif`/`nelse` 조건문
- **반복문**: `nloop` (while), `nfor` (for)
- **함수**: `nfunc`/`nret`
- **출력**: `nout` (자동 개행)
- **이스케이프 문자**: `\n`, `\t`, `\\`, `\"` 등 완벽 지원

### ⚡ 성능
- C로 구현된 네이티브 인터프리터
- Python 불필요
- 빠른 실행 속도

### 📦 설치 방법

#### macOS - DMG 설치 (권장)
1. `NiceTop-1.0.0.dmg` 다운로드
2. 더블클릭하여 열기
3. NiceTop.app을 Applications 폴더로 드래그
4. 터미널에서 `nicetop` 명령어 사용

#### 한 줄 설치
```bash
curl -sSL https://raw.githubusercontent.com/NiceTop1027/NiceTop_PL/main/install.sh | bash
```

#### ZIP 바이너리
1. `nicetop-1.0.0-macos.zip` 다운로드
2. 압축 해제
3. `./install.sh` 실행

## 예제 코드

### Hello World
```c
nout("Hello, NiceTop!")
```

### 구구단
```c
nint dan = 9
nfor (nint i = 1; i <= 9; i = i + 1) {
    nout(dan + " * " + i + " = " + dan * i)
}
```

### 함수와 재귀
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

## 다운로드

### macOS
- **NiceTop-1.0.0.dmg** (39KB) - DMG 설치 이미지
- **nicetop-1.0.0-macos.zip** (24KB) - 바이너리 패키지

### Linux
소스에서 빌드:
```bash
git clone https://github.com/NiceTop1027/NiceTop_PL.git
cd NiceTop_PL
make
sudo make install
```

## 시스템 요구사항

- **macOS**: 10.13 (High Sierra) 이상
- **Linux**: GCC 7.0+ 또는 Clang 5.0+
- **Windows**: WSL 2 (Ubuntu 20.04+)

## 문서

- [README.md](README.md) - 프로젝트 소개
- [SYNTAX.md](SYNTAX.md) - 문법 가이드
- [LANGUAGE_SPEC.md](LANGUAGE_SPEC.md) - 언어 명세서
- [INSTALL.md](INSTALL.md) - 설치 가이드

## 변경사항

### 새로운 기능
- ✨ for 루프 (`nfor`) 구현
- ✨ while 루프 (`nloop`) 완벽 작동
- ✨ 중첩 루프 지원
- ✨ 이스케이프 문자 완벽 지원
- ✨ 자동 개행 출력
- ✨ DMG 설치 파일
- ✨ 한 줄 설치 스크립트

### 개선사항
- 🚀 C로 완전히 재작성 (Python 의존성 제거)
- 🚀 성능 최적화
- 📝 완전한 문서화
- 🎨 깔끔한 프로젝트 구조

## 알려진 이슈

현재 버전에서 지원하지 않는 기능:
- 배열/리스트
- break/continue 문
- 사용자 입력 (ninput)
- 파일 I/O
- 예외 처리

## 향후 계획

- [ ] 배열 자료구조
- [ ] break/continue 문
- [ ] 사용자 입력 함수
- [ ] 표준 라이브러리 확장
- [ ] Windows 네이티브 지원

## 기여

버그 리포트, 기능 제안, Pull Request를 환영합니다!

- GitHub: https://github.com/NiceTop1027/NiceTop_PL
- Issues: https://github.com/NiceTop1027/NiceTop_PL/issues

## 라이선스

MIT License

## 감사의 말

NiceTop을 사용해주셔서 감사합니다! 🎊
