#ifndef MUSICAS_H
#define MUSICAS_H

#define TAM1 100
#define TAM2 50

typedef struct {
    int codigo;
    char titulo[TAM1];
    char artista[TAM2];
    int ano;
    int prox;
} musica;

typedef struct {
    int cabeca;
    int topo;
} cabMusica;

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
int cadastrarMusica(int cod, char titulo[], char artista[], int ano);

// Imprime os dados de uma música
// Entrada: código da música
// Retorno: 1 se encontrou, 0 se não
// Pré-condição: arquivo de musicas já foi aberto
// Pós-condição: mostra os dados na tela
int imprimirMusica(int cod);

// Lista todas as musicas do acervo
// Entrada: nenhuma
// Retorno: 1 se tem musicas, 0 se vazio
// Pré-condição: arquivo inicializado
// Pós-condição: lista tudo na tela
int listarAcervo();

// Verifica se uma musica existe pelo codigo
// Entrada: codigo da musica
// Retorno: 1 se existe, 0 se não
// Pré-condição: arquivo aberto
// Pós-condição: nenhuma
int existeMusica(int cod);

#endif