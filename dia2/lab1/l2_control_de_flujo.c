// control_flujo.c
#include <stdio.h>

typedef enum { OP_ADD=1, OP_SUB=2, OP_NOP=3 } OpCode;

int run(OpCode op, int a, int b) {
    if (op == OP_ADD) {
        return a + b;
    } else if (op == OP_SUB) {
        return a - b;
    } else {
        return 0; // NOP
    }
}

int run_switch(OpCode op, int a, int b) {
    switch (op) {
        case OP_ADD: return a + b;
        case OP_SUB: return a - b;
        case OP_NOP: return 0;
        default:     return 0; // desconocido
    }
}

int main(void) {
    for (int i = 0; i < 3; i++) {
        int r = run_switch((OpCode)(i+1), 7, 3);
        printf("op=%d -> %d\n", i+1, r);
    }
    return 0;
}
