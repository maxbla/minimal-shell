CC=gcc
CFLAGS=-ansi -std=c99 -Wall -g
POSIXFLAGS=-D_POSIX_C_SOURCE=200112L
RM=rm
RMFLAGS = -f

all: msh

msh: msh.c
	$(CC) $(CFLAGS) msh.c -o msh.o $(POSIXFLAGS)
clean:
	$(RM) $(RMFLAGS) msh.o
