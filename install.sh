#!/bin/bash
# NiceTop 프로그래밍 언어 설치 스크립트
# 사용법: curl -sSL https://raw.githubusercontent.com/NiceTop1027/NiceTop_PL/main/install.sh | bash

set -e

echo "======================================"
echo "  NiceTop 프로그래밍 언어 설치"
echo "======================================"
echo ""

# 색상 정의
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# OS 확인
OS="$(uname -s)"
case "${OS}" in
    Linux*)     MACHINE=Linux;;
    Darwin*)    MACHINE=Mac;;
    *)          MACHINE="UNKNOWN:${OS}"
esac

echo -e "${BLUE}감지된 OS: ${MACHINE}${NC}"
echo ""

# 필수 도구 확인
echo "필수 도구 확인 중..."

if ! command -v gcc &> /dev/null && ! command -v clang &> /dev/null; then
    echo -e "${RED}오류: GCC 또는 Clang 컴파일러가 필요합니다.${NC}"
    if [ "$MACHINE" = "Mac" ]; then
        echo "Xcode Command Line Tools를 설치하세요:"
        echo "  xcode-select --install"
    else
        echo "GCC를 설치하세요:"
        echo "  sudo apt-get install build-essential  # Ubuntu/Debian"
        echo "  sudo yum groupinstall 'Development Tools'  # CentOS/RHEL"
    fi
    exit 1
fi

if ! command -v make &> /dev/null; then
    echo -e "${RED}오류: make가 필요합니다.${NC}"
    exit 1
fi

echo -e "${GREEN}✓ 필수 도구 확인 완료${NC}"
echo ""

# 임시 디렉토리 생성
TEMP_DIR=$(mktemp -d)
cd "$TEMP_DIR"

echo "NiceTop 다운로드 중..."
if command -v git &> /dev/null; then
    git clone https://github.com/NiceTop1027/NiceTop_PL.git
    cd NiceTop_PL
else
    echo -e "${YELLOW}Git이 없습니다. ZIP 파일로 다운로드합니다...${NC}"
    curl -L https://github.com/NiceTop1027/NiceTop_PL/archive/refs/heads/main.zip -o nicetop.zip
    unzip -q nicetop.zip
    cd NiceTop_PL-main
fi

echo -e "${GREEN}✓ 다운로드 완료${NC}"
echo ""

# 컴파일
echo "NiceTop 컴파일 중..."
make clean > /dev/null 2>&1 || true
if make; then
    echo -e "${GREEN}✓ 컴파일 완료${NC}"
else
    echo -e "${RED}✗ 컴파일 실패${NC}"
    exit 1
fi
echo ""

# 설치
echo "NiceTop 설치 중..."
if [ -w "/usr/local/bin" ]; then
    cp nicetop /usr/local/bin/
    cp ntpm /usr/local/bin/
    chmod +x /usr/local/bin/nicetop
    chmod +x /usr/local/bin/ntpm
    echo -e "${GREEN}✓ /usr/local/bin에 설치 완료${NC}"
else
    echo -e "${YELLOW}관리자 권한이 필요합니다...${NC}"
    sudo cp nicetop /usr/local/bin/
    sudo cp ntpm /usr/local/bin/
    sudo chmod +x /usr/local/bin/nicetop
    sudo chmod +x /usr/local/bin/ntpm
    echo -e "${GREEN}✓ /usr/local/bin에 설치 완료${NC}"
fi

# 정리
cd ~
rm -rf "$TEMP_DIR"

echo ""
echo "======================================"
echo -e "${GREEN}  설치 완료!${NC}"
echo "======================================"
echo ""
echo "사용법:"
echo "  nicetop <파일.nt>    # 프로그램 실행"
echo "  nicetop              # REPL 모드"
echo "  ntpm install <pkg>   # 패키지 설치"
echo ""
echo "예제:"
echo "  echo 'nout(\"Hello, NiceTop!\")' > hello.nt"
echo "  nicetop hello.nt"
echo ""
echo "문서: https://github.com/NiceTop1027/NiceTop_PL"
echo ""

# 버전 확인
if command -v nicetop &> /dev/null; then
    echo -e "${BLUE}설치된 위치: $(which nicetop)${NC}"
fi
