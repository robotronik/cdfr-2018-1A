#ifndef MACHINEETAT_H
#define MACHINEETAT_H

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
  Attente attente;
  EtatActuel etatActuel;
} MachineEtat;

typedef struct{
  float xTerrain;
  float yTerrain;
  float xRobot;
  float yRobot;
  int deverouillageValide;
  int deverouillage;
  int deverouillagePrecedent;
  int pretTri;
} Deplacement;

typedef struct{
  int tempsDepart;
  int tempsEnCours;
} Attente;

typedef struct{
  char* couleur;
  char* couleurDetecte;
  int secouer;
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
