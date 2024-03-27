#include "tools.h"
#include <stdio.h>
#include "exo.h"

void InitIntArray(IntArray* pIntArray) {

    pIntArray->iSize = 0;
    pIntArray->iCapacity = 0;

    pIntArray->pContent = (int*)malloc(sizeof(int));

}

void Add(IntArray* pIntArray, int iValue) {

    int newSize = pIntArray->iCapacity + 1;

    pIntArray->pContent = (int*)realloc(pIntArray->pContent, sizeof(int) * newSize);
    pIntArray->pContent[pIntArray->iSize] = iValue;

    pIntArray->iSize++;
    pIntArray->iCapacity++;

}

void Insert(IntArray* pIntArray, int iValue, int iIndex) {
    if (iIndex < pIntArray->iSize && iIndex >= 0) {
        pIntArray->pContent[iIndex] = iValue;
    }
    else {
        printf_s("IndexOutOfBound Exeption\n");
    }
}

void Remove(IntArray* pIntArray, int iIndex) {
    if (iIndex < pIntArray->iSize && iIndex >= 0)
    {
        for (int i = iIndex; i < pIntArray->iSize; i++)
            pIntArray->pContent[i] = pIntArray->pContent[i + 1];

        pIntArray->iCapacity--;
        pIntArray->pContent = (int*)realloc(pIntArray->pContent, sizeof(int) * pIntArray->iCapacity);
    }
    else
        printf("IndexOutOfBound Exeption\n");
}

int Get(IntArray* pIntArray, int iIndex) {
    if (iIndex < pIntArray->iSize && iIndex >= 0) {
        return pIntArray->pContent[iIndex];
    }
    else {
        printf_s("IndexOutOfBound Exeption\n");
    }
}

void PrintIntArray(IntArray* pIntArray) {

    for (int i = 0; i < pIntArray->iCapacity; i++) {
        printf_s("| %d |", pIntArray->pContent[i]);
    }
    printf_s("\n");

}

void Destroy(IntArray* pIntArray) {

    free(pIntArray);

}

/// STRING

String CreateString(const char* str) {

    String string;

    string.iLenght = 0;
    char currentChar = str[0];
    while (currentChar != NULL) {
        string.iLenght++;
        currentChar = str[string.iLenght];
    }

    string.pContent = (char*)malloc(string.iLenght * sizeof(char));
    for (int i = 0; i < string.iLenght; i++) {
        string.pContent[i] = str[i];
    }

    return string;
}

void PrintString(const String pStr) {
    for (int i = 0; i < pStr.iLenght; i++) {
        printf_s("%c", pStr.pContent[i]);
    }
    printf_s("\n");
}

String ConcatenateString(const String* str1, const String* str2) {

    int output_char = 0;
    char* output = (char*)malloc(str1->iLenght + str2->iLenght - 2);
    for (int i = 0; i < str1->iLenght; i++) {
        output[output_char] = str1->pContent[i];
        output_char++;
    }
    for (int j = 0; j < str2->iLenght; j++) {
        output[output_char] = str2->pContent[j];
        output_char++;
    }
    output[output_char] = NULL;
    return CreateString(output);

}
String ConcatenateChar(const char* str1, const char* str2) {

    String string1 = CreateString(str1);
    String string2 = CreateString(str2);
    return ConcatenateString(&string1, &string2);

}

String SubString(const String* str, const int iStart, const int iLenght) {

    String subStr;
    subStr.iLenght = iLenght;
    subStr.pContent = (char*)malloc(iLenght * sizeof(char));


    for (int i = iStart, index = 0; i < iStart + iLenght && i < str->iLenght && index < iLenght; i++, index++) {
        subStr.pContent[index] = str->pContent[i];
    }

    return subStr;

}

String InsertString(const String* pStr1, const String* pStr2, const int iIndex) {

    int output_char = 0;
    char* output = (char*)malloc((pStr1->iLenght + pStr2->iLenght - 2) * sizeof(char));

    for (int i = 0; i < pStr1->iLenght; i++) {
        if (i == iIndex) {
            for (int j = 0; j < pStr2->iLenght; j++) {
                output[output_char] = pStr2->pContent[j];
                output_char++;
            }
        }
        output[output_char] = pStr1->pContent[i];
        output_char++;
    }
    output[output_char] = NULL;

    return CreateString(output);

}

bool AreEqual(const String* pStr1, const String* pStr2) {
    if (pStr1->iLenght != pStr2->iLenght) return false;
    for (int i = 0; i < pStr1->iLenght; i++) {
        if (pStr1->pContent[i] != pStr2->pContent[i]) {
            return false;
        }
    }
    return true;
}

bool TryCastInt(const String* pStr1, int* pResult) {

    for (int i = 0; i < pStr1->iLenght; i++) {
        if (!isdigit(pStr1->pContent[i])) {
            return false;
        }
    }

    int unit = pow(10, pStr1->iLenght - 1);
    *pResult = 0;

    for (int i = 0; i < pStr1->iLenght; i++) {
        *pResult += (int)(pStr1->pContent[i] - '0') * unit;
        unit /= 10;
    }

    return true;

}

void DestroyString(String* string) {
    free(string->pContent);
}

// List

void Init(List* pList) {

    pList->iCount = 1;
    pList->pFirst = (Node*)malloc(sizeof(Node) * 1);

}

void AddFirst(List* pList, int ivalue) {

}

void Start() {

    IntArray array;
    InitIntArray(&array);

    Add(&array, 10);
    Add(&array, 11);
    Add(&array, 12);
    PrintIntArray(&array);

    Insert(&array, 100, 0);
    PrintIntArray(&array);

    Remove(&array, 2);
    PrintIntArray(&array);
    printf("%d \n", Get(&array, 0));

    // String

    String string = CreateString("Salut la team");
    String string1 = CreateString(", wewewe");
    PrintString(string);

    String str = ConcatenateString(&string, &string1);
    PrintString(str);

    String sub = SubString(&str, 1, 3);
    PrintString(sub);

    String inserted = InsertString(&string, &string1, 3);
    PrintString(inserted);

    String a = CreateString("ABBA");
    String b = CreateString("ACCA");
    String c = CreateString("ADDEA");
    String d = CreateString("ABBA");

    printf("%d\n", AreEqual(&a, &b));
    printf("%d\n", AreEqual(&a, &d));
    printf("%d\n", AreEqual(&a, &c));

    int number = 0;
    printf("%d\n", TryCastInt(&a, &number));

    String nStr = CreateString("26259");
    if (TryCastInt(&nStr, &number)) {
        printf("%d\n", number);
    }

    DestroyString(&a);
    DestroyString(&b);
    DestroyString(&c);

}