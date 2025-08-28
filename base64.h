// file: base64.h
// vim:fileencoding=utf-8:ft=c:tabstop=2
// This is free and unencumbered software released into the public domain.
//
// Author: R.F. Smith <rsmith@xs4all.nl>
// SPDX-License-Identifier: Unlicense
// Created: 2025-01-18 20:22:18 +0100
// Last modified: 2025-08-29T00:26:50+0200

#pragma once

#include <stdint.h>

extern void b64encode(const char *in, uint32_t inlen, char *out, uint32_t outlen);
extern int b64decode(const char *in, uint32_t inlen, char *out, uint32_t outlen);
