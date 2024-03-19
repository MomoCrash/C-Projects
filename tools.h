#pragma once
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>

void AskInt(const char* text, int* value, int min, int max) {

    char c = '0';
    int error = 0;
    do {
        printf(text);
        printf("[%d;%d] : \n", min, max);
        error = scanf_s("%d", value);

        if (error == 0) {
            SetConsoleColor(12, 0);
            printf("Vous devez mettre un nombre ! \n");
            SetConsoleColor(15, 0);
            do {
                c = getchar();
            } while (!isdigit(c));
            ungetc(c, stdin);
            continue;
        }
        if (*value < min || *value > max) {
            SetConsoleColor(12, 0); //TODO : Régler le problème d'affichage de couleur permanent
            printf("Le nombre est hors des bornes ! \n");
            SetConsoleColor(15, 0);
            error = 0;
            continue;
        }
    } while (error == 0);

}