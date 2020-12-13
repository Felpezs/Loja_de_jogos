/*
 * Produtos Header - todas as opera??es que tratam com produtos
 */

#ifndef PRODUTOS_H_INCLUDED
#define PRODUTOS_H_INCLUDED
#include "structs.h"

void Cadastrar_Produto(Produto*, int*);
void Gravar_Produto(Produto*, int, int);
void Atualizar_Produto(Produto*, int*);
void Consultar_Produto(Produto*, int);

#endif // PRODUTOS_H_INCLUDED,