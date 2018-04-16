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
LIBS:1A_cdfr2017
LIBS:central-cache
LIBS:central-rescue
LIBS:robot_1A
LIBS:dsn2596
LIBS:carte_1A_cdfr2018-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 4
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
L LED-RESCUE-carte_centrale D1
U 1 1 5916B53E
P 2700 3550
F 0 "D1" H 2700 3650 50  0000 C CNN
F 1 "LED" H 2700 3450 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 2700 3550 50  0001 C CNN
F 3 "" H 2700 3550 50  0001 C CNN
	1    2700 3550
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 5916B62D
P 3150 3550
F 0 "R2" V 3230 3550 50  0000 C CNN
F 1 "2.7k" V 3150 3550 50  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 3080 3550 50  0001 C CNN
F 3 "" H 3150 3550 50  0001 C CNN
	1    3150 3550
	0    1    1    0   
$EndComp
Text GLabel 3600 2950 1    60   Input ~ 0
BATT
Text GLabel 2250 3550 0    60   Input ~ 0
GND
Text GLabel 3600 3800 3    60   Input ~ 0
BATT_P
Wire Wire Line
	2250 3550 2550 3550
Wire Wire Line
	2850 3550 3000 3550
Connection ~ 3600 3550
$Comp
L D D3
U 1 1 5916B9FB
P 2900 3750
F 0 "D3" H 2900 3850 50  0000 C CNN
F 1 "D" H 2900 3650 50  0000 C CNN
F 2 "Diodes_SMD:D_SMA_Handsoldering" H 2900 3750 50  0001 C CNN
F 3 "" H 2900 3750 50  0001 C CNN
	1    2900 3750
	-1   0    0    1   
$EndComp
Wire Wire Line
	2400 3550 2400 3750
Wire Wire Line
	2400 3750 2750 3750
Connection ~ 2400 3550
Wire Wire Line
	3050 3750 3450 3750
$Comp
L PWR_FLAG #FLG031
U 1 1 591A32A2
P 3750 3650
F 0 "#FLG031" H 3750 3725 50  0001 C CNN
F 1 "PWR_FLAG" H 3750 3800 50  0000 C CNN
F 2 "" H 3750 3650 50  0001 C CNN
F 3 "" H 3750 3650 50  0001 C CNN
	1    3750 3650
	0    1    1    0   
$EndComp
Wire Wire Line
	3600 3650 3750 3650
Connection ~ 3600 3650
Wire Wire Line
	3450 3750 3450 3550
Wire Wire Line
	3300 3550 3600 3550
Connection ~ 3450 3550
Wire Wire Line
	3600 2950 3600 3800
$Comp
L LED-RESCUE-carte_centrale D5
U 1 1 5A64E19E
P 4800 3550
F 0 "D5" H 4800 3650 50  0000 C CNN
F 1 "LED" H 4800 3450 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 4800 3550 50  0001 C CNN
F 3 "" H 4800 3550 50  0001 C CNN
	1    4800 3550
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 5A64E1A4
P 5250 3550
F 0 "R4" V 5330 3550 50  0000 C CNN
F 1 "1.2k" V 5250 3550 50  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 5180 3550 50  0001 C CNN
F 3 "" H 5250 3550 50  0001 C CNN
	1    5250 3550
	0    1    1    0   
$EndComp
Text GLabel 5700 2950 1    60   Input ~ 0
+7V4
Text GLabel 4350 3550 0    60   Input ~ 0
GND
Text GLabel 5700 3800 3    60   Input ~ 0
+7V4_P
Wire Wire Line
	4350 3550 4650 3550
Wire Wire Line
	4950 3550 5100 3550
Connection ~ 5700 3550
$Comp
L D D7
U 1 1 5A64E1B0
P 5000 3750
F 0 "D7" H 5000 3850 50  0000 C CNN
F 1 "D" H 5000 3650 50  0000 C CNN
F 2 "Diodes_SMD:D_SMA_Handsoldering" H 5000 3750 50  0001 C CNN
F 3 "" H 5000 3750 50  0001 C CNN
	1    5000 3750
	-1   0    0    1   
$EndComp
Wire Wire Line
	4500 3550 4500 3750
Wire Wire Line
	4500 3750 4850 3750
Connection ~ 4500 3550
Wire Wire Line
	5150 3750 5550 3750
$Comp
L PWR_FLAG #FLG032
U 1 1 5A64E1BA
P 5850 3650
F 0 "#FLG032" H 5850 3725 50  0001 C CNN
F 1 "PWR_FLAG" H 5850 3800 50  0000 C CNN
F 2 "" H 5850 3650 50  0001 C CNN
F 3 "" H 5850 3650 50  0001 C CNN
	1    5850 3650
	0    1    1    0   
$EndComp
Wire Wire Line
	5700 3650 5850 3650
Connection ~ 5700 3650
Wire Wire Line
	5550 3750 5550 3550
Wire Wire Line
	5400 3550 5700 3550
Connection ~ 5550 3550
Wire Wire Line
	5700 2950 5700 3800
$Comp
L LED-RESCUE-carte_centrale D9
U 1 1 5A64E38D
P 6900 3550
F 0 "D9" H 6900 3650 50  0000 C CNN
F 1 "LED" H 6900 3450 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 6900 3550 50  0001 C CNN
F 3 "" H 6900 3550 50  0001 C CNN
	1    6900 3550
	1    0    0    -1  
$EndComp
$Comp
L R R6
U 1 1 5A64E393
P 7350 3550
F 0 "R6" V 7430 3550 50  0000 C CNN
F 1 "680" V 7350 3550 50  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 7280 3550 50  0001 C CNN
F 3 "" H 7350 3550 50  0001 C CNN
	1    7350 3550
	0    1    1    0   
$EndComp
Text GLabel 7800 2950 1    60   Input ~ 0
+5V
Text GLabel 6450 3550 0    60   Input ~ 0
GND
Text GLabel 7800 3800 3    60   Input ~ 0
+5V_P
Wire Wire Line
	6450 3550 6750 3550
Wire Wire Line
	7050 3550 7200 3550
Connection ~ 7800 3550
$Comp
L D D10
U 1 1 5A64E39F
P 7100 3750
F 0 "D10" H 7100 3850 50  0000 C CNN
F 1 "D" H 7100 3650 50  0000 C CNN
F 2 "Diodes_SMD:D_SMA_Handsoldering" H 7100 3750 50  0001 C CNN
F 3 "" H 7100 3750 50  0001 C CNN
	1    7100 3750
	-1   0    0    1   
$EndComp
Wire Wire Line
	6600 3550 6600 3750
Wire Wire Line
	6600 3750 6950 3750
Connection ~ 6600 3550
Wire Wire Line
	7250 3750 7650 3750
$Comp
L PWR_FLAG #FLG033
U 1 1 5A64E3A9
P 7950 3650
F 0 "#FLG033" H 7950 3725 50  0001 C CNN
F 1 "PWR_FLAG" H 7950 3800 50  0000 C CNN
F 2 "" H 7950 3650 50  0001 C CNN
F 3 "" H 7950 3650 50  0001 C CNN
	1    7950 3650
	0    1    1    0   
$EndComp
Wire Wire Line
	7800 3650 7950 3650
Connection ~ 7800 3650
Wire Wire Line
	7650 3750 7650 3550
Wire Wire Line
	7500 3550 7800 3550
Connection ~ 7650 3550
Wire Wire Line
	7800 2950 7800 3800
$Comp
L LED-RESCUE-carte_centrale D2
U 1 1 5AC0B956
P 2700 5250
F 0 "D2" H 2700 5350 50  0000 C CNN
F 1 "LED" H 2700 5150 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 2700 5250 50  0001 C CNN
F 3 "" H 2700 5250 50  0001 C CNN
	1    2700 5250
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 5AC0B95C
P 3150 5250
F 0 "R3" V 3230 5250 50  0000 C CNN
F 1 "1.8k" V 3150 5250 50  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 3080 5250 50  0001 C CNN
F 3 "" H 3150 5250 50  0001 C CNN
	1    3150 5250
	0    1    1    0   
$EndComp
Text GLabel 3600 4650 1    60   Input ~ 0
+12V
Text GLabel 2250 5250 0    60   Input ~ 0
GND
Text GLabel 3600 5500 3    60   Input ~ 0
+12V_P
Wire Wire Line
	2250 5250 2550 5250
Wire Wire Line
	2850 5250 3000 5250
Connection ~ 3600 5250
$Comp
L D D4
U 1 1 5AC0B968
P 2900 5450
F 0 "D4" H 2900 5550 50  0000 C CNN
F 1 "D" H 2900 5350 50  0000 C CNN
F 2 "Diodes_SMD:D_SMA_Handsoldering" H 2900 5450 50  0001 C CNN
F 3 "" H 2900 5450 50  0001 C CNN
	1    2900 5450
	-1   0    0    1   
$EndComp
Wire Wire Line
	2400 5250 2400 5450
Wire Wire Line
	2400 5450 2750 5450
Connection ~ 2400 5250
Wire Wire Line
	3050 5450 3450 5450
$Comp
L PWR_FLAG #FLG034
U 1 1 5AC0B972
P 3750 5350
F 0 "#FLG034" H 3750 5425 50  0001 C CNN
F 1 "PWR_FLAG" H 3750 5500 50  0000 C CNN
F 2 "" H 3750 5350 50  0001 C CNN
F 3 "" H 3750 5350 50  0001 C CNN
	1    3750 5350
	0    1    1    0   
$EndComp
Wire Wire Line
	3600 5350 3750 5350
Connection ~ 3600 5350
Wire Wire Line
	3450 5450 3450 5250
Wire Wire Line
	3300 5250 3600 5250
Connection ~ 3450 5250
Wire Wire Line
	3600 4650 3600 5500
$Comp
L LED-RESCUE-carte_centrale D6
U 1 1 5AC0BACD
P 4800 5250
F 0 "D6" H 4800 5350 50  0000 C CNN
F 1 "LED" H 4800 5150 50  0000 C CNN
F 2 "LEDs:LED_D5.0mm" H 4800 5250 50  0001 C CNN
F 3 "" H 4800 5250 50  0001 C CNN
	1    4800 5250
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 5AC0BAD3
P 5250 5250
F 0 "R5" V 5330 5250 50  0000 C CNN
F 1 "1.8k" V 5250 5250 50  0000 C CNN
F 2 "Resistors_SMD:R_1206_HandSoldering" V 5180 5250 50  0001 C CNN
F 3 "" H 5250 5250 50  0001 C CNN
	1    5250 5250
	0    1    1    0   
$EndComp
Text GLabel 5700 4650 1    60   Input ~ 0
+15V
Text GLabel 4350 5250 0    60   Input ~ 0
GND
Text GLabel 5700 5500 3    60   Input ~ 0
+15V_P
Wire Wire Line
	4350 5250 4650 5250
Wire Wire Line
	4950 5250 5100 5250
Connection ~ 5700 5250
$Comp
L D D8
U 1 1 5AC0BADF
P 5000 5450
F 0 "D8" H 5000 5550 50  0000 C CNN
F 1 "D" H 5000 5350 50  0000 C CNN
F 2 "Diodes_SMD:D_SMA_Handsoldering" H 5000 5450 50  0001 C CNN
F 3 "" H 5000 5450 50  0001 C CNN
	1    5000 5450
	-1   0    0    1   
$EndComp
Wire Wire Line
	4500 5250 4500 5450
Wire Wire Line
	4500 5450 4850 5450
Connection ~ 4500 5250
Wire Wire Line
	5150 5450 5550 5450
$Comp
L PWR_FLAG #FLG035
U 1 1 5AC0BAE9
P 5850 5350
F 0 "#FLG035" H 5850 5425 50  0001 C CNN
F 1 "PWR_FLAG" H 5850 5500 50  0000 C CNN
F 2 "" H 5850 5350 50  0001 C CNN
F 3 "" H 5850 5350 50  0001 C CNN
	1    5850 5350
	0    1    1    0   
$EndComp
Wire Wire Line
	5700 5350 5850 5350
Connection ~ 5700 5350
Wire Wire Line
	5550 5450 5550 5250
Wire Wire Line
	5400 5250 5700 5250
Connection ~ 5550 5250
Wire Wire Line
	5700 4650 5700 5500
$Comp
L Conn_01x02 J7
U 1 1 5ACAF90E
P 6450 3850
F 0 "J7" H 6450 3950 50  0000 C CNN
F 1 "Conn_01x02" H 6450 3650 50  0000 C CNN
F 2 "Connectors_Molex:Molex_KK-6410-02_02x2.54mm_Straight" H 6450 3850 50  0001 C CNN
F 3 "" H 6450 3850 50  0001 C CNN
	1    6450 3850
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x02 J9
U 1 1 5ACAFA14
P 8550 3900
F 0 "J9" H 8550 4000 50  0000 C CNN
F 1 "Conn_01x02" H 8550 3700 50  0000 C CNN
F 2 "Connectors_Molex:Molex_KK-6410-02_02x2.54mm_Straight" H 8550 3900 50  0001 C CNN
F 3 "" H 8550 3900 50  0001 C CNN
	1    8550 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 3750 5900 3750
Wire Wire Line
	5900 3750 5900 3850
Wire Wire Line
	5900 3850 6250 3850
Wire Wire Line
	7800 3750 8000 3750
Wire Wire Line
	8000 3750 8000 3900
Wire Wire Line
	8000 3900 8350 3900
Connection ~ 7800 3750
$Comp
L GND #PWR036
U 1 1 5ACAFB82
P 6250 3950
F 0 "#PWR036" H 6250 3700 50  0001 C CNN
F 1 "GND" H 6250 3800 50  0000 C CNN
F 2 "" H 6250 3950 50  0001 C CNN
F 3 "" H 6250 3950 50  0001 C CNN
	1    6250 3950
	0    1    -1   0   
$EndComp
$Comp
L GND #PWR037
U 1 1 5ACAFBF2
P 8350 4000
F 0 "#PWR037" H 8350 3750 50  0001 C CNN
F 1 "GND" H 8350 3850 50  0000 C CNN
F 2 "" H 8350 4000 50  0001 C CNN
F 3 "" H 8350 4000 50  0001 C CNN
	1    8350 4000
	0    1    -1   0   
$EndComp
Connection ~ 5700 3750
$Comp
L Conn_01x02 J8
U 1 1 5ACB3837
P 8100 4550
F 0 "J8" H 8100 4650 50  0000 C CNN
F 1 "Conn_01x02" V 8100 4350 50  0000 C CNN
F 2 "Connectors_Molex:Molex_KK-6410-02_02x2.54mm_Straight" H 8100 4550 50  0001 C CNN
F 3 "" H 8100 4550 50  0001 C CNN
	1    8100 4550
	0    1    1    0   
$EndComp
$Comp
L GND #PWR038
U 1 1 5ACB383D
P 8000 4350
F 0 "#PWR038" H 8000 4100 50  0001 C CNN
F 1 "GND" H 8000 4200 50  0000 C CNN
F 2 "" H 8000 4350 50  0001 C CNN
F 3 "" H 8000 4350 50  0001 C CNN
	1    8000 4350
	1    0    0    1   
$EndComp
Wire Wire Line
	8100 3900 8100 4350
Connection ~ 8100 3900
$EndSCHEMATC
