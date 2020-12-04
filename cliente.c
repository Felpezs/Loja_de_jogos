#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operacoes.h"
#include "cliente.h"

//A cada tres cadastros, abre arquivo, upa dados, fecha arquivo
void Cadastrar_Cliente(Cliente *clientes, int *n_clientes)
{
	
	int i = *n_clientes;
	
    system("cls||clear");

    printf("\t\tCADASTRO DE CLIENTES\t\n\n");
	
    /* Coleta dos dados do cliente
     * - ID         (int)
     * - CPF        (int)
     * - NOME       (char[])
     * - ENDERECO   (char[])
     * - EMAIL      (char[])
     */

    /* ID (int) */
    printf("Preencha os dados do Cliente (%d):\nID: ", *n_clientes);
    scanf("%d", &(clientes + i)->id);

    /* CPF (int) */
    printf("CPF: ");
    scanf("%d", &(clientes + i)->cpf);

    /*Entrada dos dados do tipo string e feita pelo fgets
    para evitar que as strings sejam distribuidas erroneamente por conta
    de espacos em branco, utilizou-se o strcspn, substituindo por "0"
    quando e encontrado o "\n"*/

    /* NOME (char[]) */
    printf("Nome: ");
    fflush(stdin);
    fgets((clientes + i)->nome, CHAR_M, stdin);
    (clientes + i)->nome[strcspn((clientes + i)->nome, "\n")] = 0;

    /* ENDERECO (char[]) */
    printf("Endereco: ");
    fflush(stdin);
    fgets((clientes + i)->endereco, CHAR_M, stdin);
    (clientes + i)->endereco[strcspn((clientes + i)->endereco, "\n")] = 0;
    
    /* EMAIL (char[]) */
    printf("Email: ");
    fflush(stdin);
    fgets((clientes + i)->email, CHAR_M, stdin);
    (clientes + i)->email[strcspn((clientes + i)->email, "\n")] = 0;
    
    *n_clientes += 1;
}

//No fim da funcao, abre arquivo, envia dados, fecha arquivo
void Atualizar_Cliente(Cliente* clientes, int *n_clientes)
{
    /*===========================================================*/
    /*              ATUALIZAR DADOS DE CLIENTES                  */
    /*===========================================================*/

    int _atualizaroque = 0, _buscaID, i = 0, j = 0, resp;

        do
        {
            system("cls||clear");

            printf("\t\tATUALIZAR CLIENTES\n");

            if(*n_clientes == 0)
            {
                printf("\nNao ha clientes cadastrados!\n");
                _atualizaroque = 6;
            }

            else
            {
                printf("-Atualizar Nome(1)\n -Atualizar CPF(2)\n -Atualizar Endereco(3)\n -Atualizar Email(4)\n -Excluir Cliente(5)\n -Retornar(6)\n\n>> ");
                scanf("%d", &_atualizaroque);

                //Quebra o loop e volta para o in?cio
                if(_atualizaroque >=1 && _atualizaroque < 6)
                {
                    printf("\nDigite o ID do Cliente: ");
                    scanf("%d", &_buscaID);

                    //For para buscar o indice do produto no vetor
                    for(i = 0 ; i < *n_clientes; ++i)
                    {
                        if((clientes+i)->id == _buscaID)
                            break;
                    }

                    //Se chegou no final do vetor e o indice de i for maior que o numero de clientes
                    if((i + 1) > *n_clientes)
                    {
                        printf("Usuario nao esta cadastrado!\nFaca seu cadastro no menu principal.\n");
                        break;
                    }

                    switch (_atualizaroque)
                    {
                        case 1:
                            printf("Digite o novo nome do cliente (%d):\n>> ", i+1);
                            fflush(stdin);
                            fgets((clientes+i)->nome, CHAR_M, stdin);
                            (clientes+i)->nome[strcspn((clientes+i)->nome, "\n")] = 0;
                            printf("Atualizacao feita com sucesso!\n");
                            Loop_Tela();
                        break;

                        case 2:
                            printf("Digite o novo CPF do cliente (%d):\n>> ", i+1);
                            scanf("%d", &(clientes+i)->cpf);
                            printf("Atualizacao feita com sucesso!\n");
                            Loop_Tela();
                        break;

                        case 3:
                            printf("Digite o novo endere?o do cliente (%d):\n>> ", i+1);
                            fflush(stdin);
                            fgets((clientes+i)->endereco, CHAR_M, stdin);
                            (clientes+i)->endereco[strcspn((clientes+i)->endereco, "\n")] = 0;
                            printf("Atualizacao feita com sucesso!\n");
                            Loop_Tela();
                        break;

                        case 4:
                            printf("Digite o novo email do cliente (%d):\n>> ", i+1);
                            fflush(stdin);
                            fgets((clientes+i)->email, CHAR_M, stdin);
                            (clientes+i)->email[strcspn((clientes+i)->email, "\n")] = 0;
                            printf("Atualizacao feita com sucesso!\n");
                            Loop_Tela();
                        break;

                        case 5:
                            printf("Voce realmente deseja excluir o cliente (%d) ?\n", i+1);
                            printf(" -Sim(1)\n -N?o(2)\n\n>> ");
                            scanf("%d", &resp);

                            if(resp == 1)
                            {
                                //Utilizando o ultimo valor de i usado no laco de busca (cliente encontrado)
                                for(i; i < *n_clientes - 1; i++)
                                {
                                    //Copiando os dados da posicao posterior para o espaco deletado
                                    j = i + 1;

                                    (clientes+i)->id = (clientes+j)->id;
                                    strcpy(((clientes+i)->nome), ((clientes+j)->nome));
                                    (clientes+i)->cpf = (clientes+j)->cpf;
                                    strcpy(((clientes+i)->endereco), ((clientes+j)->endereco));
                                    strcpy(((clientes+i)->email), ((clientes+j)->email));

                                }

                                *n_clientes -= 1;

                                printf("Exclus?o feita com sucesso!");
                                Loop_Tela();
                            }
                        break;
                    }
                }
            }

        }while(_atualizaroque != 6);

    Loop_Tela();
}

//Traz para a memória, fecha arquivo, consulta, libera memória ou consulta direto do arquivo (mais eficaz)
void Consultar_Cliente(Cliente* clientes, int n_clientes)
{
	int i;
	
    system("cls||clear");

    printf("\t\tCONSULTAR DADOS DE CLIENTES\n\n");

    // Exibir que nao existem registros
    if(n_clientes == 0)
    {
        printf("Nenhum registro encontrado.\n");
    }
    // Senao, exibir os registros do sistema
    else
    {
        for(i = 0; i < n_clientes; i++)
        {
            printf("\nRegistro Cliente <%d>\n", i+1);

            printf("\tID:       %d\n", (clientes+i)->id);
            printf("\tCPF:      %d\n", (clientes+i)->cpf);
            printf("\tNome:     %s\n", (clientes+i)->nome);
            printf("\tEndere?o: %s\n", (clientes+i)->endereco);
            printf("\tEmail:    %s\n", (clientes+i)->email);
        }
    }

    Loop_Tela();
}








