#pragma once

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

// Constructors
function inline StringView StringView_new(char *data, u64 length) {
        return (StringView){.data = data, .length = length};
}

function inline StringView StringView_newFromChar(char *data) {
        return StringView_new(data, strlen(data));
}

// Predicates
typedef b8 (*StringViewPredicate)(char c);

// Functional (immutable) API
StringView StringView_trimLeft(StringView sv, char c);
StringView StringView_trimRight(StringView sv, char c);
StringView StringView_trim(StringView sv, char c);
StringView StringView_trimLeftWhitespace(StringView sv);
StringView StringView_trimRightWhitespace(StringView sv);
StringView StringView_trimWhitespace(StringView sv);

StringView StringView_chopByDelimiter(
    StringView *sv, char delim);  // mutates sv
StringView StringView_substring(StringView sv, u64 start, u64 end);

// In-place mutators
void StringView_trimLeftInPlace(StringView *sv, char c);
void StringView_trimRightInPlace(StringView *sv, char c);
void StringView_trimInPlace(StringView *sv, char c);
void StringView_trimWhitespaceInPlace(StringView *sv);

// Queries
b8 StringView_contains(StringView sv, char c);
b8 StringView_containsSV(StringView sv, StringView sv2);
b8 StringView_equals(StringView sv, StringView sv2);
b8 StringView_startsWith(StringView sv, StringView prefix);
b8 StringView_endsWith(StringView sv, StringView suffix);

// Conversions
char *StringView_toChar(Allocator allocator, StringView sv);
char *StringView_toLower(Allocator allocator, StringView sv);
char *StringView_toUpper(Allocator allocator, StringView sv);

// Counts and indexes
u64 StringView_count(StringView sv, char c);
u64 StringView_countSV(StringView sv, StringView sv2);
i64 StringView_indexOf(StringView sv, char c);
i64 StringView_indexOfSV(StringView sv, StringView sv2);
i64 StringView_lastIndexOf(StringView sv, char c);
i64 StringView_lastIndexOfSV(StringView sv, StringView sv2);

// Debug
void StringView_print(StringView sv);

#ifdef __cplusplus
}
#endif
