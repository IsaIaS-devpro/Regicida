#include <stdio.h>
#include <stdlib.h>

#define COR_AMARELA "\x1b[33m"
#define COR_AZUL "\x1b[34m"
#define COR_VERMELHA "\x1b[31m"
#define COR_VERDE "\x1b[32m"
#define COR_MAGENTA "\x1b[35m"
#define COR_CYAN "\x1b[36m"
#define RESET_COR "\x1b[0m"

void introduc() {
    printf(COR_AMARELA "\n \t \t \t AS CASAS EST�O DISPUTANDO FEROZMENTE PELO TRONO\n " RESET_COR);
    system("pause");
    printf(COR_AZUL "\t \t \t RESTA VOC�, DONO DE TODOS OS SEGREDOS, MANIPULAR VASSALOS E NOBRES PARA CHEGAR A UM RESULTADO QUE, APESAR DE N�O AGRADAR A TODOS, TRAR� PAZ\n" RESET_COR);
    system("pause");
    printf(COR_VERMELHA "\t \t \t ENTRETANTO, O TEMPO � ESCASSO E ALGUMAS DAS SUAS PRECIOSAS INFORMA��ES TARDAM A CHEGAR.\n" RESET_COR);
    system("pause");
    printf(COR_VERDE "\t \t \t VOC� PRECISAR� TRABALHAR COM INCERTEZAS POR UM MOMENTO.\n" RESET_COR);
    system("pause");
    printf(COR_MAGENTA "\t \t \t E QUANDO AS INFORMA��ES CHEGAREM... TALVEZ SEJA TARDE DEMAIS PARA REVERTER A SITUA��O.\n" RESET_COR);
    system("pause");
    printf(COR_CYAN "\t \t \t A GUERRA PODE ESTAR MAIS PERTO DO QUE NUNCA E A �NICA PESSOA CAPAZ DE EVIT�-LA � VOC�.\n" RESET_COR);
    system("pause");
    system("cls");
}

void Menu() {
    printf("\n");
    printf("\x1b[31m");
    printf("********************** REGICIDA **********************\n");
    printf("\x1b[0m");
    printf(COR_AMARELA "1. Jogar\n"RESET_COR);
    printf(COR_VERDE "2. Cr�ditos\n"RESET_COR);
    printf(COR_MAGENTA "3. Sair\n"RESET_COR);
     printf("\x1b[31m");
    printf("*******************************************************\n");
    printf("\x1b[0m");
    printf("Escolha uma op��o: ");
}

int main() {
    introduc();
    int escolha;
    while (1) {
       Menu();
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                system("cls");
                printf("\nIniciando o jogo...\n");
                system("cls");
                //game();
                break;
            case 2:
                system("cls");
                printf(COR_VERDE "\nExibindo os cr�ditos...\n"RESET_COR);
                printf(COR_MAGENTA"\n JOGO FEITO PELO PROFESSOR HUGO ROBERTO PINHEIRO, \n ASSIM COMO O TRABALHO PARA A TURMA 2023.1 DE CI�NCIDA DA COMPUTA��O"RESET_COR);
                printf(COR_MAGENTA"\n QUEM ESCREVEU O C�DIGO.....HENRIQUE IZ�DIO, ISAIAS FERNANDES E PHELIPPE \n \n "RESET_COR);
                system("\n pause");
                system("cls");
                break;
            case 3:
                system("cls");
                printf(COR_CYAN  "\nSaindo do jogo. At� logo!\n"RESET_COR);
                return 0;
            default:
                printf("\nOp��o inv�lida. Por favor, escolha uma op��o v�lida.\n");
                break;
        }
    }

    return 0;
}
