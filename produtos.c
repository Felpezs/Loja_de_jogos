#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operacoes.h"
#include "produtos.h"

void Cadastrar_Produto(Produto** produtos, int *n_produtos)
{
    system("cls||clear");

    printf("\t\tCADASTRO DE PRODUTOS\t\n\n");

    //Verificar se eh a primeira execucao do programa para fazer malloc ou realloc
    if(*n_produtos == 0)
    {
        printf("Digite a quantidade de produtos a ser cadastrada:\n\n>> ");
        scanf("%d", &*n_produtos);

        if(*n_produtos <= 0)
            printf("\nHouve um erro no registro!\n");

        //Cadastramento de produtos
        else
        {
            //Alocacao dinamica com malloc
            *produtos = (Produto*) malloc(*n_produtos * sizeof(Produto));

            for(int i = 0; i < *n_produtos; ++i)
            {
                printf("Preencha os dados do Produto (%d):\nID: ", i+1);
                scanf("%d", &(*produtos+i)->id);

                printf("Nome: ");
                fflush(stdin);
                fgets((*produtos+i)->nome, CHAR_MAX, stdin);
                (*produtos+i)->nome[strcspn((*produtos+i)->nome, "\n")] = 0;

                printf("Categoria: ");
                fflush(stdin);
                fgets((*produtos+i)->categoria, CHAR_MAX, stdin);
                (*produtos+i)->categoria[strcspn((*produtos+i)->categoria, "\n")] = 0;

                printf("Quantidade: ");
                scanf("%d", &(*produtos+i)->quantidade);

                printf("Preco: ");
                scanf("%f", &(*produtos+i)->preco);
            }
        printf("Registrado com sucesso!\n");
        }
    }

    else
    {
        int _qnt;
        printf("Digite a quantidade de produtos a ser cadastrada: ");
        scanf("%d", &_qnt);

        if(_qnt <= 0)
            printf("\nHouve um erro no registro!\n");

        //Cadastramento de produtos
        else
        {
            *n_produtos += _qnt;

            //Realocacao dinamica com realloc
            *produtos = (Produto*) realloc(*produtos, *n_produtos * sizeof(Produto));

            for(int i = (*n_produtos - _qnt); i < *n_produtos; ++i)
            {
            printf("Preencha os dados do Produto (%d):\nID: ", i+1);
            scanf("%d", &(*produtos+i)->id);

            printf("Nome: ");
            fflush(stdin);
            fgets((*produtos+i)->nome, CHAR_MAX, stdin);
            (*produtos+i)->nome[strcspn((*produtos+i)->nome, "\n")] = 0;


            printf("Categoria: ");
            fflush(stdin);
            fgets((*produtos+i)->categoria, CHAR_MAX, stdin);
            (*produtos+i)->categoria[strcspn((*produtos+i)->categoria, "\n")] = 0;


            printf("Quantidade: ");
            scanf("%d", &(*produtos+i)->quantidade);

            printf("Preco: ");
            scanf("%f", &(*produtos+i)->preco);
            }
        printf("Registrado com sucesso!\n");
        }
    }
    Loop_Tela();

    system("cls||clear");
}

void Atualizar_Produto(Produto** produtos, int *n_produtos)
{
    /*===========================================================*/
    /*              ATUALIZAR DADOS DE PRODUTOS                  */
    /*===========================================================*/

    int _atualizaroque = 0, _buscaID, i = 0, j = 0, resp;

        do
        {
            system("cls||clear");

            printf("\t\tATUALIZAR PRODUTOS\t\n");

            if(*n_produtos == 0)
            {
                printf("\nNão há produtos cadastrados!\n");
                _atualizaroque = 6;
            }

            else
            {
                printf("-Atualizar Nome(1)\n -Categoria(2)\n -Quantidade(3)\n -Preço(4)\n -Excluir Produto(5)\n -Retornar(6)\n\n>> ");
                scanf("%d", &_atualizaroque);

                if(_atualizaroque >= 1 && _atualizaroque < 6)
                {
                    printf("\nDigite o ID do produto: ");
                    scanf("%d", &_buscaID);

                    //For para buscar o indice do produto no vetor
                    for(i = 0; i < *n_produtos; ++i)
                    {
                        if((*produtos+i)->id == _buscaID)
                            break;
                    }

                    //Se o i chegou no final do vetor, a mercadoria não existe
                    if((i + 1) > *n_produtos)
                    {
                        printf("Mercadoria não está cadastrada!\nFaça seu cadastro no menu principal.\n");
                        break;
                    }

                    switch (_atualizaroque)
                    {
                        case 1:
                            printf("Digite o novo nome do produto (%d):\n>> ", i+1);
                            fflush(stdin);
                            fgets((*produtos+i)->nome, CHAR_MAX, stdin);
                            (*produtos+i)->nome[strcspn((*produtos+i)->nome, "\n")] = 0;
                            printf("Atualização feita com sucesso!\n");

                            Loop_Tela();
                        break;

                        case 2:
                            printf("Digite a nova categoria do produto (%d):\n>> ", i+1);
                            fflush(stdin);
                            fgets((*produtos+i)->categoria, CHAR_MAX, stdin);
                            (*produtos+i)->categoria[strcspn((*produtos+i)->categoria, "\n")] = 0;
                            printf("Atualização feita com sucesso!\n");

                            Loop_Tela();
                        break;

                        case 3:
                            printf("Digite a nova quantidade do produto (%d):\n>> ", i+1);
                            scanf("%d", &(*produtos+i)->quantidade);
                            printf("Atualização feita com sucesso!\n");

                            Loop_Tela();
                        break;

                        case 4:
                            printf("Digite o novo preço do produto (%d):\n>> ", i+1);
                            scanf("%f", &(*produtos+i)->preco);
                            printf("Atualização feita com sucesso!\n");

                            Loop_Tela();
                        break;

                        case 5:
                                printf("Você realmente deseja excluir o produto (%d) ?\n", i+1);
                                printf(" -Sim(1)\n -Não(2)\n\n>> ");
                                scanf("%d", &resp);

                                if(resp == 1)
                                {
                                    //Utilizando o último valor de i usado no laço de busca (produto encontrado)
                                    for(i=i; i < *n_produtos - 1; i++)
                                    {
                                        //Copiando os dados da posição posterior para o espaço deletado
                                        j = i + 1;

                                        (*produtos+i)->id = (*produtos+j)->id;
                                        strcpy(((*produtos+i)->nome), ((*produtos+j)->nome));
                                        strcpy(((*produtos+i)->categoria), ((*produtos+j)->categoria));
                                        (*produtos+i)->quantidade = (*produtos+j)->quantidade;
                                        (*produtos+i)->preco = (*produtos+j)->preco;
                                    }

                                    *n_produtos -= 1;

                                    //Fazendo a realocação dinâmica para liberar os espaços vazios
                                    *produtos = (Produto*) realloc(*produtos, *n_produtos * sizeof(Produto));

                                    printf("Exclusão feita com sucesso!");
                                    Loop_Tela();
                                }
                        break;
                    }
                }
            }

        }while(_atualizaroque != 6);

    Loop_Tela();
}

void Consultar_Produto(Produto** produtos, int* n_produtos)
{
    system("cls||clear");

    printf("\t\tCONSULTAR DADOS DE PRODUTOS\n\n");

    // Exibir que não existem registros
    if(*n_produtos == 0)
    {
        printf("Nenhum registro encontrado.\n");
    }
    // Senão exibir os registros do sistema
    else
    {
        for(int i = 0; i < *n_produtos; ++i)
        {
            printf("\nRegistro Produto nº(%d)\n", i+1);

            printf("\tID:         %d\n", (*produtos+i)->id);
            printf("\tNome:       %s\n", (*produtos+i)->nome);
            printf("\tCategoria:  %s\n", (*produtos+i)->categoria);
            printf("\tQuantidade: %d\n", (*produtos+i)->quantidade);
            printf("\tPreco:    R$%.2f\n", (*produtos+i)->preco);
        }
    }

    Loop_Tela();
}