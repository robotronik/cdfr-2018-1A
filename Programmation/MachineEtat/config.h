#ifndef CONFIG_H
#define CONFIG_H


/* Temps d'attente de la machine a etat */
#define tempsAttente 20

/* Dimension du terrain */
#define xTerrain 3000
#define yTerrain 2000

/* Position du robot au depart */
#define xRobotDepart 1486.5
#define yRobotDepart 989

/* Position du premier container */
#define xContainer1
#define yContainer1

/* Position du deuxieme container */
#define xContainer2
#define yContainer2

/* Position du tir */
#define xTir
#define yTir


/* Initialisation des parametre de tir qui se fait en meme temps que le tri */
float xTir;
float yTir;
float intervalleTir;


#endif