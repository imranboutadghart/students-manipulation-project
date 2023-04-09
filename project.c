#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> 

#define MAX_CARACTERE 100 // max caracters per first or last name

// Defining boolean enum and date structure
typedef enum bool{faux, vrai}Bool;
typedef struct Date
{
    short int mois, jour, annee;
}Date;
// Month names for printing
const char* nomMois[] = {"","Janvier", "Fevrier", "Mars", "Avril", "Mai", "Juin", "Juillet", "Aout", "Septembre", "Octobre", "Novembre", "Decembre"};

// Defining student's struct
typedef struct Etudiant{
short int numApogee;
char *nom;
char *prenom;
Date date_inscription;
char formation[3];
Bool redoublant;
short G_TD;
int MAXNOTES;
float *notes;
int nbnotes;
float moyenne;
}Etudiant;

// Customized clearing of the console
void ClearConsole(int n)
{
    for (int i = 0; i < n; i++) {
        // clear the console
        system("clear");

        printf("Traitement des donnees saisies... %d/%d\n", i+1,n);

        // pause for 1 second
        sleep(1);
    }
    system("clear");
}

// Function to read booleans from o or N
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

// Function to read a variable date
void lireDate(Date *date){
    short int d,m,y;
    do{
    scanf("%hd %hd %hd",&d,&m,&y);
    }while(d<=0||d>31 || m <= 0||m>12);
    date->jour=d;
    date->mois=m;
    date->annee=y;
}

// Generate a random sequence of number of 7 digits
int generateRandomNum(){
    short int num;
    time_t t;
    t = time(NULL);
    srand((unsigned) t);
    num = rand() %9999999 + 1000000;
    return num;
}

// Function to read data of a student
void LireEtud(Etudiant *etud){
    int random = generateRandomNum();
    etud->numApogee = random;
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
    printf("\033[0;33m+ Saisir la formation de l'etudiant (3 lettres) : \033[0;32m");
    scanf(" %3[^\n]s",etud->formation);
    printf("\033[0;33m+ Est-ce-que l'etudiant est un redoublant?(O/N): \033[0;32m");
    lireBool(&etud->redoublant);
    printf("\033[0;33m+ Saisir le groupe de TD :\033[0;32m");
    scanf("%hd",&etud->G_TD);
    printf("\033[0;33m+ Saisir le nombre maximales de notes : \033[0;32m");
    scanf("%d",&etud->MAXNOTES);
    etud->notes = (float*)malloc(etud->MAXNOTES * sizeof(float));
    printf("\033[0;33m+-------------------------------------------------+\n");
    ClearConsole(2);
}

// Function to use in the whole editEtud function
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

// Function to edit data of a student
void editEtud(Etudiant *etud){
    short int choix;
    fflush(stdin);
    printf("\033[0;33m+-------------------------------------------------+\n");
    printf("+ Quel information souhaitez vous modifier :\n+ 1:modifier le nom\n+ 2:modifier le prenom\n+ 3:modifier la date d'inscription\n+ 4:modifier le niveau de formation\n+ 5:modifier le groupe de td\n+ 6:modifier les notes\n+ 7:Annuler\n");
    do{
    printf("+ \033[0;32m=>");
    scanf("%hd",&choix);
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
        printf("\033[0;33m+ Saisir le niveau de formation de l'etudiant :(3 lettres)\033[0;32m\n");
        scanf(" %3[^\n]s",etud->formation);
        break;
    
    case 5:
        printf("\033[0;33m+ Saisir le groupe de TD :\033[0;32m\n");
        scanf("%hd",&etud->G_TD);
        break;
    
    case 6:
        editNotes(etud);
        break;

    case 7:
        break;

    default:
        printf("\033[0;33m+ Veuillez entrer un choix valable\033[0;32m");
        break;
    }
}

// Printing Table's header
void TabHeader(FILE *fichier)
{
    fseek(fichier,0,SEEK_END);
    if (ftell(fichier) == 0) // Test if the file is empty
    {
        fprintf(fichier,"----------------------------------------------------------------------------------------------------------\n");
        fprintf(fichier,"| Nom\t\t     | Prenom\t\t  | Apogee | Date d'insciption | Formation | Redoublant | G-TD | Moyenne |\n");
        fprintf(fichier,"|----------------|----------------|--------|-------------------|-----------|------------|------|---------|\n");
    }
}

// Function to save student's data in an external file
void EcrireEtud(Etudiant etud,FILE *fichier){
    
    fprintf(fichier,"|%-16.*s", 16, etud.nom);
    fprintf(fichier,"|%-16.*s", 16, etud.prenom);
    fprintf(fichier,"|%hd ", etud.numApogee);
    fprintf(fichier,"|%-2hd/%-8s/%-6hd ", etud.date_inscription.jour, nomMois[etud.date_inscription.mois], etud.date_inscription.annee);
    fprintf(fichier,"|%-11s",etud.formation);
    if (etud.redoublant == vrai){
    fprintf(fichier,"| Redoublant ");
    }
    else{
    fprintf(fichier,"| ~~~~~~~~~~ ");
    }
    fprintf(fichier,"| Grp%hd ",etud.G_TD);
    fprintf(fichier,"|");
    fprintf(fichier,"%2.3f   ",etud.moyenne);
    fprintf(fichier,"|\n");
}

// Function to print student's data 
void AfficheEtud(Etudiant etud){
    printf("\033[0;33m+-------------------------------------------------+\n");
    printf("+-Nom :\033[0;32m%s\n\033[0;33m",etud.nom);
    printf("+-Preom :\033[0;32m%s\033[0;33m\n",etud.prenom);
    printf("+-Numero d'apogee: \033[0;32m%7d\033[0;33m\n", etud.numApogee);
    printf("+-Date d'inscription : \033[0;32m%hd/%s/%hd\033[0;33m\n", etud.date_inscription.jour, nomMois[etud.date_inscription.mois], etud.date_inscription.annee);
    printf("+-Niveau de formation : \033[0;32m%s \033[0;33m\n",etud.formation);
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

// Function to add notes to a student if possible
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

//positions of first caracters of each line for printing purposes
int *numberAndPositionOflines(FILE *fp){
    int size=5, *array = (int *)malloc(size*sizeof(int)), lineCount=1,i=1;
    char *line = (char *)malloc(200*sizeof(char));
    while (fgets(line,200,fp) != NULL)
    {
        if (line == NULL)
        {
            printf("couldn't allocate memory");
            return NULL;
        }
        
        if (lineCount%5==0)
        {
            size +=5;
            array = realloc(array,size);
        }
        lineCount++;
        array[i]=ftell(fp);
        i++;
    }
    array[0]=lineCount-1;
    free(line);
    return array;
}

//printing a line from a line position
void printFromFile(FILE *file,int linePos){
    fseek(file,linePos,SEEK_SET);
    char student[120];
    fgets(student,120,file);
    printf("%s",student);
}

//printing an array of lines (first element of array must be array size)
void printArrayFromFile(FILE *file,int *array){
    for (int i = 1; i < array[0]; i++)//first element of array is size of array
    {
        printFromFile(file, array[i]);
    }
    
}



// Programme principal de test
int main(){
    Etudiant student;
    FILE *fichier = NULL;
    fichier = fopen("test.txt","a+");
    TabHeader(fichier);
    LireEtud(&student);
    AjouteNote(&student);
    AfficheEtud(student);
    editEtud(&student);
    EcrireEtud(student,fichier);
    fclose(fichier);
    printf("\033[0;37m");
    return 0;
}
