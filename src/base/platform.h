#pragma once
#include "../defines.h"

#ifndef BASE_PLATFORM_H
#        define BASE_PLATFORM_H

/* ===========================
   Compiler Detection
   =========================== */
#        if defined(__clang__)
#                define BASE_COMPILER_CLANG true
#        elif defined(__GNUC__) || defined(__GNUG__)
#                define BASE_COMPILER_GCC true
#        elif defined(_MSC_VER)
#                define BASE_COMPILER_MSVC true
#        else
#                define BASE_COMPILER_UNKNOWN true
#        endif

/* ===========================
   OS Detection
   =========================== */
#        if defined(_WIN32) || defined(_WIN64)
#                define BASE_OS_WINDOWS true
#        elif defined(__APPLE__) && defined(__MACH__)
#                define BASE_OS_MACOS true
#                include <TargetConditionals.h>
#                if TARGET_OS_IPHONE || TARGET_OS_SIMULATOR
#                        define BASE_OS_IOS true
#                endif
#        elif defined(__linux__)
#                define BASE_OS_LINUX 1
#        elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
#                define BASE_OS_FREEBSD 1
#        elif defined(__NetBSD__)
#                define BASE_OS_NETBSD 1
#        elif defined(__OpenBSD__)
#                define BASE_OS_OPENBSD 1
#        elif defined(__sun) && defined(__SVR4)
#                define BASE_OS_ILLUMOS 1 /* illumos or Solaris */
#        elif defined(__unix__) || defined(__unix)
#                define BASE_OS_UNIX 1 /* Fallback generic Unix */
#        else
#                define BASE_OS_UNKNOWN 1
#        endif

/* ===========================
   Architecture Detection
   =========================== */
#        if defined(_M_X64) || defined(__x86_64__)
#                define BASE_ARCH_X86_64 true
#        elif defined(_M_IX86) || defined(__i386__)
#                define BASE_ARCH_X86_32 true
#        elif defined(__aarch64__) || defined(_M_ARM64)
#                define BASE_ARCH_ARM64 true
#        elif defined(__arm__) || defined(_M_ARM)
#                define BASE_ARCH_ARM32 true
#        else
#                define BASE_ARCH_UNKNOWN true
#        endif

// Initializes all to false.
#        if !defined(BASE_COMPILER_CLANG)
#                define BASE_COMPILER_CLANG false
#        endif
#        if !defined(BASE_COMPILER_GCC)
#                define BASE_COMPILER_GCC false
#        endif
#        if !defined(BASE_COMPILER_MSVC)
#                define BASE_COMPILER_MSVC false
#        endif
#        if !defined(BASE_COMPILER_UNKNOWN)
#                define BASE_COMPILER_UNKNOWN false
#        endif

#        if !defined(BASE_OS_WINDOWS)
#                define BASE_OS_WINDOWS false
#        endif
#        if !defined(BASE_OS_MACOS)
#                define BASE_OS_MACOS false
#        endif
#        if !defined(BASE_OS_IOS)
#                define BASE_OS_IOS false
#        endif
#        if !defined(BASE_OS_LINUX)
#                define BASE_OS_LINUX false
#        endif
#        if !defined(BASE_OS_FREEBSD)
#                define BASE_OS_FREEBSD false
#        endif
#        if !defined(BASE_OS_NETBSD)
#                define BASE_OS_NETBSD false
#        endif
#        if !defined(BASE_OS_OPENBSD)
#                define BASE_OS_OPENBSD false
#        endif
#        if !defined(BASE_OS_ILLUMOS)
#                define BASE_OS_ILLUMOS false
#        endif
#        if !defined(BASE_OS_UNIX)
#                define BASE_OS_UNIX false
#        endif
#        if !defined(BASE_OS_UNKNOWN)
#                define BASE_OS_UNKNOWN false
#        endif

#        if !defined(BASE_ARCH_X86_64)
#                define BASE_ARCH_X86_64 false
#        endif
#        if !defined(BASE_ARCH_X86_32)
#                define BASE_ARCH_X86_32 false
#        endif
#        if !defined(BASE_ARCH_ARM64)
#                define BASE_ARCH_ARM64 false
#        endif
#        if !defined(BASE_ARCH_ARM32)
#                define BASE_ARCH_ARM32 false
#        endif
#        if !defined(BASE_ARCH_UNKNOWN)
#                define BASE_ARCH_UNKNOWN false
#        endif

#endif /* BASE_PLATFORM_H */
