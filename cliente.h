/*
 * Cliente Header - todas as operações que tratam com clientes
 */

#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED
#include "structs.h"

void Cadastrar_Cliente(Cliente**, int*);
void Atualizar_Cliente(Cliente**, int*);
void Consultar_Cliente(Cliente**, int*);

#endif // CLIENTE_H_INCLUDED