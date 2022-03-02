#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "geraSintegra.h"

void menuPrincipal();
void menuSecundario();
void registrarEmp();
void logarNoSist();
void cadastrarProd();
void cadastrarForn();
void cadastrarCl();
void registrarComp();
void registrarVen();
void sintegra();
void verificador(char oDado[], char oqVerifica[], int tam);
int verificarCodigoForn(char cod[]);
int verificarCodigoCl(char cod[]);
int verificadorCodigoProd(char cod[]);

struct ARQUIVOs{
  FILE* cadastrarEmpresa;
  FILE* cadastroProdutos;         // STRUCT COM TODAS VARIÁVEIS DE ARQUIVOS
  FILE* fornecedores;
  FILE* registrarCompras;
  FILE* registrarVendas;
  FILE* comprasNF;
  FILE* vendasNF;
  FILE* clientes;
} arq;

struct CNPJs{ 
  char cnpjDeVerificar[20];
} cnpj;

struct CODIGOs{  
  char codigoVerificar[10];
} codigo;

struct FORNECEDOREs{
  char nomeEmpresaForn[100];
  char codigoFornecedor[10];      // STRUCT COM INFOS DOS FORNECEDORES
  char cnpjDoFornecedor[20]; 
} forn;

struct PRODUTOs{
  char codigoProduto[10];
  char nomeProduto[100];
  int qtdProduto;                 // STRUCT COM INFOS DOS PRODUTOS
  float valorProduto;
} produto;

struct CLIENTEs{
  char codigoCliente[10];
  char nomeCliente[100];          // STRUCT COM INFOS DOS CLIENTES
  char cnpjCliente[20];
} cl;

struct PROPRIETARIO{
  char cnpjDaEmpresa[20];
  char nomeEmpresa[100];
  char nome[100];           // STRUCT COM INFOS DO PROPRIETARIO
  char cpf[20];
} prop;

struct notaFiscalEntrada{
  char codigoEnt[10];
  int numeroNF;
  int serieNF;
  int qtdProdutoNF;           // STRUCT COM INFOS DA NF - ENTRADA
  float valorTTnf;
} nfEntrada;

struct notaFiscalSaida{
  char codigoSai[10];
  int numeroNF;
  int serieNF;
  int qtdProdutoNF;                // STRUCT COM INFOS DA NF - SAIDA
  float valorTTnf;
} nfSaida;

int main() {

  setlocale(LC_ALL, "Portuguese");

  menuPrincipal();

  return 0;
}

// ########################################################################################################
//                                                MENU PRINCIPAL

void menuPrincipal() {

    int op;

    puts("######################################");
    puts("#####    Escolha a operação   ########");
    puts("#####    1- Logar no sistema  ########");
    puts("#####    2- Cadastrar empresa ########");
    puts("#####    3- Sair              ########");
    puts("######################################");
    printf("     --> ");
    scanf("%d", &op);
    system("clear");

    switch(op){
        case 1:
          logarNoSist();
        break;
        case 2:
          registrarEmp();
        break;
        case 3:
          exit(0);
        break;
        default:
          menuPrincipal();
    }
}

// ########################################################################################################
//                                              MENU SECUNDARIO

void menuSecundario() {
  int op;
  puts("######################################");
  puts("#####    Escolha a operação   ########");
  puts("#####   1- Cadastrar Produtos ########");
  puts("#####   2- Registrar Compras  ########");
  puts("#####   3- Registrar Vendas   ########");
  puts("#####   4- Sintegra           ########");
  puts("#####   5- Voltar             ########");
  puts("#####   6- Sair               ########");
  puts("######################################");
  printf("    --> ");
  scanf("%d", &op);
  system("clear");

  switch(op){
    case 1:
      cadastrarProd();
    break;
    case 2:
      puts("######################################");
      puts("#####    Escolha a operação      #####");
      puts("#####   1- Cadastrar Fornecedor  #####");
      puts("#####   2- Registrar Compras     #####");
      puts("######################################");
      printf("    --> ");
      scanf("%d", &op);
      system("clear");
      switch(op){
        case 1:
          cadastrarForn();
        break;
        case 2:
          registrarComp();
        break;
        default:
          puts("Opção inválida!");
          menuSecundario();
      }
    break;
    case 3:
      puts("######################################");
      puts("#####    Escolha a operação      #####");
      puts("#####   1- Cadastrar Clientes    #####");
      puts("#####   2- Registrar Vendas      #####");
      puts("######################################");
      printf("    --> ");
      scanf("%d", &op);
      system("clear");
      switch(op){
        case 1:
          cadastrarCl();
        break;
        case 2:
        registrarVen();
        break;
        default:
          puts("Opção inválida!");
          menuSecundario();
      }
    break;
    case 4:
      sintegra();
    break;
    case 5:
      menuPrincipal();
    break;
    case 6:
      exit(0);
    default:
      puts("Opção inválida!");
      menuSecundario();
  }
}

// ########################################################################################################
//                                            CADASTRAR EMPRESA

void registrarEmp() {

  if((arq.cadastrarEmpresa = fopen("Empresa.txt", "w")) == NULL){
    puts("ERROR: Arquivo não encontrado!");
    exit(0);
  }
  
  puts("########            Cadastrar empresa            ########");
  puts("######## Digite todas as informações necessárias ########");
  printf("CNPJ da empresa..............: ");
  scanf("%s", prop.cnpjDaEmpresa);
  verificador(prop.cnpjDaEmpresa,  "CNPJ", 14);
  printf("Nome da empresa (Sem espaços): ");
  scanf("%s", prop.nomeEmpresa);
  printf("CPF do proprietário..........: ");
  scanf("%s", prop.cpf);
  verificador(prop.cpf, "CPF", 11);
  getchar();
  printf("Nome completo do proprietário: ");
  scanf("%[^\n]s", prop.nome);

  fprintf(arq.cadastrarEmpresa, "%s", prop.cnpjDaEmpresa);
  fprintf(arq.cadastrarEmpresa, "%14s", prop.nomeEmpresa);
  fprintf(arq.cadastrarEmpresa, "%14s", prop.cpf);
  fprintf(arq.cadastrarEmpresa, "%30s", prop.nome);
  fclose(arq.cadastrarEmpresa);

  system("clear");
  menuPrincipal();
}

// ########################################################################################################
//                                            LOGAR NO SISTEMA

void logarNoSist() {

  int op;

  puts("######################################");
  puts("#########    Insira o CNPJ   #########");
  puts("######################################");
  printf("      --> ");
  scanf("%s", cnpj.cnpjDeVerificar);

  verificador(cnpj.cnpjDeVerificar, "CNPJ", 14);
  system("clear");

  if((arq.cadastrarEmpresa = fopen("Empresa.txt", "r")) == NULL){
    puts("ERROR: Arquivo não encontrado!");
    exit(0);
  }

  fgets(prop.cnpjDaEmpresa, 15, arq.cadastrarEmpresa);
  fclose(arq.cadastrarEmpresa);

  if(strcmp(prop.cnpjDaEmpresa, cnpj.cnpjDeVerificar) == 0){
    menuSecundario();
  }else{
    puts("#############################################################################");
    puts("########                 Não foi possivel logar!                     ########");
    puts("########      Cadastre sua empresa ou insira novamente o cnpj        ########");
    puts("########                   1- Cadastrar empresa                      ########");
    puts("########                   2- Inserir cnpj                           ########");
    puts("########                   3- Sair                                   ########");
    puts("#############################################################################");
    printf("                       --> ");
    scanf("%d", &op);
    system("clear");
    switch(op){
      case 1:
        registrarEmp();
      break;
      case 2:
        logarNoSist();
      case 3:
        exit(0);
        break;
      default:
        puts("Opção inválida!");
        puts("Retornando ao menu...");
        menuPrincipal();
    }
  }
}

// ########################################################################################################
//                                            CADASTRAR PRODUTO

void cadastrarProd(){

  int op;
  int verify;

  puts("######## Digite todas as informações necessárias ########");
  puts("########           Cadastro de produtos          ########");
  printf("Digite o código do produto (00001 a 99999): ");
  scanf("%s", produto.codigoProduto);
  verificador(produto.codigoProduto, "Código", 5);

  verify = verificadorCodigoProd(produto.codigoProduto);

  if(verify == 1){
    system("clear");
    puts("########          Esse código já existe!!        ########");
    puts("#########################################################");
    cadastrarProd();
  }else{
    if((arq.cadastroProdutos = fopen("Produtos.txt", "a")) == NULL){
    puts("ERROR: Arquivo não encontrado!");
    exit(0);
    }

    printf("Digite o nome do produto (sem espaço).....: ");
    scanf("%s", produto.nomeProduto);
    printf("Digite o valor do produto.................: ");
    scanf("%f", &produto.valorProduto);
    printf("Digite a quantidade de produtos...........: ");
    scanf("%d", &produto.qtdProduto);
    
    fprintf(arq.cadastroProdutos, "%s", produto.codigoProduto);
    fprintf(arq.cadastroProdutos, "%30s", produto.nomeProduto);
    fprintf(arq.cadastroProdutos, "%10.2f", produto.valorProduto);
    fprintf(arq.cadastroProdutos, "%8d\n", produto.qtdProduto);
    fclose(arq.cadastroProdutos);

    system("clear");

    puts("########       Cadastro de produtos        ########");
    puts("###################################################");
    puts("#######   Cadastro realizado com sucesso!   #######");
    puts("#######   Deseja realizar mais cadastros?   #######");
    puts("#######   1- Sim                            #######");
    puts("#######   2- Voltar                         #######");
    puts("###################################################");
    printf("        --> ");
    scanf("%d", &op);
    system("clear");

    if (op == 1){
      cadastrarProd();
    }else if(op == 2){
      menuSecundario();
    }else{
      puts("Opção inválida!");
      puts("Retornando ao menu...");
      menuSecundario();
    }
  }
}

// ########################################################################################################
//                                          CADASTRAR FORNECEDORES

void cadastrarForn() {

  int op;
  int verify;

  puts("########          Cadastrar Fornecedores         ########");
  puts("######## Digite todas as informações necessárias ########");
  printf("Código do fornecedor (00001 a 99999): ");
  scanf("%s", forn.codigoFornecedor);
  verificador(forn.codigoFornecedor, "Código", 5);

  verify = verificarCodigoForn(forn.codigoFornecedor);

  if(verify == 1){
    system("clear");
    puts("########          Esse código já existe!!        ########");
    puts("#########################################################");
    cadastrarForn();
  }else{
    if((arq.fornecedores = fopen("Fornecedores.txt", "a")) == NULL){
    puts("ERROR: Arquivo não encontrado!");
    exit(0);
    }
    printf("CNPJ do fornecedor..................: ");
    scanf("%s", forn.cnpjDoFornecedor);
    verificador(forn.cnpjDoFornecedor, "CNPJ", 14);
    getchar();
    printf("Nome da empresa (Sem espaços).......: ");
    scanf("%s", forn.nomeEmpresaForn);

    fprintf(arq.fornecedores, "%s", forn.codigoFornecedor);
    fprintf(arq.fornecedores, "%18s", forn.cnpjDoFornecedor);
    fprintf(arq.fornecedores, "%30s\n", forn.nomeEmpresaForn);
    fclose(arq.fornecedores);

    system("clear");

    puts("#####     Cadastrar Fornecedores   ######");
    puts("#########################################");
    puts("#####    Escolha a operação        ######");
    puts("#####    1- Cadastrar Fornecedores ######");
    puts("#####    2- Voltar                 ######");
    puts("#####    3- Sair                   ######");
    puts("#########################################");
    printf("      --> ");
    scanf("%d", &op);

    system("clear");

    switch(op){
      case 1:
        cadastrarForn();
      break;
      case 2:
        menuSecundario();
      break;
      case 3:
        exit(0);
      break;
      default:
        puts("Opção inválida!");
        puts("Retornando ao menu...");
        menuSecundario();
    }
  }
}

// ########################################################################################################
//                                      CADASTRAR CLIENTES

void cadastrarCl() {

  int op;
  int verify;

  puts("########            Cadastrar Clientes           ########");
  puts("######## Digite todas as informações necessárias ########");
  printf("Código do cliente (00001 a 99999).....: ");
  scanf("%s", cl.codigoCliente);
  verificador(cl.codigoCliente, "Código", 5);

  verify = verificarCodigoCl(cl.codigoCliente);

  if(verify == 1){
    system("clear");
    puts("########          Esse código já existe!!        ########");
    puts("#########################################################");
    cadastrarCl();
  }else{
    if((arq.clientes = fopen("Cliente.txt", "a")) == NULL){
    puts("ERROR: Arquivo não encontrado!");
    exit(0);
    }
    printf("Digite o CNPJ do cliente..............: ");
    scanf("%s", cl.cnpjCliente);
    verificador(cl.cnpjCliente, "CNPJ", 14);
    printf("Digite o nome do cliente (sem espaços): ");
    scanf("%s", cl.nomeCliente);

    fprintf(arq.clientes, "%s", cl.codigoCliente);
    fprintf(arq.clientes, "%18s", cl.cnpjCliente);
    fprintf(arq.clientes, "%30s\n", cl.nomeCliente);
    fclose(arq.clientes);

    system("clear");

    puts("#####     Cadastrar clientes       ######");
    puts("#########################################");
    puts("#####    Escolha a operação        ######");
    puts("#####    1- Cadastrar clientes     ######");
    puts("#####    2- Voltar                 ######");
    puts("#####    3- Sair                   ######");
    puts("#########################################");
    printf("      --> ");
    scanf("%d", &op);

    system("clear");

    switch(op){
      case 1:
        cadastrarCl();
      break;
      case 2:
        menuSecundario();
      break;
      case 3:
        exit(0);
      break;
      default:
        puts("Opção inválida!");
        puts("Retornando ao menu...");
        menuSecundario();
    }
  }
}

// ########################################################################################################
//                                          REGISTRAR COMPRAS

void registrarComp(){

  int op = 1;
  int verify;

  puts("########         Registrar compras/NF            ########");
  puts("######## Digite todas as informações necessárias ########");
  printf("Código do fornecedor (00001 a 99999): ");
  scanf("%s", forn.codigoFornecedor);
  verificador(forn.codigoFornecedor, "Código", 5);

  verify = verificarCodigoForn(forn.codigoFornecedor);

  if(verify == 0){
    system("clear");
    puts("#############################################################################");
    puts("########                  Código não encontrado!                     ########");
    puts("########      Cadastre fornecedor ou insira novamente o código       ########");
    puts("########                   1- Cadastrar fornecedor                   ########");
    puts("########                   2- Inserir código                         ########");
    puts("########                   3- Voltar                                 ########");
    puts("########                   4- Sair                                   ########");
    puts("#############################################################################");
    printf("                       --> ");
    scanf("%d", &op);
    system("clear");
    switch(op){
      case 1:
        cadastrarForn();
      break;
      case 2:
        registrarComp();
      break;
      case 3:
        menuSecundario();
      break;
      case 4:
        exit(0);
      break;
      default:
        puts("Opção inválida!");
        puts("Retornando ao menu...");
        menuSecundario();
    }
  }else{
    if((arq.registrarCompras = fopen("produtoCompras.txt", "a")) == NULL){
    puts("ERROR: Arquivo não encontrado!");
    exit(0);
    }

    if((arq.comprasNF = fopen("NFcompras.txt", "a")) == NULL){
      puts("ERROR: Arquivo não encontrado!");
      exit(0);
    }
    printf("Numero da Nota......................: ");
    scanf("%d", &nfEntrada.numeroNF);
    printf("Serie da Nota.......................: ");
    scanf("%d", &nfEntrada.serieNF);

    fprintf(arq.comprasNF, "%s", forn.codigoFornecedor);
    fprintf(arq.comprasNF, "%8d",1101);
    fprintf(arq.comprasNF, "%8d", nfEntrada.numeroNF);
    fprintf(arq.comprasNF, "%5d", nfEntrada.serieNF);
    fclose(arq.comprasNF);

    system("clear");

    nfEntrada.valorTTnf = 0;
    nfEntrada.qtdProdutoNF = 0;

    while(op != 0){
      puts("########           Registrar compras             ########");
      puts("######## Digite todas as informações necessárias ########");
      printf("Digite o código do produto (00001 a 99999): ");
      scanf("%s", produto.codigoProduto);
      verificador(produto.codigoProduto, "Código", 5);
      printf("Digite o nome do produto (sem espaço).....: ");
      scanf("%s", produto.nomeProduto);
      printf("Digite o valor do produto.................: ");
      scanf("%f", &produto.valorProduto);
      printf("Digite a quantidade de produtos...........: ");
      scanf("%d", &produto.qtdProduto);
      
      nfEntrada.valorTTnf += (produto.valorProduto*produto.qtdProduto);
      nfEntrada.qtdProdutoNF += produto.qtdProduto;

      fprintf(arq.registrarCompras, "%s", forn.codigoFornecedor);
      fprintf(arq.registrarCompras, "%10s", produto.codigoProduto);
      fprintf(arq.registrarCompras, "%30s", produto.nomeProduto);
      fprintf(arq.registrarCompras, "%10.2f", produto.valorProduto);
      fprintf(arq.registrarCompras, "%8d\n", produto.qtdProduto);

      system("clear");

      puts("#####     Registrar Compras     ######");
      puts("######################################");
      puts("#####    Escolha a operação     ######");
      puts("#####    1- Continuar           ######");
      puts("#####    0- Sair                ######");
      puts("######################################");
      printf("      --> ");
      scanf("%d", &op);

      system("clear");
    }
      
    fclose(arq.registrarCompras);

    arq.comprasNF = fopen("NFcompras.txt", "a");
    fprintf(arq.comprasNF, "%10.2f", nfEntrada.valorTTnf);
    fprintf(arq.comprasNF, "%8d\n", nfEntrada.qtdProdutoNF);
    fclose(arq.comprasNF);

  }

  puts("#####     Registrar Compras     ######");
  puts("######################################");
  puts("#####    Escolha a operação     ######");
  puts("#####    1- Voltar              ######");
  puts("#####    2- Sair                ######");
  puts("######################################");
  printf("      --> ");
  scanf("%d", &op);

  system("clear");

  switch(op){
    case 1:
      menuSecundario();
    break;
    case 2:
      exit(1);
    default:
      puts("Opção inválida!");
      puts("Retornando ao menu...");
      menuSecundario();
  }
}

// ########################################################################################################
//                                           REGISTRAR VENDAS

void registrarVen(){

  int verify;
  int op = 1;

  puts("########          Registrar vendas/NF            ########");
  puts("######## Digite todas as informações necessárias ########");
  printf("Código do cliente (00001 a 99999)...: ");
  scanf("%s", cl.codigoCliente);
  verificador(cl.codigoCliente, "Código", 5);

  verify = verificarCodigoCl(cl.codigoCliente);

  if(verify == 0){
    system("clear");
    puts("#############################################################################");
    puts("########                  Código não encontrado!                     ########");
    puts("########        Cadastre cliente ou insira novamente o código        ########");
    puts("########                   1- Cadastrar cliente                      ########");
    puts("########                   2- Inserir código                         ########");
    puts("########                   3- Voltar                                 ########");
    puts("########                   4- Sair                                   ########");
    puts("#############################################################################");
    printf("                       --> ");
    scanf("%d", &op);
    system("clear");
    switch(op){
      case 1:
        cadastrarCl();
      break;
      case 2:
        registrarVen();
      break;
      case 3:
        menuSecundario();
      break;
      case 4:
        exit(0);
      break;
      default:
        puts("Opção inválida!");
        puts("Retornando ao menu...");
        menuSecundario();
    }
  }else{
    if ((arq.vendasNF = fopen ("NFvendas.txt", "a")) == NULL){
    puts("ERROR: Arquivo não encontrado!");
    exit(0);
    }
    
    if((arq.registrarVendas = fopen("produtoVendas.txt", "a")) == NULL){
      puts("ERROR: Arquivo não encontrado!");
      exit(0);
    }
    printf("Numero da Nota......................: ");
    scanf("%d", &nfSaida.numeroNF);
    printf("Serie da Nota.......................: ");
    scanf("%d", &nfSaida.serieNF);
    fprintf(arq.vendasNF, "%s", cl.codigoCliente);
    fprintf(arq.vendasNF, "%8d", 5101);
    fprintf(arq.vendasNF, "%8d", nfSaida.numeroNF);
    fprintf(arq.vendasNF, "%5d ", nfSaida.serieNF);
    fclose(arq.vendasNF);

    system("clear");

    nfSaida.valorTTnf = 0;
    nfSaida.qtdProdutoNF = 0;

    while(op != 0){
      puts("########           Registrar vendas              ########");
      puts("######## Digite todas as informações necessárias ########");
      printf("Digite o código do produto (00001 a 99999)....: ");
      scanf("%s", produto.codigoProduto);
      verificador(produto.codigoProduto, "Código", 5);

      verify = verificadorCodigoProd(produto.codigoProduto);

      if(verify == 1){
        printf("Digite a quantidade do produto que foi vendida: ");
        scanf("%d", &produto.qtdProduto);
        printf("Digite o valor do produto.....................: ");
        scanf("%f", &produto.valorProduto);

        fprintf(arq.registrarVendas, "%s", cl.codigoCliente);
        fprintf(arq.registrarVendas, "%10s", produto.codigoProduto);
        fprintf(arq.registrarVendas, "%10.2f", produto.valorProduto);
        fprintf(arq.registrarVendas, "%8d\n", produto.qtdProduto);

        nfSaida.valorTTnf += (produto.valorProduto*produto.qtdProduto);
        nfSaida.qtdProdutoNF += produto.qtdProduto;

        system("clear");

        puts("#####     Registrar Compras     ######");
        puts("######################################");
        puts("#####    Escolha a operação     ######");
        puts("#####    1- Continuar           ######");
        puts("#####    0- Sair                ######");
        puts("######################################");
        printf("      --> ");
        scanf("%d", &op);

        system("clear");
      }else{
        puts("ERROR: Não existe um produto cadastrado com esse código!");
      }
    }
    fclose(arq.registrarVendas);
  }

  arq.vendasNF = fopen("NFvendas.txt", "a");
  fprintf(arq.vendasNF, "%10.2f", nfSaida.valorTTnf);
  fprintf(arq.vendasNF, "%8d\n", nfSaida.qtdProdutoNF);
  fclose(arq.vendasNF);

  puts("########        Registro de vendas         ########");
  puts("###################################################");
  puts("#######   Registro realizado com sucesso!   #######");
  puts("#######   Deseja realizar mais Registros?   #######");
  puts("#######   1- Sim                            #######");
  puts("#######   2- Voltar                         #######");
  puts("###################################################");
  printf("        --> ");
  scanf("%d", &op);
  system("clear");

  if(op == 1){
    cadastrarProd();
  }else if(op == 2){
    menuSecundario();
  }else{
    puts("Opção inválida!");
    puts("Retornando ao menu...");
    menuSecundario();
  }
}

// ########################################################################################################
// GERAR SINTEGRA

void sintegra(){

  int auxInt[4];
  float auxFloat[3];
  char c;

  FILE* sint;

  // Registros 10 e 11
  if((arq.cadastrarEmpresa = fopen("Empresa.txt", "r")) == NULL){
    puts("ERROR: Arquivo não encontrado!");
    exit(0);
  }
  fscanf(arq.cadastrarEmpresa, "%s%s%s%[^\n]s", prop.cnpjDaEmpresa, prop.nomeEmpresa, prop.cpf, prop.nome);
  fclose(arq.cadastrarEmpresa);
  geraRegistro10(prop.cnpjDaEmpresa, prop.nomeEmpresa);
  geraRegistro11(prop.nome);

  // Registro 50 NF - Entrada
  if((arq.fornecedores = fopen("Fornecedores.txt", "r")) == NULL){
    puts("ERROR: Arquivo não encontrado!");
    exit(0);
  }
  while(!feof(arq.fornecedores)){
    if(fscanf(arq.fornecedores, "%s%s%s", forn.codigoFornecedor, forn.cnpjDoFornecedor, forn.nomeEmpresaForn) != EOF){
      if((arq.comprasNF = fopen("NFcompras.txt", "r")) == NULL){
      puts("ERROR: Arquivo não encontrado!");
      exit(0);
      }
      while(!feof(arq.comprasNF)){
        if(fscanf(arq.comprasNF, "%s%d%d%d%f%d", codigo.codigoVerificar, &auxInt[2], &auxInt[1], &auxInt[0], &auxFloat[0], &nfEntrada.qtdProdutoNF) != EOF){
          auxFloat[2] = 17;
          auxFloat[1] = auxFloat[0] * (auxFloat[2]/100);
          if(strcmp(forn.codigoFornecedor, codigo.codigoVerificar) == 0){
            geraRegistro50('T', forn.cnpjDoFornecedor, auxInt, auxFloat);
          }
        }
      }
      fclose(arq.comprasNF);
    }
  }
  fclose(arq.fornecedores);

  // Registro 50 NF - Saida
  if((arq.clientes = fopen("Cliente.txt", "r")) == NULL){
    puts("ERROR: Arquivo não encontrado!");
    exit(0);
  }
  while(!feof(arq.clientes)){
    if(fscanf(arq.clientes, "%s%s%s", cl.codigoCliente, cl.cnpjCliente, cl.nomeCliente) != EOF){
      if((arq.vendasNF = fopen("NFvendas.txt", "r")) == NULL){
        puts("ERROR: Arquivo não encontrado!");
        exit(0);
      }
      while(!feof(arq.vendasNF)){
        if(fscanf(arq.vendasNF, "%s%d%d%d%f%d", codigo.codigoVerificar, &auxInt[2], &nfSaida.numeroNF, &nfSaida.serieNF, &nfSaida.valorTTnf, &nfSaida.qtdProdutoNF) != EOF){
          auxFloat[2] = 17;
          auxFloat[1] = auxFloat[0] * (auxFloat[2]/100);
          if(strcmp(cl.codigoCliente, codigo.codigoVerificar) == 0){
            geraRegistro50('P', cl.cnpjCliente, auxInt, auxFloat);
          }
        }
      };
      fclose(arq.vendasNF);
    }
  }
  fclose(arq.clientes);

  // Registro 54 Produtos - Entrada
  if((arq.fornecedores = fopen("Fornecedores.txt", "r")) == NULL){
    puts("ERROR: Arquivo não encontrado!");
    exit(0);
  }
  while(!feof(arq.fornecedores)){
    if(fscanf(arq.fornecedores, "%s%s%s", forn.codigoFornecedor, forn.cnpjDoFornecedor, forn.nomeEmpresaForn) != EOF){
      if((arq.comprasNF = fopen("NFcompras.txt", "r")) == NULL){
        puts("ERROR: Arquivo não encontrado!");
        exit(0);
      }
      while(!feof(arq.comprasNF)){
        if(fscanf(arq.comprasNF, "%s%d%d%d%f%d", nfEntrada.codigoEnt, &auxInt[0], &auxInt[1], &auxInt[2], &nfEntrada.valorTTnf ,&nfEntrada.qtdProdutoNF) != EOF){
          if((arq.registrarCompras = fopen("produtoCompras.txt", "r")) == NULL){
            puts("ERROR: Arquivo não encontrado!");
            exit(0);
          }
          if(strcmp(forn.codigoFornecedor, nfEntrada.codigoEnt) == 0){
            while(!feof(arq.registrarCompras)){
              if(fscanf(arq.registrarCompras, "%s%s%s%f%d", codigo.codigoVerificar, produto.codigoProduto, produto.nomeProduto, &produto.valorProduto, &produto.qtdProduto) != EOF){
                if(strcmp(nfEntrada.codigoEnt, codigo.codigoVerificar) == 0){
                  auxFloat[0] = produto.valorProduto*produto.qtdProduto;
                  auxFloat[1] = 17;
                  auxInt[3] = produto.qtdProduto;
                  geraRegistro54(forn.cnpjDoFornecedor, produto.codigoProduto, auxInt, auxFloat);
                }
              }
            }
          }
          fclose(arq.registrarCompras);
        }
      }
      fclose(arq.comprasNF);
    }
  }
  fclose(arq.fornecedores);

  // Registro 54 Produtos - Saida
  if((arq.clientes = fopen("Cliente.txt", "r")) == NULL){
    puts("ERROR: Arquivo não encontrado!");
    exit(0);
  }
  while(!feof(arq.clientes)){
    if(fscanf(arq.clientes, "%s%s%s", cl.codigoCliente, cl.cnpjCliente, cl.nomeCliente) != EOF){
      if((arq.vendasNF = fopen("NFvendas.txt", "r")) == NULL){
        puts("ERROR: Arquivo não encontrado!");
        exit(0);
      }
      while(!feof(arq.vendasNF)){
        if(fscanf(arq.vendasNF, "%s%d%d%d%f%d", nfSaida.codigoSai, &auxInt[0], &auxInt[1], &auxInt[2], &nfSaida.valorTTnf ,&nfSaida.qtdProdutoNF) != EOF){
          if((arq.registrarVendas = fopen("produtoVendas.txt", "r")) == NULL){
            puts("ERROR: Arquivo não encontrado!");
            exit(0);
          }
          if(strcmp(cl.codigoCliente, nfSaida.codigoSai) == 0){
            while(!feof(arq.registrarVendas)){
              if(fscanf(arq.registrarVendas, "%s%s%f%d", codigo.codigoVerificar, produto.codigoProduto, &produto.valorProduto, &produto.qtdProduto) != EOF){
                if(strcmp(nfSaida.codigoSai, codigo.codigoVerificar) == 0){
                  auxFloat[0] = produto.valorProduto*produto.qtdProduto;
                  auxFloat[1] = 17;
                  auxInt[3] = produto.qtdProduto;
                  geraRegistro54(forn.cnpjDoFornecedor, produto.codigoProduto, auxInt, auxFloat);
                }
              }
            }
          }
          fclose(arq.registrarVendas);
        }
      }
      fclose(arq.vendasNF);
    }
  }
  fclose(arq.clientes);
  
  // Registro 74
  if((arq.cadastroProdutos = fopen("Produtos.txt", "r")) == NULL){
    puts("ERROR: Arquivo não encontrado!");
    exit(0);
  }
  while(!feof(arq.cadastroProdutos)){
    if(fscanf(arq.cadastroProdutos, "%s%s%f%d", produto.codigoProduto, produto.nomeProduto, &produto.valorProduto, &produto.qtdProduto) != EOF){
      auxFloat[0] = produto.valorProduto*produto.qtdProduto;
      geraRegistro74(prop.cnpjDaEmpresa, produto.codigoProduto, produto.qtdProduto, auxFloat[0]);
    }
  }
  fclose(arq.cadastroProdutos);

  // Registro 75
  if((arq.cadastroProdutos = fopen("Produtos.txt", "r")) == NULL){
    puts("ERROR: Arquivo não encontrado!");
    exit(0);
  }
  while(!feof(arq.cadastroProdutos)){
    if(fscanf(arq.cadastroProdutos, "%s%s%f%d", produto.codigoProduto, produto.nomeProduto, &produto.valorProduto, &produto.qtdProduto) != EOF){
      geraRegistro75(produto.codigoProduto, 17);
    }
  }
  fclose(arq.cadastroProdutos);

  // Imprimir na tela o arquivo sintegra
  if((sint = fopen("gerarSintegra.txt", "r")) == NULL){
    puts("ERROR: Arquivo não encontrado!");
    exit(0);
  }
  while(!feof(sint)){
    if(fscanf(sint, "%c", &c) != EOF){
      printf("%c", c);
    }
  }
  fclose(sint);
}

// ########################################################################################################
//                          VERIFICADOR DE CNPJ, CPF E CODIGO PARA VER SE É VALIDO

void verificador(char oDado[], char oqVerifica[], int tam){
  int qtd;
  do{
      qtd = 0;
      while(oDado[qtd] != '\0'){
        qtd++;
      }
      if(qtd != tam){
        printf("%s Inválido! - ", oqVerifica);
        printf("%s: ", oqVerifica);
        scanf("%s", oDado);
      }
  }while(qtd != tam);
}

// ########################################################################################################
//                                    VERIFICAR SE EXISTE FORNECEDOR

int verificarCodigoForn(char cod[]){

  if((arq.fornecedores = fopen("Fornecedores.txt", "r")) == NULL){
    puts("ERROR: Arquivo não encontrado!");
    exit(0);
  }

  do{
    fscanf(arq.fornecedores, "%s%s%s", codigo.codigoVerificar, forn.cnpjDoFornecedor, forn.nomeEmpresaForn);
    if(strcmp(cod, codigo.codigoVerificar) == 0){
      fclose(arq.fornecedores);
      return 1;
    }
  }while(!feof(arq.fornecedores));
  fclose(arq.fornecedores);
  
  return 0;
}

// ########################################################################################################
//                                    VERIFICAR SE EXISTE CLIENTE

int verificarCodigoCl(char cod[]){

  if((arq.clientes = fopen("Cliente.txt", "r")) == NULL){
    puts("ERROR: Arquivo não encontrado!");
    exit(0);
  }

  do{
    fscanf(arq.clientes, "%s%s%s", codigo.codigoVerificar, cl.cnpjCliente, cl.nomeCliente);
    if(strcmp(cod, codigo.codigoVerificar) == 0){
      fclose(arq.clientes);
      return 1;
    }
  }while(!feof(arq.clientes));
  fclose(arq.clientes);
  
  return 0;
}

// ########################################################################################################
//                                       VERIFICAR SE EXISTE PRODUTO

int verificadorCodigoProd(char cod[]){

  if((arq.cadastroProdutos = fopen("Produtos.txt", "r")) == NULL){
    puts("ERROR: Arquivo não encontrado!");
    exit(0);
  }

  do{
    fscanf(arq.cadastroProdutos, "%s%s%f%d", codigo.codigoVerificar, produto.nomeProduto, &produto.valorProduto, &produto.qtdProduto);
    if(strcmp(cod, codigo.codigoVerificar) == 0){
      fclose(arq.cadastroProdutos);
      return 1;
    }
  }while (!feof(arq.cadastroProdutos));
  fclose(arq.cadastroProdutos);

  return 0;
}