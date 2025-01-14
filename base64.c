// file: base64.c
// vim:fileencoding=utf-8:ft=c:tabstop=2
//
// Copyright © 2025 R.F. Smith <rsmith@xs4all.nl>
// SPDX-License-Identifier: MIT
// Created: 2025-01-13 21:22:40 +0100
// Last modified: 2025-01-14T21:48:32+0100

#include <stdio.h>
#include <stdint.h>
#include <string.h>  // memcpy

const char B64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                   "abcdefghijklmnopqrstuvwxyz"
                   "0123456789+/";

int b64encode(char *in, uint32_t inlen, char *out, uint32_t outlen)
{
    uint32_t xlen = 3 - (inlen % 3);
    if (xlen == 3) {
      xlen = 0;
    }
    xlen += inlen;
    unsigned char buf[xlen];
    memset(buf, '=', xlen);
    memcpy(buf, in, inlen);
    for (int32_t j = 0, olen = 0; j < xlen; j+=3, olen+=4) {
      unsigned char obuf[4] = {0};
      uint32_t t = (buf[j]<<16)|(buf[j+1]<<8)|(buf[j+2]);
      obuf[0] = B64[(t&0xfc0000)>>18];
      obuf[1] = B64[(t&0x3f000)>>12];
      obuf[2] = B64[(t&0xfc0)>>6];
      obuf[3] = B64[t&0x3f];
      if (olen <= outlen - 4) {
        memcpy(out, obuf, 4);
        out += 4;
      }
      //else {
      //  uint32_t rem = olen - outlen;
      //  memcpy(out, obuf, rem);
      //}
    }
    return 0;
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
    printf("expected : %s\n", expected[j]);
    printf("b64encode: %s\n", out);
    puts("--");
  }
  return 0;
}
