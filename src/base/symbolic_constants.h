
#pragma once

#include "macros.h"
#include "platform.h"
#include "types.h"

enum Axis {
        Axis_X,
        Axis_Y,
        Axis_Z,
        Axis_W,
};

enum Side {
        Side_Min,
        Side_Max,
};

typedef enum OperatingSystem {
        OperatingSystem_Windows,
        OperatingSystem_MacOS,
        OperatingSystem_Linux,
        OperatingSystem_FreeBSD,
        OperatingSystem_NetBSD,
        OperatingSystem_OpenBSD,
        OperatingSystem_Illumos,
        OperatingSystem_Unix,
        OperatingSystem_Unknown,
        OperatingSystem_Count,
} OperatingSystem;

typedef enum Architecture {
        Architecture_X86_64,
        Architecture_X86_32,
        Architecture_ARM64,
        Architecture_ARM32,
        Architecture_Unknown,
        Architecture_Count,
} Architecture;

typedef enum Month {
        Month_January,
        Month_February,
        Month_March,
        Month_April,
        Month_May,
        Month_June,
        Month_July,
        Month_August,
        Month_September,
        Month_October,
        Month_November,
        Month_December,
} Month;

typedef enum DayOfWeek {
        DayOfWeek_Monday,
        DayOfWeek_Tuesday,
        DayOfWeek_Wednesday,
        DayOfWeek_Thursday,
        DayOfWeek_Friday,
        DayOfWeek_Saturday,
        DayOfWeek_Sunday,
} DayOfWeek;

#define MonthsInYear 12
#define DaysInWeek 7

local const char *OperatingSystemName[] = {
    [OperatingSystem_Windows] = "Windows",
    [OperatingSystem_MacOS] = "MacOS",
    [OperatingSystem_Linux] = "Linux",
    [OperatingSystem_FreeBSD] = "FreeBSD",
    [OperatingSystem_NetBSD] = "NetBSD",
    [OperatingSystem_OpenBSD] = "OpenBSD",
    [OperatingSystem_Illumos] = "Illumos",
    [OperatingSystem_Unix] = "Unix",
    [OperatingSystem_Unknown] = "Unknown",
};

local const char *ArchitectureName[] = {
    [Architecture_X86_64] = "X86_64",
    [Architecture_X86_32] = "X86_32",
    [Architecture_ARM64] = "ARM64",
    [Architecture_ARM32] = "ARM32",
    [Architecture_Unknown] = "Unknown",
};

local const char *MonthShort[] = {
    [Month_January] = "Jan",
    [Month_February] = "Feb",
    [Month_March] = "Mar",
    [Month_April] = "Apr",
    [Month_May] = "May",
    [Month_June] = "Jun",
    [Month_July] = "Jul",
    [Month_August] = "Aug",
    [Month_September] = "Sep",
    [Month_October] = "Oct",
    [Month_November] = "Nov",
    [Month_December] = "Dec",
};

local const char *MonthLong[] = {
    [Month_January] = "January",
    [Month_February] = "February",
    [Month_March] = "March",
    [Month_April] = "April",
    [Month_May] = "May",
    [Month_June] = "June",
    [Month_July] = "July",
    [Month_August] = "August",
    [Month_September] = "September",
    [Month_October] = "October",
    [Month_November] = "November",
    [Month_December] = "December",
};

local const char *DayOfWeekShort[] = {
    [DayOfWeek_Monday] = "Mon",
    [DayOfWeek_Tuesday] = "Tue",
    [DayOfWeek_Wednesday] = "Wed",
    [DayOfWeek_Thursday] = "Thu",
    [DayOfWeek_Friday] = "Fri",
    [DayOfWeek_Saturday] = "Sat",
    [DayOfWeek_Sunday] = "Sun",
};

local const char *DayOfWeekLong[] = {
    [DayOfWeek_Monday] = "Monday",
    [DayOfWeek_Tuesday] = "Tuesday",
    [DayOfWeek_Wednesday] = "Wednesday",
    [DayOfWeek_Thursday] = "Thursday",
    [DayOfWeek_Friday] = "Friday",
    [DayOfWeek_Saturday] = "Saturday",
    [DayOfWeek_Sunday] = "Sunday",
};

function inline const char *MonthToStringShort(Month month) {
        return (month >= 0 && month < MonthsInYear)
                   ? MonthShort[month]
                   : "Unknown";
}

function inline const char *MonthToStringLong(Month month) {
        return (month >= 0 && month < MonthsInYear) ? MonthLong[month]
                                                    : "Unknown";
}

function inline const char *DayOfWeekToStringShort(DayOfWeek day) {
        return (day >= 0 && day < DaysInWeek) ? DayOfWeekShort[day]
                                              : "Unknown";
}

function inline const char *DayOfWeekToStringLong(DayOfWeek day) {
        return (day >= 0 && day < DaysInWeek) ? DayOfWeekLong[day]
                                              : "Unknown";
}

function inline const char *OperatingSystemToString(
    OperatingSystem osv) {
        return (osv >= 0 && osv < OperatingSystem_Count)
                   ? OperatingSystemName[osv]
                   : "Unknown";
}

function inline const char *ArchitectureToString(Architecture arch) {
        return (arch >= 0 && arch < Architecture_Count)
                   ? ArchitectureName[arch]
                   : "Unknown";
}

function inline OperatingSystem OperatingSystemFromContext() {
        OperatingSystem result = OperatingSystem_Unknown;

#if BASE_OS_WINDOWS == 1
        result = OperatingSystem_Windows;
#elif BASE_OS_MACOS == 1
        result = OperatingSystem_MacOS;
#elif BASE_OS_LINUX == 1
        result = OperatingSystem_Linux;
#elif BASE_OS_FREEBSD == 1
        result = OperatingSystem_FreeBSD;
#elif BASE_OS_NETBSD == 1
        result = OperatingSystem_NetBSD;
#elif BASE_OS_OPENBSD == 1
        result = OperatingSystem_OpenBSD;
#elif BASE_OS_ILLUMOS == 1
        result = OperatingSystem_Illumos;
#elif BASE_OS_UNIX == 1
        result = OperatingSystem_Unix;
#endif

        return result;
}

function inline Architecture ArchitectureFromContext() {
        Architecture result = Architecture_Unknown;
#if BASE_ARCH_X86_64 == 1
        result = Architecture_X86_64;
#elif BASE_ARCH_X86_32 == 1
        result = Architecture_X86_32;
#elif BASE_ARCH_ARM64 == 1
        result = Architecture_ARM64;
#elif BASE_ARCH_ARM32 == 1
        result = Architecture_ARM32;
#endif
        return result;
}
