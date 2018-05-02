#ifndef DEPLACEMENT_H
#define DEPLACEMENT_H

#include "machineEtat.h"

/* Definition des fonctions de l'etat deplacement */

/*
Initialise la variable deverouillageValide a 0
*/
void Initialisation(Deplacement* deplacement);

/*
Fait avancer le vehicule en changeant les positions x et y du robot
En faisant attention aux autres robots 
*/
void Deplacement(Deplacement* deplacement);

/*
Fait tourner le vehicule vers la :
- Gauche : sens = 1
- Droite : sens = -1
*/
void Tourner(int sens);

/*
Deplace le robot afin de deverouiller le loquet vers la position :
- 1 si deverouillageValide = 0
- 2 si deverouillageValide = 1
*/
void Deverouillage(Deplacement* deplacement);

/*
Deplace le robot sur la position de tir avec l'orientation
*/
void PositionnementTir(Deplacement* deplacement);

/*
Renvoie :
0 si detecte en face
1 si detecte a gauche
2 si detecte a droite
3 si detecte derriere
*/
int DetectionUltrason();

#endif
