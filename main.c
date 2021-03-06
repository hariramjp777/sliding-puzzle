#include <stdio.h>
#include <stdlib.h>
#include "colors.h"
#include "puzzle.c"
#include "unistd.h"

bool includes(char options[], char option);

int main(void) {
    puzzleGame* game = constructPuzzleGame(4);
    if (game == NULL) {
        return -2;
    }
    char options[] = {'k', 'j', 'h', 'l', 's', 'q', '\0'};
    char option;
    int prev = 1;
    system("cls");
    while (true) {
        if (prev == 0) {
            printf(F_RED "<Invalid Option>\n" RESET);
        }
        printf("\n");
        printBoard(game);
        printf("\n");
        printf(F_YELLOW "> " RESET F_D_BLUE "'k' " RESET "for KeyUp\n");
        printf(F_YELLOW "> " RESET F_D_BLUE "'j' " RESET "for KeyDown\n");
        printf(F_YELLOW "> " RESET F_D_BLUE "'h' " RESET "for KeyLeft\n");
        printf(F_YELLOW "> " RESET F_D_BLUE "'l' " RESET "for KeyRight\n");
        printf(F_YELLOW "> " RESET F_D_BLUE "'s' " RESET "for AutoSolve\n");
        printf(F_YELLOW "> " RESET F_D_BLUE "'q' " RESET "for Quit\n");
        printf("\n" F_YELLOW ">> " RESET);
        scanf("\n%c", &option);
        if (!includes(options, option)) {
            prev = 0;
            system("cls");
            continue;
        }
        prev = 1;
        if (option == 'q') {
            return 0;
        }
        if (option == 's') {
            autoSolve(game);
            system("cls");
            printf("\n");
            printBoard(game);
            printf("\n");
            printf(F_B_PURPLE "Game Solved!\n" RESET);
            break;
        }
        if (move(game, option)) {
            system("cls");
            printf("\n");
            printBoard(game);
            printf("\n");
            printf(F_B_PURPLE "You win the game!\n" RESET);
            break;
        }
        system("cls");
    }
    free(game);
    return 0;
}

bool includes(char options[], char option) {
    for (int i = 0, n = strlen(options); i < n; i++) {
        if (options[i] == option) {
            return true;
        }
    }
    return false;
}