#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> 

#define MAX_CARACTERE 120 

// Definition d'enumeration booleenne
typedef enum bool{faux, vrai}Bool;
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
const char* formation[] = {"","lmd", "master", "doctorat"};

// Definition de structure etudiant
typedef struct Etudiant{
unsigned int numApogee;
char *nom;
char *prenom;
Date date_inscription;
short int formation;
Bool redoublant;
short filiere;
short G_TD;
int MAXNOTES;
float *notes;
int nbnotes;
float moyenne;
}Etudiant;

// Nettoyage de la console
void ClearConsole(int n)
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

// Lire une booleenne (o-O/n-N)
void lireBool(Bool *bool){
    char tmp;
    do
    {
    scanf("%c", &tmp);
    if (tmp == 'o' || tmp == 'O')
    {
        *bool = vrai;
    }else if (tmp == 'n' || tmp == 'N')
    {
        *bool = faux;
    }
    } while (!(tmp == 'o' || tmp == 'O' || tmp == 'n' || tmp == 'N'));
}

// Saisie de la date
void lireDate(Date *date){
    short int d,m,y;
    do{
    scanf("%hu %hu %hu",&d,&m,&y);
    }while(d<=0||d>31 || m <= 0||m>12);
    date->jour=d;
    date->mois=m;
    date->annee=y;
}


// Generer une sequence de nombre aleatoire de 7 chiffres
int NombreAleatoire_7(int year) {
    unsigned int num;
    time_t t;
    t = time(NULL);
    srand((unsigned) t);
    num = rand() %100000;
    num += year * 100000;
    return num;
}

// Recuperer les 2 derniers chiffres de l'annee 
int DateChiffre_2(Etudiant* etudiant) {
    return etudiant->date_inscription.annee % 100;
}

// Sasie de la filiere de l'etudiant
void FiliereEtudiant(Etudiant *etud){
    printf("\033[0;33m+ Saisir la filiere de l'etudiant: \n");
    printf("+ 1: SMPC\n+ 2: SMC\n+ 3: SMP\n+ 4: STU\n+ 5: SV\n+ 6: SVTU\n+ 7: SMIA\n+ 8: SMA\n+ 9: SMI\n");
    printf("+ \033[0;32m=>");
    scanf("%hd",&etud->filiere);
}

// Lire les donnees de l'etudiant
void LireEtudiant(Etudiant *etud){
    etud->nbnotes = 0;
    etud->prenom = (char*)malloc(MAX_CARACTERE * sizeof(char));
    etud->nom = (char*)malloc(MAX_CARACTERE * sizeof(char));
    printf("\033[0;33m+-------------------------------------------------+\n");
    printf("\033[0;33m+ Saisir le nom de l'etudiant : \033[0;32m");
    scanf(" %100[^\n]s",etud->nom);
    etud->nom = (char*)realloc(etud->nom,(strlen(etud->nom) + 1 ) * sizeof(char));
    printf("\033[0;33m+ Saisir le prenom de l'etudiant : \033[0;32m");
    scanf(" %100[^\n]s", etud->prenom);
    etud->prenom = (char*)realloc(etud->prenom,(strlen(etud->prenom) + 1 ) * sizeof(char));
    printf("\033[0;33m+ Saisir la date d'inscription de l'etudiant (jj mm aa) : \033[0;32m");
    lireDate(&etud->date_inscription);
    FiliereEtudiant(etud);
    int random = NombreAleatoire_7(DateChiffre_2(etud));
    etud->numApogee = random; // Generer un numero d'appogee de 7 chiffres (2 premiers font reference a l'annee de l'inscription)
    
    do{
    printf("\033[0;33m+ Saisir le niveau de formation de l'etudiant\n+ 1: lmd\n+ 2: master\n+ 3: doctorat : \033[0;32m");
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
    printf("\033[0;33m+-------------------------------------------------+\n");
}

// Modifier les donnees de l'etudiant
void EditEtudiant(Etudiant *etud){
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
        printf("\033[0;33m+ Saisir le nom de l'etudiant :\033[0;32m\n");
        scanf(" %100[^\n]s",etud->nom);
        etud->nom = (char*)realloc(etud->nom,(strlen(etud->nom) + 1 ) * sizeof(char));

        break;
    
    case 2:
        etud->prenom = (char*)realloc(etud->prenom,MAX_CARACTERE * sizeof(char));
        printf("\033[0;33m+ Saisir le prenom de l'etudiant :\033[0;32m\n");
        scanf(" %100[^\n]s",etud->prenom);
        etud->prenom = (char*)realloc(etud->prenom,(strlen(etud->prenom) + 1 ) * sizeof(char));
   break;
    
    case 3:
        lireDate(&etud->date_inscription);
        break;
    case 4:
        FiliereEtudiant(etud);
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
void TabHeader(FILE *fichier)
{
    fseek(fichier,0,SEEK_END);
    if (ftell(fichier) == 0) // Tester si le fichier est vide
    {
        fprintf(fichier,"----------------------------------------------------------------------------------------------------------------------\n");
        fprintf(fichier,"| Nom\t\t     | Prenom\t\t  | Apogee | Date d'insciption | Filere |  Formation   | Redoublant | G-TD | Moyenne |\n");
        fprintf(fichier,"|----------------|----------------|--------|-------------------|--------|--------------|------------|------|---------|\n");
    }
}

// Afficher l'entete du tableau sur la console
void AfficheTabHeader()
{
    printf("----------------------------------------------------------------------------------------------------------------------\n");
    printf("| Nom\t\t | Prenom\t  | Apogee | Date d'insciption | Filiere|  Formation   | Redoublant | G-TD | Moyenne |\n");
    printf("|----------------|----------------|--------|-------------------|-----------|-----------|------------|------|---------|\n");
}

// Sauvegarder les donnees de l'etudiant dans un fichier externe
void SauvegardeEtudiant(Etudiant etud,FILE *fichier){
    
    fprintf(fichier,"|%-16.*s", 16, etud.nom);
    fprintf(fichier,"|%-16.*s", 16, etud.prenom);
    fprintf(fichier,"|%-7i ", etud.numApogee);
    fprintf(fichier,"| %-2hd/%-9s/%-5hd", etud.date_inscription.jour, nomMois[etud.date_inscription.mois], etud.date_inscription.annee);
    fprintf(fichier,"|  %-6s",Filieres[etud.filiere]);
    fprintf(fichier,"|    %-10s",formation[etud.formation]);
    if (etud.redoublant == vrai){
    fprintf(fichier,"| Redoublant ");
    }
    else{
    fprintf(fichier,"| ~~~~~~~~~~ ");
    }
    fprintf(fichier,"| Grp%-1hu ",etud.G_TD);
    fprintf(fichier,"|");
    fprintf(fichier,"  %2.3f  ",etud.moyenne);
    fprintf(fichier,"|\n");
}

// Afficher les donnees de l'etudiant
void AfficheEtudiant(Etudiant etud){
    printf("\033[0;33m+-------------------------------------------------+\n");
    printf("+-Nom :\033[0;32m%s\n\033[0;33m",etud.nom);
    printf("+-Preom :\033[0;32m%s\033[0;33m\n",etud.prenom);
    printf("+-Numero d'apogee: \033[0;32m%-7i\033[0;33m\n", etud.numApogee);
    printf("+-Date d'inscription : \033[0;32m%hu/%s/%hu\033[0;33m\n", etud.date_inscription.jour, nomMois[etud.date_inscription.mois], etud.date_inscription.annee);
    printf("+-Filiere : \033[0;32m%s\033[0;33m\n",Filieres[etud.filiere]);
    printf("+-Niveau de formation : \033[0;32m%s \033[0;33m\n",formation[etud.formation]);
    if (etud.redoublant == vrai){
    printf("+-L'etduiant est un \033[0;32mredoublant.\033[0;33m\n");
    }
    else{
    printf("+-L'etduiant \033[0;32mn'est pas un redoublant.\033[0;33m\n");
    }
    printf("+-Groupe de TD : \033[0;32m%d\033[0;33m\n",etud.G_TD);
    printf("+-Les notes de l'etudiant :\033[0;32m");
    for (int i = 0; i < etud.nbnotes; i++){
    printf("\t%.3f",etud.notes[i]);
    }
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
int* NombrePositionLigne(FILE *fp){
    int size=5, *array = (int *)malloc(size*sizeof(int)), lineCount=1,i=1;
    char *line = (char *)malloc(MAX_CARACTERE*sizeof(char));
    if (line == NULL)
    {
        printf("\033[0;31m+ Erreur d'allocation en memoire!\n\033[0;37m");
        return NULL;
    }
    while (fgets(line,MAX_CARACTERE,fp) != NULL)
    {    
        if (lineCount % 5 == 0)
        {
            size +=5;
            array = realloc(array,size*sizeof(int));
        }
        lineCount++;
        array[i] = ftell(fp);
        i++;
    }
    array[0]=lineCount-1;
    free(line);
    return array;
}

// Afficher une ligne a partir de sa position
void AfficheLigne(FILE *file,int linePos){
    fseek(file,linePos,SEEK_SET);
    char student[MAX_CARACTERE];
    fgets(student,MAX_CARACTERE,file);
    printf("%s",student);
}

// Afficher un tableau de lignes (Premier element du tableau est sa taille)
void AfficheTabLignes(FILE *file,int *array){
    ClearConsole(2);
    AfficheTabHeader();
    for (int i = 1; i <= array[0]; i++)//first element of array is size of array
    {
        AfficheLigne(file, array[i]);
    }
    printf("----------------------------------------------------------------------------------------------------------\n");
}

// Rechercher les etudiants par noms ou prenoms
int* RechercheEtudiant_Nom_Prenom(FILE *fp){
    int *array = (int *) malloc(sizeof(int));
    int *linePositions = NombrePositionLigne(fp),lineCount = 0;
    char key[17], src[35], line[MAX_CARACTERE];
    printf("\033[0;33m+-------------------------------------------------+\n");
    printf("+ Veuillez saisir le nom ou le prenom a chercher: \n");
    printf("+ \033[0;32m=>");
    scanf("%16s",key);
    printf("\033[0;33m");
    for (int i = 3; i < linePositions[0]; i++)
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


// Programme principal de test
int main(){
    Etudiant student;
    FILE *fichier = NULL;
    fichier = fopen("test.txt","a+");
    TabHeader(fichier);
    LireEtudiant(&student);
    SauvegardeEtudiant(student,fichier);
    LireEtudiant(&student);
    SauvegardeEtudiant(student,fichier);
    LireEtudiant(&student);
    SauvegardeEtudiant(student,fichier);
    fclose(fichier);
    printf("\033[0;37m");
    return 0;
}
