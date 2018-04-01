#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

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

int main (int argc, char** argv)  {
	if (argc < 4) {
    printf("Usage : <p> <q> <file>\n");
    }

    char fichier[512];
    long code[512];
    int fdo=0;
	int fdi=0;
    

    long p=atol(argv[1]);
    long q=atol(argv[2]);
    long n=0,phi=0,e=0,d=0,debut=0;
    int i=0;
    long code_caractere=0;
    char caractere;

    sprintf(fichier, argv[3], 512);
    
	fdi=open(fichier, O_RDONLY, 0644);
    if (fdi==-1) {
        perror("ouverture lecture");
        exit(1);
    }

        fdo=open("decrypt.dat", O_WRONLY|O_CREAT|O_TRUNC, 0644);
    if (fdo==-1) {
        perror("ouverture ecriture");
        exit(1);
    }

    n=p*q;
    phi=(p-1)*(q-1);

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

    for (int i=debut; i<phi; i++) {
        if ((e*i)%phi==1) {
            printf("d=%d\n", i);
            d=i;
        }
    }

    printf("cle privée(%d, %d)\n", d, n);

    int count=0;
    while (read(fdi, &code_caractere,sizeof(long))>0) {
  		 int caractere_numerique=expo(code_caractere,d,n);
         caractere=(char) caractere_numerique;
  		 printf("code: %d caractere numerique: %ld caractere: %c\n",code_caractere, caractere_numerique, caractere);
  		 write(fdo, &caractere,sizeof(char));
	}
	close(fdi);
    close( fdo );

    return EXIT_SUCCESS;
}