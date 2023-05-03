#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../headers/utilitaires.h"
#include "../headers/consultation.h"
#include "../headers/structs.h"
#include "../headers/modification.h"
#include "../headers/recherche.h"
#include "../headers/suppression.h"
#include "../headers/triage.h"

char FICHIERDATA[MAX_CARACTERE];
char FICHIERNOTES[MAX_CARACTERE];
// Nettoyage de la console
void ClearConsole(int n){
    for (int i = 0; i < n; i++) {
        // Vider la console
        #ifdef _WIN32 // Si le code est compile sur windows
            system("cls");
        #else
            system("clear");
        #endif

        printf("\t\t\t\t\t\tTraitement des donnees saisies... %d/%d\n", i+1,n);
        // pauser le programme pour 250 ms
        usleep(250000);
    }
    system("clear");
}

// Tester l'ouverture du fichier
short TesterFichier(FILE *fichier){
    if (fichier == NULL)
    {
        Erreur(2);
        exit(0);
    }
    return 0;
}

// Tester si le fichier est vide
Bool estFichierVide(FILE *fichier){
    // Déplace le pointeur de fichier au début du fichier
    rewind(fichier);
    // Vérifier si le premier caractère est EOF
    if (fgetc(fichier) == EOF) return vrai;
    else return faux;
}

// Messages d'erreur
void Erreur(short error) {
    if (error == 0){printf("+\033[0;31m (-)Erreur: Mal saisie de donnees!\033[0;33m\n"); return;}
    if (error == 1){printf("+\033[0;31m (-)Erreur: Allocation en memoire a echoué!\033[0;33m\n"); return;}
    if (error == 2){printf("+\033[0;31m (-)Erreur: Ouverture du fichier a echoué!\033[0;33m\n"); return;}
    if (error == 3){printf("+\033[0;31m (-)Erreur: Veuillez entrer un choix valable\033[0;32m\n"); return;}
}

// Lire le nom des deux fichiers a partir de l'utilisateur 
void LireNomFichiers(FILE **fichier, FILE **fichier_note) {
    char nom_fichier[MAX_CARACTERE];
    char nom_fichier_note[MAX_CARACTERE];
    char data_path[MAX_CARACTERE];

    printf("\n\t\t\t\t\033[0;33m+- Entrer le nom du fichier dont vous voulez travailler: ");
    scanf("%s", nom_fichier);

    // Ajouter le préfixe "data/" et le suffixe ".txt" aux noms de fichiers
    sprintf(data_path, "data/%s.txt", nom_fichier);
    sprintf(nom_fichier_note, "data/%s_note.txt", nom_fichier);

    // Ouvrir des fichiers
    *fichier = fopen(data_path, "a+");
    
    TesterFichier(*fichier);

    // Ouvrir le fichier de notes
    *fichier_note = fopen(nom_fichier_note, "a+");
    TesterFichier(*fichier_note);

    // Sauvegarder les noms complets des fichiers dans les variables globales
    strcpy(FICHIERDATA, data_path);
    strcpy(FICHIERNOTES, nom_fichier_note);
}

// Afficher le nom de l'app en ASCII Art
void PrintAsciiArt(void) {
    printf("\t\t\t\t\033[0;34m      ___                   ___          ___          ___          ___                   ___     \n");
    printf("\t\t\t\t\033[0;34m     /  /\\     ___         /  /\\        /  /\\        /  /\\        /  /\\     ___         /  /\\    \n");
    printf("\t\t\t\t\033[0;34m    /  /::\\   /__/\\       /  /:/       /  /::\\      /  /::\\      /  /::\\   /__/\\       /  /::\\   \n");
    printf("\t\t\t\t\033[0;33m   /  /:/\\:\\  \\  \\:\\     /  /:/       /  /:/\\:\\    /  /:/\\:\\    /  /:/\\:\\  \\  \\:\\     /  /:/\\:\\  \n");
    printf("\t\t\t\t\033[0;33m  /  /::\\ \\:\\  \\__\\:\\   /  /:/       /  /:/  \\:\\  /  /:/  \\:\\  /  /::\\ \\:\\  \\__\\:\\   /  /::\\ \\:\\ \n");
    printf("\t\t\t\t\033[0;33m /__/:/\\:\\ \\:\\ /  /::\\ /__/:/     /\\/__/:/ \\__\\:|/__/:/_\\_ \\:\\/__/:/\\:\\_\\:\\ /  /::\\ /__/:/\\:\\ \\:\\ \n");
    printf("\t\t\t\t\033[0;33m \\  \\:\\ \\:\\_\\//  /:/ \\:\\  \\:\\    /:/\\  \\:\\ /  /:/\\  \\:\\__/\\_\\/\\__\\/  \\:\\/://  /:/\\:\\\\  \\:\\ \\:\\_\\/\n");
    printf("\t\t\t\t\033[0;33m  \\  \\:\\ \\:\\ /  /:/__\\/ \\  \\:\\  /:/  \\  \\:\\  /:/  \\  \\:\\ \\:\\       \\__\\:://  /:/__\\/ \\  \\:\\ \\:\\  \n");
    printf("\t\t\t\t\033[0;34m   \\  \\:\\_\\//__/:/       \\  \\:\\/:/    \\  \\:\\/:/    \\  \\:\\/:/       /  /://__/:/       \\  \\:\\_\\/  \n");
    printf("\t\t\t\t\033[0;34m    \\  \\:\\  \\__\\/         \\  \\::/      \\  \\::/      \\  \\::/       /__/:/ \\__\\/         \\  \\:\\    \n");
    printf("\t\t\t\t\033[0;34m     \\__\\/                 \\__\\/        \\__\\/        \\__\\/        \\__\\/                 \\__\\/    \n");
    printf("\t\t\t\t\033[0m\n"); // réinitialiser la couleur
}

// Lancer le programme
void Lancement(void){
    Bool reponse;
    ClearConsole(0);
    printf("\n\n\n+ Veuillez mettre la fenêtre de votre console en\033[1;36m plein écran\033[0;37m pour une expérience optimale");
    fflush(stdout);
    for (int i = 0; i < 3; i++)
    {
        printf(".");
        fflush(stdout);
        sleep(2);
    }
    ClearConsole(1);
    printf("\n");
    PrintAsciiArt();
    // Pauser le prog pour une seconde
    sleep(1);
    // Afficher une breve description de l'app
    printf("\t\t\t\t\033[0;36m+------------------------------------------------------------------------------------------------+\n");
    printf("\t\t\t\t+\033[0;33m EtudGate est une application console performante qui permet une gestion facile et efficace     \033[0;36m+\n");
    printf("\t\t\t\t+\033[0;33m des étudiants. Avec EtudGate, vous pouvez facilement ajouter, modifier et supprimer des        \033[0;36m+\n");
    printf("\t\t\t\t+\033[0;33m étudiants, ainsi que consulter la liste complète, la liste des étudiants admis et la liste des \033[0;36m+\n");
    printf("\t\t\t\t+\033[0;33m étudiants d'une filière spécifique. En outre, vous pouvez trier les étudiants par numéro       \033[0;36m+\n");
    printf("\t\t\t\t+\033[0;33m Apogée, moyenne ou date d'inscription, et rechercher rapidement un étudiant par son            \033[0;36m+\n");
    printf("\t\t\t\t+\033[0;33m numéro Apogée ou par d'autres critères tels que le nom, le prénom et la date d'inscription.    \033[0;36m+\n");
    printf("\t\t\t\t+------------------------------------------------------------------------------------------------+\n");
    sleep(2);
    printf("\t\t\t\t\t\t\t\t\t\033[0;36m-Commencer?(O/N)\n");
        printf("\t\t\t\t\t\t\t\t\t\033[0;32m=>");
        lireBool(&reponse);
    if (reponse == faux){exit(0);}// Quitter le programme
    ClearConsole(1);
}

void MenuPrincipal(Etudiant *tableauEtudiants,FILE *fichier,FILE *fichierNote,short  taille){
    short reponse;
    Bool res;
    printf("\t==>names:%s\t%s\n",FICHIERDATA,FICHIERNOTES);
    afficheTabEtudiants(tableauEtudiants,taille);
    printf("\t\t\t\t\t\t\033[0;36m+-----------------------------------------------------------------------+\n");
    printf("\t\t\t\t\t\t+\033[0;33m Que souhaitez-vous faire ?    \t\t\t\t\t\033[0;36m+\n");
    printf("\t\t\t\t\t\t+\033[0;33m 1- Ajouter des etudiants dans le fichier.\t\t\t        \033[0;36m+\n \t\t\t\t\t\t+\033[0;33m 2- Modifier les informations d'un etudiant.\t\t\t\t\033[0;36m+\n \t\t\t\t\t\t+\033[0;33m 3- Supprimer un etudiant du fichier.\t\t\t\t\t\033[0;36m+\n \t\t\t\t\t\t+\033[0;33m 4- Rechercher un ou des etudiants par nom ou prenom      \033[0;36m\t\t+\n \t\t\t\t\t\t+\033[0;33m 5- Trier les etudiant selon des criteres specifiques.\033[0;36m\t\t\t+\n\t\t\t\t\t\t+\033[0;33m 6- Quitter l'application.\033[0;36m\t\t\t\t\t\t+\n");
    printf("\t\t\t\t\t\t\033[0;36m+-----------------------------------------------------------------------+\n");
    do
    {
        printf("\t\t\t\t\t\t\033[0;36m+\033[0;32m=>");
        scanf("%hd",&reponse);
        printf("\033[0;36m");
        if (reponse < 1 || reponse > 6)
        {
            printf("\t\t\t\t\t\t");
            Erreur(0);
        }
    } while (!(reponse > 0 && reponse <= 6));
    switch (reponse){
    case 1:
        do{
            Etudiant etudiant_;
            LireEtudiant(&etudiant_,fichier,fichierNote);
            printf("Ajouter un autre etudiant ? (O/N)\n");
            lireBool(&res);
        } while (res != faux);
        break;
    case 2:
        editEtudiantFile(tableauEtudiants,&fichier,&fichierNote,taille);
        break;
    case 3:;
        short num;
        printf("+ \033[0;33mEntrez le numero de l'etudiant que vous souhaitez supprimer ses informations: \n");
        do
        {
            printf("+ \033[0;32m=>");
            scanf("%hd", &num);
        } while (num <= 0 || num > taille);
        suprimerEtudiant(&fichier,&fichierNote,tableauEtudiants[num]);
        break;
    case 4:
        // RechercheEtudiant_Nom_Prenom(fichier);
        break;
    case 5:
        unsigned int desTabSize;
        Etudiant *desTab = trierEtudiants(tableauEtudiants,taille,&desTabSize);
        afficheTabEtudiants(desTab,desTabSize);
        break;
    case 6:
        exit(0);
        break;
    
    default:
        Erreur(3);
        break;
    }
}