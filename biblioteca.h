#ifndef biblioteca

// run = "gcc main.c biblioteca.c -o main && ./main"
// language = "c"
  
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <string.h>
#include <ctype.h>



typedef struct cripto {
  char nome[20];
  char ticker[10];
  char cotacao[20];
  char taxa_compra[20];
  char taxa_venda[20];
  char saldo[20];
} Cripto;


typedef struct cadastro {
  char tipo[20]; // tipo da conta
  char nome[51];
  char senha[15];
  char CPF[30];
  char real[30]; 
  char BTC[30];
  char RIP[30];
  char ETH[30];
  Cripto criptomoedas[10];
} Cadastro;



   /*                                       Prototipo das funcoes                                              */

void confirmacao(char *confirmar, char *nome, char *menu, char *sair); //funcao para continuar no menu ou sair do programa

void permissao (char *senharegistrada); // funcao para realizar a acao desejada apos a confirmacao de senha

void nome(char nome_mostra[], const char nome[]);

void consultar_extrato(char *registro, char *nome, char *cpf); 

void depositar(char *real, char *bitcoin_usuario, char *ripple_usuario, char *ethereum_usuario, char *registro);

void sacar (char *real, char *registro, char *bitcoin_usuario, char *ripple_usuario, char *ethereum_usuario);

void consultar_saldo(char *real,char *bitcoin,char *ripple,char *ethereum, char *nome, char *cpf,Cripto *criptomoedas, int total, Cadastro *usuario, int NV);

void comprar_criptomoeda(char *real_usuario, char *bitcoin_usuario, char *ripple_usuario, char *ethereum_usuario, char *registro, char *cotacao_btc2, char *cotacao_rip2, char *cotacao_eth2, Cripto *criptomoedas, int total, Cadastro *usuario, int NV);

void vender_criptomoeda(char *real_usuario, char *bitcoin_usuario, char *ripple_usuario, char *ethereum_usuario, char *registro, char *cotacao_btc1, char *cotacao_rip1, char *cotacao_eth1, Cripto *criptomoedas, int total, Cadastro *usuario, int NV);

void atualizar_cotacao(char *cotacao_btc, char *cotacao_rip, char *cotacao_eth, Cripto *criptomoedas, int total);

void cadastrar_investidor(Cadastro *usuarios, int *contador_cadastros, Cripto *criptomoedas, int total);

void excluir_investidor(Cadastro *usuarios, int *contador_cadastros, Cripto *criptomoedas, int total_criptomoedas); 

void consultar_saldo_investidor(Cadastro *usuarios, int *contador_cadastros,Cripto *criptomoedas, int total);

void consultar_extrato_investidor(Cadastro *usuarios, int *contador_cadastros, char registros[10][15]); 

void cadastrar_criptomoeda(Cripto *criptomoedas, int *total, Cadastro *usuarios, int *contador_cadastros);

int numero(char input[]); // verifica se eh numero

void excluir_criptomoeda(Cripto *criptomoedas, int *total,  Cadastro *usuarios, int *total_usuarios);
#endif


// PRECISO MUDAR AS FUNCOES: 

// COMPRAR CRIPTO (MUDEI)

// VENDER CRIPTOMOEDA (MUDEI)

// CONSULTAR SALDO (MUDEI)

// ATUALIZAR COTACAO  (MUDEI)

// CRIAR CRIPTOMOEDA (MUDEI)

// EXCLUIR CRIPTOMOEDA(MUDEI)

// CONSULTAR SALDO DE UM INVESTIDOR (MUDEI)

// CADASTRAR NOVO INVESTIDOR

// EXCLUIR INVESTIDOR (?)