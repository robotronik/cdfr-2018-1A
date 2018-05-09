#include "machineEtat.h"
#include "config.h"
#include "lancer.h"
#include "attente.h"
#include "deplacement.h"

void TransitionEtats(MachineEtat* machineEtat){
    switch (machineEtat->etatActuel){
        case DEPLACEMENT:
            /* Passage de deplacement a attente si le deverouillage a ete execute */
            if ((machineEtat->deplacement).deverouillage > (machineEtat->deplacement).deverouillagePrecedent){
                ((machineEtat->deplacement).deverouillagePrecedent)++;
                machineEtat->etatActuel = ATTENTE;
                (machineEtat->attente).finAttente = 0;
                Pause(machineEtat);
            }

            /* Passage de deplacement a triage si pret a tri (mis dans la bonne position) */
            else if ((machineEtat->deplacement).pretTri){
                machineEtat->etatActuel = TRIAGE;
            }

            /* Si ultrason detecte quelque chose */
            else if ((machineEtat->deplacement).detectionCapteur.detection){
                machineEtat->etatActuel = ATTENTE;
                (machineEtat->attente).finAttente = 0;
                ArretUltrason(machineEtat);
            }

            else{
                DeplacementGlobal(machineEtat);
            }
            break;

        case TRIAGE:
            /* Passe au tir si la couleur detecte est egal a la notre */
            if ((machineEtat->triage).maCouleur == (machineEtat->triage).couleurDetecte){
                (machineEtat->lancer).tir = 1;
                machineEtat->etatActuel = LANCER;
                ActivationMoteur();
            }
            /* Passe au deplacement si le tri actuel est fini */
            else if ((machineEtat->triage).tri > (machineEtat->triage).triPrecedent){
                machineEtat->etatActuel = DEPLACEMENT;
                (machineEtat->triage).nombreBallesTri1 = (machineEtat->triage).nombreBallesDetectees;
                (machineEtat->triage).triPrecedent++;
            }
            break;

        case LANCER:
            /* Passe au tri quand le tir est fini */
            if ((machineEtat->lancer).tir == 0){
                machineEtat->etatActuel = TRIAGE;
            }
            break;

        case ATTENTE:
            /* Reste en attente si une detection se fait */
            if ((machineEtat->deplacement).detectionCapteur.detection){
                ArretUltrason(machineEtat);
            }

            /* Reviens au deplacement quand l'attente est fini */
            else if ((machineEtat->attente).finAttente){
                machineEtat->etatActuel = DEPLACEMENT;
                DeplacementGlobal(machineEtat);
            }

            break;
    }
}

void InitialisationParametresGlobaux(MachineEtat* machineEtat){
    (machineEtat->deplacement).dimTerrain.x = xTerrain;
    (machineEtat->deplacement).dimTerrain.y = yTerrain;
    (machineEtat->attente).deltaT = tempsAttente;
    machineEtat->etatActuel = DEPLACEMENT;
    (machineEtat->attente).finAttente = 1;
    (machineEtat->deplacement).deverouillage = 0;
    (machineEtat->deplacement).deverouillageValide = 0;
    (machineEtat->deplacement).deverouillagePrecedent = 0;
    (machineEtat->deplacement).detectionCapteur.detection = 0;
    (machineEtat->triage).secouer = 0;
    (machineEtat->triage).secouerPrecedent = 0;
    (machineEtat->triage).nombreBallesDetectees = 0;
    (machineEtat->triage).nombreBallesTri1 = 0;
    (machineEtat->triage).servoPret = -1;
    (machineEtat->deplacement).detectionCapteur.seuilDetection = distanceDeSeuil;

    if ((machineEtat->triage).maCouleur == 1){
        (machineEtat->deplacement).positionRobot.x = xRobotDepartO;
        (machineEtat->deplacement).positionRobot.y = yRobotDepartO;
        (machineEtat->deplacement).positionContainer1.x = xContainer1O;
        (machineEtat->deplacement).positionContainer1.y = yContainer1O;
        (machineEtat->deplacement).positionContainer2.x = xContainer2O;
        (machineEtat->deplacement).positionContainer2.y = yContainer2O;
        (machineEtat->deplacement).positionTir.x = xTirO;
        (machineEtat->deplacement).positionTir.y = yTirO;
    }

    else{
        (machineEtat->deplacement).positionRobot.x = xRobotDepartV;
        (machineEtat->deplacement).positionRobot.y = yRobotDepartV;
        (machineEtat->deplacement).positionContainer1.x = xContainer1V;
        (machineEtat->deplacement).positionContainer1.y = yContainer1V;
        (machineEtat->deplacement).positionContainer2.x = xContainer2V;
        (machineEtat->deplacement).positionContainer2.y = yContainer2V;
        (machineEtat->deplacement).positionTir.x = xTirV;
        (machineEtat->deplacement).positionTir.y = yTirV;
    }
    //XL_Set_Goal_Position( &((machineEtat->lancer).accelerateur.servo), (machineEtat->lancer).accelerateur.posOuvert, 1);
}