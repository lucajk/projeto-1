# Sistema de Gerenciamento de Criptomoedas

## Descrição do Projeto

Este projeto é um sistema de gerenciamento de criptomoedas que permite aos usuários cadastrar-se, fazer login, depositar e sacar dinheiro, além de comprar e vender criptomoedas como Bitcoin (BTC), Ethereum (ETH) e Ripple (XRP). O sistema também oferece a funcionalidade de visualizar saldos e extratos de transações.

## Funcionalidades

- Cadastrar novos usuários com CPF e senha.
- Fazer login com CPF e senha.
- Consultar saldo em reais e criptomoedas.
- Consultar extrato de transações.
- Depositar e sacar valores em reais.
- Comprar e vender criptomoedas.
- Atualização das cotações de criptomoedas com variações aleatórias.

## Pré-requisitos

- Um compilador C (por exemplo, `gcc`).
- Sistema operacional compatível com comandos `clear` e `sleep` (Linux ou MacOS).

## Como Compilar

Para compilar o projeto, siga as etapas abaixo:

1. Abra o terminal.
2. Navegue até o diretório onde o arquivo de código fonte (`sistema_criptomoedas.c`) está localizado.
3. Execute o seguinte comando para compilar o código:

   ```bash
   gcc -o sistema_criptomoedas sistema_criptomoedas.c
