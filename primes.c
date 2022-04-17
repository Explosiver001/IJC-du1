// ===============     primes.c     ===============
// Řešení IJC-DU1, příklad a), 22.03.2022
//
// Autor: 		Michal Novák, FIT
// 				xnovak3g@stud.fit.vutbr.cz
//
// Přeloženo: 	gcc (Ubuntu 9.4.0-1ubuntu1~20.04) 9.4.0

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "erastothenes.c"

#define SIZE 300000000L

//	výtisk 10 největších prvočísel ze zadaného rozsahu
static inline void last10print(bitset_t jmeno_pole){
	unsigned long buffer[10];
	unsigned int counter = 10;
	for(bitset_index_t i = jmeno_pole[0] - 1; counter; i--){
		if(!(bitset_getbit(jmeno_pole, i)))
            buffer[--counter] = i;
	}
	for(int i = 0; i<10; i++){
		printf("%lu\n", buffer[i]);
	}
}

int main () {
	time_t start = clock();

	bitset_create(primes, SIZE);
	Erastothenes(primes);
	last10print(primes);

	fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
	return 0;
}