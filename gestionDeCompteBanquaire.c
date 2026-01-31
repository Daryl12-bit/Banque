#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FONCTION.h"
/*----------------------------------------------------------------- */  
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define RESET "\033[0m"

#define TAILLE_NOM 50
/*----------------------------------------------------------------- */

int main(){
    /*DECLARATION DE LA STRUCTURE */
    MrBARTHELEMY B1[10]={0};
    strcpy(B1[0].nom,"DARYL");
    /*Fin */
    int a;
    int nombreDeUtilisateur=1;
    int choix=5;
    int prix;
    int prix2;
    int debit1;
    int credit1;
    int numero=0;
    int use = -1;
    int u;
    int i=0;
    char nom[TAILLE_NOM];
     printf(GREEN"Vuillez entrez votre nom:");
    printf(RESET);
    fgets(nom, TAILLE_NOM, stdin);
    nom[strcspn( nom, "\n")] = '\0';
    do{
        u = -1;
            if (strcmp(nom,"")==0)
            {
                printf(RED"AUucun nom n'a ete entre"RESET);
                getchar();
                system("cls");
                printf(GREEN"Vuillez entrez votre nom:");
                printf(RESET);
                fgets(nom, TAILLE_NOM, stdin);
                nom[strcspn( nom, "\n")] = '\0';
            }
            else{
                for (int i = 0; i < nombreDeUtilisateur; i++) {
                    if (strcmp(nom, B1[i].nom) == 0) {
                        u = i;
                        break;
                    }
                }    
                if(u==-1){
                    printf(RED);
                    printf("Aucun utilisateur  trouve\n ");
                    printf(RESET);
                    getchar();
                    system("cls");
                    printf(GREEN"Vuillez entrez votre nom: ");
                    printf(RESET);
                    fgets(nom, TAILLE_NOM, stdin);
                    nom[strcspn( nom, "\n")] = '\0';   
                    }
            }
    }while(u==-1 || strcmp(nom,"")==0 );

    printf(GREEN "Bienvenue a la %s\n" RESET, B1[u].nom);
    while(choix!=4){
 // --- création initiale ---
            getchar();
            system("cls");
            printf(GREEN);
            printf("\nQue voulez vous faire ?\n 10-Cree un compte \n 1-Debiter\n 2-Crediter\n 3-Afficher\n 4-Arreter\n 5-Ajouter\n 6-Transfert\n 7-Changer Utilisateur\n 8-ajouter Utilisateur\n 9-selectionner un compte\n 11-transferer argent entre utilisateur\n 12-Afficher tous les comptes\n 13-Sauvegarder dans un fichier binaire\n 14-Charger depuis un fichier binaire\n");
            printf(RESET);
            scanf("%d",&choix);
            while (choix>14 || choix <=0){
                system("cls");
                printf(RED);
                printf("Choix incorrect\n");
                printf(RESET);
                printf("10-Cree un compte \n 1-Debiter\n 2-Crediter\n 3-Afficher\n 4-Arreter\n 5-Ajouter\n 6-Transfert\n 7-Changer Utilisateur\n 8-ajouter Utilisateur\n 9-selectionner un compte\n 11-transferer argent entre utilisateur \n 12-Afficher tous les comptes\n 13-Sauvegarder dans un fichier binaire\n 14-Charger depuis un fichier binaire\n");
                printf(RESET);
                scanf("%d",&choix);
                while(getchar() != '\n');
            }
            printf(RESET);
            
            switch (choix)
            {
            //debut case 1-----------------------------------------------------------------------------------------------
            case 1:
                do{
                    printf("Voulez vous debiter  de votre compte ?\n 1-Oui \n 2-Non  \n");
                    scanf("%d",&a);
                    while(getchar() != '\n');
                }while (a<0 || a>2);

                if (a==1){
                debiter(&debit1,B1,&use,&u,&B1[u].nbComptes,&numero,&nombreDeUtilisateur);

                if (use != -1) {
                    printf(YELLOW "Solde:%d\nMontant debiter:%d\n" RESET,
                    B1[u].comptes[use].solde, debit1);
                }
                    break;
                }
                else {
                    break;
                }
                
                //fin case 1-----------------------------------------------------------------------------------------------

            //debut case 2-----------------------------------------------------------------------------------------------
            case 2:
                do{
                    printf("Voulez vous acrediter votre compte ?\n 1-Oui \n 2-Non \n");
                    scanf("%d",&a);
                    while(getchar() != '\n');
                }while (a<0 || a>2);

                if (a==1){
                    credit(&prix2,&credit1,B1,&use,&u,&B1[u].nbComptes,&numero,&nombreDeUtilisateur);
                    if (use != -1) {
                    printf(YELLOW "Solde:%d\nMontant crediter:%d\n" RESET,
                    B1[u].comptes[use].solde, credit1);
                }
                break;
                }
                else {
                    break;
                }
            //fin case 2-----------------------------------------------------------------------------------------------
            //debut case 3-----------------------------------------------------------------------------------------------
            case 3:
                afficher(B1,&use,&u,&B1[u].nbComptes,&numero,&nombreDeUtilisateur);
                getchar();
                break;
            //fin case 3-----------------------------------------------------------------------------------------------
            //debut case 4-----------------------------------------------------------------------------------------------
            case 4:
                printf("Fin du programme\n");
                break;
            //fin case 4-----------------------------------------------------------------------------------------------
            //debut case 5-----------------------------------------------------------------------------------------------
            case 5:
                do{
                    printf("Voulez vous ajouter un nouveau compte ?\n 1-Oui \n 2-Non \n");
                    scanf("%d",&a);
                    while(getchar() != '\n');
                }while (a<0 || a>2);

                if (a==1){
                    ajouter (B1, &B1[u].nbComptes, &u, &B1[u].nbComptes,&use,&numero,&nombreDeUtilisateur);
                    break;
                }
                else {
                    break;
                }
            //fin case 5-----------------------------------------------------------------------------------------------
            //debut case 6-----------------------------------------------------------------------------------------------
            case 6:
                do{
                    printf("Voulez vous transferer de l'argent de d'un compte a un autre  compte ?\n 1-Oui \n 2-Non \n");
                    scanf("%d",&a);
                    while(getchar() != '\n');
                }while (a<0 || a>2);

                if (a==1){
                    transfert(B1, &B1[u].nbComptes, &u,&use,&numero,&nombreDeUtilisateur);
                    break;
                }
                else {
                    break;
                }
            case 7:
                changerUtilisateur(B1,&u,nom,&nombreDeUtilisateur,&use);
                break;
            case 8:
                ajouterUtilisateur(B1,&u,nom,&nombreDeUtilisateur);
                break;
            case 9:
                selectionnerCompte(B1, &use, &u);
                break;
            case 10:
                do{
                    printf("Voulez vous creer un compte ?\n 1-Oui \n 2-Non \n");
                    scanf("%d",&a);
                    while(getchar() != '\n');
                }while (a<0 || a>2);

                if (a==1){
                    creerCompte(B1, &B1[u].nbComptes, &u,&use,&numero,&nombreDeUtilisateur);
                    break;
                }
                else {
                    break;
                }
            case 11:
                do{
                    printf("Voulez vous transferer de l'argent a un autre utilisateur ?\n 1-Oui \n 2-Non \n");
                    scanf("%d",&a);
                    while(getchar() != '\n');
                }while (a<0 || a>2);

                if (a==1){
                    transfererArgentUtilisateur(B1, &nombreDeUtilisateur, &u );
                    break;
                }
                else {
                    break;
                }
            case 12:
                afficherToutCompte(B1, &nombreDeUtilisateur,&u);
                getchar();
                break;
            case 13:
                sauvegarderDansUnFichierBinaire(B1, &nombreDeUtilisateur);
                getchar();
                break;
            case 14:
                chargerDepuisUnFichierBinaire(B1, &nombreDeUtilisateur);
                getchar();
                break;
            default:
                printf(RED);
                printf("Choix incorrect");
                printf(RESET);
                break;
            }
    // --- fin création initiale ---
       
    }
        return 0;
}
/*----------------------------------------------------------------- */
