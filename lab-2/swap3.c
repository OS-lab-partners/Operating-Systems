/**
 * @file swap3.c
 * @brief This code attempts to swap the values of u and t but fails because it does not update the value of u, which is why t and u contain the same values after swap 3.
 * @date 2023-10-01
 */

#include <stdio.h>
#include <stdlib.h>

void swap3 (int * a, int * b)
{
  int k = * a;
  a = b;
  * b = k;
}


int main (int argc ,char * * argv)
{
  int u;
  int t;
  u = 17;
  t = -96;
  printf ("before swap3: u = %d , t = %d \n" , u , t);
  swap3 (& u , & t);
  printf ("after  swap3: u = %d , t = %d \n" , u , t);
  return EXIT_SUCCESS;
}