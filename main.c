#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> // Para função sleep


int main() {
  int opcao;

  while (1) {
    printf("\n[1] Cadastrar novo usuário\n[2] Fazer Login\n[3] Sair\n");
    printf("Digite sua opção: ");
    scanf("%d", &opcao);

    if (opcao == 1) {
      // Cadastro de novo usuário
      fazer_login(login, senha);
      if (buscar_usuario(login, senha)) {
        printf("Usuário já existente!\n");
      } else {
        FILE *arquivo = fopen("usuarios.txt", "a");
        if (arquivo != NULL) {
          fprintf(arquivo, "%s %s\n", login, senha);
          fclose(arquivo);
          printf("Cadastro aprovado!\n");
        } else {
          printf("Erro ao abrir o arquivo de usuários!\n");
        }
      }
    } else if (opcao == 2) {
      // Fazer login
      fazer_login(login, senha);
      if (buscar_usuario(login, senha)) {
        printf("Login realizado com sucesso!\n");
        menu();
      } else {
        printf("Usuário ou senha incorretos. Tente novamente!\n");
      }
    } else if (opcao == 3) {
      printf("Goodbye!\n");
      break;
    } else {
      printf("Opção inválida!\n");
    }
  }

  return 0;
}


          #define MAX_INVESTIDORES 100
          #define MAX_CRIPTOS 50

          // Estruturas
          typedef struct {
              char nome[50];
              char cpf[12];
              char senha[20];
              float saldo;
              char extrato[1000];
          } Investidor;

          typedef struct {
              char nome[50];
              float cotacao;
              float taxaCompra;
              float taxaVenda;
          } Criptomoeda;

          // Funções auxiliares
          void limparBuffer() {
              int c;
              while ((c = getchar()) != '\n' && c != EOF);
          }

          void salvarInvestidores(Investidor investidores[], int numInvestidores) {
              FILE *arquivo = fopen("investidores.dat", "wb");
              if (arquivo) {
                  fwrite(&numInvestidores, sizeof(int), 1, arquivo);
                  fwrite(investidores, sizeof(Investidor), numInvestidores, arquivo);
                  fclose(arquivo);
              }
          }

          void carregarInvestidores(Investidor investidores[], int *numInvestidores) {
              FILE *arquivo = fopen("investidores.dat", "rb");
              if (arquivo) {
                  fread(numInvestidores, sizeof(int), 1, arquivo);
                  fread(investidores, sizeof(Investidor), *numInvestidores, arquivo);
                  fclose(arquivo);
              } else {
                  *numInvestidores = 0;
              }
          }

          void salvarCriptomoedas(Criptomoeda criptos[], int numCriptos) {
              FILE *arquivo = fopen("criptomoedas.dat", "wb");
              if (arquivo) {
                  fwrite(&numCriptos, sizeof(int), 1, arquivo);
                  fwrite(criptos, sizeof(Criptomoeda), numCriptos, arquivo);
                  fclose(arquivo);
              }
          }

          void carregarCriptomoedas(Criptomoeda criptos[], int *numCriptos) {
              FILE *arquivo = fopen("criptomoedas.dat", "rb");
              if (arquivo) {
                  fread(*numCriptos, sizeof(int), 1, arquivo);
                  fread(criptos, sizeof(Criptomoeda), *numCriptos, arquivo);
                  fclose(arquivo);
              } else {
                  *numCriptos = 0;
              }
          }

          // Funções principais
          void cadastrarInvestidor(Investidor investidores[], int *numInvestidores) {
              if (*numInvestidores >= MAX_INVESTIDORES) {
                  printf("Limite de investidores atingido.\n");
                  return;
              }
              Investidor novo;
              printf("Nome: ");
              fgets(novo.nome, 50, stdin);
              strtok(novo.nome, "\n");
              printf("CPF: ");
              fgets(novo.cpf, 12, stdin);
              strtok(novo.cpf, "\n");
              printf("Senha: ");
              fgets(novo.senha, 20, stdin);
              strtok(novo.senha, "\n");
              novo.saldo = 0.0;
              strcpy(novo.extrato, "Extrato Inicial\n");

              investidores[(*numInvestidores)++] = novo;
              salvarInvestidores(investidores, *numInvestidores);
              printf("Investidor cadastrado com sucesso.\n");
          }

          void excluirInvestidor(Investidor investidores[], int *numInvestidores) {
              char cpf[12];
              printf("Digite o CPF do investidor a ser excluído: ");
              fgets(cpf, 12, stdin);
              strtok(cpf, "\n");

              for (int i = 0; i < *numInvestidores; i++) {
                  if (strcmp(investidores[i].cpf, cpf) == 0) {
                      printf("Investidor encontrado: %s\n", investidores[i].nome);
                      printf("Confirmar exclusão? (s/n): ");
                      char confirmacao;
                      scanf(" %c", &confirmacao);
                      limparBuffer();
                      if (confirmacao == 's') {
                          for (int j = i; j < *numInvestidores - 1; j++) {
                              investidores[j] = investidores[j + 1];
                          }
                          (*numInvestidores)--;
                          salvarInvestidores(investidores, *numInvestidores);
                          printf("Investidor excluído com sucesso.\n");
                      }
                      return;
                  }
              }
              printf("Investidor não encontrado.\n");
          }
          void cadastrarCriptomoeda(Criptomoeda criptos[], int *numCriptos) {
              if (*numCriptos >= MAX_CRIPTOS) {
                  printf("Limite de criptomoedas atingido.\n");
                  return;
              }
              Criptomoeda nova;
              printf("Nome: ");
              limparBuffer();
              fgets(nova.nome, 50, stdin);
              strtok(nova.nome, "\n");
              printf("Cotação inicial: ");
              scanf("%f", &nova.cotacao);
              printf("Taxa de compra (%%): ");
              scanf("%f", &nova.taxaCompra);
              printf("Taxa de venda (%%): ");
              scanf("%f", &nova.taxaVenda);
              limparBuffer();

              criptos[(*numCriptos)++] = nova;
              salvarCriptomoedas(criptos, *numCriptos);
              printf("Criptomoeda cadastrada com sucesso!.\n");
          }

          void excluirCriptomoeda(Criptomoeda criptos[], int *numCriptos) {
              char nome[50];
              printf("Digite o nome da criptomoeda a ser excluída: ");
              limparBuffer();
              fgets(nome, 50, stdin);
              strtok(nome, "\n");

              for (int i = 0; i < *numCriptos; i++) {
                  if (strcmp(criptos[i].nome, nome) == 0) {
                      printf("Criptomoeda encontrada: %s\n", criptos[i].nome);
                      printf("Confirmar exclusão? (s/n): ");
                      char confirmacao;
                      scanf(" %c", &confirmacao);
                      limparBuffer();
                      if (confirmacao == 's') {
                          for (int j = i; j < *numCriptos - 1; j++) {
                              criptos[j] = criptos[j + 1];
                          }
                          (*numCriptos)--;
                          salvarCriptomoedas(criptos, *numCriptos);
                          printf("Criptomoeda excluída com sucesso.\n");
                      }
                      return;
                  }
              }
              printf("Criptomoeda não encontrada.\n");
          }

          void consultarSaldo(Investidor investidores[], int numInvestidores) {
              char cpf[12];
              printf("Digite o CPF do investidor: ");
              fgets(cpf, 12, stdin);
              strtok(cpf, "\n");

              for (int i = 0; i < numInvestidores; i++) {
                  if (strcmp(investidores[i].cpf, cpf) == 0) {
                      printf("Saldo do investidor %s: R$%.2f\n", investidores[i].nome, investidores[i].saldo);
                      return;
                  }
              }
              printf("Investidor não encontrado.\n");
          }

          void consultarExtrato(Investidor investidores[], int numInvestidores) {
              char cpf[12];
              printf("Digite o CPF do investidor: ");
              fgets(cpf, 12, stdin);
              strtok(cpf, "\n");

              for (int i = 0; i < numInvestidores; i++) {
                  if (strcmp(investidores[i].cpf, cpf) == 0) {
                      printf("Extrato do investidor %s:\n%s", investidores[i].nome, investidores[i].extrato);
                      return;
                  }
              }
              printf("Investidor não encontrado.\n");
          }