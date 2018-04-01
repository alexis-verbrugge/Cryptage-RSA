#ifndef ARITHMETIQUE_H
#define ARITHMETIQUE_H

struct elong{
	unsigned long int h; /* partie haute */
	unsigned long int l; /* partie basse */
}typedef elong;


void printHexa(elong a);

int equals(elong a, elong b);

int elCompar(elong a, elong b);

elong elDclg(int decalage, elong a, int boolean);

elong eladd(elong a, elong b);

elong elsub(elong a,elong b);

elong mul64(unsigned long int a , unsigned long int b);

elong mulElong(elong a, elong b);

elong elModulo(elong a, elong b);

elong exponentiation(elong nombre,elong exposant,elong modulo); 



#endif