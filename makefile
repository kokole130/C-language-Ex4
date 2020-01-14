CC=gcc
CFLAG=-Wall
TRIEH=trie.h

all: Ex4

Ex4: trie.o 
	$(CC) $(CFLAG) trie.o -Werror -g -o frequency

trie.o: trie.c $(TRIEH)
	$(CC) $(CFLAG) -c -Werror -g trie.c -o $@

clean: 
	rm *.o frequency

.PHONY: all clean