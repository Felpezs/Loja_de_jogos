#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operacoes.h"

//Funcao para consultar dados de vendas da memoria
void Consultar_Vendas(Venda* vendas, int n_vendas)
{
    int i;

    system("cls||clear");
    printf("\tCONSULTAR DADOS CADASTRAIS DAS VENDAS\n\n");

    if(n_vendas == 0)   /* sem registros na memoria para exibir */
    {
        printf("Nenhum registro encontrado.\n");
    }
    else    /* exibir os dados armazenados na memoria de cada registro */
    {
        //valor total arrecadado das vendas
        float _totalVendas = 0;

        for(i = 0; i < n_vendas; ++i)
        {
            printf("\nRegistro Venda <%d>\n",   i+1);
            printf("\tID Cliente:     %d\n",    (vendas+i)->id_comprador);
            printf("\tCategoria Jogo: %s\n",    (vendas+i)->categoria);
            printf("\tNome Jogo:      %s\n",    (vendas+i)->nome);
            printf("\tQuantidade:     %d\n",    (vendas+i)->quantidade);
            printf("\tLucro:        R$%.2f\n",  (vendas+i)->lucro);

            //soma os valores da venda de cada registro
            _totalVendas += (vendas+i)->lucro;
        }

        printf("\nTotal arrecadado: R$%.2f\n", _totalVendas);
    }
    Loop_Tela();
}

//Funcao para gravar os dados das vendas no disco por escrita binaria e depois fechar o arq
void Gravar_Venda(Venda *vendas, int n_vendas, int ctrl_vendasBuffer)
{
    FILE *arq;
    //abrir o arquivo de vendas para gravacao binaria
    arq = fopen("vendas.dat", "wb");
    if (arq != NULL)
    {
        fwrite(&n_vendas, sizeof(int), 1, arq);             /* grava o numero total de registros da memoria */
        fwrite(&ctrl_vendasBuffer, sizeof(int), 1, arq);    /* grava a quantidade do controle do buffer */
        fwrite(vendas, sizeof(Venda), n_vendas, arq);       /* grava os dados das vendas da memoria para o disco */
        fclose(arq);
    }
}

//Funcao de pedidos de compra, valida o usuario e produtos cadastrados (tudo em memoria)
void Comprar(Cliente* clientes, Produto* produtos, Venda** vendas, int n_clientes, int n_produtos, int* n_vendas, int* ctrl_vendasBuffer)
{
    /*===============================================================================*/
    /*                      ADQUIRIR PRODUTOS VALIDANDO:                             */
    /*   ID DO CLIENTE, NOME DA CATEGORIA DO PRODUTO, NOME DO PRODUTO E QUANTIDADE   */
    /*===============================================================================*/

    int _userID, _prodQntd, i;
    char _prodCat[100] = "", _prodNome[100];
    
    //submenu
    system("cls||clear");
    printf("\tCOMPRAR PRODUTO\n\n");
    printf("Codigo do cliente:\n\n>> ");
    scanf("%d", &_userID);

    //verifica se o codigo fornecido (ID) do CLIENTE esta cadastrado
    for(i = 0; i < n_clientes; ++i)
    {
        if((clientes+i)->id == _userID)
        {
            /* Usuario esta cadastrado! Pedir:
             * - CATEGORIA DO PRODUTO   (char[])
             * - NOME DO PRODUTO        (char[])
             * - QUANTIDADE DO PRODUTO  (int)
             */

            /* CATEGORIA DO PRODUTO (char[]) */
            printf("Categoria do jogo:\n>> ");
            fflush(stdin);
            fgets(_prodCat, CHAR_M, stdin);
            _prodCat[strcspn(_prodCat, "\n")] = 0;
~
            /* NOME DO PRODUTO (char[]) */
            printf("Nome do jogo:\n>> ");
            fflush(stdin);
            fgets(_prodNome, CHAR_M, stdin);
            _prodNome[strcspn(_prodNome, "\n")] = 0;

            /* QUANTIDADE DO PRODUTO (int) */
            printf("Quantidade desejada:\n>> ");
            scanf("%d", &_prodQntd);

            break;
        }
    }

    /* Nao verificar o produto(loop abaixo) caso o usuario nao esteja cadastrado
     * Obs: a variavel _prodCat fara esse controle, portanto:
     * Para _prodCat == '': o usuario nao esta cadastrado
     * Para _prodCat != '': o usuario esta cadastrado e solicitou um produto
     */
    if(strcmp(_prodCat, "") == 0)
    {
        //Caso o usuario nao esteja cadastrado e Solicitado o cadastro no sistema ao usuario
        printf("Usuario nao esta cadastrado!\nFaca seu cadastro no menu principal.\n");
    }
    else
    {
    	/* Verifica-se o codigo fornecido (ID) do PRODUTO esta cadastrado */
	    i = 0;
	    //O Loop enquanto o codigo procurado nao for igual ao codigo pedido ou nao ser encontrado
	    do
	    {
	        if(strcmp((produtos+i)->categoria, _prodCat) == 0)
	        {  
	            if(strcmp((produtos+i)->nome, _prodNome) == 0)
	            {
	                if((produtos+i)->quantidade >= _prodQntd)
	                {
	                    /* O produto esta disponivel! */
	                    printf("Produto disponivel. A quantidade desejada foi retirada do estoque\n");
	                    (produtos+i)->quantidade -= _prodQntd;  /* remover a quantidade solicitada do estoque (em memoria) */
	
                        /*---------------------------------*/
	                    /* Tratamento com struct de vendas */
                        /*---------------------------------*/
	
	                    //contabilizar mais uma venda
	                    *n_vendas += 1;
	
	                    //realocar espaco quando a quantidade de vendas estourar o valor do buffer
                        if(*n_vendas > (CTRL_BUFFER * (*ctrl_vendasBuffer)))
	                    {
	                        //incrementa mais uma quantidade de vezes do buffer de vendas
	                        *ctrl_vendasBuffer += 1;
	                        //faz a realocacao dinamica de mais posições
	                        *vendas = (Venda*) realloc(*vendas, (CTRL_BUFFER * (*ctrl_vendasBuffer)) * sizeof(Venda));
	                    }
	
	                    /* Registrar os dados na estrutura de vendas (MEMORIA)
                         * - ID DO COMPRADOR        (int)
                         * - CATEGORIA DO PRODUTO   (char[])
                         * - NOME DO PRODUTO        (char[])
                         * - QUANTIDADE DO PRODUTO  (int)
                         * - LUCRO/RENDA OBTIDA     (float)
                         */

	                    (*vendas + (*n_vendas - 1))->id_comprador = _userID;
	                    strcpy((*vendas + (*n_vendas - 1))->categoria, (produtos+i)->categoria);
	                    strcpy((*vendas + (*n_vendas - 1))->nome, (produtos+i)->nome);
	                    (*vendas + (*n_vendas - 1))->quantidade = _prodQntd;
	                    (*vendas + (*n_vendas - 1))->lucro = ((produtos+i)->preco * _prodQntd);
	
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
	            //caso nao seja encontrado o nome ate o final de n_produtos
	            else if (i >= n_produtos - 1)
	            {
	                printf("NOME DO JOGO NAO ENCONTRADO.\n");
	                break;
	            }
	        }
	        //caso nao seja encontrado a categoria ate o final de n_produtos
	        else if (i >= n_produtos - 1)
	        {
	            printf("CATEGORIA NAO ENCONTRADA.\n");
	            break;
	        }
	
	        i++;
	    }
	    while((i < n_produtos) || (strcmp((produtos+i)->categoria, _prodCat) != 0));
	}
    Loop_Tela();
}


void Loop_Tela()
{
    //Funcao nao sai do loop enquanto o usuario nao digitar a tecla enter
    printf("\nPressione [Enter] para continuar.");
    while(getchar()!='\n');
    getchar();
}