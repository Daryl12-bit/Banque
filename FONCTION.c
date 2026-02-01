#include <stdio.h>
#include <stdlib.h>
#include "FONCTION.h"

#define MAX_CLIENTS 10
#define MAX_COMPTES 5

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"

void afficherMenuPrincipal(Banque *banque)
{
    // Code pour afficher le menu principal
    int choice;
    printf(CYAN "_______________________________________________________________Menu Principal:_________________________________________________________\n");
    printf("0. Creer Client\n");
    printf("1. Menu Client\n");
    printf("2. Menu Administrateur\n");
    printf("3. Quitter\n" RESET);
    while (scanf("%d", &choice) != 1 || choice < 0 || choice > 3)
    {
        printf(RED "Choix invalide. Veuillez entrer un nombre entre 0 et 3: " RESET);
        while (getchar() != '\n')
            ; // Clear invalid input
    }
    switch (choice)
    {
    case 0:
        afficherMenuCreationClient(banque);
        break;
    case 1:
        afficherMenuClient(banque);
        break;
    case 2:
        afficherMenuAdmin(banque);
        break;
    case 3:
        printf(MAGENTA "Au revoir !\n" RESET);
        exit(0); // For exiting the program entirely even if called from a function
        break;

    default:
        break;
    }
}

int vreficationIdClient(Banque *banque, int idClient)
{
    // Code pour vérifier l'ID client
    for (int i = 0; i < banque->nbClients; i++)
    {
        if (banque->client[i].idClient == idClient)
        {
            return 1; // ID client déjà utilisé
        }
    }
    return 0; // ID client disponible
}
void afficherMenuCreationClient(Banque *banque)
{
    // Code pour afficher le menu de création de client
    printf(GREEN "Affichage du menu de création de client...\n" RESET);
    // Implémenter les options de création de client ici
    if (banque->nbClients >= MAX_CLIENTS)
    {
        printf(RED "Nombre maximum de clients atteint (%d). Impossible d'ajouter un nouveau client.\n" RESET, MAX_CLIENTS);
        return;
    }
    Client *newClient = &banque->client[banque->nbClients];

    printf("Entrez le nom du client: ");
    scanf("%s", newClient->nom);
    printf("Entrez le PIN du client (code numérique): ");
    while (scanf("%d", &newClient->pin) != 1)
    {
        printf(RED "PIN invalide. Veuillez entrer un code numérique: " RESET);
        while (getchar() != '\n')
            ; // Clear invalid input
    }

    int idClientTest;
    do
    {
        idClientTest = rand() % 1000 + 1; // Générer un ID client aléatoire entre 1 et 1000
    } while (vreficationIdClient(banque, idClientTest)); // Vérifier si l'ID est déjà utilisé
    newClient->idClient = idClientTest;
    newClient->nbComptes = 0;
    newClient->compte = malloc(sizeof(Compte) * MAX_COMPTES); // Allouer de l'espace pour les comptes du client
    banque->currenntClientIndex = banque->nbClients;
    banque->nbClients++;
    printf(GREEN "Client créé avec succès. ID Client: %d, Nom: %s\n" RESET, newClient->idClient, newClient->nom);
}

void afficherMenuClient(Banque *banque)
{
    // Code pour afficher le menu client
    printf(GREEN "Affichage du menu client...\n" RESET);
    // Implémenter les options du menu client ici
    printf(CYAN "_______________________________________________________________Menu Client:_________________________________________________________\n");
    printf("0. Creation de compte\n");
    printf("1. Gestion des Comptes\n");
    printf("2. Retrait d'argent\n");
    printf("3. Dépôt d'argent\n");
    printf("4. Voir le solde\n");
    printf("5. Virement entre comptes\n");
    printf("6. Suppression des comptes\n");
    printf("7. Vos informations\n");
    printf("8. Retour au menu principal\n" RESET);
    int choice;
    while (scanf("%d", &choice) != 1 || choice < 0 || choice > 8)
    {
        printf(RED "Choix invalide. Veuillez entrer un nombre entre 0 et 8: " RESET);
        while (getchar() != '\n')
            ; // Clear invalid input
    }
    switch (choice)
    {
    case 0:
        afficherMenuCreationCompte(banque);
        break;
    case 1:
        afficherMenuGestionComptes(banque);
        break;
    case 2:
        afficherMenuRetrait(banque);
        break;
    case 3:
        afficherMenuDepot(banque);
        break;
    case 4:
        afficherMenuConsultationSolde(banque);
        break;
    case 5:
        afficherMenuVirement(banque);
        break;
    case 6:
        afficherMenuSuppressionCompte(banque);
        break;
    case 7:
        afficherInformationsClient(banque);
        break;
    case 8:
        break; // Retourner au menu principal
    default:
        perror("Choix invalide dans le menu client.");
        break;
    }
}

void afficherMenuAdmin(Banque *banque)
{
    // Code pour afficher le menu administrateur
    printf(YELLOW "Affichage du menu administrateur...\n" RESET);
    // Implémenter les options du menu administrateur ici
}
// Autres fonctions de menu à implémenter ici_____________________________________________________

void afficherMenuCreationCompte(Banque *banque)
{
    // Code pour afficher le menu de création de compte
    printf(GREEN "Affichage du menu de création de compte...\n" RESET);
    // Implémenter les options de création de compte ici
    if (banque->nbClients == 0)
    {
        printf(RED "Aucun client disponible. Veuillez créer un client avant de créer un compte.\n" RESET);
        return;
    }
    printf("Liste des clients disponibles:\n");
    for (int i = 0; i < banque->nbClients; i++)
    {
        printf("%d. %s (ID: %d)\n", i + 1, banque->client[i].nom, banque->client[i].idClient);
    }
    printf("Sélectionnez le numéro du client pour lequel vous souhaitez créer un compte: ");
    int clientIndex;
    while (scanf("%d", &clientIndex) != 1 || clientIndex < 1 || clientIndex > banque->nbClients)
    {
        printf(RED "Choix invalide. Veuillez entrer un nombre valide: " RESET);
        while (getchar() != '\n')
            ; // Clear invalid input
    }
    Client *selectedClient = &banque->client[clientIndex - 1];
    if (selectedClient->nbComptes >= MAX_COMPTES)
    {
        printf(RED "Le client a déjà le nombre maximum de comptes (%d).\n" RESET, MAX_COMPTES);
        return;
    }
    // Création du nouveau compte

    banque->client[clientIndex - 1].compte[selectedClient->nbComptes].idCompte = banque->nbComptesGlobal + 1;
    banque->client[clientIndex - 1].compte[selectedClient->nbComptes].RIB = 100 + banque->nbComptesGlobal;
    banque->client[clientIndex - 1].compte[selectedClient->nbComptes].solde = 0.0f;
    selectedClient->nbComptes++;
    banque->nbComptesGlobal++;
    printf(GREEN "Compte créé avec succès pour le client %s. ID Compte: %d, RIB: %d, Solde: %.2f\n" RESET,
           selectedClient->nom,
           banque->client[clientIndex - 1].compte[selectedClient->nbComptes - 1].idCompte,
           banque->client[clientIndex - 1].compte[selectedClient->nbComptes - 1].RIB,
           banque->client[clientIndex - 1].compte[selectedClient->nbComptes - 1].solde);
}
void afficherMenuGestionComptes(Banque *banque)
{
    // Code pour afficher le menu de gestion des comptes
    printf(GREEN "Affichage du menu de gestion des comptes...\n" RESET);
    // Implémenter les options de gestion des comptes ici
}

void afficherMenuRetrait(Banque *banque)
{
    // Code pour afficher le menu de retrait
    printf(GREEN "Affichage du menu de retrait...\n" RESET);
    // Implémenter les options de retrait ici
}

void afficherMenuDepot(Banque *banque)
{
    // Code pour afficher le menu de dépôt
    printf(GREEN "Affichage du menu de dépôt...\n" RESET);
    // Implémenter les options de dépôt ici
}

void afficherMenuConsultationSolde(Banque *banque)
{
    // Code pour afficher le menu de consultation de solde
    printf(GREEN "Affichage du menu de consultation de solde...\n" RESET);
    // Implémenter les options de consultation de solde ici
}

void afficherMenuVirement(Banque *banque)
{
    // Code pour afficher le menu de virement
    printf(GREEN "Affichage du menu de virement...\n" RESET);
    // Implémenter les options de virement ici
}

void afficherMenuSuppressionCompte(Banque *banque)
{
    // Code pour afficher le menu de suppression de compte
    printf(GREEN "Affichage du menu de suppression de compte...\n" RESET);
    // Implémenter les options de suppression de compte ici
}
void afficherInformationsClient(Banque *banque)
{
    // Code pour afficher les informations du client
    printf(GREEN "Affichage des informations du client...\n" RESET);
    // Implémenter l'affichage des informations du client ici
    if (banque->nbClients == 0)
    {
        printf(RED "Aucun client disponible.\n" RESET);
        return;
    }
    if (banque->currenntClientIndex < 0 || banque->currenntClientIndex >= banque->nbClients)
    {
        printf(RED "Index de client courant invalide.\n" RESET);
        return;
    }
    Client *currentClient = &banque->client[banque->currenntClientIndex];
    printf("Informations du client:\n");
    printf("ID Client: %d\n", currentClient->idClient);
    printf("Nom: %s\n", currentClient->nom);
    printf("Nombre de comptes: %d\n", currentClient->nbComptes);
    for (int i = 0; i < currentClient->nbComptes; i++)
    {
        Compte *compte = &currentClient->compte[i];
        printf("  Compte %d: ID Compte: %d, RIB: %d, Solde: %.2f\n", i + 1, compte->idCompte, compte->RIB, compte->solde);
    }
}