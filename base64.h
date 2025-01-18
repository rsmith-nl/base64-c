// file: base64.h
// vim:fileencoding=utf-8:ft=cpp:tabstop=2
//
// Copyright © 2025 R.F. Smith <rsmith@xs4all.nl>
// SPDX-License-Identifier: MIT
// Created: 2025-01-18 20:22:18 +0100
// Last modified: 2025-01-18T21:12:43+0100

#pragma once

#include <stdint.h>

extern void b64encode(const char *in, uint32_t inlen, char *out, uint32_t outlen);
extern int b64decode(const char *in, uint32_t inlen, char *out, uint32_t outlen);
