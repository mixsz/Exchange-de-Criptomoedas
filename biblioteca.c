#include "biblioteca.h"

void confirmacao(char *confirmar, char *nome, char *menu, char *sair){
  char novamente = 't';
  while(novamente == 't'){
    printf("\nDeseja continuar? [S/N]: ");
    fgets(confirmar,sizeof(confirmar),stdin);
    if (confirmar[0] == 's' && strlen(confirmar) == 2 || confirmar[0] == 'S' && strlen(confirmar) == 2){
      novamente = 'f';
    }
    else if (confirmar[0] == 'n' && strlen(confirmar ) == 2|| confirmar[0] == 'N'&& strlen(confirmar) == 2){
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

void depositar(char *real){
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
}

void sacar (char *real, char *registro){
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
              FILE *escreve4 = fopen(registro, "a"); 
              fprintf(escreve4, "\n");
              fprintf(escreve4, "-R$%s", real_sacado);
              fclose(escreve4);

            }
          }
          else{
            puts("Valor inválido!\n");
          }
      }
    }
  }
}

void consultar_saldo(char *real,char *bitcoin,char *ripple,char *ethereum){
  if (strcmp(real, "0.00") == 0 && strcmp(bitcoin, "0.00") == 0 && strcmp(ethereum, "0.00") == 0 
  && strcmp(ripple, "0.00") == 0){                                //verifica se o saldo eh diferente de 0
    puts("Ops! Parece que você não possui um saldo!");
  }
  else{
    printf("\nReal: %s\n", real);
    printf("Bitcoin: %s\n", bitcoin);
    printf("Ripple: %s\n", ripple);
    printf("Ethereum: %s\n", ethereum);
  }
}

void comprar_criptomoeda(char *real_usuario, char *bitcoin_usuario, char *ripple_usuario, char *ethereum_usuario){
  int i;
  char escolha[10];
  char ok = 'f'; // variavel de verificacao de input
  char valor[18];
  double double_valor, double_bitcoin, double_ripple, double_ethereum; // converter string p double
  double valor_atual, bitcoin_atual, ripple_atual, ethereum_atual; // converter o saldo atual de string p double

  double taxa;

  while (ok != 't'){
    puts("\n1. Bitcoin - Cotação: 0.02"); //COTACAO MUDA AO ATUALIZAR COTACAO - TRANSFORMAR EM VARIAVEL CT
    puts("2. Ripple - Cotação: 0.01");
    puts("3. Ethereum - Cotação: 0.01");
    puts("4. Cancelar compra\n");
    printf("Digite a criptomoeda desejada: ");
    fgets(escolha, sizeof(escolha), stdin);

    if (strlen(escolha) > 2 || escolha[0] != '1' && escolha[0] != '2' && escolha[0] != '3' && escolha[0] != '4'){
      puts("Opção inválida!");
    }
    else{
      ok = 't';
    }              
  }
  ok = 'f';
  if (escolha[0] == '4'){
    puts("Compra cancelada com sucesso!");
    ok = 't';
  }
  if (escolha[0] == '1'){
    while (ok == 'f'){
      char numero = 'f', letra = 'f'; // variaveis de verificacao
      printf("\nDigite o valor que deseja investir em Bitcoin: R$");
      letra = 'f';
      fgets(valor, sizeof(valor), stdin);
      valor[strcspn(valor, "\n")] = '\0';
      for (i = 0; i < strlen(valor);i++){
        if ( !isdigit(valor[i])){ // verificacao de caracter (caso tenha letras) e numero negativo
          if (valor[i] != '.' && valor[i] != ','|| numero == 'f'){
            letra = 't';
          }
          else if (valor[i] == ','){
            valor[i] = '.'; // muda a virgula para um ponto
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
        double_valor = atof(valor);
        if(double_valor > 0){
          if (double_valor > atof(real_usuario)){
            puts("Saldo insuficiente!");
            ok = 't';
          }
          else{ // COMPRA DE BITCOIN
            taxa = double_valor * 0.02; // MUDAR PARA VARIAVEL DE COTACAO DEPOISSSSSSSSSSSSSSSSSSSSSS AAAAA
            double_valor -= taxa; // valor de REAL taxado
            double_bitcoin = double_valor / 357340.87; // valor em bitcoin comprado
            bitcoin_atual = atof(bitcoin_usuario) + double_bitcoin; // valor TOTAL em bitcoin
            valor_atual = atof(real_usuario) - double_valor; // valor TOTAL em real

            sprintf((real_usuario), "%.2lf", valor_atual); // double para string
            sprintf(bitcoin_usuario, "%.6lf", bitcoin_atual); // double para string
            puts("Compra realizada com sucesso!");  
            ok = 't';
          }
        }
        else{
          puts("Valor inválido!\n");
        }
      }
    }          
  }
  if (escolha[0] == '2'){
    while (ok == 'f'){
      char numero = 'f', letra = 'f'; // variaveis de verificacao
      printf("\nDigite o valor que deseja investir em Ripple: R$");
      letra = 'f';
      fgets(valor, sizeof(valor), stdin);
      valor[strcspn(valor, "\n")] = '\0';
      for (i = 0; i < strlen(valor);i++){
        if ( !isdigit(valor[i])){ // verificacao de caracter (caso tenha letras) e numero negativo
          if (valor[i] != '.' && valor[i] != ','|| numero == 'f'){
            letra = 't';
          }
          else if (valor[i] == ','){
            valor[i] = '.'; // muda a virgula para um ponto
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
        double_valor = atof(valor);
        if(double_valor > 0){
          if (double_valor > atof(real_usuario)){
            puts("Saldo insuficiente!");
            ok = 't';
          }
          else{ // COMPRA DE RIPPLE
            taxa = double_valor * 0.01; // MUDAR PARA VARIAVEL DE COTACAO DEPOISSSSSSSSSSSSSSSSSSSSSS AAAAA
            double_valor -= taxa; // valor de REAL taxado
            double_ripple = double_valor / 3.36; // valor em ripple comprado
            ripple_atual = atof(ripple_usuario) + double_ripple; // valor TOTAL em ripple
            valor_atual = atof(real_usuario) - double_valor; // valor TOTAL em real

            sprintf((real_usuario), "%.2lf", valor_atual); // double para string
            sprintf(ripple_usuario, "%.6lf", ripple_atual); // double para string
            puts("Compra realizada com sucesso!");
            ok = 't';
          }
        }
        else{
          puts("Valor inválido!\n");
        }
      }
    }          
  }
  if (escolha[0] == '3'){
    while (ok == 'f'){
      char numero = 'f', letra = 'f'; // variaveis de verificacao
      printf("\nDigite o valor que deseja investir em Ethereum: R$");
      letra = 'f';
      fgets(valor, sizeof(valor), stdin);
      valor[strcspn(valor, "\n")] = '\0';
      for (i = 0; i < strlen(valor);i++){
        if ( !isdigit(valor[i])){ // verificacao de caracter (caso tenha letras) e numero negativo
          if (valor[i] != '.' && valor[i] != ','|| numero == 'f'){
            letra = 't';
          }
          else if (valor[i] == ','){
            valor[i] = '.'; // muda a virgula para um ponto
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
        double_valor = atof(valor);
        if(double_valor > 0){
          if (double_valor > atof(real_usuario)){
            puts("Saldo insuficiente!");
            ok = 't';
          }
          else{ // COMPRA DE ETHEREUM
            taxa = double_valor * 0.01; // MUDAR PARA VARIAVEL DE COTACAO DEPOISSSSSSSSSSSSSSSSSSSSSS AAAAA
            double_valor -= taxa; // valor de REAL taxado
            double_ethereum = double_valor / 14999.58; // valor em ethereum comprado
            ethereum_atual = atof(ethereum_usuario) + double_ethereum; // valor TOTAL em ethereum
            valor_atual = atof(real_usuario) - double_valor; // valor TOTAL em real

            sprintf((real_usuario), "%.2lf", valor_atual); // double para string
            sprintf(ethereum_usuario, "%.6lf", ethereum_atual); // double para string
            puts("Compra realizada com sucesso!");
            ok = 't';
          }
        }
        else{
          puts("Valor inválido!\n");
        }
      }
    }          
  }
}
