base64 encoding/decoding for C
##############################

:date: 2025-01-13
:tags: C programming, base64, public domain
:author: Roland Smith

.. Last modified: 2026-05-10T13:20:58+0200
.. vim:spelllang=en

Introduction
============

This code was inspired by the Python ``base64`` module.
That is, to provide base64 encoding and decoding.


No AI policy
============

This code is by a human and for humans.
"AI" / LLM-generated rewrites and additions are not welcome.


Implementation
==============

Both encoding and decoding read from and write to ``char *`` buffers with
caller provided lengths.

The only external functions it uses are ``memset``, ``memcpy`` from ISO/IEC
9899:1990 (“ISO C90”) and ``strnlen`` from IEEE Std 1003.1-2008 (“POSIX.1”).


Usage
=====

Just copy the source files (``base64.h``, ``base64.c``) in to your project.

Use ``make b64test`` to compile the test program.
The expected base64 encoded strings were generated with Python.
