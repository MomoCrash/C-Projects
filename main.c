#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void CheckAnswer(const int number, const int answer) {

    printf("This is your path: %d\n", answer);
    if (number > answer) {
        printf("Moins");
    } else if (number == answer) {
        printf("Gagner");
    } else {
        printf("Plus");
    }

}

int main(void) {

    srand(time(NULL));
    int r = rand();

    printf("Donnez un nombre entre 1 et 100 : \n");

    int iError = scanf("%d");
    if (iError == 0) {
        printf("NAN");
    }
    CheckAnswer(r, iError);

    return 0;
}