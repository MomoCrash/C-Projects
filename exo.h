#pragma once
#include "tools.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>

// Array type

typedef struct IntArray
{
    int* pContent;

    int iSize;
    int iCapacity;

} IntArray;

void InitIntArray(IntArray* pIntArray);

void Add(IntArray* pIntArray, int iValue);

void Insert(IntArray* pIntArray, int iValue, int iIndex);

void Remove(IntArray* pIntArray, int iIndex);

int Get(IntArray* pIntArray, int iIndex);

void PrintIntArray(IntArray* pIntArray);

void Destroy(IntArray* pIntArray);

// String type

typedef struct String {
    char* pContent;
    int iLenght;
} String;

String CreateString(const char* str);

void PrintString(const String pStr);

String ConcatenateString(const String* str1, const String* str2);

String ConcatenateChar(const char* str1, const char* str2);

String SubString(const String* str, const int iStart, const int iLenght);

String InsertString(const String* pStr1, const String* pStr2, const int iIndex);

bool AreEqual(const String* pStr1, const String* pStr2);

bool TryCastInt(const String* pStr1, int* pResult);

void DestroyString(String* string);

void Start();

// List type 

typedef struct Node {

    Node* pNext;
    Node* pPrevious;

    int iValue;

} Node;

typedef struct List {
    Node* pFirst;

    int iCount;
}List;

void Init(List* pList);