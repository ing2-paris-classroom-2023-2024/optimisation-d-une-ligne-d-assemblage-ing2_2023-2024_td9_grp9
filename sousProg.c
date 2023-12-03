#include "header.h"

//Initit
void initSommets(Sommet sommets[], int nbSommets) {
    for (int i = 1; i < nbSommets; i++) {
        sommets[i].tache = i;
        sommets[i].temps = 0.0;
        sommets[i].grp_ordonnancement = -1;
        sommets[i].exclu = -1;
        sommets[i].station = -1;
        sommets[i].assignee = -1;

    }
}


void lireTempsMaxCycle(const char* nomFichier, float *tempsMax) {
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(1);
    }

    if (fscanf(fichier, "%f", tempsMax) != 1) {
        fprintf(stderr, "Erreur de format dans le fichier %s\n", nomFichier);
        exit(1);
    }

    fclose(fichier);
}
void lireTempsTaches(const char* nomFichier, Sommet sommets[], int taille) {
    FILE *fichier = fopen(nomFichier, "r");
    int tache;
    float temps;

    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(1);
    }

    // Initialiser tous les sommets avec un temps de 0
    for (int i = 1; i < taille; i++) {
        sommets[i].tache = i;
        sommets[i].temps = 0.0;
    }

    while (fscanf(fichier, "%d %f", &tache, &temps) == 2) {
        if (tache >= 1 && tache < taille) {
            sommets[tache].temps = temps;
        }
    }

    fclose(fichier);
}


//EXCLUSION
int lireExclusions(const char* nomFichier, int (*exclusions)[2]) {
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 0;
    }

    int nbPaires = 0;
    while (fscanf(fichier, "%d %d", &exclusions[nbPaires][0], &exclusions[nbPaires][1]) == 2) {
        nbPaires++;
    }

    fclose(fichier);
    return nbPaires;
}


bool estExclue(int tache, int station, Sommet sommets[], int exclusions[][2], int nbExclusions) {
    for (int i = 0; i < nbExclusions; i++) {
        if ((exclusions[i][0] == tache || exclusions[i][1] == tache) &&
            (sommets[exclusions[i][0]].station == station || sommets[exclusions[i][1]].station == station)) {
            return true; // L'exclusion est violée
        }
    }
    return false; // Aucune exclusion pour cette tâche et cette station
}
void assignerStationsET(Sommet sommets[], int nbSommets, float tempsMaxCycle, int exclusions[][2], int nbExclusions) {
    for (int j = 0; j < nbSommets; j++) { // Parcourir les stations
        float tempsCumule = 0.0;

        for (int i = 1; i < nbSommets; i++) { // Essayer d'assigner chaque tâche à la station j
            if (sommets[i].temps == 0.0 || sommets[i].station != -1) continue; // Ignorer si la tâche n'a pas de temps ou est déjà assignée

            // Vérifier les contraintes
            if (!estExclue(i, j, sommets, exclusions, nbExclusions) && tempsCumule + sommets[i].temps <= tempsMaxCycle) {
                sommets[i].station = j; // Assigner la tâche i à la station j
                sommets[i].exclu = j;
                tempsCumule += sommets[i].temps;
                //printf("temps: %f", tempsCumule);
            }
        }
    }
}



// Initialisation du graphe
#include "header.h"


// Vérifie si une tâche existe dans le tableau des sommets
bool tacheExiste(int tache, Sommet sommets[], int nombreSommets) {
    for (int i = 0; i < nombreSommets; i++) {
        if (sommets[i].tache == tache) {
            return true;
        }
    }
    return false;
}
void initGraphe(Graphe *g, int nbSommets) {
    g->nbSommets = nbSommets;
    for (int i = 0; i < nbSommets; i++) {
        g->degreEntrant[i] = 0; // Initialiser le degré entrant de tous les sommets
        for (int j = 0; j < nbSommets; j++) {
            g->matriceAdj[i][j] = false;
        }
    }
}

void ajouterArete(Graphe *g, int debut, int fin) {
    g->matriceAdj[debut - 1][fin - 1] = true;
    g->degreEntrant[fin - 1]++;
}

void lirePrecedence(Graphe *g, const char* nomFichier) {
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(1);
    }

    int debut, fin;
    while (fscanf(fichier, "%d %d", &debut, &fin) == 2) {
        ajouterArete(g, debut, fin);
    }

    fclose(fichier);
}
void assignerStations(Graphe *g, Station *stations, Sommet sommets[], int nombreSommets, int *nbStations) {
    int fileAttente[MAX_TACHES], tete = 0, queue = 0;

    // Enfiler les tâches sans prérequis
    for (int i = 0; i < g->nbSommets; i++) {
        if (g->degreEntrant[i] == 0) {
            fileAttente[queue++] = i;
        }
    }

    *nbStations = 0;
    while (tete < queue) {
        int nbTachesStationActuelle = 0;
        int prochaineFile[MAX_TACHES], prochaineQueue = 0;

        while (tete < queue) {
            int tache = fileAttente[tete++];

            // Vérifier si la tâche existe dans le tableau des sommets avant de l'assigner à une station
            if (tacheExiste(tache + 1, sommets, nombreSommets)) {
                stations[*nbStations].etapes[nbTachesStationActuelle++] = tache + 1;

                // Mettre à jour grp_ordonencement pour chaque sommet correspondant
                for (int k = 0; k < nombreSommets; k++) {
                    if (sommets[k].tache == tache + 1) {
                        sommets[k].grp_ordonnancement = *nbStations + 1;
                        break;
                    }
                }

                // Diminuer le degré entrant de toutes les tâches adjacentes
                for (int j = 0; j < g->nbSommets; j++) {
                    if (g->matriceAdj[tache][j]) {
                        g->degreEntrant[j]--;
                        if (g->degreEntrant[j] == 0 && tacheExiste(j + 1, sommets, nombreSommets)) {
                            prochaineFile[prochaineQueue++] = j;
                        }
                    }
                }
            }
        }

        if (nbTachesStationActuelle > 0) {
            stations[*nbStations].nbEtapes = nbTachesStationActuelle;
            (*nbStations)++;
        }

        // Copier prochaineFile dans fileAttente
        for (int i = 0; i < prochaineQueue; i++) {
            fileAttente[i] = prochaineFile[i];
        }
        tete = 0;
        queue = prochaineQueue;
    }
}


void trierSommets(Sommet sommets[], int nombreSommets) {
    // nous allons utiliser un tri pour classer les sommets par ordres croissant
}
void attribuerStations(Sommet sommets[], int nombreSommets, float temps_max) {
    float tempsCumule = 0.0;
    int stationActuelle = 1;

    for (int i = 0; i < nombreSommets; i++) {
        if (tempsCumule + sommets[i].temps > temps_max) {
            stationActuelle++;
            tempsCumule = 0.0;
        }
        sommets[i].station = stationActuelle;
        tempsCumule += sommets[i].temps;
    }
}
int comparerGrpOrdonencement(const void *a, const void *b) {
    Sommet *sommetA = (Sommet *)a;
    Sommet *sommetB = (Sommet *)b;
    return sommetA->grp_ordonnancement - sommetB->grp_ordonnancement;
}
void classerTachesParStation(Sommet sommets[], int nombreSommets, float temps_max) {
    qsort(sommets, nombreSommets, sizeof(Sommet), comparerGrpOrdonencement);

    int stationActuelle = 1;
    float tempsCumule = 0.0;
    int grpOrdonnancementActuel = 0;

    for (int i = 0; i < nombreSommets; i++) {
        if (tempsCumule + sommets[i].temps > temps_max ||
            (grpOrdonnancementActuel != sommets[i].grp_ordonnancement && grpOrdonnancementActuel != 0)) {
            stationActuelle++;
            tempsCumule = 0.0;
        }

        sommets[i].station = stationActuelle;
        sommets[i].prece = stationActuelle + 100;
        tempsCumule += sommets[i].temps;
        grpOrdonnancementActuel = sommets[i].grp_ordonnancement;
    }
}


