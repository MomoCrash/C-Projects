#include <stdio.h>

void AskInt(const char* text, int* value) {
    printf("%s\n", text);
    scanf("%d", value);
}

int Replay() {
    printf("Rejouer (y, n, Y, N)?\n");
    char choice;
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y') {
        return 1;
    }
    else if (choice == 'n' || choice == 'N') {
        return 0;
    }
    return 0;
}