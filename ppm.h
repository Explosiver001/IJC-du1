// ===============     ppm.h     ===============
// Řešení IJC-DU1, příklad b), 22.03.2022
//
// Autor: 		Michal Novák, FIT
// 				xnovak3g@stud.fit.vutbr.cz
//
// Přeloženo: 	gcc (Ubuntu 9.4.0-1ubuntu1~20.04) 9.4.0

struct ppm {
    unsigned xsize;
    unsigned ysize;
    char data[];    // RGB bajty, celkem 3*xsize*ysize
};

struct ppm * ppm_read(const char * filename);

void ppm_free(struct ppm *p);
