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

void removerUrl(struct pagina **cabeca, struct pagina **final, struct pagina **atual);

void exibirHistorico(struct pagina **cabeca);

int tamanhoLista(struct pagina **cabeca);

void navegar(struct pagina **atual, struct pagina **cabeca, struct pagina **final);

int main() {
    int continuar = 1, escolharUser;
    struct pagina *cabeca = NULL, *atual = NULL, *final = NULL;

    while (continuar == 1) {

        // apresenta as opções do usuário e após isso o usuário escolhe
        printf("Escolha:\n");
        printf("[1] Inserir URL;\n");
        printf("[2] Remover URL;\n");
        printf("[3] Exibir o Histórico;\n");
        printf("[4] Exibir o Tamanho do Histórico;\n");
        printf("[5] Navegar;\n"); 
        printf("[0] Sair;\n");
        scanf("%d", &escolharUser);

        getchar();

        switch (escolharUser) {
        case 1:
            inserirUrl(&cabeca, &final, &atual);
            break;
        
        case 2:
            removerUrl(&cabeca, &final, &atual);
            break;

        case 3:
            exibirHistorico(&cabeca);
            break;
            
        case 4:
            printf("O tamanho do histórico é: %d\n", tamanhoLista(&cabeca));
            break; 

        case 5:
            navegar(&atual, &cabeca, &final);
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
        // faz o final caminhar para o próximo e conecta os ponteiros

        // o novo nó vai apontar para o anterior
        NovaUrl->ant = *final;
        // o antigo final aponta para o próximo
        (*final)->prox = NovaUrl;
        // novo final aponta para NULL
        NovaUrl->prox = NULL;
        // o novo nó agora é o final 
        *final = NovaUrl;
    }
}

void removerUrl(struct pagina **cabeca, struct pagina **final, struct pagina **atual) {
    char urlRemovida[20];
    struct pagina *ptrI = *cabeca;

    printf("Qual a URL que você gostaria de apagar?\n");

    fgets(urlRemovida, sizeof(urlRemovida), stdin);
    urlRemovida[strcspn(urlRemovida, "\n")] = '\0';
    
    while (ptrI != NULL) {
        // verifica se é a cabeça que tem que ser removida
        if (strcmp((*cabeca)->url, urlRemovida) == 0) {
            // salva o que vai ser removido
            struct pagina *remover = ptrI;

            // a cabeça aponta para a nova cabeça
            *cabeca = ptrI->prox;
            // se a cabeça tiver algum valor
            if (*cabeca != NULL) {
                (*cabeca)->ant = NULL;
            }

            // se a atual for a que vai ser removida, ele aponta para a cabeça
            if (*atual == ptrI) {
                *atual = *cabeca;
            }

            // se a final também for removida, ele aponta para a cabeça
            if (*final == ptrI) {
                *final = *cabeca;
            }

            // libera
            free(remover);
            remover = NULL;

            printf("Apagado com sucesso!\n");
            return;
        }

        // se a url do próximo for igual a url que vai ser removida
        if (ptrI->prox != NULL && strcmp(ptrI->prox->url, urlRemovida) == 0  ) {
            // pega o anterior e o próximo para conecta-los
            struct pagina *anterior = ptrI, *proximo = ptrI->prox->prox;

            // se a atual for a que vai ser removida
            if (*atual == ptrI->prox) {
                *atual = anterior;
            }

            // se o final for a que vai ser removida
            if (*final == ptrI->prox) {
                *final = anterior;
            } 

            // o antecessor vai começar a apontar para o novo próximo
            anterior->prox = proximo;
            if (proximo != NULL) {
                proximo->ant = anterior;
            }

            // libera
            free(ptrI->prox);
            ptrI->prox = NULL;

            printf("Apagado com sucesso!\n");
            return;
        }

        ptrI = ptrI->prox;
    }

    printf("Não encontrado \n");
}

void exibirHistorico(struct pagina **cabeca) {
    // é um ponteiro iterador para percorrer o histórico
    struct pagina *ptrI = *cabeca;

    while (ptrI != NULL) {
        printf("%s ", ptrI->url);
        ptrI = ptrI->prox;
    }
    printf("\n");
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

void navegar(struct pagina **atual, struct pagina **cabeca, struct pagina **final) {
    // verifica se o atual é válido
    if (atual == NULL) {
        return;
    }

    int continuar = 1, opcaoUser;

    while (continuar == 1) {
        // limpa o terminal
        system("clear");
        printf("Você está em: %s\n", (*atual)->url);
        printf("\n");
        // opções para o usuário
        printf("Escolha: \n [1] Próximo;\n [2] Voltar;\n [0] Sair da Navegação;\n");

        scanf("%d", &opcaoUser);

        switch (opcaoUser) {
            case 1:
                // se o usuário estiver no limite ele mostrará
                if (*atual == *final) {
                    printf("você chegou ao limite\n");
                    getchar(); // limpa o caractere do \n que sobrou ao digitar
                    getchar(); // só continua quando o usuário apertar 'enter'
                } else {
                    *atual = (*atual)->prox;
                }
                break;

            case 2:
                // se o usuário estiver no limite ele mostrará
                if (*atual == *cabeca) {
                    printf("você chegou ao limite\n");
                    getchar(); // limpa o caractere do \n que sobrou ao digitar
                    getchar(); // só continua quando o usuário apertar 'enter'
                } else {
                    *atual = (*atual)->ant;
                }
                break;
            case 0:
                continuar = 0;
                break;
        }
    }

}