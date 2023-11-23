#ifndef OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_2023_2024_TD9_GRP9_HEADER_H
#define OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_2023_2024_TD9_GRP9_HEADER_H


#include <stdio.h>
#include <stdlib.h>

#define MAX_TACHES 31 // Définissez ceci en fonction de la taille maximale attendue

// Structure pour stocker les informations sur chaque sommet
typedef struct {
    int tache;
    float temps;
    int station;
} Sommet;

// Prototypes de fonctions
float lireTempsMax();
void trierSommets(Sommet sommets[], int nombreSommets);
void attribuerStations(Sommet sommets[], int nombreSommets, float temps_max);


#endif //OPTIMISATION_D_UNE_LIGNE_D_ASSEMBLAGE_ING2_2023_2024_TD9_GRP9_HEADER_H