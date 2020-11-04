#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operacoes.h"
#include "cliente.h"

void Cadastrar_Cliente(Cliente **clientes, int *n_clientes)
{
    system("cls||clear");

    int i = 0;

    printf("\t\tCADASTRO DE CLIENTES\t\n\n");

    //Verificar se eh a primeira execucao do programa para fazer o malloc ou realloc
    if(*n_clientes == 0)
    {
        printf("Digite a quantidade de clientes a ser cadastrada:\n\n>> ");
        scanf("%d", &*n_clientes);

        if(*n_clientes <= 0)
            printf("\nHouve um erro no registro!\n");

        else
        {
            //Alocacao dinamica com malloc
            *clientes = (Cliente*) malloc(*n_clientes * sizeof(Cliente));

            //Cadastramento de clientes
            for(i = 0; i < *n_clientes; ++i)
            {
                printf("Preencha os dados do Cliente (%d):\nID: ", i+1);
                scanf("%d", &(*clientes+i)->id);

                printf("CPF: ");
                scanf("%d", &(*clientes+i)->cpf);

                /*Entrada dos dados do tipo string é feita pelo fgets
                para evitar que as strings sejam distribuidas erroneamente por conta
                de espaços em branco, utilizou-se o strcspn, substituindo por "0"
                quando é encontrado o "\n"*/

                printf("Nome: ");
                fflush(stdin);
                fgets((*clientes+i)->nome, CHAR_MAX, stdin);
                (*clientes+i)->nome[strcspn((*clientes+i)->nome, "\n")] = 0;

                printf("Endereço: ");
                fflush(stdin);
                fgets((*clientes+i)->endereco, CHAR_MAX, stdin);
                (*clientes+i)->endereco[strcspn((*clientes+i)->endereco, "\n")] = 0;

                printf("Email: ");
                fflush(stdin);
                fgets((*clientes+i)->email, CHAR_MAX, stdin);
                (*clientes+i)->email[strcspn((*clientes+i)->email, "\n")] = 0;
            }
            printf("Registrado com sucesso!\n");
        }
    }
    else
    {
        int _qnt;
        printf("Digite a quantidade de clientes a ser cadastrada:\n>> ");
        scanf("%d", &_qnt);

        if(_qnt <= 0)
            printf("\nHouve um erro no registro!\n");

        else
        {
            *n_clientes += _qnt;

            //Realocacao dinamica com realloc
            *clientes = (Cliente*) realloc(*clientes, *n_clientes * sizeof(Cliente));

            //Cadastramento de clientes
            for(int i = (*n_clientes - _qnt); i < *n_clientes; ++i)
            {
                printf("Preencha os dados do Cliente (%d):\nID: ", i+1);
                scanf("%d", &(*clientes+i)->id);

                printf("CPF: ");
                scanf("%d", &(*clientes+i)->cpf);

                printf("Nome: ");
                fflush(stdin);
                fgets((*clientes+i)->nome, CHAR_MAX, stdin);
                (*clientes+i)->nome[strcspn((*clientes+i)->nome, "\n")] = 0;

                printf("Endereço: ");
                fflush(stdin);
                fgets((*clientes+i)->endereco, CHAR_MAX, stdin);
                (*clientes+i)->endereco[strcspn((*clientes+i)->endereco, "\n")] = 0;

                printf("Email: ");
                fflush(stdin);
                fgets((*clientes+i)->email, CHAR_MAX, stdin);
                (*clientes+i)->email[strcspn((*clientes+i)->email, "\n")] = 0;
            }
            printf("Registrado com sucesso!\n");
        }
    }
    Loop_Tela();

    system("cls||clear");
}

void Atualizar_Cliente(Cliente** clientes, int *n_clientes)
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
                printf("\nNão há clientes cadastrados!\n");
                _atualizaroque = 6;
            }

            else
            {
                printf("-Atualizar Nome(1)\n -Atualizar CPF(2)\n -Atualizar Endereço(3)\n -Atualizar Email(4)\n -Excluir Cliente(5)\n -Retornar(6)\n\n>> ");
                scanf("%d", &_atualizaroque);

                //Quebra o loop e volta para o in?cio
                if(_atualizaroque >=1 && _atualizaroque < 6)
                {
                    printf("\nDigite o ID do Cliente: ");
                    scanf("%d", &_buscaID);

                    //For para buscar o indice do produto no vetor
                    for(i = 0 ; i < *n_clientes; ++i)
                    {
                        if((*clientes+i)->id == _buscaID)
                            break;
                    }

                    //Se chegou no final do vetor e o indice de i for maior que o numero de clientes
                    if((i + 1) > *n_clientes)
                    {
                        printf("Usuário não está cadastrado!\nFaça seu cadastro no menu principal.\n");
                        break;
                    }

                    switch (_atualizaroque)
                    {
                        case 1:
                            printf("Digite o novo nome do cliente (%d):\n>> ", i+1);
                            fflush(stdin);
                            fgets((*clientes+i)->nome, CHAR_MAX, stdin);
                            (*clientes+i)->nome[strcspn((*clientes+i)->nome, "\n")] = 0;
                            printf("Atualização feita com sucesso!\n");
                            Loop_Tela();
                        break;

                        case 2:
                            printf("Digite o novo CPF do cliente (%d):\n>> ", i+1);
                            scanf("%d", &(*clientes+i)->cpf);
                            printf("Atualização feita com sucesso!\n");
                            Loop_Tela();
                        break;

                        case 3:
                            printf("Digite o novo endere?o do cliente (%d):\n>> ", i+1);
                            fflush(stdin);
                            fgets((*clientes+i)->endereco, CHAR_MAX, stdin);
                            (*clientes+i)->endereco[strcspn((*clientes+i)->endereco, "\n")] = 0;
                            printf("Atualização feita com sucesso!\n");
                            Loop_Tela();
                        break;

                        case 4:
                            printf("Digite o novo email do cliente (%d):\n>> ", i+1);
                            fflush(stdin);
                            fgets((*clientes+i)->email, CHAR_MAX, stdin);
                            (*clientes+i)->email[strcspn((*clientes+i)->email, "\n")] = 0;
                            printf("Atualização feita com sucesso!\n");
                            Loop_Tela();
                        break;

                        case 5:
                            printf("Você realmente deseja excluir o cliente (%d) ?\n", i+1);
                            printf(" -Sim(1)\n -Não(2)\n\n>> ");
                            scanf("%d", &resp);

                            if(resp == 1)
                            {
                                //Utilizando o último valor de i usado no laço de busca (cliente encontrado)
                                for(i=i; i < *n_clientes - 1; i++)
                                {
                                    //Copiando os dados da posição posterior para o espaço deletado
                                    j = i + 1;

                                    (*clientes+i)->id = (*clientes+j)->id;
                                    strcpy(((*clientes+i)->nome), ((*clientes+j)->nome));
                                    (*clientes+i)->cpf = (*clientes+j)->cpf;
                                    strcpy(((*clientes+i)->endereco), ((*clientes+j)->endereco));
                                    strcpy(((*clientes+i)->email), ((*clientes+j)->email));

                                }

                                *n_clientes -= 1;

                                //Fazendo a realocação dinâmica para liberar espaços vazios
                                *clientes = (Cliente*) realloc(*clientes, *n_clientes * sizeof(Cliente));

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

void Consultar_Cliente(Cliente** clientes, int* n_clientes)
{
    system("cls||clear");

    printf("\t\tCONSULTAR DADOS DE CLIENTES\n\n");

    // Exibir que não existem registros
    if(*n_clientes == 0)
    {
        printf("Nenhum registro encontrado.\n");
    }
    // Senão, exibir os registros do sistema
    else
    {
        for(int i = 0; i < *n_clientes; ++i)
        {
            printf("\nRegistro Cliente nº(%d)\n", i+1);

            printf("\tID:       %d\n", (*clientes+i)->id);
            printf("\tCPF:      %d\n", (*clientes+i)->cpf);
            printf("\tNome:     %s\n", (*clientes+i)->nome);
            printf("\tEndereço: %s\n", (*clientes+i)->endereco);
            printf("\tEmail:    %s\n", (*clientes+i)->email);
        }
    }

    Loop_Tela();
}