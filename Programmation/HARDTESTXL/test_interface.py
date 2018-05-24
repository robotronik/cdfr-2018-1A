# -*- coding: utf-8 -*-

# Amelioration possible en recevant constamment les valeurs et en tracant le
# graphique en temps reel

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

def drawValues(n1):
    #Draw the first sweep's values
    for i in range(n1):
        xm1 = int(L1[i]*cos(radians(theta1[i])))
        ym1 = -int(L1[i]*sin(radians(theta1[i])))
        pygame.gfxdraw.filled_circle(screen, x_midpoint+int(coeff*xm1),
        y_midpoint+int(coeff*ym1), 2, value_color)

    #Draw the second sweep's values
    # for j in range(n2):
    #     xm2 = int(L2[j]*cos(radians(theta2[j])))
    #     ym2 = -int(L2[j]*sin(radians(theta2[j])))
    #     pygame.gfxdraw.filled_circle(screen, x_midpoint+int(coeff*xm2),
    #     y_midpoint+int(coeff*ym2), 2, value_color)

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
        #Draw the first 'sweep'
        xl1 = sweep_length * cos(angle-i*sweep_inter_speed) + screen_width/2
        yl1 = -sweep_length * sin(angle-i*sweep_inter_speed) + screen_height/2 - border_down
        pygame.draw.line(screen, S[i], midpoint, [xl1,yl1], line_width)

        #Draw the second sweep
        # xl2 = sweep_length * cos(angle-i*sweep_speed+pi) + screen_width/2
        # yl2 = -sweep_length * sin(angle-i*sweep_speed+pi) + screen_height/2 - border_down
        # pygame.draw.line(screen, S[i], midpoint, [xl2,yl2], line_width)

def drawText(text1, x1, y1, text2, x2, y2):
    #Draw the text for the first sweep in the box
    rect1 = pygame.Rect(x1, screen_height-2*border_down+y1, screen_width/2, screen_height-2*border_down)
    text_surface1 = font.render(text1, True, color)
    screen.blit(text_surface1, rect1)
    rect2 = pygame.Rect(x2, screen_height-2*border_down+y2, screen_width/2, screen_height-2*border_down)
    text_surface2 = font.render(text2, True, color)
    screen.blit(text_surface2, rect2)

    #Draw the text for the second sweep in the box
    # rect3 = pygame.Rect(x3, screen_height-2*border_down+y3, screen_width/2, screen_height-2*border_down)
    # text_surface3 = font.render(text3, True, color)
    # screen.blit(text_surface3, rect3)
    # rect4 = pygame.Rect(x4, screen_height-2*border_down+y4, screen_width/2, screen_height-2*border_down)
    # text_surface4 = font.render(text4, True, color)
    # screen.blit(text_surface4, rect4)

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
sweep_speed = .02
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
L1 = [300, 310, 320, 330, 340, 350, 360, 350, 340, 330, 320, 310, 300, 300,
310, 320, 330, 340, 350, 360, 350, 340, 330, 320, 310, 300, 310, 320, 330,
340, 350, 360, 350, 340, 330, 320, 310, 300, 310, 320, 330, 340, 350, 360, 350]
theta1 = [0, 7, 14, 21, 28, 36, 43, 50, 57, 64, 72, 79, 86, 93, 100, 108,
115, 122, 129, 136, 144, 151, 158, 165, 172, 180, 187, 194, 201, 208, 216,
223, 230, 237, 244, 252, 259, 266, 273, 280, 288, 295, 302, 309, 316]
# L1 = [0]
# # L2 = [0]
# theta1 = [0]
# # theta2 = [180]
# nb1 = 50
# # nb2 = 25
# for k in range(nb1):
#     d1 = random.randint(0, 2000)
#     L1.append(d1)
#     t1 = random.randint(0,320)
#     theta1.append(t1)
# # for l in range(nb2):
# #     d2 = random.randint(0, 2200)
# #     L2.append(d2)
# #     t2 = random.randint(180,359)
# #     theta2.append(t2)
# # L1 = [250,500,1000,1500,2000]
# # theta1 = [0,36,72,108,144]
n1 = len(theta1)
# L2 = [20,270,130,180,220]
# theta2 = [180,216,252,288,324,360]
# n2 = len(L2)
# theta1.sort()
# theta2.sort()
print L1
print theta1
# print L2
# print theta2

# Create the screen
screen = pygame.display.set_mode((screen_width,screen_height))
pygame.display.set_caption('Test interface balise pygame')
box = pygame.Rect(0, screen_height-2*border_down, screen_width, screen_height-2*border_down)
font = pygame.font.SysFont('OpenSans-Light', 28)

my_clock = pygame.time.Clock()

#Loop until the user clicks the close button.
continuer = 1
repeat = 358

while (continuer == 1):
    for event in pygame.event.get(): # User did something
        if event.type == pygame.QUIT: # If user clicked close
            continuer = 0
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE or event.key == pygame.K_q:
                continuer = 0
            #
            # if event.key == pygame.K_LEFT:
            #     pass
            #
            # elif event.key == pygame.K_RIGHT:
            #     pass
            #
            # elif event.key == pygame.K_UP:
            #     # no upper bounds on speed
            #     sweep_speed += sweep_interval
            #
            # elif event.key == pygame.K_DOWN:
            #     # slow it down, or stop
            #     sweep_speed -= sweep_interval
            #     if sweep_speed < 0:
            #         sweep_speed = 0

    # # Repeat the process
    # if (int((degrees(angle))) >= repeat):
    #     i = 0
    #     # j = 0
    #     angle = 0
    #     L1 = [0]
    #     # L2 = [0]
    #     theta1 = [0]
    #     # theta2 = [180]
    #     for k in range(nb1):
    #         d1 = random.randint(0, 2200)
    #         L1.append(d1)
    #         t1 = random.randint(0, 320)
    #         theta1.append(t1)
    #     # for l in range(nb2):
    #     #     d2 = random.randint(0, 2200)
    #     #     L2.append(d2)
    #     #     t2 = random.randint(180,359)
    #     #     theta2.append(t2)
    #     n1 = len(L1)
    #     # n2 = len(L2)
    #     theta1.sort()
    #     print L1
    #     print theta1
    #     # theta2.sort()

    # Draw the screen
    screen.fill(background_color)
    # text = "Out of Range"
    # dist = -1
    drawRadar()

    #Draw the values
    drawValues(i)

    #Draw the sweep_color
    drawSweep(S, 20)

    # Draw the measures of the first 'sweep'
    if (i != n1 and theta1[i] <= int(degrees(angle))):
        xm1 = int(L1[i]*cos(radians(theta1[i])))
        ym1 = -int(L1[i]*sin(radians(theta1[i])))
        pygame.gfxdraw.filled_circle(screen, x_midpoint+int(coeff*xm1),
        y_midpoint+int(coeff*ym1), 2, value_color)
        dist = L1[i]
        i+=1
        # time.sleep(0.2)
        text1 = "Angle : " + str(int(degrees(angle))) + deg
        text2 = "Distance : " + str(dist) + " mm"

    # Draw the measures of the second 'sweep'
    # if (j != n2 and theta2[j] == int(degrees(angle))+180):
    #     xm2 = int(L2[j]*cos(radians(theta2[j])))
    #     ym2 = -int(L2[j]*sin(radians(theta2[j])))
    #     pygame.gfxdraw.filled_circle(screen, x_midpoint+int(coeff*xm2),
    #     y_midpoint+int(coeff*ym2), 2, value_color)
    #     dist = L2[j]
    #     j+=1
    #     text3 = "Angle2 : " + str(int(degrees(angle))+180) + deg
    #     text4 = "Distance2 : " + str(dist) + " mm"

    # Drax the text in the box
    drawText(text1, 220, 6, text2, 360, 6)

    # # do the distortion lines
    # pygame.draw.line(screen, [133,147,176], midpoint, [311.3, 587.8], 1)
    # if (angle > 2.3 and angle < 2.8) or (angle > 4.1 and angle < 4.4):
    #     pygame.draw.line(screen, [133,147,176], midpoint, [66.2, 468.2], 1)
    # else:
    #     pygame.draw.line(screen, [133,147,176], midpoint, [502.4, 504.9], 1)

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
