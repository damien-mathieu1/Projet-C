#include "../common/include/votechain.h"

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define V if (verbose)
#define ID_SIZE 10

handlerAjoutElecteur(sqlite3 *db, char *id) {
    createElecteur(db, id, ID_SIZE);
    int readId = getIdFromNumeroID(db, id, ID_SIZE);
    g_print("readId = %d\n", readId);
    printf("AJOUT_ELECTEUR\n");
}

handlerSupprimeElecteur(sqlite3 *db, char *id) {
    deleteElecteur(db, id, ID_SIZE);
    g_assert(electeurExists(db, id, ID_SIZE) == 0);

    printf("SUPPRIME_ELECTEUR\n");
}

handlerEstPresent(sqlite3 *db, char *id) {
    g_assert(electeurExists(db, id, ID_SIZE) == 1);
    printf("EST_PRESENT: %d\n");
}

handlerChangementElecteur(sqlite3 *db, char *id, char *id2) {
    updateElecteur(db, id, 10, id2, ID_SIZE);
    int r = electeurExists(db, id, ID_SIZE);
    g_print("r = %d", r);
    g_assert(r == 0);
    g_assert(electeurExists(db, id2, ID_SIZE) == 1);
    printf("CHANGEMENT_ELECTEUR\n");
}

handlerLireInformationElecteur(sqlite3 *db, char *id) {
    readElecteur(db, id, ID_SIZE);
    printf("LIRE_INFORMATION_ELECTEUR\n");
}

commandHandler(sqlite3 *db, char *id, char *id2, Commande cmd) {
    switch(cmd.type) {
        case AJOUT_ELECTEUR:
            handlerAjoutElecteur(db, id);
            break;
        case SUPPRIME_ELECTEUR:
            handlerSupprimeElecteur(db, id2);
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
        default:
            printf("NOP\n");
    }
}

int main(int argc, char *argv[])
{
    GError *error = NULL;
    GOptionContext *context;

    // Définition des options
    gboolean verbose = FALSE;
    gchar *file_path = NULL;
    GOptionEntry entries[] = {
        {"verbose", 'v', 0, G_OPTION_ARG_NONE, &verbose, "Mode verbeux", NULL},
        {"file", 'f', 0, G_OPTION_ARG_STRING, &file_path, "Chemin du fichier", "FILE"},
        {NULL}};

    // Création d'un contexte d'option
    context = g_option_context_new("- test pour la création de la base de donnée");
    g_option_context_add_main_entries(context, entries, NULL);

    // Analyse des options de ligne de commande
    if (!g_option_context_parse(context, &argc, &argv, &error))
    {
        g_print("Erreur lors de l'analyse des options: %s\n", error->message);
        g_error_free(error);
        g_option_context_free(context);
        return 1;
    }

    // Affichage des résultats
    if (verbose)
    {
        g_print("Mode verbeux activé\n");
    }
    if (file_path != NULL)
    {
        g_print("Chemin du fichier: %s\n", file_path);
        int needInit = database_exists(file_path);
        struct stat buffer;
        g_print("exists ?%d", (stat(file_path, &buffer)));
        g_print("needInit: %d\n", needInit);
        g_assert(needInit == -1);
        sqlite3 *db = database_open(file_path);
        g_assert_nonnull(db);
        if (needInit == -1)
        {
            g_print("initilisation de la base de données");
            database_init(db);
        }

        char id[ID_SIZE] = "XXXXXXXXXX";
        char id2[ID_SIZE] = "XXXXXXXXX1";
        char idElection[ID_SIZE] = "EXXXXXXXXX";

        Commande cmd;

        // creation d un electeur
        cmd.type = AJOUT_ELECTEUR;
        commandHandler(db, id, id2, cmd);
        // createElecteur(db, id2, 10);

        cmd.type = LIRE_INFORMATION_ELECTEUR;
        commandHandler(db,id ,id2,cmd);

        cmd.type = EST_PRESENT;
        commandHandler(db,id,id2,cmd);

        cmd.type = CHANGEMENT_ELECTEUR;
        commandHandler(db,id,id2,cmd);

        cmd.type = SUPPRIME_ELECTEUR;
        commandHandler(db, id, id2 , cmd);
    }
    else
    {
        g_print("Aucun chemin de fichier fourni\n");
    }

    // Libération de la mémoire
    g_free(file_path);
    g_option_context_free(context);
    return 0;
}
