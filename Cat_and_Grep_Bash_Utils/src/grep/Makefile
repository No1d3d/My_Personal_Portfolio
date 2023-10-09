CC=gcc
CFLAGS=-c -Wall -Werror -Wextra
K=
SOURCES=s21_grep.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=s21_grep

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(K) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) 

rebuild: clean all
