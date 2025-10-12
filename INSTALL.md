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

## Windows 지원

현재 Windows는 WSL(Windows Subsystem for Linux)을 통해 지원됩니다:

1. WSL 설치
2. Ubuntu 설치
3. 위의 Linux 설치 방법 따라하기

## 도움말

- GitHub: https://github.com/NiceTop1027/NiceTop_PL
- 문서: [README.md](README.md)
- 문법: [SYNTAX.md](SYNTAX.md)
- 언어 명세: [LANGUAGE_SPEC.md](LANGUAGE_SPEC.md)
