/*[GabiShell]*/
#define _GNU_SOURCE          // Requisito para o getline()
#include <stdio.h>           // Requisito para o printf()
#include <unistd.h>          // Requisito para fork()
#include <sys/wait.h>        // Requisito para waitpid()
#include <stdlib.h>          // Requisito para free(), malloc(), realloc() e exit();
#include <string.h>          // Requisito para strcmp()
#include "gash.h"
/*---[Gash]---*/

/*
 * Shell builtins
 * <--TODO-->
 *
 */
int gash_cd(char **args);
int gash_help(char **args);
int gash_fumei(char **args);
int gash_exit(char **args);
int gash_amor(char **args);

char *builtin_str[] = {
  "cd",
  "help",
  "fumei",
  "exit",
  "amor",
};

int (*builtin_func[]) (char **) = {
  &gash_cd,
  &gash_help,
  &gash_fumei,
  &gash_exit,
  &gash_amor,
};

int gash_num_buitins(){
  return sizeof(builtin_str) / sizeof(char *);
}

/* [Implementando Funções Builtins] */

int gash_cd(char **args)
{
  if (args[1] == NULL){
    fprintf(stderr, "[gash]: Era esperado um argumento para \"cd\"\n");
  } else{
    if (chdir(args[1]) != 0){
      perror("[gash]");
    }
  }
  return 1;
}

int gash_help(char **args){

  int i;

  printf("[gash] - [GabiShell] by FelipeArnt\n");
  printf("[gash]: Digite nome de programas, argumentos e pressione enter!!\n");
  printf("[gash:builtins]:  \n");

  for (i = 0; i < gash_num_buitins; i++){printf(" %s\n", builtin_str[i]);}

  printf("[gash]: Use o comando man para exiber informações de outros programas...\n");
}

int gash_fumei(char **args){

  int i;

  printf("[gash]: Contador de cigarros, para de fumar desgraçado!\n");

  if (args[1] == NULL) {
    fprintf(stderr, "[gash]: Era esperado o número de crivos fumados para o comando \"fumei\"\n");
  } else {
    if (fumei(args[1]) != 0){
      perror("[gash]");
    }
  }
}



int gash_amor(char **args){

  int i;

  printf("Eu te amo GabiDalla\n");
}

int gash_exit(){
  return 0;
}


/* [Executor da shell] */

void gash_launch(char **args)
{
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0){
    /*processo filho*/
    if (execvp(args[0], args) == -1) {
      perror("[gash]");
    }
    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    /*[erro no fork]*/
    perror("[gash]");
  } else {
    /* [processo pai] */
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }
  return 1;
 }

int gash_execute(char **args){

  int i;

  if (args[0] == NULL) { return 1; } /* Comando vazio foi digitado*/
  for (i=0; i < gash_num_buitins(); i++){
    if (strcmp(args[0], builtin_str[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }
  return gash_launch();
 }

// Loop da shell 
void gash_loop(void)
{
  char *line;
  char **args;
  int status;

  do {
    printf("> ");

    line = gash_read_line();
    args = gash_split_line(line);
    status = gash_execute(args);

    free(line);
    free(args);
  } while (status);
}

#define GASH_TOK_BUFSIZE 64
#define GASH_TOK_DELIM "\t\r\n\a"
char **gash_split_line(char *line)
{
  int bufzise = GASH_TOK_BUFSIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char));
  char *token;


  if (!tokens)
  {
    fprintf(stderr, "[gash]: Erro ao alocar\n");
    exit(EXIT_FAILURE);
  }

  token = strtok(line, GASH_TOK_DELIM);
  while (token != NULL){
    tokens[position] = token;
    position++;

    if (position >= bufsize){
      bufsize += GASH_TOK_BUFSIZE;
      tokens = realloc(tokens, bufsize * sizeof(char*));
      if (!tokens) {
        fprintf(stderr, "[gash]: Erro ao alocar\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, GASH_TOK_DELIM);
  }
  tokens[position] = NULL;
  return tokens;
}


#define GASH_RL_BUFSIZE 1024
char *gash_read_line(void)
{
  int bufsize = GASH_RL_BUFSIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;

  if (!buffer){
    fprintf(stderr, "[gash]: erro ao alocar\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    c = getchar();

    if (c == EOF || c == '\n'){
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

    if (position >= bufsize){
      bufsize = GASH_RL_BUFSIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer){
        fprintf(stderr, "[gash]: erro ao alocar\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

int main(int argc, char **argv)
{
  gash_loop();
  return EXIT_SUCCESS;
}

