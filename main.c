#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "operacoes.h"
#include "cliente.h"
#include "produtos.h"
#include "structs.h"

int main()
{
    //TRAZER TODOS OS DADOS PARA A MEMÓRIA

    /*===========================================================
                 Sistema de Estoque de Loja de Jogos
    Projeto desenvolvido pelos integrantes:
    -> Jonatas Goes da Silva
    -> Felipe Eduardo
    -> Victor Yukio Shirasuna
    =============================================================*/

//Escala de Frequencia de uso: 1 a 3
    setlocale(LC_ALL, "Portuguese");

    int resp;
    int qntd_clientes = 0, qntd_produtos = 0, qntd_vendas = 0, tela_desejada = 0;
    int ctrl_vendasBuffer = 1, ctrl_clienteBuffer = 1, ctrl_produtosBuffer = 1;
    int i;
    
    FILE *arq_produtos;     //produtos.dat
    FILE *arq_clientes;     //clientes.dat
    FILE *arq_vendas;       //vendas.dat

    Cliente *clientes;
    Produto *produtos;
    Venda *vendas;
    
    //Trazendo dados do arquivo para a memoria
    
        arq_clientes = fopen("clientes.dat", "rb");
        arq_produtos = fopen("produtos.dat", "rb");
        arq_vendas = fopen("vendas.dat", "rb");

        //Se os arquivos nao existirem, e feita a alocacao dinamica de 3 unidades

        /*Primeira linha: quantidade de dados
          Demais linhas: dados gerais        */

        if(arq_clientes != NULL)
        {
            fread(&qntd_clientes, sizeof(int), 1, arq_clientes);
            fread(&ctrl_clienteBuffer, sizeof(int), 1, arq_clientes);
            clientes = (Cliente*) malloc((qntd_clientes + 3) * sizeof(Cliente));
            fread(clientes, sizeof(Cliente), qntd_clientes, arq_clientes);
        }

        else
        	clientes = (Cliente*) malloc(CTRL_BUFFER * sizeof(Cliente));
		
		fclose(arq_clientes);

        if(arq_produtos != NULL)
        {
            fread(&qntd_produtos, sizeof(int), 1, arq_produtos);
            fread(&ctrl_produtosBuffer, sizeof(int),1, arq_produtos);
            produtos = (Produto*) malloc((qntd_produtos + 3) * sizeof(Produto));
            fread(produtos, sizeof(Produto), qntd_produtos, arq_produtos);
        }

        else
        	produtos = (Produto*) malloc(CTRL_BUFFER * sizeof(Produto));
        
        fclose(arq_produtos);

        if(arq_vendas != NULL)
        {
            fread(&qntd_vendas, sizeof(int), 1, arq_vendas);                            /* ler o numero total de registros */
            fread(&ctrl_vendasBuffer, sizeof(int), 1, arq_vendas);                      /* ler a quantidade de vezes que o buffer ocupa */
            vendas = (Venda*) malloc(ctrl_vendasBuffer * CTRL_BUFFER * sizeof(Venda));  /* alocar espaco na memoria para receber os dados do disco */
            fread(vendas, sizeof(Venda), qntd_vendas, arq_vendas);                      /* transferir os dados do disco para a memoria dinamica */
        }

        else
        	vendas = (Venda*) malloc(CTRL_BUFFER * sizeof(Venda));                      /* senao, aloca espaco inicial na memoria do buffer */
            
		fclose(arq_vendas);
		
    /*ESCOLHA DAS OPCOES
    OPCAO 1: Tela de cadastro dos produtos ou clientes dependendo da escolha
    OPCAO 2: Tela de consulta de dados de produtos, de clientes ou de vendas dependendo da escolha
    OPCAO 3: Tela de atualizacao de dados de produtos ou clientes dependendo da escolha
    OPCAO 4: Tela de compra de produtos
    OPCAO 5: Encerra o programa
    OBS.: Apos o encerramento de uso em cada tela, o usuario voltara para a tela principal
    system("cls||clear") = Executa a limpeza de tela*/

    //Loop para permanencia na tela inicial
    do
    {
        printf("\t\tSISTEMA DE ESTOQUE E COMPRA DE JOGOS\n\n");
        printf("Escolha uma opcao para prosseguir:\n\n");
        printf("- Cadastrar(1)\n- Consultar(2)\n- Atualizar(3)\n- Comprar(4)\n- Sair(5)\n\n>> ");
        scanf("%d", &resp);
		
        switch (resp)
        {
            case 1:
                do
                {
                    system("cls||clear");

                    //Submenu de Cadastro
                    printf("\t\tCADASTRO\n\n");
                    printf("Escolha uma opcao para prosseguir:\n");
                    printf("- Clientes (1)\n- Produtos (2)\n- Retornar (3)\n\n>> ");
                    scanf("%d", &tela_desejada);

                    char _userResp;
                    switch (tela_desejada)
                    {
                        //Frequencia de uso: 2
                        case 1:                       	
                            do
                            {
                                //Se estourou o buffer, realoca a memoria e arquiva dados
                                if(qntd_clientes == (ctrl_clienteBuffer * CTRL_BUFFER))
                                {
                                    //Tentar dar apenas o append para poupar tempo de execucao
                                	arq_clientes = fopen("clientes.dat", "wb");
							
                                	//Escrita e fechamento do arquivo
                                	fwrite(&qntd_clientes, sizeof(int), 1, arq_clientes);
                                	fwrite(&ctrl_clienteBuffer, sizeof(int), 1, arq_clientes);
                                	fwrite(clientes, sizeof(Cliente), qntd_clientes, arq_clientes);
                                
                                	fclose(arq_clientes);
      
                                    ctrl_clienteBuffer += 1;
                                    clientes = (Cliente*) realloc(clientes, (ctrl_clienteBuffer * CTRL_BUFFER * sizeof(Cliente)));
                                    
                                    if(clientes == NULL)
                                    {
                                    	printf("\nERRO NA MEM�RIA");
                                    	return 55;
									}
                                }

                                Cadastrar_Cliente(clientes, &qntd_clientes);
								
                                printf("Deseja cadastrar mais clientes (S/N)?");
                                _userResp = getche();

                            }while(toupper(_userResp) == 'S');
						    
                            system("cls||clear");
                            
                            break;

                        case 2:
                            do
                            {
                            	//Se estourou o buffer, realoca a memoria e arquiva dados
                                if(qntd_produtos == (ctrl_produtosBuffer * CTRL_BUFFER))
                                {
                                    //Tentar dar apenas o append para poupar tempo de execucao
                                	arq_produtos = fopen("produtos.dat", "wb");
							
                                	//Escrita e fechamento do arquivo
                                	fwrite(&qntd_produtos, sizeof(int), 1, arq_produtos);
                                	fwrite(&ctrl_produtosBuffer, sizeof(int), 1, arq_produtos);
                                	fwrite(produtos, sizeof(Produto), qntd_produtos, arq_produtos);
                                
                                	fclose(arq_produtos);
      
                                    ctrl_produtosBuffer += 1;
                                    produtos = (Produto*) realloc(produtos, (ctrl_produtosBuffer * CTRL_BUFFER * sizeof(Produto)));
                                    
                                    if(produtos == NULL)
                                    {
                                    	printf("\nERRO NA MEM�RIA");
                                    	return 55;
									}
                                }

                                Cadastrar_Produto(produtos, &qntd_produtos);
								
                                printf("Deseja cadastrar mais produtos (S/N)?");
                                _userResp = getche();
                            	
                            }while(toupper(_userResp) == 'S');
                            
                            system("cls||clear");

                        break;
                    }

                }while(tela_desejada != 3);

            	break;

            case 2:
                do
                {
                    system("cls||clear");

                    //Submenu de Consulta
                    printf("\t\tCONSULTAR DADOS\n\n");
                    printf("Escolha uma opcao para prosseguir:\n");
                    printf("- Clientes (1)\n- Produtos (2)\n- Vendas (3)\n- Retornar (4)\n\n>> ");
                    scanf("%d", &tela_desejada);

                    switch (tela_desejada)
                    {
                        //Nos tres casos, fazer a leitura dos dados da memoria 
                        case 1:
                            Consultar_Cliente(clientes, qntd_clientes);
                        break;

                        case 2:
                            Consultar_Produto(produtos, qntd_produtos);
                        break;

                        case 3:
                            Consultar_Vendas(vendas, qntd_vendas);
                        break;
                    }

                } while(tela_desejada != 4);
            	break;

            case 3:
                do
                {
                    system("cls||clear");

                    //Submenu de Atualizacao
                    printf("\t\tATUALIZAR DADOS\n\n");
                    printf("Escolha uma opcao para prosseguir:\n");
                    printf("- Clientes (1)\n- Produtos (2)\n- Retornar (3)\n\n>> ");
                    scanf("%d", &tela_desejada);

                    switch (tela_desejada)
                    {
                        case 1:

                            //Frequencia de uso: 1
                            Atualizar_Cliente(clientes, &qntd_clientes);
                        break;

                        case 2:

                            // Frequencia de uso: 2
                            Atualizar_Produto(produtos, &qntd_produtos);
                        break;
                    }

                } while(tela_desejada !=3);
            	break;

            case 4:
                //Frequencia de uso: 3
                Comprar(clientes, produtos, &vendas, qntd_clientes, qntd_produtos, &qntd_vendas, &ctrl_vendasBuffer);

                //gravar da memoria para o disco a cada 3 registros de vendas
                if((qntd_vendas % 3) == 0)
                {
                    Gravar_Venda(arq_vendas, vendas, qntd_vendas, ctrl_vendasBuffer);
                    Gravar_Produto(arq_produtos, produtos, qntd_produtos, ctrl_produtosBuffer); /* gravar estoque atualizado */
                }
            	break;
        }
        system("cls||clear");
    }while(resp != 5);

    //gravar os ultimos registros remascentes de vendas
    if((qntd_vendas % 3) != 0)
    {
        Gravar_Venda(arq_vendas, vendas, qntd_vendas, ctrl_vendasBuffer);
        Gravar_Produto(arq_produtos, produtos, qntd_produtos, ctrl_produtosBuffer); /* gravar estoque atualizado */
    }
    
	free(clientes);
    free(produtos);
    free(vendas);
    
    return 0;
}