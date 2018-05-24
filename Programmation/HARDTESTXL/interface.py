# -*- coding: utf-8 -*-

# Amelioration possible en recevant constamment les valeurs et en tracant le
# graphique en temps reel

# Module de lecture/ecriture du port serie
from serial import *
from math import cos, pi, sin
import matplotlib.pyplot as plt

# Port serie ttyACM0
# Vitesse de baud : 115200
# Timeout en lecture : 1 sec
# Timeout en ecriture : 1 sec
L=[]  #liste des valeurs lues par le capteur

# Import librairies
import random
import time
import pygame
import pygame.gfxdraw
import math
from math import cos, sin, sqrt, radians, degrees

def drawGraphValues():
    # Draw the values of the angle references
    textfont = pygame.font.SysFont('OpenSans-Light', 22)
    rectv1 = pygame.Rect(340, 7, 50, 20)
    text_surfacev1 = textfont.render("90"+deg, True, color)
    screen.blit(text_surfacev1, rectv1)
    rectv2 = pygame.Rect(500, 45, 50, 20)
    text_surfacev2 = textfont.render("60"+deg, True, color)
    screen.blit(text_surfacev2, rectv2)
    rectv3 = pygame.Rect(620, 165, 50, 20)
    text_surfacev3 = textfont.render("30"+deg, True, color)
    screen.blit(text_surfacev3, rectv3)
    rectv4 = pygame.Rect(665, 320, 50, 20)
    text_surfacev4 = textfont.render("0"+deg, True, color)
    screen.blit(text_surfacev4, rectv4)
    rectv5 = pygame.Rect(175, 45, 50, 20)
    text_surfacev5 = textfont.render("120"+deg, True, color)
    screen.blit(text_surfacev5, rectv5)
    rectv6 = pygame.Rect(50, 165, 50, 20)
    text_surfacev6 = textfont.render("150"+deg, True, color)
    screen.blit(text_surfacev6, rectv6)
    rectv7 = pygame.Rect(5, 320, 50, 20)
    text_surfacev7 = textfont.render("180"+deg, True, color)
    screen.blit(text_surfacev7, rectv7)
    rectv8 = pygame.Rect(45, 480, 50, 20)
    text_surfacev8 = textfont.render("210"+deg, True, color)
    screen.blit(text_surfacev8, rectv8)
    rectv9 = pygame.Rect(170, 600, 50, 20)
    text_surfacev9 = textfont.render("240"+deg, True, color)
    screen.blit(text_surfacev9, rectv9)
    rectv10 = pygame.Rect(335, 638, 50, 20)
    text_surfacev10 = textfont.render("270"+deg, True, color)
    screen.blit(text_surfacev10, rectv10)
    rectv11 = pygame.Rect(500, 600, 50, 20)
    text_surfacev11 = textfont.render("300"+deg, True, color)
    screen.blit(text_surfacev11, rectv11)
    rectv12 = pygame.Rect(620, 480, 50, 20)
    text_surfacev12 = textfont.render("330"+deg, True, color)
    screen.blit(text_surfacev12, rectv12)
    rectv13 = pygame.Rect(615, 313, 50, 20)

    # Draw the values of the distance references
    text_surfacev13 = textfont.render("2m", True, color)
    screen.blit(text_surfacev13, rectv13)
    rectv14 = pygame.Rect(530, 313, 50, 20)
    text_surfacev14 = textfont.render("1.5m", True, color)
    screen.blit(text_surfacev14, rectv14)
    rectv15 = pygame.Rect(470, 313, 50, 20)
    text_surfacev15 = textfont.render("1m", True, color)
    screen.blit(text_surfacev15, rectv15)
    rectv16 = pygame.Rect(382, 313, 50, 20)
    text_surfacev16 = textfont.render("50cm", True, color)
    screen.blit(text_surfacev16, rectv16)

def drawValues(n):
    #Draw the sweep's values
    for i in range(n1):
        xm1 = int(Distance[i]*cos(radians(Angle[i])))
        ym1 = -int(Distance[i]*sin(radians(Angle[i])))
        pygame.gfxdraw.filled_circle(screen, x_midpoint+int(coeff*xm1),
        y_midpoint+int(coeff*ym1), 2, value_color)

def Sweepcolor(S, x):
    # Calculate the colors for the 'sweep' effect
    delta = int(220/x)
    for i in range(x):
        color = [0, 220-i*delta,0]
        S.append(color)

def drawSweep(S, x):
    # Calculate the x,y for the end point of our 'sweep' based on the current angle
    # Draw the line from the center to the calculated end spot
    for i in range(x-5):
        #Draw the 'sweep'
        xDistance = sweep_length * cos(angle-i*sweep_inter_speed) + screen_width/2
        yDistance = -sweep_length * sin(angle-i*sweep_inter_speed) + screen_height/2 - border_down
        pygame.draw.line(screen, S[i], midpoint, [xDistance,yDistance], line_width)

def drawText(text1, x1, y1, text2, x2, y2):
    #Draw the text for the sweep in the box
    rect1 = pygame.Rect(x1, screen_height-2*border_down+y1, screen_width/2, screen_height-2*border_down)
    text_surface1 = font.render(text1, True, color)
    screen.blit(text_surface1, rect1)
    rect2 = pygame.Rect(x2, screen_height-2*border_down+y2, screen_width/2, screen_height-2*border_down)
    text_surface2 = font.render(text2, True, color)
    screen.blit(text_surface2, rect2)

def drawRadar():
    # Draw the circles
    pygame.gfxdraw.aacircle(screen, midpoint[0], midpoint[1], circle_radius, color)
    pygame.gfxdraw.aacircle(screen, midpoint[0], midpoint[1], 2*circle_radius, color)
    pygame.gfxdraw.aacircle(screen, midpoint[0], midpoint[1], 3*circle_radius, color)
    pygame.gfxdraw.aacircle(screen, midpoint[0], midpoint[1], 4*circle_radius, color)

    # Draw the lines
    pygame.gfxdraw.line(screen, x_midpoint-line_length, y_midpoint,
    x_midpoint+line_length, y_midpoint, color)
    pygame.gfxdraw.line(screen, x_midpoint-int(cos(radians(30))*line_length),
    y_midpoint+int(sin(radians(30))*line_length), x_midpoint+int(cos(radians(30))*line_length),
    y_midpoint-int(sin(radians(30))*line_length), color)
    pygame.gfxdraw.line(screen, x_midpoint-int(cos(radians(60))*line_length),
    y_midpoint+int(sin(radians(60))*line_length), x_midpoint+int(cos(radians(60))*line_length),
    y_midpoint-int(sin(radians(60))*line_length), color)
    pygame.gfxdraw.line(screen, x_midpoint-int(cos(radians(90))*line_length),
    y_midpoint+int(sin(radians(90))*line_length), x_midpoint+int(cos(radians(90))*line_length),
    y_midpoint-int(sin(radians(90))*line_length), color)
    pygame.gfxdraw.line(screen, x_midpoint-int(cos(radians(120))*line_length),
    y_midpoint+int(sin(radians(120))*line_length), x_midpoint+int(cos(radians(120))*line_length),
    y_midpoint-int(sin(radians(120))*line_length), color)
    pygame.gfxdraw.line(screen, x_midpoint-int(cos(radians(150))*line_length),
    y_midpoint+int(sin(radians(150))*line_length), x_midpoint+int(cos(radians(150))*line_length),
    y_midpoint-int(sin(radians(150))*line_length), color)

    # Draw the box
    pygame.gfxdraw.box(screen, box, box_color)

    # Draw the values on the graph
    drawGraphValues()

def graph(Angle, Distance):
    # Initialize the game engine
    pygame.init()
    pygame.font.init()

    # Define the colors we will use in RGB format
    background_color    = [  46,  48,  47 ]
    S = []
    Sweepcolor(S, 20)
    color               = [   0, 220,   0 ]
    box_color           = [  20,  20,  20 ]
    value_color         = [   0,   0, 255 ]

    # Set the height and width of the screen
    screen_width = 700
    screen_height = 700
    border_down = 20
    screen_border = 20

    # Set the other variables
    circle_radius = 73
    line_width = 2
    sweep_speed = .05
    sweep_inter_speed = .01
    sweep_length = 305
    line_length = sweep_length
    deg = "\xb0"
    pi = 3.141592653
    coeff = 0.1465
    x_midpoint = screen_width/2
    y_midpoint = screen_height/2 - border_down
    midpoint = [ x_midpoint, y_midpoint ]

    # Init variables
    angle = 0
    dist = -1
    i = 0
    # j = 0
    # Distance = [0]
    # # L2 = [0]
    # Angle = [0]
    # # theta2 = [180]
    # nb1 = 50
    # # nb2 = 25
    # for k in range(nb1):
    #     d1 = random.randint(0, 2200)
    #     Distance.append(d1)
    #     t1 = random.randint(0,359)
    #     Angle.append(t1)
    # n1 = len(Distance)
    # Angle.sort()
    # print Distance
    # print Angle

    # Create the screen
    screen = pygame.display.set_mode((screen_width,screen_height))
    pygame.display.set_caption('Test interface balise pygame')
    box = pygame.Rect(0, screen_height-2*border_down, screen_width, screen_height-2*border_down)
    font = pygame.font.SysFont('OpenSans-Light', 28)

    my_clock = pygame.time.Clock()

    # Loop until the user clicks the close button.
    continuer = 1

    while (continuer == 1):
        for event in pygame.event.get(): # User did something
            if event.type == pygame.QUIT: # If user clicked close
                continuer = 0
            elif event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE or event.key == pygame.K_q:
                    continuer = 0

        # Draw the screen
        screen.fill(background_color)
        # text = "Out of Range"
        # dist = -1
        drawRadar()

        #Draw the values
        drawValues(i)

        #Draw the sweep_color
        drawSweep(S, 20)

        # Draw the measures of the 'sweep'
        if (i != n1 and Angle[i] <= int(degrees(angle))):
            xm1 = int(Distance[i]*cos(radians(Angle[i])))
            ym1 = -int(Distance[i]*sin(radians(Angle[i])))
            pygame.gfxdraw.filled_circle(screen, x_midpoint+int(coeff*xm1),
            y_midpoint+int(coeff*ym1), 2, value_color)
            dist = Distance[i]
            i+=1
            # time.sleep(0.2)
            text1 = "Angle : " + str(int(degrees(angle))) + deg
            text2 = "Distance : " + str(dist) + " mm"

        # Drax the text in the box
        drawText(text1, 220, 6, text2, 360, 6)

        # Increase the angle by 0.05 radians
        angle = angle + sweep_speed

        # If we have done a full sweep, reset the angle to 0
        if angle > 2*pi:
            angle = angle - 2*pi

        # Update the display, wait out the clock tick
        pygame.display.update()
        my_clock.tick(60)

    # Quit the pygame's elements
    pygame.font.quit()
    pygame.quit()

with Serial(port="/dev/ttyACM0", baudrate=115200, timeout=1, writeTimeout=1) as port_serie:   #port serie
    if port_serie.isOpen():
	while True:
            ligne = port_serie.readline()                             #lire la ligne de transmission
            if(len(ligne)>1):                                         #si pas de problemes
                ligne=ligne[:-1]                                      #virer le \n
                L=ligne.split('|')                                    #recomposer les valeurs
                print("Liste :")
                print(L)
                D=L[0].split(',')
                A=L[1].split(',')
                #theta = [t*360/len(L)*pi/180 for t in range(len(L))]  #theta
                print("distance :")
                print(D)
                print("theta :")
                print(A)
                #graph(D,A)                                       #graphe
