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


// Initialisation du graphe
void initGraphe(Graphe *g, int nbSommets) {
    g->nbSommets = nbSommets;
    for (int i = 0; i < nbSommets; i++) {
        g->degreEntrant[i] = 0; // Initialiser le degré entrant de tous les sommets
        for (int j = 0; j < nbSommets; j++) {
            g->matriceAdj[i][j] = false;
        }
    }
}

// Ajout d'une arête
void ajouterArete(Graphe *g, int debut, int fin) {
    g->matriceAdj[debut - 1][fin - 1] = true;
    g->degreEntrant[fin - 1]++;
}

// Lecture des contraintes à partir d'un fichier
void lireContraintes(Graphe *g, const char* nomFichier) {
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

// Assignation des tâches aux stations avec vérification de l'existence des tâches
void assignerStations(Graphe *g, Station *stations, Sommet sommets[], int nombreSommets, int *nbStations) {
    int fileAttente[NB_MAX_ETAPES], tete = 0, queue = 0;

    // Enfiler les tâches sans prérequis
    for (int i = 0; i < g->nbSommets; i++) {
        if (g->degreEntrant[i] == 0) {
            fileAttente[queue++] = i;
        }
    }

    *nbStations = 0;
    while (tete < queue) {
        int nbTachesStationActuelle = 0;
        int prochaineFile[NB_MAX_ETAPES], prochaineQueue = 0;

        while (tete < queue) {
            int tache = fileAttente[tete++];

            // Vérifier si la tâche existe dans le tableau des sommets avant de l'assigner à une station
            if (tacheExiste(tache + 1, sommets, nombreSommets)) {
                stations[*nbStations].etapes[nbTachesStationActuelle++] = tache + 1;

                // Mettre à jour grp_ordonencement pour chaque sommet correspondant
                for (int k = 0; k < nombreSommets; k++) {
                    if (sommets[k].tache == tache + 1) {
                        sommets[k].grp_ordonencement = *nbStations + 1;
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



// Lit et retourne le temps maximum par station depuis un fichier
float lireTempsMax() {
    FILE *fichier = fopen("../txt/rcycle.txt", "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier rcycle.txt");
        exit(1);
    }

    float temps_max;
    if (fscanf(fichier, "%f", &temps_max) != 1) {
        perror("Erreur lors de la lecture du fichier rcycle.txt");
        fclose(fichier);
        exit(1);
    }

    fclose(fichier);
    return temps_max;
}

// Trie les sommets selon un critère spécifique (à implémenter)
void trierSommets(Sommet sommets[], int nombreSommets) {
    // nous allons utiliser un tri pour classer les sommets par ordres croissant
}

// Attribue des stations aux tâches en fonction du temps maximum par station
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

// Fonction de comparaison pour le tri basé sur grp_ordonencement
int comparerGrpOrdonencement(const void *a, const void *b) {
    Sommet *sommetA = (Sommet *)a;
    Sommet *sommetB = (Sommet *)b;
    return sommetA->grp_ordonencement - sommetB->grp_ordonencement;
}

// Classe les tâches par station en regroupant les ordres d'ordonnancement
void classerTachesParStation(Sommet sommets[], int nombreSommets, float temps_max) {
    qsort(sommets, nombreSommets, sizeof(Sommet), comparerGrpOrdonencement);

    int stationActuelle = 1;
    float tempsCumule = 0.0;
    int grpOrdonnancementActuel = 0;

    for (int i = 0; i < nombreSommets; i++) {
        if (tempsCumule + sommets[i].temps > temps_max ||
            (grpOrdonnancementActuel != sommets[i].grp_ordonencement && grpOrdonnancementActuel != 0)) {
            stationActuelle++;
            tempsCumule = 0.0;
        }

        sommets[i].station = stationActuelle;
        tempsCumule += sommets[i].temps;
        grpOrdonnancementActuel = sommets[i].grp_ordonencement;
    }
}
