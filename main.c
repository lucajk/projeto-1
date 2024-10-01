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



































int main(void) {
  return 0;
}