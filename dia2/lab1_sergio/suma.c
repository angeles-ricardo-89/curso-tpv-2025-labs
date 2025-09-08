#include <stdio.h>

int main() {
    int num1, num2;
    int validInput;

    do {
        printf("Ingresa el primer número: ");
        validInput = scanf("%d", &num1);

        if (validInput != 1) {
            printf("Entrada inválida. Por favor, ingresa un número entero.\n");
            while (getchar() != '\n');
        }
    } while (validInput != 1);

    do {
        printf("Ingresa el segundo número: ");
        validInput = scanf("%d", &num2);

        if (validInput != 1) {
            printf("Entrada inválida. Por favor, ingresa un número entero.\n");
            while (getchar() != '\n');
        }
    } while (validInput != 1);

    printf("La suma de %d + %d es: %d\n", num1, num2, num1 + num2);

    return 0;
}