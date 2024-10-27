# Gerenciador de Contatos
### Projeto em C para Gerenciamento de Lista Telefônica
> Este programa de agenda telefônica permite adicionar, visualizar, deletar e salvar contatos. Cada contato contém um nome e um número de telefone, armazenados em arquivos de texto e binário para preservar as informações entre as sessões.

## Objetivo

Desenvolver um sistema simples de gerenciamento de contatos com armazenamento local e interface baseada em terminal.

&nbsp;

## Compilação e Execução
Para compilar e executar o código, siga as instruções abaixo no terminal da sua IDE ou compilador:

1. **Compilação**:
   ```bash
   gcc main2.c -o main2.exe
   ```

2. **Execução**:
   ```bash
   ./main2.exe
   ```
   O programa então abrirá e permitirá a utilização das funcionalidades disponíveis.

&nbsp;

# **Structs**

## Contato
A struct `Contato` armazena as informações de cada contato, incluindo:
   - `nome`: Nome do contato (máximo de 50 caracteres).
   - `telefone`: Número de telefone (máximo de 15 caracteres).

&nbsp;

# **Funções**

### `adicionar_contato`
Adiciona um novo contato à lista. Solicita ao usuário que insira o nome e o telefone e armazena as informações. Após adicionar, o contato é salvo automaticamente nos arquivos `contatos.txt` (texto) e `contatos.bin` (binário).

### `lista_contatos`
Exibe todos os contatos atualmente salvos na lista. Se não houver contatos, informa que a lista está vazia.

### `salvar_texto` e `salvar_binario`
Salvam a lista de contatos em arquivos. `salvar_texto` armazena as informações no arquivo `contatos.txt`, enquanto `salvar_binario` as armazena em `contatos.bin` para facilitar a recuperação.

### `carregar_contatos`
Carrega os contatos do arquivo `contatos.bin` ao iniciar o programa, permitindo que a lista de contatos seja recuperada de sessões anteriores.

### `deletar_contato`
Permite que o usuário remova um contato específico da lista com base no índice fornecido. Após deletar, os arquivos são atualizados para refletir a mudança.

### `main`
Exibe um menu de opções, permitindo que o usuário adicione, visualize e delete contatos ou saia do programa. A interação é baseada em escolhas numéricas.

&nbsp;

# **Participantes**
- Breno Queiroga Faustino R.A: 22124001-3
- Rafael Levi Ramos Fernandes R.A: 22124057-5
- Vinicius Brasileiro Nobre R.A: 22124013-8
