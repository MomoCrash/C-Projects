#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include "tools.c"

//Variables
int nombreEntre = 0;
int nombreEssais = 0;
int nombreMaxEssais = 5;
int borneMinimale = 0;
int borneMaximale = 0;

//Fonctions pouvant être intégrer dans le tools
void Replay() {
    printf("Rejouer (y, n, Y, N)\n");
    char validChar[] = "yYnN";
    char playerchar[] = "%c";
    scanf_s("c", &playerchar);
    if (validChar == playerchar) {
        return 0;
    }
    else {
        return 1;
    }
}

void AskInt(const char* text, int* value) {
    printf(text, "\n");
    scanf_s("%d", value);
}

//Fonction principale
int main() {

    srand(time(NULL));

    printf("Jeu : Plus ou Moins!\n");

    printf("borne minimale ?");
    scanf_s("%d", &borneMinimale);

    printf("borne maximale ?");
    scanf_s("%d", &borneMaximale);

    int nombreMystere = borneMinimale +(rand() % (borneMaximale - borneMinimale));

    printf("Devinez le nombre mystère entre %d et %d.\n", borneMinimale, borneMaximale);

    // Boucle de jeu
    do {
        printf("Quel est le nombre ? ");
        scanf_s("%d", &nombreEntre);
        nombreEssais++;

        if (nombreEntre < nombreMystere) {
            printf("C'est plus !\n");
        }
        else if (nombreEntre > nombreMystere) {
            printf("C'est moins !\n");
        }
        else {
            printf("Bravo, vous avez trouvé le nombre mystère en %d essais !\n", nombreEssais);
            break;
            Replay();
        }
    } while (nombreEssais < nombreMaxEssais);

    if (nombreEssais >= nombreMaxEssais) {
        printf("Vous avez perdu.\n");
        Replay();
        //return 1;
    }

    return 0;
}