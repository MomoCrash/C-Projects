#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>

/* Ex 8
int main() {
	int a, b;
	printf("Entre 2 entiers\n");
	scanf_s("%d%d", &a, &b);
	if (a > b) {
		printf("Voici l'entier le plus grand : %d\n", a);
	}
	else {
		printf("voici l'entier le plus grand : %d\n", b);
	}
	system("pause");
	return 0;
}
*/

/* Ex 7
int main() {
	double R1, R2, Aire1, Aire2, AireF;
	printf("Entrer le rayon du premier cercle :\n");
	scanf_s("%lf", &R1);
	Aire1 = (R1 * R1) * 3.14159265358979323846264338;
	printf("Entrer le rayon du deuxieme cercle :\n");
	scanf_s("%lf", &R2);
	Aire2 = (R2 * R2) * 3.14159265358979323846264338;
	printf("Voici l'aire du premier cercle : %.2lf.\n Et voici l'aire du deuxieme : %.2lf.\n", Aire1, Aire2);
	AireF = Aire1 - Aire2;
	printf("Voici l'aire de la surface comprise entre les 2 cercles : %.2lf.\n", AireF);
	system("pause");
	return 0;
}
*/

/* Ex 6
int main() {
	//pas de système de vérification comme AskChar
	char c;
	printf("veuillez entrer une lettre entre a et y ou A et Y.\n");
	scanf_s("%c", &c);
	c++;
	printf("la lettre apres celle que vous avez entre est : %c\n", c);
	system("pause");
	return 0;
}
*/

/* Ex 5
int main() {
	int a, b, c = 0;
	float moyenne = 0;
	printf("Entrer 3 entiers\n");
	scanf_s("%d%d%d", &a, &b, &c);
	moyenne = (a + b + c) / 3;
	printf("voici la moyenne de vos 3 entiers avec une precision de 2 chiffres apres la virgule : %.2f", moyenne);
	system("pause");
	return 0;
}
*/

/* Ex 4
int main() {
	int a, b, c = 0;
	printf("Entrer deux nombres entiers\n");
	scanf_s("%d%d", &a, &b);
	printf("variables avant permutation : a = %d, b = %d\n", a, b);
	c = a;
	a = b;
	b = c;
	printf("variables apres permutation : a = %d, b = %d\n", a, b);
	system("pause");
	return 0;
}
*/

/* Ex 3
int main() {
	float a, b, c;
	printf("Entrer deux nombres reel\n");
	scanf_s("%f%f", &a, &b);
	c = a * b;
	printf("voici le resultat : %.3f", c); //.xf = x chiffres après la virgule
	system("pause");
	return 0;
}
*/

/* Ex 2
int main() {
	int i = 0;
	int i2 = 0;
	int i3 = 0;
	int i4 = 0;
	printf("Entrer un nombre entier de 3 chiffres : \n");
	scanf_s("%d", &i);
	i2 = (i % 10)*100;
	printf("voici i2 : %d \n", i2);
	i3 = (i % 100) - (i % 10);
	printf("voici i3 : %d \n", i3);
	i4 = i / 100; //marche uniquement avec des entiers 
	printf("voici i4 : %d \n", i4);
	i = i2 + i3 + i4;
	return i;
	system("pause");
	return 0;
}
*/

/* Ex 1
int main() {
	printf("Bonjour \n");
	return 0;
}
*/

//site des exos : https://theccoder.com/exercices-c