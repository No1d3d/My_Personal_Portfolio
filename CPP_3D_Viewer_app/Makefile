TARGET = s21_3D_VIEWER_V_2.0.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c++17 -lstdc++
TEST_FLAGS = -pthread
TEST_TARGET = containers_test_exe
INCPATH       = -I ../Project -I. -I /usr/local/Qt-6.6.2/include -I /usr/local/Qt-6.6.2/include/QtOpenGLWidgets -I /usr/local/Qt-6.6.2/include/QtOpenGL -I /usr/local/Qt-6.6.2/include/QtWidgets -I /usr/local/Qt-6.6.2/include/QtGui -I /usr/local/Qt-6.6.2/include/QtCore -I. -I /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/System/Library/Frameworks/OpenGL.framework/Headers -I /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/System/Library/Frameworks/AGL.framework/Headers -I. -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/System/Library/Frameworks/OpenGL.framework/Headers -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX13.3.sdk/System/Library/Frameworks/AGL.framework/Headers -I/usr/local/Qt-6.6.2/mkspecs/macx-clang
#QMAKE         = /usr/local/Qt-6.6.2/bin/qmake6

all: install

install:
	mkdir build
	cd Project && /usr/local/Qt-6.6.2/bin/qmake6 && make && make clean && rm Makefile
	mv Project/3d-2ver.app ./build

uninstall:
	rm -rf build

dist: uninstall install
	tar -cvzf ./build/3d-2ver.app ./build/3d-2ver.app

dvi:
	open ../README_RUS.md


test:
	cd Project/tests/tests && /usr/local/Qt-6.6.2/bin/qmake6 && make && make clean && rm Makefile
	./Project/tests/tests/tests
	

leaks:
	leaks --quiet --atExit -- ./Project/tests/tests/tests


check_style:
	@find . \( -name '*.h' -o -name '*.cpp' \) -print0 | xargs -0 clang-format -i -style=Google
	@find . \( -name '*.h' -o -name '*.cpp' \) -print0 | xargs -0 clang-format -n -style=Google

clean:
	rm -rf Project/tests/tests/tests
	@rm -rf *.o *.a *.out *.log *.gcno *.gcda *.html *.css

