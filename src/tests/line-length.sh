# Make the file
cd ../..
make
if [[ "$?" -ne 0 ]]; then
	echo "Program failed to make";
	return -1;
fi;

bin/lexer >/dev/null 2>&1 <<EOF
1
2
mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
EOF
if [[ "$?" -ne 0 ]]; then
	echo "Program rejects valid line lengths.";
fi;
bin/lexer >/dev/null 2>&1 <<EOF
1
2
mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm
EOF
if [[ "$?" -eq 0 ]]; then
	echo "Program accepts invalid line lengths.";
fi;
