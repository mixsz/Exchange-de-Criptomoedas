#include "biblioteca.h"

typedef struct cadastro {
  char nome[51];
  char senha[15];
  char CPF[30];
  char real[30]; 
  char BTC[30];
  char RIP[30];
  char ETH[30];
} Cadastro;

int main() {

  char cotacao_btc[30];
  char cotacao_rip[30];
  char cotacao_eth[30];
  setlocale(LC_ALL, "portuguese");
  char sair = 'f', bemvindo = 't', oi = 't';
  char resposta[10], confirmar[10], cpflogin[16], senhalogin[15], opcao[10];
  Cadastro usuarios[10];
  int tamanho, i, j;
  char verificar = 'n', login = 'f', menu = 't';
  int contador = 0;
  int contador_cadastros = 0;
  int PT = 0;                      // CONTADOR DE PONTO E VÍRGULA
  int contador_nome, contador_CPF, contador_senha, contador_real,contador_btc, contador_ripple, contador_eth;
  int permissao_acesso = 1, CPF_existente = 1,CPF_existente1 = 0,permissao_funcao = 1;
  int indice_usuario = -1, cpf_finder, cpf_finder1,
      senha_finder; // variaveis que comparam se o cpf e a senha existem nos

                    // dados armazenados
  char registros[10][15] ={"registro0.txt","registro1.txt","registro2.txt","registro3.txt","registro4.txt","registro5.txt","registro6.txt","registro7.txt","registro8.txt","registro9.txt"};
  char registro[15];

  FILE *arquivo_moedas = fopen("cotacao.txt", "r");
  char linha1[2550];
  PT = 0;
  while (fgets(linha1, 2550, arquivo_moedas) !=NULL){
    PT++; 
    fscanf(arquivo_moedas, "%s", linha1);
    for (i = 0; i < strlen(linha1) - 1; i++){
      switch(PT){
        case 1:
          cotacao_btc[i] = linha1[i];
          break; 
        case 2:
          cotacao_rip[i] = linha1[i];
          break;
        case 3:
          cotacao_eth[i] = linha1[i];
          break;
      }      
    }   
  }
  printf(" %s" ,cotacao_btc);
  printf(" %s" ,cotacao_rip);
  printf(" %s" ,cotacao_eth);


  fclose(arquivo_moedas);


  FILE *ler = fopen("usuarios.txt", "r"); // LER ARQUIVO TXT
  char linha[2550]; // VARIAVEL QUE ARMAZENA TEMPORARIAMENTE OS CADASTROS DO TXT
  while (fgets(linha, 2550, ler) !=
         NULL) { // LOOP QUE LE SEPARADAMENTE OS CADASRTOS SEPARADOS POR \n
    contador_CPF = 0;
    contador_nome = 0;
    contador_senha = 0;
    contador_real = 0;
    contador_btc = 0;
    contador_ripple = 0;
    contador_eth = 0;
    PT = 0; // CONTADOR DE PONTO E VÍRGULA
    fscanf(ler, "%s", linha);
    for (i = 0; i < strlen(linha); i++) {
      if (linha[i] == '*') {
        contador_cadastros++;
      }
    }

    for (i = 0; i < strlen(linha); i++) {
      if (linha[i] == ';') {
        PT++;
      } else if (linha[i] == '*') {
        continue;
      } else {
        switch (PT) {
        case 1:
          usuarios[contador_cadastros - 1].CPF[contador_CPF] = linha[i]; // COLOCA O CPF NO VETOR
          usuarios[contador_cadastros - 1].CPF[contador_CPF + 1] = '\0'; // TIRA LIXOS QUE FICAM NO FINAL DO VETOR
          contador_CPF++;
          break;
        case 2:
          usuarios[contador_cadastros - 1].senha[contador_senha] = linha[i];
          usuarios[contador_cadastros - 1].senha[contador_senha + 1] = '\0';
          contador_senha++;
          break;
        case 3:
          usuarios[contador_cadastros - 1].nome[contador_nome] = linha[i];
          usuarios[contador_cadastros - 1].nome[contador_nome + 1] = '\0';
          contador_nome++;
          break;
        case 4:
          usuarios[contador_cadastros - 1].real[contador_real] = linha[i];
          usuarios[contador_cadastros - 1].real[contador_real + 1] = '\0';
          contador_real++;
          break;
        case 5:
          usuarios[contador_cadastros - 1].BTC[contador_btc] = linha[i];
          usuarios[contador_cadastros - 1].BTC[contador_btc + 1] = '\0';
          contador_btc++;
          break;
        case 6:
          usuarios[contador_cadastros - 1].RIP[contador_ripple] = linha[i];
          usuarios[contador_cadastros - 1].RIP[contador_ripple + 1] = '\0';
          contador_ripple++;
          break;
        case 7:
          usuarios[contador_cadastros - 1].ETH[contador_eth] = linha[i];
          usuarios[contador_cadastros - 1].ETH[contador_eth + 1] = '\0';
          contador_eth++;
          break;


        default:
          break;
        }
      }
    }

  }
  //printf("%s\n", usuarios[0].nome);
 // printf("%s\n", usuarios[0].CPF);
  // printf(" %d", contador_cadastros);
  fclose(ler);

  FILE *escreve1 = fopen("usuarios.txt", "a"); 
  if (contador_cadastros == 0){
  fprintf(escreve1, "\n");}
  fclose(escreve1);

  //printf(" %d\n\n", contador_cadastros);



  while (sair != 't') { 

    int NV = contador_cadastros; // Novo Cadastro
    printf("1 - Criar conta \n");
    printf("2 - Acessar conta\n");
    printf("3 - Sair\n");
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
        printf("Número máximo de contas atingido.\n\n\n");
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
  ;
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
          puts("Deseja cadastrar a conta? [S/N]: "); // CONFIRMACAO DE CADASTRO DE CONTA
          fgets(confirmar, sizeof(confirmar), stdin);
          if (confirmar[0] == 's'  && strlen(confirmar) == 2 || confirmar[0] == 'S' && strlen(confirmar) == 2) {
            // SALVAR STRUCT
            puts("\nConta cadastrada com sucesso!\n");


            FILE *escreve = fopen("usuarios.txt", "a"); // SALVA O CADSATRO NO TXT

            fprintf(
                escreve, "*;%s;%s;%s;%s;%s;%s;%s;\n", usuarios[NV].CPF, usuarios[NV].senha,
                usuarios[NV].nome, usuarios[NV].real,usuarios[NV].BTC,usuarios[NV].RIP,usuarios[NV].ETH); // ADICIONA O %X E ESCREVE O USUARIO[NV].XXXX

            fclose(escreve);

            contador_cadastros++;


            verificar = 't';
          } else if (confirmar[0] == 'n'  && strlen(confirmar) == 2 ||
                     confirmar[0] == 'N' && strlen(confirmar) == 2) { // VOLTA AO INICIO DO PROGRAMA!
            puts("\nConta cancelada com sucesso!\n");
            verificar = 't';
          } else {
            puts("Opção inválida!\n");
          } /////////////////////////////////////////////////////////////////////
        }
      }
    } else if (resposta[0] == '2' && strlen(resposta) == 2) { // Acessar a conta
      verificar = 't';
      // login = 'f';
      while (verificar == 't') {
        printf("Digite seu CPF: ");
        fgets(cpflogin, sizeof(cpflogin), stdin);
        for (i = 0; i < 10; i++) {
          if (CPF_existente == 0) {
            break;
          } // Caso o CPF já tenha sido encontrado pare o loop
          for (j = 0; j < 14; j++) {
            if (usuarios[i].CPF[j] == cpflogin[j]) {
              cpf_finder = 0;
            } // Comparador
            else {
              cpf_finder = 1;
              break;
            }
            if (j == 13 && cpf_finder == 0) {
              CPF_existente = 0;
              indice_usuario = i;
              break;
            }
          }
        }
        if (CPF_existente == 0) {
          while (permissao_acesso == 1){
            printf("\nDigite sua senha: ");
            fgets(senhalogin, sizeof(senhalogin), stdin);

            for (i = 0; i < 10; i++) {
              if (permissao_acesso == 0) {
                break;
              } // Caso a senha já tenha sido encontrada pare o loop
              for (j = 0; j < 6; j++) {
                if (usuarios[i].senha[j] == senhalogin[j]) {
                  senha_finder = 0;
                } // Comparador
                else {
                  senha_finder = 1;
                  break;
                }
                if (j == 5 && senha_finder == 0) {
                  permissao_acesso = 0;
                  verificar = 'f';
                  break;
                }
              }
            }
            if (permissao_acesso == 1) {
              printf("Senha incorreta!\n");
            }
          }
        }
        else {
          printf("CPF não encontrado!\n\n");
        }
        ///////////////////////////////////////////////////
      }
      if (permissao_acesso == 0) {    
        strcpy(registro, registros[indice_usuario]);

        while (menu == 't') {

          FILE *nova_cotacao = fopen("cotacao.txt", "w");
          fprintf(nova_cotacao, "\n");
          fprintf(nova_cotacao, "%s;\n%s;\n%s;", cotacao_btc, cotacao_rip, cotacao_eth);
          fclose(nova_cotacao);

          FILE *escreve2 = fopen("usuarios.txt", "w"); // ATUALIZA O CADASTRO QUANDO RETORNA AO MENU!
          fprintf(escreve2, "\n");
          for(i = 0; i < contador_cadastros; i++){
          fprintf(
              escreve2, "*;%s;%s;%s;%s;%s;%s;%s;\n", usuarios[i].CPF, usuarios[i].senha,
              usuarios[i].nome, usuarios[i].real, usuarios[i].BTC, usuarios[i].RIP, usuarios[i].ETH); 
          }
          fclose(escreve2);

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
            printf("Olá Sr(a) %s! Digite a opção desejada: ",
                   usuarios[indice_usuario].nome);
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
            consultar_saldo(usuarios[indice_usuario].real, usuarios[indice_usuario].BTC,usuarios[indice_usuario].RIP,                  usuarios[indice_usuario].ETH);
            confirmacao(confirmar, usuarios[indice_usuario].nome, &menu, &sair);

          } else if (opcao[0] == '2') {

            permissao(usuarios[indice_usuario].senha);
            consultar_extrato(registro);
            confirmacao(confirmar, usuarios[indice_usuario].nome, &menu, &sair);

          } else if (opcao[0] == '3') {

            permissao(usuarios[indice_usuario].senha);
            depositar(usuarios[indice_usuario].real,usuarios[indice_usuario].BTC,usuarios[indice_usuario].RIP, usuarios[indice_usuario].ETH, registro);
            confirmacao(confirmar, usuarios[indice_usuario].nome, &menu, &sair);

          } else if (opcao[0] == '4') {

            permissao(usuarios[indice_usuario].senha);
            sacar(usuarios[indice_usuario].real, registro,usuarios[indice_usuario].BTC,usuarios[indice_usuario].RIP,                   usuarios[indice_usuario].ETH);
            confirmacao(confirmar, usuarios[indice_usuario].nome, &menu, &sair);

          } else if (opcao[0] == '5') {

            permissao(usuarios[indice_usuario].senha);
            comprar_criptomoeda(usuarios[indice_usuario].real,usuarios[indice_usuario].BTC,usuarios[indice_usuario].RIP, usuarios[indice_usuario].ETH, registro, cotacao_btc, cotacao_rip, cotacao_eth);      
            confirmacao(confirmar, usuarios[indice_usuario].nome, &menu, &sair);

          } else if (opcao[0] == '6') {

            permissao(usuarios[indice_usuario].senha);
            vender_criptomoeda(usuarios[indice_usuario].real,usuarios[indice_usuario].BTC,usuarios[indice_usuario].RIP,usuarios[indice_usuario].ETH, registro, cotacao_btc, cotacao_rip, cotacao_eth);
            confirmacao(confirmar, usuarios[indice_usuario].nome, &menu, &sair);

          } else if (opcao[0] == '7') {
            atualizar_cotacao(cotacao_btc, cotacao_rip, cotacao_eth);
            confirmacao(confirmar, usuarios[indice_usuario].nome, &menu, &sair);

          } else if (opcao[0] == '8') {
            printf("Tenha um ótimo dia Sr(a) %s!\n",usuarios[indice_usuario].nome);
            menu = 'f';
            sair = 't';
          }
        }

        FILE *escreve3 = fopen("usuarios.txt", "w"); // ATUALIZA O CADASTRO QUANDO SAI DO PROGRAMA!
        fprintf(escreve3, "\n");
        for(i = 0; i < contador_cadastros; i++){
        fprintf(
            escreve3, "*;%s;%s;%s;%s;%s;%s;%s;\n", usuarios[i].CPF, usuarios[i].senha,
            usuarios[i].nome, usuarios[i].real, usuarios[i].BTC, usuarios[i].RIP, usuarios[i].ETH); 
        }
        fclose(escreve3);
      }
    } else if (resposta[0] == '3' && strlen(resposta) == 2) { // Sair do programa
      puts("Tenha um ótimo dia!\n");
      sair = 't';
    } else {
      puts("Resposta inválida!\n");
      bemvindo = 'f';
    }
  }

  // system("pause");
  return 0;
}
