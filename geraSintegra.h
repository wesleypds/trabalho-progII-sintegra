#include <stdio.h>
#ifndef SINTEGRA_H_INCLUDED
#define SINTEGRA_H_INCLUDED
  void geraRegistro10(char cpnj[], char nomeEmpresa[]);
  void geraRegistro11(char nome[]);
  void geraRegistro50(char emitente, char cnpj[], int auxInt[], float auxFloat[]);
  void geraRegistro54(char cnpj[], char codigo[], int auxInt[], float auxFloat[]);
  void geraRegistro74(char cnpj[], char codigo[], float qtdPro, float valorPro);
  void geraRegistro75(char codigo[], float icms);
#endif