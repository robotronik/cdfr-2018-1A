#ifndef CONFIG_H
#define CONFIG_H

#include "ultrason.h"
#include "machineEtat.h"

/* Temps d'attente de la machine a etat */
#define tempsAttente 20

/* Distance de detection ultrason */
#define distanceDeSeuil 300

/* Dimension du terrain */
#define xTerrain 3000
#define yTerrain 2000

/* Position du robot au depart si Orange */
#define xRobotDepartO 2865
#define yRobotDepartO 1890

/* Position du robot au depart si Vert */
#define xRobotDepartV 135
#define yRobotDepartV 1890

/* Position du premier container si Orange */
#define xContainer1O 30
#define yContainer1O 1075

/* Position du deuxieme container si Orange */
#define xContainer2O 695
#define yContainer2O 30

/* Position du premier container si Vert */
#define xContainer1V 2970
#define yContainer1V 1245

/* Position du deuxieme container si Vert */
#define xContainer2V 525
#define yContainer2V 30

/* Position du tir si Orange */
#define xTirO 1000
#define yTirO 1000

/* Position du tir si Vert */
#define xTirV 1000
#define yTirV 1000

/* Parametre des servos */
#define debutPorteEntree 250
#define finPorteEntree 650

#define debutPorteSortie 620
#define finPorteSortie 420

#define debutAccelerateur 380
#define finAccelerateur 220

#define _te 0.01
#define _kp 0.01
#define _ki 0.01
#define _kd 0.0001

DetectionCapteur detectionCapteur;
MachineEtat machineEtat;

#endif
