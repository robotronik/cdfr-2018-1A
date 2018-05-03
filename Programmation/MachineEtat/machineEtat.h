#ifndef MACHINEETAT_H
#define MACHINEETAT_H

#include "XL_320.h"
typedef enum{
  DEPLACEMENT,
  TRIAGE,
  LANCER,
  ATTENTE
} EtatActuel;

typedef struct{
  Deplacement deplacement;
  Triage triage;
  Lancer lancer;
  Attente attente;deltaT
  EtatActuel etatActuel;
} MachineEtat;

typedef struct{
  float xTerrain;
  float yTerrain;
  float xRobot;
  float yRobot;
  float xContainer1
  float yContainer1
  float xContainer2
  float yContainer2
  float depo
  int deverouillageValide;
  int deverouillage;
  int deverouillagePrecedent;
  int pretTri;
} Deplacement;

typedef struct{
  int deltaT;
  int finAttente; //1 si fini, 0 sinon
} Attente;

typedef struct{
  XL servo;
  uint16_t posFerme;
  uint16_t posOuvert;
} XL_ME_Wrapper

typedef struct{
  char* maCouleur; // cest la couleur de notre equipe
  char* couleurDetecte;
  int secouer;
  int tri; //prend la valeur 1 si le premier tri a bugue ou s'il est fini, 2 au deuxième tri
  int triPrecedent; // cest un peu iconoclaste
  XL_ME_Wrapper xl_porte_entre;
  XL_ME_Wrapper xl_porte_sortie;
} Triage;

typedef struct{
  int tir;
} Lancer;

/*
Initialise tout les parametres globaux du jeu
*/
void InitialisationParametresGlobaux();

/*
Gere la transition des etats
*/
void TransitionEtats(MachineEtat* MachineEtat);

#endif
