// arrays_cadenas.c
#include <stdio.h>
#include <string.h>

int main(void) {
    char name[16] = "PAGO";        // incluye '\0'
    printf("name='%s'\n", name);

    // Lectura segura con fgets (no deja basura en buffer)
    char line[32];
    printf("Ingrese texto: ");
    if (fgets(line, sizeof(line), stdin)) {
        // quitar '\n'
        line[strcspn(line, "\r\n")] = 0;
        printf("Len=%zu, Texto='%s'\n", strlen(line), line);
    }

    // Arreglo de enteros
    int nums[5] = {1,2,3,4,5};
    int suma = 0;
    for (size_t i=0; i<5; i++) suma += nums[i];
    printf("Suma={1..5} -> %d\n", suma);
    return 0;
}
