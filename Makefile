# vim:fileencoding=utf-8:ft=make
.MAKEFLAGS: -j C

all: b64test single_header/base64.h

CFLAGS = -pipe -std=c11 -g3 -Wall -Wextra -Wstrict-prototypes -Wpedantic \
                -Wshadow -Wmissing-field-initializers -Wpointer-arith

SRCS = b64test.c base64.c

b64test: $(SRCS) base64.h  ## Compile test program (default)
	$(CC) $(CFLAGS) -o b64test $(SRCS)

single_header/base64.h: base64.c base64.h  ## Build single header library (POSIX only).
	cp base64.h single_header/base64.h
	echo "" >>single_header/base64.h
	echo "#ifdef BASE64_IMPLEMENTATION" >>single_header/base64.h
	tail -n +11 base64.c >>single_header/base64.h
	echo "" >>single_header/base64.h
	echo "#endif // BASE64_IMPLEMENTATION" >>single_header/base64.h

.PHONY: style
style:  ## Reformat source code using astyle.
	astyle -n *.c *.h

.PHONY: tidy
tidy:  ## Run static code checker clang-tidy.
	 clang-tidy19 --use-color --quiet *.c *.h --

.PHONY: clean
clean:  ## Remove generated files
	rm -f *.o b64test b64test.exe single_header/base64.h

.PHONY: help
help:  ## List available commands
	@echo "make targets:"
	@sed -n -e '/##/s/:.*\#\#/\t/p' Makefile
	@echo
