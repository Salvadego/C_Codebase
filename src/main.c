#include <stdio.h>

#include "base/macros.h"
#include "core/memory.h"

#define MEMORY_USE_VM 0
#define CORE_IMPLEMENTATION
#include "core/core.h"

#define EvalPrint(x) printf("%s: %s\n", Stringify(x), x);
#define EvalPrintNumber(x) printf("%s: %d\n", Stringify(x), (int)x);
#define EvalPrintBool(x) \
        printf("%s: %s\n", Stringify(x), x ? "true" : "false");
#define EvalPrintChar(x) printf("%s: %c\n", Stringify(x), (char)x);
#define EvalPrintPointer(x) \
        printf("%s: %p\n", Stringify(x), (void *)x);
#define EvalPrintSize(x) printf("%s: %zu\n", Stringify(x), (size_t)x);
#define EvalPrintStringView(x) \
        printf("%s: %s\n", Stringify(x), x.data);

i32 main(void) {
        Allocator allocator = {
            .alloc = mem_alloc,
            .free = mem_free,
        };

        StringView sv = StringView_newFromChar("Hello, World!");
        char *result = StringView_toChar(allocator, sv);
        EvalPrint(result);
        EvalPrintStringView(StringView_trimLeft(sv, 'H'));
        EvalPrintStringView(StringView_trimRight(sv, '!'));
        EvalPrintStringView(StringView_trim(sv, ','));
        EvalPrintStringView(StringView_trimLeftWhitespace(sv));
        EvalPrintStringView(StringView_trimRightWhitespace(sv));
        EvalPrintStringView(StringView_trimWhitespace(sv));
        EvalPrintStringView(StringView_chopByDelimiter(sv, ','));
        EvalPrintStringView(
            StringView_chopBySV(sv, StringView_new(",", 1)));
        EvalPrintBool(StringView_contains(sv, ','));
        EvalPrintBool(
            StringView_containsSV(sv, StringView_new(",", 1)));
        EvalPrintBool(StringView_equals(
            sv, StringView_new("Hello, World!", 13)));
        EvalPrintBool(
            StringView_startsWith(sv, StringView_new("Hello", 5)));
        EvalPrintBool(
            StringView_endsWith(sv, StringView_new("World!", 6)));

        char *upper = StringView_toUpper(allocator, sv);
        EvalPrint(upper);
        allocator.free(upper);

        char *lower = StringView_toLower(allocator, sv);
        EvalPrint(lower);
        allocator.free(lower);

        EvalPrintNumber(StringView_count(sv, 'e'));
        EvalPrintNumber(
            StringView_countSV(sv, StringView_new(",", 1)));
        EvalPrintNumber(StringView_indexOf(sv, 'l'));
        EvalPrintNumber(
            StringView_indexOfSV(sv, StringView_new(",", 1)));
        EvalPrintNumber(StringView_lastIndexOf(sv, 'l'));
        EvalPrintNumber(
            StringView_lastIndexOfSV(sv, StringView_new(",", 1)));
        StringView sv2 = StringView_new("Hello, World!", 13);
        EvalPrintBool(StringView_equals(sv, sv2));
        EvalPrintBool(StringView_startsWith(sv, sv2));
        EvalPrintBool(StringView_endsWith(sv, sv2));

        allocator.free(result);
        return 0;
}
