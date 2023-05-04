#include "../headers/structs.h"
#include "../headers/utilitaires.h"
#include "../headers/consultation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> 


// Lire une booleenne (o-O/n-N)
void lireBool(Bool *bool){
    char tmp;
    do
    {
        scanf("%c", &tmp);
        if (tmp == 'o' || tmp == 'O')
        {
            *bool = vrai;
        }
        else if (tmp == 'n' || tmp == 'N')
        {
            *bool = faux;
        }
        
        
    } while (!(tmp == 'o' || tmp == 'O' || tmp == 'n' || tmp == 'N'));
}

// Verifier si l'anner saisie est bissextile
Bool estBissextile(short annee) {
    if ((annee % 4 == 0 && annee % 100 != 0) || annee % 400 == 0) {
        return vrai;
    } else {
        return faux;
    }
}
// Verifier si la date saisie est valide
Bool estDateValide(short jour, short mois, short annee) { 
    int joursDansMois[] = {31, 28 + estBissextile(annee), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (mois < 1 || mois > 12) {
        return faux;
    }
    if (jour < 1 || jour > joursDansMois[mois - 1]) {
        return faux;
    }
    return vrai;
}
// Saisie de la date
void lireDate(Date *date){
    scanf("%hu %hu %hu",&date->jour,&date->mois,&date->annee);
    if (date->annee<100)
    {
        if(date->annee <50)date->annee +=2000;
        else if(date->annee >=50)date->annee +=1900;
    }
    
    while (!estDateValide(date->jour, date->mois, date->annee))
    {
        Erreur(0);
        printf("\t\t\t\t+ \033[0;32m=>");
        scanf("%hu %hu %hu", &date->jour, &date->mois, &date->annee);
    }
}

// Generer une sequence de nombre aleatoire de 7 chiffres
unsigned int NombreAleatoire_7(short year) { 
    unsigned int num;
    time_t t;
    t = time(NULL);
    srand((unsigned) t);
    num = rand() %100000;
    num += (year % 100) * 100000; // Ajout des deux derniers chiffres de l'année
    return num;
}

// Sasie de la filiere de l'etudiant
void FiliereEtudiant(Etudiant *etud){
    do
    {
        printf("\t\t\t\t\033[0;33m+ Saisir la filiere de l'etudiant: \n");
        printf("\t\t\t\t+ 1: SMPC\n\t\t\t\t+ 2: SMC\n\t\t\t\t+ 3: SMP\n\t\t\t\t+ 4: STU\n\t\t\t\t+ 5: SV\n\t\t\t\t+ 6: SVTU\n\t\t\t\t+ 7: SMIA\n\t\t\t\t+ 8: SMA\n\t\t\t\t+ 9: SMI\n");
        printf("\t\t\t\t+ \033[0;32m=>");
        scanf("%hd",&etud->filiere);
    } while (etud->filiere < 1 || etud->filiere > 9);
}

// Saisie du niveau de formation de l'etudiant
void FormationEtudiant(Etudiant *etud){
    do
    {
        printf("\033[0;33m+ Saisir le niveau de formation de l'etudiant\n+ 1: License\n+ 2: Master\n+ 3: Doctorat \n+ \033[0;32m=>");
        scanf(" %hd",&etud->formation);
    }while(etud->formation<1 || etud->formation >3);
}

// Ajouter des notes si possible
void AjouteNote(Etudiant *etud){
    Bool reponse = vrai;
    printf("\033[0;33m+-------------------------------------------------+\n");
    if (etud->nbnotes == MAX_NOTES) {
        printf("+ Vous avez atteint le nombre maximal de notes.\n");
        return;
    }
    while (reponse != faux && etud->nbnotes < MAX_NOTES)
    {
            printf("+ Saisir la note :\033[0;32m");
            scanf("%f",&etud->notes[etud->nbnotes]);
            printf("\033[0;33m");
            etud->nbnotes++;
            etud->moyenne = (etud->moyenne * (etud->nbnotes - 1) + etud->notes[etud->nbnotes - 1]) / etud->nbnotes;
        
        
        if (etud->nbnotes > MAX_NOTES)
        {
            printf("+ Vous avez atteindre le nombre maximal des notes.\n");
            break;
        }
        if (etud->nbnotes < MAX_NOTES)
        {
            printf("+ Voulez-vous ajouter une note? (O/N)\n");
            printf("+ \033[0;32m=>");
            lireBool(&reponse);
            printf("\033[0;33m");
        }
    }
    float moyenne = 0;
    if (0 < etud->nbnotes)
    {
    
        for (int i = 0; i < etud->nbnotes; i++)
        {
            moyenne += etud->notes[i];
        }
        moyenne /= etud->nbnotes;
    }
    etud->moyenne = moyenne;
    if(etud->moyenne <10)etud->redoublant = vrai;
    else if(etud->moyenne >=10)etud->redoublant = faux;
    
    ClearConsole(3);
}

// Convertir la chaîne de caractères nom de l'étudiant en minuscules,tout en maintenant la première lettre de chaque mot en majuscule
void CapitaliserNom(char *string){
    int length = strlen(string);
    if (string[0] >= 'a' && string[0] <= 'z')
    {
        string[0] -= 32;
    }
    for (int i = 1; i < length; i++)
    {
        // Si le caractère est en minuscule (ASCII code >= 'a') et n'est pas un espace (ASCII code = 32)
        if (string[i] >= 'A' && string[i] <= 'Z')
        {
            string[i] += 32; // Convertir la lettre en majiscule
        }
        // Si le caractère précédent est un espace (donc début d'un nouveau mot)
        if (string[i-1] == ' ') 
        {
            if (string[i] >= 'a')// convertir la première lettre du nouveau mot en majuscule en soustrayant 32 de son code ASCII
            {
                string[i] -= 32; // Convertir la lettre en majiscule
            } 
        }   
    }
}


// Lire les donnees de l'etudiant
void LireEtudiant(Etudiant *etud,FILE *fichier, FILE *fichierNote){ 
    etud->nbnotes = 0;
    etud->prenom = (char*)malloc(MAX_CARACTERE * sizeof(char));
    etud->nom = (char*)malloc(MAX_CARACTERE * sizeof(char));
    if (etud->nom == NULL || etud->prenom == NULL){Erreur(1);}
    printf("\033[0;33m+-------------------------------------------------+\n");
    printf("\033[0;33m+ Saisir le nom de l'etudiant : \033[0;32m");
    scanf(" %100[^\n]s",etud->nom);
    etud->nom = (char*)realloc(etud->nom,(strlen(etud->nom) + 1 ) * sizeof(char));
    CapitaliserNom(etud->nom);
    printf("\033[0;33m+ Saisir le prenom de l'etudiant : \033[0;32m");
    scanf(" %100[^\n]s", etud->prenom);
    CapitaliserNom(etud->prenom);
    etud->prenom = (char*)realloc(etud->prenom,(strlen(etud->prenom) + 1 ) * sizeof(char));
    printf("\033[0;33m+ Saisir la date d'inscription de l'etudiant (jj mm aa) : \033[0;32m");
    lireDate(&etud->date_inscription);
    FiliereEtudiant(etud);
    int random = NombreAleatoire_7(etud->date_inscription.annee % 100);
    etud->numApogee = random; // Generer un numero d'appogee de 7 chiffres (2 premiers font reference a l'annee de l'inscription)
    FormationEtudiant(etud);
    printf("\033[0;33m+ Est-ce-que l'etudiant est un redoublant?(O/N): \033[0;32m");
    lireBool(&etud->redoublant);
    printf("\033[0;33m+ Saisir le groupe de TD :\033[0;32m");
    scanf("%hu",&etud->G_TD);
    etud->nbnotes = 0;
    etud->notes = (float*)calloc(MAX_NOTES, sizeof(float));
    etud->moyenne = 0;
    Bool tmp;
    printf("\033[0;33m+ voulez vous ajouter des notes?(o/n) :\033[0;32m");
    lireBool(&tmp);
    if(tmp)AjouteNote(etud);
    SauvegardeEtudiant(*etud, fichier, fichierNote);
    printf("\033[0;33m+-------------------------------------------------+\n");
    ClearConsole(2);
}

// Afficher l'entete du tableau sur la console
void AfficheTabHeader()
{
    printf("\t\t     \033[0;33m+-------------------------------------------------------------------------------------------------------------------------+\n");
    printf("\t\t     | N | Nom            | Prenom         | Apogee | Date d'insciption | Filiere|  Formation   | Redoublant | G-TD | Moyenne  |\n");
    printf("\t\t     |---|----------------|----------------|--------|-------------------|--------|--------------|------------|------|----------|\n");
}

// Afficher les donnees de l'etudiant
void AfficheEtudiant(Etudiant etud){
    printf("\t\t\t\t\033[0;33m+-------------------------------------------------+\n");
    printf("\t\t\t\t+-Nom :\033[0;32m%s\n\033[0;33m",etud.nom);
    printf("\t\t\t\t+-Preom :\033[0;32m%s\033[0;33m\n",etud.prenom);
    printf("\t\t\t\t+-Numero d'apogee: \033[0;32m%07i\033[0;33m\n", etud.numApogee);
    printf("\t\t\t\t+-Date d'inscription : \033[0;32m%hu/%s/%hu\033[0;33m\n", etud.date_inscription.jour, nomMois[etud.date_inscription.mois], etud.date_inscription.annee);
    printf("\t\t\t\t+-Filiere : \033[0;32m%s\033[0;33m\n",Filieres[etud.filiere]);
    printf("\t\t\t\t+-Niveau de formation : \033[0;32m%s \033[0;33m\n",Formations[etud.formation]);
    if (etud.redoublant == 1){printf("\t\t\t\t+-L'etduiant est un \033[0;32mredoublant.\033[0;33m\n");}
    else{printf("\t\t\t\t+-L'etduiant \033[0;32mn'est pas un redoublant.\033[0;33m\n");}
    printf("\t\t\t\t+-Groupe de TD : \033[0;32m%d\033[0;33m\n",etud.G_TD);
    printf("\t\t\t\t+-Les notes de l'etudiant :\033[0;32m");
    for (int i = 0; i < etud.nbnotes; i++){
        printf("  \033[0;33m|\033[0;32m%.3f",etud.notes[i]);
    }
    printf("\n\t\t\t\t\033[0;33m+-La moyenne de l'etudiant : \033[0;32m%f\n",etud.moyenne);
    printf("\t\t\t\t\033[0;33m+-------------------------------------------------+\n");
}

// Appelée quand le programme est lancée, retourne un tableau de tous les etudiants du fichier
Etudiant *tabEtudiants(FILE *fichier,FILE *fichierNote, unsigned int *NPL){ // NPL nummberAndPositionOfLines // !!!
    Etudiant *tab =(Etudiant *)malloc(NPL[0]*sizeof(Etudiant));
    if(tab == NULL){Erreur(1);return NULL;}
    for (unsigned int i = 3; i <= NPL[0]; i++)
    {
        tab[i-3] = lireEtudiantFichier(fichier,fichierNote, NPL[i]);
        tab[i-3].line = i;
    }
    return tab;
}

// Afficher un tableau des etudiants
void afficheTabEtudiants(Etudiant *tab,short size){
    AfficheTabHeader();
    for (short i = 0; i < size; i++)
    {
        printf("\t\t     |\033[0;34m%-3d\033[0;33m",i+1);
        printf("|\033[0;32m%-16.*s\033[0;33m", 16, tab[i].nom);
        printf("|\033[0;32m%-16.*s\033[0;33m", 16, tab[i].prenom);
        printf("|\033[0;32m%07i \033[0;33m", tab[i].numApogee);
        printf("|\033[0;32m %2hd/%-9s/%-5hd\033[0;33m", tab[i].date_inscription.jour, nomMois[tab[i].date_inscription.mois], tab[i].date_inscription.annee);
        printf("|\033[0;32m  %-6s\033[0;33m",Filieres[tab[i].filiere]);
        printf("|\033[0;32m    %-10s\033[0;33m",Formations[tab[i].formation]);
        if (tab[i].redoublant == vrai) {
            printf("| \033[0;32mRedoublant \033[0;33m");}
        else {
            printf("|  \033[0;32mAdmis(e)  \033[0;33m");}
        printf("| \033[0;32mGrp%-2hu\033[0;33m",tab[i].G_TD);
        if (tab[i].moyenne < 10) {
            printf("|\033[0;32m  0%2.3f  \033[0;33m",tab[i].moyenne);}
        else {
            printf("|\033[0;32m  %2.3f  \033[0;33m",tab[i].moyenne);}
        printf("|\n");
    }
    printf("\t\t     +-------------------------------------------------------------------------------------------------------------------------+\n");
}

// Lire les notes des etudiants a partir du fichier des notes
void lireNoteFichier(FILE *fichierNote, Etudiant *etud, short linenbr) {
    rewind(fichierNote);
    short nbr = 1;
    unsigned int tmp_apogee = 0;
    char a;
    char tmp_nom[17], tmp_prenom[17];
    while (nbr != linenbr && (a = getc(fichierNote)) != EOF) {
        if (a == '\n')
            ++nbr;
    }
    char *line =(char *)malloc((_Line+11)*sizeof(char));
    fgets(line,_Line+10,fichierNote);
    float *tab = malloc(6*sizeof(float));
    sscanf(line, "|%16[^|]|%16[^|]|%d | %f | %f | %f | %f | %f | %f |", tmp_nom, tmp_prenom, &tmp_apogee, &tab[0], &tab[1], &tab[2], &tab[3], &tab[4], &tab[5]);
    int i = 0;
    for ( ; i < MAX_NOTES;)
    {
        if (-11111.0 == tab[i])
        {
            break;
        }
        ++i;
    }
    if (0 == i){
        free(tab);
    }
    else if(6 > i){
    tab = (float *)realloc(tab,i*sizeof(float));
    }
    etud->nbnotes = i;
    etud->notes = tab;
}

// Lire un etudiant a partir du fichier
Etudiant lireEtudiantFichier(FILE* fichier , FILE *fichierNote,int line) { //!!!
    Etudiant etud;
    char mois[10];
    char filiere[5];
    char formation_[10];
    char redoublant[11];
    etud.nbnotes = 0;
    etud.prenom = (char*)malloc(MAX_CARACTERE * sizeof(char));
    etud.nom = (char*)malloc(MAX_CARACTERE * sizeof(char));
    
    // Mise du curseur au debut de la ligne convenable
    fseek(fichier,line,SEEK_SET);
    // Lecture des donnees a partir du tableau
    fscanf(fichier,"|%16[^|]|%16[^|]|%d |%2hu/%10s /%4hu |%s |%s |%s | Grp%2hu |%f|", etud.nom, etud.prenom,&etud.numApogee,&etud.date_inscription.jour,mois,&etud.date_inscription.annee,filiere,formation_,redoublant,&etud.G_TD,&etud.moyenne);
    // Association de la chaine de caractere lise au champ convenable (mois,filiere,formation,redoublant)
    for (int i = 1; i < 13; i++){
        if (strcmp(mois,nomMois[i]) == 0){
            etud.date_inscription.mois = i;
        }
    }
    for (int i = 1; i < 10; i++){
        if (strcmp(filiere,Filieres[i]) == 0){
            etud.filiere = i;
        }
    }
    for (int i = 1; i < 4; i++){
        if (strcmp(formation_,Formations[i]) == 0){
            etud.formation = i;
        }
    }
    if (strcmp(redoublant,"Redoublant") == 0){
        etud.redoublant = 1;
    }
    else{
        etud.redoublant = 0;
    }
    etud.notes =(float *)malloc(MAX_NOTES * sizeof(float));
    etud.nbnotes = 0;
    // Calcul du numero de la ligne apartir de la position du curseur
    etud.line = (line/_Line) +1;
    lireNoteFichier(fichierNote, &etud, etud.line);
    return etud;
}


// Afficher l'entete du tableau sur le fichier
void TabHeader(FILE *fichier)
{
    fseek(fichier,0,SEEK_END);
    if (ftell(fichier) == 0) // Tester si le fichier est vide
    {
        fprintf(fichier,"----------------------------------------------------------------------------------------------------------------------\n");
        fprintf(fichier,"| Nom            | Prenom         | Apogee | Date d'insciption | Filere |  Formation   | Redoublant | G-TD | Moyenne |\n");
        fprintf(fichier,"|----------------|----------------|--------|-------------------|--------|--------------|------------|------|---------|\n");
    }
    fseek(fichier,0,SEEK_END);
}

// Afficher l'entete du tableau sur le fichier
void TabHeaderNotes(FILE *fichierNote) // DONE
{
    fseek(fichierNote,0,SEEK_END);
    if (ftell(fichierNote) == 0) // Tester si le fichier est vide
    {
        fprintf(fichierNote,"--------------------------------------------------");
        for (int i = 0; i < MAX_NOTES; i++)
        {
            fprintf(fichierNote,"--------");
        }
        fprintf(fichierNote,"\n");
        fprintf(fichierNote,"| Nom            ");
        fprintf(fichierNote,"| Prenom         ");
        fprintf(fichierNote,"| Apogee |");
        for (int i = 0; i < MAX_NOTES; i++)
        {
            fprintf(fichierNote," Note %d |",i+1);
        }
        fprintf(fichierNote,"\n");
        fprintf(fichierNote,"|----------------|----------------|--------|");
        for (int i = 0; i < MAX_NOTES; i++)
        {
            fprintf(fichierNote,"--------|");
        }
        fprintf(fichierNote,"\n");
    }
    fseek(fichierNote,0,SEEK_END);
}

// Sauvgarder les notes d'un etudiant dans un fichier externe
void sauvgardeNotes(Etudiant etud,FILE *fichierNote){ //!!!
    TabHeaderNotes(fichierNote);
    fprintf(fichierNote,"|%-16.*s", 16, etud.nom);
    fprintf(fichierNote,"|%-16.*s", 16, etud.prenom);
    fprintf(fichierNote,"|%07i |", etud.numApogee);
    for (short i = 0; i < MAX_NOTES; i++)
    {
        if (i < etud.nbnotes)
        {
            fprintf(fichierNote, " %06.3f |",etud.notes[i]);
        }
        else
        {
            fprintf(fichierNote, " -11111 |");
        }
    }
    fprintf(fichierNote,"\n");
}
// Sauvegarder les donnees de l'etudiant dans un fichier externe
void SauvegardeEtudiant(Etudiant etud,FILE *fichier, FILE *fichierNote){ // !!!
    TabHeader(fichier);
    fprintf(fichier,"|%-16.*s", 16, etud.nom);
    fprintf(fichier,"|%-16.*s", 16, etud.prenom);
    fprintf(fichier,"|%07i ", etud.numApogee);
    fprintf(fichier,"| %2hd/%-9s/%-5hd", etud.date_inscription.jour, nomMois[etud.date_inscription.mois], etud.date_inscription.annee);
    fprintf(fichier,"|  %-6s",Filieres[etud.filiere]);
    fprintf(fichier,"|    %-10s",Formations[etud.formation]);
    if (etud.redoublant == vrai){
    fprintf(fichier,"| Redoublant ");
    }
    else{
    fprintf(fichier,"|  Admis(e)  ");
    }
    fprintf(fichier,"| Grp%-2hu",etud.G_TD);
    fprintf(fichier,"|");
    if (etud.moyenne < 10) fprintf(fichier," 0%2.3f  ",etud.moyenne);
    else fprintf(fichier," %02.3f  ",etud.moyenne);
    fprintf(fichier,"|\n");
    sauvgardeNotes(etud, fichierNote);
}