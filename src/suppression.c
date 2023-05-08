#include "../headers/structs.h"
#include "../headers/utilitaires.h"
#include "../headers/consultation.h"
#include "../headers/suppression.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Supprimer un etudiant du fichier
void suprimerEtudiant(FILE **fichier, FILE **fichierNote,Etudiant etud){
    int lineToDelete = etud.line;
    FILE *tmp = fopen("data/tmp.txt","w+");
    if (tmp == NULL){Erreur(3);return;}
    rewind(*fichier);
    int count = 0;
    char ch;
    while ((ch = fgetc(*fichier)) != EOF) {
        if (ch == '\n') {
            count++;
        }
        // ecrire la ligne dans le fichier temporaire sauf s'il est la lignne a suprime
        if (count != lineToDelete) {
            fputc(ch, tmp);
        }
    }
    fclose(*fichier);
    fclose(tmp);
    remove(FICHIERDATA);
    rename("data/tmp.txt", FICHIERDATA);
    *fichier = fopen(FICHIERDATA,"a+");
    TesterFichier(*fichier);
    tmp = fopen("data/tmp.txt","w+");
    if (tmp == NULL){Erreur(3);return;}
    rewind(*fichierNote);
    count = 0;
    while ((ch = fgetc(*fichierNote)) != EOF) {
        if (ch == '\n') {
            count++;
        }
        // ecrire la ligne dans le fichier temporaire sauf s'il est la lignne a suprime
        if (count != lineToDelete) {
            fputc(ch, tmp);
        }
    }
    fclose(*fichierNote);
    fclose(tmp);
    remove(FICHIERNOTES);
    rename("data/tmp.txt", FICHIERNOTES);
    *fichierNote = fopen(FICHIERNOTES,"a+");  
    TesterFichier(*fichierNote);
    printf("(+) Student's data has been deleted successfully\n");
}