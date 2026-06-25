#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>


typedef struct{
    char codigo[40];
    char titulo[40];
    char secao[40];
    char grupo[8];
    char tipo[9];
    int fig_colada;
    int disponiveltroca;
} Figurinha;


void carregar_csv(Figurinha *album, int *rodada2, FILE *arq){
    char buffer[300];

    if(*rodada2 == 1){
        for(int i = 0; i < 981; i++){
            fgets(buffer,300,arq);
            sscanf(buffer, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n",
                   &album[i].codigo,
                   &album[i].titulo,
                   &album[i].secao,
                   &album[i].grupo,
                   &album[i].tipo);
            
            album[i].fig_colada = 0;
            album[i].disponiveltroca = 0;

            printf("Código da figurinha:|%s|\n", album[i].codigo);
            printf("Título da Figurinha:|%s|\n", album[i].titulo);
            printf("Seção da Figurinha:|%s|\n", album[i].secao);
            printf("Grupo da Figurinha:|%s|\n", album[i].grupo);
            printf("Tipo da Figurinha:|%s\n", album[i].tipo);
        }
        *rodada2 = 0;
    }
    return;
}

Figurinha* cadastrar(Figurinha* album, int *quantidade) {

    album = realloc(album, (*quantidade) * sizeof(Figurinha));

    printf("Digite o código da figurinha:");
    setbuf(stdin, NULL);
    fgets(album[*quantidade].codigo, 6, stdin);
    album[*quantidade].codigo[strcspn(album[*quantidade].codigo, "\n")] = '\0';

    printf("Digite o título da figurinha:");
    setbuf(stdin,NULL);
    fgets(album[*quantidade].titulo, 29, stdin);
    album[*quantidade].titulo[strcspn(album[*quantidade].titulo, "\n")] = '\0';

    printf("Digite a seção da figurinha:");
    setbuf(stdin, NULL);
    fgets(album[*quantidade].secao, 20, stdin);
    album[*quantidade].secao[strcspn(album[*quantidade].secao, "\n")] = '\0';

    printf("Digite o grupo da figurinha:");
    setbuf(stdin, NULL);
    fgets(album[*quantidade].grupo, 8, stdin);
    album[*quantidade].grupo[strcspn(album[*quantidade].grupo, "\n")] = '\0';

    printf("Digite o tipo da figurinha:");
    setbuf(stdin, NULL);
    fgets(album[*quantidade].tipo, 9, stdin);
    album[*quantidade].tipo[strcspn(album[*quantidade].tipo, "\n")] = '\0';

    printf("Digite 1 para colar figurinha ou 0 caso não queira:");
    scanf("%d", &album[*quantidade].fig_colada);

    (*quantidade)++;

    printf("A figurinha foi cadastrada\n");
    
    return album;
}//funcao pra cadastrar a fig

void lista(Figurinha album[], int quantidade){

    if(quantidade == 981) {
        printf("Nenhuma figurinha cadastrada\n");
        return;
    }

    for(int i = 0; i < quantidade; i++){
        printf("Código da figurinha: %s\n", album[i].codigo);
        printf("Título da Figurinha: %s\n", album[i].titulo);
        printf("Seção da Figurinha: %s\n", album[i].secao);
        printf("Grupo da Figurinha: %s\n", album[i].grupo);
        printf("Tipo da Figurinha: %s\n", album[i].tipo);
        if(album[i].fig_colada == 1){
            printf("Figurinha colada: sim\n");
        }else{
            printf("Figurinha colada: não \n");
        }

    }
}//funcao q lista fig

int pesquisar(Figurinha album[], int quantidade, char codigo[]){

    int a = -1;
    for(int i = 0; i < quantidade; i++){
        if(strcmp(album[i].codigo,codigo) == 0){
            a = i;
        }
    }
    return a;
}//funcao que pesquisa fig

void alterar(Figurinha album[], int quantidade){

    char codigo[6];

    printf("Digite o código da figurinha:");
    setbuf(stdin, NULL);
    fgets(codigo, 5, stdin);
    codigo[strcspn(codigo, "\n")] = '\0';

    int posicao = pesquisar(album, quantidade, codigo);

    if(posicao == -1){
        printf("Figurinha não encontrada\n");
    }else{
        printf("Digite o novo título:");
        setbuf(stdin, NULL);
        fgets(album[posicao].titulo, 29, stdin);
        album[posicao].titulo[strcspn(album[posicao].titulo, "\n")] = '\0';

        printf("Digite a nova seção:");
        setbuf(stdin, NULL);
        fgets(album[posicao].secao, 20, stdin);
        album[posicao].secao[strcspn(album[posicao].secao, "\n")] = '\0';

        printf("Digite o novo grupo:");
        setbuf(stdin, NULL);
        fgets(album[posicao].grupo, 8, stdin);
        album[posicao].grupo[strcspn(album[posicao].grupo, "\n")] = '\0';

        printf("Digite o novo tipo:");
        setbuf(stdin, NULL);
        fgets(album[posicao].tipo, 9, stdin);
        album[posicao].tipo[strcspn(album[posicao].tipo, "\n")] = '\0';

        printf("Quer colar?(1 para sim, 0 para não):");
        scanf("%d", &album[posicao].fig_colada);

        printf("Alteração realizada\n");
    }
    return;
}//funcao que altera fig

Figurinha* excluir(Figurinha* album, int *quantidade) {

    char codigo[6];

    printf("Codigo da figurinha:");
    setbuf(stdin, NULL);
    fgets(codigo, 6, stdin);
    codigo[strcspn(codigo, "\n")] = '\0';

    int posicao = pesquisar(album,*quantidade,codigo);

    if(posicao == -1) {
        printf("A Figurinha não foi encontrada\n");
        return;
    }

    for(int i = posicao; i < *quantidade - 1; i++) {
        album[i] = album[i + 1];
    }

    (*quantidade)--;

    album = realloc(album, (*quantidade) * sizeof(Figurinha));

    printf("Figurinha removida\n");
}//funcao q exclui fig

void abrirpacote(Figurinha album[], int quantidade){
    if(quantidade == 0)
    {
        printf("Não existem figurinhas cadastradas");
        return;
    }
    
    for(int i = 0; i < 7; i++){
        int sorteada = rand() % quantidade;

        printf("Figurinha %d do pacote\n", i + 1);
        printf("Código: %s\n", album[sorteada].codigo);
        printf("Título: %s\n", album[sorteada].titulo);
        printf("Seção: %s\n", album[sorteada].secao);
        printf("Tipo: %s\n", album[sorteada].tipo);

        if(album[sorteada].fig_colada){
            printf("Você ja possui essa figurinha");

            album[sorteada].disponiveltroca++;

            printf("Adicionada automaticamente para troca");
            printf("Quantidade para troca: %d",
            album[sorteada].disponiveltroca);
        }
        else{
            int opcao;

            printf("o que deseja fazer?\n");
            printf("1 para colar no album, ");
            printf("2 para guardar para troca, ");
            printf("0 para ignorar, ");
            printf("Digite sua opção:");

            scanf("%d", &opcao);

            switch(opcao){
            case 1:
                album[sorteada].fig_colada = 1;
                printf("Figurinha colada");
                break;

                case 2:
                album[sorteada].disponiveltroca++;
                printf("Figurinha adicionada para troca");
                break;

                case 0:
                printf("Figurinha descartada");
                break;

                default:
                printf("Opção inválida");
            }
        }
    }
}

int main() {

    Figurinha *album;
    int quantidade = 981;
    album = (Figurinha*) malloc(quantidade * sizeof(Figurinha));
    if(album == NULL){
        printf("Memória insuficiente!");
        exit(1);
    }
    int opcao;
    srand(time(NULL));
    int rodada = 1;

    FILE *arq_csv = fopen("figurinhas2026.csv","r");
    if(arq_csv == NULL){
        printf("Erro!");
        exit(1);
    }
    do{
        printf("1 para cadastrar\n");
        printf("2 para listar\n");
        printf("3 para pesquisar\n");
        printf("4 para alterar\n");
        printf("5 para excluir\n");
        printf("6 para abrir pacote\n");
        printf("0 para sair\n");
        printf("Opção:");
        scanf("%d", &opcao);
        getchar();

        switch(opcao){

            case 1:
                if(rodada == 1){
                    carregar_csv(album, &rodada, arq_csv);
                    rodada = 0;
                    quantidade++;
                }else{
                    album = cadastrar(album, &quantidade);
                }
                break;

            case 2:
                lista(album, quantidade);
                break;

            case 3:

                char codigo[6];
                printf("Codigo:");
                fgets(codigo, 5, stdin);
                codigo[strcspn(codigo, "\n")] = '\0';

                int posicao = pesquisar(album, quantidade, codigo);

                if(posicao == -1){
                    printf("Não encontrada\n");
                }
                else{
                    printf("Encontrada:%s\n", album[posicao].titulo);
                }
                break;
            case 4:
                alterar(album, quantidade);
                break;
            case 5:
                excluir(album, &quantidade);
                break;
            case 6: 
                abrirpacote(album, quantidade);
                break;
            case 0:
                break;
            default:
                printf("Opção inválida\n"); 
        } 
    }while(opcao != 0);
    
    free(album);
    return 0;
}//main
