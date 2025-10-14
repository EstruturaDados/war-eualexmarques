#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_MISSAO 100
#define MAX_TERRITORIOS 5

struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};
//Cadastro dos territorios
void cadastrarTerritorios(struct Territorio *mapas, int total){
    for (int i = 0; i < total; i++){
        printf("\nCadastrando território n°%i\n", i + 1);
        printf("Nome do território: ");
        fgets(mapas[i].nome, sizeof(mapas[i].nome), stdin);
        mapas[i].nome[strcspn(mapas[i].nome, "\n")] = 0;

        printf("Cor do exército (ex: vermelho, amarelo, etc...): ");
        fgets(mapas[i].cor, sizeof(mapas[i].cor), stdin);
        mapas[i].cor[strcspn(mapas[i].cor, "\n")] = 0;

        printf("Número de tropas: ");
        scanf("%i", &mapas[i].tropas);
        getchar();
    }
    
}
//Mostrar o estado atual dos terririos
void mostrarTerritorios(struct Territorio *mapas, int cartas) {
    printf("\nEstado atual dos territorios!\n");
    for (int id = 0; id < cartas; id++) {
        printf("n°%i. %s          (Exército %s, Tropas: %i)\n", id + 1, mapas[id].nome, mapas[id].cor, mapas[id].tropas);
    }
}
//Atribuindo missão para o jogador
void atribuirMissao(char *destino, char *missoes[], int totalMissoes){
    int sorteio = rand() % totalMissoes;
    strcpy(destino, missoes[sorteio]);
}
//Escolhendo quem ira atacacar e defender
void atacar(struct Territorio *mapas, int total, char *missaoJogador){
    int atacante = -1, defensor = -1;

            do {
                printf("Escolha o território que irá atacar (1 a 5): ");
                scanf("%d", &atacante);
                getchar();
                if (atacante < 1 || atacante > total || mapas[atacante - 1].tropas <= 0) {
                    printf("Território inválido ou sem tropas!\n");
                    atacante = -1;
                }
            } while (atacante == -1);

            do {
                printf("Escolha o território que irá defender (1 a 5): ");
                scanf("%d", &defensor);
                getchar();
                if (defensor < 1 || defensor > total || defensor == atacante || mapas[defensor - 1].tropas <= 0) {
                    printf("Território inválido ou sem tropas!\n");
                    defensor = -1;
                }
            } while (defensor == -1);

            atacante -= 1;
            defensor -= 1;

            int dado_atacante = rand() % 6 + 1;
            int dado_defensor = rand() % 6 + 1;

            printf("\n-----Resultado da batalha-----\n");
            printf("O atacante %s rolou: %d\n", mapas[atacante].nome, dado_atacante);
            printf("O defensor %s rolou: %d\n", mapas[defensor].nome, dado_defensor);

            if (dado_atacante > dado_defensor) {
                printf("Vitória do atacante!\n");
                //Missão nova quem conseguir tirar 6 tira dois pontos do defensor
                int dano = (dado_atacante == 6) ? 2 : 1;
                mapas[defensor].tropas -= dano;

                printf("O defensor perdeu %d tropa(s).\n", dano);

                if (mapas[defensor].tropas <= 0) {
                    printf("O território %s foi conquistado!\n", mapas[defensor].nome);
                    strcpy(mapas[defensor].cor, mapas[atacante].cor);
                    mapas[defensor].tropas = 1;
                    mapas[atacante].tropas -= 1;
                }
            } else if (dado_atacante < dado_defensor) {
                printf("O defensor resistiu ao ataque!\n");
                mapas[atacante].tropas -= 1;
            } else{
                printf("Empate na batalha!\n");
            }
            // Verificação da nova missão: dois territórios com tropas igual a zero
            int territoriosZerados = 0;
            for (int i = 0; i < MAX_TERRITORIOS; i++) {
            if (mapas[i].tropas == 0) {
             territoriosZerados++;
            }
            }
            int fimdeJogo =0;
            if (territoriosZerados >= 4) {
             printf("\n Missão especial cumprida: existem %d territórios com tropas zeradas.\n", territoriosZerados);
                printf(" Fim de jogo! Essa condição encerra a partida.\n");
                fimdeJogo =1;
            }
            
}
//5 Missoes que seram sorteadas
int verificarMissao(char *missao, struct Territorio *mapas, int cartas, char *corJogador) {
    if (strcmp(missao, "eliminar todos os territorios vermelhos") == 0) {
        int territoriosVermelhos = 0;
        for (int i = 0; i < cartas; i++) {
            if (strcmp(mapas[i].cor, "vermelho") == 0 && mapas[i].tropas > 0) {
                territoriosVermelhos++;
            }
        }
        if (territoriosVermelhos == 0) {
            printf("\nParabéns! Você completou a missão: %s!\n", missao);
        } else {
            printf("\nMissão ainda não concluída. Restam %d território(s) vermelho(s) com tropas.\n", territoriosVermelhos);
        }
    } else if (strcmp(missao, "conquistar dois territorios") == 0) {
    int conquistados = 0;
    for (int i = 0; i < cartas; i++) {
        if (strcmp(mapas[i].cor, corJogador) == 0) {
            conquistados++;
        }
    }
    if (conquistados >= 2) {
        printf("\nMissão concluída: %s\n", missao);
    } else {
        printf("\nMissão pendente. Você possui apenas %d território(s) conquistado(s).\n", conquistados);
    }
}
    else if (strcmp(missao, "se quatro territorios chegarem a 0 acaba") == 0){
        int territorioszero = 0;
        for (int i = 0; i < cartas; i++) {
        if (mapas[i].tropas == 0) {
            territorioszero++;
        }
    }
    if (territorioszero >= 4) {
        printf("\nParabéns! Você completou a missão: %s!\n", missao);
        return 1;
    } else {
        printf("\nMissão ainda não concluída. Existem apenas %d território(s) com tropas zeradas.\n", territorioszero);
        return 0;
        }
  
    } if (strcmp(missao, "eliminar todos os territorios amarelos") == 0) {
        int territoriosAmarelos = 0;
        for (int i = 0; i < cartas; i++) {
            if (strcmp(mapas[i].cor, "amarelo") == 0 && mapas[i].tropas > 0) {
                territoriosAmarelos++;
            }
        }
        if (territoriosAmarelos == 0) {
            printf("\nParabéns! Você completou a missão: %s!\n", missao);
        } else {
            printf("\nMissão ainda não concluída. Restam %d território(s) amarelas(s) com tropas.\n", territoriosAmarelos);
        }
    
    } else if (strcmp(missao, "quem tirar 6 tira dois pontos do defensor") == 0) {
        printf("\nEssa missão é ativada automaticamente durante o ataque.\n");
        printf("Se o atacante tirar 6 no dado, o defensor perde 2 tropas em vez de 1.\n");
        printf("Continue atacando e torça por um 6!\n");
    }
    else{
        printf("\nMissão desconhecida ou não implementada.\n");
    }
    
}

int main() {
    srand(time(NULL));

    struct Territorio *mapas = (struct Territorio *) calloc(MAX_TERRITORIOS, sizeof(struct Territorio));
    if (mapas == NULL){
        printf("Erro ao alocar memoria\n");
        return 1;
    }
    

    // Vetor de missões
    char *missoes[] = {
        "eliminar todos os territorios vermelhos",
        "conquistar dois territorios",
        "se quatro territorios chegarem a 0 acaba",
        "eliminar todos os territorios amarelos",
        "quem tira 6 tira dois pontos do defensor"
    };
    int totalMissoes = 5;

    
    char *missaoJogador = (char *)malloc(MAX_MISSAO * sizeof(char));
    if (missaoJogador == NULL) {
        printf("Erro ao alocar memória para missão!\n");
        free (mapas);
        return 1;
    }
    
    char corJogador[20];
    printf("   ======================================\n");
    printf("    Bem-vindo ao jogo ****WAR CITIES****\n");
    printf("   ======================================\n");
    printf("\nFaça o cadastro de 5 territórios\n");

    
    printf("\nCadastrando território \n");
    cadastrarTerritorios(mapas, MAX_TERRITORIOS);

    printf("\nCadastro dos territórios concluído!\n");

    atribuirMissao(missaoJogador, missoes, totalMissoes);
    printf("\nSua missão é: %s\n", missaoJogador);

    printf("\nDigite a cor do seu exército: ");
    fgets(corJogador, sizeof(corJogador), stdin);
    corJogador[strcspn(corJogador, "\n")] = 0;

   int opcao;
    int fimdeJogo = 0;
    do {
        printf("\n1 - Atacar\n");
        printf("2 - Verificar missão\n");
        printf("0 - Sair\n");
        printf("Escolha a opção: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            atacar(mapas, MAX_TERRITORIOS, missaoJogador);
            mostrarTerritorios(mapas, MAX_TERRITORIOS);
             if (fimdeJogo) break;
            // Verificação da missão
        }else  if (opcao == 2) {
                verificarMissao(missaoJogador, mapas, MAX_TERRITORIOS, corJogador);
        }
        

    } while (opcao != 0);

    printf("\n-----Estado final dos territórios-----\n");
    mostrarTerritorios(mapas, MAX_TERRITORIOS);

    free(mapas);
    free(missaoJogador);
    return 0;
}