// file: base64.c
// vim:fileencoding=utf-8:ft=c:tabstop=2
//
// Copyright © 2025 R.F. Smith <rsmith@xs4all.nl>
// SPDX-License-Identifier: MIT
// Created: 2025-01-13 21:22:40 +0100
// Last modified: 2025-01-14T22:41:51+0100

#include <stdio.h>
#include <stdint.h>
#include <string.h>  // memcpy

const char B64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                   "abcdefghijklmnopqrstuvwxyz"
                   "0123456789+/";

void b64encode(char *in, uint32_t inlen, char *out, uint32_t outlen)
{
    uint32_t xlen = 3 - (inlen % 3), after;
    if (xlen == 3) {
      xlen = 0;
    }
    after = xlen;
    xlen += inlen;
    unsigned char buf[xlen];
    memset(buf, 0, xlen);
    memset(out, 0, outlen);
    memcpy(buf, in, inlen);
    char *ix = out;
    for (int32_t j = 0, olen = 0; j < xlen; j+=3, olen+=4) {
      unsigned char obuf[4] = {0};
      uint32_t t = (buf[j]<<16)|(buf[j+1]<<8)|(buf[j+2]);
      obuf[0] = B64[(t&0xfc0000)>>18];
      obuf[1] = B64[(t&0x3f000)>>12];
      obuf[2] = B64[(t&0xfc0)>>6];
      obuf[3] = B64[t&0x3f];
      if (olen <= outlen - 4) {
        memcpy(ix, obuf, 4);
        ix += 4;
      }
    }
    uint32_t offs = strlen(out);
    switch (after) {
      case 1:
        out[offs-1] = '=';
        break;
      case 2:
        out[offs-2] = '=';
        out[offs-1] = '=';
        break;
    };
}

// Test for b64encode.
int main(int argc, char *argv[]) {
  char *in[5] =  {
    "This is a test",
    "foo",
    "Hello",
    "Testing, testing 1, 2, 3.",
    "Abacadabra"
  };
  char *expected[5] = {
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
      printf("PASSED: b64encode(\"%s\") == \"%s\"\n", in[j], expected[j]);
    }
    //printf("expected : %s\n", expected[j]);
    //printf("b64encode: %s\n", out);
  }
  return 0;
}
