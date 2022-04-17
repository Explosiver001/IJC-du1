// ===============     error.h     ===============
// Řešení IJC-DU1, příklad b), 22.03.2022
//
// Autor: 		Michal Novák, FIT
// 				xnovak3g@stud.fit.vutbr.cz
//
// Přeloženo: 	gcc (Ubuntu 9.4.0-1ubuntu1~20.04) 9.4.0

#include <stdio.h>
#include <stdarg.h>


void warning_msg(const char *fmt, ...);

void error_exit(const char *fmt, ...);

void msg_print(const char *fmt, va_list args);


