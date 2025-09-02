// memoria_dinamica.c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    size_t n = 5;

    // malloc: memoria no inicializada
    int *a = (int*)malloc(n * sizeof(int));
    if (!a) { perror("malloc"); return 1; }

    // llenar
    for (size_t i=0; i<n; i++) a[i] = (int)(i*i);

    // crecer con realloc
    size_t new_n = 10;
    int *tmp = (int*)realloc(a, new_n * sizeof(int));
    if (!tmp) { free(a); perror("realloc"); return 1; }
    a = tmp;
    for (size_t i=n; i<new_n; i++) a[i] = (int)(i*i);

    // imprimir
    for (size_t i=0; i<new_n; i++) printf("%d ", a[i]);
    printf("\n");

    free(a); // ¡siempre liberar!
    return 0;
}
