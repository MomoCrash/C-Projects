#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

int* CreateIntArray(int size) {
    int* intArray = malloc(size * sizeof(int));
    if (!intArray) { return; }
    return intArray;
}

int* ExtendArray(int* oldArray, int extendSize) {

    int* newArray = realloc(oldArray, extendSize * sizeof(int));
    if (!newArray) { return; }
    oldArray = newArray;

}

void AskInt(const char* text, int* value, int min, int max) {

    int error = 0;
    do {
        printf(text);
        printf("[%d;%d] : \n", min, max);
        error = scanf_s("%d", value);

        if (error == 0) {
            printf("Vous devez mettre un nombre ! \n");
        }
        if (*value < min || *value > max) {
            printf("Le nombre est hors des bornes ! \n");
            error = 0;
        }
    } while (error == 0);

}

int AskReplay() {

    char validChar[] = "ynYN";
    char userChar;

    int isAValidChar = 0;
    while (!isAValidChar) {
        printf_s("Voulez-vous rejouer ? (Y/n) : ");
        scanf_s("%c", &userChar, 1);
        for (int i = 0; i < sizeof validChar; i++) {
            if (validChar[i] == userChar) {
                isAValidChar = 1;
                break;
            }
        }
    }

    if (userChar == 'y' || userChar == 'Y') {
        return 1;
    }
    else {
        return 0;
    }

}

int Game(int maxTry) {

    int min;
    int max;

    AskInt("Donnez la borne minimal ", &min, 0, INT_MAX);
    AskInt("Donnez la borne maximal ", &max, min, INT_MAX);

    int random =  (rand() % (max - min + 1)) + min;
    int answer = -1;

    int currentTryCount = 0;

    while (1) {
        if (currentTryCount >= maxTry) {
            printf("Vous n'avez plus d'essais ! PERDU !");
            break;
        }
        AskInt("Donnez un nombre ", &answer, min, max);
        if (random < answer) {
            printf("C'est moins que %d \n", answer);
        }
        else if (random == answer) {
            printf("Vous avez gagne !! \n");
            break;
        }
        else {
            printf("C'est plus que %d \n", answer);
        }
        currentTryCount++;
    }

    return random;
}

int main(void) {

    int wantReplay = 1;
    int* numberPassed = CreateIntArray(0);
    int indexPassed = 0;

    while (wantReplay) {
        ExtendArray(numberPassed, indexPassed + 1);
        int maxTry;
        AskInt("En combien d'essais voulez vous jouer. ", &maxTry, 0, INT_MAX);

        numberPassed[indexPassed] = Game(maxTry);
        wantReplay = AskReplay();
        indexPassed++;
    }

    printf("Vous avez eu les nombres suivants : \n");
    for (int i = 0; i < indexPassed; i++) {
        printf("%d | ", numberPassed[i]);
    }

    free(numberPassed);

    return 0;
}