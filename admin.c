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
              printf("Criptomoeda cadastrada com sucesso.\n");
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

          void atualizarCotacao(Criptomoeda criptos[], int numCriptos) {
              char nome[50];
              printf("Digite o nome da criptomoeda: ");
              limparBuffer();
              fgets(nome, 50, stdin);
              strtok(nome, "\n");

              for (int i = 0; i < numCriptos; i++) {
                  if (strcmp(criptos[i].nome, nome) == 0) {
                      printf("Cotação atual da %s: R$%.2f\n", criptos[i].nome, criptos[i].cotacao);
                      printf("Nova cotação: ");
                      scanf("%f", &criptos[i].cotacao);
                      salvarCriptomoedas(criptos, numCriptos);
                      printf("Cotação da %s atualizada com sucesso.\n", criptos[i].nome);
                      return;
                  }
              }
              printf("Criptomoeda não encontrada.\n");
          }

          // Main
          int main() {
              Investidor investidores[MAX_INVESTIDORES];
              Criptomoeda criptos[MAX_CRIPTOS];
              int numInvestidores, numCriptos;

              carregarInvestidores(investidores, &numInvestidores);
              carregarCriptomoedas(criptos, &numCriptos);

              int opcao;
              do {
                  printf("\n--- Menu Administrador ---\n");
                  printf("1. Cadastrar novo investidor\n");
                  printf("2. Excluir investidor\n");
                  printf("3. Cadastrar criptomoeda\n");
                  printf("4. Excluir criptomoeda\n");
                  printf("5. Consultar saldo do investidor\n");
                  printf("6. Consultar extrato do investidor\n");
                  printf("7. Atualizar cotação de criptomoeda\n");
                  printf("8. Sair\n");
                  printf("Escolha uma opção: ");
                  scanf("%d", &opcao);
                  limparBuffer();
                  
                  switch (opcao) {
                      case 1:
                          cadastrarInvestidor(investidores, &numInvestidores);
                          break;
                      case 2:
                          excluirInvestidor(investidores, &numInvestidores);
                          break;
                      case 3:
                          cadastrarCriptomoeda(criptos, &numCriptos);
                          break;
                      case 4:
                          excluirCriptomoeda(criptos, &numCriptos);
                          break;
                      case 5:
                          consultarSaldo(investidores, numInvestidores);
                          break;
                      case 6:
                          consultarExtrato(investidores, numInvestidores);
                          break;
                      case 7:
                          atualizarCotacao(criptos, numCriptos);
                          break;
                      case 8:
                          printf("Encerrando...\n");
                          break;
                      default:
                          printf("Opção inválida.\n");
                  }
                  } while (opcao != 8);
                  
                  return 0;
                  } 