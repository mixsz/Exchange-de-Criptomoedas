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
        fprintf(escreve4, "%s:___+R$%s\n",horario, real_depositado);
        fprintf(escreve4, "%s:___R$%.2lf___BTC:%s___RIP:%s___ETH:%s",horario, valor, bitcoin, ripple, ethereum);
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
              fprintf(escreve4, "%s:___-R$%s\n",horario, real_sacado);
              fprintf(escreve4, "%s:___R$%.2lf___BTC:%s___RIP:%s___ETH:%s",horario, valor, bitcoin, ripple, ethereum);
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

void comprar_criptomoeda(char *real_usuario, char *bitcoin_usuario, char *ripple_usuario, char *ethereum_usuario,char *registro){
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
    puts("\n1. Bitcoin   - Cotação: 357340.87"); //COTACAO MUDA AO ATUALIZAR COTACAO - TRANSFORMAR EM VARIAVEL CT
    puts("2. Ripple    - Cotação: 3.36");
    puts("3. Ethereum  - Cotação: 14999.58");
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
            double_bitcoin = double_valor / 357340.87; // valor em bitcoin comprado
            double_bitcoin = double_bitcoin * 0.98; // taxa de comissao
            bitcoin_atual = atof(bitcoin_usuario) + double_bitcoin; // valor TOTAL em bitcoin
            valor_atual = atof(real_usuario) - double_valor; // valor TOTAL em real

            sprintf((real_usuario), "%.2lf", valor_atual); // double para string
            sprintf(bitcoin_usuario, "%.6lf", bitcoin_atual); // double para string
            puts("Compra realizada com sucesso!");

            FILE *escreve5 = fopen(registro, "a"); 
            fprintf(escreve5, "\n");
            fprintf(escreve5, "%s:___-R$%.2lf\n",horario, double_valor);
            fprintf(escreve5, "%s:___R$%.2lf___BTC:%.6lf___RIP:%s___ETH:%s",horario, valor_atual, bitcoin_atual, ripple_usuario,ethereum_usuario);
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
            double_ripple = double_valor / 3.36; // valor em ripple comprado
            double_ripple = double_ripple * 0.99; // taxa de comissao
            ripple_atual = atof(ripple_usuario) + double_ripple; // valor TOTAL em ripple
            valor_atual = atof(real_usuario) - double_valor; // valor TOTAL em real

            sprintf((real_usuario), "%.2lf", valor_atual); // double para string
            sprintf(ripple_usuario, "%.6lf", ripple_atual); // double para string
            FILE *escreve6 = fopen(registro, "a"); 
            fprintf(escreve6, "\n");
            fprintf(escreve6, "%s:___-R$%.2lf\n",horario, double_valor);
            fprintf(escreve6, "%s:___R$%.2lf___BTC:%s___RIP:%.6lf___ETH:%s",horario, valor_atual, bitcoin_usuario, ripple_atual, ethereum_usuario);
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
            double_ethereum = double_valor / 14999.58; // valor em ethereum comprado
            double_ethereum = double_ethereum * 0.99; // taxa de comissao
            ethereum_atual = atof(ethereum_usuario) + double_ethereum; // valor TOTAL em ethereum
            valor_atual = atof(real_usuario) - double_valor; // valor TOTAL em real

            sprintf((real_usuario), "%.2lf", valor_atual); // double para string
            sprintf(ethereum_usuario, "%.6lf", ethereum_atual); // double para string
            FILE *escreve7 = fopen(registro, "a"); 
            fprintf(escreve7, "\n");
            fprintf(escreve7, "%s:___-R$%.2lf\n",horario, double_valor);
            fprintf(escreve7, "%s:___R$%.2lf___BTC:%s___RIP:%s___ETH:%.6lf", horario, valor_atual, bitcoin_usuario, ripple_usuario, ethereum_atual);
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

void vender_criptomoeda(char *real_usuario, char *bitcoin_usuario, char *ripple_usuario, char *ethereum_usuario,char *registro){
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
    puts("\n1. Bitcoin   - Cotação: 357340.87"); //COTACAO MUDA AO ATUALIZAR COTACAO - TRANSFORMAR EM VARIAVEL CT
    puts("2. Ripple    - Cotação: 3.36");
    puts("3. Ethereum  - Cotação: 14999.58");
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
              double_real = double_valor * 357340.87; // valor em real do bitcoin
              double_real *= 0.97; // taxa de comissao
              real_atual = atof(real_usuario) + double_real; // valor TOTAL em real
              bitcoin_atual = atof(bitcoin_usuario) - double_valor; // valor TOTAL em bitcoin

              sprintf(real_usuario, "%.2lf", real_atual); // double para string
              sprintf(bitcoin_usuario, "%.6lf", bitcoin_atual); // double para string
              puts("Venda realizada com sucesso!");

             FILE *escreve8 = fopen(registro, "a"); 
             fprintf(escreve8, "\n");
             fprintf(escreve8, "%s:___-BTC:%.6lf\n", horario, double_valor);
             fprintf(escreve8, "%s:___+R$%.2lf\n", horario, double_real);
             fprintf(escreve8, "%s:___R$%.2lf___BTC:%.6lf___RIP:%s___ETH:%s", horario, real_atual, bitcoin_atual, ripple_usuario, ethereum_usuario);
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
              double_real = double_valor * 3.36; // valor em real do ripple
              double_real *= 0.99; // taxa de comissao
              real_atual = atof(real_usuario) + double_real; // valor TOTAL em real
              ripple_atual = atof(ripple_usuario) - double_valor; // valor TOTAL em ripple

              sprintf(real_usuario, "%.2lf", real_atual); // double para string
              sprintf(ripple_usuario, "%.6lf", ripple_atual); // double para string
              puts("Compra realizada com sucesso!");

              FILE *escreve9 = fopen(registro, "a"); 
               fprintf(escreve9, "\n");
               fprintf(escreve9, "%s:___-RIP:%.6lf\n", horario, double_valor);
               fprintf(escreve9, "%s:___+R$%.2lf\n", horario, double_real);
               fprintf(escreve9, "%s:___R$%.2lf___BTC:%s___RIP:%.6lf___ETH:%s", horario, real_atual, bitcoin_usuario, ripple_atual, ethereum_usuario);
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
            if (double_valor > atof(ripple_usuario)){
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
              puts("Compra realizada com sucesso!");

              FILE *escreve10 = fopen(registro, "a"); 
               fprintf(escreve10, "\n");
               fprintf(escreve10, "%s:___-ETH:%.6lf\n", horario, double_valor);
               fprintf(escreve10, "%s:___+R$%.2lf\n", horario, double_real);
               fprintf(escreve10, "%s:___R$%.2lf___BTC:%s___RIP:%s___ETH:%.6lf", horario, real_atual, bitcoin_usuario, ripple_usuario, ethereum_atual);
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

void consultar_extrato(char *registro){

  FILE *extrato = fopen(registro, "r");

  char linha[2550];
  int i;
  while (fgets(linha, 2550, extrato) != NULL)
  {
    fscanf(extrato, "%s", linha);
    for (i = 0; i < strlen(linha); i++) {      
    }
    printf(" \n%s", linha);
  }
}
