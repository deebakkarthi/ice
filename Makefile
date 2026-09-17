CFLAGS=-std=c89 -Wall -pedantic -Wextra -Werror -Wshadow -Wconversion \
       -Wno-unused-variable -Wno-unused-but-set-variable -Wno-unused-parameter
LDFLAGS=-lcurl

all: build/ice

build/ice: build/main.o
	${CC} ${LDFLAGS} $< -o $@

build/main.o: src/main.c
	${CC} ${CFLAGS} -c $< -o $@

.PHONY: all

clean:
	rm -rf build/*
