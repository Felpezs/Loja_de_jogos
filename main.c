#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define CHAR_MAX 100
#define VENDAS_BUFFER 5

typedef struct cliente
{
    int id;
    int cpf;
    char nome[CHAR_MAX];
    char endereco[CHAR_MAX];
    char email[CHAR_MAX];
} Cliente;

typedef struct produto
{
    int id;
    char nome[CHAR_MAX];
    char categoria[CHAR_MAX];
    int quantidade;
    float preco;
} Produto;

typedef struct venda
{
    int id_comprador;
    char categoria[CHAR_MAX];
    char nome[CHAR_MAX];
    int quantidade;
    float lucro;
} Venda;

void Cadastrar_Cliente(Cliente**, int*);
void Cadastrar_Produto(Produto**, int*);
void Consultar(Cliente**, Produto**, Venda**, int*, int*, int*);
void Atualizar_Cliente(Cliente**, int*);
void Atualizar_Produto(Produto**, int*);
void Comprar(Cliente**, Produto**, Venda**, int*, int*, int*, int*);
void Loop_Tela();

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
    OPÇÃO 1: Tela de cadastro dos produtos ou usuários dependendo da escolha
    OPÇÃO 2: Tela de consulta de dados de produtos ou de clientes dependendo da escolha
    OPÇÃO 3: Tela de atualização de dados de produtos ou clientes dependendo da escolha
    OPÇÃO 4: Tela de compra de produtos
    OPÇÃO 5: Encerra o programa
    OBS.: Após o encerramento de uso em cada tela, o usuário voltará para a tela principal*/

    //Loop para permanência na tela inicial

    do
    {
        printf("\t\tSISTEMA DE ESTOQUE E COMPRA DE JOGOS\n\n");
        printf("Escolha uma opção para prosseguir:\n\n");
        printf("- Cadastrar(1)\n");
        printf("- Consultar(2)\n");
        printf("- Atualizar(3)\n");
        printf("- Comprar(4)\n");
        printf("- Sair(5)\n\n>> ");
        scanf("%d", &resp);

        switch (resp)
        {
            //Opcao de Cadastro de Clientes ou Produtos
            case 1:
                do
                {
                    //Limpeza de Tela
                    system("cls||clear");
                    
                    //Submenu de Cadastro
                    printf("\t\tCADASTRO\n\n");
                    printf("Escolha uma opção para prosseguir:\n");
                    printf("- Clientes (1)\n");
                    printf("- Produtos (2)\n");
                    printf("- Retornar (3)\n\n>>");
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
        
                    //Limpeza de Tela
                    system("cls||clear");

                }while(tela_desejada !=3);
            break;

            //Opcao de Consultar Clientes e Produtos
            case 2:
                Consultar(&clientes, &produtos, &vendas, &qntd_clientes, &qntd_produtos, &qntd_vendas);
            break;

            //Opcao de Atualizar Clientes ou Produtos
            case 3:

                do
                {
                    //Limpeza de Tela
                    system("cls||clear");

                    //Submenu de Atualização
                    printf("\t\tATUALIZAR\n\n");
                    printf("Escolha uma opção para prosseguir:\n");
                    printf("- Clientes (1)\n");
                    printf("- Produtos (2)\n");
                    printf("- Retornar (3)\n\n>>");
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
        
                    //Limpeza de Tela
                    system("cls||clear");

                }while(tela_desejada !=3);
            break;
            
            //Opcao de Comprar Produtos
            case 4:
                Comprar(&clientes, &produtos, &vendas, &qntd_clientes, &qntd_produtos, &qntd_vendas, &ctrl_vendasBuffer);
            break;
        }

        //Limpeza de Tela
        system("cls||clear");
    }
    while(resp !=5);

    return 0;
}

void Cadastrar_Cliente(Cliente **clientes, int *n_clientes)
{
    system("cls||clear");

    int i = 0;

    printf("\t\tCADASTRO DE CLIENTES\t\n\n");

    //Verificar se é a primeira execucao do programa
    if(*n_clientes == 0)
    {
        printf("Digite a quantidade de clientes a ser cadastrada:\n\n>>");
        scanf("%d", &*n_clientes);

        if(*n_clientes <= 0)
            printf("\nHouve um erro no registro!\n");

        else
        {
            //Alocacao dinamica com malloc
            *clientes = (Cliente*) malloc(*n_clientes * sizeof(Cliente));

            //Cadastramento de produtos
            for(i = 0; i < *n_clientes; ++i)
            {
                printf("Preencha os dados do Cliente (%d):\nID: ", i+1);
                scanf("%d", &(*clientes+i)->id);
                
                printf("Cpf: ");
                scanf("%d", &(*clientes+i)->cpf);
                
                fflush(stdin);

                printf("Nome: ");

                fgets((*clientes+i)->nome, CHAR_MAX, stdin);
                (*clientes+i)->nome[strcspn((*clientes+i)->nome, "\n")] = 0;

                printf("Endereço: ");
                fgets((*clientes+i)->endereco, CHAR_MAX, stdin);
                (*clientes+i)->nome[strcspn((*clientes+i)->endereco, "\n")] = 0;

                printf("Email: ");
                fgets((*clientes+i)->email, CHAR_MAX, stdin);
                (*clientes+i)->nome[strcspn((*clientes+i)->email, "\n")] = 0;
            }
            printf("Registrado com sucesso!\n");
        }
            
    }

    else
    {   
        int _qnt;
        printf("Digite a quantidade de clientes a ser cadastrada:\n>>");
        scanf("%d", &_qnt);

        if(_qnt <= 0)
            printf("\nHouve um erro no registro!\n");
        
        else
        {
            *n_clientes += _qnt;

            //Realocacao dinamica com realloc
            *clientes = (Cliente*) realloc(*clientes, *n_clientes * sizeof(Cliente));

            //Cadastramento de produtos 
            for(int i = (*n_clientes - _qnt); i < *n_clientes; ++i)
            {
                printf("Preencha os dados do Cliente (%d):\nID: ", i+1);
                scanf("%d", &(*clientes+i)->id);
                
                printf("Cpf: ");
                scanf("%d", &(*clientes+i)->cpf);
                
                fflush(stdin);

                printf("Nome: ");

                /*Entrada dos dados do tipo string é feita pelo fgets
                para evitar que as strings sejam distribuidas erroneamente por conta 
                de espaços em branco, utilizou-se o strcspn, substituindo por "0"
                quando é encontrado o "\n"*/

                fgets((*clientes+i)->nome, CHAR_MAX, stdin);
                (*clientes+i)->nome[strcspn((*clientes+i)->nome, "\n")] = 0;

                printf("Endereço: ");
                fgets((*clientes+i)->endereco, CHAR_MAX, stdin);
                (*clientes+i)->nome[strcspn((*clientes+i)->endereco, "\n")] = 0;

                printf("Email: ");
                fgets((*clientes+i)->email, CHAR_MAX, stdin);
                (*clientes+i)->nome[strcspn((*clientes+i)->email, "\n")] = 0;
            }
            printf("Registrado com sucesso!\n");
        }

    }

    Loop_Tela();
}

void Cadastrar_Produto(Produto** produtos, int *n_produtos)
{
    system("cls||clear");
    
    printf("\t\tCADASTRO DE PRODUTOS\t\n\n");
    
    //Verificar se eh a primeira execucao do programa
    if(*n_produtos == 0)
    {
        printf("Digite a quantidade de produtos a ser cadastrada:\n\n>>");
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

                fflush(stdin);

                printf("Nome: ");
                fgets((*produtos+i)->nome, CHAR_MAX, stdin);
                (*produtos+i)->nome[strcspn((*produtos+i)->nome, "\n")] = 0;

                printf("Categoria: ");
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
            
            fflush(stdin);

            printf("Nome: ");
            fgets((*produtos+i)->nome, CHAR_MAX, stdin);
            (*produtos+i)->nome[strcspn((*produtos+i)->nome, "\n")] = 0;


            printf("Categoria: ");
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
}

void Consultar(Cliente** clientes, Produto** produtos, Venda** vendas, int* n_clientes, int* n_produtos, int* n_vendas)
{
    int _veroque;
    system("cls||clear");

    // Submenu para ver clientes ou produtos
    printf("\tCONSULTAR DADOS CADASTRAIS\n\n");
    printf("Ver:\n- Clientes (1)\n- Produtos (2) \n- Vendas (3)\n\n>> ");
    scanf("%d", &_veroque);

    // Consultar os dados dos clientes
    if(_veroque == 1)
    {
        // Exibir que não existem registros
        if(*n_clientes == 0)
        {
            printf("Nenhum registro encontrado.\n");
        }
        
        // Senão exibir os registros do sistema
        else
        {
            for(int i = 0; i < *n_clientes; ++i)
            {
                printf("\nRegistro Cliente nº(%d)\n", i+1);
                printf("\tID:   %d\n", (*clientes+i)->id);
                printf("\tCPF:      %d\n", (*clientes+i)->cpf);
                printf("\tNome:     %s\n", (*clientes+i)->nome);
                printf("\tEndereço: %s\n", (*clientes+i)->endereco);
                printf("\tEmail:    %s\n", (*clientes+i)->email);
            }
        }
    }
    // Consultar os dados dos produtos
    else if(_veroque == 2)
    {
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
                printf("\tID:     %d\n", (*produtos+i)->id);
                printf("\tNome:       %s\n", (*produtos+i)->nome);
                printf("\tCategoria:  %s\n", (*produtos+i)->categoria);
                printf("\tQuantidade: %d\n", (*produtos+i)->quantidade);
                printf("\tPreco:    R$%.2f\n", (*produtos+i)->preco);
            }
        }
    }
    // Consultar os dados das vendas
    else if(_veroque == 3)
    {
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
                printf("\tID Cliente: %d\n", (*vendas+i)->id_comprador);
                printf("\tCategoria Jogo: %s\n", (*vendas+i)->categoria);
                printf("\tNome Jogo:      %s\n", (*vendas+i)->nome);
                printf("\tQuantidade:     %d\n", (*vendas+i)->quantidade);
                printf("\tLucro:        R$%.2f\n", (*vendas+i)->lucro);

                _totalVendas += (*vendas+i)->lucro;
            }

            printf("\nTotal arrecadado: R$%.2f\n", _totalVendas);
        }
    }

    Loop_Tela();
}

void Atualizar_Cliente(Cliente** clientes, int *n_clientes)
{
    int _atualizaroque = 0, _buscaID, i = 0; 
    
    if(*n_clientes == 0)
        printf("\nNão há clientes cadastrados!\n");

    else
        do
        {
            system("cls||clear");

            printf("\t\tATUALIZAR CLIENTES\n");

            printf("-Atualizar Nome(1)\n -Atualizar CPF(2)\n -Atualizar Endereço(3)\n -Atualizar Email(4)\n -Retornar(5)\n\n>> ");
            scanf("%d", &_atualizaroque);

            //Quebra o loop e volta para o início
            if(_atualizaroque >=1 && _atualizaroque < 5)
            {
                printf("\nDigite o ID do Cliente: ");
                scanf("%d", &_buscaID);
            
                //For para buscar o indice do produto no vetor
                for(i = 0 ; i < *n_clientes; ++i)
                {
                    if((*clientes+i)->id == _buscaID)
                        break;
                }

                /*OBSERVAÇÃO: o if seguinte está dando erros, ajustar posteriormente*/
                //Se o i chegou no final do vetor, o usuario não existe
                if(i >= *n_clientes - 1)
                {
                    printf("Usuário não está cadastrado!\nFaça seu cadastro no menu principal.\n");
                    break;
                }

                switch (_atualizaroque)
                {
                    case 1:
                        printf("Digite o novo nome do cliente (%d):\n>>", i+1);
                        fgets((*clientes+i)->nome, CHAR_MAX, stdin);
                        (*clientes+i)->nome[strcspn((*clientes+i)->nome, "\n")] = 0;
                    break;

                    case 2:
                        printf("Digite o novo CPF do cliente (%d):\n>>", i+1);
                        scanf("%d", &(*clientes+i)->cpf);   
                    break;

                    case 3:
                        printf("Digite o novo endereço do cliente (%d):\n>>", i+1);
                        fgets((*clientes+i)->endereco, CHAR_MAX, stdin);
                        (*clientes+i)->endereco[strcspn((*clientes+i)->endereco, "\n")] = 0;
                    break;

                    case 4:
                        printf("Digite o novo email do cliente (%d):\n>>", i+1);
                        fgets((*clientes+i)->email, CHAR_MAX, stdin);
                        (*clientes+i)->email[strcspn((*clientes+i)->email, "\n")] = 0;  
                    break;
                } 
            }
        }while(_atualizaroque != 5);

    Loop_Tela();
}

void Atualizar_Produto(Produto** produtos, int *n_produtos)
{
    int _atualizaroque = 0, _buscaID, i = 0; 
    
    if(*n_produtos == 0)
        printf("\nNão há produtos cadastrados!\n");
    
    else
        do
        {
            system("cls||clear");

            printf("\t\tATUALIZAR PRODUTOS\t\n");
 
            printf("-Atualizar Nome(1)\n -Categoria(2)\n -Quantidade(3)\n -Preço(4)\n -Retornar(5)\n\n>> ");
            scanf("%d", &_atualizaroque);

                //Quebra o loop e volta para o início
            if(_atualizaroque >= 1 && _atualizaroque < 5)
            {
                printf("\nDigite o ID do produto: ");
                scanf("%d", &_buscaID);
        
                //For para buscar o indice do produto no vetor
                for(i = 0; i < *n_produtos; ++i)
                {
                    if((*produtos+i)->id == _buscaID)
                        break;
                }

                /*OBSERVAÇÃO: o if seguinte está dando erros, ajustar posteriormente*/
                //Se o i chegou no final do vetor, a mercadoria não existe
                if(i >= *n_produtos - 1)
                {
                    printf("Mercadoria não cadastrada!\n Faça o cadastro no menu principal.\n");
                    break;
                }

                switch (_atualizaroque)
                {   
                    case 1:
                        printf("Digite o novo nome do produto (%d):\n>>", i+1);
                        fgets((*produtos+i)->nome, CHAR_MAX, stdin);
                        (*produtos+i)->nome[strcspn((*produtos+i)->nome, "\n")] = 0;
                    break;

                    case 2:
                        printf("Digite a nova categoria do produto (%d):\n>>", i+1);
                        fgets((*produtos+i)->categoria, CHAR_MAX, stdin);
                        (*produtos+i)->categoria[strcspn((*produtos+i)->categoria, "\n")] = 0;   
                    break;

                    case 3:
                        printf("Digite a nova quantidade do produto (%d):\n>>", i+1);
                        scanf("%d", &(*produtos+i)->quantidade);
                    break;

                    case 4:
                        printf("Digite o novo preço do produto (%d):\n>>", i+1);
                        scanf("%f", &(*produtos+i)->preco);   
                    break;
                }
            } 
        }while(_atualizaroque != 5);

    Loop_Tela();
}

void Comprar(Cliente** clientes, Produto** produtos, Venda** vendas, int* n_clientes, int* n_produtos, int* n_vendas, int* ctrl_vendasBuffer)
{
    int _userID, _prodQntd;
    char _prodCat[CHAR_MAX] = "", _prodNome[CHAR_MAX];
    system("cls||clear");

    // Submenu para comprar um produto
    printf("\tCOMPRAR PRODUTO\n\n");
    printf("Código do cliente:\n\n>> ");
    scanf("%d", &_userID);

    // Verificar se o Código fornecido (ID) do CLIENTE está cadastrado
    for(int i = 0; i < *n_clientes; ++i)
    {
        if((*clientes+i)->id == _userID)
        {
            // Usuário está cadastrado! 
            // Pedir o ID do produto e a quantidade
            printf("Categoria do jogo:\n>> ");
            scanf("%s", _prodCat);
            printf("Nome do jogo:\n>> ");
            scanf("%s", _prodNome);
            printf("Quantidade desejada:\n>> ");
            scanf("%d", &_prodQntd);

            break;
        }
        // else if(i >= (*n_clientes - 1))
        // {
        //     // Usuário não está cadastrado!
        //     // Solicitar que faça seu cadastro no sistema
        //     printf("Usuário não está cadastrado!\nFaça seu cadastro no menu principal.\n");

        //     printf("\nPressione [Enter] para continuar.\n>> ");
        //     while(getchar()!='\n');
        //     getchar();
        //     //FIM
        // }
    }
    
    /* Não verificar o produto(loop abaixo) caso o usuário não esteja cadastrado
     * Obs: a variável _prodID fará esse controle, portanto:
     * Para _prodID == 0: o usuário não está cadastrado
     * Para _prodId != 0: o usuário está cadastrado e solicitou um produto
     */
    if(strcmp(_prodCat, "") == 0)
    {
        // Usuário não está cadastrado!
        // Solicitar que faça seu cadastro no sistema
        printf("Usuário não está cadastrado!\nFaça seu cadastro no menu principal.\n");

        Loop_Tela();
        // FIM
        return;
    }

    /* Verificar se o Código fornecido (ID) do PRODUTO está cadastrado */
    int i = 0;
    //Loop enquanto o codigo procurado nao for igual ao codigo pedido ou nao ser encontrado
    do
    {
        if(strcmp((*produtos+i)->categoria, _prodCat) == 0)            //se o codigo procurado for igual ao codigo pedido
        {
            if(strcmp((*produtos+i)->nome, _prodNome) == 0)
            {
                if((*produtos+i)->quantidade >= _prodQntd)   //se a quantidade desejada estiver disponivel
                {
                    // A compra foi realizada com sucesso!
                    printf("Produto disponivel. A quantidade desejada foi retirada do estoque\n");
                    (*produtos+i)->quantidade -= _prodQntd;           //decrementa a qntd desejada

                    // Contabilizar mais uma venda
                    *n_vendas += 1;

                    // Realizar o malloc caso a quantidade de vendas for a primeira
                    if(*n_vendas == 1)
                    {
                        // Fazer a alocação dinâmica inicial com o tamanho do buffer
                        *vendas = (Venda*) malloc(VENDAS_BUFFER * sizeof(Venda));
                        *ctrl_vendasBuffer += 1;
                    }
                    // Ou realloc quando a quantidade de vendas estourar o valor do buffer
                    else if(*n_vendas > (VENDAS_BUFFER * (*ctrl_vendasBuffer)))
                    {
                        // Incrementar mais uma quantidade de vezes do buffer de vendas
                        *ctrl_vendasBuffer += 1;
                        
                        // Fazer a realocação dinâmica
                        *vendas = (Venda*) realloc(*vendas, (VENDAS_BUFFER * (*ctrl_vendasBuffer)) * sizeof(Venda));               
                    }
                    
                    // Registrar os dados na estrutura vendas
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
                    printf("LUCRO:             %.2f\n", (*vendas + (*n_vendas - 1))->lucro);

                    break;
                }
                else
                {
                    printf("ESTOQUE INSUFICIENTE.\n");
                    break; 
                }
            }
            else if (i >= (*n_produtos - 1))
            {
                printf("NOME DO JOGO NÃO ENCONTRADO.\n");
                break;
            }
        }
        else if (i >= (*n_produtos - 1))
        {
            printf("CATEGORIA NÃO ENCONTRADA.\n");
            break;
        } 

        i++; 
    }
    while((i <= (*n_produtos)) || (strcmp((*produtos+i)->categoria, _prodCat) != 0));

    Loop_Tela();
}

void Loop_Tela()
{   
    //Função que não sai do loop enquanto o usuário não digitar a tecla enter
    printf("\nPressione [Enter] para continuar.\n");
    while(getchar()!='\n');
    getchar();
}
