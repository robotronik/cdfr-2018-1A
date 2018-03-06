from serial import *
from math import cos, pi, sin
import matplotlib.pyplot as plt
import time

L=[1,2,3,4,5,6,7,8,9,10]
L1=[11,12,13,14,15,16,17,18,19,20]
theta=[0,36,72,108,144,180,216,252,288,324,360]

def graphe(L,theta):
    X=[]
    Y=[]
    plt.ion()
    fig=plt.figure(1)
    for i in range(10):
        time.sleep(0.1)
        X.append(int(L[i])*cos(theta[i]))
        Y.append(int(L[i])*sin(theta[i]))
        plt.plot(X,Y,'go')
        fig.canvas.draw()      
    plt.show()


graphe(L,theta)
graphe(L1,theta)
