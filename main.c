#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "./tool_box.h"

struct House {
    char name[9];
    int objective;
    int actualScore;
    int intriged;
    int revel;
};

struct Piece {
    int value;
    int intriged;
};

void game(int difficulty){
    
    //* Funções
    void getUserInput(char *input);
    void setupGame(struct House *houses);
    void resetStructTable(struct Piece **matriz);
    void choiceToRevel(struct House *houses, int difficulty);    
    void readStructScores(struct Piece **matriz, struct House *houses);
    void drawInterfaceWithStruct(struct Piece **matriz, int actualPiece, struct House *houses);
    void exchangeValues(struct Piece **pPieces, int i1, int j1, int i2, int j2, struct House *pHouses);
    int validateVictory(struct House *houses);
    int shuffleHouses(int *housesDeck, int size);
    int moveStructTable(struct Piece **matriz, char *input);
    int insetInStructTable(struct Piece **matriz, char *commandInput, int piece, int round_0);

    //* Variaveis
    int actualPiece, size, newPiece, play, round_0, intriga, victory;

    //* Ponteiros e atrelados
    struct Piece **pPieces = (struct Piece **)malloc(6 * sizeof(struct Piece *));
    for(int i = 0; i < 6; i++) {
        pPieces[i] = (struct Piece *)malloc(6 * sizeof(struct Piece));
    }

    int housesDeck[36] = {
        1, 2, 3, 4, 5, 6,
        1, 2, 3, 4, 5, 6,
        1, 2, 3, 4, 5, 6,
        1, 2, 3, 4, 5, 6,
        1, 2, 3, 4, 5, 6,
        1, 2, 3, 4, 5, 6
    };
    int *pHousesDeck = housesDeck;

    struct House houses[6];
    struct House *pHouses = houses;
    
    char UserInputCommand[100];
    char *pUserInputCommand = UserInputCommand;

    int gameTable[6][6];

    //* Execução
    play = 1;
    victory = 0;
    intriga = 0;
    round_0 = 1;
    newPiece = 1;
    size = 36;

    setupGame(pHouses);
    resetStructTable(pPieces);
    choiceToRevel(pHouses, difficulty);

    // for(int i = 0; i < 6; i++){
    //     for(int j = 0; j < 6; j++){
    //         actualPiece = shuffleHouses(housesDeck, size);
    //         size--;
    //         pPieces[i][j].value = actualPiece;
    //     }
    // }

    do{//* Ciclo do jogo - Fase de Expanção

        if(newPiece == 1 && size > 0){
            actualPiece = shuffleHouses(housesDeck, size);
            size--;
            newPiece = 0;
        }

        readStructScores(pPieces, pHouses);

        drawInterfaceWithStruct(pPieces, actualPiece, pHouses);

        getUserInput(pUserInputCommand);

        //* Tratamento dos comandos
        if(strcmp(pUserInputCommand, "SAIR") == 0) return;
        
        if(moveStructTable(pPieces, pUserInputCommand) == 1) continue;

        int result = insetInStructTable(pPieces, pUserInputCommand, actualPiece, round_0);

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
                newPiece = 1;
                round_0 = 0;
                if(size == 0) play = 0;
                break;
        }
    }while(play == 1);

    for(int i = 0; i < 6; i++){
        pHouses[i].revel = 1;
    }

    int control = 0;

    do{

        int i1 = 0;
        int j1 = 0;
        int i2 = 0;
        int j2 = 0;

        readStructScores(pPieces, pHouses);

        victory = validateVictory(pHouses);

        intriga = 0;

        for(int i = 0; i < 6; i++){
            if(pHouses[i].intriged == 1){
                intriga++;
            }
        }

        if(victory == 1 || intriga == 6){
            clearScreen();
            break;
        }

        drawInterfaceWithStruct(pPieces, actualPiece, pHouses);
        
        getUserInput(pUserInputCommand);

        if(control == 0){
            control = 1;
            printf("Fase de intriga Iniciada");
            getchar();
            continue;
        }

        if(strcmp(pUserInputCommand, "SAIR") == 0) return;
        
        i1 = pUserInputCommand[0] - 65;
        j1 = pUserInputCommand[1] - '1';
        i2 = pUserInputCommand[2] - 65;
        j2 = pUserInputCommand[3] - '1';

        //* Comando invalido
        if(i1 < 0 || i1 > 5 || j1 < 0 || j1 > 5) {
            printf("Primeira coordenada é invalida\n");
            getchar();
            continue;
        }else if(i2 < 0 || i2 > 5 || j2 < 0 || j2 > 5) {
            printf("Segunda coordenada é invalida\n");
            getchar();
            continue;
        }

        if(pPieces[i1][j1].intriged == 1 || pPieces[i2][j2].intriged == 1){
            printf("Uma dos territorios já fiz intriga\n");
            getchar();
            continue;
        }

        if(pHouses[pPieces[i1][j1].value - 1].intriged && pHouses[pPieces[i2][j2].value - 1].intriged){
            printf("As casas já fizeram intriga\n");
            getchar();
            continue;
        }

        if(i1 == i2 && (j1 - j2 == 1 || j1 - j2 == -1)){
            exchangeValues(pPieces, i1, j1, i2, j2, pHouses);

            getchar();
        }else if(j1 == j2 && (i1 - i2 == 1 || i1 - i2 == -1)){
            exchangeValues(pPieces, i1, j1, i2, j2, pHouses);
            getchar();
        }else{
            printf("Os territorios não são adjacentes");
            getchar();
        }
        
    }while(intriga < 6);

    if(victory == 1){
        printf("A guerra foi evitada com sucesso!");
        printf("Gloria ao tintereiro!");
    }else{
        printf("Você falhou em sua missão");
        printf("A guerra está entre nós");
    }
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

void setupGame(struct House *houses){

    int shuffleObjectives(int *objectivesDeck, int size);

    int objectivesDeck[6] = { 0, 1, 2, 3, 4, 6 };
    int *pObjectivesDeck = objectivesDeck;

    char houseNames[6][9] = {
        "Drave   \0",
        "Halvern \0",
        "Bearth  \0",
        "Gantis  \0",
        "Na'Ghar \0",
        "Avondale\0"
    };

    int size = 6;

    for(int i = 0; i < 6; i++){
        strcpy(houses[i].name, houseNames[i]);
        houses[i].actualScore = 0;
        houses[i].intriged = 0;
        houses[i].revel = 0;
        houses[i].objective = shuffleObjectives(pObjectivesDeck, size);
        size--;
    }
}

int shuffleObjectives(int *objectivesDeck, int size){

    srand(time(NULL)); //* Inicia o gerador pseudo-aleatorio

    int index = rand() % size;

    int selected = objectivesDeck[index];

    for(index; index < size - 1; index++){
        objectivesDeck[index] = objectivesDeck[index + 1];
    }

    return selected;
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

void resetStructTable(struct Piece **matriz){
    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            matriz[i][j].value = 0;
            matriz[i][j].intriged = 0;
        }
    }
    return;
}

void readStructScores(struct Piece **matriz, struct House *houses){

    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            houses[i].actualScore = 0;
        }
    }

    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            if(i > 0 && i < 5 && j > 0 && j < 5 && matriz[i][j].value > 0){
                houses[((matriz[i][j].value)-1)].actualScore++;
            }
        }
    }
    return;
}

void drawInterfaceWithStruct(struct Piece **matriz, int actualPiece, struct House *houses){

    void clearScreen();
    char checkIfreveled(struct House houses, int index);

    clearScreen();

    printf("===========  REGICIDA  =========== Proxima Peça:\n");
    printf(
        "   |  1 |  2 |  3 |  4 |  5 |  6 | \033[0;1;3%dm %d - %s\033[0;0m\n",
        actualPiece,
        actualPiece,
        houses[actualPiece -1].name
    );
    printf("================================== PONTUAÇOES\n");

    for(int i = 0; i < 6; i++){

        char tag = '0';

        printf(" %c | ", (i+65));

        for(int j = 0; j < 6; j++){
            printf("\033[0;1;3%dm", matriz[i][j].value); // muda para a cor da casa
            if(matriz[i][j].intriged == 1){
                tag = '!';
            }else{
                tag = '0';
            }
            printf("%c%d ", tag, matriz[i][j].value); // pinta o numero da casa
            printf("\033[255;0m| "); // reseta para a cor padrão
        }

        if(houses[i].intriged == 1){
            printf("!");
        }else{
            printf(" ");
        }

        printf(
            "%d - \033[0;1;3%dm%s  %d/%c Pontos\033[0;0m\n",
            i+1, i+1, houses[i].name, houses[i].actualScore, checkIfreveled(houses[i], i)
        );
    }

    printf("\nSeu proximo movimento sera: ");
}

int moveStructTable(struct Piece **matriz, char *input){
    int c = 0;

    if(strcmp(input, "MVD") == 0){
        for(c; c < 6; c++){ if(matriz[c][5].value > 0)break; }

        if(c == 6){   
            for(int i = 0; i <= 5; i++){
                for(int j = 5; j >= 0; j--){
                    if(j == 0){
                        matriz[i][j].value = 0;
                    }else{
                        matriz[i][j].value = matriz[i][j-1].value;
                    }
                }
            }
        }else{
            printf("Não é possivel mover para está direção...");
            getchar();
        }
        
    }else if(strcmp(input, "MVE")  == 0){
        for(c; c < 6; c++){ if(matriz[c][0].value > 0)break; }

        if(c == 6){   
            for(int i = 0; i <= 5; i++){
                for(int j = 0; j <= 5; j++){
                    if(j == 5){
                        matriz[i][j].value = 0;
                    }else{
                        matriz[i][j].value = matriz[i][j+1].value;
                    }
                }
            }
        }else{
            printf("Não é possivel mover para está direção...");
            getchar();
        }

    }else if(strcmp(input, "MVC")  == 0){
        for(c; c < 6; c++){ if(matriz[0][c].value > 0)break; }

        if(c == 6){   
            for(int i = 0; i <= 5; i++){
                for(int j = 0; j <= 5; j++){
                    if(i == 5){
                        matriz[i][j].value = 0;
                    }else{
                        matriz[i][j].value = matriz[i+1][j].value;
                    }
                }
            }
        }else{
            printf("Não é possivel mover para está direção...");
            getchar();
        }

    }else if(strcmp(input, "MVB")  == 0){
        for(c; c < 6; c++){ if(matriz[5][c].value > 0)break; }

        if(c == 6){   
            for(int i = 5; i >= 0; i--){
                for(int j = 0; j <= 5; j++){
                    if(i == 0){
                        matriz[i][j].value = 0;
                    }else{
                        matriz[i][j].value = matriz[i-1][j].value;
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

int insetInStructTable(struct Piece **matriz, char *commandInput, int piece, int round_0){
    
    int i = commandInput[0] - 65;
    int j = commandInput[1] - '1';
    
    //* Comando invalido
    if(i < 0 || i > 5 || j < 0 || j > 5) return 0;

    //* Posição ocupada
    if(matriz[i][j].value != 0) return 1;

    if(round_0 == 1){
        matriz[i][j].value = piece;
        return 3; //* Posicionamento feito
    }

    //* preencher matriz
    if(i > 0 && matriz[i - 1][j].value > 0){
        matriz[i][j].value = piece;
        return 3;
    }else if(i < 5 && matriz[i + 1][j].value > 0){
        matriz[i][j].value = piece;
        return 3;
    }else if(j > 0 && matriz[i][j - 1].value > 0){
        matriz[i][j].value = piece;
        return 3;
    }else if(j < 5 && matriz[i][j + 1].value > 0){
        matriz[i][j].value = piece;
        return 3;
    }else {
        return 2; //* Posicionamento não adjacente
    }
}

char checkIfreveled(struct House house, int index){
    if(house.revel == 0){
        return '?';
    }else{
        char str[1];
        sprintf(str, "%d", house.objective);
        return str[0];
    }
}

void choiceToRevel(struct House *houses, int difficulty){
    int h;

    printf("Escolha um objetivo e você descobrira a qual casa ele pertence!\n");
    printf("0 | 1 | 2 | 3 | 4 | 6\n");

    for(int i = 0; i < difficulty; i++){
        printf("Escolha o %dº objetivo: ");
        do{
            scanf("%d", &h);
        }while(h < 0 || h > 6 || h == 5);

        for(int j = 0; j < 6; j++){
            if(houses[j].objective == h){
                houses[j].revel = 1;
            }
        }
    }
}

void exchangeValues(struct Piece **pPieces, int i1, int j1, int i2, int j2, struct House *pHouses){

    int indexHouse1 = pPieces[i1][j1].value - 1;
    int indexHouse2 = pPieces[i2][j2].value - 1;

    int opcao = 0;

    if(pPieces[i1][j1].intriged == 1 && pPieces[i2][j2].intriged == 0){

        pPieces[i2][j2].intriged = 1;

    } else if(pPieces[i1][j1].intriged == 0 && pPieces[i2][j2].intriged == 1){

        pPieces[i1][j1].intriged = 1;

    }else{

        char strI1 = i1 + 65;
        char strJ1 = j1 + '1';
        char strI2 = i2 + 65;
        char strJ2 = i2 + '1';

        printf("Escolha a peça que recebera a intriga:\n");
        printf("\033[0;1;3%dm1 - %c%c: %s\n", pPieces[i1][j1].value, strI1, strJ1, pHouses[indexHouse1].name);
        printf("\033[0;1;3%dm2 - %c%c: %s\n", pPieces[i2][j2].value, strI2, strJ2, pHouses[indexHouse2].name);
        printf("\033[0;0m");

        do{
            printf("Sua escolha sera: ");
            scanf("%d", &opcao);
            if(opcao != 1 && opcao != 2) printf("Opcao invalida");
        }while(opcao != 1 && opcao != 2);

        if(opcao == 1) pPieces[i1][j1].intriged = 1;
        if(opcao == 2) pPieces[i2][j2].intriged = 1;
    }

    if(pHouses[indexHouse1].intriged == 1 && pHouses[indexHouse2].intriged == 0){
        
        pHouses[indexHouse2].intriged = 1;

    }else if(pHouses[indexHouse1].intriged == 0 && pHouses[indexHouse2].intriged == 1){
        
        pHouses[indexHouse1].intriged = 1;

    }else{
        printf("Escolha a casa que recebera a intriga:\n");
        printf("\033[0;1;3%dm1 - %s\n", pPieces[i1][j1].value, pHouses[indexHouse1].name);
        printf("\033[0;1;3%dm2 - %s\n", pPieces[i2][j2].value, pHouses[indexHouse2].name);
        printf("\033[0;0m");

        do{
            printf("Sua escolha sera: ");
            scanf("%d", &opcao);
            if(opcao != 1 && opcao != 2) printf("Opcao invalida!");
        }while(opcao != 1 && opcao != 2);

        if(opcao == 1) pHouses[indexHouse1].intriged = 1;
        if(opcao == 2) pHouses[indexHouse2].intriged = 1;
    }

    int temp = pPieces[i1][j1].value;

    pPieces[i1][j1].value = pPieces[i2][j2].value;

    pPieces[i2][j2].value  = temp;

    return;
}

int validateVictory(struct House *houses){
    int i;
    for(i = 0; i < 6; i++){
        if(houses[i].actualScore != houses[i].objective){
            return 0;
        }
    }

    return 1;
}
