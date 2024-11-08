#ifndef biblioteca

// run = "gcc main.c biblioteca.c -o main && ./main"
// language = "c"
  
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

typedef struct cadastro {
  char tipo[20]; // tipo da conta
  char nome[51];
  char senha[15];
  char CPF[30];
  char real[30]; 
  char BTC[30];
  char RIP[30];
  char ETH[30];
} Cadastro;

   /*                                       Prototipo das funcoes                                              */

void confirmacao(char *confirmar, char *nome, char *menu, char *sair); //funcao para continuar no menu ou sair do programa

void permissao (char *senharegistrada); // funcao para realizar a acao desejada apos a confirmacao de senha

void consultar_extrato(char *registro, char *nome, char *cpf); // funcao para consultar o extrato)

void depositar(char *real, char *bitcoin_usuario, char *ripple_usuario, char *ethereum_usuario, char *registro);

void sacar (char *real, char *registro, char *bitcoin_usuario, char *ripple_usuario, char *ethereum_usuario);

void consultar_saldo(char *real,char *bitcoin,char *ripple,char *ethereum, char *nome, char *cpf);

void comprar_criptomoeda(char *real_usuario, char *bitcoin_usuario, char *ripple_usuario, char *ethereum_usuario, char *registro, char *cotacao_btc2, char *cotacao_rip2, char *cotacao_eth2);

void vender_criptomoeda(char *real_usuario, char *bitcoin_usuario, char *ripple_usuario, char *ethereum_usuario, char *registro, char *cotacao_btc1, char *cotacao_rip1, char *cotacao_eth1);

void atualizar_cotacao(char *cotacao_btc, char *cotacao_rip, char *cotacao_eth);

void cadastrar_investidor(Cadastro *usuarios, int *contador_cadastros);

void excluir_investidor(Cadastro *usuarios, int *contador_cadastros); // falta excluir do struct

void consultar_saldo_investidor(Cadastro *usuarios, int *contador_cadastros);

void consultar_extrato_investidor(Cadastro *usuarios, int *contador_cadastros); // como passar registros como parametro
#endif
