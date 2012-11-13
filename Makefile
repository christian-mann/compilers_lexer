all: code

code:
	gcc -Wall -g -std=c99 src/*.c -o bin/lexer

clean:
	rm -f bin/*
	rm -f report.aux report.log report.out report.pdf report.toc
	rm -f src/tests/*.sym src/tests/*.lst src/tests/*.tok

report: tests graphs
	pdflatex report.tex
	pdflatex report.tex

tests: code
	for f in src/tests/*.pas; do \
		echo $$f; \
		f=`basename $$f .pas`; \
		bin/lexer -r data/reserved-words.txt -l src/tests/$$f.lst -t /tmp/tok -s src/tests/$$f.sym src/tests/$$f.pas; \
		cat /tmp/tok | column -t > src/tests/$$f.tok; \
	done;

graphs:
	for f in doc/*.dot; do \
		echo $$f; \
		f=`basename $$f .dot`; \
		dot -Tpng doc/$$f.dot > doc/$$f.png; \
	done;
