// tipos_basicos.c
#include <stdio.h>
#include <limits.h>

int main(void) {
    int a = 10;
    char b = 'X';          // 1 byte
    unsigned int c = 300;  // sin signo
    long d = 100000L;      // puede ser 32 o 64 bits según plataforma

    printf("a=%d, b=%c, c=%u, d=%ld\n", a, b, c, d);
    printf("sizeof(int)=%zu, sizeof(long)=%zu, sizeof(char)=%zu\n",
           sizeof(int), sizeof(long), sizeof(char));

    // Comportamiento con signo
    signed char s = -1;
    unsigned char u = (unsigned char)s; // conversión
    printf("signed char s=-1 -> como unsigned: %u\n", u);

    // Rango típico (no asumido): use límites de <limits.h>
    printf("INT_MIN=%d, INT_MAX=%d\n", INT_MIN, INT_MAX);
    return 0;
}
