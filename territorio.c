#include <stdio.h>
#include <string.h>

//Definição da estrutura (Struct)
struct Territorio
{
    char nome [30];
    char cor [10];
    int tropas;
};

//Função principal 
int main() {

    int cartas = 5;
    struct Territorio mapas[5];
    //Exibindo a tela inicial
    printf("   ======================================\n");
    printf("    Bem vindo ao jogo ****WAR CITIES****\n");
    printf("   ======================================\n");
    printf("\nFaça o cadastro de 5 territorios\n");
    //Lendo os dados dos territorios
    for (int id = 0; id < cartas; id++)
    {
        printf("\nCadastrando territorio n°%i\n",id +1);
        printf("Nome do territorio: ");
        fgets(mapas[id].nome, sizeof(mapas[id].nome), stdin);//Usanod (Sizeof) para que o (Fgets) saiba o limite de caracteris
        mapas[id].nome[strcspn(mapas[id].nome, "\n")]=0;//Remover o '\n'
        
        printf("Cor do exercito (ex: vermelho, amarelo, etc...): ");
        fgets(mapas[id].cor,  sizeof(mapas[id].cor), stdin);//Usanod (Sizeof) para que o (Fgets) saiba o limite de caracteris
        mapas[id].cor[strcspn(mapas[id].cor, "\n")]=0;//Remover o '\n'

        printf("Número de tropas: ");
        scanf("%i", &mapas[id].tropas);
        getchar();// Limpar o '\n' deixando pelo scanf
    }
    printf("\nCadastro dos territorios concluidos!!\n\n");
    printf("\nAgora iremos visualizar os territorios cadastrados\n\n");
    //Exibindo os territorios
    for (int id = 0; id < cartas; id++)
    {
        printf("territorio n°%i\n", id + 1);
        printf("Nome: %s\n", mapas[id].nome);
        printf("Cor do exercito: %s\n", mapas[id].cor);
        printf("Tropas: %i\n\n", mapas[id].tropas);
    }
    
    
    

}