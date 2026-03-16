// file: base64test.c
// vim:fileencoding=utf-8:ft=c:tabstop=2
// This is free and unencumbered software released into the public domain.
//
// Author: R.F. Smith <rsmith@xs4all.nl>
// SPDX-License-Identifier: Unlicense
// Created: 2025-01-18 20:25:21 +0100
// Last modified: 2026-03-16T23:28:19+0100

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
  const char *in[7] =  {
    "This is a test",
    "foo",
    "Hello",
    "Testing, testing 1, 2, 3.",
    "Abacadabra",
    "ünicóde",
    "Abacadabra",
  };
  const char *expected[7] = {
    "VGhpcyBpcyBhIHRlc3Q=",
    "Zm9v",
    "SGVsbG8=",
    "VGVzdGluZywgdGVzdGluZyAxLCAyLCAzLg==",
    "QWJhY2FkYWJyYQ==",
    "w7xuaWPDs2Rl",
    "QWJhY 2FkYWJyYQ==",
  };
  int failcount = 0;
  puts(PURPLE"Start tests"RESET);
  puts(CYAN"Running tests for b64encode"RESET);
  for (int32_t j = 0; j < 6; j++) {
    char out[64] = {0};
    b64encode(in[j], strlen(in[j]), out, 63);
    if (strcmp(out, expected[j]) == 0) {
      printf(GREEN"PASSED:"RESET" b64encode(\"%s\") == \"%s\"\n", in[j], out);
    } else {
      printf(RED"FAILED:"RESET" b64encode(\"%s\") != \"%s\"\n", in[j], out);
      failcount++;
    }
  }
  puts(CYAN"Running tests for b64decode"RESET);
  for (int32_t j = 0; j < 7; j++) {
    char out[64] = {0};
    b64decode(expected[j], strlen(expected[j]), out, 63);
    if (strcmp(out, in[j]) == 0) {
      printf(GREEN"PASSED:"RESET" b64decode(\"%s\") == \"%s\"\n", expected[j], out);
    } else {
      printf(RED"FAILED:"RESET" b64decode(\"%s\") != \"%s\"\n", expected[j], out);
      failcount++;
    }
  }
  puts(PURPLE"*** Result ***"RESET);
  if (failcount == 0) {
    puts(GREEN"+++ All tests PASSED! +++"RESET);
  } else {
    printf("\033[1;31m--- %d failing tests.---\033[0m\n", failcount);
  }
  return 0;
}
