# file: Makefile
# vim:fileencoding=utf-8:ft=make
#
# Author: R.F. Smith <rsmith@xs4all.nl>
# Created: 2025-01-14T21:43:09+0100
# Last modified: 2025-01-14T21:47:05+0100

all: base64test

CFLAGS=-Os -pipe

base64test: base64.o
	$(CC) -o base64test base64.o

.PHONY: clean
clean:
	rm -f *.o base64test
