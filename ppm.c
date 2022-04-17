// ===============     ppm.c     ===============
// Řešení IJC-DU1, příklad b), 22.03.2022
//
// Autor: 		Michal Novák, FIT
// 				xnovak3g@stud.fit.vutbr.cz
//
// Přeloženo: 	gcc (Ubuntu 9.4.0-1ubuntu1~20.04) 9.4.0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ppm.h"
#include "error.h"


struct ppm * ppm_read(const char * filename){
	FILE * picture = fopen(filename, "rb");
	if(picture == NULL){
		error_exit("Soubor nelze otevrit!");
	}
	
	char params[4][5] = { 0, };
	
	for(int paramCount = 0;paramCount != 4; ){
		int c, counter = 0;
		char buffer[20] = { 0 };
		while((c=fgetc(picture)) != ' ' &&  c != '\n' &&  c != '\r' && counter < 20){
			buffer[counter++] = c;
			buffer[counter] = '\0';
		}
		if(paramCount == 0){
			if(buffer[0] != 'P'){
				fclose(picture);
				error_exit("Byl zadan spatny typ souboru!");
			}
			strncpy(params[0],buffer,5);
			paramCount++;
			continue;
		}
		strncpy(params[paramCount++],buffer,5);
	}
	
	struct ppm * pictureData = malloc(sizeof(struct ppm)+3*strtoll(params[1], NULL, 0)*strtoll(params[2], NULL, 0));
	pictureData->xsize = strtoll(params[1], NULL, 0);
	pictureData->ysize = strtoll(params[2], NULL, 0);
	int c;
	unsigned long pos = 0;
	while((c=fgetc(picture))!=EOF){
		pictureData->data[pos++] = c;
	}

	fclose(picture);
	return pictureData;
}

void ppm_free(struct ppm *p){
	free(p);
}

