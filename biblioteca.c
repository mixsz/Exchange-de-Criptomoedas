#include "biblioteca.h"

void confirmacao(char *confirmar, char *nome, char *menu, char *sair){
  char novamente = 't';
  while(novamente == 't'){
    printf("\nDeseja continuar? [S/N]: ");
    fgets(confirmar,sizeof(confirmar),stdin);
    if (confirmar[0] == 's' || confirmar[0] == 'S'){
      novamente = 'f';
    }
    else if (confirmar[0] == 'n' || confirmar[0] == 'N'){
      printf("\nTenha um ótimo dia Sr(a) %s!\n", nome);
      *menu = 'f';
      *sair = 't';
      novamente = 'f';
    }
    else{
      puts("Resposta inválida!");
    }
  }
}


void permissao (char *senharegistrada){ 
  int permissao_acesso = 1;
  int permissao_funcao = 1;
  char senhalogin[40];
  while (permissao_acesso == 1){

    printf("Digite sua senha: ");
    fgets(senhalogin, sizeof(senhalogin), stdin);
    senhalogin[strcspn(senhalogin, "\n")] = '\0'; // TIRANDO O \n PRA PODER COMPARAR AS SENHAS
    if (strcmp(senhalogin,senharegistrada) == 0){ // SE FOR = 0 É PQ N TEM DIFERENCA DE CARACTER

      permissao_funcao = 0;
      permissao_acesso = 0;
    }
    else{
      printf("Senha incorreta!\n\n");
    }
  }
}

char depositar(char *real){
  double valor;
    int i;
    char ok = 'f';
    char real_depositado[50];
    valor = atof(real);
    printf("\nSaldo atual: R$%.2lf\n\n\n", valor);
    while (ok == 'f'){

      char numero = 'f', letra = 'f';
      printf("Insira o valor que deseja depositar: R$");
      letra = 'f';
      fgets(real_depositado, sizeof(real_depositado), stdin);
      real_depositado[strcspn(real_depositado, "\n")] = '\0';
      for (i = 0; i < strlen(real_depositado);i++){
        if ( !isdigit(real_depositado[i])){ // verificacao de caracter (caso tenha letras) e numero negativo
          if (real_depositado[i] != '.' && real_depositado[i] != ','|| numero == 'f'){
            letra = 't';
          }
          else if (real_depositado[i] == ','){
            real_depositado[i] = '.'; // muda a virgula para um ponto
          }
        }
        else{
          numero = 't'; // caso o usuario digite apenas '.' o programa entendera que esta errado!
        }
      }
    if (letra != 'f'){
      puts("Valor inválido!\n");
    }
    else{
      if (atof(real_depositado) > 0){ // se o valor for = 0 nao funcionara!
        valor += atof(real_depositado);    
        sprintf(real, "%.2lf", valor);
        puts("\nDepósito bem sucedido!\n");
        printf("Valor do depósito: R$%.2lf\n",atof(real_depositado));
        printf("Saldo atual: R$%.2lf\n", valor);
        ok = 't';
      }
      else{
        puts("Valor inválido!\n");
      }
    }
  }
  if (ok == 't'){
    return *real;
  }
  else{
    return 'f';
  }
}

char sacar (char *real){
    double valor;
    valor = atof(real);
    int i = 0;
    char ok = 'f';
    char real_sacado[50];
    if (real[0] == '0'){ // se tiver zerado ou com centavos n funcionará!
      puts("\nOps! Parece que você não possui saldo suficiente para realizar essa operação!");
    }
    else{
      printf("\nSaldo atual: R$%.2lf\n\n\n", valor);
      while (ok == 'f'){

        char numero = 'f', letra = 'f'; // variaveis de verificacao
        printf("Digite o valor que deseja sacar: R$");
        letra = 'f';
        fgets(real_sacado, sizeof(real_sacado), stdin);
        real_sacado[strcspn(real_sacado, "\n")] = '\0';
        for (i = 0; i < strlen(real_sacado);i++){
          if ( !isdigit(real_sacado[i])){ // verificacao de caracter (caso tenha letras) e numero negativo
            if (real_sacado[i] != '.' && real_sacado[i] != ','|| numero == 'f'){
            }
            else if (real_sacado[i] == ','){
              real_sacado[i] = '.'; // muda a virgula para um ponto
            }
          }
          else{
            numero = 't'; // caso o usuario digite apenas '.' o programa entendera que esta errado!
          }
        }
        if (letra != 'f'){
          puts("Valor inválido!\n");
        }
        else{
          if (atof(real_sacado) > 0){ // se o valor for = 0 nao funcionara!
            if (atof(real_sacado) > valor){
              puts("Você não possui esse valor!\n");
            }
            else{
              valor -= atof(real_sacado);    
              sprintf(real, "%.2lf", valor);
              puts("\nSaque bem sucedido!\n");
              printf("Valor do saque: R$%.2lf\n",atof(real_sacado));
              printf("Saldo atual: R$%.2lf\n", valor);
              ok = 't';
            }
          }
          else{
            puts("Valor inválido!\n");
          }
      }
    }
  }
  if (ok == 't'){
    return *real;
  }
  else{
    return 'f';
  }
}
