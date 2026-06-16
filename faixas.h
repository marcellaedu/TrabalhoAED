#ifndef FAIXAS_H
#define FAIXAS_H
#include "playlists.h"

typedef struct{
    int topo;
    int livres;
} CabecalhoFaixas;

typedef struct{
    int codMusica;
    int prox;
} Faixa;

// Grava uma faixa em uma posição específica do arquivo
// Entrada: ponteiro do arquivo aberto, ponteiro da faixa a salvar, posição 
// Retorno: nenhum
// Pré-condição: arquivo aberto  e posição válida
// Pós-condição: os dados da faixa são persistidos no arquivo na posição informada
void escreve_no(FILE* arq, Faixa* x, int pos);

// Lê uma faixa de uma posição específica do arquivo
// Entrada: ponteiro do arquivo aberto, posição, ponteiro onde guardar a faixa lida
// Retorno: nenhum
// Pré-condição: arquivo aberto em modo de leitura e ter uma posição existente e ponteiro de destino alocado
// Pós-condição: a faixa guardada em 'x' recebe os dados do arquivo
void le_no(FILE* arq, int pos, Faixa* x);

// Lê o cabeçalho do arquivo de faixas
// Entrada: ponteiro do arquivo aberto, ponteiro de destino da estrutura do cabeçalho
// Retorno: nenhum
// Pré-condição: arquivo aberto e ponteiro de destino alocado
// Pós-condição: o ponteiro 'cab' recebe o topo e a lista de livres do arquivo
void le_cabecalho(FILE* arq, CabecalhoFaixas* cab);

// Atualiza o cabeçalho no início do arquivo
// Entrada: ponteiro do arquivo aberto, ponteiro da estrutura do cabeçalho
// Retorno: nenhum
// Pré-condição: arquivo aberto para gravação e cabeçalho válido na memória
// Pós-condição: o cabeçalho no início do arquivo (posição 0) é atualizado
void escreve_cabecalho(FILE* arq, CabecalhoFaixas* cab);

// Atualiza uma playlist no arquivo playlists.dat
// Entrada: ponteiro para a playlist e posição da playlist no arquivo
// Retorno: nenhum
// Pré-condição: playlist existente e posição válida
// Pós-condição: os dados da playlist são atualizados no arquivo
void atualizarPlaylist(Playlist *p, int pos_playlist);

// Obtém uma posição disponível para inserção de uma nova faixa
// Entrada: ponteiro do arquivo de faixas e ponteiro para o cabeçalho
// Retorno: posição livre disponível
// Pré-condição: arquivo aberto e cabeçalho carregado em memória
// Pós-condição: a posição é removida da lista de livres ou obtida do topo
int obterPosicaoLivre(FILE *arq, CabecalhoFaixas *cab);

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