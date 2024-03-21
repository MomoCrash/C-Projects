#include "tools.h"
#include "graphics.h"
#include "game.h"

int main(void) {

    DisplayGame();

    return 1;

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