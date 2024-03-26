#pragma once

typedef enum { false, true } bool;

void SetConsoleColor(int textcolor, int backgroundcolor);

bool AskChar(const char* anwserText, const char* wantedChar, const char* trueChars, const char* falseChars);

void AskInt(const char* text, int* value, int min, int max);

char IntToChar(const int number);

int RandomRange(int min, int max);

bool ContainInt(int* intArray, int value);

void ClearBuffer();

void RemoveIndexFromArray(int* array, int index);