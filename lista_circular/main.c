#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tarefa
{
    char nome[50];
    char esforco[50];
    struct tarefa *prox;

}tarefa;

void criar(tarefa **cabeca, char *nome, char *esforco);
void imprimir(tarefa **cabeca);
void remover(tarefa **cabeca, char *nome);
void buscar(tarefa **cabeca, char *nome);

int main()
{
    tarefa *cabeca = NULL;
    int opcao;
    char nome[50], esforco[50];

    do {
        printf("\n=== MENU DE TAREFAS ===\n");
        printf("1 - Criar tarefa\n");
        printf("2 - Imprimir tarefas\n");
        printf("3 - Remover tarefa\n");
        printf("4 - Buscar tarefa\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // consome o \n deixado pelo scanf

        switch(opcao) {
            case 1:
                printf("Nome da tarefa: ");
                scanf(" %50[^\n]", nome);
                printf("Nivel de esforco (minimo, medio, maximo): ");
                scanf(" %50[^\n]", esforco);
                criar(&cabeca, nome, esforco);
                break;

            case 2:
                imprimir(&cabeca);
                break;

            case 3:
                printf("Nome da tarefa a remover: ");
                scanf(" %50[^\n]", nome);
                remover(&cabeca, nome);
                break;

            case 4:
                printf("Nome da tarefa a buscar: ");
                scanf(" %50[^\n]", nome);
                buscar(&cabeca, nome);
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while(opcao != 0);

    return 0;
}
void criar(tarefa **cabeca, char *nome, char *esforco)
{

    tarefa *novo = malloc(sizeof(tarefa));
    strcpy(novo->nome, nome);
    strcpy(novo->esforco, esforco);

    if(*cabeca == NULL)
    {
        *cabeca = novo;
        novo->prox = *cabeca;
    }

    else
    {
        tarefa *aux = *cabeca;
        while (aux->prox != *cabeca)
        {
            aux = aux->prox;
        }
        aux->prox = novo;
        novo->prox = *cabeca;
    }
}
void imprimir(tarefa **cabeca)
{
    tarefa *aux = *cabeca;
    if(aux == NULL)
    {
        printf("lista vazia");
        return;
    }
    do
    {
        printf("%s - %s\n", aux->nome, aux->esforco);
        aux = aux->prox;

    } while (aux != *cabeca);
    
}
void remover(tarefa **cabeca, char *nome)
{
    if (*cabeca == NULL)
    {
        printf("lista vazia");
        return; 
    }
    tarefa *aux = *cabeca;
    tarefa *anterior = NULL;
    char nomeRecebido[50];
    strcpy(nomeRecebido, nome);

    do {
        if (strcmp(aux->nome, nomeRecebido) == 0) {
            if (aux == aux->prox) {
                free(aux);
                *cabeca = NULL;
                return;
            }

            if (aux == *cabeca) {
                tarefa *ultimo = *cabeca;
                while (ultimo->prox != *cabeca)
                    ultimo = ultimo->prox;
                *cabeca = aux->prox;
                ultimo->prox = *cabeca;
                free(aux);
                return;
            }
            anterior->prox = aux->prox;
            free(aux);
            return;
        }

        anterior = aux;
        aux = aux->prox;
    } while (aux != *cabeca);
}
void buscar(tarefa **cabeca, char *nome)
{
    tarefa *aux = *cabeca;

    do
    {
        if(strcmp(aux->nome, nome) == 0)
        {
            printf("%s - %s\n", aux->nome, aux->esforco);
        }
        aux = aux->prox;
    }while(aux != *cabeca);
}
