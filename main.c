#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "musicas.h"
#include "playlists.h"
#include "faixas.h"
#include "arquivo.h"
#include <locale.h>

int main() {
    inicializarArquivoMusicas();
    inicializarArquivoPlaylists();
    inicializarArquivoFaixas();

    int opcao;
    int codMusica, codPlaylist, ano, resultado;
    char titulo[TAM1];
    char artista[TAM2];
    char nomeArqTxt[100];
    

    do {
        printf("\n=================== MENU ===================\n");
        printf("1. Cadastrar Musica\n");
        printf("2. Listar Todo o Acervo\n");
        printf("3. Pesquisar Musica por Codigo\n");
        printf("4. Cadastrar Playlist\n");
        printf("5. Listar Todas as Playlists\n");
        printf("6. Pesquisar Playlist por Codigo\n");
        printf("7. Inserir Musica no Inicio da Playlist\n");
        printf("8. Inserir Musica no Fim da Playlist\n");
        printf("9. Remover Musica de uma Playlist\n");
        printf("10. Imprimir Musicas de uma Playlist\n");
        printf("11. Imprimir Nos Livres\n");
        printf("12. Carregar arquivo \n");
        printf("13. Sair\n");
        printf("\n=============================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); 

        switch(opcao) {
            case 1:
                printf("\n--- Nova Musica ---");
                printf("\nDigite o codigo da musica (inteiro): ");
                scanf("%d", &codMusica);
                getchar();

                printf("Digite o titulo: ");
                fgets(titulo, TAM1, stdin);
                titulo[strcspn(titulo, "\n")] = '\0'; 

                printf("Digite o artista/banda: ");
                fgets(artista, TAM2, stdin);
                artista[strcspn(artista, "\n")] = '\0';

                printf("Digite o ano de lancamento: ");
                scanf("%d", &ano);

                resultado = cadastrarMusica(codMusica, titulo, artista, ano);
                if (resultado == 1) {
                    printf("\nSucesso: Musica %s foi cadastrada \n", titulo);
                } else {
                    printf("\nErro: Nao foi possivel cadastrar. O codigo ja existe ou houve erro no arquivo.\n");
                }
                break;

            case 2:
                listarAcervo();
                break;

            case 3:
                printf("Digite o codigo da musica: ");
                scanf("%d", &codMusica);

                resultado = imprimirMusica(codMusica);
                if (resultado == 0) {
                    printf("\nAviso: Musica com o codigo %d nao foi encontrada.\n", codMusica);
                }
                break;

            case 4:
                printf("\n--- Nova Playlist ---");
                printf("\nDigite o codigo da playlist (inteiro): ");
                scanf("%d", &codPlaylist);
                getchar();

                printf("Digite o titulo: ");
                fgets(titulo, TAM1, stdin);
                titulo[strcspn(titulo, "\n")] = '\0';

                resultado = criarPlaylist(codPlaylist, titulo);
                if (resultado == 1) {
                    printf("\nSucesso: Playlist %s foi cadastrada !\n", titulo);
                } else {
                    printf("\nErro: Nao foi possivel cadastrar. O codigo ja existe ou houve erro no arquivo.\n");
                }
                break;
            
            case 5:
                listarPlaylists();
                break;
            
            case 6:
                printf("Digite o codigo da playlist: ");
                scanf("%d", &codPlaylist);

                resultado = imprimirPlaylist(codPlaylist);
                if (resultado == 0) {
                    printf("\nAviso: Playlist com o codigo %d nao foi encontrada.\n", codPlaylist);
                }
                break;

            case 7:
                printf("\n--- Inserir Musica no Inicio da Playlist ---\n");
                printf("Digite o codigo da playlist: ");
                scanf("%d", &codPlaylist);
                printf("Digite o codigo da musica: ");
                scanf("%d", &codMusica);
                getchar();

                resultado = inserirInicioPlaylist(codPlaylist, codMusica);
                if (resultado) {
                    printf("\nSucesso: Musica com o codigo %d foi inserida no inicio da playlist com codigo %d", codMusica, codPlaylist);
                } else {
                    printf("\nErro: Falha ao inserir musica (Playlist ou Musica nao encontrada).\n");
                }
                break;
                
            case 8:
                printf("\n--- Inserir Musica no Fim da Playlist ---\n");
                printf("Digite o codigo da playlist: ");
                scanf("%d", &codPlaylist);
                printf("Digite o codigo da musica: ");
                scanf("%d", &codMusica);
                getchar();
                
                resultado = inserirFimPlaylist(codPlaylist, codMusica);
                if (resultado) {
                    printf("\nSucesso: Musica com o codigo %d foi inserida no fim da playlist com codigo %d", codMusica, codPlaylist);
                } else {
                    printf("\nErro: Falha ao inserir musica (Playlist ou Musica nao encontrada).\n");
                }
                break;
            
            case 9:
                printf("Digite o codigo da playlist na qual a musica pertence: ");
                scanf("%d", &codPlaylist);
                printf("Digite o codigo da musica a ser removida: ");
                scanf("%d", &codMusica);
                getchar();
                
                resultado = removerMusicaPlaylist(codPlaylist, codMusica);
                if (resultado) {
                    printf("\nSucesso: Musica com o codigo %d foi removida da playlist com codigo %d", codMusica, codPlaylist);
                } else {
                    printf("\nErro: Falha na remocao (Musica ou Playlist nao encontradas).\n");
                }
                break;
                
            case 10:
                printf("Digite o codigo da playlist: ");
                scanf("%d", &codPlaylist);
                getchar();
                
                imprimirMusicasPlaylist(codPlaylist);
                break;

            case 11:
                imprimirNosLivres();
                break;

            case 12:
                printf("Digite o nome do arquivo texto (ex: arquivo.txt): ");
                scanf("%s", nomeArqTxt);
                carregarArquivo(nomeArqTxt);
                break;

            case 13:
                printf("Programa finalizado.\n");
                break;

            default:
                printf("\nErro: Opcao invalida! Tente novamente.\n");
        }

    } while(opcao != 13);

    return 0;
}