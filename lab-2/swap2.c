/**
 * @file swap2.c
 * @brief This code attempts to switch the values of variables u and t by using the pointer to the variables. However, the memory addresses are passed to the function swap2, which switches the values of variables u and t using the memory address. However, it is done locally in the swap2 function and does not change the original values of variables u and t.
 * @date 2023-10-01
 */

#include <stdio.h>
#include <stdlib.h>
void swap2 (int * a , int * b)
{
  int * k = a;
  a = b;
  b = k;
}

int main (int argc ,char * * argv)
{
  int u;
  int t;
  u = 17;
  t = -96;
  printf ("before swap2: u = %d , t = %d \n" , u , t);
  swap2 (& u , & t);
  printf ("after  swap2: u = %d , t = %d \n" , u , t);
  return EXIT_SUCCESS;
}