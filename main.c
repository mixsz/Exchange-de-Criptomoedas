#include "biblioteca.h"

typedef struct cadastro{
  char nome[51];
  char senha[15];
  char CPF[16];   
} Cadastro;

int main() {

  
  setlocale(LC_ALL,"portuguese");
  char sair = 'f';
  char resposta[10], confirmar[10];
  Cadastro usuarios;
  int tamanho;
  char verificar = 'n';
  
  
  while (sair != 't'){
    puts("Bem-vindo! Digite a opção desejada:");
    puts("");
    printf("1 - Criar conta \n");
    printf("2 - Acessar conta\n");
    printf("3 - Sair\n");
    fgets(resposta,sizeof(resposta),stdin);
    puts("");
    
    if(resposta[0] == '1'){ //Cadastra conta
      verificar = 'n'; //VARIÁVEL 'verificar' QUE VERIFICA SE A INFORMAÇÃO DADA ESTÁ CORRETA!
      while (verificar == 'n'){
        printf("Digite seu nome completo: ");
        fgets(usuarios.nome,sizeof(usuarios.nome),stdin);
        if(strlen(usuarios.nome) < 10 || strlen(usuarios.nome) > 50){ //nome maior que 10 e menor que 50
          puts("Nome inválido!\n");
          continue;
      }          
      else{
      puts("Nome cadastrado!\n");
        verificar = 't';
      }
      }
      verificar = 'n';
      while (verificar == 'n'){
        printf("Digite uma senha de 6 dígitos: ");
        fgets(usuarios.senha,sizeof(usuarios.senha),stdin);
        tamanho = strlen(usuarios.senha);
        if (tamanho != 7){
          puts("A senha precisa ter 6 caracteres!\n");
          
          continue;
         }
         else{
          puts("Senha cadastrada!\n");
          verificar = 't';
      }
      }
      verificar = 'n';
      while (verificar == 'n'){
        printf("Digite seu CPF (formato de CPF: xxx.xxx.xxx-xx): ");
        fgets(usuarios.CPF,sizeof(usuarios.CPF),stdin);
        if (strlen(usuarios.CPF) != 15){
          puts("CPF inválido!");
        }
        else{
          puts("CPF cadastrado!\n");
          verificar = 't';
      }
    }
    verificar = 'n';
    while (verificar == 'n'){
      puts("Deseja cadastrar a conta? [S/N]: "); //CONFIRMACAO DE CADASTRO DE CONTA
      fgets(confirmar,sizeof(confirmar),stdin);
      if (confirmar[0] == 's' || confirmar[0] == 'S'){
        // SALVAR STRUCT
        puts("Conta cadastrada com sucesso!\n");
        verificar = 't';
      }
      else if(confirmar[0] == 'n' || confirmar[0] == 'N'){ //VOLTA AO INICIO DO PROGRAMA!
        puts("Conta cancelada com sucesso!\n");
        verificar = 't';
      }
      else{
        puts("Opção inválida!\n");
      }
    }
  }      
      else if(resposta[0] == '2'){
        puts("2"); // Acessar a conta
      }
      else if(resposta[0] == '3'){ // Sair do programa
        puts("Tenha um ótimo dia!");
        sair = 't';
      }
    else{
      puts("\nResposta inválida!");
    }
  }
  // system("pause");
  return 0;
}
