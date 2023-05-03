#pragma once // directive de préprocesseur pour éviter les inclusions multiples

#ifndef EDIT_H
#define EDIT_H

#include "../headers/structs.h"
#include "../headers/utilitaires.h"
#include "../headers/consultation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void editNotes(Etudiant*);
extern void editEtudiantFile(Etudiant* ,FILE** ,FILE** ,short);
extern void EditEtudiant(Etudiant* ,FILE** ,FILE**);

#endif /*EDIT_H*/