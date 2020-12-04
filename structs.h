#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

#define CHAR_M 100
#define CTRL_BUFFER 3

typedef struct Cliente
{
    int id;
    int cpf;
    char nome[CHAR_M];
    char endereco[CHAR_M];
    char email[CHAR_M];
} Cliente;

typedef struct Produto
{
    int id;
    char nome[CHAR_M];
    char categoria[CHAR_M];
    int quantidade;
    float preco;
} Produto;

typedef struct Venda
{
    int id_comprador;
    char categoria[CHAR_M];
    char nome[CHAR_M];
    int quantidade;
    float lucro;
} Venda;

#endif // STRUCTS_H_INCLUDED
