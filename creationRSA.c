#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>

int pgcd (long a, long b)  {
	int pgcd=0;
	int reste=1;
	while(reste>0) {
	reste=a%b;
	a=b;
	if (reste > 0) {
	b=reste;
	}
	}
	return b;
}

int main (void) {
	long long p;
	long long q;

	long long p1_borne_inf=strtoul(argv[1],NULL,0);
	long long p1_borne_sup=strtoul(argv[2],NULL,0);
	long long p2_borne_inf=strtoul(argv[3],NULL,0);
	long long p2_borne_sup=strtoul(argv[4],NULL,0);

	long long i=0;
	for (i=)
}