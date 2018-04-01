crypt: cryptage_rsa_elong.o arithmetique.o
	gcc -o crypt cryptage_rsa_elong.o arithmetique.o

decrypt: decryptage_rsa_elong.o arithmetique.o
	gcc -o decrypt decryptage_rsa_elong.o arithmetique.o

cryptage_rsa_elong.o: cryptage_rsa_elong.c arithmetique.h
	gcc -o cryptage_rsa_elong.o -c cryptage_rsa_elong.c

decryptage_rsa_elong.o: decryptage_rsa_elong.c arithmetique.h
	gcc -o decryptage_rsa_elong.o -c decryptage_rsa_elong.c

arithmetique.o: arithmetique.c
	gcc -o arithmetique.o -c arithmetique.c

				