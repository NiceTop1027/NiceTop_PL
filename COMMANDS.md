# NiceTop 명령어 모음집

## 🚀 설치 및 빌드

### 빠른 설치 (한 줄)
```bash
curl -sSL https://raw.githubusercontent.com/NiceTop1027/NiceTop_PL/main/install.sh | bash
```

### 저장소 클론
```bash
git clone https://github.com/NiceTop1027/NiceTop_PL.git
cd NiceTop_PL
```

### 컴파일
```bash
make                    # 일반 빌드
make clean              # 정리
make clean && make      # 완전 재빌드
```

### 설치
```bash
sudo make install       # /usr/local/bin에 설치
make install            # 권한이 있는 경우
```

### 제거
```bash
sudo rm /usr/local/bin/nicetop
sudo rm /usr/local/bin/ntpm
```

## 📦 릴리즈 빌드

### macOS 릴리즈 (DMG + ZIP)
```bash
./build_release.sh
```

생성 파일:
- `release/NiceTop-1.0.0.dmg`
- `release/nicetop-1.0.0-macos.zip`

### Windows 릴리즈 (.exe)
```bash
# MinGW 설치 (최초 1회)
brew install mingw-w64

# Windows 빌드
./build_windows.sh
```

생성 파일:
- `release/nicetop-1.0.0-windows.zip`

### 모든 플랫폼 빌드
```bash
./build_release.sh && ./build_windows.sh
```

## 🎯 실행

### 파일 실행
```bash
nicetop hello.nt                    # 파일 실행
./nicetop examples/hello.nt         # 상대 경로
nicetop /path/to/file.nt            # 절대 경로
```

### REPL 모드
```bash
nicetop                             # 대화형 모드 시작
```

## 🧪 테스트

### 기본 테스트
```bash
make test                           # 예제 파일 테스트
```

### 개별 예제 실행
```bash
nicetop examples/hello.nt           # Hello World
nicetop examples/variables.nt       # 변수
nicetop examples/procedures.nt      # 함수
nicetop examples/for_loop.nt        # for 루프
nicetop examples/while_loop.nt      # while 루프
nicetop examples/loops_complete.nt  # 구구단
```

### 빠른 테스트
```bash
echo 'nout("Hello!")' | nicetop     # 표준 입력
echo 'nout(5 * 5)' > test.nt && nicetop test.nt
```

## 📝 파일 생성

### Hello World
```bash
cat > hello.nt << 'EOF'
nout("Hello, NiceTop!")
EOF
nicetop hello.nt
```

### 구구단
```bash
cat > gugudan.nt << 'EOF'
nint dan = 9
nfor (nint i = 1; i <= 9; i = i + 1) {
    nout(dan + " * " + i + " = " + dan * i)
}
EOF
nicetop gugudan.nt
```

### 팩토리얼
```bash
cat > factorial.nt << 'EOF'
nfunc factorial(n) {
    nif (n <= 1) {
        nret 1
    } nelse {
        nret n * factorial(n - 1)
    }
}
nout(factorial(5))
EOF
nicetop factorial.nt
```

## 🔧 개발

### 디버그 빌드
```bash
make CFLAGS="-Wall -Wextra -std=c11 -g -Isrc"
```

### 최적화 빌드
```bash
make CFLAGS="-Wall -Wextra -std=c11 -O3 -Isrc"
```

### 특정 파일만 재컴파일
```bash
gcc -Wall -Wextra -std=c11 -O2 -Isrc -c src/interpreter.c -o src/interpreter.o
make
```

### 경고 무시
```bash
make 2>&1 | grep -v "warning:"
```

## 📚 Git 작업

### 커밋 및 푸시
```bash
git add .
git commit -m "메시지"
git push
```

### 상태 확인
```bash
git status
git log --oneline -5
git diff
```

### 브랜치
```bash
git branch                          # 브랜치 목록
git checkout -b feature/new         # 새 브랜치
git checkout main                   # main으로 전환
git merge feature/new               # 병합
```

### 태그 (릴리즈)
```bash
git tag v1.0.0                      # 태그 생성
git push origin v1.0.0              # 태그 푸시
git tag -d v1.0.0                   # 태그 삭제
git push origin :refs/tags/v1.0.0  # 원격 태그 삭제
```

## 🌐 GitHub Release

### 릴리즈 생성 순서
```bash
# 1. 릴리즈 빌드
./build_release.sh
./build_windows.sh

# 2. 파일 확인
ls -lh release/

# 3. Git 태그
git tag v1.0.0
git push origin v1.0.0

# 4. GitHub에서 Release 생성
# - https://github.com/NiceTop1027/NiceTop_PL/releases
# - "Create a new release" 클릭
# - 파일 업로드: release/*.dmg, release/*.zip
```

## 🧹 정리

### 빌드 파일 정리
```bash
make clean                          # 오브젝트 파일 삭제
rm -rf build/ release/              # 빌드 디렉토리 삭제
rm -f nicetop                       # 실행 파일 삭제
```

### 테스트 파일 정리
```bash
rm -f test*.nt
rm -f *.nt
```

### 완전 정리
```bash
make clean
rm -rf build/ release/
git clean -fdx                      # Git 추적 안 되는 모든 파일 삭제 (주의!)
```

## 📊 정보 확인

### 버전 확인
```bash
nicetop --version                   # (구현 필요)
which nicetop                       # 설치 위치
file nicetop                        # 파일 타입
```

### 파일 크기
```bash
ls -lh nicetop
du -h nicetop
```

### 의존성 확인
```bash
otool -L nicetop                    # macOS
ldd nicetop                         # Linux
```

### 코드 통계
```bash
wc -l src/*.c src/*.h               # 라인 수
find src -name "*.c" -o -name "*.h" | xargs wc -l
cloc src/                           # cloc 설치 필요
```

## 🔍 디버깅

### GDB 디버깅
```bash
gcc -g -Isrc src/*.c -o nicetop
gdb nicetop
# (gdb) run examples/hello.nt
# (gdb) break main
# (gdb) continue
```

### Valgrind (메모리 검사)
```bash
valgrind --leak-check=full ./nicetop examples/hello.nt
```

### 스택 트레이스
```bash
lldb nicetop
# (lldb) run examples/hello.nt
# (lldb) bt
```

## 📦 패키지 관리 (ntpm)

### 패키지 설치
```bash
ntpm install math                   # 패키지 설치
ntpm list                           # 설치된 패키지 목록
```

### 패키지 사용
```bash
cat > test.nt << 'EOF'
use math
nout(math.sqrt(16))
EOF
nicetop test.nt
```

## 🎨 유용한 별칭 (Alias)

### Bash/Zsh 설정 (~/.bashrc 또는 ~/.zshrc)
```bash
alias nt='nicetop'
alias ntb='make clean && make'
alias ntr='./build_release.sh'
alias ntw='./build_windows.sh'
alias ntt='make test'
alias ntc='make clean'
```

사용:
```bash
nt hello.nt                         # nicetop hello.nt
ntb                                 # 재빌드
ntr                                 # 릴리즈 빌드
```

## 📱 빠른 참조

### 한 줄 명령어
```bash
# 설치
curl -sSL https://raw.githubusercontent.com/NiceTop1027/NiceTop_PL/main/install.sh | bash

# 빌드
make clean && make && sudo make install

# 테스트
echo 'nout("Test")' | nicetop

# 릴리즈
./build_release.sh && ./build_windows.sh

# 정리
make clean && rm -rf build/ release/
```

## 🆘 문제 해결

### 컴파일 오류
```bash
# GCC 확인
gcc --version

# 재빌드
make clean && make

# 권한 문제
sudo make install
```

### 실행 오류
```bash
# PATH 확인
echo $PATH
which nicetop

# 권한 부여
chmod +x nicetop
```

### Git 문제
```bash
# 변경사항 취소
git checkout .

# 강제 푸시 (주의!)
git push -f origin main
```

## 📖 더 보기

- [README.md](README.md) - 프로젝트 소개
- [SYNTAX.md](SYNTAX.md) - 문법 가이드
- [LANGUAGE_SPEC.md](LANGUAGE_SPEC.md) - 언어 명세
- [INSTALL.md](INSTALL.md) - 설치 가이드
- [RELEASE.md](RELEASE.md) - 릴리즈 가이드
