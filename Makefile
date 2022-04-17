# ===============     Makefile     ===============
# Řešení IJC-DU1,  22.03.2022
#
# Autor: 		Michal Novák, FIT
# 				xnovak3g@stud.fit.vutbr.cz

CC = gcc
CFLAGS = -g -w -std=c11 -pedantic -Wall -Wextra 

#přeloží a vytvoří všechny spustitelné soubory pro DU1
default: primes primes-i steg-decode clean

#přeloží a spustí všechny spustitelné soubory s rozlišením aktuálně 
#spouštěných souborů pro větší přehled
all_commented: primes primes-i steg-decode clean
	@echo "Running primes:"
	@./primes
	@echo "Running primes with USE_INLINE:"
	@./primes-i
	@echo "Running steg-decode:"
	@./steg-decode du1-obrazek.ppm

primes: error.o primes.c bitset.h erastothenes.c
	@$(CC) $(CFLAGS) -o2 primes.c error.o -o primes -lm

primes-i: error.o primes.c bitset.h erastothenes.c
	@$(CC) $(CFLAGS) -o2 primes.c error.o -o primes-i -lm -DUSE_INLINE


error.o: error.c
	@$(CC) $(CFLAGS) -c error.c

run: primes primes-i steg-decode
	@./primes
	@./primes-i


#steg-decode
steg-decode: steg-decode.c ppm.o error.o bitset.h erastothenes.c
	@$(CC) $(CFLAGS) steg-decode.c ppm.o error.o -o steg-decode -lm

ppm.o:
	@$(CC) $(CFLAGS) -c ppm.c

run_steg-decode:
	@./steg-decode du1-obrazek.ppm


clean:
	@rm *.o 

zip: *.c *.h Makefile
	zip xnovak3g.zip *.c *.h Makefile



