#include "../headers/structs.h"
#include "../headers/utilitaires.h"
#include "../headers/consultation.h"
#include "../headers/modification.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Modifier les notes de l'etudiant
void editNotes(Etudiant *etud){ 
    int noteIndex;
    float oldNote;
    printf("\t\t\t\t\t\t\t\033[0;36m+-----------------------------------------------+\n");
    do{
        printf("\t\t\t\t\t\t\t+\033[0;33m Quelle est la note que vous souhaitez changer?\033[0;36m+\n");
        for (int i = 0; i < etud->nbnotes; i++){
            printf("\t\t\t\t\t\t\t\033[0;36m+\033[0;33m %d: %f\t\t\t\t\t\033[0;36m+\n", i, etud->notes[i]);
        }
        printf("\t\t\t\t\t\t\t\033[0;36m+\033[0;33m %d: Annuler.\t\t\t\t\t\033[0;36m+\n", etud->nbnotes);
        printf("\t\t\t\t\t\t\t\033[0;36m+-----------------------------------------------+\n");
        entrerDonnee();
        scanf("%d", &noteIndex);
    } while (noteIndex < 0 || noteIndex > etud->nbnotes);
    if (noteIndex != etud->nbnotes)
    {
        oldNote = etud->notes[noteIndex];
        printf("\t\t\t\t\t\t\t\033[0;36m+\033[0;33m  Veuillez saisir la nouvelle valeur : \n");
        entrerDonnee();
        scanf("%f", &etud->notes[noteIndex]);
        etud->moyenne = etud->moyenne + ((etud->notes[noteIndex] - oldNote) / etud->nbnotes);
    }
    if(etud->moyenne <10)etud->redoublant = vrai;
    if(etud->moyenne >=10)etud->redoublant = faux;
}

// Modifier les informations de l'etudiant a partir des fichiers
void editEtudiantFile(Etudiant* tab_etud, FILE **fichier, FILE **fichierNote, short tab_size){
    short num;
    FILE *tmp = fopen("data/tmp.txt","w+"); // Fichier temporaire ou les donnees modifiees seront ajoutees
    FILE *tmp_notes = fopen("data/tmp_notes.txt","w+"); // Fichier temporaire ou les motes modifiees seront ajoutees
    TesterFichier(tmp);
    TesterFichier(tmp_notes);
    afficheTabEtudiants(tab_etud, tab_size);
    printf("\t\t\t\t\t\t\033[0;36m+\033[0;33m Entrez le numero de l'etudiant que vous souhaitez modifier ses informations: \n");
    do
    {
        entrerDonnee();
        scanf("%hd", &num);
        if (num <= 0 || num > tab_size){
            Erreur(3);
        }
    } while (num <= 0 || num > tab_size);
    EditEtudiant(&tab_etud[num-1]);
    afficheTabEtudiants(tab_etud, tab_size);
    for (int i = 0; i < tab_size ; i++){
        SauvegardeEtudiant(tab_etud[i], tmp, tmp_notes);
    }
    printf("\t\t\t\t\t\t\033[0;36m+\033[0;32m (+) Votre modification a ete sauvegarde avec succes.\n");
    sleep(2);
    ClearConsole(0);
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
void EditEtudiant(Etudiant *etud){ 
    short int choix;
    Bool bool = 0;
    do{
        fflush(stdin);
        printf("\t\t\t\t\t\t\033[0;36m+-----------------------------------------------------------------------+\n");
        printf("\t\t\t\t\t\t+\033[0;33m Quelle information souhaitez-vous modifier:\t\t\t\t\033[0;36m+ \n");
        printf("\t\t\t\t\t\t+\033[0;33m 1:Modifier le nom.\t\t\t\t\t\t\t\033[0;36m+\n");
        printf("\t\t\t\t\t\t+\033[0;33m 2:Modifier le prenom.       \t\t\t\t\t\t\033[0;36m+\n");
        printf("\t\t\t\t\t\t+\033[0;33m 3:Modifier la date d'inscription.   \t\t\t\t\t\033[0;36m+\n");
        printf("\t\t\t\t\t\t+\033[0;33m 4:Modifier la filiere.      \t\t\t\t\t\t\033[0;36m+\n");
        printf("\t\t\t\t\t\t+\033[0;33m 5:Modifier le niveau de formation.  \t\t\t\t\t\033[0;36m+\n");
        printf("\t\t\t\t\t\t+\033[0;33m 6:Modifier le groupe de TD. \t\t\t\t\t\t\033[0;36m+\n");
        printf("\t\t\t\t\t\t+\033[0;33m 7:Modifier les notes.       \t\t\t\t\t\t\033[0;36m+\n");
        printf("\t\t\t\t\t\t+\033[0;33m 8:Annuler.  \t\t\t\t\t\t\t\t\033[0;36m+\n");
        printf("\t\t\t\t\t\t\033[0;36m+-----------------------------------------------------------------------+\n");
        do{
        entrerDonnee();
        scanf("%hu",&choix);
        }while (choix < 1 && choix > 6);
        switch (choix){
        case 1:
            etud->nom = (char*)realloc(etud->nom,MAX_CARACTERE * sizeof(char));
            if (etud->nom == NULL){Erreur(1);}
            printf("\t\t\t\t\t\t\033[0;36m+ \033[0;33mVeuillez saisir le nom de l'etudiant:\033[0;36m\n");
            entrerDonnee();
            scanf(" %100[^\n]s",etud->nom);
            CapitaliserNom(etud->nom);
            etud->nom = (char*)realloc(etud->nom,(strlen(etud->nom) + 1 ) * sizeof(char));
            break;
        case 2:
            etud->prenom = (char*)realloc(etud->prenom,MAX_CARACTERE * sizeof(char));
            if (etud->prenom == NULL){Erreur(1);}
            printf("\t\t\t\t\t\t\033[0;36m+ \033[0;33mVeuillez saisir le prenom de l'etudiant:\033[0;36m\n");
            entrerDonnee();
            scanf(" %100[^\n]s",etud->prenom);
            CapitaliserNom(etud->prenom);
            etud->prenom = (char*)realloc(etud->prenom,(strlen(etud->prenom) + 1 ) * sizeof(char));
            break;
        case 3:
            printf("\t\t\t\t\t\t\033[0;36m+ \033[0;33mVeuillez saisir la date d'inscription :\033[0;36m\n");
            entrerDonnee();
            lireDate(&etud->date_inscription);
            break;
        case 4:
            FiliereEtudiant(etud);
            break;
        case 5:
            FormationEtudiant(etud);
            break;
        case 6:
            printf("\t\t\t\t\t\t\033[0;36m+ \033[0;33mVeuillez saisir le groupe de TD :\033[0;36m\n");
            entrerDonnee();
            scanf("%hu",&etud->G_TD);
            break;
    
        case 7: ;
            short ajoutnote;
            printf("\t\t\t\t\t\t\033[0;36m+-----------------------------------------------------------------------+\n");
            printf("\t\t\t\t\t\t\033[0;36m+ \033[0;33mVoulez vous:\t\t\t\t\t\t\t\t\033[0;36m+\n");
            printf("\t\t\t\t\t\t+\033[0;33m 1:Modifier une note?  \t\t\t\t\t\t\033[0;36m+\n");
            printf("\t\t\t\t\t\t+\033[0;33m 2:Ajouter une note?  \t\t\t\t\t\t\t\033[0;36m+\n");
            printf("\t\t\t\t\t\t\033[0;36m+-----------------------------------------------------------------------+\n");
            do{
                entrerDonnee();
                scanf("%hd",&ajoutnote);
                if (ajoutnote <1 || ajoutnote >2){
                    Erreur(3);
                }
                
            }while (ajoutnote <1 || ajoutnote >2);
            if(!(ajoutnote-1)){editNotes(etud);}
            else{AjouteNote(etud);}
            break;
        case 8:
            break;

        default:
            Erreur(3);
            break;
        }
        printf("\t\t\t\t\t\t\033[0;36m+ \033[0;33mVoullez-vous modifier plus d'informations?(o/n):\n");
        lireBool(&bool);
    }while(bool);
}
