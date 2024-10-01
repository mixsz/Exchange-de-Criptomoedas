# Exchange Criptomoedas (C) 

Feito por:
* Danilo Cardoso Pradella (mixsz) - 24.124.069-6 
* Felipe Pereira Munerato - 24.124.067-0 
* Caue Yusuke Bonets Ohta - 24.124.098-8


Documentação Projeto - Exchange de Criptomoedas

Cadastro de conta: É necessário que o usuário insira o nome completo, senha obrigatoriamente de 6 dígitos e CPF no formato: XXX.XXX.XXX-XX. 
Após digitar corretamente os dados fornecidos, o programa pedirá para o usuário confirmar o registro de conta com “S/s” ou “N/n”, caso o usuário digite “n/N”, o cadastro da conta será cancelado e ele retornará ao menu, se digitado “S/s” a conta será criada e armazenada (em TXT) em um arquivo onde ficará todos os perfis separados por linha, cada perfil terá os atributos na seguinte ordem: CPF, senha, nome, saldo inicializado com 0 (Real, Bitcoin, Ripple e Ethereum), e um arquivo separado contendo todos os extratos da conta individual (os arquivos de extrato são identificados e separados por ID) onde será armazenada as transações como o depósito, saque, compra de criptomoedas e vendas de criptomoedas.
Obs: Será possível criar no máximo 10 contas. Caso o usuário tente criar mais do que isso, uma mensagem de erro será exibida informando o limite excedido.

Login: Após o cadastro, o usuário será redirecionado ao menu, podendo acessar sua conta através do CPF e senha. O programa só continuará quando tais informações forem identificadas corretamente através do arquivo TXT de armazém de contas .

Menu: Depois de efetuar o login, o usuário verá o menu onde terá 8 opções para serem utilizadas. Cada ação é representada por um número de 1 a 8, qualquer outro valor será considerado inválido e o programa só continuará caso o usuário digite um valor correto (entre 1 a 8). O menu apresentará as seguintes ações:

1. Consultar saldo: Caso o usuário digite "1", o programa pedirá novamente a senha, se estiver correta, ele conseguirá ver precisamente o dinheiro armazenado, além de seus valores obtidos em criptomoedas. Será mostrado na seguinte ordem: 
* Nome
* CPF
* Real
* Bitcoin
* Ripple
* Ethereum
  
Obs: Caso o usuário esteja com o saldo totalmente zerado, aparecerá uma mensagem informando que o mesmo não possui saldo.

2. Consultar extrato: Se for digitado "2", o programa pedirá novamente sua senha, se estiver correta, o usuário verá todas as suas transações com as seguintes informações: data, horário, adição ou subtração de valor, valor, cotação da criptomoeda (se houver), taxação e saldo após a ação realizada.
Obs: Se o usuário não possuir uma transação, o programa mostrará apenas seu nome e CPF.

3. Depositar: Se for digitado "3", o programa pedirá a senha do usuário, se estiver correta, o usuário será informado com o saldo atual e depois poderá depositar uma quantia ilimitada apenas em R$, o valor não poderá ser negativo, igual a 0 ou qualquer coisa diferente de números, vírgula ou ponto (a função substitui “,” por “.” caso o usuário utilize).
Após digitar um valor válido, será mostrado uma mensagem informando que o depósito foi bem sucedido, o valor do depósito e o saldo após a ação.

4. Sacar: Para a ação "4", o programa pedirá a senha do usuário, se estiver certa, o usuário será informado com o saldo atual e então poderá sacar uma quantia válida em R$, se o valor estiver válido o programa mostrará a mensagem "Saque bem sucedido!", valor do saque e o saldo atualizado. Caso o usuário digite um valor inválido (negativo, igual a 0, maior que o saldo atual ou letras/caracteres), o programa exibirá uma mensagem informando que o mesmo não possui o valor inserido ou que o valor é inválido, e depois pedirá novamente uma quantia válida.

5. Comprar criptomoedas: A ação "5" realiza a compra dos 3 tipos de criptomoedas: Bitcoin, Ripple e Ethereum. Será pedido a senha, se estiver correta, o programa exibirá uma nova pergunta, onde será pedido um valor de 1 ao 4, cada valor terá sua respectiva criptomoeda, mostrando também a cotação de cada uma delas, além do botão "4" de cancelar a compra.
Se for digitado qualquer valor diferente de 1 - 2 - 3 - 4, o programa mostrará a mensagem "Digite um valor válido: " e só dará continuidade quando for cumprido o pedido.
Caso o usuário insira um valor de 1 a 3, o programa pedirá um valor na criptomoeda desejada, se for digitado um valor disponível, será exibido a mensagem "Compra realizada com sucesso!" e será atualizado seu saldo, descontando em Real o valor fornecido e adicionando na criptomoeda desejada, além de aplicar a taxa de compra junto com a cotação atual. Caso o valor seja incorreto como citado nas funções anteriores, o programa exibirá uma mensagem de erro e prosseguirá pedindo um valor válido..

6. Vender criptomoedas: A ação "6" realiza a venda dos 3 tipos de criptomoedas citado na ação anterior. Será pedido a senha, se estiver certa, o programa exibirá a mesma pergunta da ação anterior, e mostrará também os valores de cotação de cada criptomoeda. A resposta será válida do 1 ao 4 e se estiver incorreta, pedirá para o usuário digitar um valor válido.
Após o usuário escolher a criptomoeda, o programa pedirá para o usuário digitar um valor a ser vendido na moeda escolhida, se for digitado um valor válido, será exibido uma mensagem de venda bem sucedida, o saldo será atualizado, adicionando o valor em R$ (aplicando a taxa + cotação atual) e subtraindo o valor na criptomoeda fornecida.

7. Atualizar cotação: Essa ação é rápida e simples. Quando o usuário digitar "7", o programa atualizará a cotação individualmente dos 3 tipos de criptomoedas, variando um valor entre -5% a 5% do valor anterior, esse número é aleatório e gerado pelo próprio programa. O usuário receberá apenas a mensagem "Cotação atualizada!" e o valores da cotação serão atualizados automaticamente. 
As 3 cotações são armazenadas dentro de um arquivo TXT para facilitar a identificação.

8. Sair: Se o usuário digitar 8, o programa será finalizado e exibirá a seguinte mensagem: Tenha um ótimo dia, Sr(a)[nome do usuário]!


Informações adicionais:

1.  Além das 8 funções já existentes, foram criadas mais duas chamadas “permissao” e “confirmacao” utilizadas para facilitar a leitura do código e reduzir redundâncias.

*1.1. Função permissão: Essa função tem como objetivo permitir acesso para outra função e é utilizada na ação “1” até a “6”. O usuário precisa informar a senha corretamente para prosseguir com o programa.

*1.2 Função confirmação: Função utilizada na maior parte do código após uma ação. Essa função tem o objetivo de identificar se o usuário quer continuar utilizando o sistema ou se quer sair através da mensagem “Deseja continuar? [S/N]:”  se a resposta for “n/N”, o programa é encerrado, caso contrário, o programa deve prosseguir.
Obs: A função só deve aceitar resposta válida.

2. Existem dois tipos de finalizar o programa:

*2.1 Usando a ação "8" (Sair).

*2.2 Com a função confirmação, se o input for “n/N”.

3. Os dados são salvos após a ação.

4. As cotações são atualizadas individualmente por criptomoeda, porém são as mesmas para quaisquer perfis.

5. O usuário não pode criar uma conta com um CPF que já está sendo utilizado, caso contrário o programa mostrará uma mensagem informando que o CPF já está sendo utilizado.

