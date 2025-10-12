#!/bin/bash
# NiceTop Windows 빌드 스크립트
# MinGW를 사용하여 Windows .exe 생성

set -e

VERSION="1.0.0"
BUILD_DIR="build"
RELEASE_DIR="release"

echo "======================================"
echo "  NiceTop Windows 빌드 v${VERSION}"
echo "======================================"
echo ""

# MinGW 확인
if ! command -v x86_64-w64-mingw32-gcc &> /dev/null; then
    echo "오류: MinGW가 설치되어 있지 않습니다."
    echo ""
    echo "설치 방법:"
    echo "  macOS:   brew install mingw-w64"
    echo "  Ubuntu:  sudo apt-get install mingw-w64"
    echo "  Fedora:  sudo dnf install mingw64-gcc"
    exit 1
fi

echo "✓ MinGW 발견"
echo ""

# 정리
mkdir -p "$BUILD_DIR" "$RELEASE_DIR"

# Windows용 컴파일
echo "Windows용 컴파일 중..."
x86_64-w64-mingw32-gcc -Wall -Wextra -std=c11 -O3 -Isrc \
    src/main.c src/lexer.c src/value.c src/interpreter.c \
    -o "$BUILD_DIR/nicetop.exe"

echo "✓ 컴파일 완료"
echo ""

# Windows 패키지 생성
echo "Windows 패키지 생성 중..."
WIN_DIR="$BUILD_DIR/nicetop-${VERSION}-windows"
mkdir -p "$WIN_DIR/bin"
mkdir -p "$WIN_DIR/examples"
mkdir -p "$WIN_DIR/docs"

# 파일 복사
cp "$BUILD_DIR/nicetop.exe" "$WIN_DIR/bin/"
cp examples/*.nt "$WIN_DIR/examples/" 2>/dev/null || true
cp README.md SYNTAX.md LANGUAGE_SPEC.md INSTALL.md "$WIN_DIR/docs/"

# Windows 설치 배치 파일 생성
cat > "$WIN_DIR/install.bat" << 'EOF'
@echo off
echo NiceTop 설치 중...
echo.

REM 관리자 권한 확인
net session >nul 2>&1
if %errorLevel% == 0 (
    echo 관리자 권한으로 실행 중...
) else (
    echo 이 스크립트는 관리자 권한이 필요합니다.
    echo 마우스 오른쪽 버튼 클릭 후 "관리자 권한으로 실행"을 선택하세요.
    pause
    exit /b 1
)

REM C:\Program Files\NiceTop에 설치
set INSTALL_DIR=C:\Program Files\NiceTop
mkdir "%INSTALL_DIR%" 2>nul
copy bin\nicetop.exe "%INSTALL_DIR%\" /Y

REM PATH에 추가
setx /M PATH "%PATH%;%INSTALL_DIR%"

echo.
echo 설치 완료!
echo.
echo 사용법: nicetop [파일.nt]
echo.
echo 새 터미널을 열어서 사용하세요.
pause
EOF

# README 생성
cat > "$WIN_DIR/README.txt" << EOF
NiceTop 프로그래밍 언어 v${VERSION} - Windows
====================================

설치 방법 1 (권장):
  1. install.bat을 마우스 오른쪽 버튼 클릭
  2. "관리자 권한으로 실행" 선택

설치 방법 2 (수동):
  1. bin/nicetop.exe를 원하는 위치에 복사
  2. 해당 위치를 PATH에 추가

사용법:
  nicetop.exe <파일.nt>
  nicetop.exe  (REPL 모드)

예제:
  nicetop.exe examples\hello.nt

문서:
  docs\README.md
  docs\SYNTAX.md
  docs\LANGUAGE_SPEC.md

주의사항:
  - Windows 10 이상 권장
  - 명령 프롬프트(cmd) 또는 PowerShell에서 실행

GitHub:
  https://github.com/NiceTop1027/NiceTop_PL
EOF

# ZIP 압축
cd "$BUILD_DIR"
zip -r "../$RELEASE_DIR/nicetop-${VERSION}-windows.zip" "nicetop-${VERSION}-windows"
cd ..

echo "✓ Windows 패키지 생성 완료"
echo "  → $RELEASE_DIR/nicetop-${VERSION}-windows.zip"
echo ""

# 파일 크기 확인
echo "생성된 파일:"
ls -lh "$RELEASE_DIR/nicetop-${VERSION}-windows.zip"
echo ""

echo "======================================"
echo "  Windows 빌드 완료!"
echo "======================================"
echo ""
echo "배포 파일: $RELEASE_DIR/nicetop-${VERSION}-windows.zip"
echo ""
