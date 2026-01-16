#include "gash.h"

/*
 *----------------------------------------------------------------------------------------------------------------*\
 * Estudando --> Referências no final do arquivo README.md                                                         |
 *----------------------------------------------------------------------------------------------------------------*\
 * ac = contador de argumentos;                                                                                    \
 * av = vetor de argumentos;                                                                                       |
 * execvp() = Troca o process image atual por um novo process image;                                               \
 * v = "vetor", p = "path";                                                                                        |
 * char **av = {"ls", "-la", NULL};                                                                                \
 * execvp ("ls", av);                                                                                              |
 *----------------------------------------------------------------------------------------------------------------*\
 * R --> Read          --> gash_read_line() -> lê a linha de comando que foi digitada.                             |
 * E --> Evaluate      --> gash_execute()   -> Decide se é builtin ou comando externo,faz fork/exec se necessário. |
 * P --> Print/Execute --> printf/perror;   -> Mostra prompt, saídas e erros.                                      |
 * L --> loop          --> while(status);   -> Repete até o usuário sair (ex: builtin "exit").                     |
 *----------------------------------------------------------------------------------------------------------------*\
 * [Entry point para uma shell sem loop]                                                                           |
 *----------------------------------------------------------------------------------------------------------------*|
 * int main (int ac, char **av){                                                                                   |
 * (void) ac;                                                                                                      |
 *  int status;                                                                                                    \
 *  // processo filho                                                                                              |
 *  if (fork() == 0)                                                                                               |
 *    execvp(av[1], av + 1); // Recebe um array de argumentos e usa o PATH para achar o executável.                |
 *  wait(&status);                                                                                                 \
 * }                                                                                                               |
 *----------------------------------------------------------------------------------------------------------------*|
 * [Explicação do vetor de argumentos (av)]                                                                        |
 *----------------------------------------------------------------------------------------------------------------*\
 * [comando] -> [argumento] [argumento]                                                                            \
 * 1. tokens --> [ls]                                                                                              |
 * 2. tokens --> [-la]                                                                                             |
 * 3. tokens --> [arquivo]                                                                                         \
 * [ls] --> [-la]-[arquivo]                                                                                            |
 *----------------------------------------------------------------------------------------------------------------*|
 * [Explicação do uso do while()]                                                                                  |
 *----------------------------------------------------------------------------------------------------------------*|
 * 1. get line --> gash_get_line(void)
 * 2. get tokens -> gettok()
 *----------------------------------------------------------------------------------------------------------------*|
*/


char *gash_read_line(void) {

  char *buf;
  size_t bufsize;
  char cwd[BUFSIZE];


  buf = NULL; 
  
  p("> ");  


  if getline(&buf, &bufsize, stdin == - 1) {
    buf = NULL;
    if (feof(stdin)){ p(RED"[gash]:[ EOF ]!!!"RST); }
    else { p(RED"[gash]: Getline falhou!"RST); }
 
 }
  return buf;
  }
/*Entry point*/
int main(int ac, char **av) {
char *line;
 while(0xCE77) { /*Getline*/
    line = gash_read_line();
    p("%s\n", buf);
    pause();
   }
  return EXIT_SUCCESS;
}

