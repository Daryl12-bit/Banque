#ifndef FONCTION_H
#define FONCTION_H

#define TAILLE_NOM 50

typedef struct Compte{
    int numDeCompte;
    int solde;
}CompteDeMrBARTHELEMY;

typedef struct Utilisateur{
    CompteDeMrBARTHELEMY comptes[5];
    int nbComptes;
    char nom[TAILLE_NOM];
} MrBARTHELEMY;

void debiter(int *debit1 , MrBARTHELEMY *user,int *use, int *u, int *nbComptes,int *numero,int *nbUtilisateurs);
void credit( int *prix2,int *credit1,MrBARTHELEMY *user, int *use, int *u, int *nbComptes,int *numero,int *nbUtilisateurs);
void  afficher(MrBARTHELEMY *user,int *use, int *u, int *nbComptes,int *numero,int *nbUtilisateurs);
void ajouter(MrBARTHELEMY *user,int *i, int *u, int *nbComptes,int *use,int *numero,int *nbUtilisateurs);
void transfert(MrBARTHELEMY *user, int *nbComptes, int *u,int *use,int *numero,int *nbUtilisateurs);
void ajouterUtilisateur(MrBARTHELEMY *user, int *u, char *nom, int *nbUtilisateurs);
void changerUtilisateur(MrBARTHELEMY *user, int *u, char *nom, int *nbUtilisateurs,int *use);
void creerCompte(MrBARTHELEMY *user, int *nbComptes, int *u, int *use,int *numero,int *nbUtilisateurs);
void selectionnerCompte(MrBARTHELEMY *user, int *use, int *u);
void transfererArgentUtilisateur(MrBARTHELEMY *user, int *nbUtilisateurs, int *u );
int verificationId(MrBARTHELEMY *user, int *nbUtilisateurs);
void afficherToutCompte(MrBARTHELEMY *user, int *nbUtilisateurs,int *u);
void sauvegarderDansUnFichierBinaire(MrBARTHELEMY *user, int *nbUtilisateurs);
void chargerDepuisUnFichierBinaire(MrBARTHELEMY *user, int *nbUtilisateurs);

#endif
