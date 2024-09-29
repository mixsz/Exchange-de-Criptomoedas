#ifndef biblioteca

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

   /*                                       Prototipo das funcoes                                              */

void confirmacao(char *confirmar, char *nome, char *menu, char *sair); //funcao para continuar no menu ou sair do programa

void permissao (char *senharegistrada); // funcao para realizar a acao desejada apos a confirmacao de senha

void consultar_extrato(char *registro); // funcao para consultar o extrato)

void depositar(char *real, char *bitcoin_usuario, char *ripple_usuario, char *ethereum_usuario, char *registro);

void sacar (char *real, char *registro, char *bitcoin_usuario, char *ripple_usuario, char *ethereum_usuario);

void consultar_saldo(char *real,char *bitcoin,char *ripple,char *ethereum);

void comprar_criptomoeda(char *real_usuario, char *bitcoin_usuario, char *ripple_usuario, char *ethereum_usuario, char *registro);

void vender_criptomoeda(char *real_usuario, char *bitcoin_usuario, char *ripple_usuario, char *ethereum_usuario, char *registro);

#endif
