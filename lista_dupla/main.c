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

void inserirUrl(struct pagina **cabeca, struct pagina **final, struct pagina **atual);

int tamanhoLista(struct pagina **cabeca);

void main() {
    int continuar = 1, escolharUser;
    struct pagina *cabeca = NULL, *atual = NULL, *final = NULL;

    while (continuar == 1) {

        // apresenta as opções do usuário e após isso o usuário escolhe
        printf("Escolha:\n");
        printf("[1] Inserir URL;\n");
        printf("[2] Remover URL;\n"); // por indice ou por nome
        printf("[3] Exibir o Histórico;\n");
        printf("[4] Exibir o Tamanho do Histórico;\n");
        printf("[5] Avançar;\n");
        printf("[6] Voltar;\n"); 
        printf("[0] Sair;\n");
        scanf("%d", &escolharUser);

        switch (escolharUser) {
        case 1:
            inserirUrl(&cabeca, &final, &atual);
            break;
        
        case 4:
            printf("O tamanho do histórico é: %d\n", tamanhoLista(&cabeca));
            break; 

        case 0:
            continuar = 0;
            break;
        }
    }
}

void inserirUrl(struct pagina **cabeca, struct pagina **final, struct pagina **atual) {
    struct pagina *NovaUrl = malloc(sizeof *NovaUrl);

    printf("Digite a URL que quer acessar:\n");

    // cancela resíduos que podem ter ficado na entrada
    getchar();

    // lê a URL
    fgets(NovaUrl->url, sizeof(NovaUrl->url), stdin);

    // remove o caracter que simboliza o 'enter' ao final da string
    NovaUrl->url[strcspn(NovaUrl->url, "\n")] = '\0';

    if (*cabeca == NULL) {
        *cabeca = NovaUrl;
        *atual = NovaUrl;
        *final = NovaUrl;

        // por ser a cabeça ele aponta NULL para os outros lados
        NovaUrl->ant = NULL;
        NovaUrl->prox = NULL;

    } else {
        // só é possível adicionar no final
        struct pagina *temp = *final;
        
        NovaUrl->ant = temp; 
        (*final)->prox = NovaUrl;
        *final = NovaUrl;
        NovaUrl->prox = NULL;
    }
}

int tamanhoLista(struct pagina **cabeca) {
    struct pagina *ptrI = *cabeca;
    int i = 0;
    while (ptrI != NULL) {
        i++;
        ptrI = ptrI->prox;
    }
    return i;
}