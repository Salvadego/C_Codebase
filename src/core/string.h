#pragma once

#include <string.h>

#include "../base/base.h"
#include "memory.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
        u64 length;
        char *data;
} StringView;

function inline StringView StringView_new(char *data, u64 length) {
        StringView sv = {
            .length = length,
            .data = data,
        };
        return sv;
};

function inline StringView StringView_newFromChar(char *data) {
        return StringView_new(data, strlen(data));
};

typedef b8 (*StringViewPredicate)(char c);

StringView StringView_trimLeft(StringView sv, char c);
StringView StringView_trimRight(StringView sv, char c);
StringView StringView_trim(StringView sv, char c);
StringView StringView_trimLeftWhitespace(StringView sv);
StringView StringView_trimRightWhitespace(StringView sv);
StringView StringView_trimWhitespace(StringView sv);
StringView StringView_chopByDelimiter(StringView sv, char delim);
StringView StringView_chopBySV(StringView sv, StringView delimiter);
b8 StringView_contains(StringView sv, char c);
b8 StringView_containsSV(StringView sv, StringView sv2);
b8 StringView_equals(StringView sv, StringView sv2);
b8 StringView_startsWith(StringView sv, StringView prefix);
b8 StringView_endsWith(StringView sv, StringView suffix);

char *StringView_toChar(Allocator allocator, StringView sv);
char *StringView_toLower(Allocator allocator, StringView sv);
char *StringView_toUpper(Allocator allocator, StringView sv);

u64 StringView_count(StringView sv, char c);
u64 StringView_countSV(StringView sv, StringView sv2);
u64 StringView_indexOf(StringView sv, char c);
u64 StringView_indexOfSV(StringView sv, StringView sv2);
u64 StringView_lastIndexOf(StringView sv, char c);
u64 StringView_lastIndexOfSV(StringView sv, StringView sv2);

StringView StringView_substring(StringView sv, u64 start, u64 end);

#ifdef __cplusplus
}
#endif
