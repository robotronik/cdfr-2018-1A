# Module de lecture/ecriture du port serie
from serial import *
from math import cos, pi, sin
import matplotlib.pyplot as plt

# Port serie ttyACM0
# Vitesse de baud : 115200
# Timeout en lecture : 1 sec
# Timeout en ecriture : 1 sec

L=[]                                           #liste des valeurs lues par le capteur

def graphe(L,theta):                           #fonction graphe
    X=[]                                       #abscisses
    Y=[]                                       #ordonnees
    plt.clf()                                  #clear le graphe
    plt.ion()                                  #affichage dynamique
    fig=plt.figure(1)                          #creation figure 1
    mng = plt.get_current_fig_manager()        #affichage plein ecran
    mng.resize(*mng.window.maxsize())
    for i in range(len(L)):                    #parcourir la trame de donnees recues
        plt.scatter(0,0,s=200,color="grey")    #point central
        plt.show()                             #affichage du point central
        if(L[i].isdigit()):                    #si pas de problemes
            X.append(int(L[i])*cos(int(theta[i])*pi/180))  #ajout x en polaires
            Y.append(int(L[i])*sin(int(theta[i])*pi/180))  #ajout y en polaires
            plt.title("!!! Super Mega Radar De La Mort Qui Tue !!!", size='x-large',
            position=(0.5, 1.03), color = '0.2') #titre
            plt.axis('equal')                  #forme circulaire (evite les problemes de deformation des axes)
            plt.axis([0, 0, -230, 230])        #range des axes (force l'axe des y)
            plt.xlabel('X polaire', size='large')  #titre x
            plt.ylabel('Y polaire', size='large')  #titre y
            plt.plot(X,Y,"o:")                 #affichage en pointilles avec points en etoile
            #plt.plot([0, X[i]], [0, Y[i]])    #affichage du trait "dynamique"
            fig.canvas.draw()                  #affichage dynamique de la figure
    plt.show()                                 #affichage


with Serial(port="/dev/ttyACM0", baudrate=115200, timeout=1, writeTimeout=1) as port_serie:   #port serie
    if port_serie.isOpen():
	while True:
            ligne = port_serie.readline()           #lire la ligne de transmission
            if(len(ligne)>1):                       #si pas de problemes
                ligne=ligne[:-1]                    #virer le \n
                L=ligne.split('|')                  #separation des distances des angles
                print("Liste :")
                print(L)
                D=L[0].split(',')                   #creation liste distance
                A=L[1].split(',')                   #creation liste angle
                print("distance :")
                print(D)
                print("theta :")
                print(A)
                graphe(D,A)                        #graphe
