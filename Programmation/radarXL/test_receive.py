# Module de lecture/ecriture du port serie
from serial import *
from math import cos, pi, sin
import matplotlib.pyplot as plt
import time
# Port serie ttyACM0
# Vitesse de baud : 9600
# Timeout en lecture : 1 sec
# Timeout en ecriture : 1 sec
L=[]                                           #liste des valeurs lues par le capteur

def graphe(L,theta):                           #fonction graphe                       
    X=[]                                       #abscisses 
    Y=[]                                       #ordonnees
    plt.clf()                                  #clear le graphe
    plt.ion()                                  #affichage dynamique
    fig=plt.figure(1)                          #creation figure 1
    for i in range(len(L)):                    #parcourir la trame de donnees recues
        if(L[i]!=''):                          #si pas de problemes
            X.append(int(L[i])*cos(theta[i]))  #ajout x en polaire
            Y.append(int(L[i])*sin(theta[i]))  #ajout y en poalire
            plt.plot(X,Y,"*:")                 #affichage en pointilles avec points en etoile
            fig.canvas.draw()                  #affichage dynamique de la figure
    plt.show()                                 #affichage


with Serial(port="/dev/ttyACM0", baudrate=1000000, timeout=1, writeTimeout=1) as port_serie:   #port serie
    if port_serie.isOpen():
	while True:
            ligne = port_serie.readline()                             #lire la ligne de transmission
            if(len(ligne)>1):                                         #si pas de problemes
                ligne=ligne[:-1]                                      #virer le \n
                L=ligne.split(',')                                    #recomposer les valeurs
                print("Liste :")   
                print(L)
                theta = [t*360/len(L)*pi/180 for t in range(len(L))]  #theta
                print("theta :")
                print(theta)
                graphe(L,theta)                                       #graphe

