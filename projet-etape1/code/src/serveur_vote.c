#include "../common/include/votechain.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

handlerAjoutElecteur() {
    printf("AJOUT_ELECTEUR\n");
}

handlerSupprimeElecteur() {
    printf("SUPPRIME_ELECTEUR\n");
}

handlerEstPresent() {
    printf("EST_PRESENT\n");
}

handlerChangementElecteur() {
    printf("CHANGEMENT_ELECTEUR\n");
}

handlerLireInformationElecteur() {
    printf("LIRE_INFORMATION_ELECTEUR\n");
}

handlerAjoutElection() {
    printf("AJOUT_ELECTION\n");
}

handlerSupprimeElection() {
    printf("SUPPRIME_ELECTION\n");
}

handlerLireResultatElection() {
    printf("LIRE_RESULTAT_ELECTION\n");
}

handlerChangementElection() {
    printf("CHANGEMENT_ELECTION\n");
}

int main(int argc, char const *argv[])
{
    Commande cmd;
    switch(cmd.type) {
        case AJOUT_ELECTEUR:
            handlerAjoutElecteur();
            break;
        case SUPPRIME_ELECTEUR:
            handlerSupprimeElecteur();
            break;
        case EST_PRESENT:
            handlerEstPresent();
            break;

        case CHANGEMENT_ELECTEUR:
            handlerChangementElecteur();
            break; 
        case LIRE_INFORMATION_ELECTEUR:
            handlerLireInformationElecteur();
            break;
        case AJOUT_ELECTION:
            handlerAjoutElection();
            break;

        case SUPPRIME_ELECTION:
            handlerSupprimeElection();
            break;
        
        case LIRE_RESULTAT_ELECTION:
            handlerLireResultatElection();
            break;
        case CHANGEMENT_ELECTION:
            handlerChangementElection();
            break;        
        default:
            printf("NOP\n");
    }
    return 0;
}
