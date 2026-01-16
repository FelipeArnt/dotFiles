/*Gabi Shell*/
#ifndef GASH_H
# define GASH_H

# define _GNU_SOURCE         /* Requisito para o getline() */
# include <stdio.h>          /* Requisito para o printf()*/
# include <unistd.h>         /* Requisito para fork()*/
# include <sys/wait.h>       /* Requisito para waitpid()*/
# include <stdlib.h>         /* Requisito para free() malloc(), realloc() e exit();*/
# include <string.h>         /* Requisito para strcmp()*/


#define Y         "\033[1;33m"
#define G         "\033[1;32m"
#define C         "\033[1;36m"
#define RED         "\033[1;31m"
#define RST         "\033[0m"

#define p(...) printf(__VA_ARGS__);

void Getcwd(char *, size_t);

#endif
/*---Gash---*/

