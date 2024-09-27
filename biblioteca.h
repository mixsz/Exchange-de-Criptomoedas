
#ifndef biblioteca

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

   /*                                       Prototipo das funcoes                                              */

void confirmacao(char *confirmar, char *nome, char *menu, char *sair); //funcao para continuar no menu ou sair do programa
void permissao (char *senharegistrada); // funcao para realizar a acao desejada apos a confirmacao de senha
char depositar(char *real);
char sacar (char *real);

#endif
