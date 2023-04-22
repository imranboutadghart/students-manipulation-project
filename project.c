#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> 

#define MAX_CARACTERE 120 
#define _Line 119

// Definition d'enumeration booleenne
typedef enum Bool{faux, vrai}Bool;
// Definition de structure de date
typedef struct Date
{
    short int annee;
    short int mois;
    short int jour;
}Date;
// Affiche les mois par leur nom
const char* nomMois[] = {"","Janvier", "Fevrier", "Mars", "Avril", "Mai", "Juin", "Juillet", "Aout", "Septembre", "Octobre", "Novembre", "Decembre"};
// Affiche le nom de la filiere
const char* Filieres[] = {"","SMPC","SMC","SMP","STU","SV","SVTU","SMIA","SMA","SMI"};
//affichage du formation
const char* Formations[] = {"","License", "Master", "Doctorat"};

// Definition de structure etudiant
typedef struct Etudiant{
char *nom;
char *prenom;
unsigned short formation;
unsigned short filiere;
unsigned short G_TD;
unsigned int line;
unsigned int numApogee;
unsigned int MAXNOTES;
unsigned int nbnotes;
float *notes;
float moyenne;
Bool redoublant;
Date date_inscription;
}Etudiant;

// Nettoyage de la console
void ClearConsole(int n) //DONE
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
    if (err == 2){printf("+-\033[0;31mErreur: ouverture d'un fichier a echoué!\033[0;33m\n"); return;}
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
Bool estBissextile(int annee) { //DONE 
    if ((annee % 4 == 0 && annee % 100 != 0) || annee % 400 == 0) {
        return vrai;
    } else {
        return faux;
    }
}
// Verifier si la date saisie est valide
Bool estDateValide(int jour, int mois, int annee) { //DONE
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
    while (!estDateValide(date->jour, date->mois, date->annee))
    {
        Erreur(0);
        printf("+ \033[0;32m=>");
        scanf("%hu %hu %hu", &date->jour, &date->mois, &date->annee);
    }
}

// Generer une sequence de nombre aleatoire de 7 chiffres
int NombreAleatoire_7(int year) { //DONE
    unsigned int num;
    time_t t;
    t = time(NULL);
    srand((unsigned) t);
    num = rand() %100000;
    num += (year % 100) * 100000; // Ajout des deux derniers chiffres de l'année
    return num;
}


// Lire les donnees de l'etudiant
void LireEtudiant(Etudiant *etud){ //DONE
    etud->nbnotes = 0;
    etud->prenom = (char*)malloc(MAX_CARACTERE * sizeof(char));
    etud->nom = (char*)malloc(MAX_CARACTERE * sizeof(char));
    if (etud->nom == NULL || etud->prenom == NULL){Erreur(1);}

    printf("\033[0;33m+-------------------------------------------------+\n");
    
    printf("\033[0;33m+ Saisir le nom de l'etudiant : \033[0;32m");
    scanf(" %100[^\n]s",etud->nom);
    etud->nom = (char*)realloc(etud->nom,(strlen(etud->nom) + 1 ) * sizeof(char));
    
    printf("\033[0;33m+ Saisir le prenom de l'etudiant : \033[0;32m");
    scanf(" %100[^\n]s", etud->prenom);
    etud->prenom = (char*)realloc(etud->prenom,(strlen(etud->prenom) + 1 ) * sizeof(char));
    printf("\033[0;33m+ Saisir la date d'inscription de l'etudiant (jj mm aa) : \033[0;32m");
    lireDate(&etud->date_inscription);

    do
    {
        printf("\033[0;33m+ Saisir la filiere de l'etudiant: \n+ 1: SMPC\n+ 2: SMC\n+ 3: SMP\n+ 4: STU\n+ 5: SV\n+ 6: SVTU\n+ 7: SMIA\n+ 8: SMA\n+ 9: SMI\n+ \033[0;32m=>");
        scanf("%hd",&etud->filiere);
    } while (etud->filiere < 1 || etud->filiere > 9);

    int random = NombreAleatoire_7(etud->date_inscription.annee % 100);
    etud->numApogee = random; // Generer un numero d'appogee de 7 chiffres (2 premiers font reference a l'annee de l'inscription)

    do{
    printf("\033[0;33m+ Saisir le niveau de formation de l'etudiant\n+ 1: License\n+ 2: Master\n+ 3: Doctorat : \033[0;32m");
    scanf(" %hd",&etud->formation);
    }while(etud->formation<1 && etud->formation >3);
    
    printf("\033[0;33m+ Est-ce-que l'etudiant est un redoublant?(O/N): \033[0;32m");
    lireBool(&etud->redoublant);
    
    printf("\033[0;33m+ Saisir le groupe de TD :\033[0;32m");
    scanf("%hu",&etud->G_TD);
    
    printf("\033[0;33m+ Saisir le nombre maximales de notes : \033[0;32m");
    scanf("%d",&etud->MAXNOTES);
    
    etud->notes = (float*)malloc(etud->MAXNOTES * sizeof(float));
    printf("\033[0;33m+-------------------------------------------------+\n");
    ClearConsole(2);
}

// Modifier les notes de l'etudiant
void editNotes(Etudiant *etud){ //XXX
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
    printf("\033[0;33m+-------------------------------------------------+\n");
}

// Modifier les donnees de l'etudiant
void EditEtudiant(Etudiant *etud){ //XXX
    short int choix;
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
        etud->nom = (char*)realloc(etud->nom,(strlen(etud->nom) + 1 ) * sizeof(char));

        break;
    
    case 2:
        etud->prenom = (char*)realloc(etud->prenom,MAX_CARACTERE * sizeof(char));
        if (etud->prenom == NULL){Erreur(1);}
        printf("\033[0;33m+ Saisir le prenom de l'etudiant :\033[0;32m\n");
        scanf(" %100[^\n]s",etud->prenom);
        etud->prenom = (char*)realloc(etud->prenom,(strlen(etud->prenom) + 1 ) * sizeof(char));
        break;
    
    case 3:
        lireDate(&etud->date_inscription);
        break;
    case 4:
        
        do
        {
            printf("\033[0;33m+ Saisir la filiere de l'etudiant: \n+ 1: SMPC\n+ 2: SMC\n+ 3: SMP\n+ 4: STU\n+ 5: SV\n+ 6: SVTU\n+ 7: SMIA\n+ 8: SMA\n+ 9: SMI\n+ \033[0;32m=>");
            scanf("%hd",&etud->filiere);
        } while (etud->filiere < 1 || etud->filiere > 9);

        break;
    case 5:
    
        do{
        printf("\033[0;33m+ Saisir le niveau de formation de l'etudiant\n+ 1: lmd\n+ 2: master\n+ 3: doctorat : \033[0;32m");
        scanf(" %hd",&etud->formation);
        }while(etud->formation<1 && etud->formation >3);

        break;
    
    case 6:
        printf("\033[0;33m+ Saisir le groupe de TD :\033[0;32m\n");
        scanf("%hu",&etud->G_TD);
        break;
    
    case 7:
        editNotes(etud);
        break;

    case 8:
        break;

    default:
        printf("\033[0;33m+ Veuillez entrer un choix valable\033[0;32m");
        break;
    }
}

// Afficher l'entete du tableau sur le fichier
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
    printf("----------------------------------------------------------------------------------------------------------------------\n");
    printf("| Nom            | Prenom         | Apogee | Date d'insciption | Filiere|  Formation   | Redoublant | G-TD | Moyenne |\n");
    printf("|----------------|----------------|--------|-------------------|--------|--------------|------------|------|---------|\n");
}

// Sauvegarder les donnees de l'etudiant dans un fichier externe
void SauvegardeEtudiant(Etudiant etud,FILE *fichier){ // DONE
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
    fprintf(fichier,"  %2.3f  ",etud.moyenne);
    fprintf(fichier,"|\n");
}

// Afficher les donnees de l'etudiant
void AfficheEtudiant(Etudiant etud){ //DONE
    printf("\033[0;33m+-------------------------------------------------+\n");
    printf("+-Nom :\033[0;32m%s\n\033[0;33m",etud.nom);
    printf("+-Preom :\033[0;32m%s\033[0;33m\n",etud.prenom);
    printf("+-Numero d'apogee: \033[0;32m%07i\033[0;33m\n", etud.numApogee);
    printf("+-Date d'inscription : \033[0;32m%hu/%s/%hu\033[0;33m\n", etud.date_inscription.jour, nomMois[etud.date_inscription.mois], etud.date_inscription.annee);
    printf("+-Filiere : \033[0;32m%s\033[0;33m\n",Filieres[etud.filiere]);
    printf("+-Niveau de formation : \033[0;32m%s \033[0;33m\n",Formations[etud.formation]);
    if (etud.redoublant == 1){printf("+-L'etduiant est un \033[0;32mredoublant.\033[0;33m\n");}
    else{printf("+-L'etduiant \033[0;32mn'est pas un redoublant.\033[0;33m\n");}
    printf("+-Groupe de TD : \033[0;32m%d\033[0;33m\n",etud.G_TD);
    printf("+-Les notes de l'etudiant :\033[0;32m");
    for (int i = 0; i < etud.nbnotes; i++){
    printf("\t%.3f",etud.notes[i]);
    }
    printf("\033[0;33m\n+-La moyenne de l'etudiant :\033[0;32m%f",etud.moyenne);
    printf("\033[0;33m\n");
}

// Ajouter des notes si possible
void AjouteNote(Etudiant *etud){
    int comp = 0;
    Bool reponse;
    printf("\033[0;33m+-------------------------------------------------+\n");
    if (etud->nbnotes == etud->MAXNOTES) {
        printf("+ Vous avez atteint le nombre maximal de notes.\n");
    }
    while (reponse != faux && comp < etud->MAXNOTES)
    { 
        comp++;
        if (etud->nbnotes < etud->MAXNOTES)
        {
            printf("+ Saisir la note :\033[0;32m");
            scanf("%f",&etud->notes[etud->nbnotes]);
            printf("\033[0;33m");
            etud->nbnotes++;
            etud->moyenne = (etud->moyenne * (etud->nbnotes - 1) + etud->notes[etud->nbnotes - 1]) / etud->nbnotes;
        }
        else
        {
            printf("+ Vous avez depasser le nombre maximal des notes.\n");
            break;
        }
        if (comp < etud->MAXNOTES)
        {
            printf("+ Voulez-vous ajouter une note? (O/N)\n");
            printf("+ \033[0;32m=>");
            lireBool(&reponse);
            printf("\033[0;33m");
        }
    }
    ClearConsole(3);
}

// Position du premier characteres pour chaque ligne pour des raisons d'affichage
int* NombrePositionLigne(FILE *fichier){ //DONE
    rewind(fichier);
    int size=5, *array = (int *)malloc(size*sizeof(int)), lineCount=0;
    char *line = (char *)malloc(MAX_CARACTERE*sizeof(char));
    if(array == NULL || line == NULL){erreur(1);return NULL;}

    while (fgets(line,MAX_CARACTERE,fichier) != NULL)
    {    
        if (lineCount % 5 == 4)
        {
            size +=5;
            array = realloc(array,size*sizeof(int));
            if(array == NULL){erreur(1);return NULL;}
        }
        lineCount++;
        array[lineCount] = ftell(fichier);
        
    }
    array[0]=lineCount-1;
    free(line);
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
Etudiant lireEtudiantFichier(FILE* fichier ,int line) { //DONE
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
    fscanf(fichier,"|%16[^|]|%16[^|]|%7d |%2hu/%10s /%4hu |%s |%s |%s | Grp%2hu |%f|", etud.nom, etud.prenom,&etud.numApogee,&etud.date_inscription.jour,mois,&etud.date_inscription.annee,filiere,formation_,redoublant,&etud.G_TD,&etud.moyenne);
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
        etud.redoublant = 0;
    }
    else
    {
        etud.redoublant = 1;
    }
    // Calcul du numero de la ligne apartir de la position du curseur
    etud.line = (line/_Line);
    printf("%d\n",etud.line);
    return etud;
}

//appelée quand le program lance, retourne un tableau de tous les etudiants du fichier
Etudiant *tabEtudiants(FILE *fichier, int *NPL){ // NPL nummberAndPositionOfLines
    Etudiant *tab =(Etudiant *)malloc(NPL[0]*sizeof(Etudiant));
    if(tab == NULL){erreur(1);return NULL;}
    for (int i = 3; i <= NPL[0]; i++)
    {
        tab[i-3] = lireEtudiantFichier(fichier, NPL[i]);
        tab[i-3].line = i;
    }
    return tab;
}

void afficheTabEtudiants(Etudiant *tab,int size){
    for (int i = 0; i < size; i++)
    {
        AfficheEtudiant(tab[i]);
    }
    
}

FILE *suprimerEtudiant(FILE *fichier,Etudiant etud){
    int lineToDelete = etud.line;
    FILE *tmp = fopen("tmp.txt","w+");
    if (tmp == NULL){erreur(3);return fichier;}
    rewind(fichier);
    int count = 1;
    char ch;
    while ((ch = fgetc(fichier)) != EOF) {
        if (ch == '\n') {
            count++;
        }
        // ecrire la ligne dans le fichier temporaire sauf s'il est la lignne a suprime
        if (count != lineToDelete) {
            fputc(ch, tmp);
        }
    }
    fclose(fichier);
    fclose(tmp);

    remove("test.txt");
    rename("tmp.txt", "test.txt");
    return fopen("test.txt","r+");
}


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
int filtrerEtudiantsRedoublant(Etudiant *originalTab,int originalTabSize,int redoublant,Etudiant **destinationTabPtr){
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
    FILE *fichier = NULL;
    fichier = fopen("test.txt", "r+");
    int *NPL = NombrePositionLigne(fichier);
    Etudiant *tab = tabEtudiants(fichier, NPL);
    int tabsize = NPL[0] - 2;
    Etudiant *tab2 = NULL;
    int tab2Size = filtrerEtudiantsFiliere(tab,tabsize,8,&tab2);
    afficheTabEtudiants(tab2,tab2Size);
    

    fclose(fichier);
    printf("\033[0;37m");
    return 0;
}