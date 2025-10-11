#include <stdio.h>

// Vou fazer uma fila de impressão
// essa fila de impressão segue o princípio de FIFO (First In, First Out)

int main() {
    int continuar = 1, escolharUser;

    while (continuar == 1) {

        // apresenta as opções do usuário e após isso o usuário escolhe
        printf("Escolha:\n");
        printf("[1] Iniciar Fila de Impressão;\n");
        printf("[2] Inserir Arquivo na Fila;\n");
        printf("[3] Remover Arquivo da Fila;\n"); // por indice ou por nome
        printf("[4] Exibir Fila de Impressão;\n");
        printf("[5] Exibir o Tamanho da Fila;\n");
        printf("[6] Exibir o Próximo Arquivo a ser Impresso;\n");
        printf("[7] Imprimir arquivo;\n"); // vai imprimir um, assim os outros irão para frente após isso e esse será excluído
        printf("[0] Sair;\n");
        //limpar fila?
        
        scanf("%d", &escolharUser);
        switch (escolharUser) {
        case 1:
            break;
        
        default:
            printf("Opção Inexistente\n");
            break;
        }
    }
}