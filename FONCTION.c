#include <stdio.h>
#include <string.h>
#include "FONCTION.h"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define RESET "\033[0m"

#define TAILLE_NOM 50

//system("cls");
//getchar();


void debiter(int *debit1, MrBARTHELEMY *user, int *use, int *u, int *nbComptes,int *numero,int *nbUtilisateurs) {

    if (user[*u].nbComptes == 0) {
        printf(RED "Aucun compte disponible\n" RESET);
        creerCompte(user, nbComptes, u,use,numero,nbUtilisateurs);
        *use = user[*u].nbComptes - 1;
        return;
    }
    if (*use < 0 || *use >= user[*u].nbComptes) {
        printf(RED "Veuillez selectionner un compte \n" RESET);
        return;
    }
    
    printf(GREEN "Combien voulez-vous retirer ?\n" RESET);
    scanf("%d", debit1);
    while(getchar() != '\n');

    while (*debit1 < 0 || *debit1 > user[*u].comptes[*use].solde) {
        if (*debit1 < 0){ 
            printf(RED "Impossible de retirer un solde negative (%d)\n" RESET);
            break;
        }
        printf(RED "Solde insuffisant (%d)\n" RESET,user[*u].comptes[*use].solde);
        scanf("%d", debit1);
        while(getchar() != '\n');
    }

    user[*u].comptes[*use].solde -= *debit1;
    printf(GREEN "Debit effectue avec succes\n" RESET);
}

void credit (int *prix2, int *credit1,MrBARTHELEMY *user, int *use, int *u, int *nbComptes,int *numero,int *nbUtilisateurs){
    if(user[*u].nbComptes==0){
    printf(RED);
    printf("Aucun compte n'est disponible pour acrediter\n");
    printf(RESET);
    creerCompte(user,&(user[*u].nbComptes),u,use,numero,nbUtilisateurs);
    *use = user[*u].nbComptes - 1;
    return;
    }
    if (*use < 0 || *use >= user[*u].nbComptes) {
    printf(RED "Compte non sélectionné\n" RESET);
    return;
}   
    printf(GREEN);
    printf("Combien voulez vous crediter\n");
    printf(RESET);
    scanf("%d",credit1); 
    while(getchar() != '\n');
    while ( *credit1<=0){
        printf(RED);
        printf("Impossible vous ne pouvez pas entrez ni de valeur negative ni une valeur null\n");
        printf(RESET);
         printf(GREEN);
        printf("Combien voulez vous crediter\n");
        printf(RESET);
        scanf("%d",credit1);
        while(getchar()!='\n');
    }
    *prix2= user[*u].comptes[*use].solde+ *credit1;
    user[*u].comptes[*use].solde=*prix2;
}

void afficher(MrBARTHELEMY *user, int *use, int *u, int *nbComptes,int *numero,int *nbUtilisateurs) {
         
    if(user[*u].nbComptes==0){
        printf(RED);
        printf("Aucun compte n'est disponible pour debiter\n");
        printf(RESET);
        creerCompte(user,&(user[*u].nbComptes),u,use,numero,nbUtilisateurs);
        return;
    }
    if (*use < 0 || *use >= user[*u].nbComptes) {
    printf(RED "Compte non selectionne\n" RESET);
    return;
}
     printf(BLUE);
     printf("Numero de compte :%d\n",user[*u].comptes[*use].numDeCompte);
    printf("Solde:%d\n",user[*u].comptes [*use].solde);
    printf(RESET);
}

void ajouter(MrBARTHELEMY  *user, int *nbComptes, int *u, int *nbComptes2,int *use, int *numero,int *nbUtilisateurs) {
    int nbr;

    if(user[*u].nbComptes==0){
        printf(RED);
        printf("Aucun compte n'est disponible pour debiter\n");
        printf(RESET);
        printf("Vous devez creer un compte d'abord\n");
        printf(YELLOW"Voulez vous creer un compte ?\n 1-Oui \n 2-Non \n"RESET);
        int a;
        scanf("%d",&a);
        while(getchar() != '\n');
        while (a<0 || a>2){
            printf(RED "Choix incorrect\n" RESET);
            printf(YELLOW"Voulez vous creer un compte ?\n 1-Oui \n 2-Non \n"RESET);
            scanf("%d",&a);
            while(getchar() != '\n');
        }
        if(a==1){
            creerCompte(user,&(user[*u].nbComptes),u,use,numero,nbUtilisateurs);
        }
        return;
    }
    if (user[*u].nbComptes == 5) {
        printf(RED "Limite atteinte (5 comptes)\n" RESET);
        return;
    }
    if (*use == -1) {
    printf(RED "Veuillez selectionner un compte\n" RESET);
    return;
}

    printf("Combien de comptes voulez-vous ajouter ? ");
    scanf("%d", &nbr);
    while(getchar() != '\n');

    // Vérifier que le nombre demandé ne dépasse pas la limite
    while (nbr <= 0 || user[*u].nbComptes + nbr > 5) {
        printf(RED "Impossible ! Reste %d place(s)\n" RESET, 5 - user[*u].nbComptes);
        scanf("%d", &nbr);
        while(getchar() != '\n');
    }

    // Boucle pour saisir chaque compte
    for (int i = 0; i < nbr; i++) {
        *numero = verificationId(user, nbUtilisateurs);
        user[*u].comptes[user[*u].nbComptes].numDeCompte = *numero;
        user[*u].comptes[user[*u].nbComptes].solde = 0;

        (user[*u].nbComptes)++; // augmenter le compteur de comptes
    }
}
void transfert(MrBARTHELEMY *user, int *nbComptes, int *u ,int *use,int *numero,int *nbUtilisateurs) {
        
    int fromAccount, toAccount, amount;
        if(user[*u].nbComptes==0){
            printf(RED);
            printf("Aucun compte n'est disponible pour debiter\n");
            printf(RESET);
            printf("Vous devez creer un compte d'abord\n");
            printf(YELLOW"Voulez vous creer un compte ?\n 1-Oui \n 2-Non \n"RESET);
            int a;
            scanf("%d",&a);
            while(getchar() != '\n');
            while (a<0 || a>2){
                printf(RED "Choix incorrect\n" RESET);
                printf(YELLOW"Voulez vous creer un compte ?\n 1-Oui \n 2-Non \n"RESET);
                scanf("%d",&a);
                while(getchar() != '\n');
            }
            if(a==1){
                creerCompte(user,&(user[*u].nbComptes),u,use,numero,nbUtilisateurs);
            }
            return;
    }
    if (*use == -1) {
    printf(RED "Veuillez selectionner un compte\n" RESET);
    return;
}
    printf("Entrez le numero du compte source : ");
    scanf("%d", &fromAccount);
    while(getchar()!='\n');
    printf("Entrez le numero du compte destination : ");
    scanf("%d", &toAccount);
    while(getchar()!='\n');
    printf("Entrez le montant a transferer : ");
    scanf("%d", &amount);
    while(getchar()!='\n');
    if (amount <= 0) {
    printf(RED "Montant invalide\n" RESET);
    return;
}

    int fromIndex = -1, toIndex = -1;


    for (int i = 0; i < user[*u].nbComptes; i++) {
        if (user[*u].comptes[i].numDeCompte == fromAccount) {
            fromIndex = i;
        }
        if (user[*u].comptes[i].numDeCompte == toAccount) {
            toIndex = i;
        }
    }
    if (fromIndex == -1 || toIndex == -1) {
        printf(RED "Erreur : Numero de compte invalide.\n" RESET);
        return;
    }
        if (fromIndex == toIndex) {
    printf(RED "Impossible de transferer vers le meme compte\n" RESET);
    return;
}
    if (user[*u].comptes[fromIndex].solde < amount) {
        printf(RED "Erreur : Solde insuffisant dans le compte source.\n" RESET);
        return;
    }
    user[*u].comptes[fromIndex].solde -= amount;
    user[*u].comptes[toIndex].solde += amount;
    printf(YELLOW "Transfert reussi : %d du compte %d au compte %d.\n" RESET, amount, fromAccount, toAccount);
}
void changerUtilisateur(MrBARTHELEMY *user, int *u, char *nom,int *nbUtilisateurs, int *use) {
    int found = 0;
    if (*nbUtilisateurs==1){
        printf(RED "Aucun autre utilisateur disponible\n" RESET);
        printf(GREEN "Utilisateur actuel : %s\n" RESET, user[*u].nom);
        printf("Voulez-vous ajouter un nouvel utilisateur ?\n");
        printf("1-Oui\n2-Non\n");
        int a;
        scanf("%d",&a);
        while(getchar()!='\n');
        while (a<0 || a>2){
            printf(RED "Choix incorrect\n" RESET);
            printf("Voulez-vous ajouter un nouvel utilisateur ?\n");
            printf("1-Oui\n2-Non\n");
            scanf("%d",&a);
            while(getchar() != '\n');
        }
        if(a==1){
            ajouterUtilisateur(user,nbUtilisateurs,nom,nbUtilisateurs);
        }
        return;
    }
        fgets(nom, TAILLE_NOM, stdin);
        (nom)[strcspn(nom, "\n")] = '\0'; 

        while(strcmp(nom,"")==0){  
            printf(GREEN"Vuillez entrez le nom de l'utilisateur a ajouter:");
            fgets(nom, TAILLE_NOM, stdin);
            (nom)[strcspn(nom, "\n")] = '\0';
        }
    for (int i = 0; i < *nbUtilisateurs; i++) {
        if (strcmp(nom, user[i].nom) == 0) {
            printf(GREEN "Utilisateur trouve\n" RESET);
            *u = i;
            *use = -1;   // 🔐 RESET DU COMPTE
            found = 1;
            break;
        }
    }

    if (!found) {
        printf(RED "Aucun utilisateur trouve\n" RESET);
    }
}

 void ajouterUtilisateur(MrBARTHELEMY *user, int *u, char *nom, int *nbUtilisateurs) {
    if (*nbUtilisateurs >= 10) {
        printf(RED "Limite d'utilisateurs atteinte\n" RESET);
        return;
    }
        fgets(nom, TAILLE_NOM, stdin);
        (nom)[strcspn(nom, "\n")] = '\0';   
        while(strcmp(nom,"")==0){  
        printf(GREEN"Vuillez entrez le nom de l'utilisateur:");
        fgets(nom, TAILLE_NOM, stdin);
        (nom)[strcspn(nom, "\n")] = '\0';
    }
    strcpy(user[*nbUtilisateurs].nom, nom);
    // Initialiser les comptes
    for(int i = 0; i < 5; i++){
        user[*nbUtilisateurs].comptes[i].numDeCompte = 0;
        user[*nbUtilisateurs].comptes[i].solde = 0;
    }

    (*nbUtilisateurs)++;
    printf(YELLOW "Utilisateur %s ajoute avec succes\n" RESET, nom);
}

void creerCompte(MrBARTHELEMY *user, int *nbComptes, int *u, int *use , int *numero,int *nbUtilisateurs) {

    if (user[*u].nbComptes == 5) {
        printf(RED "Limite atteinte (5 comptes)\n" RESET);
        return;
    }


        *numero = verificationId(user, nbUtilisateurs);

        user[*u].comptes[user[*u].nbComptes].numDeCompte = *numero;
        user[*u].comptes[user[*u].nbComptes].solde = 0;
        user[*u].nbComptes++;

    printf("Compte %d cree avec succes.\n",user[*u].comptes[user[*u].nbComptes - 1].numDeCompte);

    int check;
    printf("VuILLEZ Entrez Le  Numero de compte sur lequel on fera les operations :");
        scanf("%d",&check);
        while(getchar()!='\n');
        do{
            int index = -1;
            for (int i = 0; i < user[*u].nbComptes; i++) {
                if (check == user[*u].comptes[i].numDeCompte) {
                    index = i;
                    break;
                }
            }
            if (index == -1) {
                printf(RED "Ce compte ne vous appartient pas\n" RESET);
                return;
            }
            *use = -1;
            for(int i=0;i<user[*u].nbComptes;i++){
                if (check==user[*u].comptes[i].numDeCompte){
                    printf(GREEN);
                    printf("Compte trouve\n");
                    *use=i;
                    printf(RESET);
                    break;
                }
            }
            if(*use==-1){
                printf(RED);
                printf("Aucun compte trouve\n ");
                printf(RESET);
                printf(" Entrez Le  Numero de compte sur lequel on fera les operations\n");
                scanf("%d",&check);}
                while(getchar()!='\n');
        }while(*use==-1);
        printf(GREEN);
        if (user[*u].comptes[*use].solde==0){
        printf("VuILLEZ Entrez votre solde\n ");
        printf(RESET);
        scanf("%d",&user[*u].comptes[*use].solde);
        while(getchar()!='\n');
        }   
}

void selectionnerCompte(MrBARTHELEMY *user, int *use, int *u) {
    int check;
    printf("VuILLEZ Entrez Le  Numero de compte a selectionner :");
        scanf("%d",&check);
        while(getchar()!='\n');
        do{
            *use = -1;
            for(int i=0;i<user[*u].nbComptes;i++){
                if (check==user[*u].comptes[i].numDeCompte){
                    printf(GREEN);
                    printf("Compte trouve\n");
                    *use=i;
                    printf(RESET);
                    break;
                }
            }
            if(*use==-1){
                printf(RED);
                printf("Aucun compte trouve\n ");
                printf(RESET);
                printf(" Entrez Le  Numero de compte a selectionner\n");
                scanf("%d",&check);
                while (getchar() != '\n');
            }
        }while(*use==-1);
}
void transfererArgentUtilisateur(MrBARTHELEMY *user, int *nbUtilisateurs, int *u ) {
        
    int fromAccount, toAccount, amount;
        if(*nbUtilisateurs==1){
            printf(RED);
            printf("Aucun autre utilisateur n'est disponible pour le transfert\n");
            printf(RESET);
            return;
    }
    printf("Entrez le numero du compte source : ");
    scanf("%d", &fromAccount);
    printf("Entrez le numero du compte destination : ");
    scanf("%d", &toAccount);
    printf("Entrez le montant a transferer : ");
    scanf("%d", &amount);
    while(getchar()!='\n');

    if (amount <= 0) {
    printf(RED "Montant invalide\n" RESET);
    return;
}

    int fromIndex = -1, toIndex = -1;
    int toUserIndex = -1;
    for (int i = 0; i < *nbUtilisateurs; i++) {
        if (i == *u) continue; 
        for (int j = 0; j < user[i].nbComptes; j++) {
            if (user[i].comptes[j].numDeCompte == toAccount) {
                toUserIndex = i;
                toIndex = j;
                printf(GREEN "Utilisateur  : %s\n" RESET, user[toUserIndex].nom);
                break;
            }
        }
        if (toUserIndex != -1) {
            printf(GREEN "Utilisateur trouve : %s\n" RESET, user[toUserIndex].nom);
            break;
        }
    }
    for (int i = 0; i < user[*u].nbComptes; i++) {
        if (user[*u].comptes[i].numDeCompte == fromAccount) {
            fromIndex = i;
            printf(GREEN "Compte trouve : %d\n" RESET, user[*u].comptes[fromIndex].numDeCompte);        
            break;
        }
    }
    if (fromIndex == -1 || toIndex == -1) {
            if(fromIndex==-1){
                printf(RED " Compte de l'expediteur introuvable " RESET);
                return;
            }
            if(toIndex==-1){
                printf(RED " Compte du destinateur  introuvable " RESET);
                return;
            }
    }
    if (fromIndex == toIndex && toUserIndex == *u) {
        printf(RED "Erreur : Impossible de transferer de l'argent sur le meme compte.\n" RESET);
        return;
    }
    if (user[*u].comptes[fromIndex].solde < amount) {
        printf(RED "Erreur : Solde insuffisant.\n" RESET);
        return;
    }
    user[*u].comptes[fromIndex].solde -= amount;
    user[toUserIndex].comptes[toIndex].solde += amount;
    printf(GREEN "Transfert effectue avec succes.\n" RESET);
}

int verificationId(MrBARTHELEMY *user, int *nbUtilisateurs) {
    int max = 0;

    for (int i = 0; i < *nbUtilisateurs; i++) {
        for (int j = 0; j < user[i].nbComptes; j++) {
            if (user[i].comptes[j].numDeCompte > max) {
                max = user[i].comptes[j].numDeCompte;
            }
        }
    }
    return max + 1;
}
void afficherToutCompte(MrBARTHELEMY *user, int *nbUtilisateurs,int *u)
{
    if (user[*u].nbComptes == 0) {
        printf(RED "Aucun compte disponible\n" RESET);
        return;
    }

    printf(BLUE "Comptes de l'utilisateur %s:\n" RESET, user[*u].nom);
    for (int i = 0; i < user[*u].nbComptes; i++) {
        printf("Compte %d: Numero de compte: %d, Solde: %d\n", i + 1, user[*u].comptes[i].numDeCompte, user[*u].comptes[i].solde);
    }
}
void sauvegarderDansUnFichierBinaire(MrBARTHELEMY *user, int *nbUtilisateurs) {
    FILE *fichier = fopen("utilisateurs.dat", "wb");
    if (fichier == NULL) {
        printf(RED "Erreur lors de l'ouverture du fichier pour la sauvegarde.\n" RESET);
        return;
    }
    fwrite(nbUtilisateurs, sizeof(int), 1, fichier);
    fwrite(user, sizeof(MrBARTHELEMY), *nbUtilisateurs, fichier);
    fclose(fichier);
    printf(GREEN "Sauvegarde reussie dans utilisateurs.dat\n" RESET);
}
void chargerDepuisUnFichierBinaire(MrBARTHELEMY *user, int *nbUtilisateurs) {
    FILE *fichier = fopen("utilisateurs.dat", "rb");
    if (fichier == NULL) {
        printf(RED "Aucun fichier de sauvegarde trouve. Demarrage avec des donnees vides.\n" RESET);
        *nbUtilisateurs = 1;
        return;
    }
    fread(nbUtilisateurs, sizeof(int), 1, fichier);
    fread(user, sizeof(MrBARTHELEMY), *nbUtilisateurs, fichier);
    fclose(fichier);
    printf(GREEN "Donnees chargees depuis utilisateurs.dat\n" RESET);
}