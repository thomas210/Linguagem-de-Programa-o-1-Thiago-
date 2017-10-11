#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void main (){
	struct tm tempo, unix;
	time_t temp, t_unix;
	tempo.tm_year = 1970 - 1900;
	tempo.tm_sec = 25;
	tempo.tm_min = 0;
	tempo.tm_hour = 0;
	tempo.tm_mday = 1;
	tempo.tm_mon = 1 - 1;
	temp = mktime(&tempo) - 10800;
	printf ("%s\n", ctime(&temp));
	printf ("%d\n", temp);
}