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

void nome(char nome_mostra[], const char nome[]) {
    int i = 0;
    while (nome[i] != '\0') {
        if (nome[i] == '_') {
            nome_mostra[i] = ' ';  // substitui '_' por ' '
        } else {
            nome_mostra[i] = nome[i];  // copia o caractere
        }
        i++;
    }
    nome_mostra[i] = '\0';  // adiciona \0
}

void depositar(char *real, char *bitcoin, char *ripple, char *ethereum, char *registro){
  double valor;
  int i = 0; 

  time_t antes = 0;
  time( &antes);
   antes -= 10800;// converter para horario de brasilia subtraindo 3 horas em segundos
  char horario[100]; 
  strcpy(horario, ctime( &antes));
  for (i = 0; i < strlen(horario); i++){
    if (horario[i] == ' '){
      horario[i] = '_';}
    else if(horario[i]== '\n'){
      horario[i] = '\0';
    }
  } 
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
        FILE *escreve4 = fopen(registro, "a"); 
        fprintf(escreve4, "\n");
        fprintf(escreve4, "%s_+_%.2lf_REAL__CT:_0.0__TX:_0.0\n",horario,           (atof(real_depositado)));
        fprintf(escreve4, "%s_REAL:_%.2lf__BTC:_%s__XRP:_%s__ETH:_%s\n",horario, valor, bitcoin, ripple, ethereum);
        fclose(escreve4);
        ok = 't';
      }
      else{
        puts("Valor inválido!\n");
      }
    }
  }
}

void sacar (char *real, char *registro, char *bitcoin, char *ripple, char *ethereum){
  int i = 0; 

  time_t antes = 0;
  time( &antes);
  antes -= 10800;// converter para horario de brasilia subtraindo 3 horas em segundos
  char horario[100]; 
  strcpy(horario, ctime( &antes));
  for (i = 0; i < strlen(horario); i++){
    if (horario[i] == ' '){
      horario[i] = '_';}
    else if(horario[i]== '\n'){
      horario[i] = '\0';
    }
  } 
   /////////////
    double valor;
    valor = atof(real);

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
              fprintf(escreve4, "%s_-_%.2lf_REAL__CT:_0.0__TX:_0.0\n",horario,                          (atof(real_sacado)));
              fprintf(escreve4, "%s:_REAL:_%.2lf__BTC:_%s__XRP:_%s__ETH:_%s\n",horario, valor, bitcoin, ripple, ethereum);
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

void consultar_saldo(char *real,char *bitcoin,char *ripple,char *ethereum,char *nome, char *cpf){
  if (strcmp(real, "0.00") == 0 && strcmp(bitcoin, "0.00") == 0 && strcmp(ethereum, "0.00") == 0 
  && strcmp(ripple, "0.00") == 0){                                //verifica se o saldo eh diferente de 0
    puts("Ops! Parece que você não possui um saldo!");
  }
  else{
    printf("\n%s\n",nome);
    printf("%s\n",cpf);

    printf("\nReal: %s\n", real);
    printf("Bitcoin: %s\n", bitcoin);
    printf("Ripple: %s\n", ripple);
    printf("Ethereum: %s\n", ethereum);
  }
}

void comprar_criptomoeda(char *real_usuario, char *bitcoin_usuario, char *ripple_usuario, char *ethereum_usuario,char *registro, char *cotacao_btc2, char *cotacao_rip2, char *cotacao_eth2){
  int i = 0; 

  time_t antes = 0;
  time( &antes);
   antes -= 10800;// converter para horario de brasilia subtraindo 3 horas em segundos
  char horario[100]; 
  strcpy(horario, ctime( &antes));
  for (i = 0; i < strlen(horario); i++){
    if (horario[i] == ' '){
      horario[i] = '_';}
    else if(horario[i]== '\n'){
      horario[i] = '\0';
    }
  } 
  char escolha[10];
  char ok = 'f'; // variavel de verificacao de input
  char valor[18];
  double double_valor, double_bitcoin, double_ripple, double_ethereum; // converter string p double
  double valor_atual, bitcoin_atual, ripple_atual, ethereum_atual; // converter o saldo atual de string p double

  double taxa;

  while (ok != 't'){
    printf("\n1. Bitcoin   - Cotação: %s\n", cotacao_btc2); //COTACAO MUDA AO ATUALIZAR COTACAO - TRANSFORMAR EM VARIAVEL CT
    printf("2. Ripple    - Cotação: %s\n", cotacao_rip2);
    printf("3. Ethereum  - Cotação: %s\n", cotacao_eth2);
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
            double_bitcoin = double_valor / atof(cotacao_btc2); // valor em bitcoin comprado
            double_bitcoin = double_bitcoin * 0.98; // taxa de comissao
            bitcoin_atual = atof(bitcoin_usuario) + double_bitcoin; // valor TOTAL em bitcoin
            valor_atual = atof(real_usuario) - double_valor; // valor TOTAL em real

            sprintf((real_usuario), "%.2lf", valor_atual); // double para string
            sprintf(bitcoin_usuario, "%.6lf", bitcoin_atual); // double para string
            puts("Compra realizada com sucesso!");

            FILE *escreve5 = fopen(registro, "a"); 
            fprintf(escreve5, "\n");
    
            fprintf(escreve5, "%s_+_%.6lf_BTC__CT:_%s__TX:_0.02\n",horario, double_bitcoin,cotacao_btc2);
            fprintf(escreve5, "%s_REAL:_%.2lf__BTC:_%.6lf__XRP:_%s__ETH:_%s\n",horario, valor_atual, bitcoin_atual, ripple_usuario,ethereum_usuario);
            fclose(escreve5);
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
            double_ripple = double_valor / atof(cotacao_rip2); // valor em ripple comprado
            double_ripple = double_ripple * 0.99; // taxa de comissao
            ripple_atual = atof(ripple_usuario) + double_ripple; // valor TOTAL em ripple
            valor_atual = atof(real_usuario) - double_valor; // valor TOTAL em real

            sprintf((real_usuario), "%.2lf", valor_atual); // double para string
            sprintf(ripple_usuario, "%.6lf", ripple_atual); // double para string
            FILE *escreve6 = fopen(registro, "a"); 
            fprintf(escreve6, "\n");
            fprintf(escreve6, "%s_+_%.6lf_XRP__CT:_%s__TX:_0.01\n",horario, double_ripple,cotacao_rip2);
            fprintf(escreve6, "%s_REAL:_%.2lf__BTC:_%.6lf__XRP:_%s__ETH:_%s\n",horario, valor_atual, bitcoin_atual, ripple_usuario,ethereum_usuario);

            fclose(escreve6);
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
            double_ethereum = double_valor / atof(cotacao_eth2); // valor em ethereum comprado
            double_ethereum = double_ethereum * 0.99; // taxa de comissao
            ethereum_atual = atof(ethereum_usuario) + double_ethereum; // valor TOTAL em ethereum
            valor_atual = atof(real_usuario) - double_valor; // valor TOTAL em real

            sprintf((real_usuario), "%.2lf", valor_atual); // double para string
            sprintf(ethereum_usuario, "%.6lf", ethereum_atual); // double para string
            FILE *escreve7 = fopen(registro, "a"); 
            fprintf(escreve7, "\n");
            fprintf(escreve7, "%s_+_%.6lf_ETH__CT:_%s__TX:_0.01\n",horario, double_ethereum,cotacao_eth2);
            fprintf(escreve7, "%s_REAL:_%.2lf__BTC:_%.6lf__XRP:_%s__ETH:_%s\n",horario, valor_atual, bitcoin_atual, ripple_usuario,ethereum_usuario);
            fclose(escreve7);
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

void vender_criptomoeda(char *real_usuario, char *bitcoin_usuario, char *ripple_usuario, char *ethereum_usuario,char *registro, char *cotacao_btc1, char *cotacao_rip1, char *cotacao_eth1){
  int i = 0; 

  time_t antes = 0;
  time( &antes);
   antes -= 10800;// converter para horario de brasilia subtraindo 3 horas em segundos
  char horario[100]; 
  strcpy(horario, ctime( &antes));
  for (i = 0; i < strlen(horario); i++){
    if (horario[i] == ' '){
      horario[i] = '_';}
    else if(horario[i]== '\n'){
      horario[i] = '\0';
    }
  } 
  char escolha[10];
  char ok = 'f'; // variavel de verificacao de input
  char valor[18];
  double double_real, double_valor, double_bitcoin, double_ripple, double_ethereum; // converter string p double
  double real_atual, bitcoin_atual, ripple_atual, ethereum_atual; // converter o saldo atual de string p double

  double taxa;

  while (ok != 't'){
    printf("\n1. Bitcoin   - Cotação: %s\n",cotacao_btc1); //COTACAO MUDA AO ATUALIZAR COTACAO - TRANSFORMAR EM VARIAVEL CT
    printf("2. Ripple    - Cotação: %s\n",cotacao_rip1);
    printf("3. Ethereum  - Cotação: %s\n",cotacao_eth1);
    puts("4. Cancelar venda\n");
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
    puts("Venda cancelada com sucesso!");
    ok = 't';
  }
  if (escolha[0] == '1'){
    if (strcmp(bitcoin_usuario,"0.00") == 0){
      puts("Parece que você não possui Bitcoin!");
      ok = 't';
    }
    else{
      while (ok == 'f'){
        char numero = 'f', letra = 'f'; // variaveis de verificacao
        printf("\nDigite o valor que deseja vender em Bitcoin: ");
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
            if (double_valor > atof(bitcoin_usuario)){
              puts("Saldo insuficiente!");
              ok = 't';
            }
            else  { // VENDA DE BITCOIN
              double_real = double_valor * atof(cotacao_btc1); // valor em real do bitcoin
              double_real *= 0.97; // taxa de comissao
              real_atual = atof(real_usuario) + double_real; // valor TOTAL em real
              bitcoin_atual = atof(bitcoin_usuario) - double_valor; // valor TOTAL em bitcoin

              sprintf(real_usuario, "%.2lf", real_atual); // double para string
              sprintf(bitcoin_usuario, "%.6lf", bitcoin_atual); // double para string
              puts("Venda realizada com sucesso!");

             FILE *escreve8 = fopen(registro, "a"); 
             fprintf(escreve8, "\n");
             fprintf(escreve8, "%s_-_%.6lf_BTC__CT:_%s__TX:_0.03\n",horario, double_bitcoin,cotacao_btc1);
             fprintf(escreve8, "%s_REAL:_%.2lf__BTC:_%.6lf__XRP:_%s__ETH:_%s\n",horario, real_atual, bitcoin_atual, ripple_usuario,ethereum_usuario);
             fclose(escreve8);
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
  if (escolha[0] == '2'){
    if (strcmp(ripple_usuario,"0.00") == 0){
      puts("Parece que você não possui Ripple!");
      ok = 't';
    }
    else{
      while (ok == 'f'){
        char numero = 'f', letra = 'f'; // variaveis de verificacao
        printf("\nDigite o valor que deseja vender em Ripple: ");
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
            if (double_valor > atof(ripple_usuario)){
              puts("Saldo insuficiente!");
              ok = 't';
            }
            else  { // VENDA DE XRP
              double_real = double_valor * atof(cotacao_eth1); // valor em real do ripple
              double_real *= 0.99; // taxa de comissao
              real_atual = atof(real_usuario) + double_real; // valor TOTAL em real
              ripple_atual = atof(ripple_usuario) - double_valor; // valor TOTAL em ripple

              sprintf(real_usuario, "%.2lf", real_atual); // double para string
              sprintf(ripple_usuario, "%.6lf", ripple_atual); // double para string
              puts("Venda realizada com sucesso!");

              FILE *escreve9 = fopen(registro, "a"); 
               fprintf(escreve9, "\n");
              fprintf(escreve9, "%s_-_%.2lf_XRP__CT:_%s__TX:_0.01\n",horario, atof(valor),cotacao_rip1);
               fprintf(escreve9, "%s_REAL:_%.2lf__BTC:_%.6lf__XRP:_%s__ETH:_%s\n",horario, real_atual, bitcoin_atual, ripple_usuario,ethereum_usuario);
               fclose(escreve9);
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
  if (escolha[0] == '3'){
    if (strcmp(ethereum_usuario,"0.00") == 0){
      puts("Parece que você não possui Ethereum!");
      ok = 't';
    }
    else{
      while (ok == 'f'){
        char numero = 'f', letra = 'f'; // variaveis de verificacao
        printf("\nDigite o valor que deseja vender em Ethereum: ");
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
            if (double_valor > atof(ethereum_usuario)){
              puts("Saldo insuficiente!");
              ok = 't';
            }
            else  { // VENDA DE ETHEREUM
              double_real = double_valor * 14999.58; // valor em real do ethereum
              double_real *= 0.98; // taxa de comissao
              real_atual = atof(real_usuario) + double_real; // valor TOTAL em real
              ethereum_atual = atof(ethereum_usuario) - double_valor; // valor TOTAL em ethereum

              sprintf(real_usuario, "%.2lf", real_atual); // double para string
              sprintf(ethereum_usuario, "%.6lf", ethereum_atual); // double para string
              puts("Venda realizada com sucesso!");

              FILE *escreve10 = fopen(registro, "a"); 
               fprintf(escreve10, "\n");
              fprintf(escreve10, "%s_-_%.5lf_ETH__CT:_%s__TX:_0.02\n",horario, atof(valor),cotacao_eth1);
                fprintf(escreve10,"%s_REAL:_%.2lf__BTC:_%.6lf__XRP:_%s__ETH:_%s\n",horario, real_atual, bitcoin_atual, ripple_usuario,ethereum_usuario);
               fclose(escreve10);
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
}

void consultar_extrato(char *registro, char *nome, char *cpf){
  
  FILE *extrato = fopen(registro, "r");
  printf("\n%s\n",nome);
  printf("%s\n",cpf);
  char linha[2550];
  int i, pula_linha = 0;
  while (fgets(linha, 2550, extrato) != NULL){
    fscanf(extrato, "%s", linha);
    for (i = 0; i < strlen(linha); i++) {
      if (linha[i] == '_') {
        linha[i] = ' ';
      }
    }
    printf(" \n%s", linha);
    pula_linha++;
    if (pula_linha == 2){
      printf("\n");
      pula_linha = 0;
    }
  }
}

void atualizar_cotacao(char *cotacao_btc, char *cotacao_rip, char *cotacao_eth){
  srand(time(NULL));
  double variacao1;
  double variacao2;
  double variacao3;

  double cotacao_btc_double, cotacao_rip_double, cotacao_eth_double;
  variacao1 = rand() % 11;// 0 a 10
  variacao2 = rand() % 11;
  variacao3 = rand() % 11;

  variacao1 -= 5;// -5 a +5
  variacao2 -= 5;
  variacao3 -= 5;

  cotacao_btc_double = atof(cotacao_btc);// converte string p double
  cotacao_rip_double = atof(cotacao_rip);
  cotacao_eth_double = atof(cotacao_eth);

  variacao1 = 1 + (variacao1 / 100);// 1.05 a 0.95
  variacao2 = 1 + (variacao2 / 100);// 1.05 a 0.95
  variacao3 = 1 + (variacao3 / 100);// 1.05 a 0.95

  cotacao_btc_double *= variacao1;
  cotacao_rip_double *= variacao2;
  cotacao_eth_double *= variacao3;

  sprintf(cotacao_btc, "%.2lf", cotacao_btc_double);
  sprintf(cotacao_rip, "%.2lf", cotacao_rip_double);
  sprintf(cotacao_eth, "%.2lf", cotacao_eth_double);
  
  puts("Cotação atualizada!");
}

void cadastrar_investidor(Cadastro *usuarios, int *contador_cadastro){
  int i, j, tamanho, CPF_existente1 = 0, cpf_finder1;
  char verificar,confirmar[10],resposta[10];
  if (*contador_cadastro >= 10) {
    printf("O número máximo de contas foi atingido.\n\n");
    while (1){
      puts("Digite ENTER para continuar...");
      fgets(resposta, sizeof(resposta), stdin);
      if(strlen(resposta) == 1){
        break;
      }
    }
  }
  else{
    verificar = 'n'; // VARIÁVEL 'verificar' QUE VERIFICA SE A INFORMAÇÃO DADA ESTÁ CORRETA!
    while (verificar == 'n') {
      printf("Digite o nome completo do investidor: ");
      fgets(usuarios[*contador_cadastro].nome, sizeof(usuarios[*contador_cadastro].nome), stdin);
      if (strlen(usuarios[*contador_cadastro].nome) < 10 || strlen(usuarios[*contador_cadastro].nome) > 50) { // nome maior que 10 e menor que 50
        puts("Nome inválido!\n");
        continue;
      } else {
        for (i = 0; i < strlen(usuarios[*contador_cadastro].nome); i++) {
          if (usuarios[*contador_cadastro].nome[i] == ' ') {
            usuarios[*contador_cadastro].nome[i] = '_';
          } else if (usuarios[*contador_cadastro].nome[i] == '\n') {
            usuarios[*contador_cadastro].nome[i] = '\0';
          }
        }
        puts("Nome cadastrado!\n");
        verificar = 't';
      }
    }
    verificar = 'n';
    while (verificar == 'n') {
      printf("Digite uma senha de 6 dígitos do investidor: ");
      fgets(usuarios[*contador_cadastro].senha, sizeof(usuarios[*contador_cadastro].senha), stdin);
      tamanho = strlen(usuarios[*contador_cadastro].senha);
      if (tamanho != 7) {
        puts("A senha precisa ter 6 caracteres!\n");

        continue;
      } else {
        for (i = 0; i < strlen(usuarios[*contador_cadastro].senha); i++) {
          if (usuarios[*contador_cadastro].senha[i] == '\n') {
            usuarios[*contador_cadastro].senha[i] = '\0';
          }
        }
        puts("Senha cadastrada!\n");
        verificar = 't';
      }
    }
    verificar = 'n';
    while (verificar == 'n') {
      printf("Digite o CPF do investidor (formato: xxx.xxx.xxx-xx): ");
      fgets(usuarios[*contador_cadastro].CPF, sizeof(usuarios[*contador_cadastro].CPF), stdin);

      if (strlen(usuarios[*contador_cadastro].CPF) != 15) {
        puts("CPF inválido!\n");
        verificar = 'n';
      } 
      else {
        CPF_existente1 = 0;
        if (*contador_cadastro != 0){
          for (i = 0; i < 10; i++) {

            for (j = 0; j < 14; j++) {
              if (usuarios[i].CPF[j] == usuarios[*contador_cadastro].CPF[j]) {
                cpf_finder1 = 0;
              } // Comparador
              else {
                cpf_finder1 = 1;
                break;
              }
              if (j == 13 && cpf_finder1 == 0) {
                CPF_existente1++;
                break;
              }
            }
          }
        }
        if (CPF_existente1 == 2){
          puts("Esse CPF já foi cadastrado!\n"); 
          verificar = 'n';
        }
        else{
          for (i = 0; i < strlen(usuarios[*contador_cadastro].CPF); i++) {
            if (usuarios[*contador_cadastro].CPF[i] == '\n') {
              usuarios[*contador_cadastro].CPF[i] = '\0';              
            }
          }
          strcpy(usuarios[*contador_cadastro].tipo, "investidor");
          strcpy(usuarios[*contador_cadastro].real, "0.00");
          strcpy(usuarios[*contador_cadastro].BTC, "0.00");
          strcpy(usuarios[*contador_cadastro].RIP, "0.00");
          strcpy(usuarios[*contador_cadastro].ETH, "0.00");
          puts("CPF cadastrado!\n");
          verificar = 't';
        }
      }    
    }
    verificar = 'n'; 
    while (verificar == 'n') {
      printf("Deseja cadastrar essa conta? [S/N]: "); // CONFIRMACAO DE CADASTRO DE CONTA
      fgets(confirmar, sizeof(confirmar), stdin);
      if (confirmar[0] == 's'  && strlen(confirmar) == 2 || confirmar[0] == 'S' && strlen(confirmar) == 2) {
        // SALVAR STRUCT
        puts("\nConta cadastrada com sucesso!");


        FILE *escreve = fopen("usuarios.txt", "a"); // SALVA O CADSATRO NO TXT

        fprintf(
            escreve, "*;%s;%s;%s;%s;%s;%s;%s;%s;\n",usuarios[*contador_cadastro].tipo, usuarios[*contador_cadastro].CPF, usuarios[*contador_cadastro].senha,
            usuarios[*contador_cadastro].nome, usuarios[*contador_cadastro].real,usuarios[*contador_cadastro].BTC,usuarios[*contador_cadastro].RIP,usuarios[*contador_cadastro].ETH);
        
        fclose(escreve);
        *contador_cadastro += 1;
        verificar = 't';
        
      } else if (confirmar[0] == 'n'  && strlen(confirmar) == 2 ||
                 confirmar[0] == 'N' && strlen(confirmar) == 2) { // VOLTA AO INICIO DO PROGRAMA!
        puts("\nConta cancelada com sucesso!");
        verificar = 't';
      } else {
        puts("Opção inválida!\n");
      }
    }
  } // fim do else
}

void excluir_investidor(Cadastro *usuarios, int *contador_cadastros){
  char cpf_escolhido[20], confirmar[15], nome_mostra[50];
  int i, id = -1, tentativa = 0;
  while (1){
    if (tentativa == 0){
       printf("Digite o CPF do investidor: ");
    }
    else{
       printf("Digite o CPF do investidor ou digite 'CANCELAR' para voltar: ");
    }
    fgets(cpf_escolhido, sizeof(cpf_escolhido), stdin);
    cpf_escolhido[strcspn(cpf_escolhido, "\n")] = '\0';
    if (strcmp(cpf_escolhido, "CANCELAR") == 0){
      break;
    }
    for (i = 0; i < *contador_cadastros; i++){
      if (strcmp(usuarios[i].CPF, cpf_escolhido) == 0){
        id = i;
        break;
      }
    }
    if (id == -1){
      puts("CPF não encontrado!\n");
      tentativa++;
    }
    else{
      break;
    }
  } // fim while
  if (id != -1){ 
    if (usuarios[i].tipo[0] == 'i'){ // se for investidor exclui
      nome(nome_mostra, usuarios[id].nome); 
      printf("\nNome: %s\n", nome_mostra);
      printf("CPF: %s\n", usuarios[id].CPF);
      printf("Senha: ***%c%c%c\n",usuarios[id].senha[3],usuarios[id].senha[4],usuarios[id].senha[5]);
      printf("Saldo: R$%.2lf\n", atof(usuarios[id].real));

      
      while (1){ // loop de confirmacao/rejeicao de exclusao de conta
        puts("\nDigite 'CONFIRMAR' para a excluir a conta.\nDigite 'CANCELAR' para cancelar a exclusão da conta.");
        fgets(confirmar, sizeof(confirmar), stdin);
        confirmar[strcspn(confirmar, "\n")] = '\0';
        if(strcmp(confirmar, "CONFIRMAR") == 0 || strcmp(confirmar, "CANCELAR") == 0){
          break;
        }
      }
      if (strcmp(confirmar, "CANCELAR") == 0){
        puts("\nExclusão cancelada com êxito!");
      }
      else{
        for (i = id; i < *contador_cadastros - 1; i++) {
          usuarios[i] = usuarios[i + 1]; // desloca os elementos para a esquerda, duplicando cada perfil dps do id
        }
        (*contador_cadastros)--; // exclui o ultimo indice que seria uma duplicata
        FILE *escreve = fopen("usuarios.txt", "w"); // atualiza na funcao caso o codigo seja fechado errado
        fprintf(escreve, "\n");
        for(i = 0; i < *contador_cadastros; i++){     
          fprintf( escreve, "*;%s;%s;%s;%s;%s;%s;%s;%s;\n",usuarios[i].tipo, usuarios[i].CPF, usuarios[i].senha,
          usuarios[i].nome, usuarios[i].real, usuarios[i].BTC, usuarios[i].RIP, usuarios[i].ETH);   
        }
        fclose(escreve);
      printf("Conta excluída com sucesso!\n");
      }
    }
    else{
      puts("Este usuário não pode ser excluído!");
    }
  } // fim do if id != -1
}

void consultar_saldo_investidor(Cadastro *usuarios, int *contador_cadastros){
  char cpf_escolhido[20], confirmar[15], nome_mostra[51];
  int i, id = -1, tentativa = 0;
  while (1){
    if (tentativa == 0){
       printf("Digite o CPF do investidor: ");
    }
    else{
       printf("Digite o CPF do investidor ou digite 'CANCELAR' para voltar: ");
    }
    fgets(cpf_escolhido, sizeof(cpf_escolhido), stdin);
    cpf_escolhido[strcspn(cpf_escolhido, "\n")] = '\0';
    if (strcmp(cpf_escolhido, "CANCELAR") == 0){
      break;
    }
    for (i = 0; i < *contador_cadastros; i++){
      if (strcmp(usuarios[i].CPF, cpf_escolhido) == 0){
        id = i;
        break;
      }
    }
    if (id == -1){
      puts("CPF não encontrado!\n");
      tentativa++;
    }
    else{
      break;
    }
  } // fim while
  if (id != -1){
    nome(nome_mostra, usuarios[id].nome); 
    if (usuarios[id].tipo[0] == 'i'){ // se for investidor
      printf("\nSaldo de %s:\n\n",nome_mostra);
      printf("REAL: %.2lf\n", atof(usuarios[id].real));
      printf("BTC: %.2lf\n", atof(usuarios[id].BTC));
      printf("RIP: %.2lf\n", atof(usuarios[id].RIP));
      printf("ETH: %.2lf\n", atof(usuarios[id].ETH));
    }
    else{
      puts("Este perfil nao pode ser consultado!");
    }
  }
}

  void consultar_extrato_investidor(Cadastro *usuarios, int *contador_cadastros, char registros[10][15]){
  char registro[50], nome_mostra[51];
  char cpf_escolhido[20], confirmar[15];
  int i, id = -1, tentativa = 0;
  while (1){
    if (tentativa == 0){
       printf("Digite o CPF do investidor: ");
    }
    else{
       printf("Digite o CPF do investidor ou digite 'CANCELAR' para voltar: ");
    }
    fgets(cpf_escolhido, sizeof(cpf_escolhido), stdin);
    cpf_escolhido[strcspn(cpf_escolhido, "\n")] = '\0';
    if (strcmp(cpf_escolhido, "CANCELAR") == 0){
      break;
    }
    for (i = 0; i < *contador_cadastros; i++){
      if (strcmp(usuarios[i].CPF, cpf_escolhido) == 0){
        id = i;
        break;
      }
    }
    if (id == -1){
      puts("CPF não encontrado!\n");
      tentativa++;
    }
    else{
      break;
    }
  } // fim while
  if (id != -1){
    nome(nome_mostra, usuarios[id].nome); 
    
    if (usuarios[id].tipo[0] == 'i'){
      strcpy(registro, registros[id]);
      printf("\nConsultando extrato de %s...\n", nome_mostra);
      consultar_extrato(registro, nome_mostra, usuarios[id].CPF);
    }
    else{
      puts("Este perfil nao pode ser consultado!");
    }
  } // fim id != -1
}

void cadastrar_criptomoeda(Cripto *criptomoedas, int *total){
  char confirmar[10];   // no lugar do indice [0] sera o proximo indice disponivel
  int existe;
  if (*total >= 10){
    puts("Número total de criptomoedas atingido!");
  }
  else{
    while (1){
      existe = 0;
      strcpy(confirmar, "index");
      printf("Digite o nome da criptomoeda: ");
      fgets(criptomoedas[*total].nome, sizeof(criptomoedas[*total].nome), stdin);
      criptomoedas[*total].nome[strcspn(criptomoedas[*total].nome, "\n")] = '\0';
      
      for (int i = 0; i < strlen( criptomoedas[*total].nome); i++) { // deixa o input em maiusculo normalizado
        if (i ==0){
          criptomoedas[*total].nome[i] = toupper( criptomoedas[*total].nome[i]);
        }
        else{
          criptomoedas[*total].nome[i] = tolower( criptomoedas[*total].nome[i]);

        }
      }
      for (int i=0;i < *total; i++){ // verifica se a cripto ja existe
        if (strcmp(criptomoedas[*total].nome,criptomoedas[i].nome) == 0){
          existe = 1;
          break;
        }
      }
      if(existe == 1 || strcmp(criptomoedas[*total].nome, "Bitcoin") == 0 || strcmp(criptomoedas[*total].nome, "Ethereum") == 0 || strcmp(criptomoedas[*total].nome, "Ripple") == 0  ){
        puts("Essa criptomoeda já está no sistema!\n");
      }
      else{
        puts("\nDigite 1 para confirmar o nome da criptomoeda.");
        puts("Digite 2 para editar o nome da criptomoeda.");
        while (strcmp(confirmar, "1") != 0 && strcmp(confirmar, "2") != 0){
          fgets(confirmar,sizeof(confirmar),stdin);
          confirmar[strcspn(confirmar, "\n")] = '\0';
        }
        if (strcmp(confirmar, "1") == 0){
          break;
        }
        else{
          puts("");
        }
      }
    }
    puts("");
    while (1){
      existe = 0;
      strcpy(confirmar, "index");
      printf("Digite o ticker da criptomoeda (ex: BTC): ");
      fgets(criptomoedas[*total].ticker, sizeof(criptomoedas[*total].ticker), stdin);
      criptomoedas[*total].ticker[strcspn(criptomoedas[*total].ticker, "\n" )] = '\0';
      for (int i = 0; i < strlen( criptomoedas[*total].ticker); i++) { // deixa o input em maiusculo
        criptomoedas[*total].ticker[i] = toupper(criptomoedas[*total].ticker[i]);
      }
      for (int i = 0; i < *total; i++){
        if (strcmp(criptomoedas[*total].ticker, criptomoedas[i].ticker) == 0){
          existe = 1;
          break;
        }
      }
      if (existe == 1 || strcmp(criptomoedas[*total].ticker, "BTC") == 0 || strcmp(criptomoedas[*total].ticker, "ETH") == 0 || strcmp(criptomoedas[*total].ticker, "XRP") == 0  ){
        puts("Este ticker já está em uso!\n");
      }
      else{
        puts("\nDigite 1 para confirmar o ticker da criptomoeda.");
        puts("Digite 2 para editar o ticker da criptomoeda.");
        while (strcmp(confirmar, "1") != 0 && strcmp(confirmar, "2") != 0){
          fgets(confirmar,sizeof(confirmar),stdin);
          confirmar[strcspn(confirmar, "\n")] = '\0';
        }
        if (strcmp(confirmar, "1") == 0){
          break;
        }
        else{
          puts("");
        }
      }
    }
    puts("");
    while (1){
      printf("Digite a cotação da criptomoeda: ");
      fgets(criptomoedas[*total].cotacao, sizeof(criptomoedas[*total].cotacao),stdin);
      criptomoedas[*total].cotacao[strcspn(criptomoedas[*total].cotacao, "\n")] = '\0';
      if (numero(criptomoedas[*total].cotacao) == 1){
        break;
      }
    }
    puts("");
    while (1){
      printf("Digite a taxa de compra da criptomoeda: ");
      fgets(criptomoedas[*total].taxa_compra, sizeof(criptomoedas[*total].taxa_compra),stdin);
      criptomoedas[*total].taxa_compra[strcspn(criptomoedas[*total].taxa_compra, "\n")] = '\0';
      if (numero(criptomoedas[*total].taxa_compra) == 1){
        break;
      }
    }
    puts("");
    while (1){
      printf("Digite a taxa de venda da criptomoeda: ");
      fgets(criptomoedas[*total].taxa_venda, sizeof(criptomoedas[*total].taxa_venda),stdin);  
      criptomoedas[*total].taxa_venda[strcspn(criptomoedas[*total].taxa_venda, "\n")] = '\0';
      if (numero(criptomoedas[*total].taxa_venda) == 1){
        break;
      }
    }
    puts("");
    while (1){
      printf("Deseja cadastrar essa criptomoeda? [S/N]: ");
      fgets(confirmar, sizeof(confirmar), stdin);
      confirmar[strcspn(confirmar, "\n")] = '\0';
      if (strcmp(confirmar, "S") == 0 || strcmp(confirmar, "s") == 0){
        FILE *arq = fopen("criptomoeda.txt", "a");  // Abrir no modo append
          if (arq == NULL) {
              printf("Erro ao abrir o arquivo para salvar a criptomoeda!\n");
          }
        fprintf(
        arq, "*;%s;%s;%s;%s;%s;\n",criptomoedas[*total].nome, criptomoedas[*total].ticker, criptomoedas[*total].cotacao,criptomoedas[*total].taxa_compra,criptomoedas[*total].taxa_venda);
        fclose(arq);
        puts("\nCriptomoeda cadastrada com sucesso!");
        (*total)++;
        break;
      }
      else if (strcmp(confirmar, "N") == 0 || strcmp(confirmar, "n") == 0){
        puts("\nCriptomoeda cancelada com sucesso!");
        break;
      }
      else{
        puts("Resposta inválida!\n");
      }
    }
  }
}

void excluir_criptomoeda(Cripto *criptomoedas, int *total){
  char crip[30];
  char confirmar[15];
  int id = -1, tentativa = 0;
  while (1){
    if (tentativa == 0){
      printf("Digite o nome da criptomoeda que deseja excluir: ");
    }
    else{
      printf("Digite o nome da criptomoeda ou digite 'CANCELAR' para cancelar a exclusão: ");
    }
    fgets(crip, sizeof(crip), stdin);
    crip[strcspn(crip, "\n")] = '\0';
    if (strcmp(crip, "CANCELAR") == 0 || strcmp(crip, "cancelar") == 0){
      break;
    }
    else{
      for (int i = 0; i < strlen(crip); i++) { // normaliza o input - primeira letra maiuscula e o resto minuscula
          if (i == 0) {
              crip[i] = toupper(crip[i]);
          } else {
              crip[i] = tolower(crip[i]);
          }
      }
    
    
    
      for (int i = 0; i < *total; i++){
        if (strcmp(criptomoedas[i].nome, crip) == 0){
          id = i;
          break;
        }
      }
      if(strcmp(crip, "Bitcoin") == 0 || strcmp(crip, "Ripple") == 0 || strcmp(crip, "Ethereum") == 0 ){
        puts("Essa criptomoeda não pode ser excluída!\n");
        tentativa++;
      }
      else if (id == -1){
        puts("Criptomoeda não encontrada!\n");
        tentativa++;
      }
     
      else{
        break;
      }
    }
  }
  if (id != -1){
    printf("\nNome: %s (%s)\n\n",criptomoedas[id].nome,criptomoedas[id].ticker);
    printf("Cotação: %s\n",criptomoedas[id].cotacao);
    printf("Taxa de compra: %s\n",criptomoedas[id].taxa_compra);
    printf("Taxa de venda: %s\n\n",criptomoedas[id].taxa_venda);
    while (1){
      puts("Digite 'CONFIRMAR' para confirmar a exclusão da criptomoeda");
      puts("Digite 'CANCELAR' para cancelar a exclusão da criptomoeda");
      fgets(confirmar, sizeof(confirmar), stdin);
      confirmar[strcspn(confirmar, "\n")] = '\0';
      if (strcmp(confirmar, "CONFIRMAR") == 0 || strcmp(confirmar, "CANCELAR") == 0){
        break;
      }
    }
    if (strcmp(confirmar, "CANCELAR") == 0){
      puts("\nExclusão cancelada com êxito!");
    }
    else{
      for (int i = id; i < *total - 1; i++) {
        criptomoedas[i] = criptomoedas[i + 1]; // desloca os elementos para a esquerda, duplicando cada perfil dps do id
      }
      (*total)--; // exclui o ultimo indice que seria uma duplicata
      FILE *escreve = fopen("criptomoeda.txt", "w"); // atualiza na funcao caso o codigo seja fechado errado
      for(int i = 0; i < *total; i++){
        fprintf(escreve, "*;%s;%s;%s;%s;%s;\n", criptomoedas[i].nome, criptomoedas[i].ticker, criptomoedas[i].cotacao, criptomoedas[i].taxa_compra, criptomoedas[i].taxa_venda);
      }
    fclose(escreve);
    printf("\nCriptomoeda excluída com sucesso!\n");
    }
  }
  
}


int numero(char input[]){
  int i;
  char letra = 'f', numero = 'f';
  for (i = 0; i < strlen(input);i++){
    if ( !isdigit(input[i])){ // verificacao de caracter (caso tenha letras) e numero negativo
      if (input[i] != '.' && input[i] != ','|| numero == 'f'){
        letra = 't';
      }
      else if (input[i] == ','){
        input[i] = '.'; // muda a virgula para um ponto
      }
    }
    else{
      numero = 't'; // caso o usuario digite apenas '.' o programa entendera que esta errado!
    }
  }
  if (letra != 'f'){
    puts("Valor inválido!\n");
    return 0;
  }
  else{
    if (atof(input) > 0){ // se o valor for = 0 nao funcionara!
      return 1;
    }
    else{
      puts("Valor inválido!\n");
      return 0;
    }
  }
}

