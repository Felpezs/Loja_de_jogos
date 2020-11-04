#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "operacoes.h"
#include "cliente.h"
#include "produtos.h"

int main()
{
    /*===========================================================
                 Sistema de Estoque de Loja de Jogos
    Projeto desenvolvido pelos integrantes:
    -> Jonatas Goes da Silva
    -> Felipe Eduardo
    -> Victor Yukio Shirasuna
    =============================================================*/

    setlocale(LC_ALL, "Portuguese");

    int resp;
    int qntd_clientes = 0, qntd_produtos = 0, qntd_vendas = 0, tela_desejada = 0;
    int ctrl_vendasBuffer = 0;

    Cliente *clientes;
    Produto *produtos;
    Venda *vendas;

    /*ESCOLHA DAS OPÇÕES
    OPÇÃO 1: Tela de cadastro dos produtos ou clientes dependendo da escolha
    OPÇÃO 2: Tela de consulta de dados de produtos, de clientes ou de vendas dependendo da escolha
    OPÇÃO 3: Tela de atualização de dados de produtos ou clientes dependendo da escolha
    OPÇÃO 4: Tela de compra de produtos
    OPÇÃO 5: Encerra o programa
    OBS.: Após o encerramento de uso em cada tela, o usuário voltará para a tela principal
    system("cls||clear") = Executa a limpeza de tela*/

    //Loop para permanência na tela inicial
    do
    {
        printf("\t\tSISTEMA DE ESTOQUE E COMPRA DE JOGOS\n\n");
        printf("Escolha uma opção para prosseguir:\n\n");
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
                    printf("Escolha uma opção para prosseguir:\n");
                    printf("- Clientes (1)\n- Produtos (2)\n- Retornar (3)\n\n>> ");
                    scanf("%d", &tela_desejada);

                    switch (tela_desejada)
                    {
                        case 1:
                            Cadastrar_Cliente(&clientes, &qntd_clientes);
                        break;

                        case 2:
                            Cadastrar_Produto(&produtos, &qntd_produtos);
                        break;
                    }

                } while(tela_desejada !=3);
            	break;

            case 2:
                do
                {
                    system("cls||clear");

                    //Submenu de Consulta
                    printf("\t\tCONSULTAR DADOS\n\n");
                    printf("Escolha uma opção para prosseguir:\n");
                    printf("- Clientes (1)\n- Produtos (2)\n- Vendas (3)\n- Retornar (4)\n\n>> ");
                    scanf("%d", &tela_desejada);

                    switch (tela_desejada)
                    {
                        case 1:
                            Consultar_Cliente(&clientes, &qntd_clientes);
                        break;

                        case 2:
                            Consultar_Produto(&produtos, &qntd_produtos);
                        break;

                        case 3:
                            Consultar_Vendas(&vendas, &qntd_vendas);
                        break;
                    }

                } while(tela_desejada !=4);
            	break;

            case 3:
                do
                {
                    system("cls||clear");

                    //Submenu de Atualização
                    printf("\t\tATUALIZAR DADOS\n\n");
                    printf("Escolha uma opção para prosseguir:\n");
                    printf("- Clientes (1)\n- Produtos (2)\n- Retornar (3)\n\n>> ");
                    scanf("%d", &tela_desejada);

                    switch (tela_desejada)
                    {
                        case 1:
                            Atualizar_Cliente(&clientes, &qntd_clientes);
                        break;

                        case 2:
                            Atualizar_Produto(&produtos, &qntd_produtos);
                        break;
                    }

                } while(tela_desejada !=3);
            	break;

            case 4:
                Comprar(&clientes, &produtos, &vendas, &qntd_clientes, &qntd_produtos, &qntd_vendas, &ctrl_vendasBuffer);
            	break;
        }
        system("cls||clear");
    }
    while(resp != 5);

    return 0;
}