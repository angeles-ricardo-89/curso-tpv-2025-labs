#include <stdio.h>
#include <stdlib.h>

int main() {
    int *arreglo;
    int i;

    arreglo = (int *)malloc(5 * sizeof(int));

    if (arreglo == NULL) {
        printf("Error al asignar memoria.\n");
        return 1;
    }

    for (i = 0; i < 5; i++) {
        arreglo[i] = (i + 1) * (i + 1);
    }

    printf("Contenido del arreglo:\n");
    for (i = 0; i < 5; i++) {
        printf("arreglo[%d] = %d\n", i, arreglo[i]);
    }

    free(arreglo);

    return 0;
}
