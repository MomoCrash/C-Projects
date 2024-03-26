#include "tools.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>

/// <summary>
/// Use to set the console color
/// </summary>
/// <param name="textcolor"></param>
/// <param name="backgroundcolor"></param>
void SetConsoleColor(int textcolor, int backgroundcolor)
{
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, backgroundcolor * 16 + textcolor);
}

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
            SetConsoleColor(12, 0);
            printf("Le nombre est hors des bornes ! \n");
            SetConsoleColor(15, 0);
            error = 0;
            continue;
        }
    } while (error == 0);

}

char IntToChar(const int number) {
    return (char)(number + '0');
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

void ClearBuffer() {
    while (getchar() != "\n");
}

void RemoveIndexFromArray(int* array, int index) {

    if (index >= 0)
    {
        for (int i = index; i < sizeof(array); i++)
            array[i] = array[i + 1];
    }
    else
        printf("Element Not Found\n");
}