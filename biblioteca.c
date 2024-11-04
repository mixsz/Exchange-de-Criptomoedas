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
