#include <stdio.h>

int main(){
    int stack[10];
    int sp = 0;
    
    unsigned char bytecode[] = {
        1,5,
        1,3,
        2,
        3
    };

    int ip = 0;
    while(ip < sizeof(bytecode)){
        unsigned char op = bytecode[ip];
        switch (op) {
            case 1:
            ip++;
            stack[sp++] = bytecode[ip];
            break;
            case 2:
            {
                int b = stack[--sp];
                int a = stack[--sp];
                stack[sp++] = a + b;
            }
            break;
            case 3:
            if (sp > 0){
                printf("Result: %d\n", stack[sp-1]);
            }
            break;
            default:
            printf("Unknown opcode %d\n", op);
        }
        ip++;
    }
}