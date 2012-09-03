all:
	gcc src/*.c -o bin/lexer

bin/lexer.o: src/lexer.c
	gcc -c src/lexer.c -o bin/lexer.o

bin/machines.c: src/machines.c
	gcc -c src/machines.c -o bin/machines.o

clean:
	rm -f bin/*
