#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "playlists.h"

void inicializarArquivoPlaylists(){
    FILE *arq = fopen("playlists.dat", "rb");

    if(arq != NULL){
        fclose(arq);
        return;
    }

    arq = fopen("playlists.dat", "wb");


    if(arq == NULL){
        printf("\nErro ao criar arquivo playlists.dat. \n");
        return;
    }

    CabecalhoPlaylists cab;

    cab.cabeca = -1;
    cab.topo = 0;

    fwrite(&cab, sizeof(CabecalhoPlaylists), 1, arq);

    fclose(arq);
}

int criarPlaylist(int codigo, char titulo[]){

    if (existePlaylist(codigo)) {
        return 0;
    }

    FILE *arq = fopen("playlists.dat", "rb+");
    if (arq == NULL) {
        return 0;
    }

    CabecalhoPlaylists cab;
    if (fread(&cab, sizeof(CabecalhoPlaylists), 1, arq) != 1) {
        fclose(arq);
        return 0;
    }

    Playlist novo;
    novo.codigo = codigo;
    strcpy(novo.titulo, titulo);
    novo.inicioFaixas = -1;
    novo.fimFaixas = -1; 
    novo.prox = -1;
    
    if (cab.cabeca == -1) {
        fseek(arq, sizeof(CabecalhoPlaylists) + cab.topo * sizeof(Playlist), SEEK_SET);
        fwrite(&novo, sizeof(Playlist), 1, arq);
        
        cab.cabeca = cab.topo;
    } else {
        int c = cab.cabeca;
        Playlist aux;

        fseek(arq, sizeof(CabecalhoPlaylists) + c * sizeof(Playlist), SEEK_SET);
        fread(&aux, sizeof(Playlist), 1, arq);

        while (aux.prox != -1) {
            c = aux.prox;
            fseek(arq, sizeof(CabecalhoPlaylists) + c * sizeof(Playlist), SEEK_SET);
            fread(&aux, sizeof(Playlist), 1, arq);
        }

        aux.prox = cab.topo;
        fseek(arq, sizeof(CabecalhoPlaylists) + c * sizeof(Playlist), SEEK_SET);
        fwrite(&aux, sizeof(Playlist), 1, arq);

        fseek(arq, sizeof(CabecalhoPlaylists) + cab.topo * sizeof(Playlist), SEEK_SET);
        fwrite(&novo, sizeof(Playlist), 1, arq);
    }

    cab.topo++;

    rewind(arq);
    fwrite(&cab, sizeof(CabecalhoPlaylists), 1, arq);
    fclose(arq);

    return 1;

}

int imprimirPlaylist(int codigo){
     FILE * arq = fopen("playlists.dat", "rb");
    if(arq == NULL){
        return 0;
    }

    CabecalhoPlaylists cab;
    Playlist p;

    fread(&cab, sizeof(CabecalhoPlaylists), 1, arq);
    int c = cab.cabeca;

    while(c != -1){
        fseek(arq, sizeof(CabecalhoPlaylists) + c * sizeof(Playlist), SEEK_SET);
        fread(&p, sizeof(Playlist), 1, arq);

        if(p.codigo == codigo){
            printf("\nCodigo: %d", p.codigo);
            printf("\nTitulo: %s\n", p.titulo);
            fclose(arq);
            return 1;
        }
        c = p.prox;
    }

    fclose(arq);
    return 0;
}



int listarPlaylists(){
    FILE *arq = fopen("playlists.dat", "rb");
    if(arq == NULL){
        return 0;
    }

    CabecalhoPlaylists cab;
    Playlist p;

    fread(&cab, sizeof(CabecalhoPlaylists), 1, arq);
    int c = cab.cabeca;

    if(c == -1){
        printf("\nNenhuma playlist cadastrada.\n");
        fclose(arq);
        return 1;
    }

    printf("\n------- PLAYLISTS -------");
    while(c != -1){
        fseek(arq, sizeof(CabecalhoPlaylists) + c * sizeof(Playlist), SEEK_SET);
        fread(&p, sizeof(Playlist), 1, arq);

        printf("\n[%d] %s", p.codigo, p.titulo);
        
        c = p.prox;
    }
    printf("\n-------------------------\n");

    fclose(arq);
    return 1;
}

int buscarPlaylist(int codigo, Playlist *playlist, int *posicao) {
    FILE * arq = fopen("playlists.dat", "rb");
    if (arq == NULL) return 0;

    CabecalhoPlaylists cab;
    Playlist p;
    fread(&cab, sizeof(CabecalhoPlaylists), 1, arq);
    int c = cab.cabeca;

    while (c != -1) {
        fseek(arq, sizeof(CabecalhoPlaylists) + c * sizeof(Playlist), SEEK_SET);
        fread(&p, sizeof(Playlist), 1, arq);

        if (p.codigo == codigo) {
            if (playlist != NULL) *playlist = p;
            if (posicao != NULL) *posicao = c;
            fclose(arq);
            return 1; 
        }
        c = p.prox;
    }
    fclose(arq);
    return 0; 
}

int existePlaylist(int codigo) {
    return buscarPlaylist(codigo, NULL, NULL)==1;
}