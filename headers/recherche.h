#pragma once // directive de préprocesseur pour éviter les inclusions multiples

#ifndef SEARCH_H
#define SEARCH_H

#include "../headers/structs.h"
#include "../headers/utilitaires.h"
#include "../headers/consultation.h"
#include "../headers/recherche.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> 

extern unsigned int* NombrePositionLigne(FILE*);
extern void AfficheLigne(FILE*,unsigned int);
extern void AfficheTabLignes(FILE*,short*);


#endif /*SEARCH_H*/
