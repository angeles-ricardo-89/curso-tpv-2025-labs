#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define ARENA_SIZE 1024
#define MAX_BLOCKS 10

static unsigned char ARENA[ARENA_SIZE];
static size_t arena_off = 0;

typedef struct {
    void* ptr;
    size_t size;
    int in_use;
} Block;

static Block blocks[MAX_BLOCKS];

size_t align8(size_t n) {
    return (n + 7) & ~((size_t)7);
}

void* dmalloc(size_t n) {
    size_t aligned = align8(n);
    if (arena_off + aligned > ARENA_SIZE) return NULL;

    void* p = &ARENA[arena_off];

    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (!blocks[i].in_use) {
            blocks[i].ptr = p;
            blocks[i].size = aligned;
            blocks[i].in_use = 1;
            break;
        }
    }

    arena_off += aligned;
    return p;
}

void dfree(void* p) {
    for (int i = 0; i < MAX_BLOCKS; i++) {
        if (blocks[i].ptr == p && blocks[i].in_use) {
            blocks[i].in_use = 0;
            printf("Bloque liberado: %p\n", p);
            return;
        }
    }
    printf("Error: puntero no válido o ya liberado.\n");
}

void dreset(void) {
    arena_off = 0;
    for (int i = 0; i < MAX_BLOCKS; i++) {
        blocks[i].in_use = 0;
        blocks[i].ptr = NULL;
        blocks[i].size = 0;
    }
}

int main(void) {
    dreset();

    int* a = (int*)dmalloc(sizeof(int));
    int* b = (int*)dmalloc(sizeof(int));

    if (a && b) {
        *a = 10;
        *b = 20;
        printf("a = %d, b = %d\n", *a, *b);
    }

    dfree(a);
    dfree(b);

    return 0;
}