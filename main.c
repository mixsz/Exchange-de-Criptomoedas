#include "biblioteca.h"

typedef struct cadastro {
  char nome[51];
  char senha[15];
  char CPF[30];
  char real[30]; 
} Cadastro;

int main() {

  setlocale(LC_ALL, "portuguese");
  char sair = 'f', bemvindo = 't', oi = 't';
  char resposta[10], confirmar[10], cpflogin[16], senhalogin[15], opcao[10];
  Cadastro usuarios[10];
  int tamanho, i, j;
  char verificar = 'n', login = 'f', menu = 't';
  int contador = 0;
  int contador_cadastros = 0;
  int PT = 0;                      // CONTADOR DE PONTO E VÍRGULA
  int contador_nome, contador_CPF, contador_senha, contador_real;
  int permissao_acesso = 1, CPF_existente = 1,permissao_funcao = 1;
  int indice_usuario = -1, cpf_finder,
      senha_finder; // variaveis que comparam se o cpf e a senha existem nos
                    // dados armazenados

  FILE *ler = fopen("usuarios.txt", "r"); // LER ARQUIVO TXT
  char linha[2550]; // VARIAVEL QUE ARMAZENA TEMPORARIAMENTE OS CADASTROS DO TXT
  while (fgets(linha, 2550, ler) !=
         NULL) { // LOOP QUE LE SEPARADAMENTE OS CADASRTOS SEPARADOS POR \n
    contador_CPF = 0;
    contador_nome = 0;
    contador_senha = 0;
    contador_real = 0;
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


        default:
          break;
        }
      }
    }
    // printf(" %s", linha);
  }
  printf("%s\n", usuarios[0].nome);
  printf("%s\n", usuarios[0].CPF);
  // printf(" %d", contador_cadastros);
  fclose(ler);
  printf(" %d", contador_cadastros);

  int NV = contador_cadastros; // Novo Cadastro





  while (sair != 't') {
    if (bemvindo == 't'){
      puts("Bem-vindo! Digite a opção desejada:");
    }
    else{
      puts("Digite a opção desejada:");
    }
    puts("");
    printf("1 - Criar conta \n");
    printf("2 - Acessar conta\n");
    printf("3 - Sair\n");
    fgets(resposta, sizeof(resposta), stdin);
    puts("");

    if (resposta[0] == '1') { // Cadastra conta
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
              usuarios[NV].nome[i] = ';';
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
              usuarios[NV].senha[i] = ';';
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
        } else {
          for (i = 0; i < strlen(usuarios[NV].CPF); i++) {
            if (usuarios[NV].CPF[i] == '\n') {
              usuarios[NV].CPF[i] = ';';              
            }
          }
          strcpy(usuarios[NV].real, "0.00");
          puts("CPF cadastrado!\n");
          verificar = 't';
        }
      }
      verificar = 'n';
      while (verificar == 'n') {
        puts("Deseja cadastrar a conta? [S/N]: "); // CONFIRMACAO DE CADASTRO DE CONTA
        fgets(confirmar, sizeof(confirmar), stdin);
        if (confirmar[0] == 's' || confirmar[0] == 'S') {
          // SALVAR STRUCT
          puts("\nConta cadastrada com sucesso!\n");

          FILE *escreve = fopen("usuarios.txt", "a"); // SALVA O CADSATRO NO TXT

          fprintf(
              escreve, "*;%s%s%s%s;\n", usuarios[NV].CPF, usuarios[NV].senha,
              usuarios[NV].nome, usuarios[NV].real); // ADICIONA O %X E ESCREVE O USUARIO[NV].XXXX

          fclose(escreve);

          FILE *ler = fopen("usuarios.txt", "r");//atualiza o contador de cadastros
          char linha[2550];
          contador_cadastros = 0;

          while (fgets(linha, 2550, ler) != NULL){
            fscanf(ler, "%s", linha);
            for (i = 0; i < strlen(linha); i++) {
              if (linha[i] == '*') {
                contador_cadastros++;
              }
            }
          }
          fclose(ler);


          verificar = 't';
        } else if (confirmar[0] == 'n' ||
                   confirmar[0] == 'N') { // VOLTA AO INICIO DO PROGRAMA!
          puts("\nConta cancelada com sucesso!\n");
          verificar = 't';
        } else {
          puts("Opção inválida!\n");
        } /////////////////////////////////////////////////////////////////////
      }
    } else if (resposta[0] == '2') { // Acessar a conta
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
        while (menu == 't') {


          FILE *escreve = fopen("usuarios.txt", "w"); // ATUALIZA O CADASTRO
          fprintf(escreve, "\n");
          for(i = 0; i < contador_cadastros; i++){
          fprintf(
              escreve, "*;%s;%s;%s;%s;\n", usuarios[i].CPF, usuarios[i].senha,
              usuarios[i].nome, usuarios[i].real); 
          }
          fclose(escreve);


          strcpy(confirmar, "confirme");
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
                 opcao[0] != '7' && opcao[0] != '8') {
            puts("Opção inválida!\n");
            printf("Digite uma opção válida: ");
            fgets(opcao, sizeof(opcao), stdin);
            puts("");
          }
          if (opcao[0] == '1') {
            permissao(usuarios[indice_usuario].senha);

            puts("Consultar saldo");

            confirmacao(confirmar, usuarios[indice_usuario].nome, &menu, &sair);

          } else if (opcao[0] == '2') {
            permissao(usuarios[indice_usuario].senha);

            puts("Consultar extrato");

            confirmacao(confirmar, usuarios[indice_usuario].nome, &menu, &sair);

          } else if (opcao[0] == '3') {

            permissao(usuarios[indice_usuario].senha);
            depositar(usuarios[indice_usuario].real);
            confirmacao(confirmar, usuarios[indice_usuario].nome, &menu, &sair);

          } else if (opcao[0] == '4') {
            
            permissao(usuarios[indice_usuario].senha);
            sacar(usuarios[indice_usuario].real);
            confirmacao(confirmar, usuarios[indice_usuario].nome, &menu, &sair);

          } else if (opcao[0] == '5') {
            permissao(usuarios[indice_usuario].senha);

            puts("Comprar criptomoedas");

            confirmacao(confirmar, usuarios[indice_usuario].nome, &menu, &sair);

          } else if (opcao[0] == '6') {
            permissao(usuarios[indice_usuario].senha);

            puts("Vender criptomoedas");

            confirmacao(confirmar, usuarios[indice_usuario].nome, &menu, &sair);

          } else if (opcao[0] == '7') {
            puts("Atualizar cotação");
            confirmacao(confirmar, usuarios[indice_usuario].nome, &menu, &sair);

          } else if (opcao[0] == '8') {
            printf("Tenha um ótimo dia Sr(a) %s!\n",usuarios[indice_usuario].nome);
            menu = 'f';
            sair = 't';
          }
        }
      }
    } else if (resposta[0] == '3') { // Sair do programa
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
