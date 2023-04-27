#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> 

#define MAX_CARACTERE 120 
#define _Line 120
#define ALPHABET_SIZE 32
#define MAX_NOTES 6
#define FICHIERDATA "test.txt"
#define FICHIERNOTES "notes.txt"

// Definition d'enumeration booleenne
typedef enum Bool{faux, vrai}Bool;
// Definition de structure de date
typedef struct Date
{
    short int mois, jour, annee;
}Date;
// Affiche les mois par leur nom
const char* nomMois[] = {"","Janvier", "Fevrier", "Mars", "Avril", "Mai", "Juin", "Juillet", "Aout", "Septembre", "Octobre", "Novembre", "Decembre"};
// Affiche le nom de la filiere
const char* Filieres[] = {"","SMPC","SMC","SMP","STU","SV","SVTU","SMIA","SMA","SMI"};
//affichage du formation
const char* Formations[] = {"","License", "Master", "Doctorat"};

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

void AjouteNote(Etudiant*);
void sauvgardeNotes(Etudiant, FILE*);
void lireNoteFichier(FILE*, Etudiant*,short);
void SauvegardeEtudiant(Etudiant,FILE*, FILE*);
void editEtudiantFile(Etudiant*,FILE**,FILE**,short);

// Nettoyage de la console
void ClearConsole(short n) //DONE
{
    for (int i = 0; i < n; i++) {
        // Vider la console
        system("clear");

        printf("Traitement des donnees saisies... %d/%d\n", i+1,n);

        // pauser le programme pour une seconde
        sleep(0);
    }
    system("clear");
}

// Message d'erreur
void Erreur(int err) //DONE
{
    if (err == 0){printf("+-\033[0;31mErreur: Mal saisie de donnees!\033[0;33m\n"); return;}
    if (err == 1){printf("+-\033[0;31mErreur: allocation de memoire a echoué!\033[0;33m\n"); return;}
    if (err == 2){printf("+-\033[0;31mErreur: Ouverture du fichier a echoué!\033[0;33m\n"); return;}
    if (err == 3){printf("\033[0;31m+ Veuillez entrer un choix valable\033[0;32m\n"); return;}
}

// Tester l'ouverture du fichier
int TesterFichier(FILE *fichier){
    if (fichier == NULL)
    {
        Erreur(3);
        exit(0);
    }
    return 0;
}
// Lire une booleenne (o-O/n-N)
void lireBool(Bool *bool){ //DONE
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
Bool estBissextile(short annee) { //DONE 
    if ((annee % 4 == 0 && annee % 100 != 0) || annee % 400 == 0) {
        return vrai;
    } else {
        return faux;
    }
}
// Verifier si la date saisie est valide
Bool estDateValide(short jour, short mois, short annee) { //DONE
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
void lireDate(Date *date){ //DONE
    scanf("%hu %hu %hu",&date->jour,&date->mois,&date->annee);
    if (date->annee<100)
    {
        if(date->annee <50)date->annee +=2000;
        else if(date->annee >=50)date->annee +=1900;
    }
    
    while (!estDateValide(date->jour, date->mois, date->annee))
    {
        Erreur(0);
        printf("+ \033[0;32m=>");
        scanf("%hu %hu %hu", &date->jour, &date->mois, &date->annee);
    }
}

// Generer une sequence de nombre aleatoire de 7 chiffres
int NombreAleatoire_7(short year) { //DONE
    unsigned int num;
    time_t t;
    t = time(NULL);
    srand((unsigned) t);
    num = rand() %100000;
    num += (year % 100) * 100000; // Ajout des deux derniers chiffres de l'année
    return num;
}

// Sasie de la filiere de l'etudiant
void FiliereEtudiant(Etudiant *etud){ //DONE
    do
    {
        printf("\033[0;33m+ Saisir la filiere de l'etudiant: \n");
        printf("+ 1: SMPC\n+ 2: SMC\n+ 3: SMP\n+ 4: STU\n+ 5: SV\n+ 6: SVTU\n+ 7: SMIA\n+ 8: SMA\n+ 9: SMI\n+ \033[0;32m=>");
        scanf("%hd",&etud->filiere);
    } while (etud->filiere < 1 || etud->filiere > 9);
}

// Saisie du niveau de formation de l'etudiant
void FormationEtudiant(Etudiant *etud){// !!!
    do
    {
        printf("\033[0;33m+ Saisir le niveau de formation de l'etudiant\n+ 1: License\n+ 2: Master\n+ 3: Doctorat \n+ \033[0;32m=>");
        scanf(" %hd",&etud->formation);
    }while(etud->formation<1 || etud->formation >3);
}

// Convertir la chaîne de caractères nom de l'étudiant en minuscules,tout en maintenant la première lettre de chaque mot en majuscule
void CapitaliserNom(char *string){//DONE
    int lengh = strlen(string);
    if (string[0] > 'a')
    {
        string[0] -= 32;
    }
    for (int i = 1; i < lengh; i++)
    {
        // Si le caractère est une majuscule (ASCII code <= 'a') et n'est pas un espace (ASCII code = 32)
        if (string[i] < 'a' && string[i] > '9')
        {
            string[i] += 32;
        }
        // Si le caractère précédent est un espace (donc début d'un nouveau mot)
        if (string[i-1] == ' ') 
        {
            if (string[i] >= 'a')// convertir la première lettre du nouveau mot en majuscule en soustrayant 32 de son code ASCII
                {
                    string[i] -= 32;
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

// Modifier les notes de l'etudiant
void editNotes(Etudiant *etud){ //XXX
    short noteIndex;
    float oldNote;
    printf("\033[0;33m+-------------------------------------------------+\n");
    do{
        printf("+ Quelle est la note que vous souhaitez changer?\033[0;32m\n");
        for (int i = 0; i < etud->nbnotes; i++){
            printf("\033[0;33m+ %d: %f\n", i, etud->notes[i]);
        }
        printf("+ %hu: Annuler.\n\033[0;32m", etud->nbnotes);
        printf("+ =>");
        scanf("%hu", &noteIndex);
    printf("\033[0;33m+-------------------------------------------------+\n");
    } while (noteIndex < 0 || noteIndex > etud->nbnotes);
    if (noteIndex != etud->nbnotes)
    {
        oldNote = etud->notes[noteIndex];
        printf("\033[0;33m+ Veuillez saisir la nouvelle valeur : \033[0;32m");
        scanf("%f", &etud->notes[noteIndex]);
        etud->moyenne = etud->moyenne + ((etud->notes[noteIndex] - oldNote) / etud->nbnotes);
    }
    printf("\033[0;33m+-------------------------------------------------+\n");
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
            printf("+ Vous avez depasser le nombre maximal des notes.\n");
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
    ClearConsole(3);
}

// Modifier les donnees de l'etudiant
void EditEtudiant(Etudiant *etud){
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

// Afficher l'entete du tableau dans le fichier des etudiants
void TabHeader(FILE *fichier) // DONE
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

// Afficher l'entete du tableau sur la console
void AfficheTabHeader()
{
    printf("\033[0;33m-------------------------------------------------------------------------------------------------------------------------\n");
    printf("| N | Nom            | Prenom         | Apogee | Date d'insciption | Filiere|  Formation   | Redoublant | G-TD | Moyenne |\n");
    printf("|---|----------------|----------------|--------|-------------------|--------|--------------|------------|------|---------|\n");
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
    fprintf(fichier,"| ~~~~~~~~~~ ");
    }
    fprintf(fichier,"| Grp%-2hu",etud.G_TD);
    fprintf(fichier,"|");
    fprintf(fichier," %06.3f  ",etud.moyenne);
    fprintf(fichier,"|\n");
    sauvgardeNotes(etud, fichierNote);
}

// Sauvgarder les notes d'un etudiant dans un fichier externe
void sauvgardeNotes(Etudiant etud,FILE *fichierNote){ //!!!
    TabHeaderNotes(fichierNote);
    fprintf(fichierNote,"|%-16.*s", 16, etud.nom);
    fprintf(fichierNote,"|%-16.*s", 16, etud.prenom);
    fprintf(fichierNote,"|%07i |", etud.numApogee);
    for (short i = 1; i <= MAX_NOTES; i++)
    {
        if (i < etud.nbnotes)
        {
            fprintf(fichierNote, "  %05.2f |",etud.notes[i]);
        }
        else
        {
            fprintf(fichierNote, " -11111 |");
        }
    }
    fprintf(fichierNote,"\n");
}

// Afficher les donnees de l'etudiant
void AfficheEtudiant(Etudiant etud){ //DONE
    printf("\033[0;33m+-------------------------------------------------+\n");
    printf("+-Nom :\033[0;32m%s\n\033[0;33m",etud.nom);
    printf("+-Preom :\033[0;32m%s\033[0;33m\n",etud.prenom);
    printf("+-Numero d'apogee: \033[0;32m%-7i\033[0;33m\n", etud.numApogee);
    printf("+-Date d'inscription : \033[0;32m%hu/%s/%hu\033[0;33m\n", etud.date_inscription.jour, nomMois[etud.date_inscription.mois], etud.date_inscription.annee);
    printf("+-Filiere : \033[0;32m%s\033[0;33m\n",Filieres[etud.filiere]);
    printf("+-Niveau de formation : \033[0;32m%s \033[0;33m\n",Formations[etud.formation]);
    if (etud.redoublant == 0){printf("+-L'etduiant est un \033[0;32mredoublant.\033[0;33m\n");}
    else{printf("+-L'etduiant \033[0;32mn'est pas un redoublant.\033[0;33m\n");}
    printf("+-Groupe de TD : \033[0;32m%d\033[0;33m\n",etud.G_TD);
    printf("+-Les notes de l'etudiant :\033[0;32m");
    for (int i = 0; i < etud.nbnotes; i++){
    printf("\t%.3f",etud.notes[i]);
    }
    printf("\033[0;33m\n+-La moyenne de l'etudiant :\033[0;32m%f",etud.moyenne);
    printf("\033[0;33m\n");
}

// Position du premier characteres pour chaque ligne pour des raisons d'affichage
int* NombrePositionLigne(FILE* fichier) {
    rewind(fichier);
    int lineCount = 0;
    int* array = malloc((lineCount + 1) * sizeof(int));
    array[0] = 0;
    char ch;
    while ((ch = fgetc(fichier)) != EOF) {
        if (ch == '\n') {
            lineCount++;
            array = realloc(array, (lineCount + 1) * sizeof(int));
            array[lineCount] = ftell(fichier);
        }
    }
    --lineCount;
    array = realloc(array, (lineCount + 1) * sizeof(int));
    array[0] = lineCount;
    return array;
}

// Afficher une ligne a partir de sa position
void AfficheLigne(FILE *file,int linePos){ //DONE
    fseek(file,linePos,SEEK_SET);
    char line[MAX_CARACTERE];
    fgets(line,MAX_CARACTERE,file);
    printf("%s",line);
}

// Afficher un tableau de lignes (Premier element du tableau est sa taille)
void AfficheTabLignes(FILE *file,int *NPL){ //DONE
    ClearConsole(2);
    AfficheTabHeader();
    for (int i = 3; i <= NPL[0]; i++)//first element of NPL is size of NPL
    {
        AfficheLigne(file, NPL[i]);
    }
    printf("----------------------------------------------------------------------------------------------------------------------\n");
}

/* Rechercher les etudiants par noms ou prenoms 
!elle retourne un tableau dans le premier element est le nombre des element du tableau et chaque element correspand a la position d'une ligne */
int* RechercheEtudiant_Nom_Prenom(FILE *fp){ //DONE
    int *array = (int *) malloc(sizeof(int));
    int *linePositions = NombrePositionLigne(fp),lineCount = 0;
    char key[17], src[35], line[MAX_CARACTERE];
    printf("\033[0;33m+-------------------------------------------------+\n");
    printf("+ Veuillez saisir le nom ou le prenom a chercher: \n");
    printf("+ \033[0;32m=>");
    scanf("%16s",key);
    printf("\033[0;33m");
    for (int i = 3; i < linePositions[0]+1; i++)
    {
        fseek(fp,linePositions[i], SEEK_SET);
        fgets(line,MAX_CARACTERE,fp);
        strncpy(src, line, 34);
        if (strstr(src, key)!=NULL)
        {
            if (lineCount%5 == 0)
            {
                array = realloc(array, (lineCount + 2)*sizeof(int));
            }
            ++lineCount;
            array[lineCount] = linePositions[i];
        }
    }
    array[0] = lineCount;
    free(linePositions);
    return array;
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
    fscanf(fichier,"|%16[^|]|%16[^|]|%07i |%2hu/%10s /%4hu |%s |%s |%s | Grp%2hu |%f|", etud.nom, etud.prenom,&etud.numApogee,&etud.date_inscription.jour,mois,&etud.date_inscription.annee,filiere,formation_,redoublant,&etud.G_TD,&etud.moyenne);
    // Association de la chaine de caractere lise au champ convenable (mois,filiere,formation,redoublant)
    for (int i = 1; i < 13; i++)
    {
        if (strcmp(mois,nomMois[i]) == 0)
        {
            etud.date_inscription.mois = i;
        }
    }
    for (int i = 1; i < 10; i++)
    {
        if (strcmp(filiere,Filieres[i]) == 0)
        {
            etud.filiere = i;
        }
    }
    for (int i = 1; i < 4; i++)
    {
        if (strcmp(formation_,Formations[i]) == 0)
        {
            etud.formation = i;
        }
    }
    if (strcmp(redoublant,"Redoublant") == 0)
    {
        etud.redoublant = 1;
    }
    else
    {
        etud.redoublant = 0;
    }
    etud.notes =(float *) malloc(MAX_NOTES * sizeof(int));
    etud.nbnotes = 0;
    // Calcul du numero de la ligne apartir de la position du curseur
    etud.line = (line/_Line) + 1;
    lireNoteFichier(fichierNote, &etud, etud.line);
    return etud;
}

// Lire les notes des etudiants a partir du fichier des notes
void lireNoteFichier(FILE *fichierNote, Etudiant *etud, short linenbr) {
    fseek(fichierNote, 0, SEEK_SET);
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
    sscanf(line, "|%16[^|]|%16[^|]|%07i | %f | %f | %f | %f | %f | %f |", tmp_nom, tmp_prenom, &tmp_apogee, &tab[0], &tab[1], &tab[2], &tab[3], &tab[4], &tab[5]);
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

    printf("\n");
}


// Appelée quand le programme est lancée, retourne un tableau de tous les etudiants du fichier
Etudiant *tabEtudiants(FILE *fichier,FILE *fichierNote, int *NPL){ // NPL nummberAndPositionOfLines // !!!
    Etudiant *tab =(Etudiant *)malloc(NPL[0]*sizeof(Etudiant));
    if(tab == NULL){Erreur(1);return NULL;}
    for (int i = 3; i <= NPL[0]; i++)
    {
        tab[i-3] = lireEtudiantFichier(fichier,fichierNote, NPL[i]);
        tab[i-3].line = i;
    }
    return tab;
}
// Afficher un tableau des etudiants
void afficheTabEtudiants(Etudiant *tab,short size){
    AfficheTabHeader();
    for (int i = 0; i < size - 2; i++)
    {
        CapitaliserNom(tab[i].nom);
        CapitaliserNom(tab[i].prenom);
        printf("|\033[0;34m%-3d\033[0;33m",tab[i].line-2);
        printf("|\033[0;32m%-16.*s\033[0;33m", 16, tab[i].nom);
        printf("|\033[0;32m%-16.*s\033[0;33m", 16, tab[i].prenom);
        printf("|\033[0;32m%07i \033[0;33m", tab[i].numApogee);
        printf("|\033[0;32m %2hd/%-9s/%-5hd\033[0;33m", tab[i].date_inscription.jour, nomMois[tab[i].date_inscription.mois], tab[i].date_inscription.annee);
        printf("|\033[0;32m  %-6s\033[0;33m",Filieres[tab[i].filiere]);
        printf("|\033[0;32m    %-10s\033[0;33m",Formations[tab[i].formation]);
        if (tab[i].redoublant == vrai){
        printf("| \033[0;32mRedoublant \033[0;33m");
        }
        else{
        printf("| \033[0;32m~~~~~~~~~~ \033[0;33m");
        }
        printf("| \033[0;32mGrp%-2hu\033[0;33m",tab[i].G_TD);
        printf("|\033[0;32m %06.3f  \033[0;33m",tab[i].moyenne);
        for (int j = 0; j < tab[i].nbnotes; ++j)
        {
            printf("| \033[0;32m %06.3f \033[0;33m",tab[i].notes[j]);
        }
        printf("|\n");
        }
        printf("--------------------------------------------------------------------------------------------------------------------------\n");
}

// Supprimer un etudiant du fichier
void suprimerEtudiant(FILE **fichier, FILE **fichierNote,Etudiant etud){ // !!!
    int lineToDelete = etud.line;
    FILE *tmp = fopen("tmp.txt","w+");
    if (tmp == NULL){Erreur(3);return;}
    rewind(*fichier);
    int count = 1;
    char ch;
    while ((ch = fgetc(*fichier)) != EOF) {
        if (ch == '\n') {
            count++;
        }
        // ecrire la ligne dans le fichier temporaire sauf s'il est la lignne a suprime
        if (count != lineToDelete) {
            fputc(ch, tmp);
        }
    }
    fclose(*fichier);
    fclose(tmp);
    remove(FICHIERDATA);
    rename("tmp.txt", FICHIERDATA);
    *fichier = fopen(FICHIERDATA,"a+");
    
    tmp = fopen("tmp.txt","w+");
    if (tmp == NULL){Erreur(3);return;}
    rewind(*fichierNote);
    count = 1;
    while ((ch = fgetc(*fichierNote)) != EOF){
        if (ch == '\n') {
            count++;
        }
        // ecrire la ligne dans le fichier temporaire sauf s'il est la lignne a suprime
        if (count != lineToDelete) {
            fputc(ch, tmp);
        }
    }
    fclose(*fichierNote);
    fclose(tmp);
    remove(FICHIERNOTES);
    rename("tmp.txt", FICHIERNOTES);
    *fichierNote = fopen(FICHIERNOTES,"a+");  
}


// Modifier les informations de l'etudiant a partir des fichiers
void editEtudiantFile(Etudiant* tab_etud,FILE **fichier,FILE **fichierNote,short tab_size){
    short num;
    FILE *tmp = fopen("tmp.txt","w+"); // Fichier temporaire ou les donnees modifiees seront ajoutees
    FILE *tmp_notes = fopen("tmp_notes.txt","w+"); // Fichier temporaire ou les motes modifiees seront ajoutees
    TesterFichier(tmp);
    TesterFichier(tmp_notes);
    afficheTabEtudiants(tab_etud,tab_size);
    printf("+ \033[0;33mEntrez le numero de l'etudiant que vous souhaiter modifier ses information: \n");
    do
    {
        printf("+ \033[0;32m=>");
        scanf("%hd",&num);
    } while (num <= 0 || num > tab_size - 2);
    EditEtudiant(&tab_etud[num-1]);
    afficheTabEtudiants(tab_etud,tab_size);
    for (int i = 0; i < tab_size - 2; i++)
    {
        SauvegardeEtudiant(tab_etud[i],tmp,tmp_notes);
    }
    fclose(*fichier);
    fclose(*fichierNote);
    fclose(tmp);
    fclose(tmp_notes);
    remove(FICHIERDATA);
    remove(FICHIERNOTES);
    rename("tmp.txt", FICHIERDATA);
    rename("tmp_notes.txt", FICHIERNOTES);
    *fichier = fopen(FICHIERDATA,"a+");
    TesterFichier(*fichier);
    *fichierNote= fopen(FICHIERNOTES, "a+");
    TesterFichier(*fichierNote);
    
}

// Trier les etudiant par nom
void trierTabEtudiantsParNom(Etudiant *tab, int size){
    Etudiant tmp;
    for (int i = 0; i < size; i++)
    {
        for (int j = i+1; j < size; j++)
        {
            if (strcmp(tab[i].nom,tab[j].nom) > 0)
            {
                tmp = tab[i];
                tab[i] = tab[j];
                tab[j] = tmp;
            }
        }
    }
}

// Trier les etudiant par prenom
void trierTabEtudiantsParPreom(Etudiant *tab, int size){
    Etudiant tmp;
    for (int i = 0; i < size; i++)
    {
        for (int j = i+1; j < size; j++)
        {
            if (strcmp(tab[i].prenom,tab[j].prenom) > 0)
            {
                tmp = tab[i];
                tab[i] = tab[j];
                tab[j] = tmp;
            }
        }
    }
}

// Trier les etudiant selon le numero apgee
void trierTabEtudiantsParApogee(Etudiant *tab, int size){
    Etudiant tmp;
    for (int i = 0; i < size; i++)
    {
        for (int j = i+1; j < size; j++)
        {
            if (tab[i].numApogee > tab[j].numApogee)
            {
                tmp = tab[i];
                tab[i] = tab[j];
                tab[j] = tmp;
            }   
        }
    }
}

// Trier les etudiant selon la moyenne
void trierTabEtudiantsParMoyenne(Etudiant *tab, int size){
    Etudiant tmp;
    for (int i = 0; i < size; i++)
    {
        for (int j = i+1; j < size; j++)
        {
            if (tab[i].moyenne > tab[j].moyenne)
            {
                tmp = tab[i];
                tab[i] = tab[j];
                tab[j] = tmp;
            }
        }
    }
}

// Trier les etudiant par date d'inscription
void trierTabEtudiantsParDate(Etudiant *tab, int size){
    Etudiant tmp;
    for (int i = 0; i < size; i++)
    {
        for (int j = i+1; j < size; j++)
        {
            if (tab[i].date_inscription.annee > tab[j].date_inscription.annee)
            {
                tmp = tab[i];
                tab[i] = tab[j];
                tab[j] = tmp;
                continue;
            }
            if (tab[i].date_inscription.annee < tab[j].date_inscription.annee){continue;}
            
            if (tab[i].date_inscription.mois > tab[j].date_inscription.mois)
            {
                tmp = tab[i];
                tab[i] = tab[j];
                tab[j] = tmp;
                continue;
            }
            if (tab[i].date_inscription.mois < tab[j].date_inscription.mois){continue;}
            
            if (tab[i].date_inscription.jour <= tab[j].date_inscription.jour){continue;}
            tmp = tab[i];
            tab[i] = tab[j];
            tab[j] = tmp;
            continue;
            
        }
    }
}

// Trier les etudiant par la filiere
int filtrerEtudiantsFiliere(Etudiant *originalTab,int originalTabSize,int filiere,Etudiant **destinationTabPtr){
    Etudiant *destinationTab = NULL;
    int index=0;
    for (int i = 0; i < originalTabSize; ++i)
    {
        if (originalTab[i].filiere == filiere)
        {

            destinationTab = realloc(destinationTab,(index+1)* sizeof(Etudiant));
            destinationTab[index] = originalTab[i];
            index++;
        }
    }
    *destinationTabPtr = destinationTab;
    return index;
}

// Trier les etudiant par niveau de formation
int filtrerEtudiantsFormation(Etudiant *originalTab,int originalTabSize,int formation,Etudiant **destinationTabPtr){
    Etudiant *destinationTab = NULL;
    int index=0;
    for (int i = 0; i < originalTabSize; ++i)
    {
        if (originalTab[i].formation == formation)
        {

            destinationTab = realloc(destinationTab,(index+1)* sizeof(Etudiant));
            destinationTab[index] = originalTab[i];
            index++;
        }
    }
    *destinationTabPtr = destinationTab;
    return index;
}

// Trier les etudiant par admission
int filtrerEtudiantsRedoublant(Etudiant *originalTab,int originalTabSize,Bool redoublant,Etudiant **destinationTabPtr){
    Etudiant *destinationTab = NULL;
    int index=0;
    for (int i = 0; i < originalTabSize; ++i)
    {
        if (originalTab[i].redoublant == redoublant)
        {

            destinationTab = realloc(destinationTab,(index+1)* sizeof(Etudiant));
            destinationTab[index] = originalTab[i];
            index++;
        }
    }
    *destinationTabPtr = destinationTab;
    return index;
}

// Trier les etudiants selon groupe de TD
int filtrerEtudiantsG_TD(Etudiant *originalTab,int originalTabSize,int G_TD,Etudiant **destinationTabPtr){
    Etudiant *destinationTab = NULL;
    int index=0;
    for (int i = 0; i < originalTabSize; ++i)
    {
        if (originalTab[i].G_TD == G_TD)
        {
            
            destinationTab = realloc(destinationTab,(index+1)* sizeof(Etudiant));
            destinationTab[index] = originalTab[i];
            index++;
        }
    }
    *destinationTabPtr = destinationTab;
    return index;
}

// Programme principal de test
int main()
{
    FILE *fichier= fopen(FICHIERDATA, "a+");
    TesterFichier(fichier);
    FILE *fichierNote= fopen(FICHIERNOTES, "a+");
    TesterFichier(fichierNote);
    int *NPL = NombrePositionLigne(fichier);
    Etudiant *tab = tabEtudiants(fichier,fichierNote,NPL);
    editEtudiantFile(tab,&fichier,&fichierNote,NPL[0]);
    
    printf("\033[0;37m");
    return 0;
}