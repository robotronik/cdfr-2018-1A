from serial import *
from math import cos, pi, sin
import matplotlib.pyplot as plt
import time

L=[1,2,3,4,5,6,7,8,9,10]
L1=[11,12,13,14,15,16,17,18,19,20]
theta=[0,36,72,108,144,180,216,252,288,324,360]

import pygame
from random import randint
from pygame.locals import*
import pygame.gfxdraw
from random import uniform
 
 
pygame.init()

X,Y = 800,600
fenetre = pygame.display.set_mode((X,Y))
pygame.display.set_caption("Test")
fenetre.fill((255,255,255))
pygame.display.flip()

pygame.gfxdraw.hline(fenetre,0,800,300, (0,0,0))
pygame.gfxdraw.vline(fenetre,400,0,800, (0,0,0))
pygame.display.flip()

for i in range(0,1000):
    x = randint(0,800) 
    y = randint(0,600) 
    r = randint(0,255) 
    g = randint(0,255) 
    b = randint(0,255) 
    pygame.gfxdraw.filled_circle(fenetre, x, y, 1, (r,g,b))
    pygame.display.flip()

continuer = 1
while continuer == 1:
 
    pygame.time.Clock().tick(30)
 
    for event in pygame.event.get():
        if event.type == QUIT:
            continuer = 0
        
        elif event.type==KEYDOWN:
            if event.key==K_ESCAPE or event.key==K_q:
                continuer = 0

    pygame.display.flip()
 
 
pygame.quit()

def graphe():
    X=[]
    Y=[]
    plt.clf()
    plt.ion()
    fig=plt.figure(1)
    #mng = plt.get_current_fig_manager()        
    #mng.resize(*mng.window.maxsize())  
    #plt.scatter(0,0,s=200,color="grey")
    plt.show()   
    #plt.title("!!! Super Mega Radar De La Mort Qui Tue !!!", size='x-large', position=(0.5, 1.03), color = '0.2')
    #plt.axis('equal')
    #plt.axis([0, 0, -230, 230])
    #plt.xlabel('X polaire', size='large')
    #plt.ylabel('Y polaire', size='large')
    for i in range(50):
        d = uniform(0,200)
        t = uniform(0,6)
        X.append(d*cos(t))
        Y.append(d*sin(t))
        plt.plot(X,Y,"o:")
        #fig.canvas.draw()    
    plt.ioff()  
    plt.show()


def graphe2():
    X=[]
    Y=[]
    fig=plt.figure(1)
    mng = plt.get_current_fig_manager()        
    mng.resize(*mng.window.maxsize())  
    plt.scatter(0,0,s=200,color="grey")
    fig.show()   
    fig.canvas.draw() 
    plt.title("!!! Super Mega Radar De La Mort Qui Tue !!!", size='x-large', position=(0.5, 1.03), color = '0.2')
    plt.axis('equal')
    plt.axis([0, 0, -230, 230])
    plt.xlabel('X polaire', size='large')
    plt.ylabel('Y polaire', size='large')
    #backgrounds = fig.canvas.copy_from_bbox(fig.bbox) 

    tstart = time.time()
    for i in range(50):
        #fig.canvas.restore_region(backgrounds)
        d = uniform(0,200)
        t = uniform(0,6)
        X.append(d*cos(t))
        Y.append(d*sin(t))
        plt.plot(X,Y,"o:")
        fig.canvas.draw()    
        #fig.draw_artist(line)
        #fig.canvas.blit(fig.bbox)

    print 'FPS:' , 2000/(time.time()-tstart)
    plt.ioff()
    plt.show()


graphe2()
#graphe(L1,theta)
