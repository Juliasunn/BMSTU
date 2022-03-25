#CFLAGS := -g
FILE_O := $(subst .c,.o,$(wildcard src/*.c))
HEADERS_DIR := /

app.exe:  main.o directory.o special_print.o
	gcc -o app.exe main.o directory.o special_print.o

%.o: %.c
	gcc -c $^


