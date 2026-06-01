#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
   int dia;
   int mes;
   int ano;
} Data;

typedef struct {
    int ID;
    char nome[60];
    Data dataNasc;
    char instagram[60];
    char telefone[15];
} Pessoa;




void salvarArquivo(Pessoa *dados, int quantidade) {
    FILE *arquivo = fopen("cadastro.dat", "wb"); 
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar\n");
        return;
    }
    
    
    fwrite(&quantidade, sizeof(int), 1, arquivo);
    fwrite(dados, sizeof(Pessoa), quantidade, arquivo);
    
    fclose(arquivo);
    printf("Dados salvos com sucesso!\n");
}


Pessoa* carregarArquivo(int *quantidade, int *capacidade) {
    FILE *arquivo = fopen("cadastro.dat", "rb"); 
    if (arquivo == NULL) {
        *quantidade = 0;
        *capacidade = 4; 
        Pessoa *dados = (Pessoa*) malloc((*capacidade) * sizeof(Pessoa));
        return dados;
    }
    
    
    fread(quantidade, sizeof(int), 1, arquivo);
    Pessoa *dados = (Pessoa*) malloc((*capacidade) * sizeof(Pessoa));
    fread(dados, sizeof(Pessoa), *quantidade, arquivo);
    
    fclose(arquivo);
    printf("Arquivo carregado! %d registros encontrados.\n", *quantidade);
    return dados;
}




Pessoa* inserirPessoa(Pessoa *dados, int *quantidade, int *capacidade) {
    
    if (*quantidade >= *capacidade) {
        *capacidade *= 2; 
        dados = (Pessoa*) realloc(dados, (*capacidade) * sizeof(Pessoa));
   
        printf("Vetor cheio, capacidade do vetor dobrada para: %d\n", *capacidade);
    }

    int i = *quantidade; 

    printf("\nDigite o ID da pessoa: ");
    scanf("%d", &dados[i].ID);
    getchar(); 

    printf("Digite o nome: ");
    fgets(dados[i].nome, 60, stdin);
    dados[i].nome[strcspn(dados[i].nome, "\n")] = 0; 

    printf("Digite a data de nascimento (dd/mm/aaaa): ");
    scanf("%d/%d/%d", &dados[i].dataNasc.dia, &dados[i].dataNasc.mes, &dados[i].dataNasc.ano);
    getchar();

    printf("Digite o @ do Instagram: ");
    fgets(dados[i].instagram, 60, stdin);
    dados[i].instagram[strcspn(dados[i].instagram, "\n")] = 0;

    printf("Digite o telefone: ");
    fgets(dados[i].telefone, 15, stdin);
    dados[i].telefone[strcspn(dados[i].telefone, "\n")] = 0;

    (*quantidade)++; 
    printf("Pessoa cadastrada com sucesso!\n");
    
    return dados;
}

void alterarPessoa(Pessoa *dados, int quantidade) {
    int id, achou = 0;
    printf("Digite o ID da pessoa que deseja alterar: ");
    scanf("%d", &id);
    getchar();

    for(int i = 0; i < quantidade; i++) {
        if(dados[i].ID == id) {
            printf("Digite o novo nome: ");
            fgets(dados[i].nome, 60, stdin);
            dados[i].nome[strcspn(dados[i].nome, "\n")] = 0;

            printf("Digite a nova data de nascimento (dd/mm/aaaa): ");
            scanf("%d/%d/%d", &dados[i].dataNasc.dia, &dados[i].dataNasc.mes, &dados[i].dataNasc.ano);
            getchar();

            printf("Digite o novo @ do Instagram: ");
            fgets(dados[i].instagram, 60, stdin);
            dados[i].instagram[strcspn(dados[i].instagram, "\n")] = 0;

            printf("Digite o novo telefone: ");
            fgets(dados[i].telefone, 15, stdin);
            dados[i].telefone[strcspn(dados[i].telefone, "\n")] = 0;
            
            printf("Cadastro alterado com sucesso!\n");
            break;
        }else{
           printf("ID %d não encontrado", id);
        }
    }
    
}

void excluirPessoa(Pessoa *dados, int *quantidade) {
    int id, achou = 0;
    printf("Digite o ID da pessoa que deseja excluir: ");
    scanf("%d", &id);
    getchar();

    for(int i = 0; i < *quantidade; i++) {
        if(dados[i].ID == id) {
            
            for(int j = i; j < (*quantidade) - 1; j++) {
                dados[j] = dados[j + 1];
            }
            (*quantidade)--; 
            printf("Pessoa excluída com sucesso!\n");
            break;
        }else{
           printf("ID %d não encontrado.\n", id);
        }
    }
    
}

void listarPessoas(Pessoa *dados, int quantidade) {
    if(quantidade == 0) {
        printf("\nNenhuma pessoa cadastrada na agenda.\n");
        return;
    }
    printf("\nCADASTROS (%d cadastros)\n", quantidade);
    for(int i = 0; i < quantidade; i++) {
        printf("ID: %d\n", dados[i].ID);
        printf("Nome: %s\n", dados[i].nome);
        printf("Data de Nascimento: %02d/%02d/%04d\n", dados[i].dataNasc.dia, dados[i].dataNasc.mes, dados[i].dataNasc.ano);
        printf("@ do Instagram: %s\n", dados[i].instagram);
        printf("Telefone: %s\n", dados[i].telefone);
        printf("--------------------------------\n");
    }
}

void pesquisarPorID(Pessoa *dados, int quantidade) {
    int id, achou = 0;
    printf("Digite o ID da pessoa que deseja buscar: ");
    scanf("%d", &id);
    getchar();

    for(int i = 0; i < quantidade; i++) {
        if(dados[i].ID == id) {
            printf("\n--- Usuário Encontrado ---\n");
            printf("ID: %d\n", dados[i].ID);
            printf("Nome: %s\n", dados[i].nome);
            printf("Data de Nascimento: %02d/%02d/%04d\n", dados[i].dataNasc.dia, dados[i].dataNasc.mes, dados[i].dataNasc.ano);
            printf("@ do Instagram: %s\n", dados[i].instagram);
            printf("Telefone: %s\n", dados[i].telefone);
            printf("--------------------------\n");
            break;
        }else{
           printf("ID %d não encontrado.\n", id);
        }
    }
    
}



int main() {
    int opcao;
    int quantidade = 0;   
    int capacidade = 4;   
    
    
    Pessoa *dados = carregarArquivo(&quantidade, &capacidade);
    
    do {
        printf("\n+--------------------------------+\n");
        printf("| 1. Inserir pessoa              |\n");
        printf("| 2. Alterar pessoa              |\n");
        printf("| 3. Excluir pessoa              |\n");
        printf("| 4. Listar pessoas              |\n");
        printf("| 5. Pesquisar por ID            |\n");
        printf("| 6. Sair                        |\n");
        printf("+--------------------------------+\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); 

        switch (opcao) {
            case 1:
                
                dados = inserirPessoa(dados, &quantidade, &capacidade);
                break;
            case 2:
                alterarPessoa(dados, quantidade);
                break;
            case 3:
                excluirPessoa(dados, &quantidade);
                break;
            case 4:
                listarPessoas(dados, quantidade);
                break;
            case 5:
                pesquisarPorID(dados, quantidade);
                break;
            case 6:
                
                salvarArquivo(dados, quantidade);
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 6);

    
    free(dados);
    return 0;
}
