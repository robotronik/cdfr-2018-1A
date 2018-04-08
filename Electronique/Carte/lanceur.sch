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
L IRF540N-RESCUE-central Q1
U 1 1 5A76719A
P 6200 3550
F 0 "Q1" H 6450 3625 50  0000 L CNN
F 1 "IRF540N" H 6450 3550 50  0000 L CNN
F 2 "Power_Integrations:TO-220" H 6450 3475 50  0000 L CIN
F 3 "" H 6200 3550 50  0000 L CNN
	1    6200 3550
	1    0    0    -1  
$EndComp
Text Notes 5600 3150 0    60   ~ 0
Jacky tuning
$Comp
L MC34152 U12
U 1 1 5A767332
P 4600 3900
F 0 "U12" H 4600 4000 60  0000 C CNN
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
L GND #PWR28
U 1 1 5A767FBA
P 3900 3800
F 0 "#PWR28" H 3900 3550 50  0001 C CNN
F 1 "GND" H 3900 3650 50  0000 C CNN
F 2 "" H 3900 3800 50  0000 C CNN
F 3 "" H 3900 3800 50  0000 C CNN
	1    3900 3800
	0    1    1    0   
$EndComp
$Comp
L GND #PWR27
U 1 1 5A767FD6
P 3900 3700
F 0 "#PWR27" H 3900 3450 50  0001 C CNN
F 1 "GND" H 3900 3550 50  0000 C CNN
F 2 "" H 3900 3700 50  0000 C CNN
F 3 "" H 3900 3700 50  0000 C CNN
	1    3900 3700
	0    1    1    0   
$EndComp
Wire Wire Line
	3900 3700 4000 3700
Wire Wire Line
	3900 3800 4000 3800
Wire Wire Line
	5350 3600 6000 3600
Wire Wire Line
	3300 3750 3300 3600
Wire Wire Line
	3300 3600 4000 3600
$Comp
L GND #PWR29
U 1 1 5A7685B8
P 6300 3900
F 0 "#PWR29" H 6300 3650 50  0001 C CNN
F 1 "GND" H 6300 3750 50  0000 C CNN
F 2 "" H 6300 3900 50  0000 C CNN
F 3 "" H 6300 3900 50  0000 C CNN
	1    6300 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 3750 6300 3900
Wire Wire Line
	6400 3100 6300 3100
Wire Wire Line
	6300 3100 6300 3350
Wire Wire Line
	5350 3700 5550 3700
Text GLabel 3300 3750 3    60   Input ~ 0
lanceur
Text GLabel 5550 3700 2    60   Input ~ 0
+15V_P
$Comp
L Conn_01x02 J10
U 1 1 5ACAAE5F
P 6600 3000
F 0 "J10" H 6600 3100 50  0000 C CNN
F 1 "Conn_01x02" H 6600 2800 50  0000 C CNN
F 2 "dsn2596:B plug 5mm" H 6600 3000 50  0001 C CNN
F 3 "" H 6600 3000 50  0001 C CNN
	1    6600 3000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR30
U 1 1 5ACAAEE8
P 6400 2650
F 0 "#PWR30" H 6400 2400 50  0001 C CNN
F 1 "GND" H 6400 2500 50  0000 C CNN
F 2 "" H 6400 2650 50  0000 C CNN
F 3 "" H 6400 2650 50  0000 C CNN
	1    6400 2650
	0    1    1    0   
$EndComp
Wire Wire Line
	6400 2650 6400 3000
$Comp
L D D11
U 1 1 5ACABC03
P 6300 2950
F 0 "D11" H 6300 3050 50  0000 C CNN
F 1 "D" H 6300 2850 50  0000 C CNN
F 2 "Diodes_SMD:D_SMA_Handsoldering" H 6300 2950 50  0001 C CNN
F 3 "" H 6300 2950 50  0001 C CNN
	1    6300 2950
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6300 2800 6400 2800
Connection ~ 6400 2800
$EndSCHEMATC
