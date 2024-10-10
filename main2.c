#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define WHITE_BOLD "\e[1;37m"   // Branco e Negrito
#define GREEN_UNDER "\e[4;32m"  // Verde e Sublinhado
#define GREEN_BOLD "\e[1;92m"  // Verde e Negrito
#define RESET "\x1b[0;37m"      // Branco
#define BACKGROUND_RED "\e[41m" // Fundo Vermelho
#define CYAN_BOLD " \e[1;36m"   // Ciano e Negrito

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
    char OAB[8];
} Advogado;

struct Data {
  struct tm data;
  char data2[20];
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void dia_hora(struct Data *d) {
  time_t t = time(NULL);
  d->data = *localtime(&t);

  strftime(d->data2, sizeof(d->data2), "%d-%m-%Y / %H:%M", &d->data);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Função para verificação de CPF
int validar_cpf(const char *cpf) {
  if (strlen(cpf) < 11) {
    printf(BACKGROUND_RED "CPF invalido, deve ter 11 caracteres.\n" RESET);
    return -1;
  }
  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Função para verificação de senha
int validar_senha(const char *senha) {
  if (strlen(senha) < 6) {
    printf(BACKGROUND_RED "Senha muito curta, deve ter pelo menos 6 caracteres." RESET "\n");
    return -1;
  }
  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int login_cliente() {
  Cliente user;
  Cliente user_arquivo;
  char senha[50];

  printf(WHITE_BOLD "=========== Login de Cliente =========== " WHITE_BOLD "\nPara realizar siga as seguintes instrucoes\n" RESET);

  // Inserir CPF
  printf(GREEN_UNDER "Insira seu CPF:" RESET " ");
  scanf("%13s", user.CPF);

  // Inserir senha
  printf(GREEN_UNDER "Insira sua senha:" RESET " ");
  scanf("%49s", senha);

  // Verificar se o CPF foi cadastrado e carregar dados
  if (carregar_usuario(user.CPF, &user_arquivo) != 0) {
    printf(BACKGROUND_RED"Usuario com CPF %s nao encontrado." RESET "\n\n", user.CPF);
    inicio();
    return -1;
  }

  // Verificar se o nome e a senha correspondem
  if (strcmp(senha, user_arquivo.senha) == 0) {
    printf(WHITE_BOLD "Login realizado com sucesso.\n" RESET);
    menu(user_arquivo.CPF, user_arquivo.nome);
  } else {
    printf(BACKGROUND_RED "Nome ou senha incorretos.\n" RESET "\n");
    inicio();
    return -1;
  }

  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cadastro_cliente() {
  Cliente user;
  char senha[50], confsenha[50];

  printf(WHITE_BOLD "=========== Cadastro de Cliente ===========\nPara realizar siga as seguintes instrucoes\n" RESET);

  // Cadastrar nome
  printf(WHITE_BOLD "\nInsira seu primeiro nome:" RESET " ");
  scanf("%49s", user.nome);

  // Cadastrar CPF
  printf(WHITE_BOLD "Insira seu CPF:" RESET " ");
  scanf("%13s", user.CPF);

  // Cadastrar senha
  printf(WHITE_BOLD "Insira sua senha:" RESET " ");
  scanf("%49s", senha);

  // Confirmar senha
  printf(WHITE_BOLD "Confirme sua senha:" RESET " ");
  scanf("%49s", confsenha);

  if (strcmp(senha, confsenha) == 0) {
    if (validar_senha(senha) != 0) {
      if (validar_senha(senha) != 0) {
        return -1;
      }
    }
    strcpy(user.senha, senha);

    // Inicializa todas as transações como strings vazias (opcional, mas recomendado)

    if (salvar_usuario(&user) == 0) {
      printf(WHITE_BOLD "Cadastro realizado com sucesso\n" RESET "\n");
      //menu(user.CPF, user.nome);
    } else {
      printf(BACKGROUND_RED "Erro ao salvar informacoes.\n" RESET "\n\n");
    }
  } else {
    printf(BACKGROUND_RED "Informacoes inseridas incorretamente, por favor, insira-as novamente\n" RESET "\n\n");
    cadastro_cliente();
  }
  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int login_advogado() {
  Advogado user;
  Advogado user_arquivo;
  char senha[50];

  printf(WHITE_BOLD "=========== Login de Advogado =========== " WHITE_BOLD "\nPara realizar siga as seguintes instrucoes\n" RESET);

  // Inserir CPF
  printf(GREEN_UNDER "Insira seu CPF:" RESET " ");
  scanf("%13s", user.CPF);

  // Inserir senha
  printf(GREEN_UNDER "Insira sua senha:" RESET " ");
  scanf("%49s", senha);

  // Inserir OAB
  printf(GREEN_UNDER "Insira sua OAB:" RESET " ");
  scanf("%9s", user.OAB);

  // Verificar se o CPF foi cadastrado e carregar dados
  if (carregar_usuario(user.CPF, &user_arquivo) != 0) {
    printf(BACKGROUND_RED"Usuario com CPF %s nao encontrado." RESET "\n\n", user.CPF);
    inicio();
    return -1;
  }

  // Verificar se o nome e a senha correspondem
  if (strcmp(senha, user_arquivo.senha) == 0) {
    printf(WHITE_BOLD "Login realizado com sucesso.\n" RESET);
    menu(user_arquivo.CPF, user_arquivo.nome);
  } else {
    printf(BACKGROUND_RED "Nome,senha ou OAB incorretos.\n" RESET "\n");
    inicio();
    return -1;
  }

  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cadastro_advogado() {
  Advogado user;
  char senha[50], confsenha[50];

  printf(WHITE_BOLD "=========== Cadastro de Cliente ===========\nPara realizar siga as seguintes instrucoes\n" RESET);

  // Cadastrar nome
  printf(WHITE_BOLD "\nInsira seu primeiro nome:" RESET " ");
  scanf("%49s", user.nome);

  // Cadastrar CPF
  printf(WHITE_BOLD "Insira seu CPF:" RESET " ");
  scanf("%13s", user.CPF);

  // Cadastrar senha
  printf(WHITE_BOLD "Insira sua senha:" RESET " ");
  scanf("%49s", senha);

  // Confirmar senha
  printf(WHITE_BOLD "Confirme sua senha:" RESET " ");
  scanf("%49s", confsenha);

  if (strcmp(senha, confsenha) == 0) {
    if (validar_senha(senha) != 0) {
      if (validar_senha(senha) != 0) {
        return -1;
      }
    }
    strcpy(user.senha, senha);

    // Inicializa todas as transações como strings vazias (opcional, mas recomendado)

    if (salvar_usuario(&user) == 0) {
      printf(WHITE_BOLD "Cadastro realizado com sucesso\n" RESET "\n");
      //menu(user.CPF, user.nome);
    } else {
      printf(BACKGROUND_RED "Erro ao salvar informacoes.\n" RESET "\n\n");
    }
  } else {
    printf(BACKGROUND_RED "Informacoes inseridas incorretamente, por favor, insira-as novamente\n" RESET "\n\n");
    cadastro_cliente();
  }
  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int inicio() {
    int escolha;
    
    printf(WHITE_BOLD "==== Programa de Advocacia ====\n" RESET);
    printf(WHITE_BOLD "1. Cadastro de Advogado\n2. Login de Advogado\n3. Cadastro de Cliente\n4. Login de Cliente\n" RESET);
    printf("Escolha uma das opcoes acima: ");
    scanf("%i", &escolha);


    if (escolha == 1) {
      printf("Cadastro Advogado");
    } else if (escolha == 2) {
      printf("Login Advogado");
    } else if (escolha == 3) {
      printf("\n");
      cadastro_cliente();
    } else if (escolha == 4) {
      printf("\n");
      login_cliente();
    } else {
      printf("essa escolha n existe cafajeste");
    }


    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void menu_cliente(const char *cpf, const char *nome) {
  int escolha;
  char senha[50];
  Cliente user;

  if (carregar_usuario(cpf, &user) != 0) {
    printf(BACKGROUND_RED "Erro ao carregar usuário.\n" RESET
                               "\n");
    return;
  }

  while (1) {
    printf(CYAN_BOLD);
    printf("\n ========== Menu do Cliente ========== \n");
    printf(GREEN_BOLD);
    printf("Bem-vindo, %s!\n", user.nome); // Exibe o nome do usuário
    printf("1. Consultar casos\n");
    printf("2. Registrar caso\n");
    printf("3. Advogados disponíveis\n");
    printf("4. Sair\n");

    printf("Escolha uma opcao: ");
    printf(RESET);
    scanf("%d", &escolha);

    switch (escolha) {
    case 1:
      printf("\n");
      consultar_caso(cpf);
      break;
    case 2:
      printf("\n");
      registrar_caso(cpf);
      break;
    case 3:
      printf("\n");
      adv(cpf);
      break;
    case 4:
      printf(GREEN_BOLD
             "Tudo Bem. Aguarde um momento.\nSaindo da conta...\nConta "
             "deslogada com sucesso.\n" RESET "\n");
      inicio();
      break;
    default:
      printf("Opção invalida. Tente novamente.\n");
      break;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void menu_advogado(const char *cpf, const char *nome) {
  int escolha;
  char senha[50];
  Advogado user;

  if (carregar_usuario(cpf, &user) != 0) {
    printf(BACKGROUND_RED "Erro ao carregar usuário.\n" RESET
                               "\n");
    return;
  }

  while (1) {
    printf(CYAN_BOLD);
    printf("\n ========== Menu do Advogado ========== \n");
    printf(GREEN_BOLD);
    printf("Bem-vindo, %s!\n", user.nome); // Exibe o nome do usuário
    printf("1. Casos em análise\n");
    printf("2. Casos disponiveis\n");
    printf("3. Clientes\n");
    printf("4. Sair\n");

    printf("Escolha uma opcao: ");
    printf(RESET);
    scanf("%d", &escolha);

    switch (escolha) {
    case 1:
      printf("\n");
      casos_analise(cpf);
      break;
    case 2:
      printf("\n");
      casos_disponivel(cpf);
      break;
    case 3:
      printf("\n");
      clint(cpf);
      break;
    case 4:
      printf(GREEN_BOLD
             "Tudo Bem. Aguarde um momento.\nSaindo da conta...\nConta "
             "deslogada com sucesso.\n" RESET "\n");
      inicio();
      break;
    default:
      printf("Opção invalida. Tente novamente.\n");
      break;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    inicio();
    return 0;
}
