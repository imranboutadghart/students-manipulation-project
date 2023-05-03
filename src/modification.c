#include "../headers/structs.h"
#include "../headers/utilitaires.h"
#include "../headers/consultation.h"
#include "../headers/modification.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Modifier les notes de l'etudiant
void editNotes(Etudiant *etud){ 
    int noteIndex;
    float oldNote;
    printf("\033[0;33m+-------------------------------------------------+\n");
    do{
        printf("+ Quelle est la note que vous souhaitez changer?\033[0;32m\n");
        for (int i = 0; i < etud->nbnotes; i++){
            printf("\033[0;33m+ %d: %f\n", i, etud->notes[i]);
        }
        printf("+ %d: Annuler.\n\033[0;32m", etud->nbnotes);
        printf("+ =>");
        scanf("%d", &noteIndex);
    printf("\033[0;33m+-------------------------------------------------+\n");
    } while (noteIndex < 0 || noteIndex > etud->nbnotes);
    if (noteIndex != etud->nbnotes)
    {
        oldNote = etud->notes[noteIndex];
        printf("\033[0;33m+ Veuillez saisir la nouvelle valeur : \033[0;32m");
        scanf("%f", &etud->notes[noteIndex]);
        etud->moyenne = etud->moyenne + ((etud->notes[noteIndex] - oldNote) / etud->nbnotes);
    }
    if(etud->moyenne <10)etud->redoublant = vrai;
    if(etud->moyenne >=10)etud->redoublant = faux;
    printf("\033[0;33m+-------------------------------------------------+\n");
}

// Modifier les informations de l'etudiant a partir des fichiers
void editEtudiantFile(Etudiant* tab_etud, FILE **fichier, FILE **fichierNote, short tab_size){
    short num;
    FILE *tmp = fopen("data/tmp.txt","w+"); // Fichier temporaire ou les donnees modifiees seront ajoutees
    FILE *tmp_notes = fopen("data/tmp_notes.txt","w+"); // Fichier temporaire ou les motes modifiees seront ajoutees
    TesterFichier(tmp);
    TesterFichier(tmp_notes);
    afficheTabEtudiants(tab_etud, tab_size);
    printf("+ \033[0;33mEntrez le numero de l'etudiant que vous souhaitez modifier ses informations: \n");
    do
    {
        printf("+ \033[0;32m=>");
        scanf("%hd", &num);
    } while (num <= 0 || num > tab_size);
    
    EditEtudiant(&tab_etud[num-1], fichier, fichierNote);
    afficheTabEtudiants(tab_etud, tab_size);
    
    for (int i = 0; i < tab_size ; i++){
        SauvegardeEtudiant(tab_etud[i], tmp, tmp_notes);
    }
    
    fclose(*fichier);
    fclose(*fichierNote);
    fclose(tmp);
    fclose(tmp_notes);
    
    remove(FICHIERDATA);
    rename("data/tmp.txt", FICHIERDATA);
    
    remove(FICHIERNOTES);
    rename("data/tmp_notes.txt", FICHIERNOTES);
    
    *fichier = fopen(FICHIERDATA, "a+");
    TesterFichier(*fichier);
    *fichierNote = fopen(FICHIERNOTES, "a+");
    TesterFichier(*fichierNote);
}

// Modifier les donnees de l'etudiant
void EditEtudiant(Etudiant *etud,FILE **fichier, FILE **fichierNote){ 
    short int choix;
    Bool bool = 0;
    do{
        fflush(stdin);
        printf("\033[0;33m+-------------------------------------------------+\n");
        printf("+ Quel information souhaitez vous modifier :\n+ 1:modifier le nom\n+ 2:modifier le prenom\n+ 3:modifier la date d'inscription\n+ 4:Modifier la filiere\n+ 5:Modifier le niveau de formation\n+ 6:Modifier le groupe de td\n+ 7:Modifier les notes\n+ 8:Annuler\n");
        do{
        printf("+ \033[0;32m=>");
        scanf("%hu",&choix);
        printf("\033[0;33m+-------------------------------------------------+\n");
        }while (choix < 1 && choix > 6);
        switch (choix){
        case 1:
            etud->nom = (char*)realloc(etud->nom,MAX_CARACTERE * sizeof(char));
            if (etud->nom == NULL){Erreur(1);}
            printf("\033[0;33m+ Saisir le nom de l'etudiant :\033[0;32m\n");
            scanf(" %100[^\n]s",etud->nom);
            CapitaliserNom(etud->nom);
            etud->nom = (char*)realloc(etud->nom,(strlen(etud->nom) + 1 ) * sizeof(char));
            break;
        case 2:
            etud->prenom = (char*)realloc(etud->prenom,MAX_CARACTERE * sizeof(char));
            if (etud->prenom == NULL){Erreur(1);}
            printf("\033[0;33m+ Saisir le prenom de l'etudiant :\033[0;32m\n");
            scanf(" %100[^\n]s",etud->prenom);
            CapitaliserNom(etud->prenom);
            etud->prenom = (char*)realloc(etud->prenom,(strlen(etud->prenom) + 1 ) * sizeof(char));
            break;
        case 3:
            printf("\033[0;33m+ Saisir la date d'inscription :\033[0;32m\n");
            lireDate(&etud->date_inscription);
            break;
        case 4:
            FiliereEtudiant(etud);
            break;
        case 5:
            FormationEtudiant(etud);
            break;
        case 6:
            printf("\033[0;33m+ Saisir le groupe de TD :\033[0;32m\n");
            scanf("%hu",&etud->G_TD);
            break;
    
        case 7: ;
            short ajoutnote = 3;
            while (ajoutnote <1 || ajoutnote >2)
            {
                printf("\033[0;33m+ Voulez vous:\n+1:Modifier une note\n+2:Ajouter une note\033[0;32m\n");
                scanf("%hd",&ajoutnote);
            }
            if(!(ajoutnote-1)){editNotes(etud);}
            else{AjouteNote(etud);}
            break;
        case 8:
            break;

        default:
            Erreur(3);
            break;
        }
        printf("\033[0;33m+ Voullez vous modifier plus d'informations?(o/n):\033[0;32m");
        lireBool(&bool);
    }while(bool);
}
