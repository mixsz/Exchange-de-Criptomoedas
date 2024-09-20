#include "biblioteca.h"


typedef struct cadastro {
  char nome[51];
  char senha[15];
  char CPF[16];
} Cadastro;

int main() {

  setlocale(LC_ALL, "portuguese");
  char sair = 'f';
  char resposta[10], confirmar[10];
  Cadastro usuarios[10];
  int tamanho, i;
  char verificar = 'n';
  int contador = 0;
  int contador_cadastros= 0;
  int NV = contador_cadastros + 1;// Novo Cadastro






  FILE *ler = fopen("usuarios.txt", "r");
  char linha[2550];

  
  while (fgets(linha, 2550, ler) != NULL) {
    
    
    fscanf(ler, "%s", linha);
    for (i= 0; i < strlen(linha); i++){if (linha[i] == '*'){contador_cadastros++;}}
      
    printf("%s", linha);
    
    
  
  }
  printf(" %d", contador_cadastros);
  
  fclose(ler);
// FUNÇÃO PARA LER O ARQUIVO


  

  while (sair != 't') {
    puts("Bem-vindo! Digite a opção desejada:");
    puts("");
    printf("1 - Criar conta \n");
    printf("2 - Acessar conta\n");
    printf("3 - Sair\n");
    fgets(resposta, sizeof(resposta), stdin);
    puts("");

    if (resposta[0] == '1') { // Cadastra conta
      verificar = 'n'; // VARIÁVEL 'verificar' QUE VERIFICA SE A INFORMAÇÃO DADA
                       // ESTÁ CORRETA!
      while (verificar == 'n') {
        printf("Digite seu nome completo: ");
        fgets(usuarios[NV].nome, sizeof(usuarios[NV].nome), stdin);
        if (strlen(usuarios[NV].nome) < 10 ||
            strlen(usuarios[NV].nome) > 50) { // nome maior que 10 e menor que 50
          puts("Nome inválido!\n");
          continue;
        } else {
          for (i=0; i<strlen(usuarios[NV].nome); i++){if (usuarios[NV].nome[i] == ' '){usuarios[NV].nome[i] = '_';}
                                                 else if(usuarios[NV].nome[i] == '\n'){usuarios[NV].nome[i] = ';';}}



          
          //for (i=0; i<strlen(usuarios.senha); i++){if(usuarios.nome[i] == '\n'){usuarios.senha[i] = ';';}}
                      
          
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

          for (i=0; i<strlen(usuarios[NV].senha); i++){if(usuarios[NV].senha[i] == '\n'){usuarios[NV].senha[i] = ';';}}
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
          puts("CPF inválido!");
        } else {
          
          for (i=0; i<strlen(usuarios[NV].CPF); i++){
            while(usuarios[NV].CPF[i] != '\n'){ contador = 0; contador = contador + 1;}
          }
          usuarios[NV].CPF[contador] = ';';//substitui o \n por um ponto e virgula
          //puts("Senha cadastrada!\n");

          for (i=0; i<strlen(usuarios[NV].CPF); i++){if(usuarios[NV].CPF[i] == '\n'){usuarios[NV].CPF[i] = ';';}}

          
          puts("CPF cadastrado!\n");
          verificar = 't';
        }
      }
      verificar = 'n';
      while (verificar == 'n') {
        puts("Deseja cadastrar a conta? [S/N]: "); // CONFIRMACAO DE CADASTRO DE
                                                   // CONTA
        fgets(confirmar, sizeof(confirmar), stdin);
        if (confirmar[0] == 's' || confirmar[0] == 'S') {
          // SALVAR STRUCT
          puts("Conta cadastrada com sucesso!\n");

          FILE *escreve = fopen("usuarios.txt", "a");

          fprintf(escreve, "*%s%s%s\n", usuarios[NV].CPF, usuarios[NV].senha,usuarios[NV].nome);

          fclose(escreve);

  
            

          verificar = 't';
        } else if (confirmar[0] == 'n' ||
                   confirmar[0] == 'N') { // VOLTA AO INICIO DO PROGRAMA!
          puts("Conta cancelada com sucesso!\n");
          verificar = 't';
        } else {
          puts("Opção inválida!\n");
        }
      }
    } else if (resposta[0] == '2') {
      puts("2");                     // Acessar a conta
    } else if (resposta[0] == '3') { // Sair do programa
      puts("Tenha um ótimo dia!");
      sair = 't';
    } else {
      puts("\nResposta inválida!");
    }
  }
  
  // system("pause");
  return 0;
}
