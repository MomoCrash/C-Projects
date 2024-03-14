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

// Min include, max exclude
int RandomRange(int min, int max) {
    return (rand() % (max - min - 1)) + min;
}

int ContainInt(int* intArray, int value) {

    for (int i = 0; i < sizeof intArray; i++) {
        printf("%d |||| ", intArray[i]);
        if (*(intArray + i) == value) {
            return 1;
        }
    }
    return 0;
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
}; 

void PlaceRandomMine(Grid* grid, int mineCount) {

    int* randomIntegers = (int*)malloc(sizeof(int) * mineCount);
    if (randomIntegers == NULL)
        return;

    for (int i = 0; i < sizeof randomIntegers; i++) {
        int randomValue = 0;
        do {
            randomValue = RandomRange(0, grid->size * grid->size);
        } while (ContainInt(randomIntegers, randomValue));

        printf(": %d RANDOM VALUE", randomValue);
        *(randomIntegers + i) = randomValue;
    }

    for (int i = 0; i < mineCount; i++) {
        printf("--%d--", *(randomIntegers + i));
    }

    for (int i = 0; i < mineCount; i++) {
        (grid->tiles + *(randomIntegers + i))->IsMine = 1;
    }
}

void InitGrid(Grid* grid, int gridSize, int mineCount) {
    grid->tiles = (Tile*)malloc(sizeof(Tile) * gridSize * gridSize);
    grid->size = gridSize;

    // Foreach values de tiles on les poses random

    for (int y = 0; y < gridSize; y++) {
        for (int x = 0; x < gridSize; x++) {
            InitTile(grid->tiles + (gridSize * y + x), (gridSize * y + x));
        }
    }

    PlaceRandomMine(grid, mineCount);
    PrintGrid(grid);
}

void DiscoverTile(Grid* grid, int x, int y) {

    Tile* t = grid->tiles + (grid->size * y + x);
    t->IsShowed = 1;

    for (int yAR = y - 1; yAR <= y + 1 && yAR < grid->size && yAR >= 0; yAR++) {
        for (int xAR = x - 1; xAR <= x + 1 && xAR < grid->size && yAR >= 0; xAR++) {
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

    srand(time(NULL));

    Grid grid;
    int gridSize = 5;
    InitGrid(&grid, gridSize, 6);

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