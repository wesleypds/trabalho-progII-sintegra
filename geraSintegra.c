#include <stdlib.h>
#include <stdio.h>
#include "geraSintegra.h"

struct arqSintegra{ 
  FILE* sintegra;
} file;

void geraRegistro10(char cpnj[], char nomeEmpresa[]){
  char IE[] = "ES1234561";
  char municipio[] = "Marataizes";
  char UE[] = "ES";
  char dataInicio[] = "20220222";
  char dataFinal[] = "20220222";
  if((file.sintegra = fopen("gerarSintegra.txt", "w")) == NULL){
    puts("ERROR: Arquivo não encontrado!");
    exit(0);
  }
  fprintf(file.sintegra, "10");
  fprintf(file.sintegra, "%-14s", cpnj);
  fprintf(file.sintegra, "%-14s", IE);
  fprintf(file.sintegra, "%-35s", nomeEmpresa);
  fprintf(file.sintegra, "%-30s", municipio);
  fprintf(file.sintegra, "%-2s", UE);
  fprintf(file.sintegra, "%-8s", dataInicio);
  fprintf(file.sintegra, "%-8s\n", dataFinal);
  fclose(file.sintegra);
}

void geraRegistro11(char nome[]){
  char logradouro[] = "Avenida Simaos Soares";
  char numero[] = "1100";
  char complemento[] =  "Proxima a praça";
  char bairro[] = "Barra";
  char CEP[] = "29395000";
  if((file.sintegra = fopen("gerarSintegra.txt", "a")) == NULL){
    puts("ERROR: Arquivo não encontrado!");
    exit(0);
  }
  fprintf(file.sintegra, "11");
  fprintf(file.sintegra, "%-34s", logradouro);
  fprintf(file.sintegra, "%-5s", numero);
  fprintf(file.sintegra, "%-22s", complemento);
  fprintf(file.sintegra, "%-15s", bairro);
  fprintf(file.sintegra, "%-8s", CEP);
  fprintf(file.sintegra, "%-28s\n", nome);
  fclose(file.sintegra);
}

void geraRegistro50(char emitente, char cnpj[], int auxInt[], float auxFloat[]){
  char IEempresa[] = "ES1234561";
  char IEcliente[] = "ES0264846";
  char dataEm[] = "20220222";
  char UF[] = "ES";
  if((file.sintegra = fopen("gerarSintegra.txt", "a")) == NULL){
    puts("ERROR: Arquivo não encontrado!");
    exit(0);
  }
  fprintf(file.sintegra, "50");
  fprintf(file.sintegra, "%-14s", cnpj);
  if(emitente == 'T'){
    fprintf(file.sintegra, "%-14s", IEcliente);
  }else{
    fprintf(file.sintegra, "%-14s", IEempresa);
  }
  fprintf(file.sintegra, "%-8s", dataEm);
  fprintf(file.sintegra, "%-2s", UF);
  fprintf(file.sintegra, "%-3d", auxInt[0]);
  fprintf(file.sintegra, "%-6d", auxInt[1]);
  fprintf(file.sintegra, "%-4d", auxInt[2]);
  fprintf(file.sintegra, "%-1c", emitente);
  fprintf(file.sintegra, "%-13.2f", auxFloat[0]);
  fprintf(file.sintegra, "%-13.2f", auxFloat[1]);
  fprintf(file.sintegra, "%-4.2f\n", auxFloat[2]);
  fclose(file.sintegra);
}

void geraRegistro54(char cnpj[], char codigo[], int auxInt[], float auxFloat[]){
  if((file.sintegra = fopen("gerarSintegra.txt", "a")) == NULL){
    puts("ERROR: Arquivo não encontrado!");
    exit(0);
  }
  fprintf(file.sintegra, "54");
  fprintf(file.sintegra, "%-14s", cnpj);
  fprintf(file.sintegra, "%-3d", auxInt[2]);
  fprintf(file.sintegra, "%-6d", auxInt[1]);
  fprintf(file.sintegra, "%-4d", auxInt[0]);
  fprintf(file.sintegra, "%-14s", codigo);
  fprintf(file.sintegra, "%-11d", auxInt[3]);
  fprintf(file.sintegra, "%-12.2f", auxFloat[0]);
  fprintf(file.sintegra, "%-4.2f\n", auxFloat[1]);
  fclose(file.sintegra);
}

void geraRegistro74(char cnpj[], char codigo[], float qtdPro, float valorPro){
  char UF[] = "ES";
  char dataInvent[] = "20220222";
  char IE[] = "ES1234561";
  if((file.sintegra = fopen("gerarSintegra.txt", "a")) == NULL){
    puts("ERROR: Arquivo não encontrado!");
    exit(0);
  }
  fprintf(file.sintegra, "74");
  fprintf(file.sintegra, "%-8s", dataInvent);
  fprintf(file.sintegra, "%-14s", codigo);
  fprintf(file.sintegra, "%-13.3f", qtdPro);
  fprintf(file.sintegra, "%-13.2f", valorPro);
  fprintf(file.sintegra, "%-14s", cnpj);
  fprintf(file.sintegra, "%-14s", IE);
  fprintf(file.sintegra, "%-2s\n", UF);
  fclose(file.sintegra);
}

void geraRegistro75(char codigo[], float icms){
  char dataIn[] = "20220222";
  char dataFin[] = "20220222";
  char uniMed[] = "un";
  if((file.sintegra = fopen("gerarSintegra.txt", "a")) == NULL){
    puts("ERROR: Arquivo não encontrado!");
    exit(0);
  }
  fprintf(file.sintegra, "75");
  fprintf(file.sintegra, "%-8s", dataIn);
  fprintf(file.sintegra, "%-8s", dataFin);
  fprintf(file.sintegra, "%-14s", codigo);
  fprintf(file.sintegra, "%-6s", uniMed);
  fprintf(file.sintegra, "%-4.2f\n", icms);
  fclose(file.sintegra);
}