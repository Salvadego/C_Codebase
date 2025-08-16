#pragma once

#include "string.h"

#include <ctype.h>
#include <string.h>

#include "memory.h"

// =============
// String View
// =============

StringView StringView_trimLeft(StringView sv, char c) {
        u64 i = 0;
        while (i < sv.length && sv.data[i] == c) {
                ++i;
        }
        return StringView_new(sv.data + i, sv.length - i);
}

StringView StringView_trimRight(StringView sv, char c) {
        u64 i = sv.length;
        while (i > 0 && sv.data[i - 1] == c) {
                --i;
        }
        return StringView_new(sv.data, i);
}

StringView StringView_trim(StringView sv, char c) {
        return StringView_trimLeft(StringView_trimRight(sv, c), c);
}

StringView StringView_trimLeftWhitespace(StringView sv) {
        StringView new_sv = StringView_trimLeft(sv, ' ');
        new_sv = StringView_trimLeft(new_sv, '\t');
        new_sv = StringView_trimLeft(new_sv, '\n');
        new_sv = StringView_trimLeft(new_sv, '\r');
        new_sv = StringView_trimLeft(new_sv, '\f');
        new_sv = StringView_trimLeft(new_sv, '\v');

        return new_sv;
}

StringView StringView_trimRightWhitespace(StringView sv) {
        StringView new_sv = StringView_trimRight(sv, ' ');
        new_sv = StringView_trimRight(new_sv, '\t');
        new_sv = StringView_trimRight(new_sv, '\n');
        new_sv = StringView_trimRight(new_sv, '\r');
        new_sv = StringView_trimRight(new_sv, '\f');
        new_sv = StringView_trimRight(new_sv, '\v');

        return new_sv;
}

StringView StringView_trimWhitespace(StringView sv) {
        return StringView_trim(
            StringView_trimLeftWhitespace(sv), ' ');
}

StringView StringView_chopByDelimiter(StringView sv, char delim) {
        u64 i = 0;
        while (i < sv.length && sv.data[i] != delim) {
                ++i;
        }

        StringView result = StringView_new(sv.data, i);
        if (i < sv.length) {
                sv.length -= i + 1;
                sv.data += i + 1;
                return result;
        }

        sv.length -= i;
        sv.data += i;
        return result;
}

StringView StringView_chopBySV(StringView sv, StringView delimiter) {
        u64 i = 0;
        while (i < sv.length &&
               StringView_containsSV(sv, delimiter)) {
                ++i;
        }

        StringView result = StringView_new(sv.data, i);
        if (i < sv.length) {
                sv.length -= i + delimiter.length;
                sv.data += i + delimiter.length;
                return result;
        }

        sv.length -= i;
        sv.data += i;
        return result;
}

b8 StringView_contains(StringView sv, char c) {
        for (u64 i = 0; i < sv.length; ++i) {
                if (sv.data[i] == c) return true;
        }
        return false;
}

b8 StringView_containsSV(StringView sv, StringView sv2) {
        if (sv2.length > sv.length) return false;

        for (u64 i = 0; i < sv.length - sv2.length + 1; ++i) {
                if (MemoryMatch(sv.data + i, sv2.data, sv2.length)) {
                        return true;
                }
        }

        return false;
}

b8 StringView_equals(StringView sv, StringView sv2) {
        if (sv.length != sv2.length) return false;
        return MemoryMatch(sv.data, sv2.data, sv.length);
}

b8 StringView_startsWith(StringView sv, StringView sv2) {
        if (sv2.length > sv.length) return false;
        StringView actualPrefix = StringView_new(sv.data, sv2.length);
        return StringView_equals(sv2, actualPrefix);
}

b8 StringView_endsWith(StringView sv, StringView suffix) {
        if (suffix.length > sv.length) return false;
        StringView actualSuffix = StringView_new(
            sv.data + sv.length - suffix.length, suffix.length);
        return StringView_equals(suffix, actualSuffix);
}

void StringView_toLower(StringView *sv) {
        for (u64 i = 0; i < sv->length; ++i) {
                sv->data[i] = tolower(sv->data[i]);
        }
}

void StringView_toUpper(StringView *sv) {
        for (u64 i = 0; i < sv->length; ++i) {
                sv->data[i] = toupper(sv->data[i]);
        }
}

u64 StringView_count(StringView sv, char c) {
        u64 count = 0;
        for (u64 i = 0; i < sv.length; ++i) {
                if (sv.data[i] == c) {
                        ++count;
                }
        }
        return count;
}

u64 StringView_countSV(StringView sv, StringView sv2) {
        u64 count = 0;
        for (u64 i = 0; i < sv.length - sv2.length + 1; ++i) {
                if (StringView_equals(
                        StringView_new(sv.data + i, sv2.length),
                        sv2)) {
                        ++count;
                }
        }
        return count;
}

u64 StringView_indexOf(StringView sv, char c) {
        for (u64 i = 0; i < sv.length; ++i) {
                if (sv.data[i] == c) {
                        return i;
                }
        }
        return -1;
}

u64 StringView_indexOfSV(StringView sv, StringView sv2) {
        for (u64 i = 0; i < sv.length - sv2.length + 1; ++i) {
                if (StringView_equals(
                        StringView_new(sv.data + i, sv2.length),
                        sv2)) {
                        return i;
                }
        }
        return -1;
}

u64 StringView_lastIndexOf(StringView sv, char c) {
        for (u64 i = sv.length - 1; i > 0; --i) {
                if (sv.data[i] == c) {
                        return i;
                }
        }
        return -1;
}

u64 StringView_lastIndexOfSV(StringView sv, StringView sv2) {
        u64 i = sv.length - sv2.length;
        while (i > 0) {
                if (StringView_equals(
                        StringView_new(sv.data + i, sv2.length),
                        sv2)) {
                        return i;
                }
                --i;
        }
        return -1;
}

StringView StringView_substring(StringView sv, u64 start, u64 end) {
        if (start > sv.length) return StringView_new("", 0);
        if (end > sv.length) end = sv.length;
        return StringView_new(sv.data + start, end - start);
}

char *StringView_toChar(Allocator allocator, StringView sv) {
        char *result = allocator.alloc(sv.length + 1);
        MemoryCopy(result, sv.data, sv.length);
        result[sv.length] = '\0';
        return result;
}
