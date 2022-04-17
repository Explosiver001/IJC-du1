// ===============     steg-decode.c     ===============
// Řešení IJC-DU1, příklad b), 22.03.2022
//
// Autor: 		Michal Novák, FIT
// 				xnovak3g@stud.fit.vutbr.cz
//
// Přeloženo: 	gcc (Ubuntu 9.4.0-1ubuntu1~20.04) 9.4.0

#include <stdio.h>
#include <stdlib.h>
#include "ppm.h"
#include "erastothenes.c"


//	Funkce pro nastavení specifického bitu
void char_setbit(unsigned short *c,unsigned index, unsigned value){
	if(index>CHAR_BIT){
		error_exit("char_setbit: Index mimo hranice!");
	}
	if(value){
		*c |= (1 << index);
	}
	else{
		*c &= ~(1 << index);
	}
}

//	Funkce pro získání specifického bitu
unsigned char_getbit(short c, unsigned index){
	if(index>CHAR_BIT){
		error_exit("char_getbit: Index mimo hranice!");
	}
	return (c >> index & 1);
}

void steg_decode(char *data, bitset_t primes){
	short character = 0, pos = 0;
    for(bitset_index_t i = 29; i < bitset_size(primes); i++){
        if(!(bitset_getbit(primes, i))){
			int bit = char_getbit(data[i], 0);
			char_setbit(&character, pos++, bit);
			if(pos == CHAR_BIT){
				printf("%c", character);
				if(character == '\0'){
					break;
				}
				pos = 0;
				character = 0;
			}
        }
    }
	if(character != '\0'){
		error_exit("Zprava neni radne zakoncena!");
	}
	printf("\n");
}


int main(int argc, char **argv)
{
    if(argc<2){
        error_exit("Nebyl zvolen soubor k dekodovani!");
    }

    struct ppm *data = ppm_read(argv[1]);

    bitset_t primes;
    bitset_alloc(primes, data->xsize*data->ysize*3);

	Erastothenes(primes);

	steg_decode(data->data, primes);

	bitset_free(primes);
	ppm_free(data);
    return 0;
}