all: code

code:
	gcc -Wall -g -std=c99 src/*.c -o bin/lexer

clean:
	rm -f bin/*

report: tests
	pdflatex report.tex
	pdflatex report.tex

tests: code
	for f in src/tests/*.psc; do \
		echo $$f; \
		f=`basename $$f .psc`; \
		bin/lexer -r data/reserved-words.txt -l src/tests/$$f.lst -t /tmp/tok -s src/tests/$$f.sym src/tests/$$f.psc; \
		cat /tmp/tok | column -t > src/tests/$$f.tok; \
	done;
