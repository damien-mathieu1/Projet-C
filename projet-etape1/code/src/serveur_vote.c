#include "../common/include/votechain.h"
#include "./bd.c"
#include "./threadpool.c"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "../common/include/crypto.h"

#define BALLOT_SIZE 1
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

handlerElectionCastVote(sqlite3 *db, char idVotant, char idElection, const void *ballot, const char *hashValidation)
{
    Election_castVote(db, idVotant, idElection, ballot, BALLOT_SIZE, hashValidation);
    printf("ELECTION_CAST_VOTE\n");
}

handlerElectionProcessVotes(sqlite3 *db, char *id, mpz_t sum_encrypted, mpz_t lambda, mpz_t mu, mpz_t n)
{
    int no = 0;
    int yes = 0;
    int total = 0;
    Election_processVotes(db, id, &no, &yes, &total);
    decrypt(no, sum_encrypted, lambda, mu, n);
    decrypt(yes, sum_encrypted, lambda, mu, n);
    printf("ELECTION_PROCESS_VOTES\n");
}

commandHandler(sqlite3 *db, char *id, char *id2, char *idElection, Commande cmd, ThreadPool pool, const void *ballot, const char *hashValidation, mpz_t sum_encrypted, mpz_t lambda, mpz_t mu, mpz_t n, mpz_t g, mpz_t m, mpz_t c)
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
    case ELECTION_CAST_VOTE:
        mpz_set_ui(m, ballot);
        encrypt(c, m, n, g);
        Future electionCastVote;
        futureInit(&electionCastVote, handlerElectionCastVote(db, id, idElection, m, hashValidation), NULL);
        if (!submitTaskToPool(&pool, &electionCastVote))
        {
            fprintf(stderr, "Erreur lors de la soumission de la tâche\n");
        }
        // Attendre et récupérer le résultat
        result = futureGet(&electionCastVote);
        // Utiliser le résultat...
        printf("result %s", (char *)result);

        break;
    case ELECTION_PROCESS_VOTES:
        Future electionProcessVotes;
        futureInit(&electionProcessVotes, handlerElectionProcessVotes(db, idElection, sum_encrypted, lambda, mu, n), NULL);
        if (!submitTaskToPool(&pool, &electionProcessVotes))
        {
            fprintf(stderr, "Erreur lors de la soumission de la tâche\n");
        }
        // Attendre et récupérer le résultat
        result = futureGet(&electionProcessVotes);
        // Utiliser le résultat...
        printf("result %s", (char *)result);
        break;
    default:
        printf("NOP\n");
    }
}

int main(int argc, char const *argv[])
{
    mpz_t n, lambda, g, mu, m, c, sum_encrypted;
    mpz_inits(n, lambda, g, mu, m, c, NULL);
    mpz_inits(sum_encrypted, NULL);
    // Generate keys
    generate_keys(n, lambda, g, mu);

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

    const char *command = argv[1];
    Commande cmd;

    if (strcmp(command, "AJOUT_ELECTEUR") == 0)
    {
        cmd.type = AJOUT_ELECTEUR;
    }
    else if (strcmp(command, "SUPPRIMER_ELECTEUR") == 0)
    {
        cmd.type = SUPPRIME_ELECTEUR;
    }
    else if (strcmp(command, "AJOUT_ELECTION") == 0)
    {
        cmd.type = AJOUT_ELECTION;
    }
    else if (strcmp(command, "SUPPRIMER_ELECTION") == 0)
    {
        cmd.type = SUPPRIME_ELECTION;
    }
    else if (strcmp(command, "EST_PRESENT") == 0)
    {
        cmd.type = EST_PRESENT;
    }
    else if (strcmp(command, "CHANGEMENT_ELECTEUR") == 0)
    {
        cmd.type = CHANGEMENT_ELECTEUR;
    }
    else if (strcmp(command, "LIRE_INFORMATION_ELECTEUR") == 0)
    {
        cmd.type = LIRE_INFORMATION_ELECTEUR;
    }
    else if (strcmp(command, "LIRE_RESULTAT_ELECTION") == 0)
    {
        cmd.type = LIRE_RESULTAT_ELECTION;
    }
    else if (strcmp(command, "CHANGEMENT_ELECTION") == 0)
    {
        cmd.type = CHANGEMENT_ELECTION;
    }
    else
    {
        fprintf(stderr, "Commande inconnue: %s\n", command);
        return 1;
    }

    commandHandler(db, id, id2, idElection, cmd, pool, NULL, NULL, sum_encrypted, lambda, mu, n, g, m, c);
    return 0;
}
