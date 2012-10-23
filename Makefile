all:
	gcc -Wall -g -std=c99 src/*.c -o bin/lexer

clean:
	rm -f bin/*

report:
	cd bin
	latex ../report.tex > /dev/null
	latex ../report.tex > /dev/null
	latex ../report.tex > /dev/null
	pdflatex ../report.tex > /dev/null
	cd ..
