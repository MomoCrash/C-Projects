#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tools.c"

int main() {
    // Initialisation du générateur de nombres aléatoires
    srand(time(NULL)); 
    
    // Génération d'un nombre aléatoire entre 1 et 100
    int nombreMystere = rand() % scanf("%d", "%d");
    int nombreEntre = 0;
    int nombreEssais = 0;
    int nombreMaxEssais = 5;
    
    printf("Jeu : Plus ou Moins!\n");
    printf("Devinez le nombre mystère entre 1 et 100.\n");
    
    // Boucle de jeu
    do {
        printf("Quel est le nombre ? ");
        scanf("%d", &nombreEntre);
        nombreEssais++;
        
        if (nombreEntre < nombreMystere) {
            printf("C'est plus !\n");
        }
        else if (nombreEntre > nombreMystere) {
            printf("C'est moins !\n");
        }
        else {
            printf("Bravo, vous avez trouvé le nombre mystère en %d essais !\n", nombreEssais);
        }

        if (nombreEssais == nombreMaxEssais) {
            printf("Vous avez perdu");
            return 1;
        }
        
    } while (nombreEntre != nombreMystere);
    
    return 0; // en gros ca veut dire que tout s'est bien passé. (Ok)
}
