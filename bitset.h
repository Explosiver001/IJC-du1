// ===============     bitset.h     ===============
// Řešení IJC-DU1, příklad a), 22.03.2022
//
// Autor: 		Michal Novák, FIT
// 				xnovak3g@stud.fit.vutbr.cz
//
// Přeloženo: 	gcc (Ubuntu 9.4.0-1ubuntu1~20.04) 9.4.0

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "error.h"

#define BITWISE_SIZE (sizeof(unsigned long)*CHAR_BIT)


typedef unsigned long * bitset_t;
typedef unsigned long bitset_index_t;

//	deklarace a vynulování lokálního pole
#define bitset_create(jmeno_pole, velikost) unsigned long jmeno_pole[(velikost/BITWISE_SIZE + (velikost % BITWISE_SIZE ? 1 : 0) + 1)] = {velikost, 0,}


//	vztvoření a vynulování dynamicky alokovaného pole 
#define bitset_alloc(jmeno_pole, velikost){\
	if(velikost < 0)\
		error_exit("bitsel_alloc: Zadana velikost je mensi nez 0! (%d)", velikost);\
	else\
	{\
		jmeno_pole = malloc((velikost/BITWISE_SIZE + (velikost % BITWISE_SIZE ? 1 : 0) + 1) * sizeof(unsigned long));\
		if(jmeno_pole == NULL){\
			error_exit("bitset_alloc: Chyba pri allokaci pameti!");\
		}\
		jmeno_pole[0] = velikost;\
		for(unsigned long i = 1; i<(velikost/BITWISE_SIZE + (velikost % BITWISE_SIZE ? 1 : 0) + 1); i++){\
			jmeno_pole[i] = 0;\
		};\
	}\
}

//	uvolnění paměti dynamicky alokovaného pole
#if USE_INLINE

	static inline void bitset_free(bitset_t jmeno_pole){
		free(jmeno_pole);
	}

#else

	#define bitset_free(jmeno_pole) (free(jmeno_pole))

#endif

//	získání velikosti bitového pole
#if USE_INLINE

	static inline unsigned long bitset_size(bitset_t jmeno_pole){
		return jmeno_pole[0];
	}

#else

	#define bitset_size(jmeno_pole) (unsigned long)(jmeno_pole[0])

#endif

//	nastavení specifického bitu v poli na hodnotu 0, nebo 1
#if USE_INLINE

	static inline void bitset_setbit(bitset_t jmeno_pole, bitset_index_t index, int vyraz){

		if(index >= jmeno_pole[0]){
			error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu", (unsigned long)index, (unsigned long)bitset_size(jmeno_pole) - 1);
		}

		if(vyraz)
			jmeno_pole[index/BITWISE_SIZE + 1] |= (1UL  << (index%BITWISE_SIZE));
		else
			jmeno_pole[index/BITWISE_SIZE + 1] &= ~(1UL  << (index%BITWISE_SIZE));
	}

#else

	#define bitset_setbit(jmeno_pole, index, vyraz)\
		do\
		{\ 
			if(index >= jmeno_pole[0])\
				error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu", (unsigned long)index, (unsigned long)bitset_size(jmeno_pole) - 1);\	
			if(vyraz)\
				jmeno_pole[index/BITWISE_SIZE + 1] |= (1UL  << (index%BITWISE_SIZE));\
			else\
				jmeno_pole[index/BITWISE_SIZE + 1] &= ~(1UL  << (index%BITWISE_SIZE));\
		}\
		while(0)

#endif

//	vrátí hodnotu bitu na specifické pozici v poli
#if USE_INLINE

	static inline unsigned short bitset_getbit(bitset_t jmeno_pole, bitset_index_t index){
		if(index >= jmeno_pole[0]){
			error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", (unsigned long)index, (unsigned long)bitset_size(jmeno_pole) - 1);
		}
		//(num >> n) & 1
		return ((jmeno_pole[index/BITWISE_SIZE + 1] >> ((index)%BITWISE_SIZE)) & 1UL);
	}

#else

	#define bitset_getbit(jmeno_pole, index)\
		((index >= jmeno_pole[0]) ?\
			error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", (unsigned long)index, (unsigned long)bitset_size(jmeno_pole)-1), 0\
		:\
			(unsigned short)((jmeno_pole[(index)/BITWISE_SIZE + 1] >> ((index)%BITWISE_SIZE)) & 1UL))

#endif

//	výpis pole v bitech
#if 0
	static inline void bitset_print(bitset_t jmeno_pole){
		for(bitset_index_t i = 0; i<jmeno_pole[0]; i++)
		{
				printf("%u",bitset_getbit(jmeno_pole, i));
				if((i+1)%64 == 0){
					printf(" ");
				}
		} 
		printf("\n");
	}
#endif
