#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> // Para função sleep

// Variáveis globais
double saldo_reais = 0, saldo_bitcoin = 0, saldo_ethereum = 0, saldo_ripple = 0;
double BTC = 500, ETH = 200, XRP = 100;
double variacao_bitcoin, variacao_ripple, variacao_ethereum;
char extrato[1000] = "";
char Nome[] = "Luca Juraski";
char login[12], senha[12];

// Funções auxiliares
void clear_screen() { system("clear || cls"); }

void ocultar_senha(char *senha) {
  printf("Senha: ");
  int i = 0;
  char ch;
  while ((ch = getchar()) != '\n' && i < 6) {
    if (ch == 127 || ch == '\b') { // Backspace
      if (i > 0) {
        i--;
        printf("\b \b");
      }
    } else {
      senha[i++] = ch;
      printf("*");
    }
  }
  senha[i] = '\0';
  printf("\n");
}
 
int exibir_menu() {
  int opcao;
  printf("\nBem-Vindo ao projeto!\n\n");
  printf("Escolha uma opção:\n");
  printf("[1] Cadastrar novo usuário\n");
  printf("[2] Fazer Login\n");
  printf("[3] Sair\n");
  printf("Digite sua opção: ");
  scanf("%d", &opcao);
  return opcao;
}


// Função para validar CPF (11 dígitos e apenas números)
int validar_cpf(char *cpf) {
  if (strlen(cpf) != 11) {
    printf("CPF deve ter 11 dígitos. Tente novamente!\n");
    return 0;
  }
  for (int i = 0; i < 11; i++) {
    if (!isdigit(cpf[i])) {
      printf("CPF deve conter apenas números. Tente novamente!\n");
      return 0;
    }
  }
  return 1;
}

// Função para fazer login (inclui validação do CPF e senha)
void fazer_login(char *login, char *senha) {
  int cpf_valido = 0;

  // Validar CPF
  while (!cpf_valido) {
    printf("CPF: ");
    scanf("%s", login);
    cpf_valido = validar_cpf(login);
  }

  // Limpar o buffer antes de pedir a senha
  while (getchar() != '\n')
    ; // Limpa o buffer do stdin

  // Validar senha
  while (1) {
    printf("Senha: ");
    scanf("%s", senha); // Removido ocultar_senha para facilitar a leitura do exemplo
    if (strlen(senha) < 6) {
      printf("Senha deve conter no mínimo 6 dígitos. Tente novamente!\n");
    } else {
      break;
    }
  }
}

#define MAX_USUARIOS 10  // Corrigido para usar #define

// Função para buscar usuário no arquivo
int buscar_usuario(char *login, char *senha) {
  FILE *arquivo;
  char cpf[12], pass[12];
  int encontrado = 0;

  arquivo = fopen("usuarios.txt", "r");
  if (arquivo == NULL) {
    return 0;
  }

  while (fscanf(arquivo, "%s %s", cpf, pass) != EOF) {
    if (strcmp(login, cpf) == 0 && strcmp(senha, pass) == 0) {
      encontrado = 1;
      break;
    }
  }

  fclose(arquivo);
  return encontrado;
}

// Função para contar o número de usuários cadastrados no arquivo
int contar_usuarios() {
  FILE *arquivo;
  char cpf[12], pass[12];
  int contador = 0;

  arquivo = fopen("usuarios.txt", "r");
  if (arquivo == NULL) {
    return 0;
  }

  // Conta quantas linhas existem no arquivo, cada linha corresponde a um usuário
  while (fscanf(arquivo, "%s %s", cpf, pass) != EOF) {
    contador++;
  }

  fclose(arquivo);
  return contador;
}

// Função para cadastrar um novo usuário
void cadastrar_usuario() {
  char login[12];
  char senha[12];
  int cpf_valido = 0;

  // Verifica se já existem 10 usuários cadastrados
  int total_usuarios = contar_usuarios();
  if (total_usuarios >= MAX_USUARIOS) {
    printf("Não é possível cadastrar mais usuários. Limite de %d atingido!\n", MAX_USUARIOS);
    return;
  }

  // Solicita e valida o CPF
  while (!cpf_valido) {
    printf("CPF: ");
    scanf("%s", login);
    cpf_valido = validar_cpf(login);
  }

  // Solicita e valida a senha
  while (1) {
    printf("Senha (mínimo 6 caracteres): ");
    scanf("%s", senha);
    if (strlen(senha) < 6) {
      printf("Senha deve conter no mínimo 6 dígitos. Tente novamente!\n");
    } else {
      break;
    }
  }

  // Adiciona o novo usuário ao arquivo
  FILE *arquivo = fopen("usuarios.txt", "a");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo!\n");
    return;
  }

  fprintf(arquivo, "%s %s\n", login, senha);
  fclose(arquivo);

  printf("Usuário cadastrado com sucesso!\n");
}

void obter_data_hora(char *buffer) {
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  sprintf(buffer, "%02d - %02d - %04d %02d : %02d", tm.tm_mday, tm.tm_mon + 1,
          tm.tm_year + 1900, tm.tm_hour, tm.tm_min);
}






























int main(void) {
  return 0;
}