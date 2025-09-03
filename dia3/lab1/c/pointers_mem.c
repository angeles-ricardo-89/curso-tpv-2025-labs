#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int x = 42;
    int *px = &x;
    printf("x=%d, &x=%p, px=%p, *px=%d\n", x, (void*)&x, (void*)px, *px);

    int *arr = (int*)malloc(5 * sizeof(int));
    if (!arr) return 1;
    for (int i=0; i<5; i++) arr[i] = i*i;
    for (int i=0; i<5; i++) printf("%d ", arr[i]);
    printf("\n");
    free(arr);
    return 0;
}
