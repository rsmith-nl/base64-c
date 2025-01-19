// file: base64test.c
// vim:fileencoding=utf-8:ft=c:tabstop=2
//
// Copyright © 2025 R.F. Smith <rsmith@xs4all.nl>
// SPDX-License-Identifier: MIT
// Created: 2025-01-18 20:25:21 +0100
// Last modified: 2025-01-19T18:38:08+0100

#include "base64.h"
#include <stdio.h>
#include <string.h>

#define BOLD_WHITE "\033[1;37m"
#define CYAN "\033[0;36m"
#define GREEN "\033[0;32m"
#define PURPLE "\033[0;35m"
#define BOLD_RED "\033[1;31m"
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define BOLD_YELLOW "\033[1;33m"
#define RESET "\033[0m"  // No Color

// Test for b64encode and b64decode.
int main(void)
{
  const char *in[5] =  {
    "This is a test",
    "foo",
    "Hello",
    "Testing, testing 1, 2, 3.",
    "Abacadabra"
  };
  const char *expected[5] = {
    "VGhpcyBpcyBhIHRlc3Q=",
    "Zm9v",
    "SGVsbG8=",
    "VGVzdGluZywgdGVzdGluZyAxLCAyLCAzLg==",
    "QWJhY2FkYWJyYQ=="
  };
  for (int32_t j = 0; j < 5; j++) {
    char out[64] = {0};
    b64encode(in[j], strlen(in[j]), out, 63);
    if (strcmp(out, expected[j]) == 0) {
      printf(GREEN"PASSED:"RESET" b64encode(\"%s\") == \"%s\"\n", in[j], out);
    } else {
      printf(RED"FAILED:"RESET" b64encode(\"%s\") != \"%s\"\n", in[j], out);
    }
  }
  puts("-----");
  for (int32_t j = 0; j < 5; j++) {
    char out[64] = {0};
    b64decode(expected[j], strlen(expected[j]), out, 63);
    if (strcmp(out, in[j]) == 0) {
      printf(GREEN"PASSED:"RESET" b64decode(\"%s\") == \"%s\"\n", expected[j], out);
    } else {
      printf(RED"FAILED:"RESET" b64decode(\"%s\") != \"%s\"\n", expected[j], out);
    }
  }
  return 0;
}
