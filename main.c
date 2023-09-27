#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX 36 

void game(){

    //* Funções
    void resetGameTableValues(int gameTable[6][6]);
    void getUserInput(char *input);
    void drawInterface(int gameTable[6][6], int actualPeace, int *scores);
    void readScores(int matriz[6][6],int *scores);
    int moveTable(int table[6][6], char *input);
    int shuffleHouses(int *housesDeck, int size);
    int insetInTable(int matriz[6][6], char *commandInput, int peace, int round_0);

    //* Variaveis
    int actualPeace, size, newPeace, play, round_0;

    //* Ponteiros e atrelados
    int housesDeck[36] = {
        1, 2, 3, 4, 5, 6,
        1, 2, 3, 4, 5, 6,
        1, 2, 3, 4, 5, 6,
        1, 2, 3, 4, 5, 6,
        1, 2, 3, 4, 5, 6,
        1, 2, 3, 4, 5, 6
    };
    int *pHousesDeck = housesDeck;

    int scores[6] = { 0, 0, 0, 0, 0, 0 };
    int *pScores = scores;
    
    char UserInputCommand[100];
    char *pUserInputCommand = UserInputCommand;

    int gameTable[6][6];

    //* Execução
    play = 1;
    round_0 = 1;
    newPeace = 1;
    size = MAX;

    resetGameTableValues(gameTable);

    do{//* Ciclo do jogo - Fase de Expanção

        if(newPeace == 1 && size > 0){
            actualPeace = shuffleHouses(housesDeck, size);
            size--;
            newPeace = 0;
        }

        readScores(gameTable, pScores);

        drawInterface(gameTable, actualPeace, pScores);

        getUserInput(pUserInputCommand);

        //* Tratamento dos comandos
        if(strcmp(pUserInputCommand, "SAIR") == 0) break;
        
        if(moveTable(gameTable, pUserInputCommand) == 1) continue;

        int result = insetInTable(gameTable, pUserInputCommand, actualPeace, round_0);

        switch(result){
            case 0:
                printf("Comando invalido!");
                getchar();
                break;
            case 1:
                printf("Este territorio já foi ocupado!");
                getchar();
                break;
            case 2:
                printf("Você deve posicionar a nova peça adjacente a uma já existente");
                getchar();
                break;
            case 3:
                newPeace = 1;
                round_0 = 0;
                break;
        }
    }while(play == 1);
}

void resetGameTableValues(int gameTable[6][6]){
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            gameTable[i][j] = 0;
        }
    }
    return;
}

void getUserInput(char *pTextCommand){
    int count = 0;
    char ch;

    do{
        ch = getchar();

        if(ch >= 97 && ch <= 122) ch -= 32;

        pTextCommand[count] = ch;

        count++;
    }while(ch != '\n');

    pTextCommand[count-1] = '\0';

    return;
}

int moveTable(int table[6][6], char *input){
    int c = 0;

    if(strcmp(input, "MVD") == 0){
        for(c; c < 6; c++){ if(table[c][5] > 0)break; }

        if(c == 6){   
            for(int i = 0; i <= 5; i++){
                for(int j = 5; j >= 0; j--){
                    if(j == 0){
                        table[i][j] = 0;
                    }else{
                        table[i][j] = table[i][j-1];
                    }
                }
            }
        }else{
            printf("Não é possivel mover para está direção...");
            getchar();
        }
        
    }else if(strcmp(input, "MVE")  == 0){
        for(c; c < 6; c++){ if(table[c][0] > 0)break; }

        if(c == 6){   
            for(int i = 0; i <= 5; i++){
                for(int j = 0; j <= 5; j++){
                    if(j == 5){
                        table[i][j] = 0;
                    }else{
                        table[i][j] = table[i][j+1];
                    }
                }
            }
        }else{
            printf("Não é possivel mover para está direção...");
            getchar();
        }

    }else if(strcmp(input, "MVC")  == 0){
        for(c; c < 6; c++){ if(table[0][c] > 0)break; }

        if(c == 6){   
            for(int i = 0; i <= 5; i++){
                for(int j = 0; j <= 5; j++){
                    if(i == 5){
                        table[i][j] = 0;
                    }else{
                        table[i][j] = table[i+1][j];
                    }
                }
            }
        }else{
            printf("Não é possivel mover para está direção...");
            getchar();
        }

    }else if(strcmp(input, "MVB")  == 0){
        for(c; c < 6; c++){ if(table[5][c] > 0)break; }

        if(c == 6){   
            for(int i = 5; i >= 0; i--){
                for(int j = 0; j <= 5; j++){
                    if(i == 0){
                        table[i][j] = 0;
                    }else{
                        table[i][j] = table[i-1][j];
                    }
                }
            }
        }else{
            printf("Não é possivel mover para está direção...");
            getchar();
        }
    }else {
        return 0;
    }

    return 1;
}

int insetInTable(int matriz[6][6], char *commandInput, int peace, int round_0){
    
    int i = commandInput[0] - 65;
    int j = commandInput[1] - '1';
    
    //* Comando invalido
    if(i < 0 || i > 5 || j < 0 || j > 5) return 0;

    //* Posição ocupada
    if(matriz[i][j] != 0) return 1;

    if(round_0 == 1){
        matriz[i][j] = peace;
        return 3; //* Posicionamento feito
    }

    //* preencher matriz
    if(i > 0 && matriz[i - 1][j] > 0){
        matriz[i][j] = peace;
        return 3;
    }else if(i < 5 && matriz[i + 1][j] > 0){
        matriz[i][j] = peace;
        return 3;
    }else if(j > 0 && matriz[i][j - 1] > 0){
        matriz[i][j] = peace;
        return 3;
    }else if(j < 5 && matriz[i][j + 1] > 0){
        matriz[i][j] = peace;
        return 3;
    }else {
        return 2; //* Posicionamento não adjacente
    }
}

void readScores(int matriz[6][6],int *scores){
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            if(i > 0 && i < 5 && j > 0 && j < 5 && matriz[i][j] > 0){
                scores[(matriz[i][j]-1)]++;
            }
        }
    }
    return;
}

void drawInterface(int gameTable[6][6], int actualPeace, int *scores){

    char houses[6][9] = {
        "Drave   \0",
        "Halvern \0",
        "Bearth  \0",
        "Gantis  \0",
        "Na'Ghar \0",
        "Avondale\0"
    };

    system("clear");

    printf("===========  REGICIDA  =========== Proxima Peça:\n");
    printf(
        "   |  1 |  2 |  3 |  4 |  5 |  6 | \033[0;1;3%dm %d - %s\033[0;0m\n",
        actualPeace,
        actualPeace,
        houses[actualPeace -1]
    );
    printf("================================== PONTUAÇOES\n");


    for(int i = 0; i < 6; i++){

        printf(" %c | ", (i+65));

        for(int j = 0; j < 6; j++){
            printf("\033[0;1;3%dm", gameTable[i][j]); // muda para a cor da casa
            printf("0%d ", gameTable[i][j]); // pinta o numero da casa
            printf("\033[0;0m| "); // reseta para a cor padrão
        }

        printf("%d - \033[0;1;3%dm%s  %d Pontos\033[0;0m\n", i+1, i+1, houses[i], scores[i]);
    }

    printf("\nSeu proximo movimento sera: ");
}

int shuffleHouses(int *housesDeck, int size){

    srand(time(NULL)); //* Inicia o gerador pseudo-aleatorio

    int index = rand() % size;

    int selected = housesDeck[index];

    for(index; index < size - 1; index++){
        housesDeck[index] = housesDeck[index + 1];
    }

    return selected;
}
