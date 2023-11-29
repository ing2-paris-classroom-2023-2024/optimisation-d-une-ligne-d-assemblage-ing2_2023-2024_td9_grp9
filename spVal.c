#include "header.h"

void initialisation_graphe(graphe_val *grapheVal, int n) {
    grapheVal->nombre_ops = n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            grapheVal->adjacence[i][j] = false;
        }
    }
}
void ajouter_Arete(graphe_val *grapheVal, int noeud1, int noeud2) {
    // Définir l'arête entre les noeuds noeud1 et noeud2 comme "vraie" dans la matrice d'adjacence.
    // Cela indique qu'il existe une connexion directe entre ces deux noeuds dans le graphe.
    grapheVal->adjacence[noeud1][noeud2] = true;

    // Définir également l'arête dans l'autre sens, de noeud2 à noeud1, car le graphe est non orienté.
    // Cela garantit que la connexion est bidirectionnelle.
    grapheVal->adjacence[noeud2][noeud1] = true;
}
int premiereCouleurDisponible(graphe_val *grapheVal, int couleurs[], int noeud) {
    // Initialisation d'un tableau pour suivre les couleurs disponibles
    bool couleur_disponible[NB_MAX_ETAPES];
    for (int i = 0; i < grapheVal->nombre_ops; i++) {
        couleur_disponible[i] = true; // Toutes les couleurs sont initialement considérées comme disponibles
    }

    // Parcourir tous les noeuds pour vérifier les couleurs des noeuds adjacents
    for (int i = 0; i < grapheVal->nombre_ops; i++) {
        // Si un noeud adjacent 'i' est connecté au noeud 'noeud' et a déjà une couleur assignée,
        // marquer cette couleur comme indisponible
        if (grapheVal->adjacence[noeud][i] && couleurs[i] != -1) {
            couleur_disponible[couleurs[i]] = false;
        }
    }

    // Parcourir le tableau des couleurs disponibles pour trouver la première couleur libre
    for (int i = 0; i < grapheVal->nombre_ops; i++) {
        if (couleur_disponible[i]) {
            return i; // Retourner la première couleur disponible
        }
    }

    // Si aucune couleur n'est disponible, retourner une valeur indiquant qu'il n'y a pas de couleur disponible
    return grapheVal->nombre_ops;
}
void colorergraphe(graphe_val *grapheVal) {
    int couleurs[NB_MAX_ETAPES];
    // Initialiser toutes les opérations avec -1, indiquant qu'aucune couleur (station) n'est encore assignée
    for (int i = 0; i < grapheVal->nombre_ops; i++) {
        couleurs[i] = -1;
    }

    // Assigner une couleur à chaque opération dans le graphe
    for (int v = 0; v < grapheVal->nombre_ops; v++) {
        // Trouver la première couleur disponible pour l'opération 'v'
        int couleur = premiereCouleurDisponible(grapheVal, couleurs, v);
        // Assigner cette couleur à l'opération 'v'
        couleurs[v] = couleur;
    }

    // Afficher les stations et les opérations assignées à chaque station
    printf("Stations avec leurs operations :\n");
    for (int i = 0; i < grapheVal->nombre_ops; i++) {
        bool stationAffichee = false;
        // Parcourir toutes les opérations pour trouver celles assignées à la station 'i'
        for (int j = 0; j < grapheVal->nombre_ops; j++) {
            // Si l'opération 'j' est assignée à la station 'i'
            if (couleurs[j] == i) {
                // Si la station 'i' n'a pas encore été affichée, afficher son en-tête
                if (!stationAffichee) {
                    printf("Station %d : ", i + 1); // Les stations sont indexées à partir de 1 pour l'affichage
                    stationAffichee = true;
                }
                // Afficher l'opération assignée à la station
                printf("%d ", j + 1); // Les opérations sont indexées à partir de 1 pour l'affichage
            }
        }
        // Si au moins une opération a été assignée à la station, passer à la ligne suivante
        if (stationAffichee) {
            printf("\n");
        }
    }
}
int lireExclusions(const char* nomFichier, PaireExclusion* paires) {
    // Tenter d'ouvrir le fichier dont le nom est fourni
    FILE *fichier = fopen(nomFichier, "r");
    // Initialiser le compteur de paires d'exclusions lues
    int nbPaires = 0;

    // Vérifier si l'ouverture du fichier a réussi
    if (fichier == NULL) {
        // Afficher un message d'erreur si le fichier ne peut pas être ouvert
        perror("Impossible d'ouvrir le fichier");
        // Retourner -1 pour indiquer une erreur
        return -1;
    }

    // Lire les paires d'exclusion du fichier
    while (fscanf(fichier, "%d %d", &paires[nbPaires].op1, &paires[nbPaires].op2) == 2) {
        // Décrémenter les valeurs lues pour les adapter à l'indexation à partir de zéro
        paires[nbPaires].op1--;
        paires[nbPaires].op2--;
        // Incrémenter le nombre de paires lues
        nbPaires++;
    }

    fclose(fichier);
    // Retourner le nombre de paires d'exclusion lues
    return nbPaires;
}



bool CouleurValide(graphe_val *grapheVal, int couleurs[], int noeud, int couleur) {
    // Parcourir tous les noeuds du graphe
    for (int i = 0; i < grapheVal->nombre_ops; i++) {
        // Vérifier si une arête existe entre le noeud 'noeud' et le noeud 'i',
        // et si le noeud 'i' a déjà été coloré avec la même couleur 'couleur'.
        if (grapheVal->adjacence[noeud][i] && couleur == couleurs[i]) {
            // Si un noeud adjacent 'i' a la même couleur, la couleur 'couleur' n'est pas valide
            // pour le noeud 'noeud', donc retourner false.
            return false;
        }
    }
    // Si aucun noeud adjacent n'a la couleur 'couleur', elle est valide pour le noeud 'noeud',
    // donc retourner true.
    return true;
}

