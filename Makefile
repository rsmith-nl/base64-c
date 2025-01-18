# file: Makefile
# vim:fileencoding=utf-8:ft=make
#
# Author: R.F. Smith <rsmith@xs4all.nl>
# Created: 2025-01-14T21:43:09+0100
# Last modified: 2025-01-18T21:05:45+0100

all: base64test

CFLAGS=-Os
CFLAGS += -std=c11 -march=native -pipe -ffast-math
CFLAGS += -Wall -Wextra -Wshadow -Wpointer-arith -Wstrict-prototypes

base64test: base64test.o base64.o
	$(CC) -o base64test $>

.PHONY: clean
clean:
	rm -f *.o base64test
