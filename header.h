// header.h

#ifndef TEMPS_PRECEDENCE_PROJ_HEADER_H
#define TEMPS_PRECEDENCE_PROJ_HEADER_H



///1. BIBLIOTHEQUES
//INCLUDE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <windows.h>

//DEFINE
#define MAX_TACHES 36  // Augmenté pour inclure l'indice 0 qui ne sera pas utilisé
#define MAX_EXCLUSIONS 100

///2. STRUCTURES
typedef struct {
    int tache;
    float temps;
    int grp_ordonnancement;
    int exclu;
    int prece;
    int station;
    int assignee; // Pour marquer si la tâche a déjà été assignée à une station

} Sommet;
//Exclu
//typedef struct Sommet
//TempsCycle
//typedef struct Sommet
//Precedence
//typedef struct Sommet
typedef struct {
    int nbSommets;
    bool matriceAdj[MAX_EXCLUSIONS][MAX_EXCLUSIONS];
    int degreEntrant[MAX_EXCLUSIONS];
} Graphe;

// Structure pour représenter les stations
typedef struct {
    int etapes[MAX_EXCLUSIONS];
    int nbEtapes;
} Station;
///3. SOUS PROG

void initSommets(Sommet sommets[], int nbSommets);

int lireExclusions(const char* nomFichier, int (*exclusions)[2]);

void lireTempsMaxCycle(const char* nomFichier, float *tempsMax);
void lireTempsTaches(const char* nomFichier, Sommet sommets[], int taille);


bool estExclue(int tache, int station, Sommet sommets[], int exclusions[][2], int nbExclusions);
void assignerStationsET(Sommet sommets[], int nbSommets, float tempsMaxCycle, int exclusions[][2], int nbExclusions);

void initGraphe(Graphe *g, int nbSommets);
void ajouterArete(Graphe *g, int debut, int fin);

void lirePrecedence(Graphe *g, const char* nomFichier);
void assignerStations(Graphe *g, Station *stations, Sommet sommets[], int nombreSommets, int *nbStations);


void trierSommets(Sommet sommets[], int nombreSommets);
void attribuerStations(Sommet sommets[], int nombreSommets, float temps_max);
int comparerGrpOrdonencement(const void *a, const void *b);
void classerTachesParStation(Sommet sommets[], int nombreSommets, float temps_max);




//INTERFACE:
//interface
void premierpage();
void color(int couleurDuTexte,int couleurDeFond);
void voiture();





#endif // TEMPS_PRECEDENCE_PROJ_HEADER_H
