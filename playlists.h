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


// Imprime os dados de uma playlist
// Entrada: código da playlist
// Retorno: 1 se encontrou, 0 se não
// Pré-condição: playlist deve existir
// Pós-condição: dados da playlist são exibidos na tela
int imprimirPlaylist(int codigo);


// Lista todas as playlists cadastradas
// Entrada: nenhuma
// Retorno: 1 se tem playlist, 0 se vazio
// Pré-condição: arquivo inicializado
// Pós-condição: playlists cadastradas são exibidas na tela
int listarPlaylists();


// Busca uma playlist pelo código
// Entrada: código da playlist, ponteiro para playlist encontrada e ponteiro para posição encontrada
// Retorno: 1 se encontrar e 0 caso contrário
// Pré-condição: o arquivo de playlist deve existir
// Pós-condição: playlist e posição são preenchidas caso a playlist seja encontrada
int buscarPlaylist(int codigo, Playlist *playlist, int *posicao);

// Verifica se uma playlist existe pelo codigo
// Entrada: codigo da playlist
// Retorno: 1 se existe, 0 se não
// Pré-condição: arquivo aberto
// Pós-condição: nenhuma
int existePlaylist(int codigo);

#endif