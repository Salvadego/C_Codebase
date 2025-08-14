#include <stdio.h>

#include "base/base.h"

i32 main(void) {
        OperatingSystem os_ = OperatingSystem_Linux;
        printf("%s\n", OperatingSystemToString(os_));

        Architecture arch = Architecture_X86_64;
        printf("%s\n", ArchitectureToString(arch));

        Month month = Month_January;
        printf("%s\n", MonthToStringShort(month));
        printf("%s\n", MonthToStringLong(month));

        DayOfWeek day = DayOfWeek_Monday;
        printf("%s\n", DayOfWeekToStringShort(day));
        printf("%s\n", DayOfWeekToStringLong(day));
}
