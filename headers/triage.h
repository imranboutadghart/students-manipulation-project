#pragma once // directive de préprocesseur pour éviter les inclusions multiples

#ifndef FILTER_H
#define FILTER_H

#include "../headers/structs.h"
#include "../headers/utilitaires.h"
#include "../headers/consultation.h"
#include "../headers/suppression.h"
#include <stdio.h>
#include <stdlib.h>

extern void trierTabEtudiantsParNom(Etudiant*, short);
extern void trierTabEtudiantsParPrenom(Etudiant*, short);
extern void trierTabEtudiantsParApogee(Etudiant* , short);
extern void trierTabEtudiantsParMoyenne(Etudiant* , short);
extern void trierTabEtudiantsParDate(Etudiant* , short);
extern short filtrerEtudiantsFiliere(Etudiant*, short, short, Etudiant**);
extern short filtrerEtudiantsFormation(Etudiant*, short, short, Etudiant**);
extern short filtrerEtudiantsRedoublant(Etudiant*, short, Bool, Etudiant**);
extern short filtrerEtudiantsG_TD(Etudiant*, short, short, Etudiant**);
extern Etudiant *trierEtudiants(Etudiant* ,short ,unsigned int *);

#endif /*FILTER_H*/