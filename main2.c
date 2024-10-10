#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WHITE_BOLD "\e[1;37m"  // Branco e Negrito
#define GREEN_UNDER "\e[4;32m" // Verde e Sublinhado
#define RESET "\x1b[0;37m"     // Branco
#define BACKGROUND_RED "\e[41m"      // Fundo Vermelho
#define CYAN_BOLD " \e[1;36m"  // Ciano e Negrito

typedef struct {
    char nome[255];
    char CPF[14];
    char senha[50];
    int casos[50];
} Cliente;

typedef struct {
    char nome[255];
    char CPF[14];
    char senha[50];

} Advogado;

struct Data {
  struct tm data;
  char data2[20];
};

void dia_hora(struct Data *d) {
  time_t t = time(NULL);
  d->data = *localtime(&t);

  strftime(d->data2, sizeof(d->data2), "%d-%m-%Y / %H:%M", &d->data);
}

// Função para salvar um usuário em um arquivo .dat
int salvar_usuario(const Cliente *user) {
  char filename[64];
  snprintf(filename, sizeof(filename), "%s.dat", user->CPF);

  FILE *file =
      fopen(filename, "wb"); // "wb" para abrir em modo de escrita binária
  if (file == NULL) {
    perror("Erro ao abrir o arquivo");
    return -1;
  }
  fwrite(user, sizeof(Cliente), 1, file);
  fclose(file);
  return 0;
}

// Função para carregar os arquivos salvos
int carregar_usuario(const char *cpf, Cliente *user) {
  char filename[64];
  snprintf(filename, sizeof(filename), "%s.dat", cpf);

  FILE *file =
      fopen(filename, "rb"); // "rb" para abrir em modo de leitura binária
  if (file == NULL) {
    return -1;
  }

  size_t read = fread(user, sizeof(Cliente), 1, file);
  fclose(file);

  // Verifica se a leitura foi bem-sucedida
  if (read != 1) {
    return -1;
  }
  return 0;
}

int validar_cpf(const char *cpf) {
  if (strlen(cpf) < 11) {
    printf(BACKGROUND_RED "CPF invalido, deve ter 11 caracteres.\n" RESET);
    return -1;
  }
  return 0;
}

int validar_senha(const char *senha) {
  if (strlen(senha) < 6) {
    printf(BACKGROUND_RED "Senha muito curta, deve ter pelo menos 6 "
                               "caracteres." RESET "\n");
    return -1;
  }
  return 0;
}


int inicio() {
    int choice;
    
    printf(WHITE_BOLD "==== Programa de Advocacia ====\n" RESET);
    printf(WHITE_BOLD "1. Cadastro de Advogado\n2. Login de Advogado\n3. Cadastro de Cliente\n4. Login de Cliente\n" RESET);
    printf("Escolha uma das opcoes acima: ");
    scanf("%i", choice);
    return 0;
}



int main() {
    inicio();
    return 0;
}
