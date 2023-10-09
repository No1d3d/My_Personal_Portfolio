CC=gcc
CFLAGS=-c -Wall -Werror -Wextra -std=c11
K=
SOURCES=s21_cat.c s21_cat_f.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=s21_cat

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(K) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) 

rebuild: clean all
