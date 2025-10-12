# GitHub Release 만들기 가이드

## 1단계: GitHub 웹사이트 접속

1. https://github.com/NiceTop1027/NiceTop_PL 접속
2. 상단의 **"Releases"** 클릭 (또는 오른쪽 사이드바)
3. **"Create a new release"** 버튼 클릭

## 2단계: 릴리즈 정보 입력

### Tag 설정
- **Choose a tag**: `v1.0.0` 입력
- **Create new tag: v1.0.0 on publish** 선택

### 릴리즈 제목
```
NiceTop v1.0.0 - 첫 공식 릴리즈 🎉
```

### 릴리즈 설명
`RELEASE_NOTES.md` 파일의 내용을 복사하여 붙여넣기

또는 간단히:

```markdown
# NiceTop v1.0.0 - 첫 공식 릴리즈 🎉

C 언어로 구현된 절차지향 프로그래밍 언어

## 주요 기능
- ✨ C 스타일 타입 선언 (nint, nfloat, nstring, nbool)
- ✨ for/while 루프 완벽 지원
- ✨ 함수와 재귀
- ⚡ 네이티브 C 구현으로 빠른 실행

## 설치 방법

### macOS - DMG (권장)
1. NiceTop-1.0.0.dmg 다운로드
2. 더블클릭하여 설치

### 한 줄 설치
\`\`\`bash
curl -sSL https://raw.githubusercontent.com/NiceTop1027/NiceTop_PL/main/install.sh | bash
\`\`\`

## 예제
\`\`\`c
nout("Hello, NiceTop!")

nfor (nint i = 1; i <= 10; i = i + 1) {
    nout(i)
}
\`\`\`

📚 [문서](https://github.com/NiceTop1027/NiceTop_PL)
```

## 3단계: 파일 업로드

**"Attach binaries"** 영역에 다음 파일들을 드래그 앤 드롭:

### 업로드할 파일
```
release/NiceTop-1.0.0.dmg          (39KB)
release/nicetop-1.0.0-macos.zip    (24KB)
```

파일 위치: `/Users/nicetop/Documents/NiceTop_L/release/`

## 4단계: 릴리즈 옵션

- ✅ **Set as the latest release** 체크
- ⬜ **Set as a pre-release** 체크 해제
- ⬜ **Create a discussion** (선택사항)

## 5단계: 발행

**"Publish release"** 버튼 클릭!

## 완료! 🎉

릴리즈가 생성되면:
- https://github.com/NiceTop1027/NiceTop_PL/releases/tag/v1.0.0
- 사용자들이 다운로드 가능
- README의 배지 업데이트 가능

## 추가 작업 (선택사항)

### README에 배지 추가

```markdown
[![Release](https://img.shields.io/github/v/release/NiceTop1027/NiceTop_PL)](https://github.com/NiceTop1027/NiceTop_PL/releases)
[![Downloads](https://img.shields.io/github/downloads/NiceTop1027/NiceTop_PL/total)](https://github.com/NiceTop1027/NiceTop_PL/releases)
```

### 소셜 미디어 공유

릴리즈 링크를 공유하세요!

## 문제 해결

### 파일이 너무 큰 경우
- GitHub는 2GB까지 지원
- 현재 파일들은 매우 작음 (총 63KB)

### 태그 삭제가 필요한 경우
```bash
git tag -d v1.0.0
git push origin :refs/tags/v1.0.0
```

## 다음 릴리즈

버전을 올릴 때:
1. `build_release.sh`에서 VERSION 변경
2. 새로운 릴리즈 빌드
3. 위 과정 반복
