# Makefile

CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lreadline
SRC_DIR = src
INCLUDE_DIR = src

all: myshell

myshell: main.o signal.o
	$(CC) $(CFLAGS) -o myshell main.o signal.o $(LDFLAGS)

main.o: $(SRC_DIR)/main.c $(INCLUDE_DIR)/shell.h
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -c $(SRC_DIR)/main.c -o main.o

signal.o: $(SRC_DIR)/signal.c $(INCLUDE_DIR)/shell.h
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -c $(SRC_DIR)/signal.c -o signal.o

clean:
	rm -f myshell *.o
