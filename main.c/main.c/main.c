#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// D�claration de variables
int nombreEntre = 0;
int nombreEssais = 0;
int nombreMaxEssais = 5;
int borneMinimale = 0;
int borneMaximale = 0;

// Fonctions pouvant �tre int�grer dans le tools

void AskInt(const char* text, int* value) {
    printf("%s\n", text);
    scanf_s("%d", value);
}


int Replay() {
    printf("Rejouer (y, n, Y, N)?\n");
    char choice;
    scanf_s(" %c", &choice);
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

        printf("Devinez le nombre myst�re entre %d et %d.\n", borneMinimale, borneMaximale);

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
                printf("Bravo, vous avez trouv� le nombre myst�re en %d essais !\n", nombreEssais);
                break;
            }
        }

        if (nombreEssais >= nombreMaxEssais && nombreEntre != nombreMystere) {
            printf("Vous avez perdu. Le nombre myst�re �tait %d.\n", nombreMystere);
        }
    } while (Replay());

    return 0;
}
