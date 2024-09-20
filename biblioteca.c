#include "biblioteca.h"

void confirmacao(char *confirmar, char *nome, char *menu, char *sair){ //funcao para continuar no menu ou sair do programa
  while (confirmar[0] != 's' && confirmar[0] != 'S' && confirmar[0] != 'n' && confirmar[0] != 'N'){
    printf("\nDeseja continuar? [S/N]: ");
    fgets(confirmar,sizeof(confirmar),stdin);
    puts("");
  }
  if (confirmar[0] == 's' || confirmar[0] == 'S'){
    return;
  }
  else{
    printf("Tenha um ótimo dia Sr(a) %s!\n", nome);
    *menu = 'f';
    *sair = 't';
  }
}
