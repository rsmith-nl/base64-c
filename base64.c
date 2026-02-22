// file: base64.c
// vim:fileencoding=utf-8:ft=c:tabstop=2
// This is free and unencumbered software released into the public domain.
//
// Author: R.F. Smith <rsmith@xs4all.nl>
// SPDX-License-Identifier: Unlicense
// Created: 2025-01-13 21:22:40 +0100
// Last modified: 2026-02-22T01:47:37+0100

#include "base64.h"
#include <string.h>  // for memset, memcpy, strnlen

static const char B64[64] =
  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void b64encode(const char *in, uint32_t inlen, char *out, uint32_t outlen)
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
  for (uint32_t j = 0, olen = 0; j < xlen; j+=3, olen+=4) {
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
  uint32_t offs = strnlen(out, outlen);
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


// In Python:
// invB64 = [B64.index(chr(j)) if chr(j) in B64 else -1 for j in range(128)]
static const char invB64[128] = {
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63,
  52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1,
  -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,
  18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1, -1, 26, 27,
  28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43,
  44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1
};

int b64decode(const char *in, uint32_t inlen, char *out, uint32_t outlen)
{
  int ix = 0;
  uint32_t outcnt = 0;
  unsigned char obuf[5] = {0};
  char *p = out;
  for (uint32_t j = 0; j < inlen; j++) {
    int cur = (unsigned char)in[j];
    if (cur == 61) {
      // Filler
      obuf[ix++] = 0;
    } else if (cur < 0 || invB64[cur] == -1) {
      return -1; // Input contains illegal character
    } else {
      obuf[ix++] = invB64[cur];
    }
    if (ix == 4) {
      uint32_t k = (obuf[0]<<18)|(obuf[1]<<12)|(obuf[2]<<6)|obuf[3];
      memset(obuf, 0, 5);
      ix = 0;
      unsigned char tmp[3] = {(k&0xff0000)>>16, (k&0xff00)>>8, k&0xff};
      for (int32_t q = 0; q < 3; q++) {
        *p++ = tmp[q];
        if (++outcnt >= outlen) {
          return 0;
        }
      }
    }
  }
  return 0;
}
