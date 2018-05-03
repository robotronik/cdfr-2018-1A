#include "machineEtat.h"
#include "config.h"

void TransitionEtats(MachineEtat* machineEtat){
    switch (machineEtat->etatActuel){
        case DEPLACEMENT:
            /* Passage de deplacement a attente si le deverouillage a ete execute */
            if ((machineEtat->deplacement).deverouillage > (machineEtat->deplacement).deverouillagePrecedent){
                (machineEtat->deplacement).deverouillagePrecedent)++;
                machineEtat->etatActuel = ATTENTE;
                (machineEtat->attente).finAttente = 0;
            }

            /* Passage de deplacement a triage si pret a tri (mis dans la bonne position) */
            else if ((machineEtat->deplacement).pretTri)
                machineEtat->etatActuel = TRIAGE;
            break;

        case TRIER:
            /* Passe au tir si la couleur detecte est egal a la notre */
            if ((machineEtat->triage).maCouleur == (machineEtat->triage).couleurDetecte){
                (machineEtat->lancer).tir = 1;
                machineEtat->etatActuel = LANCER;
            }
            /* Passe au deplacement si le tri actuel est fini */
            else if ((machineEtat->triage).tri > (machineEtat->triage).triPrecedent){
                machineEtat->etatActuel = DEPLACEMENT;
                (machineEtat->triage).triPrecedent++;
            }

            break;

        case LANCER:
            /* Passe au tri quand le tir est fini */
            else if ((machineEtat->lancer).tir == 0){
                (machineEtat->lancer).tir = 0;
                machineEtat->etatActuel = TRIAGE;
            }
            break;

        case ATTENTE:
            /* Reviens au deplacement quand l'attente est fini */
            if ((machineEtat->attente).finAttente)
                machineEtat->etatActuel = DEPLACEMENT;
            break;
    }
}

void InitialisationParametresGlobaux(MachineEtat* machineEtat){
    if((machineEtat->triage).couleurDetecte == "O"){
        (machineEtat->deplacement).xTerrain = xTerrainO;
        (machineEtat->deplacement).yTerrain = yTerrainO;
        (machineEtat->deplacement).xRobot = xRobotO;
        (machineEtat->deplacement).yRobot = yRobotO;
    }
    else if((machineEtat->triage).couleurDetecte == "V"){
        (machineEtat->deplacement).xTerrain = xTerrainV;
        (machineEtat->deplacement).yTerrain = yTerrainV;
        (machineEtat->deplacement).xRobot = xRobotV;
        (machineEtat->deplacement).yRobot = yRobotV;
    }
    (machineEtat->attente).deltaT = tempsAttente;
    (machineEtat->attente).finAttente = 1;

    

}