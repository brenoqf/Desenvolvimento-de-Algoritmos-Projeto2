#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ANSI_COLOR_GREEN_BOLD "\e[1;92m"  // Verde e Negrito
#define ANSI_COLOR_GREEN_UNDER "\e[4;32m" // Verde e Sublinhado
#define ANSI_COLOR_RESET "\x1b[0;37m"     // Branco
#define ANSI_BACKGROUND_RED "\e[41m"      // Fundo Vermelho
#define ANSI_COLOR_CYAN_BOLD " \e[1;36m"  // Ciano e Negrito
#define MAX_TRANSACTIONS 100

typedef struct {
  char nome[50];
  char CPF[14];
  char senha[50];
  float saldo;
  float bit;
  float eth;
  float rip;
  char transacoes[MAX_TRANSACTIONS][100];
  int num_transacoes;
} Usuario;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Data {
  struct tm data;
  char data2[20];
};

void dia_hora(struct Data *d) {
  time_t t = time(NULL);
  d->data = *localtime(&t);

  strftime(d->data2, sizeof(d->data2), "%d-%m-%Y / %H:%M", &d->data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Função para salvar um usuário em um arquivo .dat
int salvar_usuario(const Usuario *user) {
  char filename[64];
  snprintf(filename, sizeof(filename), "%s.dat", user->CPF);

  FILE *file =
      fopen(filename, "wb"); // "wb" para abrir em modo de escrita binária
  if (file == NULL) {
    perror("Erro ao abrir o arquivo");
    return -1;
  }
  fwrite(user, sizeof(Usuario), 1, file);
  fclose(file);
  return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Função para carregar os arquivos salvos
int carregar_usuario(const char *cpf, Usuario *user) {
  char filename[64];
  snprintf(filename, sizeof(filename), "%s.dat", cpf);

  FILE *file =
      fopen(filename, "rb"); // "rb" para abrir em modo de leitura binária
  if (file == NULL) {
    return -1;
  }

  size_t read = fread(user, sizeof(Usuario), 1, file);
  fclose(file);

  // Verifica se a leitura foi bem-sucedida
  if (read != 1) {
    return -1;
  }

  // Validação básica dos dados
  if (user->num_transacoes < 0 || user->num_transacoes > MAX_TRANSACTIONS) {
    return -1;
  }

  return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int validar_senha(const char *senha) {
  if (strlen(senha) < 6) {
    printf(ANSI_BACKGROUND_RED "Senha muito curta, deve ter pelo menos 6 "
                               "caracteres." ANSI_COLOR_RESET "\n");
    return -1;
  }
  return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int validar_cpf(const char *cpf) {
  if (strlen(cpf) < 11) {
    printf(ANSI_BACKGROUND_RED
           "CPF invalido, deve ter 11 caracteres.\n" ANSI_COLOR_RESET);
    return -1;
  }
  return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Função que mostra as opções de cadastro e login
void inicio() {
  int escolha;
  printf(ANSI_COLOR_CYAN_BOLD
         "====== Seja bem-vindo ao Exchange de Criptomoedas "
         "======" ANSI_COLOR_GREEN_BOLD "\nEscolha uma das opcoes a "
         "seguir:\n\n1.Login\n2.Cadastro\n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_GREEN_UNDER "Insira sua escolha:" ANSI_COLOR_RESET " ");
  scanf("%d", &escolha);

  while (escolha != 1 && escolha != 2) {
    printf(ANSI_BACKGROUND_RED
           "Opcao não existente, por favor, insira novamente\n" ANSI_COLOR_RESET
           "\n");
    scanf("%d", &escolha);
  }

  if (escolha == 1) {
    printf("\n");
    //login();
  } else if (escolha == 2) {
    printf("\n");
    //cadastro();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main(void) {

}
