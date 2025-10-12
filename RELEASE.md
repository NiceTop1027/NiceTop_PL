# NiceTop 릴리즈 가이드

## 다운로드

### macOS

#### DMG 설치 파일 (권장)
1. [NiceTop-1.0.0.dmg](https://github.com/NiceTop1027/NiceTop_PL/releases) 다운로드
2. DMG 파일을 열기
3. NiceTop.app을 Applications 폴더로 드래그
4. 터미널에서 `nicetop` 명령어 사용

#### ZIP 바이너리
1. [nicetop-1.0.0-macos.zip](https://github.com/NiceTop1027/NiceTop_PL/releases) 다운로드
2. 압축 해제
3. `./install.sh` 실행

### Linux

```bash
# 소스에서 빌드
git clone https://github.com/NiceTop1027/NiceTop_PL.git
cd NiceTop_PL
make
sudo make install
```

### Windows

WSL (Windows Subsystem for Linux) 사용:
```bash
# WSL에서 Linux 설치 방법 따라하기
```

## 릴리즈 빌드 방법

### 개발자용

```bash
# 릴리즈 패키지 생성
./build_release.sh
```

생성되는 파일:
- `release/nicetop-1.0.0-macos.zip` - 바이너리 패키지
- `release/NiceTop-1.0.0.dmg` - macOS 설치 이미지

### 수동 빌드

```bash
# 최적화 컴파일
make clean
make CFLAGS="-Wall -Wextra -std=c11 -O3 -Isrc"

# 설치
sudo make install
```

## 버전 관리

### 버전 번호 규칙
- **Major.Minor.Patch** (예: 1.0.0)
- Major: 주요 변경사항
- Minor: 새로운 기능 추가
- Patch: 버그 수정

### 릴리즈 체크리스트

- [ ] 모든 테스트 통과
- [ ] 문서 업데이트
- [ ] CHANGELOG.md 작성
- [ ] 버전 번호 업데이트
- [ ] 릴리즈 빌드 생성
- [ ] GitHub Release 생성
- [ ] 릴리즈 노트 작성

## 배포

### GitHub Release

1. 릴리즈 빌드 생성
   ```bash
   ./build_release.sh
   ```

2. GitHub에서 새 릴리즈 생성
   - Tag: v1.0.0
   - Title: NiceTop v1.0.0
   - Description: 릴리즈 노트

3. 파일 업로드
   - nicetop-1.0.0-macos.zip
   - NiceTop-1.0.0.dmg

### Homebrew (향후 계획)

```bash
brew tap nicetop/nicetop
brew install nicetop
```

## 시스템 요구사항

### macOS
- macOS 10.13 (High Sierra) 이상
- Xcode Command Line Tools

### Linux
- GCC 7.0 이상 또는 Clang 5.0 이상
- Make
- glibc 2.17 이상

### Windows
- WSL 2
- Ubuntu 20.04 이상

## 문제 해결

### macOS "앱이 손상되었습니다" 오류

```bash
xattr -cr /Applications/NiceTop.app
```

### 권한 오류

```bash
sudo chmod +x /usr/local/bin/nicetop
```

## 지원

- GitHub Issues: https://github.com/NiceTop1027/NiceTop_PL/issues
- 문서: https://github.com/NiceTop1027/NiceTop_PL
