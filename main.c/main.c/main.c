#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Déclaration de variables
int nombreEntre = 0;
int nombreEssais = 0;
int nombreMaxEssais = 5;
int borneMinimale = 0;
int borneMaximale = 0;

// Fonctions pouvant être intégrer dans le tools

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

// Fonction principale
int main() {
    do {
        srand(time(NULL));

        printf("Jeu : Plus ou Moins!\n");

        AskInt("borne minimale ?", &borneMinimale);
        AskInt("borne maximale ?", &borneMaximale);

        int nombreMystere = borneMinimale + (rand() % (borneMaximale - borneMinimale + 1));

        nombreEssais = 0;

        printf("Devinez le nombre mystère entre %d et %d.\n", borneMinimale, borneMaximale);

        while (nombreEssais < nombreMaxEssais) {
            AskInt("Quel est le nombre ?", &nombreEntre);
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
            }
        }

        if (nombreEssais >= nombreMaxEssais && nombreEntre != nombreMystere) {
            printf("Vous avez perdu. Le nombre mystère était %d.\n", nombreMystere);
        }
    } while (Replay());

    return 0;
}
