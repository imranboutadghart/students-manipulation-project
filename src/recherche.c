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

/* Rechercher les etudiants par noms ou prenoms 
Elle retourne un tableau dans le premier element est le nombre des element du tableau et chaque element correspand a la position d'une ligne */
// unsigned int* RechercheEtudiant_Nom_Prenom(FILE *fp){
//     unsigned int *array = (unsigned int *) malloc(sizeof(unsigned int));
//     unsigned int *linePositions = NombrePositionLigne(fp),lineCount = 0;
//     char key[17], src[35], line[MAX_CARACTERE];
//     printf("\033[0;33m+-------------------------------------------------+\n");
//     printf("+ Veuillez saisir le nom ou le prenom a chercher: \n");
//     printf("+ \033[0;32m=>");
//     scanf("%16s",key);
//     printf("\033[0;33m");
//     for (int i = 3; i < linePositions[0]+1; i++)
//     {
//         fseek(fp,linePositions[i], SEEK_SET);
//         fgets(line,MAX_CARACTERE,fp);
//         strncpy(src, line, 34);
//         if (strstr(src, key)!=NULL)
//         {
//             if (lineCount%5 == 0)
//             {
//                 array = realloc(array, (lineCount + 2)*sizeof(unsigned int));
//             }
//             ++lineCount;
//             array[lineCount] = linePositions[i];
//         }
//     }
//     array[0] = lineCount;
//     free(linePositions);
//     return array;
// }
// // Rechercher les etudiants par la date d'inscription
// void rechercherEtudiantDate(Etudiant *tabEtudiant, short tabSize, FILE **fichier,FILE **){
//     int year;
//     short reponse;
//     printf("Entrez l'annee a chercher: ");
//     scanf("%d",&year);
    

//     printf("Recherche des etudiants inscrits en %d:\n", year);
//     year %= 100;
//     int *indexes = (int *)malloc(sizeof(int)), j = 0;//tableau des indexes des etudiants trouvés
//     // Parcourir le tableau d'etudiants
//     for(short i = 0; i < tabSize; i++){
//         // Vérifier si la date d'inscription correspond à la date saisie
//         if(year == tabEtudiant[i].date_inscription.annee % 100){
//             indexes[j] = i;
//             j++;
//             printf("\033[31m %d: \033[0m",j);
//             AfficheEtudiant(tabEtudiant[i]);
//         }
//         if(0 != j){
//             printf("Choisir l'operation a effectuer: \n 1- Modifier les inforamations d'un l'etudiant.\n 2- Supprimer un etudiant.\n 3- Choisir une autre date.\n 4- Annuler.\n");
//             printf("+ \033[0;32m=>");
//             scanf("%hd", &reponse);
//             short i = 0;
//             switch (reponse)
//             {
//             case 1:;
//                 while(i<0 || i>j){
//                 printf("veuillez choisir l'etudiant a modifier (entre 0 et %d)",j);
//                 scanf("%hu",&i);}
//                 EditEtudiant(&tabEtudiant[indexes[i-1]],FICHIERDATA,FICHIERNOTES);
//                 break;
//             case 2:;
//                 while(i<0 || i>j){
//                 printf("veuillez choisir l'etudiant a suprimer (entre 0 et %d)",j);
//                 scanf("%hu",&i);}
//                 suprimerEtudiant(FICHIERDATA,FICHIERNOTES,tabEtudiant[indexes[i-1]]);
//                 break;
//             case 3:
//                 rechercherEtudiantDate(tabEtudiant,tabSize);
//                 break;
//             case 4:
//                 break;
            
//             default:
//                 break;
//             }
//         }
//     }
//     free(indexes);
// }

// // Rechercher un etudiant par numero apogee
// // void rechercheEtudiantApogee(Etudiant *etudiants, short nb_etudiant) {
// //     short apogee,reponse;
// //     printf("Entez le numero apogee de l'etudiant a rechercher: \n");
// //     scanf("%hd",&apogee);
// //     for (short i = 0; i < nb_etudiant; i++) {
// //         if (etudiants[i].numApogee == apogee) {
// //             AfficheEtudiant(etudiants[i]);
// //             printf("Choisir l'operation a effectuer: \n 1- Modifier les inforamations de l'etudiant.\n 2- Supprimer l'etudiant.\n 3- Entrer un autre numero apgee.\n 4- Annuler.\n");
// //             do{
// //                 printf("+ \033[0;32m=>");
// //                 scanf("%hd", &reponse);
// //             } while (reponse <= 0 || reponse > 4);
// //             switch (reponse)
// //             {
// //             case 1:
// //                 EditEtudiant(&etudiants[i],FICHIERDATA,FICHIERNOTES);
// //                 break;
// //             case 2:
// //                 suprimerEtudiant(FICHIERDATA,FICHIERNOTES,etudiants[i]);
// //                 break;
// //             case 3:
// //                 rechercheEtudiantApogee(etudiants,nb_etudiant);
// //                 break;
// //             case 4:
// //                 break;
            
// //             default:
// //                 break;
// //             }
// //         }
// //     }
// }
