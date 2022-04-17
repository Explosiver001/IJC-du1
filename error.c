// ===============     error.c     ===============
// Řešení IJC-DU1, příklad b), 22.03.2022
//
// Autor: 		Michal Novák, FIT
// 				xnovak3g@stud.fit.vutbr.cz
//
// Přeloženo: 	gcc (Ubuntu 9.4.0-1ubuntu1~20.04) 9.4.0

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void msg_print(const char *fmt, va_list args){
	fprintf(stderr, "CHYBA: ");
	vfprintf(stderr, fmt, args);
	fprintf(stderr, "\n");
}

void warning_msg(const char *fmt, ...){
	va_list args;
	va_start(args, fmt);

	msg_print(fmt, args);

	va_end(args);
}

void error_exit(const char *fmt, ...){
	va_list args;
	va_start(args, fmt);

	msg_print(fmt, args);

	va_end(args);

	exit(1);
}
