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

  variacao1 -= 5;
  variacao2 -= 5;
  variacao3 -= 5;

  cotacao_btc_double = atof(cotacao_btc);
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
