#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operacoes.h"
#include "produtos.h"
#include <locale.h>


//No fim da funcao, abrir arquivo, upar dados, fechar arquivo
void Cadastrar_Produto(Produto* produtos, int *n_produtos)
{
	int i = *n_produtos;
    system("cls||clear");

    printf("\t\tCADASTRO DE PRODUTOS\t\n\n");

    /* Coleta dos dados do produto
     * - ID         (int)
     * - NOME       (char[])
     * - CATEGORIA  (char[])
     * - QUANTIDADE (int)
     * - PRECO      (float)
     */

    /* ID (int) */
    printf("Preencha os dados do Produto (%d):\nID: ", *n_produtos + 1);
    scanf("%d", &(produtos + i)->id);

    /* NOME (char[]) */
    printf("Nome: ");
    fflush(stdin);
    fgets((produtos + i)->nome, CHAR_M, stdin);
    (produtos + i)->nome[strcspn((produtos + i)->nome, "\n")] = 0;

    /* CATEGORIA (char[]) */
    printf("Categoria: ");
    fflush(stdin);
    fgets((produtos + i)->categoria, CHAR_M, stdin);
    (produtos + i)->categoria[strcspn((produtos + i)->categoria, "\n")] = 0;

    /* QUANTIDADE (int) */
    printf("Quantidade: ");
    scanf("%d", &(produtos + i)->quantidade);

    /* PRECO (float) */
    printf("Preco: ");
    scanf("%f", &(produtos + i)->preco);

    *n_produtos += 1;
}

//Funcao para gravar os dados dos produtos no disco por escrita binaria e depois fechar o arq
void Gravar_Produto(Produto *produtos, int n_produtos, int ctrl_produtosBuffer)
{
    FILE* arq;
    arq = fopen("produtos.dat", "wb");
    if (arq != NULL)
    {
        fwrite(&n_produtos, sizeof(int), 1, arq);
        fwrite(&ctrl_produtosBuffer, sizeof(int), 1, arq);
        fwrite(produtos, sizeof(Produto), n_produtos, arq);
        fclose(arq);
    }
}

//No fim do programa, abre arquivo, envia dados, fecha arquivo
void Atualizar_Produto(Produto* produtos, int *n_produtos)
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
                printf("\nNao ha produtos cadastrados!\n");
                _atualizaroque = 6;
            }

            else
            {
                printf("\n-Atualizar Nome(1)\n -Categoria(2)\n -Quantidade(3)\n -Preco(4)\n -Excluir Produto(5)\n -Retornar(6)\n\n>> ");
                scanf("%d", &_atualizaroque);

                if(_atualizaroque >= 1 && _atualizaroque < 6)
                {
                    printf("\nDigite o ID do produto: ");
                    scanf("%d", &_buscaID);

                    //For para buscar o indice do produto no vetor
                    for(i = 0; i < *n_produtos; ++i)
                    {
                        if((produtos+i)->id == _buscaID)
                            break;
                    }

                    //Se o i chegou no final do vetor, a mercadoria n?o existe
                    if((i + 1) > *n_produtos)
                    {
                        printf("Mercadoria nao esta cadastrada!\nFaca seu cadastro no menu principal.\n");
                        break;
                    }

                    switch (_atualizaroque)
                    {
                        case 1:
                            printf("Digite o novo nome do produto (%d):\n>> ", i+1);
                            fflush(stdin);
                            fgets((produtos+i)->nome, CHAR_M, stdin);
                            (produtos+i)->nome[strcspn((produtos+i)->nome, "\n")] = 0;
                            printf("Atualiza??o feita com sucesso!\n");

                            Loop_Tela();
                        break;

                        case 2:
                            printf("Digite a nova categoria do produto (%d):\n>> ", i+1);
                            fflush(stdin);
                            fgets((produtos+i)->categoria, CHAR_M, stdin);
                            (produtos+i)->categoria[strcspn((produtos+i)->categoria, "\n")] = 0;
                            printf("Atualiza??o feita com sucesso!\n");

                            Loop_Tela();
                        break;

                        case 3:
                            printf("Digite a nova quantidade do produto (%d):\n>> ", i+1);
                            scanf("%d", &(produtos+i)->quantidade);
                            printf("Atualiza??o feita com sucesso!\n");

                            Loop_Tela();
                        break;

                        case 4:
                            printf("Digite o novo pre?o do produto (%d):\n>> ", i+1);
                            scanf("%f", &(produtos+i)->preco);
                            printf("Atualiza??o feita com sucesso!\n");

                            Loop_Tela();
                        break;

                        case 5:
                                printf("Voce realmente deseja excluir o produto (%d) ?\n", i+1);
                                printf(" -Sim(1)\n -Nao(2)\n\n>> ");
                                scanf("%d", &resp);

                                if(resp == 1)
                                {
                                    //Utilizando o ultimo valor de i usado no laco de busca (produto encontrado)
                                    for(i=i; i < *n_produtos - 1; i++)
                                    {
                                        //Copiando os dados da posicao posterior para o espaco deletado
                                        j = i + 1;

                                        (produtos+i)->id = (produtos+j)->id;
                                        strcpy(((produtos+i)->nome), ((produtos+j)->nome));
                                        strcpy(((produtos+i)->categoria), ((produtos+j)->categoria));
                                        (produtos+i)->quantidade = (produtos+j)->quantidade;
                                        (produtos+i)->preco = (produtos+j)->preco;
                                    }

                                    *n_produtos -= 1;

                                    printf("Exclusao feita com sucesso!");
                                    Loop_Tela();
                                }
                        break;
                    }
                }
            }

        }while(_atualizaroque != 6);

    Loop_Tela();
}

void Consultar_Produto(Produto* produtos, int n_produtos)
{ 
	int i;
	
    system("cls||clear");

    printf("\t\tCONSULTAR DADOS DE PRODUTOS\n\n");

    // Exibir que nao existem registros
    if(n_produtos == 0)
    {
        printf("Nenhum registro encontrado.\n");
    }
    // Sen?o exibir os registros do sistema
    else
    {
        for(i = 0; i < n_produtos; ++i)
        {
            printf("\nRegistro Produto <%d>\n", i+1);

            printf("\tID:         %d\n", (produtos+i)->id);
            printf("\tNome:       %s\n", (produtos+i)->nome);
            printf("\tCategoria:  %s\n", (produtos+i)->categoria);
            printf("\tQuantidade: %d\n", (produtos+i)->quantidade);
            printf("\tPreco:    R$%.2f\n", (produtos+i)->preco);
        }
    }

    Loop_Tela();
}