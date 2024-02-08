#ifndef MESSAGE_H
#define MESSAGE_H

#include "protocol.h"

typedef struct
{
    char identifiant[ENTITY_ID_SIZE];
} AjoutElecteurCmd;

typedef struct
{
    char identifiant[ENTITY_ID_SIZE];
} SupprimeElecteurCmd;

typedef struct
{
    char identifiant[ENTITY_ID_SIZE];
} EstPresentCmd;

typedef struct
{
    char identifiant[ENTITY_ID_SIZE];
} ChangementElecteurCmd;

typedef struct
{
    char identifiant[ENTITY_ID_SIZE];
} LireInformationElecteurCmd;

typedef struct
{
    char identifiant[ENTITY_ID_SIZE];
} AjoutElectionCmd;

typedef struct
{
    char identifiant[ENTITY_ID_SIZE];
} SupprimeElectionCmd;

typedef struct
{
    char identifiant[ENTITY_ID_SIZE];
} LireResultatElectionCmd;

typedef struct
{
    char identifiant[ENTITY_ID_SIZE];
} ChangementElectionCmd;

typedef enum
{
    NOP = 0,
    AJOUT_ELECTEUR,
    SUPPRIME_ELECTEUR,
    EST_PRESENT,
    CHANGEMENT_ELECTEUR,
    LIRE_INFORMATION_ELECTEUR,
    AJOUT_ELECTION,
    SUPPRIME_ELECTION,
    LIRE_RESULTAT_ELECTION,
    CHANGEMENT_ELECTION,
    ELECTION_CAST_VOTE,
    ELECTION_PROCESS_VOTES
} CommandType;

//--
typedef struct
{
    CommandType type;
    char signature[256]; // la signature de la commande
    union
    {
        AjoutElecteurCmd ajoutElecteur;
        SupprimeElecteurCmd supprimeElecteur;
        EstPresentCmd estPresent;
        ChangementElecteurCmd changementElecteur;
        LireInformationElecteurCmd lireInformationElecteur;
        AjoutElectionCmd ajoutElection;
        SupprimeElectionCmd supprimeElection;
        LireResultatElectionCmd lireResultatElection;
        ChangementElectionCmd changementElection;
    } commande;
} Commande;

#endif