#include <stdio.h>
#include <stdlib.h>

#define CHAR_MAX 100

typedef struct cliente
{
    int id;
    int cpf;
    char nome[CHAR_MAX];
    char endereco[CHAR_MAX];
    char email[CHAR_MAX];
} Cliente;

//Apenas testesss

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
    int id_produto;
    int lucro;
} Venda;

void Cadastrar_Cliente(Cliente**, int*);
void Cadastrar_Produto(Produto**, int*);
void Consultar(Cliente**, Produto**, Venda**, int*, int*, int*);
void Atualizar_Cliente(Cliente**, int*);
void Atualizar_Produto(Produto**, int*);
void Comprar(Cliente**, Produto**, Venda**, int*, int*, int*);

int main()
{
    /*===========================================================
                 Sistema de Estoque de Loja de Jogos

    Projeto desenvolvido pelos integrantes:          
    -> Jonatas Goes da Silva                          
    -> Felipe Eduardo                            
    -> Victor Yukio Shirasuna                          
    =============================================================*/

    int resp;
    int qntd_clientes = 0, qntd_produtos = 0, qntd_vendas = 0, tela_desejada = 0;

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
        printf("\t\tSISTEMA DE ESTOQUE E COMPRA DE JOGOS\n");
        printf("Escolha uma opção para prosseguir:\n");
        printf("- Cadastrar(1)\n");
        printf("- Consultar(2)\n");
        printf("- Atualizar(3)\n");
        printf("- Comprar(4)\n");
        printf("- Sair(5)\n\n");
        printf(">>");
        scanf("%d", &resp);

        switch (resp)
        {
            //Opcao de Cadastro de Clientes ou Produtos
            case 1:
                do
                {
                    //Limpeza de Tela
                    system("cls||clear");

                    printf("\t\tCADASTRO\n");
                    printf("Escolha uma opção para prosseguir:\n");
                    printf("- Jogos (1)\n");
                    printf("- Clientes (2)\n");
                    printf("- Retornar (3)\n>>");
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

                    printf("\t\tATUALIZAR\n");
                    printf("Escolha uma opção para prosseguir:\n");
                    printf("- Clientes (1)\n");
                    printf("- Jogos (2)\n");
                    printf("- Retornar (3)\n>>");
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
                Comprar(&clientes, &produtos, &vendas, &qntd_clientes, &qntd_produtos, &qntd_vendas);
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
    
    printf("\t\tCADASTRO DE CLIENTES\t\n");

    //Verificar se eh a primeira execucao do programa
    if(*n_clientes == 0)
    {
        printf("Digite a quantidade de clientes a ser cadastrada:\n>>");
        scanf("%d", &*n_clientes);

        //Alocacao dinamica com malloc
        *clientes = (Cliente*) malloc(*n_clientes * sizeof(Cliente));

        //Cadastramento de produtos
        for(int i = 0; i < *n_clientes; ++i)
        {
            printf("Preencha os dados do Cliente (%d):\nID: ", i+1);
            scanf("%d", &(*clientes+i)->id);
            
            printf("cpf: ");
            scanf("%d", &(*clientes+i)->cpf);
            
            printf("Nome: ");
            scanf("%s", &(*clientes+i)->nome);

            printf("Endereço: ");
            scanf("%s", &(*clientes+i)->endereco);
            
            printf("Email: ");
            scanf("%s", &(*clientes+i)->email);
        }
        printf("Registrado com sucesso!\n");
    }

    else
    {   
        int _qnt;
        printf("Digite a quantidade de clientes a ser cadastrada:\n>>");
        scanf("%d", &_qnt);
        
        *n_clientes += _qnt;
            
        //Realocacao dinamica com realloc
        *clientes = (Cliente*) realloc(*clientes, *n_clientes * sizeof(Cliente));

        //Cadastramento de produtos 
        for(int i = (*n_clientes - _qnt); i < *n_clientes; ++i)
        {
            printf("Preencha os dados do Cliente (%d):\nID: ", i+1);
            scanf("%d", &(*clientes+i)->id);
            
            printf("cpf: ");
            scanf("%d", &(*clientes+i)->cpf);
            
            printf("Nome: ");
            scanf("%s", &(*clientes+i)->nome);

            printf("Endereço: ");
            scanf("%s", &(*clientes+i)->endereco);
            
            printf("Email: ");
            scanf("%s", &(*clientes+i)->email);
        }
        printf("Registrado com sucesso!\n");
    }

    //O usuário não saírá da tela enquanto não digitar a tecla enter
    printf("Pressione [Enter] para continuar.\n");
    while(getchar()!='\n');
    getchar();
}

void Cadastrar_Produto(Produto** produtos, int *n_produtos)
{
    system("cls||clear");
    
    printf("\t\tCADASTRO DE PRODUTOS\t\n");
    
    //Verificar se eh a primeira execucao do programa
    if(*n_produtos == 0)
    {
        printf("Digite a quantidade de produtos a ser cadastrada: ");
        scanf("%d", &*n_produtos);

        //Alocacao dinamica com malloc
        *produtos = (Produto*) malloc(*n_produtos * sizeof(Produto));

        //Cadastramento de produtos
        for(int i = 0; i < *n_produtos; ++i)
        {
            printf("Preencha os dados do Produto (%d):\nCategoria: ", i+1);
            scanf("%s", &(*produtos+i)->categoria);

            printf("ID: ");
            scanf("%d", &(*produtos+i)->id);
            
            printf("Quantidade: ");
            scanf("%d", &(*produtos+i)->quantidade);

            printf("Preco: ");
            scanf("%d", &(*produtos+i)->preco);
        }
        printf("Registrado com sucesso!\n");
    }

    else
    {   
        int _qnt;
        printf("Digite a quantidade de produtos a ser cadastrada: ");
        scanf("%d", &_qnt);
        
        *n_produtos += _qnt;
            
        //Realocacao dinamica com realloc
        *produtos = (Produto*) realloc(*produtos, *n_produtos * sizeof(Produto));

        //Cadastramento de produtos 
        for(int i = (*n_produtos - _qnt); i < *n_produtos; ++i)
        {
            printf("Preencha os dados do Produto (%d):\nCategoria: ", i+1);
            scanf("%s", &(*produtos+i)->categoria);

            printf("ID: ");
            scanf("%d", &(*produtos+i)->id);
            
            printf("Quantidade: ");
            scanf("%d", &(*produtos+i)->quantidade);

            printf("Preco: ");
            scanf("%d", &(*produtos+i)->preco);
        }

        printf("Registrado com sucesso!\n");
    }

    //O usuário não saírá da tela enquanto não digitar a tecla enter
    printf("Pressione [Enter] para continuar.\n");
    while(getchar()!='\n');
    getchar();
}

void Consultar(Cliente** clientes, Produto** produtos, Venda** vendas, int* n_clientes, int* n_produtos, int* n_vendas)
{
    int _veroque;
    system("cls||clear");

    // Submenu para ver clientes ou produtos
    printf("\tConsultar dados cadastrais\t\t\n");
    printf("Ver\n1. Clientes\n2. Produtos\n3. Vendas\n>> ");
    scanf("%d", &_veroque);

    // Consultar os dados dos clientes
    if(_veroque == 1)
    {
        for(int i = 0; i < *n_clientes; ++i)
        {
            printf("Cliente (%d)\n", i+1);
            printf("\tCódigo:\t\t%d\n", (*clientes+i)->id);
            printf("\tCPF:\t%d\n", (*clientes+i)->cpf);
            printf("\tNome:\t%s\n", (*clientes+i)->nome);
            printf("\tEndereço:\t%s\n", (*clientes+i)->endereco);
            printf("\tEmail:\t%s\n", (*clientes+i)->email);
        }
    }
    // Consultar os dados dos produtos
    else if(_veroque == 2)
    {
        for(int i = 0; i < *n_produtos; ++i)
        {
            printf("Produto (%d)\n", i+1);
            printf("\tCódigo:\t\t%d\n", (*produtos+i)->id);
            printf("\tCódigo:\t\t%s\n", (*produtos+i)->nome);
            printf("\tCategoria:\t%s\n", (*produtos+i)->categoria);
            printf("\tQuantidade:\t%d\n", (*produtos+i)->quantidade);
            printf("\tPreco:\t%d\n", (*produtos+i)->preco);
        }
    }
    else if(_veroque == 3)
    {
       for(int i = 0; i < *n_vendas; ++i)
        {
            printf("Venda (%d)\n", i+1);
            printf("\tCódigo Cliente:\t\t%d\n", (*vendas+i)->id_comprador);
            printf("\tCódigo Produto:\t%d\n", (*vendas+i)->id_produto);
            printf("\tLucro:\t%d\n", (*vendas+i)->lucro);
        } 
    }

    //O usuário não saírá da tela enquanto não digitar a tecla enter
    printf("Pressione [Enter] para continuar.\n");
    while(getchar()!='\n');
    getchar();
}

void Atualizar_Cliente(Cliente** clientes, int *n_clientes)
{
    int _atualizaroque = 0, _buscaID, i = 0; 
    
    while(1)
    {
        system("cls||clear");

        printf("\t\tATUALIZAR CLIENTES\n");

        printf("-Atualizar Nome(1)\n -Atualizar CPF(2)\n -Atualizar Endereço(3)\n -Atualizar Email(4) -Retornar(5)\n>> ");
        scanf("%d", &_atualizaroque);

        //Quebra o loop e volta para o início
        if(_atualizaroque == 5)
            break;

        printf("\nDigite o ID do Cliente: ");
        scanf("%d", &_buscaID);
        
        //For para buscar o indice do produto no vetor
        for(i ; i < *n_clientes; ++i)
        {
            if((*clientes+i)->id == _buscaID)
                break;
        }
        
        //Se o i chegou no final do vetor, a mercadoria não existe
        if(i >= *n_clientes - 1)
        {
            printf("Usuário não está cadastrado!\nFaça seu cadastro no menu principal.\n");
            break;
        }

        switch (_atualizaroque)
        {
            case 1:
                printf("Digite o novo nome do cliente (%d):\n>>", i+1);
                scanf("%s", (*clientes+i)->nome);
            break;

            case 2:
                printf("Digite o novo CPF do cliente (%d):\n>>", i+1);
                scanf("%d", &(*clientes+i)->cpf);   
            break;

            case 3:
                printf("Digite o novo endereço do cliente (%d):\n>>", i+1);
                scanf("%s", &(*clientes+i)->endereco);
            break;

            case 4:
                printf("Digite o novo email do cliente (%d):\n>>", i+1);
                scanf("%s", &(*clientes+i)->email);   
            break;
        }
    }while(_atualizaroque != 5)

  //O usuário não saírá da tela enquanto não digitar a tecla enter  
  printf("Pressione [Enter] para continuar.\n");
  while(getchar()!='\n');
  getchar();
}

void Atualizar_Produto(Produto** produtos, int *n_produtos)
{
    int _atualizaroque = 0, _buscaID, i = 0; 
    
    while(1)
    {
        system("cls||clear");

        printf("\t\tATUALIZAR PRODUTOS\t\n");
 
        printf("-Atualizar Nome(1)\n -Categoria(2)\n -Quantidade(3)\n -Preço(4) -Retornar(5)\n>> ");
        scanf("%d", &_atualizaroque);

        //Quebra o loop e volta para o início
        if(_atualizaroque == 5)
            break;

        printf("\nDigite o ID do produto: ");
        scanf("%d", &_buscaID);
        
        //For para buscar o indice do produto no vetor
        for(int i = 0; i < *n_produtos; ++i)
        {
            if((*produtos+i)->id == _buscaID)
                break;
        }
        
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
                scanf("%s", (*produtos+i)->nome);
            break;

            case 2:
                printf("Digite a nova categoria do produto (%d):\n>>", i+1);
                scanf("%s", &(*produtos+i)->categoria);   
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
    }while(_atualizaroque != 5)

    //O usuário não saírá da tela enquanto não digitar a tecla enter
    printf("Pressione [Enter] para continuar.\n");
    while(getchar()!='\n');
    getchar();
}

void Comprar(Cliente** clientes, Produto** produtos, Venda** vendas, int* n_clientes, int* n_produtos, int* n_vendas)
{
    int _userID, _prodID = 0, _prodQntd;
    
    system("cls||clear");
    printf("\tComprar Produto\n");
    printf("Código do cliente: ");
    scanf("%d", &_userID);

    // Verificar se o Código fornecido (ID) do CLIENTE está cadastrado
    for(int i = 0; i < *n_clientes; ++i)
    {
        if((*clientes+i)->id == _userID)
        {
            // Usuário está cadastrado! 
            // Pedir o ID do produto e a quantidade
            printf("Código do produto: ");
            scanf("%d", &_prodID);
            printf("Quantidade desejada: ");
            scanf("%d", &_prodQntd);
        }
        else if(i >= (*n_clientes - 1))
        {
            // Usuário não está cadastrado!
            // Solicitar que faça um cadas
            printf("Usuário não está cadastrado!\nFaça seu cadastro no menu principal.\n");
        }
    }
    
    /* Verificar se o Código fornecido (ID) do PRODUTO está cadastrado */

    /* Não verificar o produto(loop abaixo) caso o usuário não esteja cadastrado
     * Obs: a variável _prodID fará esse controle, portanto:
     * Para _prodID == 0: o usuário não está cadastrado
     * Para _prodId != 0: o usuário está cadastrado e solicitou um produto
     */
    if(_prodID == 0)
        return;
    
    int i = 0;
    //Loop enquanto o codigo procurado nao for igual ao codigo pedido ou nao ser encontrado
    do
    {
        if((*produtos+i)->id == _prodID)            //se o codigo procurado for igual ao codigo pedido
        {
            if((*produtos+i)->quantidade >= _prodQntd)   //se a quantidade desejada estiver disponivel
            {
                // A compra foi realizada com sucesso!
                printf("Produto disponivel. A quantidade desejada foi retirada do estoque\n");
                (*produtos+i)->quantidade -= _prodQntd;           //decrementa a qntd desejada

                // Contabilizar mais uma venda
                // OBS: LEMBRAR PARA MELHORAR ESTA PART
                *n_vendas += 1;

                if(*n_vendas == 0)
                {
                    // Fazer a alocação dinâmica inicial
                    *vendas = (Venda*) malloc(*n_vendas * sizeof(Venda));
                }
                else
                {
                    // Fazer a realocação dinâmica
                    *vendas = (Venda*) realloc(*vendas, *n_vendas * sizeof(Venda));                    
                }
                
                (*vendas + (*n_vendas - 1))->id_comprador = _userID;
                (*vendas + (*n_vendas - 1))->id_produto = _prodID;
                (*vendas + (*n_vendas - 1))->lucro = ((*produtos+i)->preco * _prodQntd);

                printf("\nID COMPRADOR:%d\n", (*vendas + (*n_vendas - 1))->id_comprador);
                printf("ID PRODUTO:%d\n", (*vendas + (*n_vendas - 1))->id_produto);
                printf("LUCRO:%d\n", (*vendas + (*n_vendas - 1))->lucro);
            }
            else
                 printf("ESTOQUE INSUFICIENTE DA MERCADORIA\n");
            break; 
        }
        else if (i >= (*n_produtos))
        {
            printf("MERCADORIA NAO CADASTRADA\n");
            break;
        } 

        i++; 
    }
    while((i <= (*n_produtos)) || ((*produtos+i)->id != _prodID));

    //O usuário não saírá da tela enquanto não digitar a tecla enter
    printf("Pressione [Enter] para continuar.\n");
    while(getchar()!='\n');
    getchar();
}