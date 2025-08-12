#include <stddef.h>

typedef enum {
        ERR_LEN,
} Error;

const char* error_str[ERR_LEN] = {};

// typedef struct {
//         Error err;
//         char* data;
//         size_t len;
// } OptionalBuf;
