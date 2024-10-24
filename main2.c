#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WHITE_BOLD "\e[1;37m"   // Branco e Negrito
#define GREEN_UNDER "\e[4;32m"  // Verde e Sublinhado
#define GREEN_BOLD "\e[1;92m"    // Verde e Negrito
#define RESET "\x1b[0;37m"       // Branco
#define BACKGROUND_RED "\e[41m"  // Fundo Vermelho
#define RED_BOLD "\033[1;31m"    // Vermelho e Negrito
#define CYAN_BOLD " \e[1;36m"    // Ciano e Negrito

#define MAX_CONTATOS 100
#define NOME_LEN 50
#define TELEFONE_LEN 15

typedef struct {
    char nome[NOME_LEN];
    char telefone[TELEFONE_LEN];
} Contato;

void salvar_texto(Contato contatos[], int num_contatos);
void salvar_binario(Contato contatos[], int num_contatos);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int adicionar_contato(Contato contatos[], int *num_contatos) {
    if (*num_contatos >= MAX_CONTATOS) {
        printf(BACKGROUND_RED "Limite de contatos atingido.\n" RESET);
        return 0;
    }
    printf(CYAN_BOLD "Digite o nome do contato: " RESET);
    scanf(" %[^\n]", contatos[*num_contatos].nome);
    printf(CYAN_BOLD "Digite o telefone: " RESET);
    scanf(" %[^\n]", contatos[*num_contatos].telefone);
    (*num_contatos)++;

    // Salvar automaticamente após adicionar um contato
    salvar_texto(contatos, *num_contatos);
    salvar_binario(contatos, *num_contatos);
    printf(GREEN_BOLD "Contato salvo com sucesso!\n" RESET);
    return 1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void lista_contatos(Contato contatos[], int num_contatos) {
  if(num_contatos == 0){
    printf(BACKGROUND_RED " Nenhum contato encontrado. :< " RESET "\n");
  }
  else{
  for (int i = 0; i < num_contatos; i++) {
      printf(GREEN_UNDER "Contato %d: " GREEN_BOLD "%s - %s\n" RESET, i + 1, contatos[i].nome, contatos[i].telefone);
   }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void salvar_texto(Contato contatos[], int num_contatos) {
    FILE *file = fopen("contatos.txt", "w");
    if (file == NULL) {
        printf(BACKGROUND_RED "Erro ao abrir o arquivo.\n" RESET);
        return;
    }
    for (int i = 0; i < num_contatos; i++) {
        fprintf(file, "%s,%s\n", contatos[i].nome, contatos[i].telefone);
    }
    fclose(file);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void salvar_binario(Contato contatos[], int num_contatos) {
    FILE *file = fopen("contatos.bin", "wb");
    if (file == NULL) {
        printf(BACKGROUND_RED "Erro ao abrir o arquivo.\n" RESET);
        return;
    }
    fwrite(contatos, sizeof(Contato), num_contatos, file);
    fclose(file);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int carregar_contatos(Contato contatos[]) {
    FILE *file = fopen("contatos.bin", "rb");
    int num_contatos = fread(contatos, sizeof(Contato), MAX_CONTATOS, file);
    fclose(file);
    return num_contatos;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deletar_contato(Contato contatos[], int *num_contatos) {
    int index;
    printf(CYAN_BOLD "Digite o numero do contato a ser deletado: " RESET);
    scanf("%d", &index);

    if (index < 1 || index > *num_contatos) {
        printf(BACKGROUND_RED "Numero invalido!\n" RESET);
        return;
    }

    for (int i = index - 1; i < *num_contatos - 1; i++) {
        contatos[i] = contatos[i + 1];
    }
    (*num_contatos)--;

    // Salvar após deletar um contato
    salvar_texto(contatos, *num_contatos);
    salvar_binario(contatos, *num_contatos);
    printf(GREEN_BOLD "Contato deletado com sucesso!\n" RESET);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    Contato contatos[MAX_CONTATOS];
    int num_contatos = carregar_contatos(contatos);
    int opcao;

    do {
        printf(GREEN_BOLD "\n====== Bem Vindo ao seu perfil de Contatos. Escolha uma das opcoes abaixo. ======\n" RESET);
        printf(CYAN_BOLD "1. Adicionar contato\n" RESET);
        printf(CYAN_BOLD "2. Lista contatos\n" RESET);
        printf(CYAN_BOLD "3. Deletar contato\n" RESET);
        printf(CYAN_BOLD "4. Sair\n" RESET);
        printf(GREEN_BOLD "Escolha uma opcao: " RESET);
        scanf("%d", &opcao);

        switch (opcao) {
          case 1:
            adicionar_contato(contatos, &num_contatos);
            break;
          case 2:
            lista_contatos(contatos, num_contatos);
            break;
          case 3:
            deletar_contato(contatos, &num_contatos);
            break;
          case 4:
            printf(RED_BOLD "Saindo...\n" RESET);
            printf(GREEN_UNDER "Volte sempre :> \n" RESET);
            return 0;
          default:
            printf("Opção inválida!\n");
      }
    } while (opcao != 0);

  return 0;
}
