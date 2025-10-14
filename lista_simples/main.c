#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Vou fazer uma fila de impressão
// essa fila de impressão segue o princípio de FIFO (First In, First Out)

struct no {
    char arquivo[80];
    struct no *prox;
};

void inserirArquivo(struct no **ptrCabeca);

void removerArquivo(struct no **ptrCabeca);

void exibirFila(struct no **ptrCabeca);

int tamanhoLista(struct no **ptrCabeca);

int main() {
    int continuar = 1, escolharUser;
    struct no *cabeca = NULL, **ptrCabeca = &cabeca;

    while (continuar == 1) {

        // apresenta as opções do usuário e após isso o usuário escolhe
        printf("Escolha:\n");
        printf("[1] Inserir Arquivo na Fila de Impressão;\n");
        printf("[2] Remover Arquivo da Fila;\n"); // por indice ou por nome
        printf("[3] Exibir Fila de Impressão;\n");
        printf("[4] Exibir o Tamanho da Fila;\n");
        printf("[5] Exibir o Próximo Arquivo a ser Impresso;\n");
        printf("[6] Imprimir arquivo;\n"); // vai imprimir um, assim os outros irão para frente após isso e esse será excluído
        printf("[0] Sair;\n");
        
        scanf("%d", &escolharUser);
        switch (escolharUser) {
        case 1:
            inserirArquivo(&cabeca);
            break;

        case 2:
            removerArquivo(&cabeca);
            break;

        case 3:
            exibirFila(&cabeca);
            break;

        case 4: 
            printf("O tamanho da lista é: %d\n", tamanhoLista(&cabeca));
            break;

        case 5:

            break;

        case 6:

            break;

        case 0:
            continuar = 0;
            break;

        default:
            printf("Opção Inexistente\n");
            break;
        }
    }
}

void inserirArquivo(struct no **ptrCabeca) {
    // auxiliar para não modificar o principal
    struct no *atual = *ptrCabeca;
    // armazena o espaço do novo arquivo
    struct no *novoArquivo = malloc(sizeof *novoArquivo);
    novoArquivo->prox = NULL;

    // cancela resíduos que podem ter ficado na entrada
    getchar();

    printf("Qual o nome do arquivo (+ extensão)? \n");
    // lê o arquivo, com permissão para espaços
    fgets(novoArquivo->arquivo, sizeof(novoArquivo->arquivo), stdin);

    // remove o caracter que simboliza o 'enter' ao final da string
    novoArquivo->arquivo[strcspn(novoArquivo->arquivo, "\n")] = '\0';

    // significa que a lista ainda não possui arquivos
    if (*ptrCabeca == NULL) { 
        *ptrCabeca = novoArquivo;
        
        printf("%s adicionado com sucesso\n", (*ptrCabeca)->arquivo);
        return;

    } else {
        // looping até achar o nó que aponta para NULL como próximo
        while (atual->prox != NULL) {
            atual = atual->prox;
        }

        // quem era o último começa a apontar para o novo;
        atual->prox = novoArquivo;
        printf("%s adicionado com sucesso\n", novoArquivo->arquivo);
    }
}

void removerArquivo(struct no **ptrCabeca) {
    // para armezenar o antecessor e o que será deletado
    struct no *tempAntecessor = NULL, *atual = *ptrCabeca;
    // cancela resíduos que podem ter ficado na entrada
    getchar();

    int escolhaUser;
    printf("Como você quer remover? [1] Pelo Nome; [2] Pelo Indice\n");
    scanf("%d", &escolhaUser);

    switch (escolhaUser) {
    // por nome
    case 1:
        char nomeArquivoDeletar[80];
        // cancela resíduos que podem ter ficado na entrada
        getchar();

        // pergunto ao usuário o nome do arquivo e após isso salvo esse nome
        printf("Qual o nome do arquivo que você gostaria de remover? Escreva o nome correto, junto com sua extensão\n");

        fgets(nomeArquivoDeletar, sizeof(nomeArquivoDeletar), stdin);
        // remove o 'enter' que acaba sendo salvo no final
        nomeArquivoDeletar[strcspn(nomeArquivoDeletar, "\n")] = '\0';

        // looping até encontrar o arquivo (enquanto tiver nós e enquanto não tiver encontrado o arquivo)
        while (atual != NULL && strcmp(atual->arquivo, nomeArquivoDeletar) != 0) {
            tempAntecessor = atual;
            atual = atual->prox;
        }

        // vê se o arquivo foi encontrado
        if (atual == NULL) {
            printf("Arquivo não encontrado\n");
            return;
        }

        // se for o primeiro nó
        if (tempAntecessor == NULL) {
            *ptrCabeca = atual->prox;
        } else {
            tempAntecessor->prox = atual->prox;
        }

        // libera o nó deletado
        free(atual);
        atual = NULL;

        printf("Removido com sucesso!\n");
        break;
        
    // por indice    
    case 2:
        int i = 1, indiceEscolhaUser, tamanhoDaLista = tamanhoLista(ptrCabeca);

        // pede o indice ao usuário
        printf("Qual o indice que você gostaria de remover? \n");
        scanf("%d", &indiceEscolhaUser);

        // vê se o número que o usuário escolheu é possível de estar na lista
        if (tamanhoDaLista == 0) {
            printf("A lista não possui nós\n");
            return;
        } else if (indiceEscolhaUser > tamanhoDaLista || indiceEscolhaUser < 0) {
            printf("O número escolhido está fora do tamanho da lista\n");
            return;
        }

        // fazer um looping para ir contabilizando até encontrar o indice correto
        while (i != indiceEscolhaUser) {
            tempAntecessor = atual;
            atual = atual->prox;
            i++;
        }

        // verifica se é o primeiro
        if (tempAntecessor == NULL) {
            *ptrCabeca = atual->prox;
        } else {
            tempAntecessor->prox = atual->prox;
        }

        // libera o nó deletado
        free(atual);
        atual = NULL;

        printf("Removido com sucesso!\n");
        break;
    default:
        printf("Opção Inexistente\n");
    }
}

void exibirFila(struct no **ptrCabeca) {
    // define um ponteiro "iterador" que começa pela cabeça
    struct no *ptrI;
    ptrI = (*ptrCabeca);

    // enquanto o endereço dele não for NULL
    while(ptrI != NULL){
        // printa o arquivo e passa para o próximo
        printf("%s ", ptrI->arquivo);
        ptrI = ptrI->prox;
    }
    printf("\n");
}

int tamanhoLista(struct no **ptrCabeca) {
    int i = 0;
    // auxiliar para não alterar a original
    struct no *atual = *ptrCabeca;
    while (atual != NULL) {
        i++;
        atual = atual->prox;
    }
    return i;
} 

