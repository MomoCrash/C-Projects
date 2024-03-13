#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
//#include "tools.h>


typedef struct Tile
{

    short int IsMine;
    short int IsShowed;

    int MineNumberAround;

} Tile;

typedef struct Grid
{

    int size;
    Tile* tiles;

} Grid;

void AskInt(const char* text, int* value, int min, int max) {

    char c = '0';
    int error = 0;
    do {
        printf(text);
        printf("[%d;%d] : \n", min, max);
        error = scanf_s("%d", value);

        if (error == 0) {
            printf("Vous devez mettre un nombre ! \n");
            do {
                c = getchar();
            } while (!isdigit(c));
            ungetc(c, stdin);
            continue;
        }
        if (*value < min || *value > max) {
            printf("Le nombre est hors des bornes ! \n");
            error = 0;
            continue;
        }
    } while (error == 0);

}

void PrintTile(Tile tile) {
    if (tile.IsShowed) {
        printf("| %d |", tile.MineNumberAround);
    }
    else {
        printf("| - |");
    }
}

void InitTile(Tile* t, int index) {
    t->IsMine = 0;
    t->IsShowed = 0;
    t->MineNumberAround = 0;
}

void PrintGrid(Grid* grid) {
    //system("cls");
    for (int y = 0; y < grid->size; y++) {
        for (int x = 0; x < grid->size; x++) {
            PrintTile(*(grid->tiles + (grid->size * y + x)));
        }
        printf("\n");
    }
}

void InitGrid(Grid* grid, int gridSize) {
    grid->tiles = (Tile*)malloc(sizeof(Tile) * gridSize * gridSize);
    grid->size = gridSize;

    // Foreach values de tiles on les poses random

    for (int y = 0; y < gridSize; y++) {
        for (int x = 0; x < gridSize; x++) {
            InitTile(grid->tiles + (gridSize * y + x), (gridSize * y + x));
        }
    }

    PrintGrid(grid);

}

void DiscoverTile(Grid* grid, int x, int y) {

    Tile* t = grid->tiles + (grid->size * y + x);
    t->IsShowed = 1;

    for (int yAR = y - 1; yAR < y + 1 && yAR < grid->size && yAR >= 0; yAR++) {
        for (int xAR = x - 1; xAR < x + 1 && xAR < grid->size && yAR >= 0; xAR++) {
            Tile tile = *(grid->tiles + (grid->size * yAR + xAR));

            if (tile.IsMine) {
                tile.MineNumberAround++;
            }

            printf("%dx", xAR);
            printf("%dy", yAR);

            if (!tile.IsMine && !tile.IsShowed) {
                DiscoverTile(grid, xAR, yAR);
            }
        }

    }
}

int main(void) {

    Grid grid;
    int gridSize = 5;
    InitGrid(&grid, gridSize);

    while (1) {
        int x;
        int y;

        AskInt("Coordonnee X : ", &x, 1, gridSize);
        AskInt("Coordonnee Y : ", &y, 1, gridSize);

        x--;
        y--;

        DiscoverTile(&grid, x, y);
        PrintGrid(&grid);
    }

    return 1;

}