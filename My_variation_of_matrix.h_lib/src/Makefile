ifeq ($(shell uname -s), Linux)	
	LFLAG += -lpthread -lrt -lm -lsubunit
endif

all: s21_matrix.a

s21_matrix.a:
	gcc -Wall -Wextra -Werror -std=c11 -D_GNU_SOURCE -g -c s21_*.c
	ar rc s21_matrix.a s21_*.o
	ranlib s21_matrix.a

test: clean s21_matrix.a
	gcc -Wall -Wextra -Werror -std=c11 -D_GNU_SOURCE -g -c tests/*.c
	gcc -Wall -Wextra -Werror -std=c11 -D_GNU_SOURCE -g -o test *_test.o test_main.o s21_matrix.a -lcheck $(LFLAG)
	rm -rf *.o *.a
	./test

leaks: test
	leaks -atExit -- ./test

valgrind: test
	valgrind --leak-check=full --track-origins=yes ./test

gcov_report: clean 
	gcc s21_*.c tests/*.c -o gcov_report --coverage -lcheck $(LFLAG)
	./gcov_report
	rm -f *test*.gc*
	gcov *.gcno
	lcov -d . -o gcov_report.info -c
	genhtml -o report gcov_report.info
	open report/index.html

style:
	clang-format -style=Google -i *.c *.h tests/*.c tests/*.h
	clang-format -style=Google -n *.c *.h tests/*.c tests/*.h

rebuild: clean all

clean:
	rm -f *.gcno *.gcda *.info *.gcov 
	rm -f *.o *.a
	rm -rf report
	rm -f *.out
	rm -f test
	rm -f gcov_report


