#include <stdio.h>

#ifdef DEBUG_MODE
#define PRINT_DEBUG(...) printf(__VA_ARGS__);
#else
#define PRINT_DEBUG(...)
#endif
