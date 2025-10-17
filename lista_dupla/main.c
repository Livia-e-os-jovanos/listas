#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// vou simular uma navegação entre páginas
// o usuário vai cadastrar a página, essa página pode retornar ou avançar

struct pagina {
    char url[20];
    struct pagina *prox;
    struct pagina *ant;
};

void inserirURL(struct pagina *ptr);

void main() {
    int continuar = 1, escolharUser;
    struct pagina *cabeca, *atual;

    while (continuar == 1) {

        // apresenta as opções do usuário e após isso o usuário escolhe
        printf("Escolha:\n");
        printf("[1] Inserir URL;\n");
        printf("[2] Remover URL;\n"); // por indice ou por nome
        printf("[3] Exibir os URLs;\n");
        printf("[4] Exibir o Tamanho do Histórico;\n");
        printf("[5] Avançar;\n");
        printf("[6] Voltar;\n"); 
        printf("[0] Sair;\n");
        scanf("%d", &escolharUser);

        switch (escolharUser) {
        case 1:
            inserirURL(cabeca);
            break;
        case 0:
            continuar = 0;
            break;
        }
    }
}

void inserirURL(struct pagina *ptr) {
    
}