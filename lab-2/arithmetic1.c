/**
 * @file arithmetic1.c
 * @brief This code declares 3 different arrays; one array holds integers, one array holds characters, and the last array holds doubles. The program then prints the first values in each array, followed by the second value held in each array, and then the third and fourth values in each array as well.
 * @date 2023-10-01
 */

#include <stdio.h>
#include <stdlib.h>
int main (int argc ,char * * argv)
{
  int    arr1[] = {7, 2, 5, 3, 1, 6, -8, 16, 4};
  char   arr2[] = {'m', 'q', 'k', 'z', '%', '>'};
  double arr3[] = {3.14, -2.718, 6.626, 0.529};
  int len1 = sizeof(arr1) / sizeof(int);
  int len2 = sizeof(arr2) / sizeof(char);
  int len3 = sizeof(arr3) / sizeof(double);
  printf("lengths = %d, %d, %d\n", len1, len2, len3);
  int    * iptr = arr1;
  char   * cptr = arr2;
  double * dptr = arr3;
  printf("values = %d, %c, %f\n", * iptr, * cptr, * dptr);
  iptr ++;
  cptr ++;
  dptr ++;
  printf("values = %d, %c, %f\n", * iptr, * cptr, * dptr);
  iptr ++;
  cptr ++;
  dptr ++;
  printf("values = %d, %c, %f\n", * iptr, * cptr, * dptr);
  iptr ++;
  cptr ++;
  dptr ++;
  printf("values = %d, %c, %f\n", * iptr, * cptr, * dptr);
  return EXIT_SUCCESS;
}