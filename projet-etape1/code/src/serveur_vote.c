#include "../common/include/votechain.h"
#include "./bd.c"
#include "./threadpool.c"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define ID_SIZE 10

handlerAjoutElecteur(sqlite3 *db, char *id)
{
    createElecteur(db, id, ID_SIZE);
    printf("AJOUT_ELECTEUR\n");
}

handlerSupprimeElecteur(sqlite3 *db, char *id)
{
    deleteElecteur(db, id, ID_SIZE);
    printf("SUPPRIME_ELECTEUR\n");
}

handlerEstPresent(sqlite3 *db, char *id)
{
    int localid = electeurExists(db, id, ID_SIZE);
    printf("EST_PRESENT: %d\n", localid);
}

handlerChangementElecteur(sqlite3 *db, char *id, char *id2)
{
    updateElecteur(db, id, 10, id2, ID_SIZE);
    printf("CHANGEMENT_ELECTEUR\n");
}

handlerLireInformationElecteur(sqlite3 *db, char *id)
{
    readElecteur(db, id, ID_SIZE);
    printf("LIRE_INFORMATION_ELECTEUR\n");
}

handlerAjoutElection(sqlite3 *db, char *id)
{
    const char *question = "This is a binary question";
    createElection(db, id, ID_SIZE, question, "01/01/2023", "02/01/2023", "active");
    printf("AJOUT_ELECTION\n");
}

handlerSupprimeElection(sqlite3 *db, char *id)
{
    deleteElection(db, id);
    printf("SUPPRIME_ELECTION\n");
}

handlerLireResultatElection(sqlite3 *db, char *id)
{
    readElection(db, id);
    printf("LIRE_RESULTAT_ELECTION\n");
}

handlerChangementElection(sqlite3 *db, char *id)
{
    const char *question = "This is a different binary question";
    updateElection(db, id, question);
    printf("CHANGEMENT_ELECTION\n");
}

commandHandler(sqlite3 *db, char *id, char *id2, char *idElection, Commande cmd, ThreadPool pool)
{
    switch (cmd.type)
    {
    case AJOUT_ELECTEUR:
        Future ajoutElecteur;
        futureInit(&ajoutElecteur, handlerAjoutElecteur(db, id), NULL);
        if (!submitTaskToPool(&pool, &ajoutElecteur))
        {
            fprintf(stderr, "Erreur lors de la soumission de la tâche\n");
        }
        // Attendre et récupérer le résultat
        void *result = futureGet(&ajoutElecteur);
        // Utiliser le résultat...
        printf("result %s", (char *)result);

        break;
    case SUPPRIME_ELECTEUR:
        Future supprimeElecteur;
        futureInit(&supprimeElecteur, handlerSupprimeElecteur(db, id), NULL);
        if (!submitTaskToPool(&pool, &supprimeElecteur))
        {
            fprintf(stderr, "Erreur lors de la soumission de la tâche\n");
        }
        // Attendre et récupérer le résultat
        result = futureGet(&supprimeElecteur);
        // Utiliser le résultat...
        printf("result %s", (char *)result);
        break;
    case EST_PRESENT:
        Future estPresent;
        futureInit(&estPresent, handlerEstPresent(db, id), NULL);
        if (!submitTaskToPool(&pool, &estPresent))
        {
            fprintf(stderr, "Erreur lors de la soumission de la tâche\n");
        }
        // Attendre et récupérer le résultat
        result = futureGet(&estPresent);
        // Utiliser le résultat...
        printf("result %s", (char *)result);
        break;

    case CHANGEMENT_ELECTEUR:
        Future changementElecteur;
        futureInit(&changementElecteur, handlerChangementElecteur(db, id, id2), NULL);
        if (!submitTaskToPool(&pool, &changementElecteur))
        {
            fprintf(stderr, "Erreur lors de la soumission de la tâche\n");
        }
        // Attendre et récupérer le résultat
        result = futureGet(&changementElecteur);
        // Utiliser le résultat...
        printf("result %s", (char *)result);
        break;
    case LIRE_INFORMATION_ELECTEUR:
        Future lireInformationElecteur;
        futureInit(&lireInformationElecteur, handlerLireInformationElecteur(db, id), NULL);
        if (!submitTaskToPool(&pool, &lireInformationElecteur))
        {
            fprintf(stderr, "Erreur lors de la soumission de la tâche\n");
        }
        // Attendre et récupérer le résultat
        result = futureGet(&lireInformationElecteur);
        // Utiliser le résultat...
        printf("result %s", (char *)result);
        break;
    case AJOUT_ELECTION:
        Future ajoutElection;
        futureInit(&ajoutElection, handlerAjoutElection(db, idElection), NULL);
        if (!submitTaskToPool(&pool, &ajoutElection))
        {
            fprintf(stderr, "Erreur lors de la soumission de la tâche\n");
        }
        // Attendre et récupérer le résultat
        result = futureGet(&ajoutElection);
        // Utiliser le résultat...
        printf("result %s", (char *)result);
        break;
    case SUPPRIME_ELECTION:
        Future supprimeElection;
        futureInit(&supprimeElection, handlerSupprimeElection(db, idElection), NULL);
        if (!submitTaskToPool(&pool, &supprimeElection))
        {
            fprintf(stderr, "Erreur lors de la soumission de la tâche\n");
        }
        // Attendre et récupérer le résultat
        result = futureGet(&supprimeElection);
        // Utiliser le résultat...
        printf("result %s", (char *)result);
        break;

    case LIRE_RESULTAT_ELECTION:
        Future lireResultatElection;
        futureInit(&lireResultatElection, handlerLireResultatElection(db, idElection), NULL);
        if (!submitTaskToPool(&pool, &lireResultatElection))
        {
            fprintf(stderr, "Erreur lors de la soumission de la tâche\n");
        }
        // Attendre et récupérer le résultat
        result = futureGet(&lireResultatElection);
        // Utiliser le résultat...
        printf("result %s", (char *)result);
        break;
    case CHANGEMENT_ELECTION:
        Future changementElection;
        futureInit(&changementElection, handlerChangementElection(db, idElection), NULL);
        if (!submitTaskToPool(&pool, &changementElection))
        {
            fprintf(stderr, "Erreur lors de la soumission de la tâche\n");
        }
        // Attendre et récupérer le résultat
        result = futureGet(&changementElection);
        // Utiliser le résultat...
        printf("result %s", (char *)result);
        break;
    default:
        printf("NOP\n");
    }
}

int main(int argc, char const *argv[])
{
    int needInit = database_exists("./db");
    struct stat buffer;
    sqlite3 *db = database_open("./db");
    if (needInit == -1)
    {
        printf("initilisation de la base de données");
        database_init(db);
    }

    ThreadPool pool;
    if (!initThreadPool(&pool, 4, 10))
    {
        fprintf(stderr, "Erreur lors de l'initialisation du pool de threads\n");
        return 1;
    }

    char id[ID_SIZE] = "XXXXXXXXXX";
    char id2[ID_SIZE] = "XXXXXXXXX1";
    char idElection[ID_SIZE] = "EXXXXXXXXX";

    Commande cmd;
    cmd.type = AJOUT_ELECTEUR;

    commandHandler(db, id, id2, idElection, cmd, pool);
    return 0;
}
