CFLAGS=-std=c89 -Wall -Wextra -Werror -Wshadow -Wconversion

all:
	${CC} ${CFLAGS} src/main.c -o build/ice

.PHONY: all
