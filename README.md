# Desenvolvimento de Algoritmos 
### Projeto 2
> A ideia do projeto é fazer um programa de advocacia para analisar agendamentos, processos realizados sob o CPF de uma pessoa. As informações mais pessoais somente poderiam ser acessadas pela pessoa, pelo advogado contratado ou providenciado e pelo juiz do caso

## Objetivo

&nbsp;

## Compliação e Execução
 - Para compilar o código, abra o terminal do compilador ou IDE escolhida e siga o passo a passo:
   - Digite: **gcc code.c -o code.exe** (onde está escrito "code", coloque o nome que você deu para o arquivo contendo o código)
   - Após isso, digite: **.\code.exe**
 - Com isso feito, o programa deve rolar normalmente.
   
&nbsp;

# **Structs**

## Usuário
 - A struct 'Usuario' armazena todas as informações necessárias para gerenciar a conta de um usuário, incluindo: 
    - Nome: Armazena o primeiro nome do usuário.
    - CPF: Identificador único do usuário.
    - Senha: Senha de acesso à conta.

&nbsp;
## Data

- A struct 'Data' armazena informações de data e hora para registrar quando cada transação foi realizada. Isso inclui:
    - Data: Estrutura 'tm' que contém detalhes como ano, mês, dia, hora, minuto e segundo.
    - Data2: String formatada que representa a data e hora em um formato legível.

&nbsp;
# **Funções**
&nbsp;
## Salvar Usuário
- A função "salvar_usuario" é responsável por gravar os dados do usuário no arquivo binário correspondente. Ela abre o arquivo em modo de escrita binária, escreve os dados da estrutura Usuario e fecha o arquivo. Se ocorrer algum erro durante a abertura do arquivo, uma mensagem de erro é exibida.
 

## Carregar Usuário
- A função "carregar_usuario" lê os dados do usuário a partir do arquivo binário correspondente ao CPF fornecido. Ela abre o arquivo em modo de leitura binária, lê os dados para a estrutura Usuario e fecha o arquivo. Se o arquivo não for encontrado ou ocorrer algum erro durante a leitura, a função retorna um código de erro.
 

## Cadastro de Usuário
- A função de cadastro permite que novos usuários criem uma conta no sistema. Durante o cadastro, o usuário deve fornecer:

    - Nome: O primeiro nome do usuário.
    - CPF: O Cadastro de Pessoas Físicas, utilizado como identificador único.
    - Senha: Uma senha segura para acessar a conta.
 

    - Após a inserção dessas informações, o sistema valida a senha para garantir que ela atende aos critérios de segurança (por exemplo, mínimo de 6 caracteres). Se a validação for bem-sucedida, os dados do usuário são salvos em um arquivo binário específico, nomeado pelo CPF do usuário, garantindo que cada usuário tenha seu próprio arquivo de dados.
 
&nbsp;

&nbsp;
## **Participantes**
- Breno Queiroga Faustino R.A: 22124001-3
- Rafael Levi Ramos Fernandes R.A: 22124057-5
- Vinicius Brasileiro Nobre R.A: 22124013-8
