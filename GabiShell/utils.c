#include "gash.h"

void *Getcwd(char *buf, size_t size){

  if (NULL == getcwd(buf, size))
    perror(RED"getcwd Falhou!"RST);
}


