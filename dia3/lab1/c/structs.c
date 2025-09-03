#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
    int opcode;
    int operand;
} Instruction;

typedef struct {
    int stack[16];
    int sp;
    const unsigned char* code;
    size_t code_len;
    size_t ip;
} VMContext;

int main(void) {
    Instruction ins = {1, 7};
    printf("Instruction{ opcode=%d, operand=%d }\n", ins.opcode, ins.operand);

    VMContext ctx = { .stack={0}, .sp=-1, .code=NULL, .code_len=0, .ip=0 };
    printf("VM sp=%d ip=%zu\n", ctx.sp, ctx.ip);
    return 0;
}
