# Makefile

CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lreadline
SRC_DIR = src
INCLUDE_DIR = src

all: myshell

myshell: main.o
	$(CC) $(CFLAGS) -o myshell main.o $(LDFLAGS)

main.o: $(SRC_DIR)/main.c $(INCLUDE_DIR)/shell.h
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -c $(SRC_DIR)/main.c -o main.o

clean:
	rm -f myshell *.o
