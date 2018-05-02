#include "machineEtat.h"
#include "config.h"

void TransitionEtats(MachineEtat* machineEtat){
    switch (machineEtat->etatActuel){
        case DEPLACEMENT:
            /* Passage de deplacement a attente si le deverouillage a ete execute */
            if ((machineEtat->deplacement).deverouillage > (machineEtat->deplacement).deverouillagePrecedent){
                (machineEtat->deplacement).deverouillagePrecedent)++;
                machineEtat->etatActuel = ATTENTE;
            }

            /* Passage de deplacement a triage si pret a tri (mis dans la bonne position) */
            else if ((machineEtat->deplacement).pretTri)
                machineEtat->etatActuel = TRIAGE;
            break;

        case TRIER:
            /* Passe au tir si la couleur detecte est egal a la notre */
            else if ((machineEtat->trier).couleur == (machineEtat->trier).couleurDetecte)
                machineEtat->etatActuel = LANCER;
            break;

        case LANCER:
            else if (t)
            break;

        case ATTENTE:

            break;
    }
}