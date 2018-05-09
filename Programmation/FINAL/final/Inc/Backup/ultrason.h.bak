#ifndef ULTRASON_H
#define ULTRASON_H


#include "stm32f4xx.h"
#include "machineEtat.h"




/*
Permet la detection des obstacles
Fait evoluer les valeurs en parametre a 1 si detection sinon 0
*/
void DetecterObstacleGlobal(MachineEtat* machineEtat, uint16_t GPIO_Pin);

/*
Fait un test de detection pour un capteur quelconque
Renvoie 1 si la distance de l'objet est inferieur au seuil de detection
Sinon 0
*/
void DetecterObstableUnitaire(TestUltrason* testUltrason);

/*
Permet l'initialisation des capteurs
*/
void InitialiserCapteur(DetectionCapteur* detectionCapteur, GPIO_TypeDef* portUsAvantGauche, uint16_t pinUsAvantGauche, GPIO_TypeDef* portUsAvant, uint16_t pinUsAvant, GPIO_TypeDef* portUsAvantDroit, uint16_t pinUsAvantDroit, GPIO_TypeDef* portUsArriere, uint16_t pinUsArriere);

#endif