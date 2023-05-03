#include "../headers/structs.h"
#include "../headers/utilitaires.h"
#include "../headers/consultation.h"
#include "../headers/suppression.h"
#include <stdio.h>
#include <stdlib.h>

// Trier les etudiant par nom
void trierTabEtudiantsParNom(Etudiant *tab, short size){
    Etudiant tmp;
    for (short i = 0; i < size; i++)
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
void trierTabEtudiantsParPreom(Etudiant *tab, short size){
    Etudiant tmp;
    for (short i = 0; i < size; i++)
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
    for (short i = 0; i < size; i++)
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
    for (short i = 0; i < size; i++)
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
    for (short i = 0; i < size; i++)
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
    for (short i = 0; i < originalTabSize; ++i)
    {
        if (originalTab[i].filiere == filiere)
        {

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
void trierEtudiants(Etudiant *tableauEtudiants,short tailleTab){
    short reponse;
    Etudiant *destinationTabPtr[MAX_CARACTERE];
    printf("\t\t\t\t\t\t\033[0;36m+-----------------------------------------------------------------------+\n"); 
    printf("\t\t\t\t\t\t+\033[0;33m Comment voulez-vous trier les donnees presentees dans le fichier:\t\033[0;36m+\n");
    printf("\t\t\t\t\t\t+\033[0;33m 1- Trier par nom.\t\t\t\t\t\t\t\033[0;36m+\n\t\t\t\t\t\t+\033[0;33m 2- Trier par prenom.\033[0;36m\t\t\t\t\t\t\t+\n\t\t\t\t\t\t+\033[0;33m 3- Trier par numero apogee.\t\t\t\t\t\t\033[0;36m+\n\t\t\t\t\t\t+\033[0;33m 4- Trier par moyenne.\t\t\t\t\t\t\t\033[0;36m+\n\t\t\t\t\t\t+\033[0;33m 5- Trier par la date d'inscription.\t\t\t\t\t\033[0;36m+\n\t\t\t\t\t\t+\033[0;33m 6- Afficher les etudiants d'une filiere.\t\t\t\t\033[0;36m+\n\t\t\t\t\t\t+\033[0;33m 7- Trier par niveau de formation.\t\t\t\t\t\033[0;36m+\n\t\t\t\t\t\t+\033[0;33m 8- Filtrer les etudiants selon l'admission.\t\t\t\t\033[0;36m+\n\t\t\t\t\t\t+\033[0;33m 9- Afficher les etudiants d'un groupe de TD.\t\t\t\t\033[0;36m+\n\t\t\t\t\t\t+\033[0;33m 10- Annuler.\t\t\t\t\t\t\t\t\033[0;36m+\n");
    printf("\t\t\t\t\t\t\033[0;36m+-----------------------------------------------------------------------+\n"); 
    do
    {
        printf("\t\t\t\t\t\t\033[0;33m+\033[0;32m=>");
        scanf("%hd",&reponse);
        printf("\033[0;33m");
        if (reponse < 1 || reponse > 10)
        {
            printf("\t\t\t\t\t\t");
            Erreur(0);
        }
    } while (!(reponse > 0 && reponse <= 10));
    switch (reponse)
    {
    case 1:
        trierTabEtudiantsParNom(tableauEtudiants,tailleTab);
        break;
    case 2:
        trierTabEtudiantsParPreom(tableauEtudiants,tailleTab);
        break;
    case 3:
        trierTabEtudiantsParApogee(tableauEtudiants,tailleTab);
        break;
    case 4:
        trierTabEtudiantsParMoyenne(tableauEtudiants,tailleTab);
        break;
    case 5:
        trierTabEtudiantsParDate(tableauEtudiants,tailleTab);
        break;
    case 6:;
        char filiere[5];
        printf("\t\t\t\t\t\t\033[0;33m+Preciser la filiere dont vous souhaitez afficher ses etudians\n");
        printf("\t\t\t\t\t\t\033[0;33m+\033[0;32m=>");
        scanf("%s",filiere);
        printf("\033[0;36m");
        for (short i = 1; i < 10; i++){
            if (strcmp(filiere,Filieres[i]) == 0){
                filtrerEtudiantsFiliere(tableauEtudiants,tailleTab,i,destinationTabPtr);
            }
        }
        break;
    case 7:;
        char formation[10];
        printf("\t\t\t\t\t\t\033[0;33m+Preciser le niveau de formation selon lequelle vous souhaitez trier ses etudians\n");
        printf("\t\t\t\t\t\t\033[0;33m+\033[0;32m=>");
        scanf("%s",formation);
        for (int i = 1; i < 4; i++){
            if (strcmp(formation,Formations[i]) == 0){
                filtrerEtudiantsFormation(tableauEtudiants,tailleTab,i,destinationTabPtr);
            }
        }
        break;
    case 8:;
        short choix;
        printf("\t\t\t\t\t\t\033[0;36m+Souhaitez-vous afficher :\n1- Les etudiants admis?\n2- Les redoublants?\n");
        printf("\t\t\t\t\t\t\033[0;36m+\033[0;32m=>");
        scanf("%hd",&choix);
        if ( choix == 1){
            filtrerEtudiantsRedoublant(tableauEtudiants,tailleTab,faux,destinationTabPtr);
        }
        else{
            filtrerEtudiantsRedoublant(tableauEtudiants,tailleTab,vrai,destinationTabPtr);
        }
        break;
    case 9:;
        short gtd;
        printf("\t\t\t\t\t\t\033[0;36m+Enter le numero du groupe de TD a afficher ses etudians:\n");
        do
        {
            printf("\t\t\t\t\t\t\033[0;36m+\033[0;32m=>");
            scanf("%hd",&gtd);
        } while (!(gtd < 100));
        filtrerEtudiantsG_TD(tableauEtudiants,tailleTab,gtd,destinationTabPtr);
        break;
    case 10:
        break;
    
    default:
        Erreur(3);
        break;
    }

}