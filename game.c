#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>

#include "tools.h"
#include "graphics.h"
#include "game.h"

/// <summary>
/// Get a tile from the grid
/// </summary>
/// <param name="grid"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <returns>The tile from gift grid position</returns>
Tile* GetTile(const Grid* grid, const int x, const int y)
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
    grid->remainTiles--;
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

    int count = 0;
    for (int i = 0; i < mineCount; i++) {

        if (!randomIntegers) exit(1);
        int randIndex = rand() % (gridTileCount - count);

        Tile* tile = (grid->tiles + randomIntegers[randIndex]);
        if (tile->isShowed) {
            tile->isMine = false;
            RemoveIndexFromArray(randomIntegers, randIndex);
            randomIntegers = (int*)realloc(randomIntegers, gridTileCount * sizeof(int) - count * sizeof(int));
            i--;
        }
        else {
            tile->isMine = true;
            RemoveIndexFromArray(randomIntegers, randIndex);
            randomIntegers = (int*)realloc(randomIntegers, gridTileCount * sizeof(int) - count * sizeof(int));
        }

        count++;

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
    for (int y = 0; y < grid->size + 1; y++) {

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
            PrintTile(GetTile(grid, x, y - 1));
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
            InitTile(GetTile(grid, x, y));
        }
    }

    PrintGrid(grid);
}

bool GameLoop(Grid* grid, int mineCount) {

    bool isDefeat = false;
    bool isWin = false;
    bool isFirstPlay = true;
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

            if (isFirstPlay) {

                Tile* tile = GetTile(grid, x, y);

                for (int yAR = y - 1; yAR <= y + 1; yAR++) {
                    for (int xAR = x - 1; xAR <= x + 1; xAR++) {
                        Tile* arroundTile = GetTile(grid, xAR, yAR);
                        if (arroundTile == NULL) continue;
                        arroundTile->isShowed = true;
                    }
                }

                PlaceRandomMine(grid, mineCount);

                for (int arroundY = 0; arroundY < grid->size; arroundY++) {
                    for (int arroundX = 0; arroundX < grid->size; arroundX++) {
                        RefreshMineCountAround(grid, arroundX, arroundY);
                    }
                }


                for (int yAR = y - 1; yAR <= y + 1; yAR++) {
                    for (int xAR = x - 1; xAR <= x + 1; xAR++) {
                        DiscoverTile(grid, tile, xAR, yAR);
                    }
                }

                isFirstPlay = false;
            }
            else {
                Tile* tile = GetTile(grid, x, y);
                if (TileIsAMine(tile)) {
                    isOnMine = true;
                }
                else {
                    DiscoverTile(grid, tile, x, y);
                }
            }
        }

        PrintGrid(grid);

        if (isOnMine) {
            printf("C'est une mine ! \n\n");
            isDefeat = true;
        }

        if (grid->remainTiles == (grid->size * grid->size - (CountGoodFlag(grid) + (mineCount - CountGoodFlag(grid))))) {
            printf("Et c'est gagnee jeune entrepreneur !");
            isWin = true;
        }
    } while (!isDefeat && !isWin);

    return (!isDefeat && isWin);
}