#include <stdio.h>

#include "base/base.h"

i32 main(void) {
        OperatingSystem os_fromContext = OperatingSystemFromContext();
        printf("%s\n", OperatingSystemToString(os_fromContext));

        Architecture arch = ArchitectureFromContext();
        printf("%s\n", ArchitectureToString(arch));

        // Get the current date
}
