// header.h

#ifndef TEMPS_PRECEDENCE_PROJ_HEADER_H
#define TEMPS_PRECEDENCE_PROJ_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_TACHES 31
#define NB_MAX_ETAPES 35

// Structure pour représenter un graphe
typedef struct {
    int nbSommets;
    bool matriceAdj[NB_MAX_ETAPES][NB_MAX_ETAPES];
    int degreEntrant[NB_MAX_ETAPES];
} Graphe;

// Structure pour représenter les stations
typedef struct {
    int etapes[NB_MAX_ETAPES];
    int nbEtapes;
} Station;

// Structure pour stocker les informations sur chaque sommet
typedef struct {
    int tache;
    float temps;
    int grp_ordonencement;
    int station;
} Sommet;

// Déclarations des fonctions
float lireTempsMax();
int comparerGrpOrdonencement(const void *a, const void *b);
void trierSommets(Sommet sommets[], int nombreSommets);
void attribuerStations(Sommet sommets[], int nombreSommets, float temps_max);
void initGraphe(Graphe *g, int nbSommets);
void ajouterArete(Graphe *g, int debut, int fin);
void lireContraintes(Graphe *g, const char* nomFichier);
void assignerStations(Graphe *g, Station *stations, Sommet sommets[], int nombreSommets, int *nbStations);
void classerTachesParStation(Sommet sommets[], int nombreSommets, float temps_max);

#endif // TEMPS_PRECEDENCE_PROJ_HEADER_H
