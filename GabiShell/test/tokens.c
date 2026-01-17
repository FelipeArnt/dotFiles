#include <stdio.h>    /* printf */
#include <stdlib.h>   /* EXIT_SUCCESS */
#include <string.h>   /* strtok */
#include "gash.h"

/* Corrigido: nome diferente para evitar conflito com a versão principal */
void testar_split_line(char *line)
{
    char *tokens[6] = {0};
    int posicao = 0;
    for (char *token = strtok(line, DEL); token; token = strtok(NULL, DEL)) {
        tokens[posicao++] = token;
        if (posicao >= 6) {
            break;
        }
    }
    posicao = 0;
    while (tokens[posicao]) {
        p("%s\n", tokens[posicao++]);
    }
}

int main(void)
{
    char s[] = "ls -la README.md | bat";
    testar_split_line(s);
    return EXIT_SUCCESS;
}
