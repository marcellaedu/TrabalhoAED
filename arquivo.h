#ifndef ARQUIVO_H
#define ARQUIVO_H

// Remove os espaços em branco do início e do fim de uma string
// Entrada: ponteiro para a string (char *)
// Retorno: nenhum
// Pré-condição: a string deve estar devidamente alocada e terminada em '\0'
// Pós-condição: os espaços inúteis das pontas são eliminados diretamente na memória
void removerEspaco(char *s);

// Carrega e processa todas as operações de um arquivo de lote
// Entrada: nome do arquivo
// Retorno: nenhum
// Pré-condição: o arquivo deve existir e estar acessível
// Pós-condição: todas as operações do arquivo são executadas e um relatório é exibido
void carregarArquivo(const char *nomeArqTxt);

// Insere uma música a partir de uma linha do arquivo
// Entrada: ponteiro para a linha contendo os dados da música
// Retorno: 1 em caso de sucesso, 0 em caso de erro
// Pré-condição: a linha deve estar no formato "M;codigo;titulo;artista;ano"
// Pós-condição: a música é cadastrada no sistema
int inserirMusica(char *linha);

// Insere uma playlist a partir de uma linha do arquivo
// Entrada: ponteiro para a linha (char *) contendo os dados da playlist
// Retorno: 1 em caso de sucesso, 0 em caso de erro
// Pré-condição: a linha deve estar no formato "P;codigo;titulo"
// Pós-condição: a playlist é cadastrada no sistema
int inserirPlaylist(char *linha);

// Insere uma faixa em uma playlist a partir de uma linha do arquivo
// Entrada: ponteiro para a linha (char *) contendo os dados da faixa
// Retorno: 1 em caso de sucesso, 0 em caso de erro
// Pré-condição: a linha deve estar no formato "I;tipo;codPlaylist;codMusica"
// Pós-condição: a música é inserida na playlist (início ou fim conforme tipo)
int inserirFaixas(char *linha);

// Remove uma música de uma playlist a partir de uma linha do arquivo
// Entrada: ponteiro para a linha (char *) contendo os dados da remoção
// Retorno: 1 em caso de sucesso, 0 em caso de erro
// Pré-condição: a linha deve estar no formato "R;codPlaylist;codMusica"
// Pós-condição: a música é removida da playlist (se existir)
int remover(char *linha);



#endif // ARQUIVO_H