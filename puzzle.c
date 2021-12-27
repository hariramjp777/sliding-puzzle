#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include "colors.h"
#define MAX_MOVES 100

typedef struct {
    int size;
    int** board;
    char moves[MAX_MOVES];
    int moves_index;
} puzzleGame;

puzzleGame* constructPuzzleGame(int size);
bool move(puzzleGame* game, char key);
void printBoard(puzzleGame* game);
void autoSolve(puzzleGame* game);
char getOppositeKey(char key);
void randomize(puzzleGame* game, int randomCount);
bool goalAchieved(int** board, int size);

puzzleGame* constructPuzzleGame(int size) {
    puzzleGame* game = (puzzleGame*) malloc(sizeof(puzzleGame));
    if (game == NULL) {
        return NULL;
    }
    game->size = size;
    game->moves_index = 0;
    game->board = (int**) malloc(size * sizeof(int*));
    if (game->board == NULL) {
        return NULL;
    }
    int count = 1;
    int product = size * size;
    for (int i = 0; i < size; i++) {
        game->board[i] = (int*) malloc(size * sizeof(int));
        if (game->board[i] == NULL) {
            return NULL;
        }
        for (int j = 0; j < size; j++) {
            game->board[i][j] = count++ % product;
        }
    }
    randomize(game, 50);
    return game;
}

bool move(puzzleGame* game, char key) {
    int size, spacedRow, spacedCol, targetRow, targetCol;
    int** board;
    size = game->size;
    board = game->board;
    for (int i = 0; i < size; i++) {
        int found = 0;
        for (int j = 0; j < size; j++) {
            if (board[i][j] == 0) {
                spacedRow = targetRow = i;
                spacedCol = targetCol = j;
                found = 1;
                break;
            }
        }
        if (found == 1) {
            break;
        }
    }
    switch(key) {
        case 'k':
        targetRow = spacedRow + 1;
        break;
        case 'j':
        targetRow = spacedRow - 1;
        break;
        case 'h':
        targetCol = spacedCol + 1;
        break;
        case 'l':
        targetCol = spacedCol - 1;
        break;
    }
    if ((targetRow >= 0 && targetRow < size) && (targetCol >= 0 && targetCol < size)) {
        board[spacedRow][spacedCol] = board[targetRow][targetCol];
        board[targetRow][targetCol] = 0;
        if (game->moves_index == 0 || key != getOppositeKey(game->moves[game->moves_index - 1])) {
            game->moves[game->moves_index++] = key;
        }
        else {
            game->moves_index--;
        }
        if (goalAchieved(board, size)) {
            return true;
        }
    }
    return false;
}

void randomize(puzzleGame* game, int randomCount) {
    srand(time(0));
    int prev = 5;
    char keys[] = {'k', 'j', 'h', 'l', '\0'};
    for (int i = 0; i < randomCount; i++) {
        int pos;
        do {
            pos = rand() % 4;
        } while (keys[pos] == getOppositeKey(keys[prev]));
        prev = pos;
        move(game, keys[pos]);
    }
}

bool goalAchieved(int** board, int size) {
    for (int i = 0, count = 1, product = size * size; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] != count++ % product) {
                return false;
            }
        }
    }
    return true;
}

char getOppositeKey(char key) {
    char opp_key;
    switch(key) {
        case 'k':
        opp_key = 'j';
        break;
        case 'j':
        opp_key = 'k';
        break;
        case 'l':
        opp_key = 'h';
        break;
        case 'h':
        opp_key = 'l';
        break;
        default:
        opp_key = '\0';
        break;
    }
    return opp_key;
}

void autoSolve(puzzleGame* game) {
    int size = game->size;
    for (int i = game->moves_index - 1; i >= 0; i--) {
        system("cls");
        printf("\n");
        printBoard(game);
        sleep(1.7);
        if (move(game, getOppositeKey(game->moves[i]))) {
            return;
        }
    }
}

void printBoard(puzzleGame* game) {
    for (int i = 0, size = game->size, current; i < size; i++) {
        for (int j = 0; j < size; j++) {
            current = game->board[i][j];
            if (current) {
                printf(F_YELLOW "%-4d " RESET, game->board[i][j]);
                continue;
            }
            printf("     ");
        }
        printf("\n");
    }
}
