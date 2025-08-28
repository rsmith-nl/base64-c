# file: Makefile
# vim:fileencoding=utf-8:ft=make
#
# Author: R.F. Smith <rsmith@xs4all.nl>
# Created: 2025-01-14T21:43:09+0100
# Last modified: 2025-08-29T00:31:33+0200

all: base64test

CFLAGS = -pipe -std=c11 -fPIC -g3 -Wall -Wextra -Wstrict-prototypes -Wpedantic \
                -Wshadow-all -Wmissing-field-initializers -Wpointer-arith \
                -fsanitize=address,undefined

SRCS = base64test.c base64.c

base64test: $(SRCS)
	$(CC) $(CFLAGS) -o base64test  $(SRCS) -fsanitize=address,undefined

.PHONY: style
style:  ## Reformat source code using astyle.
	astyle -n *.c *.h

.PHONY: tidy
tidy:  ## Run static code checker clang-tidy.
	 clang-tidy19 --use-color --quiet *.c *.h --

tags: $(SRCS) *.h  ## Update tags file

.PHONY: clean
clean:
	rm -f *.o base64test
