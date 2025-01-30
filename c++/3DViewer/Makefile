PROJECT_NAME = Viewer3D
FLAGS = -Wall -Wextra -std=c++17 -g
UNAME := $(shell uname -s)
ifeq ($(UNAME),Linux)
	LDFLAGS = -lgtest -lgtest_main -lpthread --coverage
	OPEN-PATH = ./build/$(PROJECT_NAME)
	CXX = g++
	ifneq ($(shell grep -i microsoft /proc/version),)
		OPEN_CMD = open
	else
		OPEN_CMD = xdg-open
	endif
endif
ifeq ($(UNAME),Darwin)
	LDFLAGS = $(shell pkg-config --libs --cflags gtest) -Wno-sign-compare --coverage
	OPEN-PATH = ./build/$(PROJECT_NAME).app/Contents/MacOS/$(PROJECT_NAME)
	CXX = clang++
	OPEN_CMD = open
endif

all: install open

mkdir_build:
	mkdir -p build

build: mkdir_build
	make model.a
	@if [ "$(UNAME)" = "Darwin" ]; then \
		cd build/ && qmake ../src/ && cd ../build && make; \
	else \
		cmake -S ./src/ -B build; \
		cmake --build build; \
	fi

install: build
	
uninstall:
	rm -rf build

open:
	$(OPEN) $(OPEN-PATH)

dist: clean build
	cd build && tar cvzf $(PROJECT_NAME).tgz *

dvi: 
	mkdir -p ./Viewer3DDoc
	texi2any --html --quiet docs/$(PROJECT_NAME).texi -o ./Viewer3DDoc/Viewer3D.html
	$(OPEN_CMD) ./Viewer3DDoc/Viewer3D.html

	
test: clean model_test
	g++ $(FLAGS) Tests/*.cc build/model_test.a -o s21_test  $(LDFLAGS)
	./s21_test

leaks: clean test
	leaks -atExit -- ./s21_test

gcov_report: test
	@mkdir -p report
	@echo -e "\033[0;32m[  Проверка покрытия  ]\033[0m"
	@if [ "$(UNAME)" = "Darwin" ]; then \
		lcov -t "s21_test" -o s21_test.info  -c -d . --no-external --keep-going > coverage_output.txt 2>&1; \
		lcov --extract s21_test.info 'Model/src/FileReader.cpp' 'Geometry/src/TransformMatrix.cpp' -o s21_test.info; \
		genhtml -o report --ignore-errors=inconsistent s21_test.info >> coverage_output.txt 2>&1; \
	else \
		lcov -t "s21_test" -o s21_test.info -c -d . --no-external > coverage_output.txt 2>&1; \
		lcov --extract s21_test.info '*Model/src/FileReader.cpp' '*Geometry/src/TransformMatrix.cpp' -o s21_test.info; \
		genhtml -o report s21_test.info >> coverage_output.txt 2>&1; \
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

model.a: mkdir_build
	$(CXX) $(FLAGS) -c src/Geometry/src/* src/Model/src/*
	ar rcs build/model.a *.o
	ranlib build/model.a 
	rm -rf *.o 

model_test: mkdir_build
	$(CXX) $(FLAGS) -c src/Geometry/src/* src/Model/src/* --coverage
	ar rcs build/model_test.a *.o
	ranlib build/model_test.a 
	rm -rf *.o 

clean:
	rm -rf *.o s21_test *.gcda *.gcno *.info report *.out *.dSYM $(PROJECT_NAME)/.qmake.stash  $(PROJECT_NAME)/$(PROJECT_NAME).pro.user
	rm -rf coverage_output.txt coverage_summary.txt Viewer3DDoc

rebuild: clean all

style:
	clang-format -n -style=google */src/*.cpp */*.cc */include/*.h

format:
	clang-format -i -style=google */src/*.cpp */*.cc */include/*.h
