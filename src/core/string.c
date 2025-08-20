#include "string.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "memory.h"

// --- Functional ---

StringView StringView_trimLeft(StringView sv, char c) {
        u64 i = 0;
        while (i < sv.length && sv.data[i] == c) ++i;
        return StringView_new(sv.data + i, sv.length - i);
}

StringView StringView_trimRight(StringView sv, char c) {
        u64 i = sv.length;
        while (i > 0 && sv.data[i - 1] == c) --i;
        return StringView_new(sv.data, i);
}

StringView StringView_trim(StringView sv, char c) {
        return StringView_trimLeft(StringView_trimRight(sv, c), c);
}

StringView StringView_trimLeftWhitespace(StringView sv) {
        while (sv.length && isspace((unsigned char)*sv.data)) {
                ++sv.data;
                --sv.length;
        }
        return sv;
}

StringView StringView_trimRightWhitespace(StringView sv) {
        while (sv.length &&
               isspace((unsigned char)sv.data[sv.length - 1])) {
                --sv.length;
        }
        return sv;
}

StringView StringView_trimWhitespace(StringView sv) {
        return StringView_trimLeftWhitespace(
            StringView_trimRightWhitespace(sv));
}

StringView StringView_substring(StringView sv, u64 start, u64 end) {
        if (start > sv.length) return StringView_new("", 0);
        if (end > sv.length) end = sv.length;
        return StringView_new(sv.data + start, end - start);
}

// --- In-place ---

void StringView_trimLeftInPlace(StringView *sv, char c) {
        while (sv->length && sv->data[0] == c) {
                ++sv->data;
                --sv->length;
        }
}
void StringView_trimRightInPlace(StringView *sv, char c) {
        while (sv->length && sv->data[sv->length - 1] == c) {
                --sv->length;
        }
}
void StringView_trimInPlace(StringView *sv, char c) {
        StringView_trimLeftInPlace(sv, c);
        StringView_trimRightInPlace(sv, c);
}
void StringView_trimWhitespaceInPlace(StringView *sv) {
        *sv = StringView_trimWhitespace(*sv);
}

// --- Chop ---

StringView StringView_chopByDelimiter(StringView *sv, char delim) {
        u64 i = 0;
        while (i < sv->length && sv->data[i] != delim) ++i;

        StringView result = StringView_new(sv->data, i);

        if (i < sv->length) {  // skip delimiter
                sv->data += i + 1;
                sv->length -= i + 1;
                return result;
        }

        sv->data += i;
        sv->length -= i;
        return result;
}

// --- Queries ---

b8 StringView_contains(StringView sv, char c) {
        for (u64 i = 0; i < sv.length; ++i)
                if (sv.data[i] == c) return true;
        return false;
}

b8 StringView_containsSV(StringView sv, StringView sv2) {
        if (sv2.length > sv.length) return false;
        for (u64 i = 0; i <= sv.length - sv2.length; ++i) {
                if (MemoryMatch(sv.data + i, sv2.data, sv2.length))
                        return true;
        }
        return false;
}

b8 StringView_equals(StringView sv, StringView sv2) {
        if (sv.length != sv2.length) return false;
        return MemoryMatch(sv.data, sv2.data, sv.length);
}

b8 StringView_startsWith(StringView sv, StringView sv2) {
        if (sv2.length > sv.length) return false;
        return MemoryMatch(sv.data, sv2.data, sv2.length);
}

b8 StringView_endsWith(StringView sv, StringView suffix) {
        if (suffix.length > sv.length) return false;
        return MemoryMatch(
            sv.data + sv.length - suffix.length,
            suffix.data,
            suffix.length);
}

// --- Conversions ---

char *StringView_toChar(Allocator allocator, StringView sv) {
        char *result = allocator.alloc(sv.length + 1, allocator.ctx);
        MemoryCopy(result, sv.data, sv.length);
        result[sv.length] = '\0';
        return result;
}

char *StringView_toLower(Allocator allocator, StringView sv) {
        char *result = StringView_toChar(allocator, sv);
        for (u64 i = 0; i < sv.length; ++i)
                result[i] = tolower(result[i]);
        return result;
}

char *StringView_toUpper(Allocator allocator, StringView sv) {
        char *result = StringView_toChar(allocator, sv);
        for (u64 i = 0; i < sv.length; ++i)
                result[i] = toupper(result[i]);
        return result;
}

// --- Counts & Indexes ---

u64 StringView_count(StringView sv, char c) {
        u64 count = 0;
        for (u64 i = 0; i < sv.length; ++i)
                if (sv.data[i] == c) ++count;
        return count;
}

u64 StringView_countSV(StringView sv, StringView sv2) {
        u64 count = 0;
        for (u64 i = 0; i + sv2.length <= sv.length; ++i)
                if (StringView_equals(
                        StringView_new(sv.data + i, sv2.length), sv2))
                        ++count;
        return count;
}

i64 StringView_indexOf(StringView sv, char c) {
        for (u64 i = 0; i < sv.length; ++i)
                if (sv.data[i] == c) return i;
        return -1;
}

i64 StringView_indexOfSV(StringView sv, StringView sv2) {
        for (u64 i = 0; i + sv2.length <= sv.length; ++i)
                if (StringView_equals(
                        StringView_new(sv.data + i, sv2.length), sv2))
                        return i;
        return -1;
}

i64 StringView_lastIndexOf(StringView sv, char c) {
        if (!sv.length) return -1;
        for (i64 i = (i64)sv.length - 1; i >= 0; --i)
                if (sv.data[i] == c) return i;
        return -1;
}

i64 StringView_lastIndexOfSV(StringView sv, StringView sv2) {
        if (sv2.length > sv.length) return -1;
        for (i64 i = (i64)(sv.length - sv2.length); i >= 0; --i)
                if (StringView_equals(
                        StringView_new(sv.data + i, sv2.length), sv2))
                        return i;
        return -1;
}

// --- Debug ---

void StringView_print(StringView sv) {
        printf(
            "StringView(len=%lu, data='%.*s')\n",
            sv.length,
            (int)sv.length,
            sv.data);
}
