#include "defines.h"

#define EvalPrint(x) printf("%s = %d\n", #x, (int)x)

typedef struct {
        u8 b;
        u16 c;
        u32 d;
        size_t a;
} TestStruct;

int main(void) {
        size_t foo[100];
        for (size_t i = 0; i < ArrayCount(foo); i++) {
                foo[i] = i;
        }

        EvalPrint(ArrayCount(foo));

        size_t bar[100];
        MemoryCopyArray(bar, foo);
        EvalPrint(bar[50]);
        EvalPrint(MemoryMatch(foo, bar, sizeof(foo)));
        MemoryZeroArray(bar);
        EvalPrint(bar[50]);
        EvalPrint(MemoryMatch(foo, bar, sizeof(foo)));

        EvalPrint(OffsetOfMember(TestStruct, a));
        EvalPrint(OffsetOfMember(TestStruct, b));
        EvalPrint(OffsetOfMember(TestStruct, c));
        EvalPrint(OffsetOfMember(TestStruct, d));
        EvalPrint(SizeOfType(TestStruct));
        EvalPrint(AlignOfType(TestStruct));

        TestStruct test = {.a = 1, .b = 2, .c = 3, .d = 4};
        EvalPrint(test.a);
        MemoryZeroStruct(&test);
        EvalPrint(test.a);
}
