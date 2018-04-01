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

long plusGrand(long a, long b) {
	if (a>b)  {
		return a;
	}
	return b;
}

long expo(long n, long e, long modulo) {
    long r=1;
    long tmp=n;
    while(e!=0) {
        if ((e%2)==1) {
            r=(r*tmp)%modulo;
        }
        tmp=(tmp*tmp)%modulo;
        e=e >> 1;
    }
    return r;
}

// long* factoriser(long n) {
//     long tab[2];
//     long b=2;
//     while (n%b!=0) {
//         b++;
//         if (n/b==1) {
//             printf("p=%d\n", b);
//         }
//     }
//     tab[0]=b;
// }



int main (int argc, char** argv)  {
	if (argc < 4) {
    printf("Usage : <p> <q> <file>\n");
    }

    char fichier[512];
    long code;
    int fdo=0;
	int fdi=0;
    

    long p=atol(argv[1]);
    long q=atol(argv[2]);
    long n=0,phi=0,e=0,d=0,debut=0;
    int i=0;
    char caractere;
    int codeAscii=0;

    sprintf(fichier, argv[3], 512);
    
	fdi=open(fichier, O_RDONLY, 0644);
    if (fdi==-1) {
        perror("ouverture lecture");
        exit(1);
    }

        fdo=open("code.dat", O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if (fdo==-1) {
        perror("ouverture ecriture");
        exit(1);
    }

    n=p*q;
    phi=(p-1)*(q-1);
    printf("phi=%ld\n", phi);


    debut=plusGrand(p,q)+1;

    for (i=debut; i<phi; i++) {
    	int grand=pgcd(phi,i);
    	printf("pgcd(%d,%d)=%d\n",phi,i, grand);
    	if (grand==1) {
    		e=i;
    		break;
    	}
    }

    printf("cle publique(%d, %d)\n", e,n);

    int count=0;
    while (read(fdi, &caractere,1)>0) {
  		 codeAscii=(int) caractere;
         code=expo(codeAscii,e,n);
  		 printf("code ascii: %d code: %ld caractere: %c\n",codeAscii, code, caractere);
  		 write(fdo, &code,sizeof(long));
	}
	close(fdi);
    close( fdo );

    return EXIT_SUCCESS;
}