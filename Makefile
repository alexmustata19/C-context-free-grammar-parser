CC = gcc
CFLAGS = -Wall -g

all: build

lexer.c: lexer.lex
	flex --outfile=$@ $<

build: lexer

lexer: lexer.o
	$(CC) $(CFLAGS) -o $@ $^ alfabet.c gramatica.c regula.c set_reguli.c -lfl 

.PHONY: clean

run: build
	./lexer $(arg)

clean:
	rm -f *.o *~ lexer.c lexer