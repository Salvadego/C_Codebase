#include "defines.h"

#define EvalPrint(x) printf("%s = %d\n", #x, (int)x)
#define EvalPrintf(x) printf("%s = %f\n", #x, (float)x)

typedef struct {
        size_t a;
        u32 d;
        u16 c;
        u8 b;
} TestStruct;

i32 main(void) {
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

        EvalPrintf(f32_inf());
        EvalPrintf(f32_neg_inf());
        EvalPrintf(f64_inf());
        EvalPrintf(f64_neg_inf());

}
