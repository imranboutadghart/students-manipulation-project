#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>

#define MAX_CARACTERE 50 // max caracters per first or last name

int note = 0; // Variable globale note

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
char G_TD;
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
    printf("Saisir le nom de l'etudiant : ");
    scanf(" %100[^\n]s",etud->nom);
    etud->nom = (char*)realloc(etud->nom,(strlen(etud->nom) + 1 ) * sizeof(char));
    printf("Saisir le prenom de l'etudiant : ");
    scanf(" %100[^\n]s", etud->prenom);
    etud->prenom = (char*)realloc(etud->prenom,(strlen(etud->prenom) + 1 ) * sizeof(char));
    printf("Saisir la date d'inscription de l'etudiant (jj mm aa) : ");
    lireDate(&etud->date_inscription);
    printf("Saisir la formation de l'etudiant (3 lettres) : ");
    scanf(" %3[^\n]s",etud->formation);
    printf("Est-ce-que l'etudiant est un redoublant?(O/N): ");
    lireBool(&etud->redoublant);
    printf("Saisir le groupe de TD :");
    scanf("%d",&etud->G_TD);
    printf("Saisir le nombre maximales de notes : ");
    scanf("%d",&etud->MAXNOTES);
    etud->notes = (float*)malloc(etud->MAXNOTES * sizeof(float));
}

// Function to use in the whole editEtud function
void editNotes(Etudiant *etud){
    int noteIndex;
    printf("-----------------------------------------------------------------------\n");
    do{
    printf("quelle est la note que vous souhaitez changer?\n");
    for (int i = 0; i < etud->nbnotes; i++){
        printf("%d: %f", i, etud->notes[i]);
    }
    scanf("%d", &note);    
    } while (noteIndex < 0  && noteIndex > etud->nbnotes + 1);
    printf("veuillez saisir la nouvelle valeur : ");
    scanf("%2f", &etud->notes[noteIndex]);
}

// Function to edit data of a student
void editEtud(Etudiant *etud){
    int choix;
    fflush(stdin);
    printf("-----------------------------------------------------------------------\n");
    printf("Quel information souhaitez vous modifier :\n1:modifier le nom\n2:modifier le prenom\n3:modifier la date d'inscription\n4:modifier le niveau de formation\n5:modifier le groupe de td\n6:modifier les notes\n");
    do{
    scanf("%d",&choix);
    }while (choix < 1 && choix > 6);
    switch (choix){
    case 1:
        etud->nom = (char*)realloc(etud->nom,MAX_CARACTERE * sizeof(char));
        printf("Saisir le nom de l'etudiant :\n");
        scanf(" %100[^\n]s",etud->nom);
        etud->nom = (char*)realloc(etud->nom,(strlen(etud->nom) + 1 ) * sizeof(char));

        break;
    
    case 2:
        etud->prenom = (char*)realloc(etud->prenom,MAX_CARACTERE * sizeof(char));
        printf("Saisir le prenom de l'etudiant :\n");
        scanf(" %100[^\n]s",etud->prenom);
        etud->prenom = (char*)realloc(etud->prenom,(strlen(etud->prenom) + 1 ) * sizeof(char));
   break;
    
    case 3:
        lireDate(&etud->date_inscription);
        break;
    
    case 4:
        printf("Saisir le niveau de formation de l'etudiant :(3 lettres)\n");
        scanf(" %3[^\n]s",etud->formation);
        break;
    
    case 5:
        printf("Saisir le groupe de TD :\n");
        scanf("%d",&etud->G_TD);

        break;
    
    case 6:
        editNotes(etud);
        break;
    
    default:
        printf("Veuillez entrer un choix valable");
        break;
    }
}



// Function to save student's data in an external file
void EcrireEtud(Etudiant etud,FILE *fichier){
    fprintf(fichier,"|-----------------------------------------------------------------------------------------------------|\n");
    fprintf(fichier,"| Nom\t\t     | Prenom\t\t  | Apogee | Date d'insciption | Formation | Redoublant | G-TD | Note |\n");
    fprintf(fichier,"|-----------------------------------------------------------------------------------------------------|\n");
    fprintf(fichier,"|%16s",etud.nom);
    fprintf(fichier,"|%16s",etud.prenom);
    fprintf(fichier,"|%d ", etud.numApogee);
    fprintf(fichier,"|%d/%s/%d  ", etud.date_inscription.jour, nomMois[etud.date_inscription.mois], etud.date_inscription.annee);
    fprintf(fichier,"|%s\t",etud.formation);
    if (etud.redoublant == vrai){
    fprintf(fichier,"| Redoublant ");
    }
    else{
    fprintf(fichier,"|------------");
    }
    fprintf(fichier,"| G-TD%d",etud.G_TD);
    fprintf(fichier,"|");
    for (int i = 0; i < etud.nbnotes; i++){
    fprintf(fichier,"%f\t",etud.notes[i]);
    }
    fprintf(fichier,"|\n");
}

// Function to print student's data 
void AfficheEtud(Etudiant etud){
    printf("-----------------------------------------------------------------------\n");
    printf("-Nom :%s\n",etud.nom);
    printf("-Preom :%s\n",etud.prenom);
    printf("-Numero d'apogee: %d\n", etud.numApogee);
    printf("-Date d'inscription : %d/%s/%d\n", etud.date_inscription.jour, nomMois[etud.date_inscription.mois], etud.date_inscription.annee);
    printf("-Niveau de formation : %s \n",etud.formation);
    if (etud.redoublant == vrai){
    printf("-L'etduiant est un redoublant.\n");
    }
    else{
    printf("-L'etduiant n'est pas un redoublant.\n");
    }
    printf("-Groupe de TD : %d\n",etud.G_TD);
    printf("-Les notes de l'etudiant :\n");
    for (int i = 0; i < etud.nbnotes; i++){
    printf("%.3f\t",etud.notes[i]);
    }
    printf("\n");
}

// Function to add notes to a student if possible
void AjouteNote(Etudiant *etud){
if (etud->nbnotes +1 < etud->MAXNOTES)
{
printf("Saisir la note :");
scanf("%f",&etud->notes[etud->nbnotes]);
etud->nbnotes++;
etud->moyenne = (etud->moyenne * (etud->nbnotes - 1) + etud->notes[etud->nbnotes - 1]) / etud->nbnotes;
}
else
{
printf("Vous avez depassee le nombre maximal des notes.\n");
}
}

// Programme principal de test
int main(){
    Etudiant student;
    FILE *fichier = NULL;
    fichier = fopen("test.txt","a");
    LireEtud(&student);
    AjouteNote(&student);
    AfficheEtud(student);
    editEtud(&student);
    EcrireEtud(student,fichier);
    fclose(fichier);
    return 0;
}