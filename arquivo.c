#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "musicas.h"
#include "playlists.h"
#include "faixas.h"

void removerEspaco(char *s){
    int i;
    for (i = 0; i < strlen(s) && s[i] == ' '; i++);

    strcpy(s, s + i);
    for (i = (int)strlen(s) - 1; i >= 0 && s[i] == ' '; i--);

    s[i + 1] = '\0';
}

int inserirMusica(char *linha){
    int codigo, ano;
    char titulo[100];
    char artista[50];

    if (sscanf(linha, "M;%d;%[^;];%[^;];%d", &codigo, titulo, artista, &ano) != 4){
        printf("Erro ao ler musica\n");
        return 0;
    }

    removerEspaco(titulo);
    removerEspaco(artista);

    if (!cadastrarMusica(codigo, titulo, artista, ano))
        return 0;

    printf("Musica %d - %s foi cadastrada\n", codigo, titulo);

    return 1;
}

int inserirPlaylist(char *linha){
    int codigo;
    char titulo[51];

    if (sscanf(linha, "P;%d;%[^;]", &codigo, titulo) != 2) {
        printf("Erro ao ler playlist\n");
        return 0;
    }

    removerEspaco(titulo);
     if (!criarPlaylist(codigo, titulo))
        return 0;

    printf("Playlist %d - %s foi cadastrada\n", codigo, titulo);
    return 1;
}

int inserirFaixas(char *linha){
    int codPlaylist, codMusica;
    char tipo;

    if (sscanf(linha, "I;%c;%d;%d", &tipo, &codPlaylist, &codMusica) != 3){
        printf("Erro ao ler linha de faixa\n");
        return 0;
    }

    if (tipo == 'I'){
        if (!inserirInicioPlaylist(codPlaylist, codMusica))
            return 0;

        printf("Musica %d inserida no inicio da playlist %d\n",
               codMusica, codPlaylist);
        return 1;
    }

    if (tipo == 'F'){
        if (!inserirFimPlaylist(codPlaylist, codMusica))
            return 0;

        printf("Musica %d inserida no fim da playlist %d\n",
               codMusica, codPlaylist);
        return 1;
    }

    printf("Tipo de insercao invalido: %c\n", tipo);
    return 0;
}

    int remover(char *linha){
        int codPlaylist, codMusica;

        if (sscanf(linha, "R;%d;%d", &codPlaylist, &codMusica) != 2){
            printf("Erro ao ler linha de remocao\n");
            return 0;
        }

        if (!removerMusicaPlaylist(codPlaylist, codMusica))
            return 0;

        printf("Musica %d removida da playlist %d\n",
               codMusica,
               codPlaylist);

        return 1;
    }

    void carregarArquivo(const char *nomeArqTxt)
    {
        FILE *arq;
        char linha[300];

        int totalMusicas = 0;
        int totalPlaylists = 0;
        int totalInsercoes = 0;
        int totalRemocoes = 0;

        arq = fopen(nomeArqTxt, "r");

        if (arq == NULL)
        {
            printf("Erro ao abrir o arquivo: %s\n", nomeArqTxt);
            return;
        }

        while (fgets(linha, sizeof(linha), arq))
        {

            linha[strcspn(linha, "\n")] = '\0';

           if (strlen(linha) == 0)
            continue;

            switch (linha[0]) {
            case 'M':
                totalMusicas += inserirMusica(linha);
                break;
            case 'P':
                totalPlaylists += inserirPlaylist(linha);
                break;
            case 'I':
                totalInsercoes += inserirFaixas(linha);
                break;
            case 'R':
                totalRemocoes += remover(linha);
                break;
            default:
                printf("Erro: comando desconhecido '%c'\n",
                       linha[0]);
                break;
            }
        }
        fclose(arq);

        printf("\nResumo: \n");
        printf("Musicas cadastradas : %d\n", totalMusicas);
        printf("Playlists criadas   : %d\n", totalPlaylists);
        printf("Insercoes realizadas: %d\n", totalInsercoes);
        printf("Remocoes realizadas : %d\n", totalRemocoes);
        printf("\nExecucao do arquivo \"%s\" concluida\n", nomeArqTxt);
    }