#include <stdio.h>
#include <stdlib.h>

#ifdef DEBUG_MODE
#define PRINT_DEBUG(...) printf(__VA_ARGS__);
#else
#define PRINT_DEBUG(...)
#endif

#define PANIC(...) { fprintf(stderr, "PANIC: "); fprintf(stderr, __VA_ARGS__); exit(EXIT_FAILURE); }
