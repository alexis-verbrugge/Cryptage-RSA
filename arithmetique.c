#include <stdio.h>
#include <stdlib.h>
#include "arithmetique.h"

void printHexa(elong a){

	printf("%016lx . %016lx\n",a.h,a.l);

}

int equals(elong a, elong b){

	if(a.h == b.h && a.l == b.l){
		return 0;
	}else{
		return 1;
	}

}


int elCompar(elong a , elong b){

	if(a.h > b.h){
		return 1;
	}

	if(a.h < b.h){
		return -1;
	}

	if(a.l > b.l){
		return 1;
	}

	if(a.l == b.l){
		return 0;
	}

	return -1;
}


elong elDclg(int decalage, elong a,int boolean){
	// decalage à gauche multiplication
	int i;
	unsigned long int tmp;
	elong t; 

	if (boolean==0) {
		for(i=0;i<decalage;i++){
		//on recupere le bit de poids fort de la partie basse
			tmp = a.l >> 63;
			a.h = a.h << 1;
			a.h = a.h | tmp;
			a.l = a.l << 1;

		}
	} else {
		for(i=0;i<decalage;i++){
		//on recupere le bit de poids fort de la partie haute
			tmp = a.h << 63;
			a.l = a.l >> 1;
			a.l = a.l | tmp;
			a.h = a.h >> 1;

		}
	}

	return a;
}

elong eladd(elong a, elong b){
	struct elong r;
	r.h = b.h;
	r.l = b.l;
	unsigned long int t = b.l;
	r.l += a.l;
	r.h+=a.h+(r.l<t);
	return r;
}

elong elsub(elong a,elong b){

	elong r;
	elong un = {0,1};

	r.h = ~(b.h);
	r.l = ~(b.l);

	return eladd(a,eladd(r,un));

}

elong mul64(unsigned long int a,unsigned long int b){
	elong res0;
	elong res1;
	elong res2;
	unsigned long int resultat;
	unsigned long int max;
	elong r;
	//poids fort
	unsigned long int a0;
	unsigned long int b0;
	//poids faible
	unsigned long int a1;
	unsigned long int b1;

	a1 = a >> 32;
	a0 = a & 0xFFFFFFFF;

	b1 = b >> 32;
	b0 = b & 0xFFFFFFFF;

	res0.h = a1 * b1;
	res0.l=0;

	res1.l = (a0*b1+a1*b0);
	res1.h=0;

	res1=elDclg(32,res1,0);

	res2.l =  (a0*b0);
	res2.h=0;
	


	return eladd(eladd(res0,res1),res2);

}

elong mulElong(elong a, elong b) {
	elong r,t;
	elong bas, milieu, haut;

	bas=mul64(a.h, b.h);

	milieu=elDclg(64,eladd(mul64(a.h, b.l),mul64(a.l, b.h)),0);
	
	
	haut=mul64(a.l, b.l);



	return eladd(eladd(bas,milieu),haut);
}
/* return le modulo */
elong elModulo(elong a, elong b){
	elong res = {0,0},tmp;
	tmp=b;
	elong egal = {0,0};
	int count=0,i=0;

	if(equals(a,b)==0){

		return egal;
	}else{


		while(elCompar(a,tmp)==1){

				tmp=elDclg(1,tmp,0);
				count++;

			}

		for (i=0; i<=count; i++) {
			if(elCompar(a,tmp) >= 1){
				
				a=elsub(a,tmp);

			}
			
			tmp=elDclg(1,tmp,1);
			

			}
			return a;

	}
}


elong exponentiation(elong nombre, elong exposant, elong modulo) {
	elong res={0x0,0x1};
	elong el0 = {0,0};
	elong el1 = {0,1};
	elong el2 = {0,2};
	elong final = {0,1};
	elong tmp=nombre;
	int i=0;

	while (equals(exposant, el0)!=0) {
		if (equals(elModulo(exposant,el2),el1)==0) {
			final=elModulo(mulElong(final,tmp),modulo);
		}
		tmp=elModulo(mulElong(tmp,tmp), modulo);
		//decalage de 1 vers la droite

		exposant=elDclg(1,exposant,1);
	}
	return final;
}