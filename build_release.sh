#!/bin/bash
# NiceTop 릴리즈 빌드 스크립트
# macOS .dmg 및 바이너리 패키지 생성

set -e

VERSION="1.0.0"
APP_NAME="NiceTop"
BUILD_DIR="build"
RELEASE_DIR="release"

echo "======================================"
echo "  NiceTop 릴리즈 빌드 v${VERSION}"
echo "======================================"
echo ""

# 정리
echo "이전 빌드 정리 중..."
rm -rf "$BUILD_DIR" "$RELEASE_DIR"
mkdir -p "$BUILD_DIR" "$RELEASE_DIR"

# 컴파일 (최적화)
echo "컴파일 중..."
make clean
make CFLAGS="-Wall -Wextra -std=c11 -O3 -Isrc"

echo "✓ 컴파일 완료"
echo ""

# 바이너리 패키지 생성
echo "바이너리 패키지 생성 중..."
BINARY_DIR="$BUILD_DIR/nicetop-${VERSION}-macos"
mkdir -p "$BINARY_DIR/bin"
mkdir -p "$BINARY_DIR/examples"
mkdir -p "$BINARY_DIR/docs"

# 파일 복사
cp nicetop "$BINARY_DIR/bin/"
cp ntpm "$BINARY_DIR/bin/"
cp examples/*.nt "$BINARY_DIR/examples/" 2>/dev/null || true
cp README.md SYNTAX.md LANGUAGE_SPEC.md INSTALL.md "$BINARY_DIR/docs/"

# 설치 스크립트 생성
cat > "$BINARY_DIR/install.sh" << 'EOF'
#!/bin/bash
echo "NiceTop 설치 중..."
sudo cp bin/nicetop /usr/local/bin/
sudo cp bin/ntpm /usr/local/bin/
sudo chmod +x /usr/local/bin/nicetop
sudo chmod +x /usr/local/bin/ntpm
echo "✓ 설치 완료!"
echo ""
echo "사용법: nicetop <파일.nt>"
EOF
chmod +x "$BINARY_DIR/install.sh"

# README 생성
cat > "$BINARY_DIR/README.txt" << EOF
NiceTop 프로그래밍 언어 v${VERSION}
====================================

설치 방법:
  ./install.sh

또는 수동 설치:
  sudo cp bin/nicetop /usr/local/bin/
  sudo cp bin/ntpm /usr/local/bin/

사용법:
  nicetop <파일.nt>
  nicetop  (REPL 모드)

예제:
  nicetop examples/hello.nt

문서:
  docs/README.md
  docs/SYNTAX.md
  docs/LANGUAGE_SPEC.md

GitHub:
  https://github.com/NiceTop1027/NiceTop_PL
EOF

# ZIP 압축
cd "$BUILD_DIR"
zip -r "../$RELEASE_DIR/nicetop-${VERSION}-macos.zip" "nicetop-${VERSION}-macos"
cd ..

echo "✓ 바이너리 패키지 생성 완료"
echo "  → $RELEASE_DIR/nicetop-${VERSION}-macos.zip"
echo ""

# macOS .app 번들 생성
echo "macOS .app 번들 생성 중..."
APP_BUNDLE="$BUILD_DIR/${APP_NAME}.app"
mkdir -p "$APP_BUNDLE/Contents/MacOS"
mkdir -p "$APP_BUNDLE/Contents/Resources"

# 실행 파일 복사
cp nicetop "$APP_BUNDLE/Contents/MacOS/"
cp ntpm "$APP_BUNDLE/Contents/MacOS/"

# Info.plist 생성
cat > "$APP_BUNDLE/Contents/Info.plist" << EOF
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
    <key>CFBundleExecutable</key>
    <string>nicetop</string>
    <key>CFBundleIdentifier</key>
    <string>com.nicetop.nicetop</string>
    <key>CFBundleName</key>
    <string>NiceTop</string>
    <key>CFBundleVersion</key>
    <string>${VERSION}</string>
    <key>CFBundleShortVersionString</key>
    <string>${VERSION}</string>
    <key>CFBundlePackageType</key>
    <string>APPL</string>
    <key>LSMinimumSystemVersion</key>
    <string>10.13</string>
</dict>
</plist>
EOF

echo "✓ .app 번들 생성 완료"
echo ""

# DMG 생성 (macOS만)
if [[ "$OSTYPE" == "darwin"* ]]; then
    echo "DMG 이미지 생성 중..."
    
    DMG_DIR="$BUILD_DIR/dmg"
    mkdir -p "$DMG_DIR"
    
    # .app과 Applications 심볼릭 링크 복사
    cp -R "$APP_BUNDLE" "$DMG_DIR/"
    ln -s /Applications "$DMG_DIR/Applications"
    
    # 예제와 문서 복사
    mkdir -p "$DMG_DIR/Examples"
    mkdir -p "$DMG_DIR/Documentation"
    cp examples/*.nt "$DMG_DIR/Examples/" 2>/dev/null || true
    cp README.md SYNTAX.md LANGUAGE_SPEC.md "$DMG_DIR/Documentation/"
    
    # DMG 생성
    DMG_NAME="NiceTop-${VERSION}.dmg"
    hdiutil create -volname "NiceTop ${VERSION}" \
                   -srcfolder "$DMG_DIR" \
                   -ov -format UDZO \
                   "$RELEASE_DIR/$DMG_NAME"
    
    echo "✓ DMG 생성 완료"
    echo "  → $RELEASE_DIR/$DMG_NAME"
else
    echo "⚠ macOS가 아니므로 DMG 생성을 건너뜁니다."
fi

echo ""
echo "======================================"
echo "  빌드 완료!"
echo "======================================"
echo ""
echo "생성된 파일:"
ls -lh "$RELEASE_DIR"
echo ""
echo "배포 준비 완료!"
