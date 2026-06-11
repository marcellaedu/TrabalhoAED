#ifndef FAIXAS_H
#define FAIXAS_H

typedef struct{
    int topo;
    int livres;
} CabecalhoFaixas;

typedef struct{
    int codMusica;
    int prox;
} Faixa;


// Inicializa o arquivo de faixas
// Entrada: nenhuma
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: arquivo de faixas é criado caso não exista
void inicializarArquivoFaixas();


// Insere uma música no início de uma playlist
// Entrada: código da playlist e código da música
// Retorno: 1 se a inserção for realizada e 0 caso contrário
// Pré-condição: playlist e música devem existir
// Pós-condição: música é inserida no início da playlist
int inserirInicioPlaylist(int codPlaylist, int codMusica);


// Insere uma música no final de uma playlist
// Entrada: código da playlist e código da música
// Retorno: 1 se a inserção for realizada e 0 caso contrário
// Pré-condição: playlist e música devem existir
// Pós-condição: música é inserida no final da playlist
int inserirFimPlaylist(int codPlaylist, int codMusica);


// Remove uma música de uma playlist
// Entrada: código da playlist e código da música
// Retorno: 1 se a remoção for realizada e 0 caso contrário
// Pré-condição: playlist e música devem existir
// Pós-condição: música é removida da playlist
int removerMusicaPlaylist(int codPlaylist, int codMusica);


// Imprime todas as músicas de uma playlist
// Entrada: código da playlist
// Retorno: nenhum
// Pré-condição: playlist deve existir
// Pós-condição: músicas da playlist são exibidas na tela
void imprimirMusicasPlaylist(int codPlaylist);


// Imprime a lista de nós livres
// Entrada: nenhuma
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: posições livres são exibidas na tela
void imprimirNosLivres();

#endif