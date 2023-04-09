#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_CARACTERE 50 // max caracters per first or last name

// Defining boolean enum and date structure
typedef enum bool{faux, vrai}Bool;
typedef struct Date
{
    int annee;
    short int mois, jour;
}Date;
// Month names for printing
const char* nomMois[] = {"","Janvier", "Fevrier", "Mars", "Avril", "Mai", "Juin", "Juillet", "Aout", "Septembre", "Octobre", "Novembre", "Decembre"};

// Defining student's struct
typedef struct Etudiant{
int numApogee;
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
    int d,m,y;
    do{
    scanf("%d %d %d",&d,&m,&y);
    }while(d<=0||d>31 || m <= 0||m>12);
    date->jour=d;
    date->mois=m;
    date->annee=y;
}

// Generate a random sequence of number of 7 digits
int generateRandomNum(){
    int num;
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
    etud->nom = (char*)malloc(MAX_CARACTERE * sizeof(char));
    etud->prenom = (char*)malloc(MAX_CARACTERE * sizeof(char));
    printf("\033[0;33mSaisir le nom de l'etudiant : \033[0;32m");
    scanf(" %100[^\n]s",etud->nom);
    etud->nom = (char*)realloc(etud->nom,(strlen(etud->nom) + 1 ) * sizeof(char));
    printf("\033[0;33mSaisir le prenom de l'etudiant : \033[0;32m");
    scanf(" %100[^\n]s", etud->prenom);
    etud->prenom = (char*)realloc(etud->prenom,(strlen(etud->prenom) + 1 ) * sizeof(char));
    printf("\033[0;33mSaisir la date d'inscription de l'etudiant (jj mm aa) : \033[0;32m");
    lireDate(&etud->date_inscription);
    printf("\033[0;33mSaisir la formation de l'etudiant (3 lettres) : \033[0;32m");
    scanf(" %3[^\n]s",etud->formation);
    printf("\033[0;33mEst-ce-que l'etudiant est un redoublant?(O/N): \033[0;32m");
    lireBool(&etud->redoublant);
    printf("\033[0;33mSaisir le groupe de TD :\033[0;32m");
    scanf("%d",&etud->G_TD);
    printf("\033[0;33mSaisir le nombre maximales de notes : \033[0;32m");
    scanf("%d",&etud->MAXNOTES);
    etud->notes = (float*)malloc(etud->MAXNOTES * sizeof(float));
}

// Function to use in the whole editEtud function
void editNotes(Etudiant *etud){
    int noteIndex ,k = 0, rep = 0;
    printf("\033[0;33m-----------------------------------------------------------------------\n");
    do{
    printf("Quelle est la note que vous souhaitez changer?\033[0;32m\n");
    for (int i = 0; i < etud->nbnotes; i++){
        printf("\033[0;33m%d: %f\n", i, etud->notes[i]);
        k = i;
    }
    printf("%d: Annuler.\n\033[0;32m",k+1);
    scanf("%d", &noteIndex);    
    } while (noteIndex < 0  && noteIndex > etud->nbnotes + 1);
    if (noteIndex != k+1)
    {
        printf("\033[0;33mVeuillez saisir la nouvelle valeur : \033[0;32m");
        scanf("%f", &etud->notes[noteIndex]);
        etud->moyenne = (etud->moyenne * (etud->nbnotes - 1) + etud->notes[etud->nbnotes - 1]) / etud->nbnotes;
    }
}

// Function to edit data of a student
void editEtud(Etudiant *etud){
    int choix;
    fflush(stdin);
    printf("\033[0;33m-----------------------------------------------------------------------\n");
    printf("Quel information souhaitez vous modifier :\n1:modifier le nom\n2:modifier le prenom\n3:modifier la date d'inscription\n4:modifier le niveau de formation\n5:modifier le groupe de td\n6:modifier les notes\n7:Annuler\033[0;32m\n");
    do{
    scanf("%d",&choix);
    }while (choix < 1 && choix > 6);
    switch (choix){
    case 1:
        etud->nom = (char*)realloc(etud->nom,MAX_CARACTERE * sizeof(char));
        printf("\033[0;33mSaisir le nom de l'etudiant :\033[0;32m\n");
        scanf(" %100[^\n]s",etud->nom);
        etud->nom = (char*)realloc(etud->nom,(strlen(etud->nom) + 1 ) * sizeof(char));

        break;
    
    case 2:
        etud->prenom = (char*)realloc(etud->prenom,MAX_CARACTERE * sizeof(char));
        printf("\033[0;33mSaisir le prenom de l'etudiant :\033[0;32m\n");
        scanf(" %100[^\n]s",etud->prenom);
        etud->prenom = (char*)realloc(etud->prenom,(strlen(etud->prenom) + 1 ) * sizeof(char));
   break;
    
    case 3:
        lireDate(&etud->date_inscription);
        break;
    
    case 4:
        printf("\033[0;33mSaisir le niveau de formation de l'etudiant :(3 lettres)\033[0;32m\n");
        scanf(" %3[^\n]s",etud->formation);
        break;
    
    case 5:
        printf("\033[0;33mSaisir le groupe de TD :\033[0;32m\n");
        scanf("%d",&etud->G_TD);
        break;
    
    case 6:
        editNotes(etud);
        break;

    case 7:
        break;

    default:
        printf("\033[0;33mVeuillez entrer un choix valable\033[0;32m");
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
    
    fprintf(fichier,"|%-16s",etud.nom);
    fprintf(fichier,"|%-16s",etud.prenom);
    fprintf(fichier,"|%d ", etud.numApogee);
    fprintf(fichier,"|%-2d/%-8s/%-6d ", etud.date_inscription.jour, nomMois[etud.date_inscription.mois], etud.date_inscription.annee);
    fprintf(fichier,"|%-11s",etud.formation);
    if (etud.redoublant == vrai){
    fprintf(fichier,"| Redoublant ");
    }
    else{
    fprintf(fichier,"|~~~~~~~~~~~~");
    }
    fprintf(fichier,"| Grp%d ",etud.G_TD);
    fprintf(fichier,"|");
    fprintf(fichier,"%2.3f   ",etud.moyenne);
    fprintf(fichier,"|\n");
}

// Function to print student's data 
void AfficheEtud(Etudiant etud){
    printf("\033[0;33m-----------------------------------------------------------------------\n");
    printf("-Nom :\033[0;32m%s\n\033[0;33m",etud.nom);
    printf("-Preom :\033[0;32m%s\033[0;33m\n",etud.prenom);
    printf("-Numero d'apogee: \033[0;32m%7d\033[0;33m\n", etud.numApogee);
    printf("-Date d'inscription : \033[0;32m%d/%s/%d\033[0;33m\n", etud.date_inscription.jour, nomMois[etud.date_inscription.mois], etud.date_inscription.annee);
    printf("-Niveau de formation : \033[0;32m%s \033[0;33m\n",etud.formation);
    if (etud.redoublant == vrai){
    printf("-L'etduiant est un \033[0;32mredoublant.\033[0;33m\n");
    }
    else{
    printf("-L'etduiant \033[0;32mn'est pas un redoublant.\033[0;33m\n");
    }
    printf("-Groupe de TD : \033[0;32m%d\033[0;33m\n",etud.G_TD);
    printf("-Les notes de l'etudiant : \033[0;32m");
    for (int i = 0; i < etud.nbnotes; i++){
    printf("%.3f\t",etud.notes[i]);
    }
    printf("\033[0;33m\n");
}

// Function to add notes to a student if possible
void AjouteNote(Etudiant *etud){
    Bool reponse;
    printf("\033[0;33m-----------------------------------------------------------------------\n");
    while (reponse != faux)
    { 
        if (etud->nbnotes < etud->MAXNOTES)
        {
            printf("Saisir la note :\033[0;32m");
            scanf("%f",&etud->notes[etud->nbnotes]);
            printf("\033[0;33m");
            etud->nbnotes++;
            etud->moyenne = (etud->moyenne * (etud->nbnotes - 1) + etud->notes[etud->nbnotes - 1]) / etud->nbnotes;
        }
        else
        {
            printf("Vous avez depasser le nombre maximal des notes.\n");
            break;
        }
        printf("Voulez-vous ajouter une note? (O/N)\n");
        lireBool(&reponse);
    } 
}


int *numberAndPositionOflines(FILE *fp){
    int size=5, *array = (int *)malloc(size*sizeof(int)), lineCount=1,i=1;
    char *line = (char *)malloc(200*sizeof(char));
    while (fgets(line,200,fp) != NULL)
    {
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
    return array;
}

void printFromFile(FILE *file,int linePos){
    fseek(file,linePos,SEEK_SET);
    char *student = (char *)malloc(100*(sizeof(char)));
    fgets(student,100,file);
    printf("%s",student);
}


// Programme principal de test
int main(){
    Etudiant student;
    FILE *fichier = NULL;
    fichier = fopen("test.txt","a+");
    TabHeader(fichier);
    
    fclose(fichier);
    printf("\033[0;33m");
    return 0;
}
