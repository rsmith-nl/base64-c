# file: Makefile
# vim:fileencoding=utf-8:ft=make
#
# Author: R.F. Smith <rsmith@xs4all.nl>
# Created: 2025-01-14T21:43:09+0100
# Last modified: 2026-02-22T01:38:27+0100

all: b64test

CFLAGS = -pipe -std=c11 -g3 -Wall -Wextra -Wstrict-prototypes -Wpedantic \
                -Wshadow -Wmissing-field-initializers -Wpointer-arith

SRCS = b64test.c base64.c

b64test: $(SRCS)  ## Compile test program (default)
	$(CC) $(CFLAGS) -o b64test  $(SRCS)

.PHONY: style
style:  ## Reformat source code using astyle.
	astyle -n *.c *.h

.PHONY: tidy
tidy:  ## Run static code checker clang-tidy.
	 clang-tidy19 --use-color --quiet *.c *.h --

.PHONY: clean
clean:  ## Remove generated files
	rm -f *.o b64test

.PHONY: help
help:  ## List available commands
	@echo "make targets:"
	@sed -n -e '/##/s/:.*\#\#/\t/p' Makefile
	@echo
