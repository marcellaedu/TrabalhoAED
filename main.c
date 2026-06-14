#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "musicas.h"

int main() {
    inicializarArquivoMusicas();

    int opcao;
    int cod, ano, resultado;
    char titulo[TAM1];
    char artista[TAM2];

    do {
        printf("\n======= MENU ACERVO =======");
        printf("\n1. Cadastrar Musica");
        printf("\n2. Listar Todo o Acervo");
        printf("\n3. Pesquisar Musica por Codigo");
        printf("\n4. Sair");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); 

        switch(opcao) {
            case 1:
                printf("\n--- Cadastrar Nova Musica ---");
                printf("\nDigite o codigo (inteiro): ");
                scanf("%d", &cod);
                getchar();

                printf("Digite o titulo: ");
                fgets(titulo, TAM1, stdin);
                titulo[strcspn(titulo, "\n")] = '\0'; // Remove o '\n' do final

                printf("Digite o artista/banda: ");
                fgets(artista, TAM2, stdin);
                artista[strcspn(artista, "\n")] = '\0';

                printf("Digite o ano de lancamento: ");
                scanf("%d", &ano);

                resultado = cadastrarMusica(cod, titulo, artista, ano);
                if (resultado == 1) {
                    printf("\n[Sucesso] Musica cadastrada com sucesso!\n");
                } else {
                    printf("\n[Erro] Nao foi possivel cadastrar. O codigo ja existe ou houve erro no arquivo.\n");
                }
                break;

            case 2:
                listarAcervo();
                break;

            case 3:
                printf("\n--- Pesquisar Musica ---");
                printf("Digite o codigo da musica: ");
                scanf("%d", &cod);

                resultado = imprimirMusica(cod);
                if (resultado == 0) {
                    printf("\n[Aviso] Musica com o codigo %d nao foi encontrada.\n", cod);
                }
                break;

            case 4:
                printf("\nSaindo do programa. Ate logo!\n");
                break;

            default:
                printf("\n[Erro] Opcao invalida. Tente novamente.\n");
        }

    } while(opcao != 4);

    return 0;
}