EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:2
LIBS:mcp2562
LIBS:dsn2596
LIBS:1A_cdfr2017
LIBS:central-cache
LIBS:central-rescue
LIBS:carte_1A_cdfr2018-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 4
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L IRF540N-RESCUE-central Q?
U 1 1 5ACA98C2
P 6200 3550
F 0 "Q?" H 6450 3625 50  0000 L CNN
F 1 "IRF540N" H 6450 3550 50  0000 L CNN
F 2 "Power_Integrations:TO-220" H 6450 3475 50  0000 L CIN
F 3 "" H 6200 3550 50  0000 L CNN
	1    6200 3550
	1    0    0    -1  
$EndComp
Text Notes 5600 3150 0    60   ~ 0
Jacky tuning
$Comp
L MC34152 U?
U 1 1 5ACA98C3
P 4600 3900
F 0 "U?" H 4600 4000 60  0000 C CNN
F 1 "MC34152" H 4650 4150 60  0000 C CNN
F 2 "Housings_DIP:DIP-8_W7.62mm_LongPads" H 4600 3900 60  0001 C CNN
F 3 "" H 4600 3900 60  0000 C CNN
	1    4600 3900
	1    0    0    -1  
$EndComp
NoConn ~ 5350 3500
NoConn ~ 4000 3500
NoConn ~ 5350 3800
$Comp
L GND #PWR053
U 1 1 5ACA98C4
P 3900 3800
F 0 "#PWR053" H 3900 3550 50  0001 C CNN
F 1 "GND" H 3900 3650 50  0000 C CNN
F 2 "" H 3900 3800 50  0000 C CNN
F 3 "" H 3900 3800 50  0000 C CNN
	1    3900 3800
	0    1    1    0   
$EndComp
$Comp
L GND #PWR054
U 1 1 5ACA98C5
P 3900 3700
F 0 "#PWR054" H 3900 3450 50  0001 C CNN
F 1 "GND" H 3900 3550 50  0000 C CNN
F 2 "" H 3900 3700 50  0000 C CNN
F 3 "" H 3900 3700 50  0000 C CNN
	1    3900 3700
	0    1    1    0   
$EndComp
Wire Wire Line
	3300 3750 3300 3600
$Comp
L GND #PWR055
U 1 1 5ACA98C8
P 6300 3900
F 0 "#PWR055" H 6300 3650 50  0001 C CNN
F 1 "GND" H 6300 3750 50  0000 C CNN
F 2 "" H 6300 3900 50  0000 C CNN
F 3 "" H 6300 3900 50  0000 C CNN
	1    6300 3900
	1    0    0    -1  
$EndComp
Text GLabel 5550 3700 2    60   Input ~ 0
15V_P
Text GLabel 3300 3750 3    60   Input ~ 0
lanceur
Wire Wire Line
	3300 3600 4000 3600
Wire Wire Line
	3900 3700 4000 3700
Wire Wire Line
	3900 3800 4000 3800
Wire Wire Line
	5350 3700 5550 3700
Wire Wire Line
	5350 3600 6000 3600
Wire Wire Line
	6300 3750 6300 3900
Wire Wire Line
	6300 3350 6300 3100
Wire Wire Line
	6300 3100 6400 3100
$Comp
L CONN_01X03 P?
U 1 1 5ACAAA35
P 6600 3000
F 0 "P?" H 6600 3200 50  0000 C CNN
F 1 "CONN_01X03" V 6700 3000 50  0000 C CNN
F 2 "Connectors_Molex:Molex_KK-6410-03_03x2.54mm_Straight" H 6600 3000 50  0000 C CNN
F 3 "" H 6600 3000 50  0000 C CNN
	1    6600 3000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR?
U 1 1 5ACAAA82
P 6300 3000
F 0 "#PWR?" H 6300 2750 50  0001 C CNN
F 1 "GND" H 6300 2850 50  0000 C CNN
F 2 "" H 6300 3000 50  0000 C CNN
F 3 "" H 6300 3000 50  0000 C CNN
	1    6300 3000
	0    1    1    0   
$EndComp
Wire Wire Line
	6300 3000 6400 3000
Wire Wire Line
	6400 2900 6350 2900
Wire Wire Line
	6350 2900 6350 2600
Text GLabel 6350 2600 1    60   Input ~ 0
M1OUT1
$Comp
L PWR_FLAG #FLG?
U 1 1 5ACAAAAF
P 6350 2700
F 0 "#FLG?" H 6350 2775 50  0001 C CNN
F 1 "PWR_FLAG" H 6350 2850 50  0000 C CNN
F 2 "" H 6350 2700 50  0001 C CNN
F 3 "" H 6350 2700 50  0001 C CNN
	1    6350 2700
	0    -1   -1   0   
$EndComp
Connection ~ 6350 2700
$EndSCHEMATC
