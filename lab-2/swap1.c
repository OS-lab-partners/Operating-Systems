/**
 * @file swap1.c
 * @brief This code passes the values of the variables to a function that swaps the values of the variables. However, the values of u and t are not changed since we pass the variable values to a function where it cannot change the values of the original variables that were declared outside of the function.
 * @date 2023-10-01
 */

#include <stdio.h>
#include <stdlib.h>
void swap1 (int a , int b)
{
  int k = a;
  a = b;
  b = k;
}
int main (int argc ,char * * argv)
{
  int u;
  int t;
  u = 17;
  t = -96;
  printf ("before swap1: u = %d , t = %d \n" , u , t);
  swap1 (u , t);
  printf ("after  swap1: u = %d , t = %d \n" , u , t);
  return EXIT_SUCCESS;
}