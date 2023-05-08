#include "../headers/structs.h"
#include "../headers/utilitaires.h"
#include "../headers/consultation.h"
#include "../headers/suppression.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Trier les etudiant par nom
void trierTabEtudiantsParNom(Etudiant *tab, short size){
    Etudiant tmp;
    for (short i = 0; i < size - 1; i++)
    {
        for (short j = i+1; j < size; j++)
        {
            if (strcmp(tab[i].nom,tab[j].nom) > 0)
            {
                tmp = tab[i];
                tab[i] = tab[j];
                tab[j] = tmp;
            }
        }
    }
}

// Trier les etudiant par prenom
void trierTabEtudiantsParPrenom(Etudiant *tab, short size){
    Etudiant tmp;
    for (short i = 0; i < size - 1; i++)
    {
        for (short j = i+1; j < size; j++)
        {
            if (strcmp(tab[i].prenom,tab[j].prenom) > 0)
            {
                tmp = tab[i];
                tab[i] = tab[j];
                tab[j] = tmp;
            }
        }
    }
}

// Trier les etudiant selon le numero apgee
void trierTabEtudiantsParApogee(Etudiant *tab, short size){
    Etudiant tmp;
    for (short i = 0; i < size - 1; i++)
    {
        for (short j = i+1; j < size; j++)
        {
            if (tab[i].numApogee > tab[j].numApogee)
            {
                tmp = tab[i];
                tab[i] = tab[j];
                tab[j] = tmp;
            }   
        }
    }
}

// Trier les etudiant selon la moyenne
void trierTabEtudiantsParMoyenne(Etudiant *tab, short size){
    Etudiant tmp;
    for (short i = 0; i < size - 1; i++)
    {
        for (short j = i+1; j < size; j++)
        {
            if (tab[i].moyenne > tab[j].moyenne)
            {
                tmp = tab[i];
                tab[i] = tab[j];
                tab[j] = tmp;
            }
        }
    }
}

// Trier les etudiant par date d'inscription
void trierTabEtudiantsParDate(Etudiant *tab, short size){
    Etudiant tmp;
    for (short i = 0; i < size - 1; i++)
    {
        for (short j = i+1; j < size; j++)
        {
            if (tab[i].date_inscription.annee > tab[j].date_inscription.annee)
            {
                tmp = tab[i];
                tab[i] = tab[j];
                tab[j] = tmp;
                continue;
            }
            if (tab[i].date_inscription.annee < tab[j].date_inscription.annee){continue;}
            
            if (tab[i].date_inscription.mois > tab[j].date_inscription.mois)
            {
                tmp = tab[i];
                tab[i] = tab[j];
                tab[j] = tmp;
                continue;
            }
            if (tab[i].date_inscription.mois < tab[j].date_inscription.mois){continue;}
            
            if (tab[i].date_inscription.jour <= tab[j].date_inscription.jour){continue;}
            tmp = tab[i];
            tab[i] = tab[j];
            tab[j] = tmp;
            continue;
            
        }
    }
}

// Trier les etudiant par la filiere
short filtrerEtudiantsFiliere(Etudiant *originalTab,short originalTabSize,short filiere,Etudiant **destinationTabPtr){
    Etudiant *destinationTab = NULL;
    short index=0;
    for (short i = 0; i < originalTabSize; ++i){
        if (originalTab[i].filiere == filiere){
            destinationTab = realloc(destinationTab,(index+1)* sizeof(Etudiant));
            destinationTab[index] = originalTab[i];
            index++;
        }
    }
    *destinationTabPtr = destinationTab;
    return index;
}

// Trier les etudiant par niveau de formation
short filtrerEtudiantsFormation(Etudiant *originalTab,short originalTabSize,short formation,Etudiant **destinationTabPtr){
    Etudiant *destinationTab = NULL;
    short index=0;
    for (short i = 0; i < originalTabSize; ++i)
    {
        if (originalTab[i].formation == formation)
        {

            destinationTab = realloc(destinationTab,(index+1)* sizeof(Etudiant));
            destinationTab[index] = originalTab[i];
            index++;
        }
    }
    *destinationTabPtr = destinationTab;
    return index;
}

// Trier les etudiant par admission
short filtrerEtudiantsRedoublant(Etudiant *originalTab,short originalTabSize,Bool redoublant,Etudiant **destinationTabPtr){
    Etudiant *destinationTab = NULL;
    short index=0;
    for (short i = 0; i < originalTabSize; ++i)
    {
        if (originalTab[i].redoublant == redoublant)
        {

            destinationTab = realloc(destinationTab,(index+1)* sizeof(Etudiant));
            destinationTab[index] = originalTab[i];
            index++;
        }
    }
    *destinationTabPtr = destinationTab;
    return index;
}

// Trier les etudiants selon groupe de TD
short filtrerEtudiantsG_TD(Etudiant *originalTab,short originalTabSize,short G_TD,Etudiant **destinationTabPtr){
    Etudiant *destinationTab = NULL;
    short index=0;
    for (short i = 0; i < originalTabSize; ++i)
    {
        if (originalTab[i].G_TD == G_TD)
        {
            
            destinationTab = realloc(destinationTab,(index+1)* sizeof(Etudiant));
            destinationTab[index] = originalTab[i];
            index++;
        }
    }
    *destinationTabPtr = destinationTab;
    return index;
}

// Trier les etudiants selon un critere specifie par l'utilisateur
Etudiant *trierEtudiants(Etudiant *tableauEtudiants,short tailleTab,unsigned int *desTabSize){
    short reponse;
    Etudiant *destinationTabPtr = (Etudiant *)malloc(tailleTab*sizeof(Etudiant));
    *desTabSize = tailleTab;
    printf("\t\t\t\t\t\t\033[0;36m+-----------------------------------------------------------------------+\n"); 
    printf("\t\t\t\t\t\t+\033[0;33m Comment voulez-vous trier les donnees presentees dans le fichier:\t\033[0;36m+\n");
    printf("\t\t\t\t\t\t+\033[0;33m 1- Trier par nom.\t\t\t\t\t\t\t\033[0;36m+\n");
    printf("\t\t\t\t\t\t+\033[0;33m 2- Trier par prenom.\033[0;36m\t\t\t\t\t\t\t+\n");
    printf("\t\t\t\t\t\t+\033[0;33m 3- Trier par numero apogee.\t\t\t\t\t\t\033[0;36m+\n");
    printf("\t\t\t\t\t\t+\033[0;33m 4- Trier par moyenne.\t\t\t\t\t\t\t\033[0;36m+\n");
    printf("\t\t\t\t\t\t+\033[0;33m 5- Trier par la date d'inscription.\t\t\t\t\t\033[0;36m+\n");
    printf("\t\t\t\t\t\t+\033[0;33m 6- Afficher les etudiants d'une filiere.\t\t\t\t\033[0;36m+\n");
    printf("\t\t\t\t\t\t+\033[0;33m 7- Trier par niveau de formation.\t\t\t\t\t\033[0;36m+\n");
    printf("\t\t\t\t\t\t+\033[0;33m 8- Filtrer les etudiants selon l'admission.\t\t\t\t\033[0;36m+\n");
    printf("\t\t\t\t\t\t+\033[0;33m 9- Afficher les etudiants d'un groupe de TD.\t\t\t\t\033[0;36m+\n");
    printf("\t\t\t\t\t\t+\033[0;33m 10- Annuler.\t\t\t\t\t\t\t\t\033[0;36m+\n");
    printf("\t\t\t\t\t\t\033[0;36m+-----------------------------------------------------------------------+\n"); 
    do
    {
        entrerDonnee();
        if (scanf("%hd", &reponse) != 1) {  // Lire l'entrée de l'utilisateur sous la forme d'un court
            Erreur(3);
            while (getchar() != '\n');  // Effacer le tampon d'entrée
        }
        if (reponse < 1 || reponse > 10) Erreur(4);
    } while (!(reponse > 0 && reponse <= 10));
    switch (reponse)
    {
    case 1:
        trierTabEtudiantsParNom(tableauEtudiants,tailleTab);
        for (int i = 0; i < tailleTab; i++){
            destinationTabPtr[i] = tableauEtudiants[i];
        }
        break;
    case 2:
        trierTabEtudiantsParPrenom(tableauEtudiants,tailleTab);
        for (int i = 0; i < tailleTab; i++){
            destinationTabPtr[i] = tableauEtudiants[i];
        }
        break;
    case 3:
        trierTabEtudiantsParApogee(tableauEtudiants,tailleTab);
        for (int i = 0; i < tailleTab; i++){
            destinationTabPtr[i] = tableauEtudiants[i];
        }
        break;
    case 4:
        trierTabEtudiantsParMoyenne(tableauEtudiants,tailleTab);
        for (int i = 0; i < tailleTab; i++){
            destinationTabPtr[i] = tableauEtudiants[i];
        }
        break;
    case 5:
        trierTabEtudiantsParDate(tableauEtudiants,tailleTab);
        for (int i = 0; i < tailleTab; i++){
            destinationTabPtr[i] = tableauEtudiants[i];
        }
        break;
    case 6:;
        short filiere;
        printf("\t\t\t\t\t\t\033[0;36m+-----------------------------------------------------------------------+\n");
        printf("\t\t\t\t\t\t\033[0;36m+\033[0;33m Preciser la filiere dont vous souhaitez afficher ses etudians (1-9):\t\033[0;36m+\n");
        printf("\t\t\t\t\t\t\033[0;36m+\033[0;33m 1: SMPC. \t\t\t\t\t\t\t\t\033[0;36m+\n");
        printf("\t\t\t\t\t\t\033[0;36m+\033[0;33m 2: SMC.\t\t\t\t\t\t\t\t\033[0;36m+\n");
        printf("\t\t\t\t\t\t\033[0;36m+\033[0;33m 3: SMP.\t\t\t\t\t\t\t\t\033[0;36m+\n");
        printf("\t\t\t\t\t\t\033[0;36m+\033[0;33m 4: STU.\t\t\t\t\t\t\t\t\033[0;36m+\n");
        printf("\t\t\t\t\t\t\033[0;36m+\033[0;33m 5: SV.\t\t\t\t\t\t\t\t\033[0;36m+\n");
        printf("\t\t\t\t\t\t\033[0;36m+\033[0;33m 6: SVTU.\t\t\t\t\t\t\t\t\033[0;36m+\n");
        printf("\t\t\t\t\t\t\033[0;36m+\033[0;33m 7: SMIA.\t\t\t\t\t\t\t\t\033[0;36m+\n");
        printf("\t\t\t\t\t\t\033[0;36m+\033[0;33m 8: SMA.\t\t\t\t\t\t\t\t\033[0;36m+\n");
        printf("\t\t\t\t\t\t\033[0;36m+\033[0;33m 9: SMI.\t\t\t\t\t\t\t\t\033[0;36m+\n");
        printf("\t\t\t\t\t\t\033[0;36m+-----------------------------------------------------------------------+\n");
        do{
            entrerDonnee();
            if (scanf("%hd", &filiere) != 1) {  // Lire l'entrée de l'utilisateur sous la forme d'un court
                Erreur(3);
                while (getchar() != '\n');  // Effacer le tampon d'entrée
            }
            if (filiere < 1 || filiere > 9) Erreur(3);
        } while (filiere < 1 || filiere > 9);
        for (short i = 1; i < 10; i++){
            if (strcmp(Filieres[filiere],Filieres[i]) == 0){
                *desTabSize = filtrerEtudiantsFiliere(tableauEtudiants,tailleTab,i,&destinationTabPtr);
            }
        }
        break;
    case 7:;
        short formation;
        printf("\t\t\t\t\t\t\033[0;36m+-----------------------------------------------------------------------+\n");
        printf("\t\t\t\t\t\t\033[0;36m+Preciser le niveau de formation selon lequelle vous souhaitez trier ses etudians\n");
        printf("\t\t\t\t\t\t\033[0;36m+\033[0;33m Choisir le niveau de formation de l'etudiant (1-3)\t\t\t\033[0;36m+\n");
        printf("\t\t\t\t\t\t\033[0;36m+\033[0;33m 1: License. \t\t\t\t\t\t\t\t\033[0;36m+\n");
        printf("\t\t\t\t\t\t\033[0;36m+\033[0;33m 2: Master.\t\t\t\t\t\t\t\t\033[0;36m+\n");
        printf("\t\t\t\t\t\t\033[0;36m+\033[0;33m 3: Doctorat.\t\t\t\t\t\t\t\t\033[0;36m+\n");
        printf("\t\t\t\t\t\t\033[0;36m+-----------------------------------------------------------------------+\n");
        do{
            entrerDonnee();
            if (scanf("%hd", &formation) != 1) {  // Lire l'entrée de l'utilisateur sous la forme d'un court
                Erreur(3);
                while (getchar() != '\n');  // Effacer le tampon d'entrée
            }
        if (formation < 1 || formation > 3) Erreur(3);
        } while (formation < 1 || formation > 9);
        for (short i = 1; i < 4; i++){
            if (strcmp(Formations[formation] ,Formations[i]) == 0){
                *desTabSize = filtrerEtudiantsFormation(tableauEtudiants,tailleTab,i,&destinationTabPtr);
            }
        }
        break;
    case 8:;
        short choix;
        printf("\t\t\t\t\t\t\033[0;36m+-----------------------------------------------------------------------+\n");
        printf("\t\t\t\t\t\t\033[0;36m+\033[0;33m Souhaitez-vous afficher :\t\t\t\t\t\t\033[0;36m+\n");
        printf("\t\t\t\t\t\t\033[0;36m+\033[0;33m 1- Les etudiants admis?\t\t\t\t\t\t\033[0;36m+\n");
        printf("\t\t\t\t\t\t\033[0;36m+\033[0;33m 2- Les redoublants?\t\t\t\t\t\t\t\033[0;36m+\n");
        printf("\t\t\t\t\t\t\033[0;36m+-----------------------------------------------------------------------+\n");
        do{
            entrerDonnee();
            if (scanf("%hd", &choix) != 1) {  // Lire l'entrée de l'utilisateur sous la forme d'un court
                Erreur(3);
                while (getchar() != '\n');  // Effacer le tampon d'entrée
            }
        if (choix < 1 || choix > 2) Erreur(3);
        } while (choix < 1 || choix > 2);
        if ( choix == 1){
            *desTabSize = filtrerEtudiantsRedoublant(tableauEtudiants,tailleTab,faux,&destinationTabPtr);
        }
        else{
            *desTabSize = filtrerEtudiantsRedoublant(tableauEtudiants,tailleTab,vrai,&destinationTabPtr);
        }
        break;
    case 9:;
        short gtd;
        printf("\t\t\t\t\t\t\033[0;36m+\033[0;33m Enter le numero du groupe de TD a afficher ses etudians:\n");
        do{
            entrerDonnee();
            if (scanf("%hd", &gtd) != 1) {  // Lire l'entrée de l'utilisateur sous la forme d'un court
                Erreur(3);
                while (getchar() != '\n');  // Effacer le tampon d'entrée
            }
        } while (!(gtd < 100));
        *desTabSize = filtrerEtudiantsG_TD(tableauEtudiants,tailleTab,gtd,&destinationTabPtr);
        break;
    case 10:
        destinationTabPtr = NULL;
        break;
    
    default:
        Erreur(3);
        break;
    }
    return destinationTabPtr;

}