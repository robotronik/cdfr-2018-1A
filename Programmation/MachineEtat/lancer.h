#ifndef LANCER_H
#define LANCER_H

#include "machineEtat.h"

/* Definition des fonctions de l'etat lancer */

/*
Met en marche le moteur de lancement
*/
void ActivationMoteur(MachineEtat* machineEtat);

/*
Test si la demande de tir est faite et active un servo pour assister la balle dans la propulsion
*/
void AccelerateurBalle(MachineEtat* machineEtat);

#endif