#include <stdio.h>
          #include <stdlib.h>
          #include <string.h>

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
