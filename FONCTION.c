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
        pauseEtNettoie();
        break;
    case 1:
        afficherMenuClient(banque);
        pauseEtNettoie();
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
void pauseEtNettoie()
{
    printf("\nAppuyez sur Entrée pour continuer...");
    while (getchar() != '\n'); // vide le buffer
    getchar();                 // attend une vraie Entrée
    system("clear");           // ou system("cls") sur Windows
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
    printf("8. Changer de client\n");
    printf("9. Sauvegarder Client\n");
    printf("10.Charger Client\n");
    printf("11.Retour au menu principal\n" RESET);
    int choice;
    while (scanf("%d", &choice) != 1 || choice < 0 || choice > 11)
    {
        printf(RED "Choix invalide. Veuillez entrer un nombre entre 0 et 11: " RESET);
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
        afficherMenuChoixClient(banque);
        break;
    case 9:
        sauvegarderBanque(banque);
        break; // Retourner au menu principal
    case 10:
        chargerBanque(banque);
        break;
    case 11:
        break;
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
    banque->client[clientIndex - 1].compte[selectedClient->nbComptes].RIB = rand() % 9000 + 1000 + banque->nbComptesGlobal;
    banque->client[clientIndex - 1].compte[selectedClient->nbComptes].solde = 0.0f;
    selectedClient->nbComptes++;
    banque->nbComptesGlobal++;
    printf(GREEN "Compte créé avec succès pour le client %s. ID Compte: %d, RIB: %d, Solde: %.2f\n" RESET,
           selectedClient->nom,
           banque->client[clientIndex - 1].compte[selectedClient->nbComptes - 1].idCompte,
           banque->client[clientIndex - 1].compte[selectedClient->nbComptes - 1].RIB,
           banque->client[clientIndex - 1].compte[selectedClient->nbComptes - 1].solde);
    printf("Voulez vous changer votre solde initial ? \n 1-Oui\n 2-Non\n: ");
    int choix;
    while (scanf("%d", &choix) != 1 || (choix != 1 && choix != 2))
    {
        printf(RED "Choix invalide. Veuillez entrer 1 pour Oui ou 2 pour Non: " RESET);
        while (getchar() != '\n')
            ; // Clear invalid input
    }
    if (choix == 1)
    {
        printf("Entrez le montant initial à déposer sur le compte: ");
        float montantInitial;
        while (scanf("%f", &montantInitial) != 1 || montantInitial < 0)
        {
            printf(RED "Montant invalide. Veuillez entrer un montant positif: " RESET);
            while (getchar() != '\n')
                ; // Clear invalid input
        }
        banque->client[clientIndex - 1].compte[selectedClient->nbComptes - 1].solde = montantInitial;
        printf(GREEN "Montant initial de %.2f déposé sur le compte.\n" RESET, montantInitial);
    }
    printf("Vous pouvez maintenant gérer ce compte depuis le menu client.\n");
}
void afficherMenuGestionComptes(Banque *banque)
{
    // Code pour afficher le menu de gestion des comptes
    printf(GREEN "Affichage du menu de gestion des comptes...\n" RESET);
    // Implémenter les options de gestion des comptes ici
    // iCI ON POURRAIT AJOUTER DES FONCTIONNALITES COMME MODIFIER LE COMPTE, ETC .Mais le plus important est de voir les comptes disponibles
    if (banque->nbClients == 0)
    {
        printf(RED "Aucun client disponible.\n" RESET);
        return;
    }
    Client *currentClient = &banque->client[banque->currenntClientIndex];
    if (currentClient->nbComptes == 0)
    {
        printf(RED "Aucun compte disponible pour le client %s.\n" RESET, currentClient->nom);
        return;
    }
    printf("Comptes du client %s:\n", currentClient->nom);
    for (int i = 0; i < currentClient->nbComptes; i++)
    {
        Compte *compte = &currentClient->compte[i];
        printf("  Compte %d: ID Compte: %d, RIB: %d, Solde: %.2f\n", i + 1, compte->idCompte, compte->RIB, compte->solde);
    }
}

void afficherMenuRetrait(Banque *banque)
{
    // Code pour afficher le menu de retrait
    printf(GREEN "Affichage du menu de retrait...\n" RESET);
    // Implémenter les options de retrait ici
    // Les fonctionnalités de retrait seront implémentées ici
    if (banque->nbClients == 0)
    {
        printf(RED "Aucun client disponible.\n" RESET);
        return;
    }
    Client *currentClient = &banque->client[banque->currenntClientIndex];
    if (currentClient->nbComptes == 0)
    {
        printf(RED "Aucun compte disponible pour le client %s.\n" RESET, currentClient->nom);
        return;
    }
    printf("Retrait d'argent pour le client %s:\n", currentClient->nom);
    for (int i = 0; i < currentClient->nbComptes; i++)
    {
        Compte *compte = &currentClient->compte[i];
        printf("  Compte %d: ID Compte: %d, RIB: %d, Solde: %.2f, Statut: %s\n", i + 1, compte->idCompte, compte->RIB, compte->solde, compte->status == ACTIVE ? "Actif" : "Inactif");
    }
    printf("Entrez le numéro du compte sur lequel vous souhaitez effectuer le retrait: ");
    int numCompte;
    int attemptBeforeClosedCompte = 0;
    while (scanf("%d", &numCompte) != 1 || numCompte < 1 || numCompte > currentClient->nbComptes)
    {
        printf(RED "Numéro de compte invalide. Veuillez entrer un numéro de compte valide: " RESET);
        while (getchar() != '\n')
            ; // Clear invalid input
        attemptBeforeClosedCompte++;
        if (attemptBeforeClosedCompte > 5)
        {
            printf(RED "Trop de tentatives invalides. Retour au menu principal.\n" RESET);
            statusClientsComptes(banque);
            return;
        }
    }
    if (currentClient->compte[numCompte - 1].status == CLOSED)
    {
        printf(RED "Le compte sélectionné est fermé. Impossible d'effectuer un retrait.\n" RESET);
        return;
    }
    attemptBeforeClosedCompte = 0;
    currentClient->compte[numCompte - 1];

    printf("Combieen d'argent voulez-vous retirer ?\n");
    float montant;
    while (scanf("%f", &montant) != 1 || montant <= 0)
    {
        printf(RED "Montant invalide. Veuillez entrer un montant positif: " RESET);
        while (getchar() != '\n')
            ; // Clear invalid input
            if (attemptBeforeClosedCompte > 5)
        {
            printf(RED "Trop de tentatives invalides. Retour au menu principal.\n" RESET);
            statusClientsComptes(banque);
            return;
        }
    }
    if (montant > currentClient->compte[numCompte - 1].solde)
    {
        printf(RED "Fonds insuffisants pour ce retrait. Solde actuel: %.2f\n" RESET, currentClient->compte[numCompte - 1].solde);
        return;
    }
    currentClient->compte[numCompte - 1].solde -= montant;
    // Ici, on pourrait ajouter la logique pour sélectionner le compte et effectuer le retrait
    printf(GREEN "Retrait de %.2f effectué avec succès sur le compte %d pour le client %s.\n" RESET, montant, numCompte, currentClient->nom);
}

void afficherMenuDepot(Banque *banque)
{
    // Code pour afficher le menu de dépôt
    printf(GREEN "Affichage du menu de dépôt...\n" RESET);
    // Implémenter les options de dépôt ici
    if (banque->nbClients == 0)
    {
        printf(RED "Aucun client disponible.\n" RESET);
        return;
    }
    Client *currentClient = &banque->client[banque->currenntClientIndex];
    if (currentClient->nbComptes == 0)
    {
        printf(RED "Aucun compte disponible pour le client %s.\n" RESET, currentClient->nom);
        return;
    }
    
    printf("Dépôt d'argent pour le client %s:\n", currentClient->nom);
    for (int i = 0; i < currentClient->nbComptes; i++)
    {
        Compte *compte = &currentClient->compte[i];
        printf("  Compte %d: ID Compte: %d, RIB: %d, Solde: %.2f, Statut: %s\n", i + 1, compte->idCompte, compte->RIB, compte->solde, compte->status == ACTIVE ? "Actif" : "Inactif");
    }
    int attemptBeforeClosedCompte = 0;
    printf("Entrez le numéro du compte sur lequel vous souhaitez effectuer le dépôt: ");
    int numCompte;
    while (scanf("%d", &numCompte) != 1 || numCompte < 1 || numCompte > currentClient->nbComptes)
    {
        printf(RED "Numéro de compte invalide. Veuillez entrer un numéro de compte valide: " RESET);
        while (getchar() != '\n')
            ; // Clear invalid input
        attemptBeforeClosedCompte++;
        if (attemptBeforeClosedCompte > 5)
        {
            printf(RED "Trop de tentatives invalides. Retour au menu principal.\n" RESET);
            statusClientsComptes(banque);
            return;
        }
    }
    currentClient->compte[numCompte - 1];
    attemptBeforeClosedCompte = 0;
    printf("Entrez le montant à déposer: ");
    float montant;
    while (scanf("%f", &montant) != 1 || montant <= 0)
    {
        printf(RED "Montant invalide. Veuillez entrer un montant positif: " RESET);
        while (getchar() != '\n')
            ; // Clear invalid input
            attemptBeforeClosedCompte++;
        if (attemptBeforeClosedCompte > 5)
        {
            printf(RED "Trop de tentatives invalides. Retour au menu principal.\n" RESET);
            statusClientsComptes(banque);
            return;
        }
    }
    if (currentClient->compte[numCompte - 1].status == CLOSED)
    {
        printf(RED "Le compte sélectionné est fermé. Impossible d'effectuer un dépôt.\n" RESET);
        return;
    }
    currentClient->compte[numCompte - 1].solde += montant;
    // Ici, on pourrait ajouter la logique pour sélectionner le compte et effectuer le dépôt
    printf(GREEN "Dépôt de %.2f effectué avec succès sur le compte %d pour le client %s.\n" RESET, montant, numCompte, currentClient->nom);
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
    //Pour effectuer un virement entre comptes , il faut sélectionner le compte source et le compte destination mais avant tout vérifier si les comptes existent et si le solde est suffisant   et aussi s'assurer que les deux comptes ne sont pas les mêmes et que le montant est positif et inférieur au solde du compte source et enfin effectuer le virement en débitant le compte source et en créditant le compte destination et afficher un message de confirmation mais s'en oublier quz celui qui envoit doit entrer son pin pour valider l'opération et aussi mettre le RIB des deux comptes pour éviter les erreurs
    if (banque->nbClients == 0)
    {
        printf(RED "Aucun client disponible.\n" RESET);
        return;
    }
    Client *currentClient = &banque->client[banque->currenntClientIndex];
    if (currentClient->nbComptes < 2)
    {
        printf(RED "Le client %s doit avoir au moins deux comptes pour effectuer un virement.\n" RESET, currentClient->nom);
        return;
    }
    printf("Virement entre comptes pour le client %s:\n", currentClient->nom);
    for (int i = 0; i < currentClient->nbComptes; i++)
    {
        Compte *compte = &currentClient->compte[i];
        printf("  Compte %d: ID Compte: %d, RIB: %d, Solde: %.2f, Statut: %s\n", i + 1, compte->idCompte, compte->RIB, compte->solde, compte->status == ACTIVE ? "Actif" : "Inactif");
    }
    printf("Entrez le numéro du compte source: ");
    int attemptBeforeClosedCompte = 0;
    int compteSourceIndex;
    while (scanf("%d", &compteSourceIndex) != 1 || compteSourceIndex < 1 || compteSourceIndex > currentClient->nbComptes)
    {
        printf(RED "Numéro de compte invalide. Veuillez entrer un numéro de compte valide: " RESET);
        while (getchar() != '\n')
            ; // Clear invalid input
        attemptBeforeClosedCompte++;
        if (attemptBeforeClosedCompte > 5)
        {
            printf(RED "Trop de tentatives invalides. Retour au menu principal.\n" RESET);
            statusClientsComptes(banque);
            return;
        }
    }
    attemptBeforeClosedCompte = 0;
    if(currentClient->compte[compteSourceIndex - 1].status == CLOSED)
    {
        printf(RED "Le compte source sélectionné est fermé. Impossible d'effectuer un virement.\n" RESET);
        return;
    }
    printf("Entrez le numéro du compte destination: ");
    int compteDestIndex;
    while (scanf("%d", &compteDestIndex) != 1 || compteDestIndex < 1 || compteDestIndex > currentClient->nbComptes || compteDestIndex == compteSourceIndex)
    {   
        printf(RED "Numéro de compte invalide ou identique au compte source. Veuillez entrer un numéro de compte valide: " RESET);
        while (getchar() != '\n')
            ; // Clear invalid input
    }
    printf("Enter le PIN pour valider le virement: ");
    int pinInput;
    while (scanf("%d", &pinInput) != 1 || pinInput != currentClient->pin)
    {
        printf(RED "PIN invalide. Veuillez réessayer: " RESET);
        while (getchar() != '\n')
            ; // Clear invalid input
            attemptBeforeClosedCompte++;
        if (attemptBeforeClosedCompte > 5)
        {
            printf(RED "Trop de tentatives invalides. Retour au menu principal.\n" RESET);
            statusClientsComptes(banque);
            return;
    }
    }
        attemptBeforeClosedCompte = 0;
    printf("Veuillez confirmer les RIB des comptes:\n");
    printf("RIB du compte source: ");
    int ribSourceInput;
    while (scanf("%d", &ribSourceInput) != 1 || ribSourceInput != currentClient->compte[compteSourceIndex - 1].RIB)
    {
        printf(RED "RIB invalide pour le compte source. Veuillez réessayer: " RESET);
        while (getchar() != '\n')
            ; // Clear invalid input
        attemptBeforeClosedCompte++;
        if (attemptBeforeClosedCompte > 5)
        {
            printf(RED "Trop de tentatives invalides. Retour au menu principal.\n" RESET);
            statusClientsComptes(banque);
            return;
        }
    }
    attemptBeforeClosedCompte = 0;
    printf("RIB du compte destination: ");
    int ribDestInput;
    while (scanf("%d", &ribDestInput) != 1 || ribDestInput != currentClient->compte[compteDestIndex - 1].RIB)
    {
        printf(RED "RIB invalide pour le compte destination. Veuillez réessayer: " RESET);
        while (getchar() != '\n')
            ; // Clear invalid input
    }
    printf("Entrez le montant à virer: ");
    float montant;
    while (scanf("%f", &montant) != 1 || montant <= 0)
    {
        printf(RED "Montant invalide. Veuillez entrer un montant positif: " RESET);
        while (getchar() != '\n')
            ; // Clear invalid input
            attemptBeforeClosedCompte++;
        if (attemptBeforeClosedCompte > 5)
        {
            printf(RED "Trop de tentatives invalides. Retour au menu principal.\n" RESET);
            statusClientsComptes(banque);
            return;
    }
}
    if (montant > currentClient->compte[compteSourceIndex - 1].solde)
    {
        printf(RED "Fonds insuffisants pour ce virement. Solde actuel du compte source: %.2f\n" RESET, currentClient->compte[compteSourceIndex - 1].solde);
        return;     
    }
    currentClient->compte[compteSourceIndex - 1].solde -= montant;
    currentClient->compte[compteDestIndex - 1].solde += montant;
    printf(GREEN "Virement de %.2f effectué avec succès du compte %d au compte %d pour le client %s.\n" RESET, montant, compteSourceIndex, compteDestIndex, currentClient->nom);
}

void afficherMenuSuppressionCompte(Banque *banque)
{
    // Code pour afficher le menu de suppression de compte
    printf(GREEN "Affichage du menu de suppression de compte...\n" RESET);
    // Implémenter les options de suppression de compte ici
    //Ici on veut supprimer un compte d'un client en s'assurant que le compte existe et qu'il n'a pas de solde positif avant de le supprimer et aussi si je supprime cela devrait diminuer le nombre total de comptes dans la banque et aussi le nombre de comptes du client et libérer la mémoire allouée pour ce compte DONC si j'ai le compte 1,2,3 et que je supprime le 2 je dois déplacer le 3 à la position 2 pour éviter les trous dans le tableau des comptes 
    if (banque->nbClients == 0)
    {
        printf(RED "Aucun client disponible.\n" RESET);
        return;
    }
    Client *currentClient = &banque->client[banque->currenntClientIndex];
    if (currentClient->nbComptes == 0)
    {
        printf(RED "Aucun compte disponible pour le client %s.\n" RESET, currentClient->nom);
        return;
    }
    printf("Suppression de compte pour le client %s:\n", currentClient->nom);
    for (int i = 0; i < currentClient->nbComptes; i++)
    {
        Compte *compte = &currentClient->compte[i];
        printf("  Compte %d: ID Compte: %d, RIB: %d, Solde: %.2f, Statut: %s\n", i + 1, compte->idCompte, compte->RIB, compte->solde, compte->status == ACTIVE ? "Actif" : "Inactif");
    }
    printf("Entrez le numéro du compte que vous souhaitez supprimer: ");
    int numCompte;
    while (scanf("%d", &numCompte) != 1 || numCompte < 1 || numCompte > currentClient->nbComptes)
    {
        printf(RED "Numéro de compte invalide. Veuillez entrer un numéro de compte valide: " RESET);
        while (getchar() != '\n')
            ; // Clear invalid input
    }
    if (currentClient->compte[numCompte - 1].solde > 0)
    {
        printf(RED "Le compte ne peut pas être supprimé car il a un solde positif de %.2f\n" RESET, currentClient->compte[numCompte - 1].solde);
        return;
    }

    // Déplacer les comptes suivants pour combler le trou
    for (int i = numCompte - 1; i < currentClient->nbComptes - 1; i++)
    {
        currentClient->compte[i] = currentClient->compte[i + 1];
    }
    banque->nbComptesGlobal--;
    currentClient->nbComptes--;
    printf(GREEN "Compte %d supprimé avec succès.\n" RESET, numCompte); 
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
        printf("  Compte %d: ID Compte: %d, RIB: %d, Solde: %.2f, Statut: %s\n", i + 1, compte->idCompte, compte->RIB, compte->solde, compte->status == ACTIVE ? "Actif" : "Inactif");
    }
}
void afficherMenuChoixClient(Banque *banque)
{
    // Code pour afficher le menu de choix du client
    printf(GREEN "Affichage du menu de choix du client...\n" RESET);
    // Implémenter les options de choix du client ici
    if (banque->nbClients == 0)
    {
        printf(RED "Aucun client disponible.\n" RESET);
        return;
    }
    printf("Liste des clients disponibles:\n");
    for (int i = 0; i < banque->nbClients; i++)
    {
        printf("%d. %s (ID: %d)\n", i + 1, banque->client[i].nom, banque->client[i].idClient);
    }
    printf("Sélectionnez le numéro du client: ");
    int clientIndex;
    while (scanf("%d", &clientIndex) != 1 || clientIndex < 1 || clientIndex > banque->nbClients)
    {
        printf(RED "Choix invalide. Veuillez entrer un nombre valide: " RESET);
        while (getchar() != '\n')
            ; // Clear invalid input
    }
    banque->currenntClientIndex = clientIndex - 1;
    Client *currentClient = &banque->client[banque->currenntClientIndex];
    printf(GREEN "Client sélectionné: %s (ID: %d)\n" RESET, currentClient->nom, currentClient->idClient);
}
void afficherMenuSuppressionClient(Banque *banque)
{
    // Code pour afficher le menu de suppression de client
    printf(GREEN "Affichage du menu de suppression de client...\n" RESET);
    // Implémenter les options de suppression de client ici
    if( banque->nbClients == 0)
    {
        printf(RED "Aucun client disponible.\n" RESET);
        return;
    }
    printf("Liste des clients disponibles:\n");
    for (int i = 0; i < banque->nbClients; i++)
    {
        printf("%d. %s (ID: %d)\n", i + 1, banque->client[i].nom, banque->client[i].idClient);
    }
    printf("Sélectionnez le numéro du client que vous souhaitez supprimer: ");
    int clientIndex;
    while (scanf("%d", &clientIndex) != 1 || clientIndex < 1 || clientIndex > banque->nbClients)
    {
        printf(RED "Choix invalide. Veuillez entrer un nombre valide: " RESET);
        while (getchar() != '\n')
            ; // Clear invalid input    
    }
    // Vérifier si le client a des comptes actifs
    if (banque->client[clientIndex - 1].nbComptes > 0)
    {
        printf(RED "Le client ne peut pas être supprimé car il a des comptes actifs.\n" RESET);
        return;
    }
    // Libérer la mémoire allouée pour les comptes du client
    free(banque->client[clientIndex - 1].compte);
    // Déplacer les clients suivants pour combler le trou
    for (int i = clientIndex - 1; i < banque->nbClients - 1; i++)
    {
        banque->client[i] = banque->client[i + 1];
    }
    banque->nbClients--;
    printf(GREEN "Client supprimé avec succès.\n" RESET);
}

void statusClientsComptes(Banque *banque){
    // Cette fonction pourrait afficher le statut des clients et de leurs comptes
    if( banque->nbClients == 0)
    {
        printf(RED "Aucun client disponible.\n" RESET);
        return;
    }
    Client *currentClient = &banque->client[banque->currenntClientIndex];
    currentClient->compte->status =1; // Par exemple, on pourrait définir un statut "inactif"
    // si statut vaut 0 alors actif sinon inactif
  
}

void sauvegarderBanque(Banque *banque)
{
    FILE *f = fopen("banque.txt", "w");
    if (!f) {
        perror("Erreur ouverture fichier");
        return;
    }
    Client *currentClient = &banque->client[banque->currenntClientIndex];                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
    fwrite(&banque->nbClients, sizeof(int), 1, f);
    fwrite(&banque->nbComptesGlobal, sizeof(int), 1, f);

    for (int i = 0; i < banque->nbClients; i++)
    {
        Client *c = &banque->client[i];
        fwrite(c, sizeof(Client) - sizeof(Compte *), 1, f);
        fwrite(c->compte, sizeof(Compte), c->nbComptes, f);
    }

    fclose(f);
    printf(GREEN "Sauvegarde réussie\n" RESET);
}


void chargerBanque(Banque *banque)
{
    // Code pour charger l'état de la banque depuis un fichier
    FILE *file = fopen("banque.txt", "r");
    if (file == NULL)
    {
        perror("Erreur lors de l'ouverture du fichier pour le chargement.");
        return;
    }
    fread(banque, sizeof(Banque), 1, file);
    fclose(file);
    printf(GREEN "Chargement de la banque effectué avec succès.\n" RESET);
}