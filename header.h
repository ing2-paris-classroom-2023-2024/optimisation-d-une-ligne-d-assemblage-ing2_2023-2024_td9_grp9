// header.h

#ifndef TEMPS_PRECEDENCE_PROJ_HEADER_H
#define TEMPS_PRECEDENCE_PROJ_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_TACHES 31
#define NB_MAX_ETAPES 35

#define MAX_PAIRS 100


typedef struct {
    int op1;
    int op2;
} PaireExclusion;

typedef struct {
    bool adjacence[NB_MAX_ETAPES][NB_MAX_ETAPES]; // Matrice d'adjacence avec le max d'opérations
    int nombre_ops; // Nombre d'opérations
} graphe_val;

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



bool CouleurValide(graphe_val *grapheVal, int couleurs[], int noeud, int couleur);
void initialisation_graphe(graphe_val *g, int n);
void ajouter_Arete(graphe_val *g, int noeud1, int noeud2);
int premiereCouleurDisponible(graphe_val *g, int couleurs[], int noeud);
void colorergraphe(graphe_val *grapheVal);
int lireExclusions(const char* nomFichier, PaireExclusion* paires);




#endif // TEMPS_PRECEDENCE_PROJ_HEADER_H
