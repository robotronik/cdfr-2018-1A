#ifndef DEPLACEMENT_H
#define DEPLACEMENT_H

#include "machineEtat.h"

typedef struct{
  GPIO_TypeDef* type;
  uint16_t pin;
} MoteurPin;

typedef struct{
  MoteurPin av;
  MoteurPin ar;
} Moteur;

/* Definition des fonctions de l'etat deplacement */

/*
Initialise les moteurs et la variable deverouillageValide a 0
*/
void Initialisation(MachineEtat* machineEtat, Moteur* moteurGauche, Moteur* moteurDroit);

/*
Sous programmes avancer et arreter
*/
void MoteurAvant(Moteur moteur);
void MoteurOff(Moteur moteur);

/*
Fait avancer le vehicule en changeant les positions x et y du robot
En faisant attention aux autres robots
*/
void Deplacement(MachineEtat* machineEtat);

/*
Fait tourner le vehicule vers la :
- Gauche : sens = 1
- Droite : sens = -1
*/
void Tourner(MachineEtat* machineEtat,int sens);

/*
Deplace le robot afin de deverouiller le loquet vers la position :
- 1 si deverouillageValide = 0
- 2 si deverouillageValide = 1
*/
void Deverouillage(MachineEtat* machineEtat);

/*
Deplace le robot sur la position de tir avec l'orientation
*/
void PositionnementTir(MachineEtat* machineEtat);

/*
Renvoie :
0 si detecte en face
1 si detecte a gauche
2 si detecte a droite
3 si detecte derriere
*/
int DetectionUltrason();

#endif
