/**
 * @file address-operator.c
 * @brief This code uses the address operator to print the memory address for the integer variables a and c.
 * @date 2023-10-01
 */

#include <stdio.h>
#include <stdlib.h>
int main(int argc, char * * argv)
{
  int a = 5;
  int c = 17;
  printf("a's address is %p, c's address is %p\n", &a, &c);
  return EXIT_SUCCESS;
}