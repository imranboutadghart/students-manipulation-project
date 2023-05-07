#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "../headers/structs.h"
#include "../headers/consultation.h"
#include "../headers/modification.h"
#include "../headers/recherche.h"
#include "../headers/suppression.h"
#include "../headers/triage.h"

int main(void){
    FILE *fichier = NULL;
    FILE *fichierNote = NULL;
    Lancement();
    LireNomFichiers(&fichier, &fichierNote);
    // Demander à l'utilisateur de remplir le fichier avec des données au cas où il serait vide
    if (estFichierVide(fichier))
    {
        Bool reponse;
        short n = 1;
        Etudiant *tab_etudiants = (Etudiant *)malloc(n * sizeof(Etudiant));
        do
        {
            LireEtudiant(&tab_etudiants[n - 1], fichier, fichierNote);
            n++;
            tab_etudiants = (Etudiant *)malloc(n * sizeof(Etudiant));
            printf("\t\t\t\t\t\t\033[0;36m+\033[0;33m \n");
            lireBool(&reponse);
        } while (reponse != faux);

        unsigned int *NPL = NombrePositionLigne(fichier);
        unsigned int tabTaille = NPL[0] - 2;
        tab_etudiants = tabEtudiants(fichier, fichierNote, NPL);
        MenuPrincipal(tab_etudiants, &fichier, &fichierNote, tabTaille);
    }
    else
    {
        unsigned int *NPL = NombrePositionLigne(fichier);
        unsigned int tabTaille  = NPL[0] - 2;
        Etudiant *tab_etudiants = tabEtudiants(fichier, fichierNote, NPL);
        MenuPrincipal(tab_etudiants, &fichier, &fichierNote, tabTaille );
        printf("\033[0;33m");
    }
    fermeture();
    return 0;
}
