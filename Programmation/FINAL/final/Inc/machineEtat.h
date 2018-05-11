#ifndef MACHINEETAT_H
#define MACHINEETAT_H

/* Debut des librairies necessaires a la machine a etat */
#include "xl_320.h"
#include "stm32f4xx_hal.h"
#include "odometry.h"
#include "Robotronik_corp_pid.h"
#include "fsm_position_abs.h"

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

  MoteurPin superPin;
  TIM_HandleTypeDef htim;
} Moteur;

typedef struct FSM_Position_Abs_S{
  FSM_Instance instance;
  float angle;//in rad
  float pos;//in mm
  float linear_speed;//in cm/s
  float angular_speed;//in rad/s
  float x;
  float y;
  int n;
  int initial_sum;
}FSM_Position_Abs;

typedef struct {
  int Te;
  //int prec_steps_l , prec_steps_r;
  FSM_Position_Abs fsm_pos; //init les trois
  PID_DATA pid_sum;
  PID_DATA pid_diff;
  int sum_goal;
  int diff_goal;
}Asserv;

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
  Odometry odometrie;
  Asserv asserv;
} Deplacement;

/* Fin fonctions liees au deplacement */

typedef struct{
  int deltaT;
  int finAttente; //1 si fini, 0 sinon
  int tempsEnCours;
} Attente;

/* Debut tri */

typedef struct{
  uint16_t ferme;
  uint16_t ouvert;
} PositionServo;

typedef struct{
  XL servo[3];
  XL_Interface interface;
  PositionServo positionPorteEntree;
  PositionServo positionPorteSortie;
  PositionServo positionAccelerateur;
} Servos;

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
  Servos servosGlobal;
} Triage;

/* Fin tri */

typedef struct{
  int tir;
  Servos accelerateur;
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
