#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

// Menu principal
int main() {
    int choix, ligne;
    char nom[50];

    do {
        printf("\n---- MENU ----\n");
        printf("1. Afficher tout\n");
        printf("2. Afficher une ligne\n");
        printf("3. Ajouter un contact\n");
        printf("4. Supprimer un contact\n");
        printf("5. Rechercher par nom\n");
        printf("0. Quitter\n\n");
        printf(" > Choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                afficher_fichier();
                break;
            case 2:
                printf("Numero de ligne: ");
                scanf("%d", &ligne);
                afficher_ligne(ligne);
                break;
            case 3:
                ajouter_contact();
                break;
            case 4:
                printf("Numero de ligne: ");
                scanf("%d", &ligne);
                supprimer_ligne(ligne);
                break;
            case 5:
                printf("Entrer le nom : ");
                scanf(" %[^\n]", nom);
                rechercher_nom(nom);
                break;
        }

    } while (choix != 0);

    return 0;
}