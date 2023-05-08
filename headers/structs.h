#pragma once // directive de préprocesseur pour éviter les inclusions multiples

#ifndef STRUCT_H
#define STRUCT_H

#define MAX_CARACTERE 1024 
#define _Line 119
#define ALPHABET_SIZE 32
#define MAX_NOTES 6

// Declaration of variables
extern const char* nomMois[];
extern const char* Filieres[];
extern const char* Formations[];
extern char FICHIERDATA[];
extern char FICHIERNOTES[];

// Definition d'enumeration booleenne
typedef enum Bool{faux, vrai}Bool;

// Definition de structure de date
typedef struct Date
{
    short int mois, jour, annee;
}Date;

// Definition de structure etudiant
typedef struct Etudiant{
short line;
unsigned int numApogee;
char *nom;
char *prenom;
Date date_inscription;
short int formation;
Bool redoublant;
short filiere;
short G_TD;
float *notes;
short nbnotes;
float moyenne;
}Etudiant;

#endif /* STRUCT_H */
