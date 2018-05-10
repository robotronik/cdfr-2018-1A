#ifndef TRIAGE_H
#define TRIAGE_H

#include "machineEtat.h"

/* Definition des fonctions de l'etat triage */

/*
Fonction global du tri
*/
void Tri(MachineEtat* machineEtat, GPIO_TypeDef* portArduino, uint16_t pinArduino);

/*
Initialise les capteurs
*/
void InitialisationServo(MachineEtat* machineEtat);

/*
Renvoie la couleur recu par l'arduino suivant
*/
int ReceptionArduinoCouleur(GPIO_TypeDef* portArduino, uint16_t pinArduino);

/*
Controle la porte d'entree en fonction de la position du robot (structure Deplacement)
de la couleur actuellement visible (structure Trier)
et de l'etat de tir (structure Lancer)

si :
- ouverture = 0 : on ferme
- ouverture = 1 : on ouvre
*/
void ControlePorteEntree(MachineEtat* machineEtat, int sens);

/*
Controle la porte de sortie en fonction de sens :
- sens = 1 : redirection vers le module de tir
- sens = 0 : redirection vers l'evacuation
*/
void ControleSortieBalle(MachineEtat* machineEtat,int sens);


/*
Test si le tri est fini :
- test si le secoue a fonctionne, si ca n'a pas fonctionne alors :
- si le tri a fonctionner, c'est a dire 8 balles detecte lors d'un tri alors :
on augmente la variable tri pour changer d'etat
*/
void TestFinTri(MachineEtat* machineEtat);

#endif