/*#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_OPS 35  // Nombre maximal d'opérations
#define MAX_PAIRS 100 // Nombre maximal de paires d'exclusion

typedef struct {
    int op1;
    int op2;
} PaireExclusion;

typedef struct {
    bool adjacence[MAX_OPS][MAX_OPS]; // Matrice d'adjacence avec le max d'opérations
    int nombre_ops; // Nombre d'opérations
} Graphe;

void initialisation_Graphe(Graphe *g, int n) {
    g->nombre_ops = n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            g->adjacence[i][j] = false;
        }
    }
}

void ajouterArete(Graphe *g, int noeud1, int noeud2) {
    // Définir l'arête entre les noeuds noeud1 et noeud2 comme "vraie" dans la matrice d'adjacence.
    // Cela indique qu'il existe une connexion directe entre ces deux noeuds dans le graphe.
    g->adjacence[noeud1][noeud2] = true;

    // Définir également l'arête dans l'autre sens, de noeud2 à noeud1, car le graphe est non orienté.
    // Cela garantit que la connexion est bidirectionnelle.
    g->adjacence[noeud2][noeud1] = true;
}


bool CouleurValide(Graphe *g, int couleurs[], int noeud, int couleur) {
    // Parcourir tous les noeuds du graphe
    for (int i = 0; i < g->nombre_ops; i++) {
        // Vérifier si une arête existe entre le noeud 'noeud' et le noeud 'i',
        // et si le noeud 'i' a déjà été coloré avec la même couleur 'couleur'.
        if (g->adjacence[noeud][i] && couleur == couleurs[i]) {
            // Si un noeud adjacent 'i' a la même couleur, la couleur 'couleur' n'est pas valide
            // pour le noeud 'noeud', donc retourner false.
            return false;
        }
    }
    // Si aucun noeud adjacent n'a la couleur 'couleur', elle est valide pour le noeud 'noeud',
    // donc retourner true.
    return true;
}


int premiereCouleurDisponible(Graphe *g, int couleurs[], int noeud) {
    // Initialisation d'un tableau pour suivre les couleurs disponibles
    bool couleur_disponible[MAX_OPS];
    for (int i = 0; i < g->nombre_ops; i++) {
        couleur_disponible[i] = true; // Toutes les couleurs sont initialement considérées comme disponibles
    }

    // Parcourir tous les noeuds pour vérifier les couleurs des noeuds adjacents
    for (int i = 0; i < g->nombre_ops; i++) {
        // Si un noeud adjacent 'i' est connecté au noeud 'noeud' et a déjà une couleur assignée,
        // marquer cette couleur comme indisponible
        if (g->adjacence[noeud][i] && couleurs[i] != -1) {
            couleur_disponible[couleurs[i]] = false;
        }
    }

    // Parcourir le tableau des couleurs disponibles pour trouver la première couleur libre
    for (int i = 0; i < g->nombre_ops; i++) {
        if (couleur_disponible[i]) {
            return i; // Retourner la première couleur disponible
        }
    }

    // Si aucune couleur n'est disponible, retourner une valeur indiquant qu'il n'y a pas de couleur disponible
    return g->nombre_ops;
}


void colorerGraphe(Graphe *g) {
    int couleurs[MAX_OPS];
    // Initialiser toutes les opérations avec -1, indiquant qu'aucune couleur (station) n'est encore assignée
    for (int i = 0; i < g->nombre_ops; i++) {
        couleurs[i] = -1;
    }

    // Assigner une couleur à chaque opération dans le graphe
    for (int v = 0; v < g->nombre_ops; v++) {
        // Trouver la première couleur disponible pour l'opération 'v'
        int couleur = premiereCouleurDisponible(g, couleurs, v);
        // Assigner cette couleur à l'opération 'v'
        couleurs[v] = couleur;
    }

    // Afficher les stations et les opérations assignées à chaque station
    printf("Stations avec leurs operations :\n");
    for (int i = 0; i < g->nombre_ops; i++) {
        bool stationAffichee = false;
        // Parcourir toutes les opérations pour trouver celles assignées à la station 'i'
        for (int j = 0; j < g->nombre_ops; j++) {
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


int main() {
    // Déclaration d'un tableau pour stocker les paires d'exclusion
    PaireExclusion paires[MAX_PAIRS];

    int nb_ops = 35;

    // Lecture des paires d'exclusion à partir du fichier
    int nbPaires = lireExclusions("Contrainte exclusion.txt", paires);
    // Vérifier si la lecture a échoué
    if (nbPaires < 0) {
        // Terminer le programme si une erreur s'est produite lors de la lecture du fichier
        return 1;
    }


    printf("Nombre d'operations : %d\n", nb_ops);

    printf("Paires d'exclusion :\n");
    for (int i = 0; i < nbPaires; i++) {
        // Les opérations sont réindexées à partir de 1 pour l'affichage
        printf("%d %d\n", paires[i].op1 + 1, paires[i].op2 + 1);
    }


    Graphe g;
    initialisation_Graphe(&g, nb_ops);

    // Ajout des arêtes au graphe en fonction des paires d'exclusion
    for (int i = 0; i < nbPaires; i++) {
        ajouterArete(&g, paires[i].op1, paires[i].op2);
    }

    // Coloration du graphe, ce qui assigne une "station" à chaque opération de manière à ce que
    // les opérations en exclusion mutuelle ne soient pas dans la même station
    colorerGraphe(&g);

    return 0;
}
*/