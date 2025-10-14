#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Vou fazer uma fila de impressão
// essa fila de impressão segue o princípio de FIFO (First In, First Out)

struct no {
    char arquivo[80];
    struct no *prox;
};

void inserirArquivo(struct no *ptrCabeca);

int tamanhoLista(struct no *ptrCabeca);

int main() {
    int continuar = 1, escolharUser;
    struct no *cabeca = NULL;

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
        //limpar fila?
        
        scanf("%d", &escolharUser);
        switch (escolharUser) {
        case 1:
            inserirArquivo(cabeca);
            break;
        default:
            printf("Opção Inexistente\n");
            break;
        }
    }
}

void inserirArquivo(struct no *ptrCabeca) {
    // cancela resíduos que podem ter ficado na entrada
    getchar();

    if (ptrCabeca == NULL) { // significa que a lista ainda não possui arquivos
        ptrCabeca = malloc(sizeof *ptrCabeca);

        printf("Qual o nome do arquivo (+ extensão)? \n");
        // lê o arquivo, com permissão para espaços
        fgets(ptrCabeca->arquivo, sizeof(ptrCabeca->arquivo), stdin);
        // remove o caracter que simboliza o 'enter' ao final da string
        ptrCabeca->arquivo[strcspn(ptrCabeca->arquivo, "\n")] = '\0';
        printf("%s adicionado com sucesso\n", ptrCabeca->arquivo);
    } else {
        // armazena o espaço do novo arquivo
        struct no *novoArquivo = malloc(sizeof *novoArquivo);

        // looping até achar o nó que aponta para NULL como próximo
        while (ptrCabeca->prox != NULL) {
            ptrCabeca = ptrCabeca->prox;
        }

        // quem era o último começa a apontar para o novo;
        ptrCabeca->prox = novoArquivo;
        // salva os dado do novo arquivo
        printf("Qual o nome do arquivo (+ extensão)? \n");
        fgets(novoArquivo->arquivo, sizeof(novoArquivo->arquivo), stdin);
        // remove o 'enter' que acaba sendo salvo no final
        novoArquivo->arquivo[strcspn(novoArquivo->arquivo, "\n")] = '\0';
        printf("%s adicionado com sucesso\n", novoArquivo->arquivo);

        novoArquivo->prox = NULL;
    }
}

int tamanhoLista(struct no *ptrCabeca) {
    int i = 0;
    while (ptrCabeca != NULL) {
        i++;
        ptrCabeca = ptrCabeca->prox;
    }
    return i;
} 

