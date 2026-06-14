#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "musicas.h"

void inicializarArquivoMusicas(){
     FILE *arq = fopen("musicas.dat", "rb");

    if(arq != NULL){
        fclose(arq);
        return;
    }

    arq = fopen("musicas.dat", "wb");

    if(arq == NULL){
        printf("\nErro ao criar arquivo musicas.dat. \n");
    }

    cabMusica cab;

    cab.cabeca = -1;
    cab.topo = 0;

    fwrite(&cab, sizeof(cabMusica), 1, arq);

    fclose(arq);
}

int cadastrarMusica(int cod, char titulo[], char artista[], int ano) {
    if (existeMusica(cod)) {
        return 0;
    }

    FILE *arq = fopen("musicas.dat", "rb+");
    if (arq == NULL) {
        return 0;
    }

    cabMusica cab;
    if (fread(&cab, sizeof(cabMusica), 1, arq) != 1) {
        fclose(arq);
        return 0;
    }

    musica novo;
    novo.codigo = cod;
    strcpy(novo.titulo, titulo);
    strcpy(novo.artista, artista);
    novo.ano = ano;
    novo.prox = -1;

    if (cab.cabeca == -1) {
        fseek(arq, sizeof(cabMusica) + cab.topo * sizeof(musica), SEEK_SET);
        fwrite(&novo, sizeof(musica), 1, arq);
        
        cab.cabeca = cab.topo;
    } else {
        int c = cab.cabeca;
        musica aux;

        fseek(arq, sizeof(cabMusica) + c * sizeof(musica), SEEK_SET);
        fread(&aux, sizeof(musica), 1, arq);

        while (aux.prox != -1) {
            c = aux.prox;
            fseek(arq, sizeof(cabMusica) + c * sizeof(musica), SEEK_SET);
            fread(&aux, sizeof(musica), 1, arq);
        }

        aux.prox = cab.topo;
        fseek(arq, sizeof(cabMusica) + c * sizeof(musica), SEEK_SET);
        fwrite(&aux, sizeof(musica), 1, arq);

        fseek(arq, sizeof(cabMusica) + cab.topo * sizeof(musica), SEEK_SET);
        fwrite(&novo, sizeof(musica), 1, arq);
    }

    cab.topo++;

    rewind(arq);
    fwrite(&cab, sizeof(cabMusica), 1, arq);
    fclose(arq);

    return 1;
}

int imprimirMusica(int cod){
    FILE * arq = fopen("musicas.dat", "rb");
    if(arq == NULL){
        return 0;
    }

    cabMusica cab;
    musica m;

    fread(&cab, sizeof(cabMusica), 1, arq);
    int c = cab.cabeca;

    while(c != -1){
        fseek(arq, sizeof(cabMusica) + c * sizeof(musica), SEEK_SET);
        fread(&m, sizeof(musica), 1, arq);

        if(m.codigo == cod){
            printf("\nCodigo: %d", m.codigo);
            printf("\nTitulo: %s", m.titulo);
            printf("\nArtista: %s", m.artista);
            printf("\nAno: %d\n", m.ano);
            fclose(arq);
            return 1;
        }
        c = m.prox;
    }

    fclose(arq);
    return 0;
}

int listarAcervo(){
    FILE *arq = fopen("musicas.dat", "rb");
    if(arq == NULL){
        return 0;
    }

    cabMusica cab;
    musica m;

    fread(&cab, sizeof(cabMusica), 1, arq);
    int c = cab.cabeca;

    if(c == -1){
        printf("\nAcervo vazio.\n");
        fclose(arq);
        return 1;
    }

    printf("\n--- ACERVO DE MUSICAS ---");
    while(c != -1){
        fseek(arq, sizeof(cabMusica) + c * sizeof(musica), SEEK_SET);
        fread(&m, sizeof(musica), 1, arq);

        printf("\n[%d] %s - %s (%d)", m.codigo, m.titulo, m.artista, m.ano);
        
        c = m.prox;
    }
    printf("\n-------------------------\n");

    fclose(arq);
    return 1;
}

int existeMusica(int cod){
    FILE * arq = fopen("musicas.dat", "rb");
    if(arq == NULL){
        return 0;
    }

    cabMusica cab;
    musica m;

    fread(&cab, sizeof(cabMusica), 1, arq);

    int c = cab.cabeca;

    while (c != -1){
        fseek(arq, sizeof(cabMusica) + c * sizeof(musica), SEEK_SET);
        fread(&m, sizeof(musica), 1, arq);

        if (m.codigo == cod){
            fclose(arq);
            return 1;
        }
        
        c = m.prox;
    }

    fclose(arq);
    return 0;
}