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

int main()
{
    Banque maBanque;
    // Initialisation de la banque, des clients et des comptes ici si nécessaire
    maBanque.nbClients = 0; // Exemple d'initialisation
    maBanque.client = malloc(sizeof(Client) * MAX_CLIENTS); // Allouer de l'espace pour 10 clients
    while (1)
    {
        afficherMenuPrincipal(&maBanque);
        
    }
    // Libération de la mémoire allouée
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        free(maBanque.client[i].compte);
    }
    free(maBanque.client);
    return 0;
}