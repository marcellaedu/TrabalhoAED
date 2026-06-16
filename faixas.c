#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "faixas.h"
#include "playlists.h"
#include "musicas.h"

void escreve_no(FILE* arq, Faixa* x, int pos) {
    fseek(arq, sizeof(CabecalhoFaixas) + pos * sizeof(Faixa), SEEK_SET);
    fwrite(x, sizeof(Faixa), 1, arq);
}

void le_no(FILE* arq, int pos, Faixa* x) {
    fseek(arq, sizeof(CabecalhoFaixas) + pos * sizeof(Faixa), SEEK_SET);
    fread(x, sizeof(Faixa), 1, arq);
}

void le_cabecalho(FILE* arq, CabecalhoFaixas* cab) {
    fseek(arq, 0, SEEK_SET);
    fread(cab, sizeof(CabecalhoFaixas), 1, arq);
}

void escreve_cabecalho(FILE* arq, CabecalhoFaixas* cab) {
    fseek(arq, 0, SEEK_SET);
    fwrite(cab, sizeof(CabecalhoFaixas), 1, arq);
}

void inicializarArquivoFaixas() {
    FILE *arq = fopen("faixas.dat", "rb");
    if (arq != NULL) {
        fclose(arq);
        return;
    }

    arq = fopen("faixas.dat", "wb");
    if (arq == NULL) {
        printf("\nErro ao criar arquivo faixas.dat. \n");
        return;
    }

    CabecalhoFaixas cab;
    cab.topo = 0;
    cab.livres = -1;

    escreve_cabecalho(arq, &cab);
    fclose(arq);
}

void atualizarPlaylist(Playlist *p, int pos_playlist) {
    FILE *arq = fopen("playlists.dat", "rb+");

    if (arq == NULL) {
        printf("Erro ao abrir playlists.dat.\n");
        return;
    }

    fseek(arq,sizeof(CabecalhoPlaylists) + pos_playlist * sizeof(Playlist),SEEK_SET);
    fwrite(p, sizeof(Playlist), 1, arq);
    fclose(arq);
}

int obterPosicaoLivre(FILE *arq, CabecalhoFaixas *cab){
    int pos;

    if (cab->livres != -1) {
        Faixa livre;
        pos = cab->livres;
        le_no(arq, pos, &livre);
        cab->livres = livre.prox;
    }else {
        pos = cab->topo;
        cab->topo++;
    }
    return pos;
}

int inserirInicioPlaylist(int codPlaylist, int codMusica) {
    Playlist p;
    int pos_playlist;
    
    if (buscarPlaylist(codPlaylist, &p, &pos_playlist) == 0) {
        printf("Erro: Playlist com codigo %d nao encontrada.\n", codPlaylist);
        return 0; 
    }

    if (!existeMusica(codMusica)) {
        printf("Erro: Musica com codigo %d nao encontrada.\n", codMusica);
        return 0;
    }

    FILE *arq = fopen("faixas.dat", "rb+");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo faixas.dat\n");
        return 0;
    }

    CabecalhoFaixas cabFaixas;
    le_cabecalho(arq, &cabFaixas);

    int pos_arquivo = obterPosicaoLivre(arq, &cabFaixas);;

    // Cria a nova faixa apontando para o antigo início
    Faixa nova_faixa;
    nova_faixa.codMusica = codMusica;
    nova_faixa.prox = p.inicioFaixas;

    escreve_no(arq, &nova_faixa, pos_arquivo);
    escreve_cabecalho(arq, &cabFaixas);
    fclose(arq);

    // Atualiza a playlist
    p.inicioFaixas = pos_arquivo;
    if (p.fimFaixas == -1) {
        p.fimFaixas = pos_arquivo;
    }

    atualizarPlaylist(&p, pos_playlist);

    return 1;
}

int inserirFimPlaylist(int codPlaylist, int codMusica) {
    Playlist p;
    int pos_playlist;
    
    if (buscarPlaylist(codPlaylist, &p, &pos_playlist) == 0) {
        printf("Erro: Playlist com codigo %d nao encontrada.\n", codPlaylist);
        return 0; 
    }

    if (!existeMusica(codMusica)) {
        printf("Erro: Musica com codigo %d nao encontrada.\n", codMusica);
        return 0;
    }

    FILE *arq = fopen("faixas.dat", "rb+");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo faixas.dat\n");
        return 0;
    }

    CabecalhoFaixas cabFaixas;
    le_cabecalho(arq, &cabFaixas);

   int pos_arquivo = obterPosicaoLivre(arq, &cabFaixas);

    Faixa nova_faixa;
    nova_faixa.codMusica = codMusica;
    nova_faixa.prox = -1;

    escreve_no(arq, &nova_faixa, pos_arquivo);

    // Atualiza playlist
    if (p.inicioFaixas == -1) {
        p.inicioFaixas = pos_arquivo;
        p.fimFaixas = pos_arquivo;
    } else {
        Faixa faixa_anterior;
        le_no(arq, p.fimFaixas, &faixa_anterior);

        faixa_anterior.prox = pos_arquivo;
        escreve_no(arq, &faixa_anterior, p.fimFaixas);
        p.fimFaixas = pos_arquivo;
    }

    escreve_cabecalho(arq, &cabFaixas);
    fclose(arq);

    atualizarPlaylist(&p, pos_playlist);

    return 1;
}

int removerMusicaPlaylist(int codPlaylist, int codMusica){
    Playlist p;
    int pos_playlist;

    if (!buscarPlaylist(codPlaylist, &p, &pos_playlist)) {
        printf("Erro: Playlist com codigo %d nao encontrada.\n", codPlaylist);
        return 0;
    }

    FILE *arq = fopen("faixas.dat", "rb+");

    if (arq == NULL) {
        printf("Erro ao abrir o arquivo faixas.dat\n");
        return 0;
    }

    int pos_atual = p.inicioFaixas;
    int pos_anterior = -1;
    Faixa faixa_atual;

    // Procura a música 
    while (pos_atual != -1) {
        le_no(arq, pos_atual, &faixa_atual);

        if (faixa_atual.codMusica == codMusica)
            break;

        pos_anterior = pos_atual;
        pos_atual = faixa_atual.prox;
    }

    if (pos_atual == -1) {
        fclose(arq);
        printf("Musica nao encontrada nesta playlist.\n");
        return 0;
    }

    // Remove da lista 
    if (pos_anterior == -1) {
        p.inicioFaixas = faixa_atual.prox;
    } else {
        Faixa faixa_anterior;

        le_no(arq, pos_anterior, &faixa_anterior);

        faixa_anterior.prox = faixa_atual.prox;

        escreve_no(arq, &faixa_anterior, pos_anterior);
    }

    // Atualiza fim 
    if (pos_atual == p.fimFaixas)
        p.fimFaixas = pos_anterior;

    if (p.inicioFaixas == -1)
        p.fimFaixas = -1;

    // Adiciona à lista de livres 
    CabecalhoFaixas cabFaixas;
    le_cabecalho(arq, &cabFaixas);

    faixa_atual.prox = cabFaixas.livres;
    cabFaixas.livres = pos_atual;

    escreve_no(arq, &faixa_atual, pos_atual);
    escreve_cabecalho(arq, &cabFaixas);

    fclose(arq);

    atualizarPlaylist(&p, pos_playlist);

    return 1;
}

void imprimirMusicasPlaylist(int codPlaylist) {
    Playlist p;
    int pos_playlist_arquivo;
    
    if (buscarPlaylist(codPlaylist, &p, &pos_playlist_arquivo) == 0) {
        printf("Playlist com codigo %d nao encontrada.\n", codPlaylist);
        return;
    }

    FILE *arq = fopen("faixas.dat", "rb");
    FILE *arq_acervo = fopen("musicas.dat", "rb");
    
    if (arq == NULL) {
        printf("Erro ao abrir arquivo de faixas.\n");
        if (arq_acervo != NULL) fclose(arq_acervo);
        return;
    }
    
    if (arq_acervo == NULL) {
        printf("Erro ao abrir arquivo de musicas.\n");
        fclose(arq);
        return;
    }

    int pos_atual = p.inicioFaixas;

    if (pos_atual == -1) {
        printf("\nPlaylist \"%s\" esta vazia.\n", p.titulo);
        fclose(arq);
        fclose(arq_acervo);
        return;
    }

    printf("\n ================== %s ==================\n", p.titulo);
    Faixa f;
    int contador = 1;

    cabMusica cab;
    fread(&cab, sizeof(cabMusica), 1, arq_acervo);

    while (pos_atual != -1) {
        le_no(arq, pos_atual, &f);

        musica m;
        int achou_musica = 0;
        
        fseek(arq_acervo, sizeof(cabMusica), SEEK_SET);
        
        while (fread(&m, sizeof(musica), 1, arq_acervo) == 1) {
            if (m.codigo == f.codMusica) {
                printf("%d. \"%s\" - %s\n", contador, m.titulo, m.artista);
                achou_musica = 1;
                break;
            }
        }

        if (!achou_musica) {
            printf("%d. [Musica codigo %d nao encontrada no acervo]\n", contador, f.codMusica);
        }

        pos_atual = f.prox;
        contador++;
    }
    printf("============================================================\n");

    fclose(arq);
    fclose(arq_acervo);
}

void imprimirNosLivres() {
    FILE *arq = fopen("faixas.dat", "rb");
    if (arq == NULL) {
        printf("Arquivo faixas.dat nao existe.\n");
        return;
    }

    CabecalhoFaixas cab;
    le_cabecalho(arq, &cab);

    int pos_atual = cab.livres;

    if (pos_atual == -1) {
        printf("\nNao existem nos livres.\n");
        fclose(arq);
        return;
    }

    printf("\n======== NOS LIVRES ========\n");
    
    Faixa f;
    while (pos_atual != -1) {
        printf("Posicao Livre: [%d] \n", pos_atual);

        le_no(arq, pos_atual, &f);

        pos_atual = f.prox;
    }
    printf("\n============================\n");

    fclose(arq);
}