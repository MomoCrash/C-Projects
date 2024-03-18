#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
//#include "tools.h>
#include <windows.h>


typedef struct Tile
{

    short int IsMine;
    short int IsShowed;

    int MineNumberAround;
    int x;
    int y;

} Tile;

typedef struct Grid
{

    int size;
    Tile* tiles;

    int DiscoveredMine;

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
        if (*(intArray + i) == value) {
            return 1;
        }
    }
    return 0;
}

void Color(int couleurDuTexte, int couleurDeFond);

void MineArroundTile(Grid* grid, int x, int y) {
    Tile* t = grid->tiles + (grid->size * y + x);
    for (int yAR = y - 1; yAR <= y + 1; yAR++) {

        if (yAR >= grid->size || yAR < 0) continue;
        for (int xAR = x - 1; xAR <= x + 1; xAR++) {

            if (xAR >= grid->size || xAR < 0) continue;
            Tile arroundTile = *(grid->tiles + (grid->size * yAR + xAR));
            if (arroundTile.IsMine) {
                t->MineNumberAround++;
            }

        }
    }
}

int DiscoverTile(Grid* grid, int x, int y) {

    Tile* t = grid->tiles + (grid->size * y + x);

    if (t == NULL) return 1;
    if (t->IsShowed) return 0;

    t->IsShowed = 1;
    grid->DiscoveredMine++;
    if (t->IsMine) return 1;
    if (t->MineNumberAround > 0) return 0;

    for (int yAR = y - 1; yAR <= y + 1; yAR++) {
        if (yAR >= grid->size || yAR < 0) continue;
        for (int xAR = x - 1; xAR <= x + 1; xAR++) {
            if (xAR >= grid->size || xAR < 0) continue;

            Tile tile = *(grid->tiles + (grid->size * yAR + xAR));
            if (tile.IsShowed) continue;

            DiscoverTile(grid, xAR, yAR);
        }
    }
    return 0;

}

void PrintTile(Tile tile) {
    if (tile.IsShowed && tile.IsMine) {
        Color(12, 0);
        printf("| M |");
        Color(15, 0);
    }
    else if (tile.IsShowed) {
        switch (tile.MineNumberAround) {
        case 1:
            Color(9, 0);
            printf("| %d |", tile.MineNumberAround);
            Color(15, 0);
            break;
        case 2:
            Color(10, 0);
            printf("| %d |", tile.MineNumberAround);
            Color(15, 0);
            break;
        case 3:
            Color(14, 0);
            printf("| %d |", tile.MineNumberAround);
            Color(15, 0);
            break;
        default:
            Color(5, 0);
            printf("| %d |", tile.MineNumberAround);
            Color(15, 0);
            break;
        }
    }
    else {
        printf("| - |");
    }
}

void InitTile(Tile* t, int x, int y) {
    t->IsMine = 0;
    t->IsShowed = 0;
    t->MineNumberAround = 0;
    t->x;
    t->y;
}

// GRID

void PlaceRandomMine(Grid* grid, int mineCount) {

    int* randomIntegers = (int*)malloc(sizeof(int) * mineCount);
    if (!randomIntegers) return;

    for (int i = 0; i < mineCount; i++) {
        int randomValue = 0;
        do {
            randomValue = RandomRange(0, grid->size * grid->size);
        } while (ContainInt(randomIntegers, randomValue));

        *(randomIntegers + i) = randomValue;
    }

    for (int i = 0; i < mineCount; i++)
        (grid->tiles + *(randomIntegers + i))->IsMine = 1;

    free(randomIntegers);
}

void PrintGrid(Grid* grid) {
    //system("cls");
    for (int y = 0; y < grid->size+1; y++) {

        if (y == 0) {
            printf("     ");
            for (int x = 0; x < grid->size; x++) {
                if (y == 0) {
                    Color(10, 0);
                    printf(" x%d  ", x + 1);
                    Color(15, 0);
                }
            }
            printf("\n");
            continue;
        }

        if (y < 10) {
            Color(10, 0);
            printf("y%d  ", y);
            Color(15, 0);
        }
        else {
            Color(10, 0);
            printf("y%d  ", y);
            Color(15, 0);
        }
        for (int x = 0; x < grid->size; x++) {
            PrintTile(*(grid->tiles + (grid->size * (y-1) + x)));
        }
        printf("\n");
    }
};

void InitGrid(Grid* grid, int gridSize, int mineCount) {
    grid->tiles = (Tile*)malloc(sizeof(Tile) * gridSize * gridSize);
    grid->size = gridSize;
    grid->DiscoveredMine = 0;

    for (int y = 0; y < gridSize; y++) {
        for (int x = 0; x < gridSize; x++) {
            InitTile(grid->tiles + (gridSize * y + x), x, y);
        }
    }

    PlaceRandomMine(grid, mineCount);

    for (int y = 0; y < gridSize; y++) {
        for (int x = 0; x < gridSize; x++) {
            MineArroundTile(grid, x, y);
        }
    }

    PrintGrid(grid);
}

int main(void) {

    srand(time(NULL));

    Grid grid;
    int gridSize = 5;
    int bombNumber = 10;
    InitGrid(&grid, gridSize, bombNumber);

    while (1) {
        int x;
        int y;

        AskInt("Coordonnee X : ", &x, 1, gridSize);
        AskInt("Coordonnee Y : ", &y, 1, gridSize);

        x--;
        y--;

        int IsOnMine = DiscoverTile(&grid, x, y);
        PrintGrid(&grid);

        if (IsOnMine) {
            printf("C'est une mine !!!!!");
            break;
        }

        if (grid.DiscoveredMine == (gridSize * gridSize - bombNumber)) {
            printf("Et c'est gagnée jeune entrepreneur !");
            break;
        }
    }

    return 1;

}

void Color(int couleurDuTexte, int couleurDeFond) // fonction d'affichage de couleurs
{
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, couleurDeFond * 16 + couleurDuTexte);
}