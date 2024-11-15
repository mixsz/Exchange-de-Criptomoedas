#include "biblioteca.h"


int main() {
  
  char resposta1[30];
  char cotacao_btc[30];
  char cotacao_rip[30];
  char cotacao_eth[30];
  setlocale(LC_ALL, "portuguese");
  char sair = 'f', bemvindo = 't', oi = 't';
  char resposta[10], confirmar[10], cpflogin[16], senhalogin[15], opcao[10], nome_mostra[51];
  Cadastro usuarios[10];
  Cripto criptomoedas[10];
  int tamanho, i, j;
  char verificar = 'n', login = 'f', menu = 't';
  int contador = 0;
  int contador_cadastros = 0, escolha_menu;
  int PT = 0;                      // CONTADOR DE PONTO E VÍRGULA
  int contador_nome, contador_CPF, contador_senha, contador_real,contador_btc, contador_ripple, contador_eth, contador_tipo;
  int permissao_acesso = 1, CPF_existente = 1,CPF_existente1 = 0,permissao_funcao = 1;
  int indice_usuario = -1, cpf_finder, cpf_finder1,
      senha_finder; // variaveis que comparam se o cpf e a senha existem nos

                    // dados armazenados
  char registros[10][15] ={"registro0.txt","registro1.txt","registro2.txt","registro3.txt","registro4.txt","registro5.txt","registro6.txt","registro7.txt","registro8.txt","registro9.txt"};
  char registro[15];

  
  FILE *arquivo_moedas = fopen("cotacao.txt", "r");
  char linha1[2550];
  PT = 0;
  while (fgets(linha1, 2550, arquivo_moedas) != NULL){
    PT++; 
    fscanf(arquivo_moedas, "%s", linha1);
    for (i = 0; i < strlen(linha1) - 1; i++){
      switch(PT){
        case 1:
          cotacao_btc[i] = linha1[i];
          cotacao_btc[i+1] = '\0';
          break; 
        case 2:
          cotacao_rip[i] = linha1[i];
          cotacao_rip[i+1] = '\0';
          break;
        case 3:
          cotacao_eth[i] = linha1[i];
          cotacao_eth[i+1] = '\0';
          break;
      }     
    } 
  }
  fclose(arquivo_moedas);

  int total_criptomoedas = 0; 

  FILE *arq = fopen("criptomoeda.txt", "r");
  if (arq == NULL) {
      printf("Erro ao abrir o arquivo de criptomoedas!\n");
      return 1;
  }

  char linha3[200];  

  while (fgets(linha3, sizeof(linha3), arq)) {
      linha3[strcspn(linha3, "\n")] = '\0';
    
      if (linha3[0] == '*') {
          char *token = strtok(linha3 + 1, ";");

          int indice = total_criptomoedas;

          if (token != NULL) {
              strcpy(criptomoedas[indice].nome, token);
              token = strtok(NULL, ";");
          }
          if (token != NULL) {
              strcpy(criptomoedas[indice].ticker, token);
              token = strtok(NULL, ";");
          }
          if (token != NULL) {
              strcpy(criptomoedas[indice].cotacao, token);
              token = strtok(NULL, ";");
          }
          if (token != NULL) {
              strcpy(criptomoedas[indice].taxa_compra, token);
              token = strtok(NULL, ";");
          }
          if (token != NULL) {
              strcpy(criptomoedas[indice].taxa_venda, token);
          }

          // Incrementa o total de criptomoedas lidas
          total_criptomoedas++;

          // Limita o número de criptomoedas a 10
          if (total_criptomoedas >= 10) {
              break;
          }
      }
  }

  fclose(arq);  // Fecha o arquivo

  // printf("%d numero total\n",total_criptomoedas);



  FILE *ler = fopen("usuarios.txt", "r"); // Lê o arquivo de usuários
  if (ler == NULL) {
      printf("Erro ao abrir o arquivo usuarios.txt\n");
      return 1;
  }

  contador_cadastros = 0; // Contador de cadastros lidos
  char linha[2550]; // Variável que armazena temporariamente os cadastros do TXT

  while (fgets(linha, sizeof(linha), ler) != NULL) { // Loop que lê separadamente os cadastros separados por \n
      contador_tipo = 0;
      contador_CPF = 0;
      contador_nome = 0;
      contador_senha = 0;
      contador_real = 0;
      contador_btc = 0;
      contador_ripple = 0;
      contador_eth = 0;
      PT = 0; // Contador de ponto e vírgula

      // Limpa os dados do usuário
      for (int i = 0; i < 10; i++) {
          usuarios[contador_cadastros].criptomoedas[i].nome[0] = '\0';
          usuarios[contador_cadastros].criptomoedas[i].ticker[0] = '\0';
          usuarios[contador_cadastros].criptomoedas[i].cotacao[0] = '\0';
          usuarios[contador_cadastros].criptomoedas[i].taxa_compra[0] = '\0';
          usuarios[contador_cadastros].criptomoedas[i].taxa_venda[0] = '\0';
          usuarios[contador_cadastros].criptomoedas[i].saldo[0] = '\0';
      }

      // Preenche os dados do usuário
      int criptomoeda_index = 0; // Inicia o índice para as criptomoedas
      for (int i = 0; i < strlen(linha); i++) { 
          if (linha[i] == '*') {
              contador_cadastros++;
          }
      }

      PT = 0;
      for (int i = 0; i < strlen(linha); i++) { 
          if (linha[i] == ';') {
              PT++; // Incrementa o contador quando encontra o delimitador ';'
          } else if (linha[i] == '*') {
              continue;
          } else {
              switch (PT) {
                  case 1:
                      usuarios[contador_cadastros - 1].tipo[contador_tipo] = linha[i];
                      usuarios[contador_cadastros - 1].tipo[contador_tipo + 1] = '\0';
                      contador_tipo++;
                      break;
                  case 2:
                      usuarios[contador_cadastros - 1].CPF[contador_CPF] = linha[i];
                      usuarios[contador_cadastros - 1].CPF[contador_CPF + 1] = '\0';
                      contador_CPF++;
                      break;
                  case 3:
                      usuarios[contador_cadastros - 1].senha[contador_senha] = linha[i];
                      usuarios[contador_cadastros - 1].senha[contador_senha + 1] = '\0';
                      contador_senha++;
                      break;
                  case 4:
                      usuarios[contador_cadastros - 1].nome[contador_nome] = linha[i];
                      usuarios[contador_cadastros - 1].nome[contador_nome + 1] = '\0';
                      contador_nome++;
                      break;
                  case 5:
                      usuarios[contador_cadastros - 1].real[contador_real] = linha[i];
                      usuarios[contador_cadastros - 1].real[contador_real + 1] = '\0';
                      contador_real++;
                      break;
                  case 6:
                    usuarios[contador_cadastros - 1].BTC[contador_btc] = linha[i];
                    usuarios[contador_cadastros - 1].BTC[contador_btc + 1] = '\0';
                    contador_btc++;
                    break;
                  case 7:
                    usuarios[contador_cadastros - 1].RIP[contador_ripple] = linha[i];
                    usuarios[contador_cadastros - 1].RIP[contador_ripple + 1] = '\0';
                    contador_ripple++;
                    break;
                  case 8:
                    usuarios[contador_cadastros - 1].ETH[contador_eth] = linha[i];
                    usuarios[contador_cadastros - 1].ETH[contador_eth + 1] = '\0';
                    contador_eth++;
                    break;
                  default:
                    break;
              }
          }

        if (PT >= 9 && criptomoeda_index < 10) {
            // Encontrar o próximo valor que não seja BTC, ETH ou RIP
            if (linha[i] != ';') {
                int saldo_index = 0;
                while (linha[i] != ';' && linha[i] != '\0' && saldo_index < sizeof(usuarios[contador_cadastros - 1].criptomoedas[criptomoeda_index].saldo) - 1) {
                    usuarios[contador_cadastros - 1].criptomoedas[criptomoeda_index].saldo[saldo_index] = linha[i];
                    saldo_index++;
                    i++;
                }
                // Garantir que a string 'saldo' seja terminada corretamente
                usuarios[contador_cadastros - 1].criptomoedas[criptomoeda_index].saldo[saldo_index] = '\0';
                criptomoeda_index++;
            }
        }
      }
  }

  fclose(ler);
  
  // PRINT DE TODAS AS INFORMACOES DE CADA PERFIL:
    
  // for (i = 0; i < contador_cadastros; i++){
  //   printf("%s\n",usuarios[i].nome);
  //   printf("CPF: %s\n",usuarios[i].CPF);
  //   printf("Tipo: %s\n",usuarios[i].tipo);
  //   printf("Senha: %s\n",usuarios[i].senha);
  //   printf("Real: %s\n",usuarios[i].real);
  //   printf("BTC: %s\n",usuarios[i].BTC);
  //   printf("ETH: %s\n",usuarios[i].ETH);
  //   printf("XRP: %s\n",usuarios[i].RIP);
  //   for (j = 0; j < total_criptomoedas; j++){
  //     printf("%s: %s\n",criptomoedas[j].nome, usuarios[i].criptomoedas[j].saldo);
  //   }
  // }
  

  FILE *escreve1 = fopen("usuarios.txt", "a"); 
  if (contador_cadastros == 0){
  fprintf(escreve1, "\n");}
  fclose(escreve1);
  int mostrar = 1;
  int inicio = 1;

  while (sair != 't') { 
    if (inicio == 1){
      while(1) {
        if (mostrar == 1){
          printf("                    Menu Principal\n");
          printf("                    ---- ---------\n");
          puts("1. Investidor");
          puts("2. Administrador");
          puts("3. Sair");
        }
        printf("\nDigite o tipo de usuário: ");
        fgets(resposta, sizeof(resposta), stdin);
  
        if (resposta[0] == '1'&& strlen(resposta) == 2){
          puts("");
          escolha_menu = 1;
          puts("");
          break;
        }
        else if (resposta[0] == '2'&& strlen(resposta) == 2){
          puts("");
          escolha_menu = 2;
          puts("");
          break;
        }
        else if (resposta[0] == '3'&& strlen(resposta) == 2){
          puts("\nAté a próxima!\n");
          escolha_menu = -1;
          break;
        }
        else {
          puts("Resposta inválida!");
          mostrar = 0;
        }
      }
    }
    inicio = 0;
    int NV = contador_cadastros; // Novo Cadastro
    if (escolha_menu == 1){
      puts("                      Investidor");
      puts("~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~");
      printf("1. Criar conta \n");
      printf("2. Acessar conta\n");
      printf("3. Voltar\n");
      printf("4. Sair\n");
      if (bemvindo == 't'){
        printf("\nBem-vindo! Digite a opção desejada: ");
      }
      else{
        printf("\nDigite a opção desejada: ");
      }
      fgets(resposta, sizeof(resposta), stdin);
      puts("");
  
      if (resposta[0] == '1' && strlen(resposta) == 2) { // Cadastra conta
        if (contador_cadastros >= 10) {
          printf("Número máximo de contas atingido.\n\n");
          while (1){
            puts("Digite ENTER para continuar...");
            fgets(resposta, sizeof(resposta), stdin);
            if(strlen(resposta) == 1){
              break;
            }
          }
          bemvindo = 'f';
  
        }
        else{
          verificar = 'n'; // VARIÁVEL 'verificar' QUE VERIFICA SE A INFORMAÇÃO DADA ESTÁ CORRETA!
          while (verificar == 'n') {
            printf("Digite seu nome completo: ");
            fgets(usuarios[NV].nome, sizeof(usuarios[NV].nome), stdin);
            if (strlen(usuarios[NV].nome) < 10 || strlen(usuarios[NV].nome) > 50) { // nome maior que 10 e menor que 50
              puts("Nome inválido!\n");
              continue;
            } else {
              for (i = 0; i < strlen(usuarios[NV].nome); i++) {
                if (usuarios[NV].nome[i] == ' ') {
                  usuarios[NV].nome[i] = '_';
                } else if (usuarios[NV].nome[i] == '\n') {
                  usuarios[NV].nome[i] = '\0';
                }
              }
              puts("Nome cadastrado!\n");
              verificar = 't';
            }
          }
          verificar = 'n';
          while (verificar == 'n') {
            printf("Digite uma senha de 6 dígitos: ");
            fgets(usuarios[NV].senha, sizeof(usuarios[NV].senha), stdin);
            tamanho = strlen(usuarios[NV].senha);
            if (tamanho != 7) {
              puts("A senha precisa ter 6 caracteres!\n");
  
              continue;
            } else {
  
              for (i = 0; i < strlen(usuarios[NV].senha); i++) {
                if (usuarios[NV].senha[i] == '\n') {
                  usuarios[NV].senha[i] = '\0';
                }
              }
              // troca o \n por ;
  
              puts("Senha cadastrada!\n");
              verificar = 't';
            }
          }
          verificar = 'n';
          while (verificar == 'n') {
            printf("Digite seu CPF (formato de CPF: xxx.xxx.xxx-xx): ");
            fgets(usuarios[NV].CPF, sizeof(usuarios[NV].CPF), stdin);
  
            if (strlen(usuarios[NV].CPF) != 15) {
              puts("CPF inválido!\n");
              verificar = 'n';
            } 
            else {
              CPF_existente1 = 0;
              if (contador_cadastros != 0){
                for (i = 0; i < 10; i++) {
  
                  for (j = 0; j < 14; j++) {
                    if (usuarios[i].CPF[j] == usuarios[NV].CPF[j]) {
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
                for (i = 0; i < strlen(usuarios[NV].CPF); i++) {
                  if (usuarios[NV].CPF[i] == '\n') {
                    usuarios[NV].CPF[i] = '\0';              
                  }
                }
                strcpy(usuarios[NV].tipo, "investidor");
                strcpy(usuarios[NV].real, "0.00");
                strcpy(usuarios[NV].BTC, "0.00");
                strcpy(usuarios[NV].RIP, "0.00");
                strcpy(usuarios[NV].ETH, "0.00");
                for (i = 0; i < total_criptomoedas; i++){
                  strcpy(usuarios[NV].criptomoedas[i].saldo, "0.00");
                }
                puts("CPF cadastrado!\n");
                verificar = 't';
              }
            }    
          }
          verificar = 'n'; 
          while (verificar == 'n') {
            printf("Deseja cadastrar a conta? [S/N]: "); // CONFIRMACAO DE CADASTRO DE CONTA
            fgets(confirmar, sizeof(confirmar), stdin);
            if (confirmar[0] == 's'  && strlen(confirmar) == 2 || confirmar[0] == 'S' && strlen(confirmar) == 2) {
              // SALVAR STRUCT
              puts("\nConta cadastrada com sucesso!\n");
  
  
              FILE *escreve = fopen("usuarios.txt", "a"); // SALVA O CADSATRO NO TXT
  
              fprintf(
                  escreve, "*;%s;%s;%s;%s;%s;%s;%s;%s;",usuarios[NV].tipo, usuarios[NV].CPF, usuarios[NV].senha,
                  usuarios[NV].nome, usuarios[NV].real,usuarios[NV].BTC,usuarios[NV].RIP,usuarios[NV].ETH); // ADICIONA O %X E ESCREVE O USUARIO[NV].XXXX
              for (int i = 0; i < total_criptomoedas; i++) {
                  fprintf(escreve, "%s;", usuarios[NV].criptomoedas[i].saldo);
              }
              fprintf(escreve, "\n");
              
  
              fclose(escreve);
  
              contador_cadastros++;
  
  
              verificar = 't';
            } else if (confirmar[0] == 'n'  && strlen(confirmar) == 2 ||
                       confirmar[0] == 'N' && strlen(confirmar) == 2) { // VOLTA AO INICIO DO PROGRAMA!
              puts("\nConta cancelada com sucesso!\n");
              verificar = 't';
            } else {
              puts("Opção inválida!\n");
            }
          }
        }
      } else if (resposta[0] == '2' && strlen(resposta) == 2) { // Acessar a conta
        verificar = 't';
        // login = 'f';
        while (verificar == 't') {
          printf("Digite seu CPF: ");
          fgets(cpflogin, sizeof(cpflogin), stdin);
          cpflogin[strcspn(cpflogin, "\n")] = '\0';
          for (i = 0; i < contador_cadastros; i++){
            if (strcmp(cpflogin, usuarios[i].CPF) == 0){
              verificar = 'f';
              indice_usuario = i;
              break;
            }
          }
          if (verificar == 't'){
            puts("CPF não encontrado!\n");
          }
        }
        verificar = 'f';
        while (verificar == 'f'){
          printf("Digite sua senha: ");
          fgets(senhalogin, sizeof(senhalogin), stdin);
          senhalogin[strcspn(senhalogin, "\n")] = '\0';
          if (strcmp(senhalogin, usuarios[indice_usuario].senha) == 0){
            if (strcmp(usuarios[indice_usuario].tipo, "investidor") == 0){
              verificar = 't';
              permissao_acesso = 0;
            }
            else{
              verificar = 't';
              puts("\nEste usuário não tem permissão para acessar o menu de investimentos.\nVocê será redirecionado ao menu.\n");
              while (1){
                puts("Digite ENTER para continuar...");
                fgets(resposta, sizeof(resposta), stdin);
                if(strlen(resposta) == 1){
                  break;
                }
              }
                
            }
          }
          else{
            puts("Senha incorreta!\n");
          }
        }
        
        if (permissao_acesso == 0) {  
          
          strcpy(registro, registros[indice_usuario]);
          
          i = 0;
          while(usuarios[indice_usuario].nome[i] != '\0'){
  
            if (usuarios[indice_usuario].nome[i] == '_') {
                nome_mostra[i] = ' ';
              }
            else{
              nome_mostra[i] = usuarios[indice_usuario].nome[i];
            }
            i++;
          }
          nome_mostra[i] = '\0';
  
          while (menu == 't') {
          
            FILE *nova_cotacao = fopen("cotacao.txt", "w");
            fprintf(nova_cotacao, "\n");
            fprintf(nova_cotacao, "%s;\n%s;\n%s;", cotacao_btc, cotacao_rip, cotacao_eth);
            fclose(nova_cotacao);
          

            FILE *escreve2 = fopen("usuarios.txt", "w"); // Abre o arquivo para sobrescrever o conteúdo

            fprintf(escreve2, "\n");

            for (i = 0; i < contador_cadastros; i++) {
                // Escreve as informações do usuário
                fprintf(escreve2, "*;%s;%s;%s;%s;%s;%s;%s;%s;", 
                    usuarios[i].tipo, 
                    usuarios[i].CPF, 
                    usuarios[i].senha,
                    usuarios[i].nome, 
                    usuarios[i].real,
                    usuarios[i].BTC,
                    usuarios[i].RIP, 
                    usuarios[i].ETH
                );

                for (int j = 0; j < total_criptomoedas; j++) {
                    fprintf(escreve2, "%s;", usuarios[i].criptomoedas[j].saldo);
                }

                // Finaliza o registro do usuário com uma nova linha
                fprintf(escreve2, "\n");
            }

            fclose(escreve2); // Fecha o arquivo

            FILE *escrevendoo = fopen("criptomoeda.txt", "w");
            for(i = 0; i < total_criptomoedas; i++){
              fprintf(escrevendoo, "*;%s;%s;%s;%s;%s;\n", criptomoedas[i].nome, criptomoedas[i].ticker, criptomoedas[i].cotacao, criptomoedas[i].taxa_compra, criptomoedas[i].taxa_venda);
            }
            fclose(escrevendoo);
            
            puts("");
            puts("1. Consultar saldo");
            puts("2. Consultar extrato");
            puts("3. Depositar");
            puts("4. Sacar");
            puts("5. Comprar criptomoedas");
            puts("6. Vender criptomoedas");
            puts("7. Atualizar cotação");
            puts("8. Sair");
            puts("");
            if (oi == 't') {
              printf("Olá Sr(a) %s! Digite a opção desejada: ", nome_mostra);
              oi = 'f';
            } else {
              printf("Digite a opção desejada: ");
            }
            fgets(opcao, sizeof(opcao), stdin);
            puts("");
            while (opcao[0] != '1' && opcao[0] != '2' && opcao[0] != '3' &&
                   opcao[0] != '4' && opcao[0] != '5' && opcao[0] != '6' &&
                   opcao[0] != '7' && opcao[0] != '8' || strlen(opcao) > 2) {
              puts("Opção inválida!\n");
              printf("Digite uma opção válida: ");
              fgets(opcao, sizeof(opcao), stdin);
              puts("");
            }
            if (opcao[0] == '1') {
  
              permissao(usuarios[indice_usuario].senha);
              consultar_saldo(usuarios[indice_usuario].real,   usuarios[indice_usuario].BTC,usuarios[indice_usuario].RIP,                  usuarios[indice_usuario].ETH,nome_mostra,usuarios[indice_usuario].CPF,criptomoedas, total_criptomoedas, usuarios, indice_usuario);
              confirmacao(confirmar, nome_mostra, &menu, &sair);
  
            } else if (opcao[0] == '2') {
  
              permissao(usuarios[indice_usuario].senha);
              consultar_extrato(registro,nome_mostra,usuarios[indice_usuario].CPF);
              confirmacao(confirmar, nome_mostra, &menu, &sair);
  
            } else if (opcao[0] == '3') {
  
              permissao(usuarios[indice_usuario].senha);
              depositar(usuarios[indice_usuario].real,usuarios[indice_usuario].BTC,usuarios[indice_usuario].RIP, usuarios[indice_usuario].ETH, registro);
              confirmacao(confirmar, nome_mostra, &menu, &sair);
  
            } else if (opcao[0] == '4') {
  
              permissao(usuarios[indice_usuario].senha);
              sacar(usuarios[indice_usuario].real, registro,usuarios[indice_usuario].BTC,usuarios[indice_usuario].RIP,                   usuarios[indice_usuario].ETH);
              confirmacao(confirmar, nome_mostra, &menu, &sair);
  
            } else if (opcao[0] == '5') {
  
              permissao(usuarios[indice_usuario].senha);
              comprar_criptomoeda(usuarios[indice_usuario].real,usuarios[indice_usuario].BTC,usuarios[indice_usuario].RIP, usuarios[indice_usuario].ETH, registro, cotacao_btc, cotacao_rip, cotacao_eth, criptomoedas, total_criptomoedas, usuarios, indice_usuario);  
              confirmacao(confirmar, nome_mostra, &menu, &sair);
  
            } else if (opcao[0] == '6') {
  
              permissao(usuarios[indice_usuario].senha);
              vender_criptomoeda(usuarios[indice_usuario].real,usuarios[indice_usuario].BTC,usuarios[indice_usuario].RIP,usuarios[indice_usuario].ETH, registro, cotacao_btc, cotacao_rip, cotacao_eth, criptomoedas, total_criptomoedas, usuarios, indice_usuario);
              confirmacao(confirmar, nome_mostra, &menu, &sair);
  
            } else if (opcao[0] == '7') {
              atualizar_cotacao(cotacao_btc, cotacao_rip, cotacao_eth, criptomoedas, total_criptomoedas);
              confirmacao(confirmar, nome_mostra, &menu, &sair);
  
            } else if (opcao[0] == '8') {
              printf("Tenha um ótimo dia Sr(a) %s!\n",nome_mostra);
              menu = 'f';
              sair = 't';
            }
          }
  
          FILE *escreve3 = fopen("usuarios.txt", "w"); // Abre o arquivo para sobrescrever o conteúdo

          fprintf(escreve3, "\n");

          for (i = 0; i < contador_cadastros; i++) {
              // Escreve as informações do usuário
              fprintf(escreve3, "*;%s;%s;%s;%s;%s;%s;%s;%s;", 
                  usuarios[i].tipo, 
                  usuarios[i].CPF, 
                  usuarios[i].senha,
                  usuarios[i].nome, 
                  usuarios[i].real,
                  usuarios[i].BTC,
                  usuarios[i].RIP, 
                  usuarios[i].ETH
              );

              for (int j = 0; j < total_criptomoedas; j++) {
                  fprintf(escreve3, "%s;", usuarios[i].criptomoedas[j].saldo);
              }

              // Finaliza o registro do usuário com uma nova linha
              fprintf(escreve3, "\n");
          }

          fclose(escreve3); // Fecha o arquivo
        }
      } 
      else if (resposta[0] == '4' && strlen(resposta) == 2) { // Sair do programa
        puts("Tenha um ótimo dia!\n");
        sair = 't';
      } 
      else if (resposta[0] == '3' && strlen(resposta) == 2){
        inicio = 1;
        mostrar = 1;
        puts("");
        puts("");
      }
      else {
        puts("Resposta inválida!\n");
        bemvindo = 'f';
      }
    }
    else if (escolha_menu == 2){
      puts("                     Administrador");
      puts("~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~~-~~");
      printf("1. Criar conta \n");
      printf("2. Acessar conta\n");
      printf("3. Voltar\n");
      printf("4. Sair\n");
      if (bemvindo == 't'){
        printf("\nOlá! Digite a opção desejada: ");
      }
      else{
        printf("\nDigite a opção desejada: ");
      }
      fgets(resposta, sizeof(resposta), stdin);
      puts("");
      if (resposta[0] == '1' && strlen(resposta) == 2) { // Cadastra conta
        if (contador_cadastros >= 10) {
          printf("Número máximo de contas atingido.\n\n");
          while (1){
            puts("Digite ENTER para continuar...");
            fgets(resposta, sizeof(resposta), stdin);
            if(strlen(resposta) == 1){
              break;
            }
          }
          bemvindo = 'f';

        }
        else{
          verificar = 'n';
          while (verificar == 'n') {
            printf("Digite seu nome completo: ");
            fgets(usuarios[NV].nome, sizeof(usuarios[NV].nome), stdin);
            if (strlen(usuarios[NV].nome) < 10 || strlen(usuarios[NV].nome) > 50) { // nome maior que 10 e menor que 50
              puts("Nome inválido!\n");
              continue;
            } else {
              for (i = 0; i < strlen(usuarios[NV].nome); i++) {
                if (usuarios[NV].nome[i] == ' ') {
                  usuarios[NV].nome[i] = '_';
                } else if (usuarios[NV].nome[i] == '\n') {
                  usuarios[NV].nome[i] = '\0';
                }
              }
              puts("Nome cadastrado!\n");
              verificar = 't';
            }
          }
          verificar = 'n';
          while (verificar == 'n') {
            printf("Digite uma senha de 6 dígitos: ");
            fgets(usuarios[NV].senha, sizeof(usuarios[NV].senha), stdin);
            tamanho = strlen(usuarios[NV].senha);
            if (tamanho != 7) {
              puts("A senha precisa ter 6 caracteres!\n");
  
              continue;
            } else {
  
              for (i = 0; i < strlen(usuarios[NV].senha); i++) {
                if (usuarios[NV].senha[i] == '\n') {
                  usuarios[NV].senha[i] = '\0';
                }
              }
              // troca o \n por ;
  
              puts("Senha cadastrada!\n");
              verificar = 't';
            }
          }
          verificar = 'n';
          while (verificar == 'n') {
            printf("Digite seu CPF (formato de CPF: xxx.xxx.xxx-xx): ");
            fgets(usuarios[NV].CPF, sizeof(usuarios[NV].CPF), stdin);
  
            if (strlen(usuarios[NV].CPF) != 15) {
              puts("CPF inválido!\n");
              verificar = 'n';
            } 
            else {
              CPF_existente1 = 0;
              if (contador_cadastros != 0){
                for (i = 0; i < 10; i++) {
  
                  for (j = 0; j < 14; j++) {
                    if (usuarios[i].CPF[j] == usuarios[NV].CPF[j]) {
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
                for (i = 0; i < strlen(usuarios[NV].CPF); i++) {
                  if (usuarios[NV].CPF[i] == '\n') {
                    usuarios[NV].CPF[i] = '\0';              
                  }
                }
                strcpy(usuarios[NV].tipo, "administrador");
                strcpy(usuarios[NV].real, "0.00");
                strcpy(usuarios[NV].BTC, "0.00");
                strcpy(usuarios[NV].RIP, "0.00");
                strcpy(usuarios[NV].ETH, "0.00");
                puts("CPF cadastrado!\n");
                verificar = 't';
              }
            }    
          }
          verificar = 'n'; 
          while (verificar == 'n') {
            printf("Deseja cadastrar a conta? [S/N]: "); // CONFIRMACAO DE CADASTRO DE CONTA
            fgets(confirmar, sizeof(confirmar), stdin);
            if (confirmar[0] == 's'  && strlen(confirmar) == 2 || confirmar[0] == 'S' && strlen(confirmar) == 2) {
              // SALVAR STRUCT
              puts("\nConta cadastrada com sucesso!\n");
  
  
              FILE *escreve = fopen("usuarios.txt", "a"); // SALVA O CADSATRO NO TXT
  
              fprintf(
                  escreve, "*;%s;%s;%s;%s;%s;%s;%s;%s;",usuarios[NV].tipo, usuarios[NV].CPF, usuarios[NV].senha,
                  usuarios[NV].nome, usuarios[NV].real,usuarios[NV].BTC,usuarios[NV].RIP,usuarios[NV].ETH); // ADICIONA O %X E ESCREVE O USUARIO[NV].XXXX
              for (int i = 0; i < total_criptomoedas; i++) {
                  fprintf(escreve, "%s;", usuarios[NV].criptomoedas[i].saldo);
              }
              fprintf(escreve, "\n");
  
              fclose(escreve);
  
              contador_cadastros++;
  
  
              verificar = 't';
            } else if (confirmar[0] == 'n'  && strlen(confirmar) == 2 ||
                       confirmar[0] == 'N' && strlen(confirmar) == 2) { // VOLTA AO INICIO DO PROGRAMA!
              puts("\nConta cancelada com sucesso!\n");
              verificar = 't';
            } else {
              puts("Opção inválida!\n");
            }
          }
        }
      } // fim opcao criar conta
      else if (resposta[0] == '2' && strlen(resposta) == 2) { // Acessar a conta
        permissao_acesso = 1;
        verificar = 't';
        while (verificar == 't') {
          printf("Digite seu CPF: ");
          fgets(cpflogin, sizeof(cpflogin), stdin);
          cpflogin[strcspn(cpflogin, "\n")] = '\0';
          for (i = 0; i < contador_cadastros; i++){
            if (strcmp(cpflogin, usuarios[i].CPF) == 0){
              verificar = 'f';
              indice_usuario = i;
              break;
            }
          }
          if (verificar == 't'){
            puts("CPF não encontrado!\n");
          }
        }
        verificar = 'f';
        while (verificar == 'f'){
          printf("Digite sua senha: ");
          fgets(senhalogin, sizeof(senhalogin), stdin);
          senhalogin[strcspn(senhalogin, "\n")] = '\0';
          if (strcmp(senhalogin, usuarios[indice_usuario].senha) == 0){
            if (strcmp(usuarios[indice_usuario].tipo, "administrador") == 0){
              verificar = 't';
              permissao_acesso = 0;
            }
            else{
              verificar = 't';
              puts("\nEste usuário não tem permissão para acessar o menu de administrador.\nVocê será redirecionado ao menu.\n");
              while (1){
                puts("Digite ENTER para continuar...");
                fgets(resposta, sizeof(resposta), stdin);
                if(strlen(resposta) == 1){
                  break;
                }
              }

            }
          }
          else{
            puts("Senha incorreta!\n");
          }
        }
        if (permissao_acesso == 0){
          i = 0;
          while(usuarios[indice_usuario].nome[i] != '\0'){

            if (usuarios[indice_usuario].nome[i] == '_') {
                nome_mostra[i] = ' ';
              }
            else{
              nome_mostra[i] = usuarios[indice_usuario].nome[i];
            }
            i++;
          }
          nome_mostra[i] = '\0';
          while (menu == 't') {
            
            FILE *nova_cotacao = fopen("cotacao.txt", "w");
            fprintf(nova_cotacao, "\n");
            fprintf(nova_cotacao, "%s;\n%s;\n%s;", cotacao_btc, cotacao_rip, cotacao_eth);
            fclose(nova_cotacao);
            
            FILE *escreve2 = fopen("usuarios.txt", "w"); // Abre o arquivo para sobrescrever o conteúdo

            fprintf(escreve2, "\n");

            for (i = 0; i < contador_cadastros; i++) {
                // Escreve as informações do usuário
                fprintf(escreve2, "*;%s;%s;%s;%s;%s;%s;%s;%s;", 
                    usuarios[i].tipo, 
                    usuarios[i].CPF, 
                    usuarios[i].senha,
                    usuarios[i].nome, 
                    usuarios[i].real,
                    usuarios[i].BTC,
                    usuarios[i].RIP, 
                    usuarios[i].ETH
                );

                for (int j = 0; j < total_criptomoedas; j++) {
                    fprintf(escreve2, "%s;", usuarios[i].criptomoedas[j].saldo);
                }

                // Finaliza o registro do usuário com uma nova linha
                fprintf(escreve2, "\n");
            }

            fclose(escreve2); // Fecha o arquivo
            
            FILE *escreve3 = fopen("criptomoeda.txt", "w");
            for(i = 0; i < total_criptomoedas; i++){
              fprintf(escreve3, "*;%s;%s;%s;%s;%s;\n", criptomoedas[i].nome, criptomoedas[i].ticker, criptomoedas[i].cotacao, criptomoedas[i].taxa_compra, criptomoedas[i].taxa_venda);
            }
            fclose(escreve3);
            puts("");
            puts("1. Cadastrar novo investidor");
            puts("2. Excluir investidor");
            puts("3. Cadastrar nova criptomoeda");
            puts("4. Excluir criptomoeda");
            puts("5. Consultar saldo de um investidor");
            puts("6. Consultar extrato de um investidor");
            puts("7. Atualizar cotação");
            puts("8. Sair");
            puts("");
            if (oi == 't') {
              printf("Olá Sr(a) %s! Digite a opção desejada: ", nome_mostra);
              oi = 'f';
            } 
            else {
              printf("Digite a opção desejada: ");
            }
            fgets(opcao, sizeof(opcao), stdin);
            puts("");
            while (opcao[0] != '1' && opcao[0] != '2' && opcao[0] != '3' &&
                   opcao[0] != '4' && opcao[0] != '5' && opcao[0] != '6' &&
                   opcao[0] != '7' && opcao[0] != '8' || strlen(opcao) > 2) {
              puts("Opção inválida!\n");
              printf("Digite uma opção válida: ");
              fgets(opcao, sizeof(opcao), stdin);
              puts("");
            }
            if(opcao[0] == '1'){
              cadastrar_investidor(usuarios, &contador_cadastros, criptomoedas, total_criptomoedas);
              confirmacao(confirmar, nome_mostra, &menu, &sair);
            }
            else if(opcao[0] == '2'){
              excluir_investidor(usuarios, &contador_cadastros, criptomoedas, total_criptomoedas);
              confirmacao(confirmar, nome_mostra, &menu, &sair);
            }
            else if(opcao[0] == '3'){
              cadastrar_criptomoeda(criptomoedas,&total_criptomoedas, usuarios, &contador_cadastros);
              confirmacao(confirmar, nome_mostra, &menu, &sair);
            }
            else if(opcao[0] == '4'){
              excluir_criptomoeda(criptomoedas, &total_criptomoedas, usuarios, &contador_cadastros);
              confirmacao(confirmar, nome_mostra, &menu, &sair);
            }
            else if(opcao[0] == '5'){
              consultar_saldo_investidor(usuarios, &contador_cadastros, criptomoedas, total_criptomoedas);
              confirmacao(confirmar, nome_mostra, &menu, &sair);
            }
            else if(opcao[0] == '6'){
              consultar_extrato_investidor(usuarios, &contador_cadastros, registros);
              confirmacao(confirmar, nome_mostra, &menu, &sair);
            }
            else if(opcao[0] == '7'){
              atualizar_cotacao(cotacao_btc, cotacao_rip, cotacao_eth,criptomoedas, total_criptomoedas);
              confirmacao(confirmar, nome_mostra, &menu, &sair);
            }
            else if(opcao[0] == '8'){
              printf("Tenha um ótimo dia Sr(a) %s!\n",nome_mostra);
                menu = 'f';
                sair = 't';
            }           
          } // fim menu == t
        } // fim permissao acesso (menu)
      } // fim opcao acessar conta
        
      else if (resposta[0] == '4' && strlen(resposta) == 2) { // Sair do programa
        puts("Tenha um ótimo dia!\n");
        sair = 't';
      }
      else if (resposta[0] == '3' && strlen(resposta) == 2){
        inicio = 1;
        mostrar = 1;
        puts("");
        puts("");
      }
      else {
        puts("Resposta inválida!\n");
        bemvindo = 'f';
      }
    }
  } // fim while
  // system("pause");
  return 0;
}
