#ifndef FONCTION_H
#define FONCTION_H

typedef enum {
    ACTIVE,
    CLOSED,
}StatusCompte;
typedef struct Compte
{
    int idCompte;
    int RIB;
    float solde;
    StatusCompte status;

} Compte;


typedef struct Client
{
    int idClient;
    char nom[50];
    int pin;
    int nbComptes;
    Compte *compte;
} Client;

typedef struct Banque
{
    char nomBanque[50];
    int nbClients;
    int nbComptesGlobal;  
    int currenntClientIndex;  
    Client *client;
} Banque;
void afficherMenuPrincipal(Banque *banque);
void afficherMenuClient(Banque *banque);
void afficherMenuAdmin(Banque *banque);
void afficherMenuGestionComptes(Banque *banque);
void afficherMenuDepot(Banque *banque);
void afficherMenuRetrait(Banque *banque);
void afficherMenuVirement(Banque *banque);
void afficherMenuCreationCompte(Banque *banque);
void afficherMenuSuppressionCompte(Banque *banque);
void afficherMenuModificationCompte(Banque *banque);
void afficherMenuChoixClient(Banque *banque);
void afficherMenuConsultationSolde(Banque *banque);
void afficherMenuCreationClient(Banque *banque);
void afficherMenuSuppressionClient(Banque *banque);
void afficherMenuModificationClient(Banque *banque);
void afficherMenuConsultationClients(Banque *banque);
void afficherMenuConsultationComptes(Banque *banque);
void afficherInformationsClient(Banque *banque);
void chargerBanque(Banque *banque);
void pauseEtNettoie();
int vreficationIdClient(Banque *banque, int idClient);
void statusClientsComptes(Banque *banque);
void sauvegarderBanque(Banque *banque); 
#endif