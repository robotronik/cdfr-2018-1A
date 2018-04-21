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
Sheet 3 4
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
L DSN2596 U8
U 1 1 5AC61E96
P 4000 1950
F 0 "U8" H 3700 2200 60  0000 C CNN
F 1 "DSN2596" H 3850 2300 60  0000 C CNN
F 2 "DSN:DSN2596" H 4000 1950 60  0000 C CNN
F 3 "" H 4000 1950 60  0000 C CNN
	1    4000 1950
	1    0    0    -1  
$EndComp
$Comp
L B_Plug_5mm U6
U 1 1 5AC61FAD
P 1350 1900
F 0 "U6" H 1350 2300 60  0000 C CNN
F 1 "B_Plug_5mm" H 1350 2400 60  0000 C CNN
F 2 "DSN:B plug 5mm" H 1350 1900 60  0000 C CNN
F 3 "" H 1350 1900 60  0000 C CNN
	1    1350 1900
	1    0    0    -1  
$EndComp
$Comp
L Fuse F6
U 1 1 5AC62028
P 1950 1850
F 0 "F6" V 2030 1850 50  0000 C CNN
F 1 "Fuse" V 1875 1850 50  0000 C CNN
F 2 "Fuse_Holders_and_Fuses:Fuseholder5x20_horiz_SemiClosed_Casing10x25mm" V 1880 1850 50  0001 C CNN
F 3 "" H 1950 1850 50  0001 C CNN
	1    1950 1850
	0    1    1    0   
$EndComp
$Comp
L GND #PWR039
U 1 1 5AC620F3
P 1600 2050
F 0 "#PWR039" H 1600 1800 50  0001 C CNN
F 1 "GND" H 1600 1900 50  0000 C CNN
F 2 "" H 1600 2050 50  0001 C CNN
F 3 "" H 1600 2050 50  0001 C CNN
	1    1600 2050
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG040
U 1 1 5AC62146
P 2300 1850
F 0 "#FLG040" H 2300 1925 50  0001 C CNN
F 1 "PWR_FLAG" H 2300 2000 50  0000 C CNN
F 2 "" H 2300 1850 50  0001 C CNN
F 3 "" H 2300 1850 50  0001 C CNN
	1    2300 1850
	1    0    0    -1  
$EndComp
Text GLabel 2500 2050 3    60   Input ~ 0
BATT
$Comp
L GND #PWR041
U 1 1 5AC621C7
P 3250 2150
F 0 "#PWR041" H 3250 1900 50  0001 C CNN
F 1 "GND" H 3250 2000 50  0000 C CNN
F 2 "" H 3250 2150 50  0001 C CNN
F 3 "" H 3250 2150 50  0001 C CNN
	1    3250 2150
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR042
U 1 1 5AC6235A
P 4800 2200
F 0 "#PWR042" H 4800 1950 50  0001 C CNN
F 1 "GND" H 4800 2050 50  0000 C CNN
F 2 "" H 4800 2200 50  0001 C CNN
F 3 "" H 4800 2200 50  0001 C CNN
	1    4800 2200
	1    0    0    -1  
$EndComp
$Comp
L CP C1
U 1 1 5AC62407
P 5250 2050
F 0 "C1" H 5275 2150 50  0000 L CNN
F 1 "CP" H 5275 1950 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D8.0mm_P3.50mm" H 5288 1900 50  0001 C CNN
F 3 "" H 5250 2050 50  0001 C CNN
	1    5250 2050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR043
U 1 1 5AC62460
P 5250 2350
F 0 "#PWR043" H 5250 2100 50  0001 C CNN
F 1 "GND" H 5250 2200 50  0000 C CNN
F 2 "" H 5250 2350 50  0001 C CNN
F 3 "" H 5250 2350 50  0001 C CNN
	1    5250 2350
	1    0    0    -1  
$EndComp
$Comp
L DSN2596 U9
U 1 1 5AC63DD1
P 4000 3850
F 0 "U9" H 3700 4100 60  0000 C CNN
F 1 "DSN2596" H 3850 4200 60  0000 C CNN
F 2 "DSN:DSN2596" H 4000 3850 60  0000 C CNN
F 3 "" H 4000 3850 60  0000 C CNN
	1    4000 3850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR044
U 1 1 5AC63DF7
P 3250 4050
F 0 "#PWR044" H 3250 3800 50  0001 C CNN
F 1 "GND" H 3250 3900 50  0000 C CNN
F 2 "" H 3250 4050 50  0001 C CNN
F 3 "" H 3250 4050 50  0001 C CNN
	1    3250 4050
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR045
U 1 1 5AC63DFF
P 4800 4100
F 0 "#PWR045" H 4800 3850 50  0001 C CNN
F 1 "GND" H 4800 3950 50  0000 C CNN
F 2 "" H 4800 4100 50  0001 C CNN
F 3 "" H 4800 4100 50  0001 C CNN
	1    4800 4100
	1    0    0    -1  
$EndComp
$Comp
L CP C2
U 1 1 5AC63E07
P 5250 3950
F 0 "C2" H 5275 4050 50  0000 L CNN
F 1 "CP" H 5275 3850 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D8.0mm_P3.50mm" H 5288 3800 50  0001 C CNN
F 3 "" H 5250 3950 50  0001 C CNN
	1    5250 3950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR046
U 1 1 5AC63E0F
P 5250 4250
F 0 "#PWR046" H 5250 4000 50  0001 C CNN
F 1 "GND" H 5250 4100 50  0000 C CNN
F 2 "" H 5250 4250 50  0001 C CNN
F 3 "" H 5250 4250 50  0001 C CNN
	1    5250 4250
	1    0    0    -1  
$EndComp
Text GLabel 5250 3550 1    60   Input ~ 0
+7V4
Text GLabel 5250 1600 1    60   Input ~ 0
+5V
$Comp
L DSN2596 U10
U 1 1 5AC65893
P 4000 5250
F 0 "U10" H 3700 5500 60  0000 C CNN
F 1 "DSN2596" H 3850 5600 60  0000 C CNN
F 2 "DSN:DSN2596" H 4000 5250 60  0000 C CNN
F 3 "" H 4000 5250 60  0000 C CNN
	1    4000 5250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR047
U 1 1 5AC658B9
P 3250 5450
F 0 "#PWR047" H 3250 5200 50  0001 C CNN
F 1 "GND" H 3250 5300 50  0000 C CNN
F 2 "" H 3250 5450 50  0001 C CNN
F 3 "" H 3250 5450 50  0001 C CNN
	1    3250 5450
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR048
U 1 1 5AC658C1
P 4800 5500
F 0 "#PWR048" H 4800 5250 50  0001 C CNN
F 1 "GND" H 4800 5350 50  0000 C CNN
F 2 "" H 4800 5500 50  0001 C CNN
F 3 "" H 4800 5500 50  0001 C CNN
	1    4800 5500
	1    0    0    -1  
$EndComp
$Comp
L CP C3
U 1 1 5AC658C9
P 5250 5350
F 0 "C3" H 5275 5450 50  0000 L CNN
F 1 "CP" H 5275 5250 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D8.0mm_P3.50mm" H 5288 5200 50  0001 C CNN
F 3 "" H 5250 5350 50  0001 C CNN
	1    5250 5350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR049
U 1 1 5AC658D1
P 5250 5650
F 0 "#PWR049" H 5250 5400 50  0001 C CNN
F 1 "GND" H 5250 5500 50  0000 C CNN
F 2 "" H 5250 5650 50  0001 C CNN
F 3 "" H 5250 5650 50  0001 C CNN
	1    5250 5650
	1    0    0    -1  
$EndComp
Text GLabel 5250 4950 1    60   Input ~ 0
+12V
$Comp
L GND #PWR050
U 1 1 5AC65C39
P 3250 6900
F 0 "#PWR050" H 3250 6650 50  0001 C CNN
F 1 "GND" H 3250 6750 50  0000 C CNN
F 2 "" H 3250 6900 50  0001 C CNN
F 3 "" H 3250 6900 50  0001 C CNN
	1    3250 6900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR051
U 1 1 5AC65C41
P 4800 6950
F 0 "#PWR051" H 4800 6700 50  0001 C CNN
F 1 "GND" H 4800 6800 50  0000 C CNN
F 2 "" H 4800 6950 50  0001 C CNN
F 3 "" H 4800 6950 50  0001 C CNN
	1    4800 6950
	1    0    0    -1  
$EndComp
$Comp
L CP C4
U 1 1 5AC65C49
P 5250 6800
F 0 "C4" H 5275 6900 50  0000 L CNN
F 1 "CP" H 5275 6700 50  0000 L CNN
F 2 "Capacitors_THT:CP_Radial_D8.0mm_P3.50mm" H 5288 6650 50  0001 C CNN
F 3 "" H 5250 6800 50  0001 C CNN
	1    5250 6800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR052
U 1 1 5AC65C51
P 5250 7100
F 0 "#PWR052" H 5250 6850 50  0001 C CNN
F 1 "GND" H 5250 6950 50  0000 C CNN
F 2 "" H 5250 7100 50  0001 C CNN
F 3 "" H 5250 7100 50  0001 C CNN
	1    5250 7100
	1    0    0    -1  
$EndComp
Text GLabel 5250 6400 1    60   Input ~ 0
+15V
$Comp
L B_Plug_5mm U7
U 1 1 5ACA92D8
P 3650 6700
F 0 "U7" H 3650 7100 60  0000 C CNN
F 1 "B_Plug_5mm" H 3650 7200 60  0000 C CNN
F 2 "dsn2596:B plug 5mm" H 3650 6700 60  0000 C CNN
F 3 "" H 3650 6700 60  0000 C CNN
	1    3650 6700
	-1   0    0    1   
$EndComp
$Comp
L B_Plug_5mm U11
U 1 1 5ACA93FA
P 4350 6700
F 0 "U11" H 4350 7100 60  0000 C CNN
F 1 "B_Plug_5mm" H 4350 7200 60  0000 C CNN
F 2 "dsn2596:B plug 5mm" H 4350 6700 60  0000 C CNN
F 3 "" H 4350 6700 60  0000 C CNN
	1    4350 6700
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 1950 1600 1950
Wire Wire Line
	1600 1950 1600 2050
Wire Wire Line
	1450 1850 1800 1850
Wire Wire Line
	2100 1850 3450 1850
Connection ~ 2300 1850
Wire Wire Line
	2500 2050 2500 1850
Connection ~ 2500 1850
Wire Wire Line
	3250 2150 3250 2050
Wire Wire Line
	3250 2050 3450 2050
Wire Wire Line
	4550 2050 4800 2050
Wire Wire Line
	4800 2050 4800 2200
Wire Wire Line
	4550 1850 5250 1850
Wire Wire Line
	5250 1600 5250 1900
Wire Wire Line
	5250 2200 5250 2350
Wire Wire Line
	3250 4050 3250 3950
Wire Wire Line
	3250 3950 3450 3950
Wire Wire Line
	4550 3950 4800 3950
Wire Wire Line
	4800 3950 4800 4100
Wire Wire Line
	4550 3750 5250 3750
Wire Wire Line
	5250 3550 5250 3800
Wire Wire Line
	5250 4100 5250 4250
Connection ~ 5250 3750
Connection ~ 5250 1850
Wire Wire Line
	3250 5450 3250 5350
Wire Wire Line
	3250 5350 3450 5350
Wire Wire Line
	4550 5350 4800 5350
Wire Wire Line
	4800 5350 4800 5500
Wire Wire Line
	4550 5150 5250 5150
Wire Wire Line
	5250 4950 5250 5200
Wire Wire Line
	5250 5500 5250 5650
Connection ~ 5250 5150
Wire Wire Line
	3250 6900 3250 6800
Wire Wire Line
	3250 6800 3450 6800
Wire Wire Line
	4550 6800 4800 6800
Wire Wire Line
	4800 6800 4800 6950
Wire Wire Line
	4550 6600 5250 6600
Wire Wire Line
	5250 6400 5250 6650
Wire Wire Line
	5250 6950 5250 7100
Connection ~ 5250 6600
Wire Wire Line
	3450 6600 3450 6650
Wire Wire Line
	3450 6650 3550 6650
Wire Wire Line
	3550 6750 3450 6750
Wire Wire Line
	3450 6750 3450 6800
Wire Wire Line
	4550 6600 4550 6650
Wire Wire Line
	4550 6650 4450 6650
Wire Wire Line
	4450 6750 4550 6750
Wire Wire Line
	4550 6750 4550 6800
Wire Wire Line
	2750 1850 2750 6600
Wire Wire Line
	2750 6600 3450 6600
Connection ~ 2750 1850
Wire Wire Line
	3450 5150 2750 5150
Connection ~ 2750 5150
Wire Wire Line
	3450 3750 2750 3750
Connection ~ 2750 3750
Text GLabel 1500 2250 3    60   Input ~ 0
GND
Wire Wire Line
	1500 2250 1500 1950
Connection ~ 1500 1950
$Comp
L PWR_FLAG #FLG053
U 1 1 5ACB2977
P 4900 1850
F 0 "#FLG053" H 4900 1925 50  0001 C CNN
F 1 "PWR_FLAG" H 4900 2000 50  0000 C CNN
F 2 "" H 4900 1850 50  0001 C CNN
F 3 "" H 4900 1850 50  0001 C CNN
	1    4900 1850
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG054
U 1 1 5ACB2E50
P 4950 3750
F 0 "#FLG054" H 4950 3825 50  0001 C CNN
F 1 "PWR_FLAG" H 4950 3900 50  0000 C CNN
F 2 "" H 4950 3750 50  0001 C CNN
F 3 "" H 4950 3750 50  0001 C CNN
	1    4950 3750
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG055
U 1 1 5ACB2E9D
P 4950 5150
F 0 "#FLG055" H 4950 5225 50  0001 C CNN
F 1 "PWR_FLAG" H 4950 5300 50  0000 C CNN
F 2 "" H 4950 5150 50  0001 C CNN
F 3 "" H 4950 5150 50  0001 C CNN
	1    4950 5150
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG056
U 1 1 5ACB2ED4
P 4950 6600
F 0 "#FLG056" H 4950 6675 50  0001 C CNN
F 1 "PWR_FLAG" H 4950 6750 50  0000 C CNN
F 2 "" H 4950 6600 50  0001 C CNN
F 3 "" H 4950 6600 50  0001 C CNN
	1    4950 6600
	1    0    0    -1  
$EndComp
Connection ~ 4950 6600
Connection ~ 4950 5150
Connection ~ 4950 3750
Connection ~ 4900 1850
$EndSCHEMATC