/**
 * @file example1.c
 * @brief This code prints the different representations of the variable c.
 * @date 2023-10-01
 */

#include <stdio.h>
int main ()
{
  /* variable definition: */
  int a, b;
  int c;
   
 
  /* actual initialization */
  a = 10;
  b = 20;
  c = a + b;
 
  printf("value of c integer (%d), unsigned (%u), floating (%f), character (%c), Octal (%o), hex (%8x) \n", c, c,c, c,c,c);
  
 
  return 0;
}