#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#else
    #include <unistd.h>
#endif
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
        #else // For Unix-based systems
            system("clear");
        #endif

        printf("\t\t\t\t\t\t\033[0;36m+\033[0;32m Traitement des donnees saisies... %d/%d\n", i+1,n);
        // pauser le programme pour 250 ms
        usleep(250000);
    }
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Tester l'ouverture du fichier
short TesterFichier(FILE *fichier){
    if (fichier == NULL){
        Erreur(2);
        sleep(1);
        fermeture();
    }
    return 0;
}

// Tester si le fichier est vide
Bool estFichierVide(FILE *fichier){
    // Deplace le pointeur de fichier au debut du fichier
    rewind(fichier);
    // Verifier si le premier caractere est EOF
    if (fgetc(fichier) == EOF) return vrai;
    else return faux;
}

// Messages d'erreur
void Erreur(short error) {
    if (error == 0){printf("\t\t\t\t\t\t\033[0;36m+\033[0;31m (-) Erreur: Mal saisie de donnees!\033[0;33m\n"); return;}
    if (error == 1){printf("\t\t\t\t\t\t\033[0;36m+\033[0;31m (-) Erreur: Allocation en memoire a echoue!\033[0;33m\n"); return;}
    if (error == 2){printf("\t\t\t\t\t\t\033[0;36m+\033[0;31m (-) Erreur: Ouverture du fichier a echoue!\033[0;33m\n"); return;}
    if (error == 3){printf("\t\t\t\t\t\t\033[0;36m+\033[0;31m (-) Erreur: Veuillez entrer un choix valable\033[0;32m\n"); return;}
    if (error == 4){printf("\t\t\t\t\t\t\033[0;36m+\033[0;35m (-) Aucun etudiant trouve!\n");}
    
}

// Affichage de saisie de valeur personnalisee
void entrerDonnee(void){
    printf("\t\t\t\t\t\t\033[0;36m+\033[0;32m=>");
}

// Lire le nom des deux fichiers a partir de l'utilisateur 
void LireNomFichiers(FILE **fichier, FILE **fichier_note) {
    char nom_fichier[MAX_CARACTERE];
    char nom_fichier_note[MAX_CARACTERE + 15];
    char data_path[MAX_CARACTERE + 10];

    printf("\n\t\t\t\t\t\t\033[0;36m+\033[0;33m Veuillez saisir le nom du fichier sur lequel vous souhaitez travailler: \n");
    entrerDonnee();
    scanf("%s", nom_fichier);

    // Ajouter le prefixe "data/" et le suffixe ".txt" aux noms de fichiers
    sprintf(data_path, "data\\%s.txt", nom_fichier);
    sprintf(nom_fichier_note, "data\\%s_note.txt", nom_fichier);

    // Ouvrir des fichiers
    *fichier = fopen(data_path, "a+");
    TesterFichier(*fichier);

    // Ouvrir le fichier de notes
    *fichier_note = fopen(nom_fichier_note, "a+");
    TesterFichier(*fichier_note);

    // Sauvegarder les noms complets des fichiers dans les variables globales
    strcpy(FICHIERDATA, data_path);
    strcpy(FICHIERNOTES, nom_fichier_note);
    ClearConsole(0);
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
    printf("\t\t\t\t\033[0m\n"); // reinitialiser la couleur
}

// Lancer le programme
void Lancement(void){
    Bool reponse;
    ClearConsole(0);
    printf("\n\n\n+ Veuillez mettre la fenetre de votre console en\033[1;36m plein ecran\033[0;37m pour une experience optimale");
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
    printf("\t\t\t\t+\033[0;33m des etudiants. Avec EtudGate, vous pouvez facilement ajouter, modifier et supprimer des        \033[0;36m+\n");
    printf("\t\t\t\t+\033[0;33m etudiants, ainsi que consulter la liste complete, la liste des etudiants admis et la liste des \033[0;36m+\n");
    printf("\t\t\t\t+\033[0;33m etudiants d'une filiere specifique. En outre, vous pouvez trier les etudiants par numero       \033[0;36m+\n");
    printf("\t\t\t\t+\033[0;33m Apogee, moyenne ou date d'inscription, et rechercher rapidement un etudiant par son            \033[0;36m+\n");
    printf("\t\t\t\t+\033[0;33m numero Apogee ou par d'autres criteres tels que le nom, le prenom et la date d'inscription.    \033[0;36m+\n");
    printf("\t\t\t\t+------------------------------------------------------------------------------------------------+\n");
    sleep(2);
    printf("\t\t\t\t\t\t\t\t\t\033[0;36m-Commencer?(O/N)\n");
        lireBool(&reponse);
    if (reponse == faux){fermeture();}// Quitter le programme
    ClearConsole(1);
}

// Afficher le menu principal de l'application
void MenuPrincipal(Etudiant *tableauEtudiants,FILE **fichier,FILE **fichierNote,short  taille){
    short reponse;
    Bool res;
    while(1){
        printf("\n\t\t\t\t\t\t\033[0;36m+-----------------------------\033[1;33mMenu Principal\033[0;36m----------------------------+\n");
        printf("\t\t\t\t\t\t+\033[0;33m Que souhaitez-vous faire ?    \t\t\t\t\t\033[0;36m+\n");
        printf("\t\t\t\t\t\t+\033[0;33m 1- Ajouter des etudiants dans le fichier.\t\t\t        \033[0;36m+\n");
        printf(" \t\t\t\t\t\t+\033[0;33m 2- Modifier les informations d'un etudiant.\t\t\t\t\033[0;36m+\n");
        printf("  \t\t\t\t\t\t+\033[0;33m 3- Supprimer un etudiant du fichier.\t\t\t\t\t\033[0;36m+\n");
        printf("   \t\t\t\t\t\t+\033[0;33m 4- Rechercher un ou des etudiants par nom ou prenom      \033[0;36m\t\t+\n");
        printf("    \t\t\t\t\t\t+\033[0;33m 5- Trier les etudiant selon des criteres specifiques.\033[0;36m\t\t\t+\n");
        printf("\t\t\t\t\t\t+\033[0;33m 6- Voulez-vous changer le fichier de travail actuel.  \t\t\033[0;36m+\n");
        printf("\t\t\t\t\t\t+\033[0;33m 7- Quitter l'application.\033[0;36m\t\t\t\t\t\t+\n");
        printf("\t\t\t\t\t\t\033[0;36m+-----------------------------------------------------------------------+\n");
        do{
            entrerDonnee();
            if (scanf("%hd", &reponse) != 1) {  // Lire l'entree de l'utilisateur sous la forme d'un court
                Erreur(3);
                while (getchar() != '\n');  // Effacer le tampon d'entree
            }
            if (reponse < 1 || reponse > 7){
                Erreur(3);
            }
        } while (!(reponse > 0 && reponse <= 7));
        switch (reponse){
        case 1:
            Etudiant etudiant_;
            LireEtudiant(&etudiant_,*fichier,*fichierNote);
            printf("\t\t\t\t\t\t\033[0;36m+\033[0;33m Ajouter un autre etudiant ? (O/N)\n");
            do{
                lireBool(&res);
            } while (res != faux);
            break;
        case 2:
            editEtudiantFile(tableauEtudiants,fichier,fichierNote,taille);
            break;
        case 3:;
            short num;
            printf("\t\t\t\t\t\t\033[0;36m+\033[0;33m Entrez le numero de l'etudiant que vous souhaitez supprimer ses informations: \n");
            do
            {
                entrerDonnee();
                if (scanf("%hd", &num) != 1) {  // Lire l'entree de l'utilisateur sous la forme d'un court
                    Erreur(3);
                    while (getchar() != '\n');  // Effacer le tampon d'entree
                }
                if (num < 1 || num > taille) Erreur(3);
            } while (num <= 0 || num > taille);
            suprimerEtudiant(fichier,fichierNote,tableauEtudiants[num-1]);
            break;
        case 4:
            RechercheEtudiant(tableauEtudiants,taille);
            break;
        case 5:
            unsigned int desTabSize;
            Etudiant *desTab = trierEtudiants(tableauEtudiants,taille,&desTabSize);
            if ( desTabSize == 0 ){
                Erreur(4);
                sleep(3);
                ClearConsole(0);
            }
            else if (desTab == NULL) ClearConsole(0);
            else{
                afficheTabEtudiants(desTab,desTabSize);
            }
            break;
        case 6:
            LireNomFichiers(fichier,fichierNote);
            break;
        case 7:
            fermeture();
            break;
        default:
            Erreur(3);
            break;
        }
        free(tableauEtudiants);
        unsigned int *NPL = NombrePositionLigne(*fichier);
        tableauEtudiants = tabEtudiants(*fichier,*fichierNote,NPL);
        taille = NPL[0] - 2;
    }   
}

// Droits d'auteur
void AfficherCopyright(void){
    char atSymbol = 64;
    printf("\n\t\t\t\t\t\t\033[0;36m+---------------------------------------------------------------+\n");
    printf("\t\t\t\t\t\t\033[0;36m+\t\033[0;33m\tDROITS D'AUTEUR %c 2023 EtudeGate    \t\t\033[0;36m+\n",atSymbol);
    printf("\t\t\t\t\t\t\033[0;36m+\t\033[0;33mTous droits reserves. La reproduction non autorisee     \033[0;36m+\n");
    printf("\t\t\t\t\t\t\033[0;36m+\t\033[0;33m et la distribution sont une violation de la loi.    \t\033[0;36m+\n");
    printf("\t\t\t\t\t\t\033[0;36m+---------------------------------------------------------------+\n");
}
// Fermeture de l'application
void fermeture(void) {
    ClearConsole(0);
    PrintAsciiArt();
    AfficherCopyright();
    sleep(3);
    printf("\033[0;32m (+) Programe ferme.\033[0;37m\n");
    exit(0);
}