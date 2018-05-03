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
  FVecteur2D dimTerrain;
  FVecteur2D positionRobot;
  FVecteur2D positionContainer1;
  FVecteur2D positionContainer2;
  FVecteur2D positionTir;
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
  int maCouleur; // 1 orange, -1 vert
  int couleurDetecte; // 0 sinon
  int secouer;
  int tri; //prend la valeur 1 si le premier tri a bugue ou s'il est fini, 2 au deuxième tri
  int triPrecedent; // cest un peu iconoclaste
  XL_ME_Wrapper xl_porte_entre;
  XL_ME_Wrapper xl_porte_sortie;
} Triage;

typedef struct{
  int tir;
} Lancer;

typedef struct{
  float x;
  float y;
} FVecteur2D;

/*
Initialise tout les parametres globaux du jeu
*/
void InitialisationParametresGlobaux();

/*
Gere la transition des etats
*/
void TransitionEtats(MachineEtat* MachineEtat);

#endif
