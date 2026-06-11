#ifndef MUSICAS_H
#define MUSICAS_H

#define TAM 51

typedef struct {
    int cabeca;
    int topo;
} CabMusicas;

typedef struct{
    int codigo;
    char titulo[TAM]; 
    char artista[TAM];
    int ano;
    int prox;
} musica;

// Inicializa o arquivo de músicas
// Entrada: nenhuma
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: arquivo de músicas é criado caso não exista
void inicializarArquivoMusicas();


// Cadastra uma música no acervo
// Entrada: código, título, artista e ano da música
// Retorno: 1 se a inserção for realizada e 0 caso contrário
// Pré-condição: código da música não deve existir no acervo
// Pós-condição: música é inserida no acervo
int cadastrarMusica(int codigo, char titulo[], char artista[], int ano);


// Busca uma música pelo código
// Entrada: código da música
// Retorno: posição da música no arquivo ou -1 caso não exista
// Pré-condição: nenhuma
// Pós-condição: nenhuma
int buscarMusica(int codigo);


// Imprime os dados de uma música
// Entrada: código da música
// Retorno: nenhum
// Pré-condição: música deve existir no acervo
// Pós-condição: dados da música são exibidos na tela
void imprimirMusica(int codigo);


// Lista todas as músicas cadastradas
// Entrada: nenhuma
// Retorno: nenhum
// Pré-condição: nenhuma
// Pós-condição: músicas cadastradas são exibidas na tela
void listarAcervo();

#endif