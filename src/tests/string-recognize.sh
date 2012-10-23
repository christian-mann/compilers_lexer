
# We will need machines.c, machines.h
mkdir -p /tmp/testing;
cp ../machines.c ../machines.h /tmp/testing;

cd /tmp/testing;
cat > test.c <<EOF
#include<stdio.h>
#include "machines.h"

int main() {
	char* str = " ";
	printf("%d", WS(str) - str);
	return 0;
}
EOF

gcc test.c machines.c -o ./a.out > /dev/null;
result=`./a.out`;
if [ "$result" -eq 1 ]; then
	echo "Test passed!"
else
	echo "Test failed."
fi;

rm -r /tmp/testing
