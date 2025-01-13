// file: base64.c
// vim:fileencoding=utf-8:ft=c:tabstop=2
//
// Copyright © 2025 R.F. Smith <rsmith@xs4all.nl>
// SPDX-License-Identifier: MIT
// Created: 2025-01-13 21:22:40 +0100
// Last modified: 2025-01-13T21:48:21+0100

#include <stdint.h>
#include <string.h>  // memcpy

int b64encode(char *in, uint32_t inlen, char *out, uint32_t outlen)
{
    int xlen = 3 - (inlen % 3);
    if (xlen == 3) {
      xlen = 0;
    }
    xlen += inlen;
    unsigned char buf[xlen];
    memset(buf, '=', xlen);
    memcpy(buf, in, inlen);
    const uint32_t k[4] = {0xfc0000, 0x3f000, 0xfc0, 0x3f};
    for (int32_t j = 0; j < xlen; j+=3) {
      uint32_t t = (buf[j]<<16)|(buf[j+1]<<8)|(buf[j+2]);
      *out++ = (t&0xfc0000)>>18;
      *out++ = (t&0x3f000)>>12;
      *out++ = (t&0xfc0)>>6;
      *out++ = t&0x3f;
      // TODO
    }

    return 0;
}

