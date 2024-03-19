#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
//#include "tools.h>
#include <windows.h>


typedef enum { false, true } bool;

typedef struct Tile
{

    bool IsMine;
    bool IsShowed;
    bool IsFlag;

    int MineNumberAround;
    int x;
    int y;

} Tile;

typedef struct Grid
{

    int size;
    Tile* tiles;

    int DiscoveredTile;

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

bool DiscoverTile(Grid* grid, int x, int y) {

    Tile* t = grid->tiles + (grid->size * y + x);

    if (t == NULL) return true;
    if (t->IsShowed) return false;

    t->IsShowed = 1;
    grid->DiscoveredTile++;
    if (t->IsMine) return true;
    if (t->MineNumberAround > 0) return false;

    for (int yAR = y - 1; yAR <= y + 1; yAR++) {
        if (yAR >= grid->size || yAR < 0) continue;
        for (int xAR = x - 1; xAR <= x + 1; xAR++) {
            if (xAR >= grid->size || xAR < 0) continue;

            Tile tile = *(grid->tiles + (grid->size * yAR + xAR));
            if (tile.IsShowed) continue;

            DiscoverTile(grid, xAR, yAR);
        }
    }
    return false;

}

void PlaceFlag(Grid* grid, int x, int y) {
    Tile* t = grid->tiles + (grid->size * y + x);
    if (t->IsFlag) {
        t->IsFlag = false;
    }
    else {
        t->IsFlag = true;
    }
}

void PrintTile(Tile tile) {
    if (tile.IsShowed && tile.IsMine) {
        Color(12, 0);
        printf("| M |");
        Color(15, 0);
    }
    else if (tile.IsShowed) {
        switch (tile.MineNumberAround) {
        case 0:
            Color(15, 0);
            printf("| %d |", tile.MineNumberAround);
            Color(15, 0);
            break;
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
    else if (tile.IsFlag) {
        printf("| F |");
    }
    else {
        printf("| - |");
    }
}

void InitTile(Tile* t, int x, int y) {
    t->IsMine = false;
    t->IsShowed = false;
    t->IsFlag = false;
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
        (grid->tiles + *(randomIntegers + i))->IsMine = true;

    free(randomIntegers);
}

int CountGoodFlag(Grid* grid) {
    int goodMine = 0;
    for (int y = 0; y < grid->size; y++) {
        for (int x = 0; x < grid->size; x++) {
            Tile* t = grid->tiles + (grid->size * y + x);
            if (t->IsFlag && t->IsMine) {
                goodMine++;
            }
        }
    }
    return goodMine;
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
    grid->DiscoveredTile = 0;

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

bool GameLoop(Grid* grid, int mineCount) {

    bool Defeated = false;
    bool Win = false; 
    do {

        bool Flag = AskChar("\n Mettre un drapeau ou decouvrir ?", "fFdD", "fF", "dD");
        bool IsOnMine = false;

        int x;
        int y;

        AskInt("Coordonnee X : ", &x, 1, grid->size);
        AskInt("Coordonnee Y : ", &y, 1, grid->size);

        x--;
        y--;

        if (Flag) {

            PlaceFlag(grid, x, y);
        }
        else {

            IsOnMine = DiscoverTile(grid, x, y);
        }

        PrintGrid(grid);

        if (IsOnMine) {
            printf("C'est une mine ! \n\n");
            Defeated = true;
        }

        if (grid->DiscoveredTile == (grid->size * grid->size - (CountGoodFlag(grid) + (mineCount- CountGoodFlag(grid))))) {
            printf("Et c'est gagnee jeune entrepreneur !");
            Win = true;
        }
    } while (!Defeated && !Win);

    return (!Defeated && Win);
}

int main(void) {

    srand(time(NULL));

    Grid grid;
    int gridSize = 5;
    int bombNumber = 10;

    bool WantReplay = true;

    while (WantReplay) {

        AskInt("Sur quel taille de plateau voulez-vous jouer ?", &gridSize, 0, 100);
        AskInt("Avec combiens de mine", &bombNumber, 0, gridSize*gridSize/2);

        InitGrid(&grid, gridSize, bombNumber);

        GameLoop(&grid, bombNumber);

        WantReplay = AskChar("Voulez-vous rejouer ?", "yYnN", "yY", "nN");

    }

    return 1;

}

void Color(int couleurDuTexte, int couleurDeFond) // fonction d'affichage de couleurs
{
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, couleurDeFond * 16 + couleurDuTexte);
}