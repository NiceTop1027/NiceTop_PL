#!/bin/bash
# NiceTop 설치 스크립트

echo "NiceTop 프로그래밍 언어 설치 중..."

# 실행 권한 부여
chmod +x nicetop

# 현재 디렉토리를 PATH에 추가하거나 /usr/local/bin에 심볼릭 링크 생성
if [ -w "/usr/local/bin" ]; then
    echo "시스템 전역으로 설치 중..."
    ln -sf "$(pwd)/nicetop" /usr/local/bin/nicetop
    echo "✓ nicetop이 /usr/local/bin에 설치되었습니다."
    echo "이제 'nicetop' 명령어를 사용할 수 있습니다!"
else
    echo "권한이 없습니다. sudo로 다시 시도하거나 로컬 설치를 사용하세요."
    echo ""
    echo "로컬 설치 방법:"
    echo "1. ~/.bashrc 또는 ~/.zshrc에 다음을 추가:"
    echo "   export PATH=\"$(pwd):\$PATH\""
    echo ""
    echo "2. 또는 직접 실행:"
    echo "   ./nicetop examples/hello.nt"
fi

echo ""
echo "설치 완료!"
echo ""
echo "사용법:"
echo "  nicetop <파일.nt>     # 파일 실행"
echo "  nicetop               # REPL 모드"
