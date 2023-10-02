/**
 * @file example2.c
 * @brief This code initializes and assigns the variable x to the value of 100 and uses a pointer to show the address of x as well as printing the value of x using the actual value and pointer value. The code then shows the address of an array as well as the address of the first value in the array. Then the code initializes an array where each value in the array is the index multiplied by 10.
 * @date 2023-10-01
 */

#include <stdio.h>

void main()
{ 
    int x;          		/* A normal integer*/
    int *xp;      		/* A pointer to an integer*/  

    x=100;
    xp = &x;        		/*  assigns the address of x to xp" */
    printf( " value of x  = %d\n", x );  
    printf( " value of x  = %d\n", *xp );  /* Note the use of the * to get the value */
    printf( " address of x =%8x \n", xp);
 


//Example2
    int arr[10];
    int i;

    for (i=0; i <10; i++)
	arr[i] = 10*i;
 
     
    printf("address of arr[0] = %8x \n", &arr[0]);
    printf( "address of arr[0] = %p \n", arr);

   int *temp=arr;
  
   for (i=0; i <10; i++)
	printf("%d \t", *temp++);
   printf("\n");
   temp=arr;
    for (i=0; i <10; i++)
	printf("%d \t", (*temp)++);
    printf("\n");
}