#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 256
#define FICHIER "contacts.csv"

void parser_ligne(const char *ligne, char *nom, char *prenom, char *telephone, char *genre) {
    if (sscanf(ligne, "%49[^;];%49[^;];%19[^;];%19[^\n]",
               nom, prenom, telephone, genre) != 4) {
        nom[0] = '\0';
        prenom[0] = '\0';
        telephone[0] = '\0';
        genre[0] = '\0';
    }
}

void print_header() {
    printf("N | NOM               | PRENOM           | TELEPHONE        | GENRE\n");
    printf("---------------------------------------------------------------------\n");
}

void print_line(int numero, const char *nom, const char *prenom,
                const char *telephone, const char *genre) {
    printf("%d | %-17s | %-17s | %-16s | %s\n",
           numero, nom, prenom, telephone, genre);
}

void afficher_fichier() {
    FILE *f = fopen(FICHIER, "r");
    char ligne[MAX];
    char nom[50], prenom[50], telephone[20], genre[20];
    int numero = 1;

    if (f == NULL) {
        printf("Erreur ouverture fichier\n");
        return;
    }

    print_header();

    while (fgets(ligne, sizeof(ligne), f)) {
        parser_ligne(ligne, nom, prenom, telephone, genre);

        if (nom[0] != '\0') {
            print_line(numero, nom, prenom, telephone, genre);
            numero++;
        }
    }

    fclose(f);
}

void afficher_ligne(int numero_recherche) {
    FILE *f = fopen(FICHIER, "r");
    char ligne[MAX];
    char nom[50], prenom[50], telephone[20], genre[20];
    int numero = 1;

    if (f == NULL) {
        printf("Erreur ouverture fichier\n");
        return;
    }

    while (fgets(ligne, sizeof(ligne), f)) {
        if (numero == numero_recherche) {
            parser_ligne(ligne, nom, prenom, telephone, genre);

            print_header();
            print_line(numero, nom, prenom, telephone, genre);

            fclose(f);
            return;
        }

        numero++;
    }

    printf("Ligne non trouvée\n");
    fclose(f);
}

void ajouter_contact() {
    FILE *f = fopen(FICHIER, "a+");
    char nom[50], prenom[50], telephone[20], genre[20];

    if (f == NULL) {
        printf("Erreur ouverture fichier\n");
        return;
    }

    printf("Nom: ");
    scanf(" %49[^\n]", nom);

    printf("Prenom: ");
    scanf(" %49[^\n]", prenom);

    printf("Telephone: ");
    scanf(" %19[^\n]", telephone);

    printf("Genre: ");
    scanf(" %19[^\n]", genre);

    fseek(f, 0, SEEK_END);

    long taille = ftell(f);
    if (taille > 0) {
        fprintf(f, "\n");
    }

    fprintf(f, "%s;%s;%s;%s", nom, prenom, telephone, genre);

    fclose(f);

    printf("Contact ajoute avec succes.\n");
}

void supprimer_ligne(int ligne_a_supprimer) {
    FILE *f = fopen(FICHIER, "r");
    FILE *temp = fopen("temp1.csv", "w");
    char buffer[MAX];
    int numero = 1;
    int trouve = 0;

    if (f == NULL || temp == NULL) {
        printf("Erreur ouverture fichier\n");

        if (f) fclose(f);
        if (temp) fclose(temp);

        return;
    }

    while (fgets(buffer, sizeof(buffer), f)) {
        if (numero != ligne_a_supprimer) {
            fputs(buffer, temp);
        } else {
            trouve = 1;
        }

        numero++;
    }

    fclose(f);
    fclose(temp);

    remove(FICHIER);
    rename("temp1.csv", FICHIER);

    if (trouve) {
        printf("Ligne %d supprimée.\n", ligne_a_supprimer);
    } else {
        printf("Ligne %d introuvable.\n", ligne_a_supprimer);
    }
}

void inserer_ligne(int ligne_a_inserer, const char *nom, const char *prenom,
                   const char *telephone, const char *genre) {
    FILE *f = fopen(FICHIER, "r");
    FILE *temp = fopen("temp.csv", "w");
    char buffer[MAX];
    int numero = 1;
    int trouve = 0;

    if (f == NULL || temp == NULL) {
        printf("Erreur ouverture fichier\n");

        if (f) fclose(f);
        if (temp) fclose(temp);

        return;
    }

    while (fgets(buffer, sizeof(buffer), f)) {
        if (numero == ligne_a_inserer) {
            fprintf(temp, "%s;%s;%s;%s\n", nom, prenom, telephone, genre);
            trouve = 1;
        }

        fputs(buffer, temp);
        numero++;
    }

    if (!trouve) {
        fprintf(temp, "%s;%s;%s;%s\n", nom, prenom, telephone, genre);
    }

    fclose(f);
    fclose(temp);

    remove(FICHIER);
    rename("temp.csv", FICHIER);

    printf("Ligne %d insérée.\n", ligne_a_inserer);
}

void rechercher_nom(const char *nom_recherche) {
    FILE *f = fopen(FICHIER, "r");
    char ligne[MAX];
    char nom[50], prenom[50], telephone[20], genre[20];
    int numero = 1;
    int trouve = 0;

    if (f == NULL) {
        printf("Erreur ouverture fichier\n");
        return;
    }

    while (fgets(ligne, sizeof(ligne), f)) {
        parser_ligne(ligne, nom, prenom, telephone, genre);

        if (strcmp(nom, nom_recherche) == 0) {
            if (!trouve) {
                print_header();
            }

            print_line(numero, nom, prenom, telephone, genre);
            trouve = 1;
        }

        numero++;
    }

    if (!trouve) {
        printf("Contact introuvable.\n");
    }

    fclose(f);
}

void modifier_ligne(int ligne_a_modifier) {
    FILE *f = fopen(FICHIER, "r");
    FILE *temp = fopen("temp.csv", "w");

    char buffer[MAX];
    char nom[50], prenom[50], telephone[20], genre[20];
    int numero = 1;
    int trouve = 0;
    int choix;

    if (f == NULL || temp == NULL) {
        printf("Erreur ouverture fichier\n");

        if (f) fclose(f);
        if (temp) fclose(temp);

        return;
    }

    while (fgets(buffer, sizeof(buffer), f)) {

        if (numero == ligne_a_modifier) {
            trouve = 1;

            parser_ligne(buffer, nom, prenom, telephone, genre);

            do {
                printf("\n----------------------------------------\n");
                printf("1. Nom       : %s\n", nom);
                printf("2. Prenom    : %s\n", prenom);
                printf("3. Telephone : %s\n", telephone);
                printf("4. Genre     : %s\n", genre);

                printf("\n0. Valider\n\n");
                
                printf("> Choix : ");
                scanf("%d", &choix);

                switch (choix) {
                    case 1:
                        printf("Nouveau nom : ");
                        scanf(" %49[^\n]", nom);
                        break;

                    case 2:
                        printf("Nouveau prenom : ");
                        scanf(" %49[^\n]", prenom);
                        break;

                    case 3:
                        printf("Nouveau telephone : ");
                        scanf(" %19[^\n]", telephone);
                        break;

                    case 4:
                        printf("Nouveau genre : ");
                        scanf(" %19[^\n]", genre);
                        break;

                    case 0:
                        break;

                    default:
                        printf("Choix invalide\n");
                }

            } while (choix != 0);

            fprintf(temp, "%s;%s;%s;%s\n", nom, prenom, telephone, genre);
        }
        else {
            fputs(buffer, temp);
        }

        numero++;
    }

    fclose(f);
    fclose(temp);

    if (!trouve) {
        remove("temp.csv");
        printf("Ligne %d introuvable.\n", ligne_a_modifier);
        return;
    }

    if (remove(FICHIER) != 0) {
        printf("Impossible de supprimer l'ancien fichier.\n");
        return;
    }

    if (rename("temp.csv", FICHIER) != 0) {
        printf("Impossible de renommer le fichier temporaire.\n");
        return;
    }

    printf("Ligne %d modifiee.\n", ligne_a_modifier);
}