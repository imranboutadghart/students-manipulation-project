#include "../headers/structs.h"
#include "../headers/utilitaires.h"
#include "../headers/consultation.h"
#include "../headers/recherche.h"
#include "../headers/suppression.h"
#include "../headers/modification.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> 

// Position du premier characteres pour chaque ligne pour des raisons d'affichage
unsigned int* NombrePositionLigne(FILE* fichier) {
    rewind(fichier);
    unsigned int lineCount = 0;
    unsigned int* array = malloc((lineCount + 1) * sizeof(unsigned int));
    array[0] = 0;
    char ch;
    while ((ch = fgetc(fichier)) != EOF) {
        if (ch == '\n') {
            lineCount++;
            array = realloc(array, (lineCount + 1) * sizeof(unsigned int));
            array[lineCount] = ftell(fichier);
        }
    }
    --lineCount;
    array = realloc(array, (lineCount + 1) * sizeof(unsigned int));
    array[0] = lineCount;
    return array;
}

// Afficher une ligne a partir de sa position
void AfficheLigne(FILE *file,unsigned int linePos){
    fseek(file,linePos,SEEK_SET);
    char student[MAX_CARACTERE];
    fgets(student,MAX_CARACTERE,file);
    printf("%s",student);
}

// Afficher un tableau de lignes (Premier element du tableau est sa taille)
void AfficheTabLignes(FILE *file,short *array){
    ClearConsole(2);
    AfficheTabHeader();
    for (int i = 1; i <= array[0]; i++){
        AfficheLigne(file, array[i]);
    }
    printf("----------------------------------------------------------------------------------------------------------------------\n");
}

void RechercheEtudiant(Etudiant *tabEtuds,unsigned int tabSize){
    short reponse;
    printf("\t\t\t\t\t\t\033[0;36m+-----------------------------------------------------------------------+\n");
    printf("\t\t\t\t\t\t+\033[0;33m Que souhaitez-vous chercher ?    \t\t\t\t\t\033[0;36m+\n");
    printf("\t\t\t\t\t\t+\033[0;33m 1- chercher par nom et prenom.   \t\t\t\t\t\033[0;36m+\n");
    printf(" \t\t\t\t\t\t+\033[0;33m 2- chercher par numero apogee.  \t\t\t\t\t\033[0;36m+\n");
    printf("  \t\t\t\t\t\t+\033[0;33m 3- charcher par annee d'inscription.\t\t\t\t\t\033[0;36m+\n");
    printf("\t\t\t\t\t\t\033[0;36m+-----------------------------------------------------------------------+\n");
    do
    {
        printf("\t\t\t\t\t\t\033[0;36m+\033[0;32m=>");
        scanf("%hd",&reponse);
        printf("\033[0;36m");
        if (reponse < 1 || reponse > 3)
        {
            printf("\t\t\t\t\t\t");
            Erreur(0);
        }
    } while (!(reponse > 0 && reponse <= 3));
    switch (reponse){
    case 1:
        chercherNomPrenom(tabEtuds,tabSize);
        break;
    case 2:
        chercherApogee(tabEtuds,tabSize);
        break;
    case 3:
        chercherAnnee(tabEtuds,tabSize);
        break;
    default:
        Erreur(3);
        break;
    }
    printf("\t\t\t\t\t\t+\033[0;33m veuillez saisir un caractere pour continuer:\t\t\t\t\t\033[0;36m+\n");
    printf("\t\t\t\t\t\t\033[0;36m+\033[0;32m=>");
    fgetc(stdin);
    printf("\n");
}
/* Rechercher les etudiants par noms ou prenoms 
Elle retourne un tableau dans le premier element est le nombre des element du tableau et chaque element correspand a la position d'une ligne */
void chercherNomPrenom(Etudiant *tabEtuds,unsigned int tabSize) {
    printf("\t\t\t\t\t\t+\033[0;33m veuillez saisir le nom ou prenom a chercher:\n");
    char *string = (char *)malloc(17*sizeof(char));
    printf("\t\t\t\t\t\t\033[0;36m+\033[0;32m=>");
    scanf("%s",string);
    char *stringCap = (char *)malloc(17*sizeof(char));
    strcpy(stringCap,string);
    CapitaliserNom(stringCap);
    for (unsigned int i = 0; i < tabSize; i++)
    {
        if (strstr(tabEtuds[i].nom,string) || strstr(tabEtuds[i].nom,stringCap) || strstr(tabEtuds[i].prenom,string) || strstr(tabEtuds[i].prenom,stringCap))
        {
            AfficheEtudiant(tabEtuds[i]);
        }
        
    }
    free(string);free(stringCap);
}
void chercherAnnee(Etudiant *tabEtuds,unsigned int tabSize) {
    printf("\t\t\t\t\t\t+\033[0;33m veuillez saisir l'annee d'inscription':\\n");
    printf("\t\t\t\t\t\t\033[0;36m+\033[0;32m=>");
    int annee;
    scanf("%d",&annee);
    if (50 < annee && 100 > annee)annee+=1900;
    else if(0<annee && 50 > annee)annee += 2000;
    
    for (unsigned int i = 0; i < tabSize; i++)
    {
        if (annee == tabEtuds[i].date_inscription.annee)
        {
            AfficheEtudiant(tabEtuds[i]);
        }
        
    }
}
void chercherApogee(Etudiant *tabEtuds,unsigned int tabSize) {
    printf("\t\t\t\t\t\t+\033[0;33m veuillez saisir l'apogee a chercher':\n");
    printf("\t\t\t\t\t\t\033[0;36m+\033[0;32m=>");
    int apogee;
    scanf("%d",&apogee);
    char sapogee[17],tmpsapogee[17];
    sprintf(sapogee,"%d",apogee);
    for (unsigned int i = 0; i < tabSize; i++)
    {
        sprintf(tmpsapogee,"%d",tabEtuds[i].numApogee);
        if (strstr(tmpsapogee,sapogee))
        {
            AfficheEtudiant(tabEtuds[i]);
        }
        
    }
}

