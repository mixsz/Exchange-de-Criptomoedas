#include "biblioteca.h"

typedef struct cadastro{
  char nome[51];
  char senha[15];
  char CPF[16];   
} Cadastro;

int main() {

  
  setlocale(LC_ALL,"portuguese");
  char sair = 'f',bemvindo = 't', oi = 't';
  char resposta[10], confirmar[10],cpflogin[16],senhalogin[15],opcao[10];
  Cadastro usuarios;
  int tamanho;
  char verificar = 'n',login = 'f',menu = 't';
  
  
  while (sair != 't'){
    if (bemvindo == 't'){ // dar bem-vindo na primeira vez
      puts("Bem-vindo! Digite a opção desejada:");
      bemvindo = 'f';
    }
    else{
      puts("Digite a opção desejada:");
    }
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
      else if(resposta[0] == '2'){ // Acessar a conta
        verificar = 't';
        login = 'f';
        while (verificar == 't'){         
          printf("Digite seu CPF: "); 
          fgets(cpflogin,sizeof(cpflogin),stdin);
          printf("Digite sua senha: ");
          fgets(senhalogin,sizeof(senhalogin),stdin);
          puts("");
          if (cpflogin[0] != 'a'){ // cpflogin != usuarios.CPF && senhalogin != usuarios.senha |
            
            printf("CPF ou senha inválido! Tentar novamente? [S/N]: ");
            fgets(confirmar,sizeof(confirmar),stdin);
            puts("");
            while (confirmar[0] != 's' && confirmar[0] != 'S' && confirmar[0] != 'n' && confirmar[0] != 'N'){
              puts("Opção inválida!\n");
              printf("Tentar novamente? [S/N]: ");
              fgets(confirmar,sizeof(confirmar),stdin);
              puts("");
            }
            if (confirmar[0] == 's' || confirmar[0] == 'S'){
              continue;
            }
            else if (confirmar[0] == 'n' || confirmar[0] == 'N'){
              verificar = 'f';
            }
          }
          else{
            puts("Login bem sucedido!\n");
            verificar = 'f';
            login = 't';
          }
        }
        if (login == 't'){
          while (menu == 't'){
            strcpy(confirmar, "confirme");
            strcpy(usuarios.nome, "Rafael Testa");
            puts("1. Consultar saldo");
            puts("2. Consultar extrato");
            puts("3. Depositar");
            puts("4. Sacar");
            puts("5. Comprar criptomoedas");
            puts("6. Vender criptomoedas");
            puts("7. Atualizar cotação");
            puts("8. Sair");
            puts("");
            if (oi == 't'){
              printf("Olá Sr(a) %s! Digite a opção desejada: ",usuarios.nome);
              oi = 'f';
            }
            else{
              printf("Digite a opção desejada: ");
            }
            fgets(opcao,sizeof(opcao),stdin);
            puts("");
            while (opcao[0] != '1' && opcao[0] != '2' && opcao[0] != '3' && opcao[0] != '4' && opcao[0] != '5' && opcao[0]             != '6' && opcao[0] != '7' && opcao[0] != '8'){
              puts("Opção inválida!\n");
              printf("Digite uma opção válida: ");
              fgets(opcao,sizeof(opcao),stdin);
              puts("");
            }   
            if (opcao[0] == '1'){
              puts("Consultar saldo");
              confirmacao(confirmar,usuarios.nome,&menu,&sair);
            }
            else if (opcao[0] == '2'){
              puts("Consultar extrato");
              confirmacao(confirmar,usuarios.nome,&menu,&sair);
            }
            else if (opcao[0] == '3'){
              puts("Depositar");
              confirmacao(confirmar,usuarios.nome,&menu,&sair);
            }
            else if (opcao[0] == '4'){
              puts("Sacar");
              confirmacao(confirmar,usuarios.nome,&menu,&sair);
            }
            else if (opcao[0] == '5'){
              puts("Comprar criptomoedas");
              confirmacao(confirmar,usuarios.nome,&menu,&sair);
            }
            else if (opcao[0] == '6'){
              puts("Vender criptomoedas");
              confirmacao(confirmar,usuarios.nome,&menu,&sair);
            }
            else if (opcao[0] == '7'){
              puts("Atualizar cotação");
              confirmacao(confirmar,usuarios.nome,&menu,&sair);
            }
            else if (opcao[0] == '8'){
              printf("Tenha um ótimo dia Sr(a) %s!\n",usuarios.nome);
              menu = 'f';
              sair = 't';
            }
          }
        }
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
