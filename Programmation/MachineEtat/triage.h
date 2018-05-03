#ifndef TRIAGE_H
#define TRIAGE_H

#include "machineEtat.h"

/* Definition des fonctions de l'etat triage */


/*
Renvoie la couleur recu par l'arduino suivant
*/
char* ReceptionArduinoCouleur(UART_HandleTypeDef* huart);

/*
Controle la porte d'entree en fonction de la position du robot (structure Deplacement)
de la couleur actuellement visible (structure Trier)
et de l'etat de tir (structure Lancer)

si :
- ouverture = 0 : on ferme
- ouverture = 1 : on ouvre
*/
void ControlePorteEntree(MachineEtat* machineEtat, int ouverture, XL_ME_wrapper *servo);

/*
Controle la porte de sortie en fonction de sens :
- sens = 1 : redirection vers le module de tir
- sens = 0 : redirection vers l'evacuation
*/
void ControleSortieBalle(MachineEtat* machineEtat,int sens);


/*
Test si le tri est fini :
- pas de boule detecter par le capteur
- la fonction secouer renvoie ne permet la detection d'autre boule
augmente tri de 1
*/
void TestFinTri(MachineEtat* machineEtat);

#endif