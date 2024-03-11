#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void AskInt(const char* text, int* value, int* min, int* max) {
    int newValue = *value;
    while (newValue == *value || newValue == -1 || newValue == 0 || newValue > *max || newValue < *min) {
        printf(text, *min, *max);
        scanf("%d", &newValue);
        if (newValue == 0) {
            printf("Vous devez mettre un nombre !");
        }
    }
    *value = newValue;
}

void CheckAnswer(const int number, const int answer) {
    if (number < answer) {
        printf("C'est moins que %d \n", answer);
    } else if (number == answer) {
        printf("Vous avez gagné");
    } else {
        printf("C'est plus que %d \n", answer);
    }

}

int main(void) {

    srand(time(NULL));
    
    int INT_MAX = 999999;
    int INT_MIN = 0;
    
    int min;
    int max;
    
    AskInt("Donnez la borne minimal : ", &min, &INT_MIN, &INT_MAX);
    AskInt("Donnez la borne maximal : ", &max, &min, &INT_MAX);
    
    int random = min + (rand() % (max-min));
    int anwser = -1;

    while (anwser != random) {
        printf("Nouveau tour");
        AskInt("Donnez un nombre entre %d et %d : ", &anwser, &min, &max);
        CheckAnswer(random, anwser);
    }

    return 0;
}