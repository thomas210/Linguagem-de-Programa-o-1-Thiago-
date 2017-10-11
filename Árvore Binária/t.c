#include <stdio.h>
#include <stdlib.h>

void main (){
	int a = 5;
	int b = 6;
	int res;
	res = ((a > b) ? a : b);
	printf ("%d", res);
	if (res == b) printf ("è desse jeito");
}