#include "../common/include/votechain.h"
#include "./bd.c"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define ID_SIZE 10


handlerAjoutElecteur(sqlite3 *db, char *id) {
    createElecteur(db, id, ID_SIZE);
    printf("AJOUT_ELECTEUR\n");
}

handlerSupprimeElecteur(sqlite3 *db, char *id) {
    deleteElecteur(db, id, ID_SIZE);
    printf("SUPPRIME_ELECTEUR\n");
}

handlerEstPresent(sqlite3 *db, char *id) {
    int localid = electeurExists(db, id, ID_SIZE);
    printf("EST_PRESENT: %d\n", localid);
}

handlerChangementElecteur(sqlite3 *db, char *id, char *id2) {
    updateElecteur(db, id, 10, id2, ID_SIZE);
    printf("CHANGEMENT_ELECTEUR\n");
}

handlerLireInformationElecteur(sqlite3 *db, char *id) {
    readElecteur(db, id, ID_SIZE);
    printf("LIRE_INFORMATION_ELECTEUR\n");
}

handlerAjoutElection(sqlite3 *db, char *id) {
    const char *question = "This is a binary question";
    createElection(db, id, ID_SIZE, question, "01/01/2023", "02/01/2023", "active");
    printf("AJOUT_ELECTION\n");
}

handlerSupprimeElection(sqlite3 *db, char *id) {
    deleteElection(db, id);
    printf("SUPPRIME_ELECTION\n");
}

handlerLireResultatElection(sqlite3 *db, char *id) {
    readElection(db, id);
    printf("LIRE_RESULTAT_ELECTION\n");
}

handlerChangementElection(sqlite3 *db, char *id) {
    const char *question = "This is a different binary question";
    updateElection(db, id, question);
    printf("CHANGEMENT_ELECTION\n");
}

commandHandler(sqlite3 *db, char *id, char *id2, char *idElection, Commande cmd) {
    switch(cmd.type) {
        case AJOUT_ELECTEUR:
            handlerAjoutElecteur(db, id);
            break;
        case SUPPRIME_ELECTEUR:
            handlerSupprimeElecteur(db, id);
            break;
        case EST_PRESENT:
            handlerEstPresent(db, id);
            break;
        case CHANGEMENT_ELECTEUR:
            handlerChangementElecteur(db, id, id2);
            break; 
        case LIRE_INFORMATION_ELECTEUR:
            handlerLireInformationElecteur(db, id);
            break;
        case AJOUT_ELECTION:
            handlerAjoutElection(db, idElection);
            break;
        case SUPPRIME_ELECTION:
            handlerSupprimeElection(db ,idElection);
            break;
        
        case LIRE_RESULTAT_ELECTION:
            handlerLireResultatElection(db, idElection);
            break;
        case CHANGEMENT_ELECTION:
            handlerChangementElection(db, idElection);
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
    char id[ID_SIZE] = "XXXXXXXXXX";
    char id2[ID_SIZE] = "XXXXXXXXX1";
    char idElection[ID_SIZE] = "EXXXXXXXXX";

    Commande cmd;
    cmd.type = AJOUT_ELECTEUR;

    commandHandler(db, id, id2, idElection, cmd);
    return 0;
}
