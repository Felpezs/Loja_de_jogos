/*
 * Cliente Header - todas as opera??es que tratam com clientes
 */

#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED
#include "structs.h"

void Cadastrar_Cliente(Cliente*, int*);
void Gravar_Cliente(Cliente *, int, int);
void Atualizar_Cliente(Cliente*, int*);
void Consultar_Cliente(Cliente*, int);

#endif // CLIENTE_H_INCLUDED

