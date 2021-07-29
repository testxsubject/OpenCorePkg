/** @file
  Generic code for compiler intrinsics.

  Copyright (c) 2020, vit9696. All rights reserved.
  SPDX-License-Identifier: BSD-3-Clause
**/

#include <Library/BaseLib.h>

GLOBAL_REMOVE_IF_UNREFERENCED BOOLEAN gOcCompilerIntrinsicsLib;

#if defined(MDE_CPU_IA32) && defined(__clang__) && defined(__apple_build_version__) && __apple_build_version__ < 11000000

/**
  Divides a 64-bit unsigned integer by a 64-bit unsigned integer and generates
  a 64-bit unsigned result.

  This function is generated by older clang compilers, like ones from Xcode 10.1,
  when using overflow builtins from OcGuardLib. The issue is fixed in Xcode 11.

  @param  Dividend  A 64-bit unsigned value.
  @param  Divisor   A 64-bit unsigned value.

  @return Dividend / Divisor.
**/
UINT64
__udivdi3 (
  IN UINT64  Dividend,
  IN UINT64  Divisor
  )
{
  return DivU64x64Remainder (Dividend, Divisor, NULL);
}

#endif

typedef UINTN size_t;

void *
memset (
  void   *Buffer,
  int    Value,
  size_t Length
  )
{
  unsigned char *d = Buffer;

  while (Length--)
    *d++ = (unsigned char) Value;

  return Buffer;
}

#if defined(_MSC_EXTENSIONS) && !defined(__clang__) && !defined(__GNUC__)

void *
memcpy (
  void         *DestinationBuffer,
  const void   *SourceBuffer,
  size_t       Length
  );

#pragma intrinsic(memcpy)
#pragma function(memcpy)
void *
memcpy (
  void         *DestinationBuffer,
  const void   *SourceBuffer,
  size_t       Length
  )
{
  unsigned char *d = DestinationBuffer;
  unsigned char const *s = SourceBuffer;

  while (Length--)
    *d++ = *s++;

  return DestinationBuffer;
}

#endif
