#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operacoes.h"

void Consultar_Vendas(Venda** vendas, int* n_vendas)
{
    /*===========================================================*/
    /*              CONSULTAR DADOS DE VENDAS                    */
    /*===========================================================*/

    system("cls||clear");

    // Submenu para ver clientes ou produtos
    printf("\tCONSULTAR DADOS CADASTRAIS DAS VENDAS\n\n");

    // Exibir que não existem registros
    if(*n_vendas == 0)
    {
        printf("Nenhum registro encontrado.\n");
    }
    // Senão exibir os registros do sistema
    else
    {
        // Valor total arrecadado das vendas
        float _totalVendas = 0;

        for(int i = 0; i < *n_vendas; ++i)
        {
            printf("\nRegistro Venda nº(%d)\n", i+1);
            printf("\tID Cliente:     %d\n", (*vendas+i)->id_comprador);
            printf("\tCategoria Jogo: %s\n", (*vendas+i)->categoria);
            printf("\tNome Jogo:      %s\n", (*vendas+i)->nome);
            printf("\tQuantidade:     %d\n", (*vendas+i)->quantidade);
            printf("\tLucro:        R$%.2f\n", (*vendas+i)->lucro);

            // Soma os valores de venda de cada registro
            _totalVendas += (*vendas+i)->lucro;
        }

        printf("\nTotal arrecadado: R$%.2f\n", _totalVendas);
    }
    Loop_Tela();
}

void Comprar(Cliente** clientes, Produto** produtos, Venda** vendas, int* n_clientes, int* n_produtos, int* n_vendas, int* ctrl_vendasBuffer)
{
    /*===============================================================================*/
    /*                      ADQUIRIR PRODUTOS VALIDANDO:                             */
    /*   ID DO CLIENTE, NOME DA CATEGORIA DO PRODUTO, NOME DO PRODUTO E QUANTIDADE   */
    /*===============================================================================*/

    int _userID, _prodQntd;
    char _prodCat[100] = "", _prodNome[100];
    system("cls||clear");

    // Submenu para comprar um produto
    printf("\tCOMPRAR PRODUTO\n\n");
    printf("C?digo do cliente:\n\n>> ");
    scanf("%d", &_userID);

    // Verifica-se o Codigo fornecido (ID) do CLIENTE está cadastrado
    for(int i = 0; i < *n_clientes; ++i)
    {
        if((*clientes+i)->id == _userID)
        {
            // Usuario está cadastrado!
            // Pede o ID do produto e a quantidade
            printf("Categoria do jogo:\n>> ");
            fflush(stdin);
            fgets(_prodCat, CHAR_MAX, stdin);
            _prodCat[strcspn(_prodCat, "\n")] = 0;

            printf("Nome do jogo:\n>> ");
            fflush(stdin);
            fgets(_prodNome, CHAR_MAX, stdin);
            _prodNome[strcspn(_prodNome, "\n")] = 0;

            printf("Quantidade desejada:\n>> ");
            scanf("%d", &_prodQntd);

            break;
        }
    }

    /* Não verificar o produto(loop abaixo) caso o usuário não esteja cadastrado
     * Obs: a variável _prodCat fará esse controle, portanto:
     * Para _prodCat == '': o usuário não está cadastrado
     * Para _prodCat != '': o usuário está cadastrado e solicitou um produto
     */
    if(strcmp(_prodCat, "") == 0)
    {
        
        //Caso o usuario não esteja cadastrado e Solicitado o cadastro no sistema ao usuario
        printf("Usuário não está cadastrado!\nFaça seu cadastro no menu principal.\n");

        Loop_Tela();
        // FIM
        return;
    }

    /* Verifica-se o código fornecido (ID) do PRODUTO está cadastrado */
    int i = 0;
    //O Loop enquanto o codigo procurado não for igual ao codigo pedido ou nao ser encontrado
    do
    {
        if(strcmp((*produtos+i)->categoria, _prodCat) == 0)
        {  
            if(strcmp((*produtos+i)->nome, _prodNome) == 0)
            {
                if((*produtos+i)->quantidade >= _prodQntd)
                {
                    /* O produto está disponivel! */
                    printf("Produto disponivel. A quantidade desejada foi retirada do estoque\n");
                    (*produtos+i)->quantidade -= _prodQntd;

                    /* Tratamento com struct de vendas */

                    // Contabilizar mais uma venda
                    *n_vendas += 1;

                    // Realiza o malloc caso a quantidade de vendas for a primeira
                    if(*n_vendas == 1)
                    {
                        // Faz a alocação dinâmica inicial com o tamanho do buffer (5)
                        *vendas = (Venda*) malloc(VENDAS_BUFFER * sizeof(Venda));
                        *ctrl_vendasBuffer += 1;
                    }
                    // Ou realloc quando a quantidade de vendas estourar o valor do buffer
                    else if(*n_vendas > (VENDAS_BUFFER * (*ctrl_vendasBuffer)))
                    {
                        // Incrementa mais uma quantidade de vezes do buffer de vendas
                        *ctrl_vendasBuffer += 1;

                        // Faz a realocação dinâmica
                        *vendas = (Venda*) realloc(*vendas, (VENDAS_BUFFER * (*ctrl_vendasBuffer)) * sizeof(Venda));
                    }

                    // Registra os dados na estrutura vendas
                    (*vendas + (*n_vendas - 1))->id_comprador = _userID;
                    strcpy((*vendas + (*n_vendas - 1))->categoria, (*produtos+i)->categoria);
                    strcpy((*vendas + (*n_vendas - 1))->nome, (*produtos+i)->nome);
                    (*vendas + (*n_vendas - 1))->quantidade = _prodQntd;
                    (*vendas + (*n_vendas - 1))->lucro = ((*produtos+i)->preco * _prodQntd);

                    printf("\nRESUMO DA COMPRA:\n");
                    printf("ID COMPRADOR:      %d\n", (*vendas + (*n_vendas - 1))->id_comprador);
                    printf("CATEGORIA PRODUTO: %s\n", (*vendas + (*n_vendas - 1))->categoria);
                    printf("NOME PRODUTO:      %s\n", (*vendas + (*n_vendas - 1))->nome);
                    printf("QUANTIDADE:        %d\n", (*vendas + (*n_vendas - 1))->quantidade);
                    printf("LUCRO:           R$%.2f\n", (*vendas + (*n_vendas - 1))->lucro);

                    break;
                }
                else
                {
                    printf("ESTOQUE INSUFICIENTE.\n");
                    break;
                }
            }
            // Caso não seja encontrado o nome até o final de n_produtos
            else if (i >= *n_produtos - 1)
            {
                printf("NOME DO JOGO NÃO ENCONTRADO.\n");
                break;
            }
        }
        //  Caso não seja encontrado a categoria até o final de n_produtos
        else if (i >= *n_produtos - 1)
        {
            printf("CATEGORIA NÃO ENCONTRADA.\n");
            break;
        }

        i++;
    }
    while((i < (*n_produtos)) || (strcmp((*produtos+i)->categoria, _prodCat) != 0));

    Loop_Tela();
}

void Loop_Tela()
{
    //Função  não sai do loop enquanto o usuario não digitar a tecla enter
    printf("\nPressione [Enter] para continuar.\n");
    while(getchar()!='\n');
    getchar();
}