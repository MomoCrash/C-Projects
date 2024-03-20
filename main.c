#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "tools.h"
#include <windows.h>

typedef struct Tile
{

    bool isMine;
    bool isShowed;
    bool isFlag;

    short int mineNumberAround;

} Tile;

typedef struct Grid
{

    int size;
    Tile* tiles;

    int remainTiles;

} Grid;

/// <summary>
/// Get a tile from the grid
/// </summary>
/// <param name="grid"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <returns>The tile from gift grid position</returns>
Tile* GetTile(const Grid* grid, const int x, const int y ) 
{
    if (x >= grid->size || x < 0) return NULL;
    if (y >= grid->size || y < 0) return NULL;
    Tile* t = grid->tiles + (grid->size * y + x);
    if (!t) exit(1);
    return t;
}

/// <summary>
/// Set mine number arround a tile
/// </summary>
/// <param name="grid"></param>
/// <param name="x"></param>
/// <param name="y"></param>
void RefreshMineCountAround(const Grid* grid, const int x, const int y) {
    Tile* t = GetTile(grid, x, y);
    for (int yAR = y - 1; yAR <= y + 1; yAR++) {
        for (int xAR = x - 1; xAR <= x + 1; xAR++) {
            Tile* arroundTile = GetTile(grid, xAR, yAR);
            if (arroundTile == NULL) continue;
            if (arroundTile->isMine) {
                t->mineNumberAround++;
            }
        }
    }
}

/// <summary>
/// Check if the tile is a mine
/// </summary>
/// <param name="tile"></param>
/// <returns>If the tile is a mine</returns>
bool TileIsAMine(Tile* tile) {

    if (tile == NULL) exit(1);
    if (tile->isShowed) return false;

    tile->isShowed = 1;
    if (tile->isMine) return true;
    return false;

}

/// <summary>
/// Discover tile and tile arround reccursively
/// </summary>
/// <param name="grid"></param>
/// <param name="baseTile"></param>
/// <param name="x"></param>
/// <param name="y"></param>
void DiscoverTile(Grid* grid, Tile* baseTile, const int x, const int y) {

    baseTile->isShowed = true;
    if (baseTile->mineNumberAround > 0) return;

    for (int yAR = y - 1; yAR <= y + 1; yAR++) {
        for (int xAR = x - 1; xAR <= x + 1; xAR++) {

            Tile* tile = GetTile(grid, xAR, yAR);
            if (tile == NULL) continue;
            if (tile->isShowed) continue;

            DiscoverTile(grid, tile, xAR, yAR);
        }
    }
    return;

}

/// <summary>
/// Toggle flag state of the tile
/// </summary>
/// <param name="grid"></param>
/// <param name="x"></param>
/// <param name="y"></param>
void PlaceFlag(Grid* grid, int x, int y) {
    Tile* t = GetTile(grid, x, y);
    if (t == NULL) return;
    if (t->isFlag) {
        t->isFlag = false;
    } 
    else {
        t->isFlag = true;
    }
}

void PrintTile(const Tile* tile) {
    if (tile == NULL) return;
    if (tile->isShowed && tile->isMine) {
        SetConsoleColor(12, 0);
        printf("| M |");
        SetConsoleColor(15, 0);
    }
    else if (tile->isShowed) {
        switch (tile->mineNumberAround) {
        case 0:
            SetConsoleColor(15, 0);
            printf("| %d |", tile->mineNumberAround);
            SetConsoleColor(15, 0);
            break;
        case 1:
            SetConsoleColor(9, 0);
            printf("| %d |", tile->mineNumberAround);
            SetConsoleColor(15, 0);
            break;
        case 2:
            SetConsoleColor(10, 0);
            printf("| %d |", tile->mineNumberAround);
            SetConsoleColor(15, 0);
            break;
        case 3:
            SetConsoleColor(14, 0);
            printf("| %d |", tile->mineNumberAround);
            SetConsoleColor(15, 0);
            break;
        default:
            SetConsoleColor(5, 0);
            printf("| %d |", tile->mineNumberAround);
            SetConsoleColor(15, 0);
            break;
        }
    }
    else if (tile->isFlag) {
        printf("| F |");
    }
    else {
        printf("| - |");
    }
}

void InitTile(Tile* t) {
    t->isMine = false;
    t->isShowed = false;
    t->isFlag = false;
    t->mineNumberAround = 0;
}

// GRID

void PlaceRandomMine(Grid* grid, int mineCount) {

    int gridTileCount = grid->size * grid->size;
    int* randomIntegers = (int*)malloc(sizeof(int) * (gridTileCount));
    if (!randomIntegers) exit(1);

    for (int i = 0; i < gridTileCount; i++) {
        randomIntegers[i] = i;
    }

    for (int i = 0; i < mineCount; i++) {
        if (!randomIntegers) exit(1);
        int randIndex = rand() % (gridTileCount - i);
        (grid->tiles + randomIntegers[randIndex])->isMine = true;
        RemoveIndexFromArray(randomIntegers, randIndex);
        randomIntegers = (int*) realloc(randomIntegers, gridTileCount * sizeof(int) - i * sizeof(int));
    }

    free(randomIntegers);

}

int CountGoodFlag(Grid* grid) {
    int goodMine = 0;
    for (int y = 0; y < grid->size; y++) {
        for (int x = 0; x < grid->size; x++) {
            Tile* t = GetTile(grid, x, y);
            if (t == NULL) continue;
            if (t->isFlag && t->isMine) {
                goodMine++;
            }
        }
    }
    return goodMine;
}

void PrintGrid(const Grid* grid) {
    //system("cls");
    for (int y = 0; y < grid->size+1; y++) {

        if (y == 0) {
            printf("     ");
            for (int x = 0; x < grid->size; x++) {
                if (y == 0) {
                    SetConsoleColor(10, 0);
                    printf(" x%d  ", x + 1);
                    SetConsoleColor(15, 0);
                }
            }
            printf("\n");
            continue;
        }

        if (y < 10) {
            SetConsoleColor(10, 0);
            printf("y%d  ", y);
            SetConsoleColor(15, 0);
        }
        else {
            SetConsoleColor(10, 0);
            printf("y%d  ", y);
            SetConsoleColor(15, 0);
        }
        for (int x = 0; x < grid->size; x++) {
            PrintTile(GetTile(grid, x, y-1));
        }
        printf("\n");
    }
};

void InitGrid(Grid* grid, int gridSize, int mineCount) {
    grid->tiles = (Tile*)malloc(sizeof(Tile) * gridSize * gridSize);
    grid->size = gridSize;
    grid->remainTiles = gridSize * gridSize;

    for (int y = 0; y < gridSize; y++) {
        for (int x = 0; x < gridSize; x++) {
            InitTile(GetTile(grid, x, y), x, y);
        }
    }
    PlaceRandomMine(grid, mineCount);
    for (int y = 0; y < gridSize; y++) {
        for (int x = 0; x < gridSize; x++) {
            RefreshMineCountAround(grid, x, y);
        }
    }

    PrintGrid(grid);
}

void MoveMine(Grid* grid, int x, int y) {

    int* availableTiles = (int*)malloc(sizeof(int) * (grid->size * grid->size));
    int availableCount = 0;

    for (int i = 0; i < grid->size * grid->size; i++) {
        if (!grid->tiles[i].isMine) {
            availableTiles[availableCount] = i;
            availableCount++;
        }
    }

    if (availableCount > 0) {
        int randomIndex = rand() % availableCount;
        int newTileIndex = availableTiles[randomIndex];

        Tile* originaltile = GetTile(grid, x, y);
        originaltile = false;

        grid->tiles[newTileIndex].isMine = true;


    }

}

bool GameLoop(Grid* grid, int mineCount) {

    bool isDefeat = false;
    bool isWin = false; 
    int counts = 0;

    do {

        bool isFlag = AskChar("\n Mettre un drapeau ou decouvrir ?", "fFdD", "fF", "dD");
        bool isOnMine = false;

        int x;
        int y;

        AskInt("Coordonnee X : ", &x, 1, grid->size);
        AskInt("Coordonnee Y : ", &y, 1, grid->size);

        x--;
        y--;

        if (isFlag) {

            PlaceFlag(grid, x, y);
        }
        else {

            Tile* tile = GetTile(grid, x, y);
            if (TileIsAMine(tile)) {
                if (counts == 0) {

                }
                else {
                    isOnMine = true;
                }            }
            else {
                DiscoverTile(grid, tile, x, y);
            }
        }

        PrintGrid(grid);

        if (isOnMine && counts == 0) {
            MoveMine(grid, x, y);
            PrintGrid(grid);
            continue;
        }

        else if (isOnMine) {
            printf("C'est une mine ! \n\n");
            isDefeat = true;
        }

        if (grid->remainTiles == (grid->size * grid->size - (CountGoodFlag(grid) + (mineCount- CountGoodFlag(grid))))) {
            printf("Et c'est gagne jeune entrepreneur !");
            isWin = true;
        }
        counts++;
    } while (!isDefeat && !isWin);

    return (!isDefeat && isWin);
}


int main(void) {

    srand(time(NULL));

    Grid grid;
    int gridSize = 5;
    int bombNumber = 10;

    bool isReplaying = true;

    while (isReplaying) {

        AskInt("Sur quel taille de plateau voulez-vous jouer ?", &gridSize, 0, 1000);
        AskInt("Avec combiens de mine", &bombNumber, 0, gridSize*gridSize/2);

        InitGrid(&grid, gridSize, bombNumber);

        GameLoop(&grid, bombNumber);

        isReplaying = AskChar("Voulez-vous rejouer ?", "yYnN", "yY", "nN");

    }

    free(grid.tiles);

    return 1;

}