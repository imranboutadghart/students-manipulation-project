#pragma once // directive de préprocesseur pour éviter les inclusions multiples

#ifndef CONSULT_H
#define CONSULT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> 
#include "../headers/utilitaires.h"
#include "../headers/structs.h"
#include "../headers/consultation.h"

extern void lireBool(Bool*);
extern Bool estBissextile(short);
extern Bool estDateValide(short,short,short); 
extern void lireDate(Date*);
extern unsigned int NombreAleatoire_7(short);
extern void FiliereEtudiant(Etudiant*);
extern void FormationEtudiant(Etudiant*);
extern void AjouteNote(Etudiant*);
extern void CapitaliserNom(char*);
extern void LireEtudiant(Etudiant* ,FILE* ,FILE*);
extern void AfficheTabHeader();
extern void AfficheEtudiant(Etudiant);
extern Etudiant *tabEtudiants(FILE*, FILE*, unsigned int*);
extern void afficheTabEtudiants(Etudiant*, short);
extern void lireNoteFichier(FILE*, Etudiant*, short);
extern Etudiant lireEtudiantFichier(FILE*, FILE*, int);
extern void TabHeader(FILE*);
extern void TabHeaderNotes(FILE*);
extern void sauvgardeNotes(Etudiant , FILE*);
extern void SauvegardeEtudiant(Etudiant ,FILE* ,FILE*);

#endif /* CONSULT_H */