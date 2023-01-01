CC = gcc
CFLAG = -Wall -Wextra -Werror -std=c11
CHECKFLAGS = -lcheck -lsubunit -coverage -pthread -lrt
APP = build/s21_calc.app

all: install s21_calc.a test
build:
	mkdir build
	cd ./build/ && qmake ../ && make && mv smart_calc s21_calc.app

install: build
	@mkdir $(HOME)/Desktop/SmartCalc_v1.0/
	@cp -rf $(APP) $(HOME)/Desktop/SmartCalc_v1.0/
	make clean

uninstall:
	@rm -rf build
	@rm -rf $(HOME)/Desktop/SmartCalc_v1.0/

dvi:
	open dvi.html

check:
	checkmk polish_note__tests.check > s21_test.c


dist:
	rm -rf Archive_SmartCalc_v1.0/
	mkdir Archive_SmartCalc_v1.0/
	mkdir Archive_SmartCalc_v1.0/src
	cp Makefile *.c *.h *.pro *.cpp *.ui *.user Archive_SmartCalc_v1.0/src/
	tar cvzf Archive_SmartCalc_v1.0.tgz Archive_SmartCalc_v1.0/
	mv Archive_SmartCalc_v1.0.tgz $(HOME)/Desktop/
	rm -rf Archive_SmartCalc_v1.0/

s21_calc.a:
	$(CC) $(CFLAG) -c s21_smart_calc.c
	@ar rcs s21_calc.a s21_smart_calc.o

test: check
	$(CC) $(CFLAG) *.c $(CHECKFLAGS) -lm
	./a.out

gcov_report: test
	lcov -t "s21_test" -o s21_test.info -c -d .
	genhtml -o report s21_test.info
	open ./report/index.html

clean:
	rm -rf *.o *.a *.out 
	rm -rf *.gcda *.gcno *.info
	rm -rf s21_test report
	rm -rf s21_calc s21_test s21_test.c
	rm -rf ./build*

lint:
	clang-format -i *.c *.cpp *.h 

rebuild: clean all