#include <stdio.h>
#include <string.h>
#include <time.h>


struct Territorio
{
    char nome [30];
    char cor [10];
    int tropas;
};

void mostrarTerritorios(struct Territorio *mapas, int cartas){
    printf("\nEstado atual dos territorios!\n");
    for (int id = 0; id < cartas; id++)
    {
        printf("n°%i. %s(Exercito %s, Tropas:%i)\n", id + 1, mapas[id].nome, mapas[id].cor, mapas[id].tropas);
    }
    
}


int main() {
    char continuar;
    int cartas = 5;
    struct Territorio *mapas = (struct Territorio *) calloc(cartas, sizeof(struct Territorio));
    if (mapas == NULL)
    {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }
    srand(time(NULL));//Iniciando os valores do dado

    printf("   ======================================\n");
    printf("    Bem vindo ao jogo ****WAR CITIES****\n");
    printf("   ======================================\n");
    printf("\nFaça o cadastro de 5 territorios\n");
    
    for (int id = 0; id < cartas; id++)
    {
        printf("\nCadastrando territorio n°%i\n",id +1);
        printf("Nome do territorio: ");
        fgets(mapas[id].nome, sizeof(mapas[id].nome), stdin);
        mapas[id].nome[strcspn(mapas[id].nome, "\n")]=0;
        
        printf("Cor do exercito (ex: vermelho, amarelo, etc...): ");
        fgets(mapas[id].cor,  sizeof(mapas[id].cor), stdin);
        mapas[id].cor[strcspn(mapas[id].cor, "\n")]=0;

        printf("Número de tropas: ");
        scanf("%i", &mapas[id].tropas);
        getchar(); 
    }
    printf("\nCadastro dos territorios concluidos!!\n\n");
    
    do
    {
        printf("\nAgora vamos batalhar!\n\n");
        int atacante = -1, defensor = -1;
        //Esolhendo o territorio que ira atacar
        do
        {
            printf("Escolha o territorio que irá atacar (1 a 5): ");
            scanf("%d", &atacante);
            getchar();
            if (atacante < 1 || atacante > cartas)
            {
                printf("Número invalido!\n");
                atacante = -1;
            }else if (mapas[atacante - 1].tropas <= 0)
            {
                printf("O territorio atacante não possui tropas o suficiente!\n");
                atacante = -1;
            }
            
        } while (atacante == -1);
        //Escolhendo o territorio que ira defender
        do
        {
            printf("Escolha o territorio que irá defender (1 a 5): ");
            scanf("%d", &defensor);
            getchar();
            if (defensor < 1 || defensor > cartas)
            {
                printf("Número invalido!\n");
                defensor = -1;
            }else if (defensor == atacante){
                printf("O territorio defensor não pode ser o mesmo que o atacante!\n");
                defensor = -1;
            }else if (mapas[defensor - 1].tropas <= 0){
                printf("O territorio defensor não possui tropas o suficiente!\n");
                defensor = -1;
            }
            
        } while (defensor == -1);
        //Ajuste para indice de array
        atacante -= 1;
        defensor -= 1;
        //Valor dos dados 
        int dado_atacante = (rand() %5) + 1;
        int dado_defensor = (rand() %5) + 1;

        printf("\n-----Resultado da batalha-----\n");
        printf("O atacante %s rolou o dado e tirou; %d\n", mapas[atacante].nome, dado_atacante);
        printf("O defensor %s rolou o dado e tirou; %d\n", mapas[defensor].nome, dado_defensor);

        if (dado_atacante > dado_defensor)
        {
            printf("Vitoria do atacante!\n");
            mapas[defensor].tropas -=1;

            if (mapas[defensor].tropas <=0)
            {
                printf("O territorio %s perdeu todas as tropas!\n", mapas[defensor].nome);
                printf("Ele sera agora conquistado por %s\n", mapas[atacante].nome);
                //Tranferencia de dominio 
                strcpy(mapas[defensor].cor, mapas[atacante].cor);
                mapas[defensor].tropas = 1;

                printf("Conquista! o territorio agora pertence ao exercito %s com 1 tropa\n", mapas[defensor].cor);

            }
            
        }else if (dado_atacante < dado_defensor)
        {
            printf("O defensor resistiu ao ataque!\n");
        }else{
            printf("Os territorios empataram!\n");
        }
        //Mostrar estado atual apos a rodada
        mostrarTerritorios(mapas, cartas);

        printf("\nDeseja realizar outra rodada de ataque? (s/n):");
        scanf("%s", &continuar);        
        getchar();

    } while (continuar == 's');

    printf("-----Estado final dos territorios!----\n");
    mostrarTerritorios(mapas, cartas);
    
    free(mapas);
    return 0;

}