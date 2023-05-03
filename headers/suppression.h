#pragma once // directive de préprocesseur pour éviter les inclusions multiples

#ifndef DEL_H
#define DEL_H

#include <stdio.h>
#include <stdlib.h>
#include "../headers/utilitaires.h"
#include "../headers/structs.h"
#include "../headers/consultation.h"

extern void suprimerEtudiant(FILE**, FILE**, Etudiant);

#endif /*DEL_H*/