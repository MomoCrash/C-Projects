#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
//#include "tools.h>
#include <windows.h>


typedef enum { false, true } bool;

//#TODO naming convention
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

    int remainTiles; //remainingTile

} Grid;

void ClearBuffer() {
    while (getchar() != "\n");
}

bool AskChar(const char* anwserText, const char* wantedChar, const char* trueChars, const char* falseChars) {

    char userChar;

    bool isAValidChar = false;
    do {
        printf_s(anwserText);
        printf_s("[");
        for (int i = 0; i < strlen(wantedChar); i++) {
            printf_s("%c", wantedChar[i]);
        }
        printf("]\n");
        scanf_s("%c", &userChar, 1);
        for (int i = 0; i < strlen(wantedChar); i++) {
            if (wantedChar[i] == userChar) {
                isAValidChar = true;
                break;
            }
        }
    } while (!isAValidChar);

    for (int i = 0; i < strlen(trueChars); i++) {
        if (trueChars[i] == userChar) {
            return true;
        }
    }
    for (int i = 0; i < strlen(falseChars); i++) {
        if (falseChars[i] == userChar) {
            return false;
        }
    }

    return false;

}

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

bool ContainInt(int* intArray, int value) {

    for (int i = 0; i < sizeof intArray; i++) {
        if (*(intArray + i) == value) {
            return true;
        }
    }
    return false;
}

void RemoveIndexFromArray(int* array, int index) {

    if (index >= 0)
    {
        for (int i = index; i < sizeof (array); i++)
            array[i] = array[i + 1];
    }
    else
        printf("Element Not Found\n");
}

void Color(int couleurDuTexte, int couleurDeFond);

Tile* GetTile(const Grid* grid, const int x, const int y ) 
{
    if (x >= grid->size || x < 0) return NULL;
    if (y >= grid->size || y < 0) return NULL;
    Tile* t = grid->tiles + (grid->size * y + x);
    if (!t) exit(1);
    return t;
}

void MineArroundTile(const Grid* grid, const int x, const int y) {
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

bool CheckTileState(Tile* tile) {

    if (tile == NULL) exit(1);
    if (tile->isShowed) return false;

    tile->isShowed = 1;
    if (tile->isMine) return true;
    return false;

}

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
        Color(12, 0);
        printf("| M |");
        Color(15, 0);
    }
    else if (tile->isShowed) {
        switch (tile->mineNumberAround) {
        case 0:
            Color(15, 0);
            printf("| %d |", tile->mineNumberAround);
            Color(15, 0);
            break;
        case 1:
            Color(9, 0);
            printf("| %d |", tile->mineNumberAround);
            Color(15, 0);
            break;
        case 2:
            Color(10, 0);
            printf("| %d |", tile->mineNumberAround);
            Color(15, 0);
            break;
        case 3:
            Color(14, 0);
            printf("| %d |", tile->mineNumberAround);
            Color(15, 0);
            break;
        default:
            Color(5, 0);
            printf("| %d |", tile->mineNumberAround);
            Color(15, 0);
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
            MineArroundTile(grid, x, y);
        }
    }

    PrintGrid(grid);
}

bool GameLoop(Grid* grid, int mineCount) {

    bool isDefeat = false;
    bool isWin = false; 
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
            if (CheckTileState(tile)) {
                isOnMine = true;
            }
            else {
                DiscoverTile(grid, tile, x, y);
            }
        }

        PrintGrid(grid);

        if (isOnMine) {
            printf("C'est une mine ! \n\n");
            isDefeat = true;
        }

        if (grid->remainTiles == (grid->size * grid->size - (CountGoodFlag(grid) + (mineCount- CountGoodFlag(grid))))) {
            printf("Et c'est gagnee jeune entrepreneur !");
            isWin = true;
        }
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

// #TODO english , better name
void Color(int couleurDuTexte, int couleurDeFond) // fonction d'affichage de couleurs
{
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, couleurDeFond * 16 + couleurDuTexte);
}