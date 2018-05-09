#ifndef ATTENTE_H
#define ATTENTE_H

#include "machineEtat.h"
#include "deplacement.h"

/* Definition des fonctions de l'etat attente */

/*
fait la pause qui est defini dans config.h
*/
void Pause(MachineEtat* machineEtat);

/*
s'arrete a la detection
*/
void ArretUltrason(MachineEtat* machineEtat);
#endif