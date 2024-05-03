TARGET = s21_containers.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c++20 -lstdc++
TEST_FLAGS = -lgtest -pthread
TEST_TARGET = containers_test_exe

all: test

test:
	@$(CC) $(CFLAGS) tests/*.cpp $(TEST_FLAGS) -o $(TEST_TARGET)
	./$(TEST_TARGET)

leaks:
	@$(CC) $(CFLAGS) tests/*.cpp $(TEST_FLAGS) -o $(TEST_TARGET)
	leaks --atExit -- ./$(TEST_TARGET)

valgrind: clean
	@CK_FORK=no valgrind --vgdb=no --leak-check=full \
	--show-leak-kinds=all --track-origins=yes --log-file="valgrind.log" -v --verbose -q --quiet -s ./$(TEST_TARGET)

check_style:
	@find . \( -name '*.h' -o -name '*.cpp' \) -print0 | xargs -0 clang-format -i -style=Google
	@find . \( -name '*.h' -o -name '*.cpp' \) -print0 | xargs -0 clang-format -n -style=Google

clean:
	@rm -rf *.o *.a *.out *.log *.gcno *.gcda *.html *.css $(TEST_TARGET)
test_ubuntu:
	gcc -Wall -Werror -Wextra   tests/*.cpp  -pthread -o $(TEST_TARGET) -lstdc++ -lgtest -std=c++20 -lm

vg: test_ubuntu
	valgrind  --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./$(TEST_TARGET)

report:
	gcc -Wall -Werror -Wextra --coverage  tests/*.cpp -pthread -o test -lstdc++ -lgtest -std=c++20 -lm
	./$(TEST_TARGET)
	gcovr -o gcov_report.html --html --html-details
