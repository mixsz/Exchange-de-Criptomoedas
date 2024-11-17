# Exchange Criptomoedas (C) 

Feito por:
* Danilo Cardoso Pradella (mixsz) - 24.124.069-6 
* Felipe Pereira Munerato - 24.124.067-0 
* Caue Yusuke Bonets Ohta - 24.124.098-8

Este projeto tem como objetivo simular um aplicativo de compra e venda de criptomedas.
Para a execução do código será necessária a criação e cópia dos seguintes arquivos:
* main.c
* biblioteca.c
* biblioteca.h
* cotacao.txt
* usuario.txt (somente a criação)
* .replit (precisa digitar caso não rode: run = "gcc main.c biblioteca.c -o main && ./main"    [pula linha]      language = "c")
* criptomoeda.txt

Obs: Os registros.txt serão gerados automaticamente por conta do fluxo do código, não sendo necessária a sua criação


# Documentação Projeto - Exchange de Criptomoedas

## Menu Principal:

Na nova versão do código, o programa possui um menu principal, que serve para o usuário escolher o tipo de conta que ele possui (administrador ou investidor). O usuário só pode entrar em sua devida conta escolhendo o tipo de usuário certo, ou seja, se o usuário criou uma conta "investidor" e tentou logar no tipo "administrador", o programa irá informar que a conta não possui acesso a tal área e retornará ao menu.

## Tipo Usuário:

Cadastro de conta: É necessário que o usuário insira o nome completo, senha obrigatoriamente de 6 dígitos e CPF no formato: XXX.XXX.XXX-XX. 
Após digitar corretamente os dados fornecidos, o programa pedirá para o usuário confirmar o registro de conta com “S/s” ou “N/n”, caso o usuário digite “n/N”, o cadastro da conta será cancelado e ele retornará ao menu, se digitado “S/s” a conta será criada e armazenada (em TXT) em um arquivo onde ficará todos os perfis separados por linha, cada perfil terá os atributos na seguinte ordem: CPF, senha, nome, saldo inicializado com 0 (Real, Bitcoin, Ripple e Ethereum), e um arquivo separado contendo todos os extratos da conta individual (os arquivos de extrato são identificados e separados por ID) onde será armazenada as transações como o depósito, saque, compra de criptomoedas e vendas de criptomoedas.
Obs: Será possível criar no máximo 10 contas. Caso o usuário tente criar mais do que isso, uma mensagem de erro será exibida informando o limite excedido.

Login: Após o cadastro, o usuário será redirecionado ao menu, podendo acessar sua conta através do CPF e senha. O programa só continuará quando tais informações forem identificadas corretamente através do arquivo TXT de armazém de contas.

Voltar: Volta ao menu principal.

Menu: Depois de efetuar o login, o usuário verá o menu onde terá 8 opções para serem utilizadas. Cada ação é representada por um número de 1 a 8, qualquer outro valor será considerado inválido e o programa só continuará caso o usuário digite um valor correto (entre 1 a 8). O menu apresentará as seguintes ações:

1. Consultar saldo: Caso o usuário digite "1", o programa pedirá novamente a senha, se estiver correta, ele conseguirá ver precisamente o dinheiro armazenado, além de seus valores obtidos em criptomoedas. Será mostrado na seguinte ordem: 
* Nome
* CPF
* Real
* Bitcoin
* Ripple
* Ethereum
* Novas criptomoedas flexíveis
  
Obs: Caso o usuário esteja com o saldo totalmente zerado, aparecerá uma mensagem informando que o mesmo não possui saldo.

2. Consultar extrato: Se for digitado "2", o programa pedirá novamente sua senha, se estiver correta, o usuário verá todas as suas transações com as seguintes informações: data, horário, adição ou subtração de valor, valor, cotação da criptomoeda (se houver), taxação e saldo após a ação realizada.
Obs: Se o usuário não possuir uma transação, o programa mostrará apenas seu nome e CPF.

3. Depositar: Se for digitado "3", o programa pedirá a senha do usuário, se estiver correta, o usuário será informado com o saldo atual e depois poderá depositar uma quantia ilimitada apenas em R$, o valor não poderá ser negativo, igual a 0 ou qualquer coisa diferente de números, vírgula ou ponto (a função substitui “,” por “.” caso o usuário utilize).
Após digitar um valor válido, será mostrado uma mensagem informando que o depósito foi bem sucedido, o valor do depósito e o saldo após a ação.

4. Sacar: Para a ação "4", o programa pedirá a senha do usuário, se estiver certa, o usuário será informado com o saldo atual e então poderá sacar uma quantia válida em R$, se o valor estiver válido o programa mostrará a mensagem "Saque bem sucedido!", valor do saque e o saldo atualizado. Caso o usuário digite um valor inválido (negativo, igual a 0, maior que o saldo atual ou letras/caracteres), o programa exibirá uma mensagem informando que o mesmo não possui o valor inserido ou que o valor é inválido, e depois pedirá novamente uma quantia válida.

5. Comprar criptomoedas: A ação "5" realiza a compra dos 3 tipos de criptomoedas: Bitcoin, Ripple e Ethereum. Será pedido a senha, se estiver correta, o programa exibirá uma nova pergunta, onde será pedido um valor de 1 ao 4, cada valor terá sua respectiva criptomoeda, mostrando também a cotação de cada uma delas, além do botão "0" de cancelar a compra.
Se for digitado qualquer valor diferente de 1 - 2 - 3 - 4 - [ID das novas criptomoedas], o programa mostrará a mensagem "Digite um valor válido: " e só dará continuidade quando for cumprido o pedido.
Caso o usuário insira um valor de 1 a ID da criptomoeda final, o programa pedirá um valor na criptomoeda desejada, se for digitado um valor disponível, será exibido a mensagem "Compra realizada com sucesso!" e será atualizado seu saldo, descontando em Real o valor fornecido e adicionando na criptomoeda desejada, além de aplicar a taxa de compra junto com a cotação atual. Caso o valor seja incorreto como citado nas funções anteriores, o programa exibirá uma mensagem de erro e prosseguirá pedindo um valor válido..

6. Vender criptomoedas: A ação "6" realiza a venda dos 3 tipos de criptomoedas citado na ação anterior. Será pedido a senha, se estiver certa, o programa exibirá a mesma pergunta da ação anterior, e mostrará também os valores de cotação de cada criptomoeda. A resposta será válida do 1 ao número máximo de criptomoedas e se estiver incorreta, pedirá para o usuário digitar um valor válido.
Após o usuário escolher a criptomoeda, o programa pedirá para o usuário digitar um valor a ser vendido na moeda escolhida, se for digitado um valor válido, será exibido uma mensagem de venda bem sucedida, o saldo será atualizado, adicionando o valor em R$ (aplicando a taxa + cotação atual) e subtraindo o valor na criptomoeda fornecida.

7. Atualizar cotação: Essa ação é rápida e simples. Quando o usuário digitar "7", o programa atualizará a cotação individualmente dos tipos de criptomoedas, variando um valor entre -5% a 5% do valor anterior, esse número é aleatório e gerado pelo próprio programa. O usuário receberá apenas a mensagem "Cotação atualizada!" e o valores da cotação serão atualizados automaticamente. 
As cotações das criptomoedas FIXAS são armazenadas dentro de um arquivo TXT separadamente para facilitar a identificação, já as flexíveis estão em outro arquivo TXT.

8. Sair: Se o usuário digitar 8, o programa será finalizado e exibirá a seguinte mensagem: Tenha um ótimo dia, Sr(a)[nome do usuário]!


### Informações adicionais:

1.  Além das 8 funções já existentes, foram criadas mais duas chamadas “permissao” e “confirmacao” utilizadas para facilitar a leitura do código e reduzir redundâncias.

* Função permissão: Essa função tem como objetivo permitir acesso para outra função e é utilizada na ação “1” até a “6”. O usuário precisa informar a senha corretamente para prosseguir com o programa.

* Função confirmação: Função utilizada na maior parte do código após uma ação. Essa função tem o objetivo de identificar se o usuário quer continuar utilizando o sistema ou se quer sair através da mensagem “Deseja continuar? [S/N]:”  se a resposta for “n/N”, o programa é encerrado, caso contrário, o programa deve prosseguir.
Obs: A função só deve aceitar resposta válida.

2. Existem dois tipos de finalizar o programa:
* Usando a ação "8" (Sair).
* Com a função confirmação, se o input for “n/N”.

3. Os dados são salvos após cada ação onde haja mudança de dados.

4. As cotações são atualizadas individualmente por criptomoeda, porém são as mesmas para quaisquer perfis.

5. O usuário não pode criar uma conta com um CPF que já está sendo utilizado, caso contrário o programa mostrará uma mensagem informando que o CPF já está sendo utilizado.


# Tipo Administrador:

Na nova versão do código, foi implementado o sistema de administrador, que terá ações como gerenciar usuários, adicionar e excluir criptomoedas e visualizar perfis de investidores.

O menu continua sendo o mesmo para o tipo "administrador". O usuário tem a opção de criar uma conta, acessar uma conta, voltar ao menu principal ou sair. Como mencionado antes, o usuário só poderá logar em sua conta se ela for do tipo "administrador".

Menu: Depois de efetuar o login, o usuário verá o menu onde terá 8 opções para serem utilizadas. Cada ação é representada por um número de 1 a 8, qualquer outro valor será considerado inválido e o programa só continuará caso o usuário digite um valor correto (entre 1 a 8). O menu apresentará as seguintes ações:

1. Cadastrar novo investidor: O administrador poderá cadastrar novos investidores. O processo é o mesmo de um usuário, é necessário uma senha, CPF e nome do investidor.

2. Excluir investidor: O administrador tem a opção de excluir um investidor. É necessário informar o CPF corretamente (formato xxx.xxx.xxx-xx), após digitado, o programa mostrará informações de tal investidor e pedirá para o administrador confirmar ou cancelar a exclusão através da palavra "CONFIRMAR" e "CANCELAR".
Obs: Só poderá ser excluído contas do tipo "investidor" e caso seja digitado o CPF corretamente, caso o contrário, o administrador poderá voltar ao menu de ações.

3. Cadastrar nova criptomoeda: Agora é possível cadastrar novas criptomoedas. A nova versão do código consegue armazenar até 10 novas criptomoedas.
O administrador precisa informar o nome da criptomoeda (o nome será padronizado, ou seja, o programa fará com que a palavra digitada fique com a primeira letra maiúscula e as outras minúsculas, ou seja: Se digitado "novacriptoMOEDA", o programa ajustará a palavra para ficar padronizado como "Novacriptomoeda". Isso serve para facilitar a identificação se a criptomoeda já existe no programa, além de deixar visualmente mais bonito), o ticker da criptomoeda (exemplo: BTC, ETH, XRP, também será padronizado para tudo maiúsculo), a cotação da criptomoeda, taxa de compra e venda com valores decimais (caso não seja digitado em valor decimal, o programa fará o cálculo dessa taxa em momentos necessários).

4. Excluir nova criptomoeda: Além de criar novas criptomoedas, é possível excluí-las. É necessário informar o nome da criptomoeda, após isso, se digitado corretamente, o programa informará a cotação e taxa de venda/compra e pedirá para o administrador confirmar ou cancelar a exclusão através da palavra "CONFIRMAR" e "CANCELAR".
Obs: Não poderá ser excluídas as criptomoedas já utilizada na outra versão do código, ou seja, Bitcoin, Ethereum e Ripple continuam fixas como base das criptomoedas!

5. Consultar saldo de um investidor: O administrador poderá consultar o saldo de qualquer investidor sendo digitado corretamente o CPF, o resultado é o mesmo que o do tipo "investidor", será informado nome, CPF, saldo em real e as criptomoedas existentes.
Obs: A administrador não conseguirá acessar as informações de outro administrador.

6. Consultar extrato de um investidor: Assim como o saldo, o administrador poderá ver o extrato de qualquer investidor se digitado o CPF corretamente.

7. Atualizar cotação: Essa ação é rápida e simples. Quando o usuário digitar "7", o programa atualizará a cotação individualmente dos tipos de criptomoedas, variando um valor entre -5% a 5% do valor anterior, esse número é aleatório e gerado pelo próprio programa. O usuário receberá apenas a mensagem "Cotação atualizada!" e o valores da cotação serão atualizados automaticamente. 
As cotações das criptomoedas FIXAS são armazenadas dentro de um arquivo TXT separadamente para facilitar a identificação, já as flexíveis estão em outro arquivo TXT.

8. Sair: e o usuário digitar 8, o programa será finalizado e exibirá a seguinte mensagem: Tenha um ótimo dia Sr(a) [nome_user]!

### Informações adiconais e/ou importantes:

1. Não poderá ser cadastrado contas de diferentes tipos com o mesmo CPF.

2. Funções adicionais:

* Função numero: Verifica se o input é um número.

* Função nome: Tira os "_" do txt substituindo por espaços. Ou seja: Urso_Alves ----> Urso Alves

3. Foi implementado o novo arquivo criptomoeda.txt que salva as novas criptomoedas flexíveis.

4. As criptomoedas já existentes na versão anterior do código serão fixas, ou seja, não poderá ser feito nenhuma alteração nelas (apenas a cotação).

5. O limite de criptomoedas flexíveis é 10.
