#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <termios.h>
#include <fcntl.h>

typedef struct song
{
    char name[50];
    char singer[50];
    int releaseYear;
    struct song *next;
    struct song *back;
}song;
   
void addToPlaylist(song **head, char *name, char *singer, int releaseYear);
void print(song **head);
void playMusic(song **head);
int kbhit(void);
void findMusicSinger(song **head, char *name);
void deleteMusic(song **head, char *nameDelete);
void findSong(song **head, char *name);
void findMusicYear (song **head, int year);


//=======================================

int main() {
    song *head = NULL;
    printf("\033[1;34mSEJA BEM-VINDO(A) NOVAMENTE AO APP DE MÚSICA LÍVIA E OS JOVANNOS\033[0m\n");

    // músicas padrão
    addToPlaylist(&head, "Vestido de Seda", "Milionário e José Rico", 1984);
    addToPlaylist(&head, "Tentei te Esquecer", "Mato Grosso e Mathias", 1982);
    addToPlaylist(&head, "Um Sonhador", "Leandro e Leonardo", 1982);
    addToPlaylist(&head, "Fio de Cabelo", "Chitãozinho e Xororó", 1982);
    addToPlaylist(&head, "Chorei de Saudade", "João Mineiro e Marciano", 1982);
    addToPlaylist(&head, "Convite de Casamento", "Gian e Giovani", 1982);
    addToPlaylist(&head, "Página de Amigos", "Chitãozinho e Xororó", 1982);
    addToPlaylist(&head, "Pense em Mim", "Leandro e Leonardo", 1982);
    addToPlaylist(&head, "Idas e Voltas", "Mato Grosso e Mathias", 1982);

    int escolha = -1;
    char nameSong[50], nameSinger[50];
    int releaseYear;

    while (escolha != 0) {
        printf("\n\033[1;34m===== MENU =====\033[0m\n");
        printf("01 - Ver playlist\n");
        printf("02 - Adicionar música\n");
        printf("03 - Remover música\n");
        printf("04 - Pesquisar música\n");
        printf("05 - Filtrar por cantor\n");
        printf("06 - Filtrar por ano\n");
        printf("07 - Tocar playlist\n");
        printf("00 - Sair\n\n");
        printf("Digite sua opção: ");
        scanf(" %d", &escolha);

        switch (escolha) {
            case 1:
                print(&head);
                break;

            case 2:
                printf("Nome da Música: ");
                scanf(" %50[^\n]", nameSong);
                printf("Cantor: ");
                scanf(" %50[^\n]", nameSinger);
                printf("Ano de lançamento: ");
                scanf(" %d", &releaseYear);
                addToPlaylist(&head, nameSong, nameSinger, releaseYear);
                break;

            case 3:
                printf("Qual música quer remover? ");
                scanf(" %50[^\n]", nameSong);
                deleteMusic(&head, nameSong);
                break;

            case 4:
                printf("Qual música quer encontrar? ");
                scanf(" %50[^\n]", nameSong);
                findSong(&head, nameSong);
                break;

            case 5:
                printf("Qual cantor quer filtrar? ");
                scanf(" %50[^\n]", nameSinger);
                findMusicSinger(&head, nameSinger);
                break;

            case 6:
                printf("Quer escutar músicas de qual ano? ");
                scanf(" %d", &releaseYear);
                findMusicYear(&head, releaseYear);
                break;

            case 7:
                playMusic(&head);
                break;

            case 0:
                printf("\n\033[1;32mFim do programa. Até a próxima! 🎵\033[0m\n");
                break;

            default:
                printf("\033[1;31mOpção inválida! Tente novamente.\033[0m\n");
                break;
        }
    }
}


//==============================================

void addToPlaylist(song **head, char *name, char *singer, int releaseYear)
{
    song *new = malloc(sizeof(song));

    strcpy(new->name, name);
    strcpy(new->singer, singer);
    new->releaseYear = releaseYear;

    if(*head == NULL)
    {
        *head = new;
        new->next = *head;
        new->back = new;
    }
    else
    {
        song *aux = *head;
        while(aux->next != *head)
        {
            aux = aux->next;
        }
        aux->next = new;
        new->next = *head;
        new->back = aux;
        (*head)->back = new;
    }
}
void print(song **head)
{
    song *aux = *head;
    song *back = aux->back; 
    char previous[50];
    strcpy(previous, back->name);

    printf("\nYour playlist\n");

    while(aux->next != *head)
    {
        printf("\033[1;35m\n%s\033[0m\n", aux->name);
        printf("Singer: %s\n", aux->singer);
        printf("Release year: %d\n", aux->releaseYear);
        printf("previous song:\033[1m%s\033[0m\n", previous);
        back = aux;
        strcpy(previous, back->name);
        aux = aux->next;
    }
    strcpy(previous, back->name);
    printf("\033[1;35m\n%s\033[0m\n", aux->name);
    printf("Singer: %s\n", aux->singer);
    printf("Release year: %d\n", aux->releaseYear);
    printf("previous song:\033[1m%s\033[0m\n", previous);
}
void playMusic(song **head)
{
    song *aux = *head; //cria uma variavel auxiliar
    char c;
    int i;
    int duracao = 5; 

    while(1) //toca as musicas eternamente até que o usuario peça para parar
    {
        printf("\nTocando agora: \033[1;35m%s\033[0m - \033[1m%s\033[0m\n", aux->name, aux->singer);
        printf("\np = pause | r = retome | s = pular | q = sair\n\n");
        i = 0;

        while(i < duracao) //enquanto a musica não terminar
        {
            // mostrar barra de progresso
            printf("\r[");
            int progresso = (i+1) * 10 / duracao; //essa linha aqui calcula de quanto em quantos quadradinhos deve progredir
            for(int j = 0; j < 10; j++) { //imprime os quadradinhos até que o progresso concluir os 10 espaços
                if(j < progresso) printf("\033[1;35m■\033[0m"); 
                else printf(" ");
            }
            printf("] %ds ", i+1); //Fecha a barra com ]
            fflush(stdout); //essa linha é para forçar que o quadrado apareça no momento em que for preenchido

            
            if(kbhit()) { //se foi digitado algo
                c = getchar(); //aramazena oq foi digitado
                if(c == 'p') { //se oq foi digitado foi p
                    printf("\nMúsica pausada! Pressione r para retomar...\n"); //imprime isso
                    while(1) { //cria um loop eterno até que r seja digitado
                        if(kbhit()) { //mesma coisa, verifica se user digitou
                            char resume = getchar(); //armazena o caractr digitado
                            if(resume == 'r') break; //se for r ele vai sair do loop e vai continuar o progresso
                        }
                    }
                } else if(c == 's') {
                    printf("\nPróxima música\n");
                    break; // sai do loop  e vai pra próxima música
                } else if(c == 'q') {
                    printf("\nA playlist parou de ser reprduzida\n");
                    return; // sai da playlist
                }
            }
            sleep(1); // espera 1 segundo
            i++;
        }
        system("clear"); //limpa o terminal
        sleep(0.1);
        aux = aux->next; // próxima música na lista 

    }
}

void findMusicSinger(song **head, char *name)
{
    song *aux = *head;
    char nameSinger[50];
    strcpy(nameSinger, name);

    do
    {
        if(strcmp(aux->singer, nameSinger) == 0)
        {
            printf("\033[1;35m%s\033[0m\n", aux->name);
        }
        aux = aux->next;
    }while (aux->next != *head);
}

void findMusicYear (song **head, int year)
{
    song *aux = *head;

    do
    {
        if(aux->releaseYear == year)
        {
            printf("\033[1;35m%s\033[0m\n", aux->name);
        }
        aux = aux->next;
    }while (aux->next != *head);
}

void deleteMusic(song **head, char *nameDelete)
{
    if(*head == NULL)
    {
        printf("A playlist está vazia");
        return;
    }

    song *aux = *head;
    char name[50];

    strcpy(name, nameDelete);
    while (aux->next != *head)
    {
        if(strcmp(name, aux->name) == 0)
        {
            if(aux->back == aux->next)
            {
                free(aux);
                *head = NULL;
            }
            else
            {
                aux->back->next = aux->next;
                aux->next->back = aux->back;
                free(aux);

                printf("\033[1;31mMúsica retirada da playlist\033[0m\n");
                return;
            }

        }
        aux = aux->next;
    }
    printf("Não foi encontrada música com esse título");
 
}
void findSong(song **head, char *name)
{
    if (*head == NULL) {
        printf("Playlist vazia.\n");
        return;
    }

    song *aux = *head;
    do {
        if (strcmp(aux->name, name) == 0) {
            printf("\033[1;33m\nMúsica encontrada na sua playlist!\033[0m\n");
            printf("\033[1;35m%s\033[0m - %s (%d)\n",
                   aux->name, aux->singer, aux->releaseYear);
            return;
        }
        aux = aux->next;
    } while (aux != *head);

    printf("\033[1;31mMúsica não encontrada!\033[0m\n");
}
int kbhit(void) {
    struct termios oldt /* armazena as configurações atuais do terminal para restaurar depois*/, newt /*configuração quue vai ser mudada*/;
    int ch; //caracter lido
    int oldf; //armazena flags de arquivo antigas

    tcgetattr(STDIN_FILENO, &oldt); //pega a configuração atual do terminal padrão (stdin)
    newt = oldt; //copia para newt pq vai ser mudado temporariamente
    newt.c_lflag &= ~(ICANON | ECHO); //desativa o canon e o echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);//aplica as novas configurações imediatamente
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);// pega e altera as flags de leitura do arquivo e faz com que getchar() não bloqueie

    ch = getchar();
     //Restaura o terminal ao estado normal, para não afetar o resto do programa
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    //Se ch não for EOF, significa que o usuário pressionou uma tecla
    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}