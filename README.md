# Minimal-Shell
A minimal interactive shell written in 100 lines of c

## Commands
command|description
-------|-----------
`exit`| quits, returning 0
`cd`  | changes directory (builtin)
anything else|searches $(PATH) for command and executes it in a child process

## Dependencies
* GNU Make
* GNU C compiler (or any ansi c99 compatible compiler)
* stdio.h string.h sys/types.h sys/wait.h unistd.h

## Compiling and Running
`make all`

`./msh.o`
