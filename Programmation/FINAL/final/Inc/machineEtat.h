#ifndef MACHINEETAT_H
#define MACHINEETAT_H

/* Debut des librairies necessaires a la machine a etat */
#include "xl_320.h"
#include "stm32f4xx_hal.h"

/* Fin des librairies necessaires a la machine a etat */

typedef enum{
  DEPLACEMENT,
  TRIAGE,
  LANCER,
  ATTENTE
} EtatActuel;

/* Debut fonctions liees au deplacement */

/*
Structure pour les tests de distance
*/
typedef struct{
    GPIO_TypeDef* port;
    uint16_t pin;

    int tensionPrecedent;
    int tension;
    uint32_t tempsReception;
    uint32_t tempsEnvoie;

    char detection;
} TestUltrason;

/*
Permet de connaitre quel capteur detecte
*/
typedef struct{
    uint32_t seuilDetection;
    char detection;
    TestUltrason usAvantGauche;
    TestUltrason usAvant;
    TestUltrason usAvantDroit;
    TestUltrason usArriere;
} DetectionCapteur;

typedef struct{
  float x;
  float y;
} FVecteur2D;

typedef struct{
  GPIO_TypeDef* type;
  uint16_t pin;
} MoteurPin;

typedef struct{
  MoteurPin av;
  MoteurPin ar;
} Moteur;

typedef struct{
  FVecteur2D dimTerrain;
  FVecteur2D positionRobot;
  FVecteur2D positionContainer1;
  FVecteur2D positionContainer2;
  FVecteur2D positionTir;
  int deverouillageValide;
  int deverouillage;
  int deverouillagePrecedent;
  Moteur moteurGauche;
  Moteur moteurDroit;
  DetectionCapteur detectionCapteur;
  int pretTri;
} Deplacement;

/* Fin fonctions liees au deplacement */

typedef struct{
  int deltaT;
  int finAttente; //1 si fini, 0 sinon
} Attente;

/* Debut tri */

typedef struct{
  XL servo;
  uint16_t posFerme;
  uint16_t posOuvert;
} XL_ME_Wrapper;

typedef struct{
  int maCouleur; // 1 orange, -1 vert
  int couleurDetecte; // 0 sinon
  int secouer;
  int secouerPrecedent;
  int nombreBallesDetectees;
  int nombreBallesTri1;
  int servoPret; //1 si servos dispo sinon -1 (0 est un cas intermediaire a ne pas prendre en compte)
  int tri; //prend la valeur 1 si le premier tri a bugue ou s'il est fini, 2 au deuxième tri
  int triPrecedent; // cest un peu iconoclaste
  XL_ME_Wrapper xl_porte_entre;
  XL_ME_Wrapper xl_porte_sortie;
  XL_ME_Wrapper xl_propulsion;
} Triage;

/* Fin tri */

typedef struct{
  int tir;
  XL_ME_Wrapper accelerateur;
} Lancer;

typedef struct{
  Deplacement deplacement;
  Triage triage;
  Lancer lancer;
  Attente attente;
  EtatActuel etatActuel;
} MachineEtat;

#include "config.h"

/*
Initialise tout les parametres globaux du jeu
*/
void InitialisationParametresGlobaux(MachineEtat* machineEtat);

/*
Gere la transition des etats
*/
void TransitionEtats(MachineEtat* machineEtat);

#endif
