#pragma once // directive de préprocesseur pour éviter les inclusions multiples

#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdio.h>
#include <unistd.h>
#include "../headers/structs.h"

extern void ClearConsole(int);
extern short TesterFichier(FILE*);
extern Bool estFichierVide(FILE*);
extern void Erreur(short);
extern void entrerDonnee(void);
extern void LireNomFichiers(FILE**, FILE**);
extern void PrintAsciiArt(void);
extern void Lancement(void);
extern void MenuPrincipal(Etudiant*,FILE**,FILE**,short);
extern void AfficherCopyright(void);
extern void fermeture(void);

#endif /*UTILITIES_H*/