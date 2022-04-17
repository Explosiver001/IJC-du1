// ===============     erastothenes.c     ===============
// Řešení IJC-DU1, příklad a), 22.03.2022
//
// Autor: 		Michal Novák, FIT
// 				xnovak3g@stud.fit.vutbr.cz
//
// Přeloženo: 	gcc (Ubuntu 9.4.0-1ubuntu1~20.04) 9.4.0

#include <stdio.h>
#include <stdlib.h>
#include "bitset.h"
#include <math.h>

static inline void Erastothenes(bitset_t jmeno_pole){
    bitset_setbit(jmeno_pole, 0, 1);
    bitset_setbit(jmeno_pole, 1, 1);

    unsigned long size = bitset_size(jmeno_pole);
    unsigned long limit = sqrt(size);

    //všechna sudá čísla jsou označena jako čísla složená (nejsou prvočísla)
    for(unsigned long n = 2; n*2 < size; n++)
        {
            bitset_setbit(jmeno_pole, n*2, 1);
        }
    //cyklus přeskakuje všechna sudá čísla, která byla vyřazena v předchozím kroku
    for(bitset_index_t i = 3; i < limit; i+=2){
        if(!(bitset_getbit(jmeno_pole, i)))
        {
            for(unsigned long n = 2; n*i < size; n++)
            {
                bitset_setbit(jmeno_pole, n*i, 1);
            }
        }
    } 
}

