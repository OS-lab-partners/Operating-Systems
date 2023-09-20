#include <stdio.h>

int main(){
    int integer = 235;
    
    printf("\nNow showing the value 235 in different formats...\n");
    printf("\nInteger: %d\n", integer);
    printf("\nFloat: %f\n", (float)integer);
    printf("\nOctal: %o\n", integer);
    printf("\nHexadecimal: %x\n", integer);
    
    return 0;
}