#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 256
#define FICHIER "contacts.txt"

int lignes = 0;
char nom[50], prenom[50], telephone[20], genre[20];

// decomposer une ligne en champs
void parser_ligne(char *ligne, char *nom, char *prenom, char *telephone, char *genre) {
    sscanf(ligne, "%[^;];%[^;];%[^;];%[^\n]", nom, prenom, telephone, genre);
}

// afficher le header du tableau
void print_header() {
    printf("N |  NOM   |  PRENOM    | TELEPHONE | GENRE \n");
    printf("---------------------------------------------\n");
}

// afficher une seul ligne
void print_line(int lignes, char *nom, char *prenom, char *telephone, char *genre) {
    printf("%d | %s | %s | %s | %s\n", lignes, nom, prenom, telephone, genre);
}

// Afficher tout le contenu
void afficher_fichier() {
    FILE *f = fopen(FICHIER, "r");
    char ligne[MAX];

    if (f == NULL) {
        printf("Erreur ouverture fichier\n");
        return;
    }

    printf("=== Contenu du fichier ===\n");
    
    print_header();
    
    int lignes = 1;
    
    while (fgets(ligne, MAX, f)) {
        parser_ligne(ligne, nom, prenom, telephone, genre);
        print_line(lignes, nom, prenom, telephone, genre);

        lignes++;
    }

    fclose(f);
}

// Afficher une ligne précise
void afficher_ligne(int num) {
    FILE *f = fopen(FICHIER, "r");
    char ligne[MAX];
    int compteur = 1;

    if (f == NULL) {
        printf("Erreur ouverture fichier\n");
        return;
    }

    while (fgets(ligne, MAX, f)) {
        if (compteur == num) {
            parser_ligne(ligne, nom, prenom, telephone, genre);

            print_header();
            print_line(compteur, nom, prenom, telephone, genre);
            
            fclose(f);
            return;
        }
        compteur++;
    }

    printf("Ligne non trouvée\n");
    fclose(f);
}

// Ajouter une nouvelle ligne à la fin du fichier
void ajouter_contact() {
    FILE *f = fopen(FICHIER, "a");
    char nom[50], prenom[50], telephone[20], genre[20];

    if (f == NULL) {
        printf("Erreur ouverture fichier\n");
        return;
    }

    printf("Nom: ");
    scanf(" %[^\n]", nom);

    printf("Prenom: ");
    scanf(" %[^\n]", prenom);

    printf("Telephone: ");
    scanf(" %[^\n]", telephone);

    printf("Genre: ");
    scanf(" %[^\n]", genre);

    fprintf(f, "\n%s;%s;%s;%s", nom, prenom, telephone, genre);

    printf("[i] : Contact ajoute avec succes.\n");

    fclose(f);
}

//ecrire une ligne précis dans le fichier sans supprimer les autres
/*void insert_ligne(int ligne, char *nom, char *prenom, char *telephone, char *genre) {
    FILE *f = fopen(FICHIER, "r");
    FILE *temp = fopen("temp.txt", "w");
    char ligne[MAX];
    int compteur = 1;

    if (f == NULL || temp == NULL) {
        printf("Erreur ouverture fichier\n");
        return;
    }

    while (fgets(ligne, MAX, f)) {
        if (compteur == ligne) {
            fprintf(temp, "%s;%s;%s;%s\n", nom, prenom, telephone, genre);
        } else {
            fputs(ligne, temp);
        }
        compteur++;
    }

    fclose(f);
    fclose(temp);

    remove(FICHIER);
    rename("temp.txt", FICHIER);
}*/

// crée un fichier temporaire et copie tout le contenu du fichier original sauf la ligne à supprimer, puis renomme le fichier temporaire pour remplacer l'original
void supprimer_ligne(int ligne_to_supprimer) {
    FILE *f = fopen(FICHIER, "r");
    FILE *temp = fopen("temp.txt", "w");
    char ligne[MAX];
    int compteur = 1;

    if (f == NULL || temp == NULL) {
        printf("Erreur ouverture fichier\n");
        return;
    }

    while (fgets(ligne, MAX, f)) {
        if (compteur != ligne_to_supprimer){
            fputs(ligne, temp);
        }
        compteur++;
    }

    fclose(f);
    fclose(temp);

    remove(FICHIER);
    rename("temp.txt", FICHIER);

    printf("Ligne %d supprimée (si elle existait).\n", ligne_to_supprimer);
}

// Recherche par nom
void rechercher_nom(char nom_recherche[]) {
    
    FILE *f = fopen(FICHIER, "r");
    char ligne[MAX];
    char nom[50], prenom[50], telephone[20], genre[20];
    int trouve = 0;
    int compteur = 1;

    if (f == NULL) {
        printf("Erreur ouverture fichier\n");
        return;
    }

    while (fgets(ligne, MAX, f)){
        sscanf(ligne, "%[^;];%[^;];%[^;];%[^\n]", nom, prenom, telephone, genre);

        if (strcmp(nom, nom_recherche) == 0) {
            printf("\n[i] : Contact Trouve\n");
            print_header();
            print_line(compteur,nom, prenom, telephone, genre);
            trouve = 1;
        }
        compteur++;
    }

    if (!trouve) {
        printf("[i] : Introuvable !\n");
    }

    fclose(f);
}