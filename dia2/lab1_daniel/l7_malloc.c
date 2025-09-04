#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARENA_SIZE 256

typedef struct {
    unsigned char buffer[ARENA_SIZE];
    int offset;
} MemoryArena;

MemoryArena arena = {0};

void* dmalloc(int n) {
    if (arena.offset + n > ARENA_SIZE) {
        return NULL;
    }
    void* p = &arena.buffer[arena.offset];
    arena.offset += n;
    return p;
}

void dreset() {
    arena.offset = 0;
}

void ejercicioArena() {
    dreset();

    int *arr = (int*)dmalloc(5 * sizeof(int));
    if (!arr) {
        printf("Error: sin memoria en arena.\n");
        return;
    }

    for (int i = 0; i < 5; i++) {
        arr[i] = (i+1) * (i+1);
    }

    printf("Arreglo con cuadrados: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    char *msg = (char*)dmalloc(32);
    if (!msg) {
        printf("Error: sin memoria en arena.\n");
        return;
    }

    strcpy(msg, "Hola Daniel, dmalloc!");
    printf("%s\n", msg);

    dreset();
    printf("Arena reseteada.\n");
}


int pedirEntero(const char *mensaje) {
    int num;
    int resultado;

    while (1) {
        printf("%s", mensaje);
        resultado = scanf("%d", &num);

        if (resultado == 1) {
            return num; 
        } else {
            printf("Error: Debes ingresar un número entero.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
        }
    }
}

void ejercicioSuma() {
    int num1, num2, suma;

    num1 = pedirEntero("Ingresa el primer número: ");
    num2 = pedirEntero("Ingresa el segundo número: ");

    suma = num1 + num2;
    printf("La suma de %d y %d es %d\n", num1, num2, suma);
}

void ejercicioCuadrados() {
    int n = 5;
    
    int *arr = (int *) malloc(n * sizeof(int));

    if (arr == NULL) {
        printf("Error: no se pudo reservar memoria.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        arr[i] = (i + 1) * (i + 1);
    }

    for (int i = 0; i < n; ++i) {
        printf("%5d  %5d  %p\n", i, arr[i], (void*)(arr + i));
    }

    free(arr);
    arr = NULL;
}


int main() {
    int opcion;

    printf("=== MENU DE EJERCICIOS ===\n");
    printf("Selecciona una opción:\n");
    printf("1. Suma de dos números\n");
    printf("2. Arreglo dinámico con cuadrados\n");
    printf("3. Arena allocator didáctico\n");
    scanf("%d", &opcion);

    switch (opcion) {
        case 1: ejercicioSuma(); break;
        case 2: ejercicioCuadrados(); break;
        case 3: ejercicioArena(); break;
        default:
            printf("Opción no válida.\n");
            break;
    }

    return 0;
}