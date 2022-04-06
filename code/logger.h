#include <stdio.h>

#define DEBUG_MODE 0

#if DEBUG_MODE
#define PRINT_DEBUG(...) printf(__VA_ARGS__);
#else
#define PRINT_DEBUG(...)
#endif
