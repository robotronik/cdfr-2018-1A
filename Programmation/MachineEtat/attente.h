#ifndef ATTENTE_H
#define ATTENTE_H

#include "machineEtat.h"

/* Definition des fonctions de l'etat attente */

/*
Initialise les variables :
- tempsDepart
- tempsEnCours

de la structure Attente
*/
void InitialisationTimer(Attente* attente);

/*
Fait evoluer la variable tempsEnCours de la structure Attente
*/
void ActualisationTimer(Attente* attente);

#endif