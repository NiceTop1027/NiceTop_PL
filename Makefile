CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2 -Isrc
TARGET = nicetop
SRC_DIR = src
SOURCES = $(SRC_DIR)/main.c $(SRC_DIR)/lexer.c $(SRC_DIR)/value.c $(SRC_DIR)/interpreter.c
OBJECTS = $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "✓ nicetop 컴파일 완료!"
	@echo "사용법: ./nicetop <파일.nt>"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)
	@echo "✓ 정리 완료"

install: $(TARGET)
	@echo "nicetop 설치 중..."
	@if [ -w /usr/local/bin ]; then \
		cp $(TARGET) /usr/local/bin/; \
		echo "✓ nicetop이 /usr/local/bin에 설치되었습니다"; \
	else \
		echo "권한이 필요합니다. 'sudo make install'을 실행하세요"; \
	fi

test: $(TARGET)
	@echo "=== 테스트 시작 ==="
	@echo "\n[1] Hello World:"
	@./$(TARGET) examples/hello.nt
	@echo "\n[2] Variables:"
	@./$(TARGET) examples/variables.nt
	@echo "\n[3] Procedures:"
	@./$(TARGET) examples/procedures.nt
	@echo "\n=== 테스트 완료 ==="

.PHONY: all clean install test
