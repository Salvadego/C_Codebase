#include <stdio.h>

#include "base/platform.h"

int main(void) {
        printf("cl       = %d\n", BASE_COMPILER_CLANG);
        printf("gcc      = %d\n", BASE_COMPILER_GCC);
        printf("msvc     = %d\n", BASE_COMPILER_MSVC);
        printf("unknown  = %d\n", BASE_COMPILER_UNKNOWN);

        printf("win      = %d\n", BASE_OS_WINDOWS);
        printf("macos    = %d\n", BASE_OS_MACOS);
        printf("ios      = %d\n", BASE_OS_IOS);
        printf("linux    = %d\n", BASE_OS_LINUX);
        printf("freebsd  = %d\n", BASE_OS_FREEBSD);
        printf("netbsd   = %d\n", BASE_OS_NETBSD);
        printf("openbsd  = %d\n", BASE_OS_OPENBSD);
        printf("illumos  = %d\n", BASE_OS_ILLUMOS);
        printf("unix     = %d\n", BASE_OS_UNIX);
        printf("unknown  = %d\n", BASE_OS_UNKNOWN);

        printf("x86_64   = %d\n", BASE_ARCH_X86_64);
        printf("x86_32   = %d\n", BASE_ARCH_X86_32);
        printf("arm64    = %d\n", BASE_ARCH_ARM64);
        printf("arm32    = %d\n", BASE_ARCH_ARM32);
}
