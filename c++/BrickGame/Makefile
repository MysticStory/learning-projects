CC := g++
CFLAGS := -Wall -Wextra -Werror -std=c++17 -Wpedantic
GCOV_FLAGS := -fprofile-arcs --coverage
BUILD_DIR := build
FILES_TEST := tests/*.cpp
OBJ_DIR := $(BUILD_DIR)/obj
SNAKE_SOURCES := $(wildcard src/brick_game/snake/*.cpp)
TETRIS_SOURCES := $(wildcard src/brick_game/tetris/*.cpp)
SNAKE_OBJECTS := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(notdir $(SNAKE_SOURCES)))
TETRIS_OBJECTS := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(notdir $(TETRIS_SOURCES)))

ifeq ($(shell uname -s), Darwin)
	OPEN_CMD = open
	LIB_FLAGS := $(shell pkg-config --static --cflags --libs gtest ncurses)
else
	OPEN_CMD = xdg-open
	LIB_FLAGS := $(shell pkg-config --static --cflags --libs gtest ncursesw)
endif

.PHONY: all build_dir clean tetris_gui snake_gui tetris_cli snake_cli

all: install

install: tetris_gui tetris_cli snake_cli snake_gui

uninstall:
	rm -rf $(BUILD_DIR)

build_dir:
	mkdir -p $(BUILD_DIR) $(OBJ_DIR)

dvi: clean
	$(OPEN_CMD) documentation/documentation.html

dist: clean
	tar -czvf s21_brick_game.tar.gz *

make_test: tetris.a snake.a
	$(CC) $(CFLAGS)  -g  tests/*.cpp $(BUILD_DIR)/tetris.a $(BUILD_DIR)/snake.a -o s21_test $(LDFLAGS) $(LIB_FLAGS)

make_test_coverage: build_dir clean
	$(CC) $(CFLAGS)  -g --coverage  tests/*.cpp $(SNAKE_SOURCES) $(TETRIS_SOURCES) -o s21_test $(LDFLAGS) $(LIB_FLAGS)
	./s21_test

test: build_dir make_test 
	./s21_test	

valgrind: make_test
	@echo -e "\033[0;32m[  Проверка валидатора  ]\033[0m"
	@CK_FORK=no valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./s21_test
	@grep -E "ERROR SUMMARY:" RESULT_VALGRIND.txt > valgrind_summary.txt
	@if grep -q "ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)" valgrind_summary.txt; then \
		echo -e "\033[0;32m[  VALGRIND PASSED  ]\033[0m"; \
	else \
		echo -e "\033[0;31m[  VALGRIND FAILED  ]\033[0m"; \
		cat valgrind_summary.txt; \
		cat RESULT_VALGRIND.txt; \
	fi

leaks: $(TEST_TARGET)
	@echo -e "\033[0;32m[  Проверка утечек памяти  ]\033[0m"
	@leaks -atExit -- ./s21_test

gcov_report: make_test_coverage
	@mkdir -p report
	@echo -e "\033[0;32m[  Проверка покрытия  ]\033[0m"
	@if [ "$(UNAME)" = "Darwin" ]; then \
		lcov -t "$(TEST_TARGET)" -o $(TEST_TARGET).info -c -d . --no-external --keep-going > coverage_output.txt 2>&1; \
		genhtml -o report --ignore-errors=inconsistent $(TEST_TARGET).info >> coverage_output.txt 2>&1; \
	else \
		lcov -t "$(TEST_TARGET)" -o $(TEST_TARGET).info -c -d . --no-external > coverage_output.txt 2>&1; \
		genhtml -o report $(TEST_TARGET).info >> coverage_output.txt 2>&1; \
	fi
	@grep -E 'lines......:|functions..:' coverage_output.txt > coverage_summary.txt
	@cat coverage_summary.txt
	@lines_coverage=$$(grep 'lines......:' coverage_summary.txt | grep -o '[0-9]\+\.[0-9]\+'); \
	functions_coverage=$$(grep 'functions..:' coverage_summary.txt | grep -o '[0-9]\+\.[0-9]\+'); \
	if awk "BEGIN {exit !($$lines_coverage > 85.0 && $$functions_coverage > 85.0)}"; then \
		echo -e "\033[0;32m[  PASSED  ]\033[0m"; \
	else \
		echo -e "\033[0;31m[  FAILED  ]\033[0m"; \
	fi
	@echo "Открытие отчета покрытия кода..."
	$(OPEN_CMD) ./report/index.html


clean: 
	rm -rf s21_brick_game.tar.gz report
	rm -rf s21_test valgrind_summary.txt RESULT_VALGRIND.txt
	rm -f  *.gcda *.gcno *.gcov $(TEST_TARGET).info
	rm -f coverage_output.txt coverage_summary.txt 

clean_all: clean uninstall

$(OBJ_DIR)/%.o: src/brick_game/snake/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS)  -c $< -o $@

$(OBJ_DIR)/%.o: src/brick_game/tetris/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS)  -c $< -o $@

tetris.a: $(TETRIS_OBJECTS)
	ar rc $(BUILD_DIR)/tetris.a $(TETRIS_OBJECTS)
	ranlib $(BUILD_DIR)/tetris.a
	rm -rf $(OBJ_DIR)/*.o

snake.a: $(SNAKE_OBJECTS)
	ar rc $(BUILD_DIR)/snake.a $(SNAKE_OBJECTS)
	ranlib $(BUILD_DIR)/snake.a
	rm -rf $(OBJ_DIR)/*.o

tetris_gui: build_dir
	cmake -B build -S src/gui/desktop/ -DTETRIS=1
	cmake --build build
	rm -rf $(BUILD_DIR)/Makefile $(BUILD_DIR)/CMake* $(BUILD_DIR)/cmake* $(BUILD_DIR)/*_autogen

snake_gui: build_dir
	cmake -B build -S src/gui/desktop/ -DSNAKE=1
	cmake --build build
	rm -rf $(BUILD_DIR)/Makefile $(BUILD_DIR)/CMake* $(BUILD_DIR)/cmake* $(BUILD_DIR)/*_autogen

tetris_cli: tetris.a
	$(CC) $(CFLAGS) src/main_cli.cpp $(BUILD_DIR)/tetris.a -o $(BUILD_DIR)/game_tetris_cli $(LIB_FLAGS) -DTETRIS=1 

snake_cli: snake.a
	$(CC) $(CFLAGS) src/main_cli.cpp $(BUILD_DIR)/snake.a -o $(BUILD_DIR)/game_snake_cli $(LIB_FLAGS) -DSNAKE=1
