#include "ultrason.h"



void InitialiserCapteur(DetectionCapteur* detectionCapteur, GPIO_TypeDef* portUsAvantGauche, uint16_t pinUsAvantGauche, GPIO_TypeDef* portUsAvant, uint16_t pinUsAvant, GPIO_TypeDef* portUsAvantDroit, uint16_t pinUsAvantDroit, GPIO_TypeDef* portUsArriere, uint16_t pinUsArriere, uint32_t seuilDetection){
    detectionCapteur->seuilDetection = seuilDetection;
    
    (detectionCapteur->usAvantGauche).detection = 0;
    (detectionCapteur->usAvant).detection = 0;
    (detectionCapteur->usAvantDroit).detection = 0;
    (detectionCapteur->usArriere).detection = 0;

    (detectionCapteur->usAvantGauche).tensionPrecedent = 0;
    (detectionCapteur->usAvantGauche).tension = 0;
    (detectionCapteur->usAvantGauche).tempsReception = 0;
    (detectionCapteur->usAvantGauche).tempsEnvoie = 0;
    (detectionCapteur->usAvantGauche).port = portUsAvantGauche;
    (detectionCapteur->usAvantGauche).pin = pinUsAvantGauche;

    
    (detectionCapteur->usAvant).tensionPrecedent = 0;
    (detectionCapteur->usAvant).tension = 0;
    (detectionCapteur->usAvant).tempsReception = 0;
    (detectionCapteur->usAvant).tempsEnvoie = 0;
    (detectionCapteur->usAvant).port = portUsAvant;
    (detectionCapteur->usAvant).pin = pinUsAvant;
    
    (detectionCapteur->usAvantDroit).tensionPrecedent = 0;
    (detectionCapteur->usAvantDroit).tension = 0;
    (detectionCapteur->usAvantDroit).tempsReception = 0;
    (detectionCapteur->usAvantDroit).tempsEnvoie = 0;
    (detectionCapteur->usAvantDroit).port = portUsAvantDroit;
    (detectionCapteur->usAvantDroit).pin = pinUsAvantDroit;
    
    (detectionCapteur->usArriere).tensionPrecedent = 0;
    (detectionCapteur->usArriere).tension = 0;
    (detectionCapteur->usArriere).tempsReception = 0;
    (detectionCapteur->usArriere).tempsEnvoie = 0;
    (detectionCapteur->usArriere).port = portUsArriere;
    (detectionCapteur->usArriere).pin = pinUsArriere;
}

void DetecterObstacleGlobal(DetectionCapteur* detectionCapteur, uint16_t GPIO_Pin){
    switch (GPIO_Pin){
        case US_IN_1_Pin :
                DetecterObstableUnitaire(&(detectionCapteur->usAvantGauche));
                //(detectionCapteur->usAvantDroit).detection = 1;
            break;
        
        case US_IN_2_Pin :
                DetecterObstableUnitaire(&(detectionCapteur->usAvant));
                //(detectionCapteur->usAvantDroit).detection = 1;
            break;

        case US_IN_3_Pin :
                DetecterObstableUnitaire(&(detectionCapteur->usAvantDroit));
                //(detectionCapteur->usAvantDroit).detection = 1;
            break;

        case US_IN_4_Pin :
                DetecterObstableUnitaire(&(detectionCapteur->usArriere));
            break;
    }

    if (detectionCapteur->usAvantGauche.detection==1 || detectionCapteur->usAvant.detection==1 || detectionCapteur->usAvantDroit.detection==1 || detectionCapteur->usArriere.detection==1 )
    {
        detectionCapteur->detection = 1;
        HAL_GPIO_WritePin(GPIOA, LD2_Pin,1);
    }
    else{
        detectionCapteur->detection = 0;
        HAL_GPIO_WritePin(GPIOA, LD2_Pin,0);
    }
}

void DetecterObstableUnitaire(TestUltrason* testUltrason){
    testUltrason->tension = HAL_GPIO_ReadPin (testUltrason->port, testUltrason->pin);
    if (testUltrason->tension > testUltrason->tensionPrecedent){
        testUltrason->tempsEnvoie = HAL_GetTick();
        testUltrason->tempsReception = testUltrason->tempsEnvoie;
    }
    else if (testUltrason->tension < testUltrason->tensionPrecedent){
        testUltrason->tempsReception = HAL_GetTick();
    }
    if( (((testUltrason->tempsReception - testUltrason->tempsEnvoie)*1000*17/100) < 200) && (testUltrason->tempsEnvoie < testUltrason->tempsReception)){
        testUltrason->detection = 1;
    }
    else if (testUltrason->tempsEnvoie < testUltrason->tempsReception){
        testUltrason->detection = 0;
    }
    testUltrason->tensionPrecedent = testUltrason->tension;
}