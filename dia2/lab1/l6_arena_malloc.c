// arena_malloc.c (didáctico)
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define ARENA_SIZE (1024 * 8)
static unsigned char ARENA[ARENA_SIZE];
static size_t arena_off = 0;

void* dmalloc(size_t n) {
    // Alinear a 8 bytes
    size_t aligned = (n + 7) & ~((size_t)7);
    if (arena_off + aligned > ARENA_SIZE) return NULL;
    void* p = &ARENA[arena_off];
    arena_off += aligned;
    return p;
}

void dreset(void) {
    arena_off = 0;
}

int main(void) {
    dreset();
    int *arr = (int*)dmalloc(10 * sizeof(int));
    if (!arr) { printf("Sin memoria en arena\n"); return 1; }

    for (int i=0; i<10; i++) arr[i] = i+1;
    printf("arr[0]=%d, arr[9]=%d\n", arr[0], arr[9]);

    // Otro bloque
    char *msg = (char*)dmalloc(32);
    if (!msg) { printf("Sin memoria en arena\n"); return 1; }
    strcpy(msg, "Hola desde arena allocator");
    printf("%s\n", msg);

    // “Liberar todo”
    dreset();
    return 0;
}
