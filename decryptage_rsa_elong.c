#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "arithmetique.h"

elong pgcd (elong a, elong b) {
    elong pgcd={0,0};
    elong reste={0,1};
    elong elong0={0,0};
    while(elCompar(reste,elong0)==1) {
    reste=elModulo(a,b);
    a=b;
    if (elCompar(reste,elong0)==1) {
    b=reste;
    }
    }
    return b;
}

elong plusGrand(elong a, elong b) {
    if (elCompar(a,b)==1)  {
        return a;
    }
    return b;
}

int main (int argc, char** argv)  {
	if (argc < 4) {
    printf("Usage : <partie haute de p> <partie basse de p> <partie haute de q> <partie basse de q> <file>\n");
    }

    char fichier[512];
    int fdo=0;
    int fdi=0;
    
    elong p={0,0};
    elong q={0,0};
    elong n={0,0};
    elong phi={0,0};
    elong e={0,0};
    elong d={0,0};
    elong debut={0,0};
    elong elong1={0,1};
    elong codeAscii={0,0};
    elong code={0,0};
    elong code_caractere={0,0};

    p.h=strtol(argv[1], NULL, 10);
    p.l=strtol(argv[2], NULL, 10);
    q.h=strtol(argv[3], NULL, 10);
    q.l=strtol(argv[4], NULL, 10);

    printf("recuperation : %lld, %lld, %lld, %lld\n", p.h, p.l, q.h, q.l);

    elong i={0,0};
    char caractere;

    sprintf(fichier, argv[5], 512);
    
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

     n=mulElong(p,q);

    printf("n= : %lld . %lld\n", n.h, n.l);
    phi=mulElong(elsub(p,elong1),elsub(q,elong1));
    printf("phi= : %lld . %lld\n", phi.h, phi.l);


    debut=eladd(plusGrand(p,q),elong1);
    printf("debut= : %lld . %lld\n", debut.h, debut.l);

    for (i=debut; elCompar(i,phi)==-1 ; i=eladd(i,elong1)) {
        elong grand=pgcd(phi,i);
        printf("pgcd(%lld . %lld , %lld . %lld)=%lld . %lld\n",phi.h, phi.l,i.h, i.l,grand.h, grand.l);
        if (equals(grand,elong1)==0) {
            e=i;
            break;
        }
    }
    
    printf("cle publique(%lld . %lld, %lld . %lld)\n", e.h, e.l ,n.h, n.l);

    // for (i=debut; elCompar(i,phi)==-1 ; i=eladd(i,elong1)) {
    //      printf("d=%lld . %lld\n", i.h, i.l);
    //     if (elCompar(elModulo(mulElong(e,i),phi),elong1)==0) {
           
    //         d=i;
    //     }
    // }

    d=exponentiation(elong1,e,phi);

    printf("cle privee(%lld . %lld, %lld . %lld)\n", d.h, d.l ,n.h, n.l);

    int count=0;
    while (read(fdi, &code_caractere,sizeof(elong))>0) {
  		 elong caractere_numerique=exponentiation(code_caractere,d,n);
         caractere=(char) caractere_numerique.l;
  		 printf("code: %lld . %lld caractere numerique: %lld . %lld caractere: %c\n",
            code_caractere.h, code_caractere.l, caractere_numerique.h, caractere_numerique.l, caractere);
  		 write(fdo, &caractere,sizeof(char));
	}
	close(fdi);
    close( fdo );

    return EXIT_SUCCESS;
}