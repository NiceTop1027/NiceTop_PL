# NiceTop 설치 가이드

## 빠른 설치 (권장)

### macOS / Linux

터미널에서 한 줄로 설치:

```bash
curl -sSL https://raw.githubusercontent.com/NiceTop1027/NiceTop_PL/main/install.sh | bash
```

또는 wget 사용:

```bash
wget -qO- https://raw.githubusercontent.com/NiceTop1027/NiceTop_PL/main/install.sh | bash
```

## 수동 설치

### 1. 저장소 클론

```bash
git clone https://github.com/NiceTop1027/NiceTop_PL.git
cd NiceTop_PL
```

### 2. 컴파일

```bash
make
```

### 3. 설치

```bash
sudo make install
```

또는 로컬 설치:

```bash
# ~/.local/bin에 설치 (PATH에 추가 필요)
mkdir -p ~/.local/bin
cp nicetop ~/.local/bin/
cp ntpm ~/.local/bin/
export PATH="$HOME/.local/bin:$PATH"
```

## 필수 요구사항

- **macOS**: Xcode Command Line Tools
  ```bash
  xcode-select --install
  ```

- **Ubuntu/Debian**:
  ```bash
  sudo apt-get install build-essential
  ```

- **CentOS/RHEL**:
  ```bash
  sudo yum groupinstall 'Development Tools'
  ```

## 설치 확인

```bash
nicetop --version
which nicetop
```

## 첫 프로그램 실행

```bash
# hello.nt 파일 생성
cat > hello.nt << 'EOF'
nout("Hello, NiceTop!")
EOF

# 실행
nicetop hello.nt
```

## 제거

```bash
sudo rm /usr/local/bin/nicetop
sudo rm /usr/local/bin/ntpm
```

## 문제 해결

### "command not found" 오류

PATH에 /usr/local/bin이 포함되어 있는지 확인:

```bash
echo $PATH
```

없다면 추가:

```bash
export PATH="/usr/local/bin:$PATH"
echo 'export PATH="/usr/local/bin:$PATH"' >> ~/.bashrc  # 또는 ~/.zshrc
```

### 권한 오류

```bash
sudo chmod +x /usr/local/bin/nicetop
```

### 컴파일 오류

GCC 또는 Clang이 설치되어 있는지 확인:

```bash
gcc --version
# 또는
clang --version
```

## Windows 설치

### 방법 1: ZIP 바이너리 (권장)

1. [nicetop-1.0.0-windows.zip](https://github.com/NiceTop1027/NiceTop_PL/releases) 다운로드
2. 압축 해제
3. `install.bat`을 **관리자 권한으로 실행**
   - 마우스 오른쪽 버튼 클릭
   - "관리자 권한으로 실행" 선택

### 방법 2: 수동 설치

1. `nicetop.exe`를 원하는 위치에 복사 (예: `C:\Program Files\NiceTop\`)
2. 시스템 환경 변수 PATH에 해당 경로 추가
3. 새 명령 프롬프트에서 `nicetop` 사용

### 방법 3: WSL (Linux 환경)

WSL(Windows Subsystem for Linux)을 통한 설치:

1. WSL 설치
2. Ubuntu 설치
3. 위의 Linux 설치 방법 따라하기

### 소스에서 빌드 (고급)

MinGW 설치 후:
```bash
git clone https://github.com/NiceTop1027/NiceTop_PL.git
cd NiceTop_PL
make -f Makefile.windows
```

## 도움말

- GitHub: https://github.com/NiceTop1027/NiceTop_PL
- 문서: [README.md](README.md)
- 문법: [SYNTAX.md](SYNTAX.md)
- 언어 명세: [LANGUAGE_SPEC.md](LANGUAGE_SPEC.md)
