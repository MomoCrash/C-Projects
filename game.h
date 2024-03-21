#pragma once

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "tools.h"
#include "graphics.h"
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

Tile* GetTile(const Grid* grid, const int x, const int y);

void RefreshMineCountAround(const Grid* grid, const int x, const int y);

bool TileIsAMine(Tile* tile);

void DiscoverTile(Grid* grid, Tile* baseTile, const int x, const int y);

void PlaceFlag(Grid* grid, int x, int y);

void PrintTile(const Tile* tile);

void InitTile(Tile* t);

void PlaceRandomMine(Grid* grid, int mineCount);

int CountGoodFlag(Grid* grid);

void PrintGrid(const Grid* grid);

void InitGrid(Grid* grid, int gridSize, int mineCount);

bool GameLoop(Grid* grid, int mineCount);