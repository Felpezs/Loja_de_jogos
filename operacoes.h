/*
 * Operações Header - todas as operações restantes que tratam do sistema
 */

#ifndef OPERACOES_H_INCLUDED
#define OPERACOES_H_INCLUDED
#include "structs.h"

void Consultar_Vendas(Venda**, int*);
void Comprar(Cliente**, Produto**, Venda**, int*, int*, int*, int*);
void Loop_Tela();

#endif // OPERACOES_H_INCLUDED