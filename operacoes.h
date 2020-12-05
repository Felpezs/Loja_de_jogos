/*
 * Operacoes Header - operacoes que tratam de compras/vendas e espera do usuario
 */

#ifndef OPERACOES_H_INCLUDED
#define OPERACOES_H_INCLUDED
#include "structs.h"

void Consultar_Vendas(Venda*, int);
void Gravar_Venda(FILE*, Venda*, int, int);
void Comprar(Cliente*, Produto*, Venda**, int, int, int*, int*);
void Loop_Tela();

#endif // OPERACOES_H_INCLUDED