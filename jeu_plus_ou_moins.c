
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Initialisation du générateur de nombres aléatoires
    srand(time(NULL)); // pas compris 
    
    // Génération d'un nombre aléatoire entre 1 et 100
    int nombreMystere = rand() % 100 + 1; // 100 + 1 pour faire une borne = pas trop compris pourquoi cette syntaxe
    int nombreEntre = 0;
    int nombreEssais = 0;
    
    printf("Jeu : Plus ou Moins!\n");
    printf("Devinez le nombre mystère entre 1 et 100.\n");
    
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
        }
    } while (nombreEntre != nombreMystere);
    
    return 0;
}
