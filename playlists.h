#ifndef PLAYLISTS_H
#define PLAYLISTS_H

#define TAM 51

typedef struct{
    int cabeca;
    int topo;
} CabecalhoPlaylists;

typedef struct{
    int codigo;
    char titulo[TAM];
    int inicioFaixas;
    int fimFaixas;
    int prox;
} Playlist;


// Inicializa o arquivo de playlists
// Entrada: nenhuma
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: arquivo de playlists é criado caso não exista
void inicializarArquivoPlaylists();


// Cria uma nova playlist
// Entrada: código e título da playlist
// Retorno: 1 se a criação for realizada e 0 caso contrário
// Pré-condição: código da playlist não deve existir
// Pós-condição: playlist é inserida na lista de playlists
int criarPlaylist(int codigo, char titulo[]);


// Busca uma playlist pelo código
// Entrada: código da playlist
// Retorno: posição da playlist no arquivo ou -1 caso não exista
// Pré-condição: nenhuma
// Pós-condição: nenhuma
int buscarPlaylist(int codigo);


// Imprime os dados de uma playlist
// Entrada: código da playlist
// Retorno: nenhum
// Pré-condição: playlist deve existir
// Pós-condição: dados da playlist são exibidos na tela
void imprimirPlaylist(int codigo);


// Lista todas as playlists cadastradas
// Entrada: nenhuma
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: playlists cadastradas são exibidas na tela
void listarPlaylists();

#endif