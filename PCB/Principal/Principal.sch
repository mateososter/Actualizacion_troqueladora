EESchema Schematic File Version 4
LIBS:Principal-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L Connector_Generic:Conn_02x25_Odd_Even J1
U 1 1 5C33EF4F
P 3250 3550
F 0 "J1" H 3300 4967 50  0000 C CNN
F 1 "STM32_P1" H 3300 4876 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x25_P2.54mm_Vertical" H 3250 3550 50  0001 C CNN
F 3 "~" H 3250 3550 50  0001 C CNN
	1    3250 3550
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J3
U 1 1 5C33F63F
P 3300 1100
F 0 "J3" H 3220 775 50  0000 C CNN
F 1 "Sensor_Golpes" H 3220 866 50  0000 C CNN
F 2 "TerminalBlock:TerminalBlock_bornier-3_P5.08mm" H 3300 1100 50  0001 C CNN
F 3 "~" H 3300 1100 50  0001 C CNN
	1    3300 1100
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J5
U 1 1 5C33F6D3
P 4800 1100
F 0 "J5" H 4880 1142 50  0000 L CNN
F 1 "Sensor_Unidades" H 4880 1051 50  0000 L CNN
F 2 "TerminalBlock:TerminalBlock_bornier-3_P5.08mm" H 4800 1100 50  0001 C CNN
F 3 "~" H 4800 1100 50  0001 C CNN
	1    4800 1100
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D1
U 1 1 5C33F9B2
P 9150 850
F 0 "D1" V 9188 732 50  0000 R CNN
F 1 "LED_Power" V 9097 732 50  0000 R CNN
F 2 "LED_THT:LED_D5.0mm" H 9150 850 50  0001 C CNN
F 3 "~" H 9150 850 50  0001 C CNN
	1    9150 850 
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R1
U 1 1 5C33FB26
P 9150 1300
F 0 "R1" H 9220 1346 50  0000 L CNN
F 1 "680" H 9220 1255 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 9080 1300 50  0001 C CNN
F 3 "~" H 9150 1300 50  0001 C CNN
	1    9150 1300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 5C340BD3
P 9150 1600
F 0 "#PWR04" H 9150 1350 50  0001 C CNN
F 1 "GND" H 9155 1427 50  0000 C CNN
F 2 "" H 9150 1600 50  0001 C CNN
F 3 "" H 9150 1600 50  0001 C CNN
	1    9150 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	9150 1000 9150 1150
$Comp
L Device:R R7
U 1 1 5C341751
P 4300 900
F 0 "R7" H 4370 946 50  0000 L CNN
F 1 "4,7k" H 4370 855 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 4230 900 50  0001 C CNN
F 3 "~" H 4300 900 50  0001 C CNN
	1    4300 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 1100 4300 1100
Wire Wire Line
	4300 1100 4300 1050
Wire Wire Line
	4300 750  4300 700 
Wire Wire Line
	4550 1000 4600 1000
$Comp
L power:GND #PWR012
U 1 1 5C341FFE
P 4300 1300
F 0 "#PWR012" H 4300 1050 50  0001 C CNN
F 1 "GND" H 4305 1127 50  0000 C CNN
F 2 "" H 4300 1300 50  0001 C CNN
F 3 "" H 4300 1300 50  0001 C CNN
	1    4300 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 1200 4300 1200
Wire Wire Line
	4300 1200 4300 1300
$Comp
L Device:R R3
U 1 1 5C34337C
P 3900 900
F 0 "R3" H 3970 946 50  0000 L CNN
F 1 "4,7k" H 3970 855 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3830 900 50  0001 C CNN
F 3 "~" H 3900 900 50  0001 C CNN
	1    3900 900 
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3900 1100 3900 1050
$Comp
L power:GND #PWR07
U 1 1 5C34338C
P 3900 1300
F 0 "#PWR07" H 3900 1050 50  0001 C CNN
F 1 "GND" H 3905 1127 50  0000 C CNN
F 2 "" H 3900 1300 50  0001 C CNN
F 3 "" H 3900 1300 50  0001 C CNN
	1    3900 1300
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3900 1200 3900 1300
Wire Wire Line
	3500 1200 3900 1200
Wire Wire Line
	3500 1100 3900 1100
Wire Wire Line
	3500 1000 3650 1000
$Comp
L power:GND #PWR014
U 1 1 5C345A89
P 9800 3950
F 0 "#PWR014" H 9800 3700 50  0001 C CNN
F 1 "GND" H 9805 3777 50  0000 C CNN
F 2 "" H 9800 3950 50  0001 C CNN
F 3 "" H 9800 3950 50  0001 C CNN
	1    9800 3950
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5C346EA8
P 1300 4150
F 0 "R2" H 1370 4196 50  0000 L CNN
F 1 "4,7k" H 1370 4105 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 1230 4150 50  0001 C CNN
F 3 "~" H 1300 4150 50  0001 C CNN
	1    1300 4150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 5C346F12
P 1600 4150
F 0 "R4" H 1670 4196 50  0000 L CNN
F 1 "4,7k" H 1670 4105 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 1530 4150 50  0001 C CNN
F 3 "~" H 1600 4150 50  0001 C CNN
	1    1600 4150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R5
U 1 1 5C347090
P 1900 4150
F 0 "R5" H 1970 4196 50  0000 L CNN
F 1 "4,7k" H 1970 4105 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 1830 4150 50  0001 C CNN
F 3 "~" H 1900 4150 50  0001 C CNN
	1    1900 4150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 5C347096
P 2200 4150
F 0 "R6" H 2270 4196 50  0000 L CNN
F 1 "4,7k" H 2270 4105 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2130 4150 50  0001 C CNN
F 3 "~" H 2200 4150 50  0001 C CNN
	1    2200 4150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR05
U 1 1 5C34D857
P 1300 4400
F 0 "#PWR05" H 1300 4150 50  0001 C CNN
F 1 "GND" H 1305 4227 50  0000 C CNN
F 2 "" H 1300 4400 50  0001 C CNN
F 3 "" H 1300 4400 50  0001 C CNN
	1    1300 4400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR08
U 1 1 5C34D89B
P 1600 4400
F 0 "#PWR08" H 1600 4150 50  0001 C CNN
F 1 "GND" H 1605 4227 50  0000 C CNN
F 2 "" H 1600 4400 50  0001 C CNN
F 3 "" H 1600 4400 50  0001 C CNN
	1    1600 4400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR09
U 1 1 5C34D91E
P 1900 4400
F 0 "#PWR09" H 1900 4150 50  0001 C CNN
F 1 "GND" H 1905 4227 50  0000 C CNN
F 2 "" H 1900 4400 50  0001 C CNN
F 3 "" H 1900 4400 50  0001 C CNN
	1    1900 4400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR010
U 1 1 5C34D962
P 2200 4400
F 0 "#PWR010" H 2200 4150 50  0001 C CNN
F 1 "GND" H 2205 4227 50  0000 C CNN
F 2 "" H 2200 4400 50  0001 C CNN
F 3 "" H 2200 4400 50  0001 C CNN
	1    2200 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 3950 1300 4000
Wire Wire Line
	1600 3850 1600 4000
Wire Wire Line
	1900 3750 1900 4000
Wire Wire Line
	2200 3650 2200 4000
Wire Wire Line
	1300 4300 1300 4400
Wire Wire Line
	1600 4300 1600 4400
Wire Wire Line
	1900 4300 1900 4400
Wire Wire Line
	2200 4300 2200 4400
$Comp
L Device:R_POT_TRIM_US RV1
U 1 1 5C34C0C8
P 7250 3050
F 0 "RV1" H 7182 3096 50  0000 R CNN
F 1 "Display_Brillo" H 7182 3005 50  0000 R CNN
F 2 "Potentiometer_THT:Potentiometer_Bourns_3266Y_Vertical" H 7250 3050 50  0001 C CNN
F 3 "~" H 7250 3050 50  0001 C CNN
	1    7250 3050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR017
U 1 1 5C34C1B3
P 7800 3550
F 0 "#PWR017" H 7800 3300 50  0001 C CNN
F 1 "GND" H 7805 3377 50  0000 C CNN
F 2 "" H 7800 3550 50  0001 C CNN
F 3 "" H 7800 3550 50  0001 C CNN
	1    7800 3550
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR018
U 1 1 5C34C2B7
P 7700 2700
F 0 "#PWR018" H 7700 2550 50  0001 C CNN
F 1 "+5V" H 7715 2873 50  0000 C CNN
F 2 "" H 7700 2700 50  0001 C CNN
F 3 "" H 7700 2700 50  0001 C CNN
	1    7700 2700
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR015
U 1 1 5C34C3B1
P 7250 2800
F 0 "#PWR015" H 7250 2650 50  0001 C CNN
F 1 "+5V" H 7265 2973 50  0000 C CNN
F 2 "" H 7250 2800 50  0001 C CNN
F 3 "" H 7250 2800 50  0001 C CNN
	1    7250 2800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR016
U 1 1 5C34C404
P 7250 3300
F 0 "#PWR016" H 7250 3050 50  0001 C CNN
F 1 "GND" H 7255 3127 50  0000 C CNN
F 2 "" H 7250 3300 50  0001 C CNN
F 3 "" H 7250 3300 50  0001 C CNN
	1    7250 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 2800 7250 2900
Wire Wire Line
	7250 3200 7250 3300
Wire Wire Line
	7800 2850 7800 3550
Wire Wire Line
	7700 2950 7700 2700
NoConn ~ 8000 3250
NoConn ~ 8000 3450
NoConn ~ 8000 3550
NoConn ~ 8000 3650
NoConn ~ 8000 3750
NoConn ~ 8000 4250
NoConn ~ 8000 4350
NoConn ~ 3050 4050
NoConn ~ 3050 4550
NoConn ~ 3050 4650
NoConn ~ 3550 4650
NoConn ~ 3550 4550
NoConn ~ 3550 4450
NoConn ~ 3550 4350
NoConn ~ 3550 4250
NoConn ~ 3550 4150
NoConn ~ 3550 4050
NoConn ~ 3550 3950
NoConn ~ 3550 3450
NoConn ~ 3550 3350
NoConn ~ 5400 4750
NoConn ~ 3550 2350
NoConn ~ 3550 2950
NoConn ~ 3550 2850
NoConn ~ 3550 2750
NoConn ~ 3550 2650
NoConn ~ 3550 2550
NoConn ~ 3550 2450
NoConn ~ 3050 3450
NoConn ~ 3050 2750
NoConn ~ 3050 2650
NoConn ~ 3050 2550
NoConn ~ 3050 2450
NoConn ~ 3050 2350
NoConn ~ 5400 4550
NoConn ~ 5400 4450
NoConn ~ 5400 4350
NoConn ~ 5400 4250
NoConn ~ 4900 4550
NoConn ~ 4900 4450
NoConn ~ 4900 4350
NoConn ~ 4900 4250
NoConn ~ 4900 4150
NoConn ~ 4900 4050
NoConn ~ 4900 3950
NoConn ~ 4900 3850
NoConn ~ 4900 4750
NoConn ~ 4900 4650
NoConn ~ 5400 3350
NoConn ~ 5400 3250
NoConn ~ 5400 3150
NoConn ~ 5400 3050
NoConn ~ 5400 2950
NoConn ~ 5400 2850
NoConn ~ 5400 2750
NoConn ~ 5400 2650
NoConn ~ 4900 2750
NoConn ~ 4900 2650
NoConn ~ 4900 3450
NoConn ~ 4900 3350
NoConn ~ 4900 3250
NoConn ~ 4900 3150
NoConn ~ 4900 3050
NoConn ~ 4900 2950
NoConn ~ 5400 3650
Wire Wire Line
	9150 1450 9150 1600
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5C449653
P 10950 1000
F 0 "#FLG0101" H 10950 1075 50  0001 C CNN
F 1 "PWR_FLAG" H 10950 1174 50  0000 C CNN
F 2 "" H 10950 1000 50  0001 C CNN
F 3 "~" H 10950 1000 50  0001 C CNN
	1    10950 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2450 3350 3050 3350
Wire Wire Line
	2350 3250 3050 3250
Wire Wire Line
	5400 3450 6300 3450
Wire Wire Line
	6300 3450 6300 3600
Wire Wire Line
	6300 3600 7400 3600
Wire Wire Line
	7400 3600 7400 3150
Wire Wire Line
	5400 3550 6200 3550
Wire Wire Line
	6200 3550 6200 3700
Wire Wire Line
	6200 3700 7500 3700
Wire Wire Line
	7500 3700 7500 3350
Wire Wire Line
	5400 3750 6100 3750
Wire Wire Line
	6100 3750 6100 3850
Wire Wire Line
	2250 2850 3050 2850
NoConn ~ 3050 2950
NoConn ~ 3550 3550
NoConn ~ 3550 3650
NoConn ~ 3550 3750
NoConn ~ 3550 3850
NoConn ~ 4900 3750
NoConn ~ 4900 3650
NoConn ~ 4900 3550
NoConn ~ 5400 3850
Wire Wire Line
	3550 3250 4100 3250
Text GLabel 3850 3050 2    50   Input ~ 0
PA4
Text GLabel 2850 3050 0    50   Input ~ 0
PA5
Text GLabel 2850 3150 0    50   Input ~ 0
PA7
Text GLabel 3850 3150 2    50   Input ~ 0
PA6
Wire Wire Line
	3850 3050 3550 3050
Wire Wire Line
	3550 3150 3850 3150
Wire Wire Line
	3050 3150 2850 3150
Wire Wire Line
	2850 3050 3050 3050
$Comp
L Connector_Generic:Conn_02x25_Odd_Even J2
U 1 1 5C33EFD9
P 5100 3550
F 0 "J2" H 5150 4967 50  0000 C CNN
F 1 "STM32_P2" H 5150 4876 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x25_P2.54mm_Vertical" H 5100 3550 50  0001 C CNN
F 3 "~" H 5100 3550 50  0001 C CNN
	1    5100 3550
	1    0    0    -1  
$EndComp
Text GLabel 5600 2450 2    50   Input ~ 0
5V
Text GLabel 4700 2450 0    50   Input ~ 0
5V
Wire Wire Line
	4200 2850 4900 2850
Wire Wire Line
	5400 2450 5600 2450
Wire Wire Line
	4900 2450 4700 2450
Wire Wire Line
	4300 1100 4200 1100
Wire Wire Line
	4200 1100 4200 2850
Connection ~ 4300 1100
Wire Wire Line
	4100 1100 3900 1100
Wire Wire Line
	4100 1100 4100 3250
Connection ~ 3900 1100
$Comp
L Regulator_Linear:LM7805_TO220 U1
U 1 1 5DA02D20
P 1550 800
F 0 "U1" H 1550 1042 50  0000 C CNN
F 1 "LM7805" H 1550 951 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 1550 1025 50  0001 C CIN
F 3 "http://www.fairchildsemi.com/ds/LM/LM7805.pdf" H 1550 750 50  0001 C CNN
	1    1550 800 
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J4
U 1 1 5DA03262
P 650 900
F 0 "J4" H 570 575 50  0000 C CNN
F 1 "Fuente" H 570 666 50  0000 C CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 650 900 50  0001 C CNN
F 3 "~" H 650 900 50  0001 C CNN
	1    650  900 
	-1   0    0    1   
$EndComp
Wire Wire Line
	850  800  950  800 
Wire Wire Line
	850  900  900  900 
Text GLabel 4700 2350 0    50   Input ~ 0
GND
Text GLabel 5600 2350 2    50   Input ~ 0
GND
Wire Wire Line
	5600 2350 5400 2350
Wire Wire Line
	4900 2350 4700 2350
Text GLabel 2100 1200 2    50   Input ~ 0
GND
Text GLabel 2100 800  2    50   Input ~ 0
5V
Wire Wire Line
	2100 800  2000 800 
$Comp
L Device:C C1
U 1 1 5DA1E14B
P 1150 1000
F 0 "C1" H 1265 1046 50  0000 L CNN
F 1 "330n" H 1265 955 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D7.5mm_W2.5mm_P5.00mm" H 1188 850 50  0001 C CNN
F 3 "~" H 1150 1000 50  0001 C CNN
	1    1150 1000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C2
U 1 1 5DA1E1CD
P 2000 1000
F 0 "C2" H 2115 1046 50  0000 L CNN
F 1 "100n" H 2115 955 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D7.5mm_W2.5mm_P5.00mm" H 2038 850 50  0001 C CNN
F 3 "~" H 2000 1000 50  0001 C CNN
	1    2000 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	2100 1200 2000 1200
Wire Wire Line
	900  900  900  1200
Wire Wire Line
	1150 1150 1150 1200
Connection ~ 1150 1200
Wire Wire Line
	1150 1200 900  1200
Wire Wire Line
	1550 1100 1550 1200
Connection ~ 1550 1200
Wire Wire Line
	1550 1200 1150 1200
Wire Wire Line
	2000 1150 2000 1200
Connection ~ 2000 1200
Wire Wire Line
	2000 1200 1550 1200
Wire Wire Line
	2000 850  2000 800 
Connection ~ 2000 800 
Wire Wire Line
	2000 800  1850 800 
Wire Wire Line
	1150 850  1150 800 
Connection ~ 1150 800 
Wire Wire Line
	1150 800  1250 800 
Text GLabel 5600 2550 2    50   Input ~ 0
3V
Wire Wire Line
	5400 2550 5600 2550
Text GLabel 4700 2550 0    50   Input ~ 0
3V
Wire Wire Line
	4900 2550 4700 2550
Text GLabel 10100 4050 0    50   Input ~ 0
3V
Wire Wire Line
	10200 3950 10200 4050
Connection ~ 10200 4050
Wire Wire Line
	10200 4050 10100 4050
Wire Wire Line
	9800 3850 9800 3950
NoConn ~ 10300 3750
NoConn ~ 5400 4650
Text GLabel 10550 1050 0    50   Input ~ 0
GND
$Comp
L power:GND #PWR02
U 1 1 5DA6CF23
P 10650 1100
F 0 "#PWR02" H 10650 850 50  0001 C CNN
F 1 "GND" H 10655 927 50  0000 C CNN
F 2 "" H 10650 1100 50  0001 C CNN
F 3 "" H 10650 1100 50  0001 C CNN
	1    10650 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	10550 1050 10650 1050
Wire Wire Line
	10650 1050 10650 1100
Text GLabel 10100 3650 0    50   Input ~ 0
PA6
Text GLabel 10100 3550 0    50   Input ~ 0
PA7
Text GLabel 10100 3450 0    50   Input ~ 0
PA5
Text GLabel 10100 3350 0    50   Input ~ 0
PA4
$Comp
L power:+5V #PWR01
U 1 1 5DA86FA2
P 10650 750
F 0 "#PWR01" H 10650 600 50  0001 C CNN
F 1 "+5V" H 10665 923 50  0000 C CNN
F 2 "" H 10650 750 50  0001 C CNN
F 3 "" H 10650 750 50  0001 C CNN
	1    10650 750 
	1    0    0    -1  
$EndComp
Text GLabel 10550 850  0    50   Input ~ 0
5V
Wire Wire Line
	10650 750  10650 850 
Wire Wire Line
	10650 850  10550 850 
Wire Wire Line
	1150 800  1150 500 
Text Label 3650 600  0    50   ~ 0
9V
Text GLabel 4100 650  1    50   Input ~ 0
5V
Wire Wire Line
	3900 700  3900 750 
Wire Wire Line
	3650 500  3650 1000
Wire Wire Line
	4550 500  4550 1000
Wire Wire Line
	3900 700  4100 700 
Wire Wire Line
	4100 700  4100 650 
Connection ~ 4100 700 
Wire Wire Line
	4100 700  4300 700 
Wire Wire Line
	10950 1000 10950 1050
Wire Wire Line
	10950 1050 10650 1050
Connection ~ 10650 1050
$Comp
L power:PWR_FLAG #FLG01
U 1 1 5DAD8E39
P 950 700
F 0 "#FLG01" H 950 775 50  0001 C CNN
F 1 "PWR_FLAG" H 950 874 50  0000 C CNN
F 2 "" H 950 700 50  0001 C CNN
F 3 "~" H 950 700 50  0001 C CNN
	1    950  700 
	1    0    0    -1  
$EndComp
Wire Wire Line
	950  700  950  800 
Connection ~ 950  800 
Wire Wire Line
	950  800  1050 800 
NoConn ~ 10800 3750
Wire Wire Line
	9150 500  9150 700 
Wire Wire Line
	4550 500  9150 500 
Wire Wire Line
	1150 500  3650 500 
Wire Wire Line
	3650 500  4550 500 
Connection ~ 3650 500 
Connection ~ 4550 500 
NoConn ~ 8000 4450
NoConn ~ 8000 4550
NoConn ~ 8000 4650
NoConn ~ 8000 4750
NoConn ~ 8500 4750
NoConn ~ 8500 4650
NoConn ~ 8500 4550
NoConn ~ 8500 4450
NoConn ~ 8500 4350
NoConn ~ 8500 4250
NoConn ~ 8500 3750
NoConn ~ 8500 3650
NoConn ~ 8500 3550
NoConn ~ 8500 3450
NoConn ~ 8500 3250
$Comp
L Connector:Jack-DC J9
U 1 1 5DB7E28E
P 700 1500
F 0 "J9" H 755 1825 50  0000 C CNN
F 1 "Jack-DC" H 755 1734 50  0000 C CNN
F 2 "Connector_BarrelJack:BarrelJack_Horizontal" H 750 1460 50  0001 C CNN
F 3 "~" H 750 1460 50  0001 C CNN
	1    700  1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	1050 800  1050 1400
Wire Wire Line
	1050 1400 1000 1400
Connection ~ 1050 800 
Wire Wire Line
	1050 800  1150 800 
Wire Wire Line
	1150 1200 1150 1600
Wire Wire Line
	1150 1600 1000 1600
Wire Wire Line
	2250 2850 2250 3250
Wire Wire Line
	2350 3350 2350 3250
Wire Wire Line
	2450 3450 2450 3350
Wire Wire Line
	2200 3650 3050 3650
Wire Wire Line
	1900 3750 3050 3750
Wire Wire Line
	1600 3850 3050 3850
Wire Wire Line
	1300 3950 3050 3950
$Comp
L Device:R R8
U 1 1 5DA1FF99
P 1300 5150
F 0 "R8" H 1370 5196 50  0000 L CNN
F 1 "4,7k" H 1370 5105 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 1230 5150 50  0001 C CNN
F 3 "~" H 1300 5150 50  0001 C CNN
	1    1300 5150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R9
U 1 1 5DA1FF9F
P 1600 5150
F 0 "R9" H 1670 5196 50  0000 L CNN
F 1 "4,7k" H 1670 5105 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 1530 5150 50  0001 C CNN
F 3 "~" H 1600 5150 50  0001 C CNN
	1    1600 5150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R10
U 1 1 5DA1FFA5
P 1900 5150
F 0 "R10" H 1970 5196 50  0000 L CNN
F 1 "4,7k" H 1970 5105 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 1830 5150 50  0001 C CNN
F 3 "~" H 1900 5150 50  0001 C CNN
	1    1900 5150
	1    0    0    -1  
$EndComp
$Comp
L Device:R R11
U 1 1 5DA1FFAB
P 2200 5150
F 0 "R11" H 2270 5196 50  0000 L CNN
F 1 "4,7k" H 2270 5105 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2130 5150 50  0001 C CNN
F 3 "~" H 2200 5150 50  0001 C CNN
	1    2200 5150
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR03
U 1 1 5DA271C9
P 1300 4900
F 0 "#PWR03" H 1300 4750 50  0001 C CNN
F 1 "+5V" H 1315 5073 50  0000 C CNN
F 2 "" H 1300 4900 50  0001 C CNN
F 3 "" H 1300 4900 50  0001 C CNN
	1    1300 4900
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR06
U 1 1 5DA27283
P 1600 4900
F 0 "#PWR06" H 1600 4750 50  0001 C CNN
F 1 "+5V" H 1615 5073 50  0000 C CNN
F 2 "" H 1600 4900 50  0001 C CNN
F 3 "" H 1600 4900 50  0001 C CNN
	1    1600 4900
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR011
U 1 1 5DA272C0
P 1900 4900
F 0 "#PWR011" H 1900 4750 50  0001 C CNN
F 1 "+5V" H 1915 5073 50  0000 C CNN
F 2 "" H 1900 4900 50  0001 C CNN
F 3 "" H 1900 4900 50  0001 C CNN
	1    1900 4900
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR013
U 1 1 5DA272FD
P 2200 4900
F 0 "#PWR013" H 2200 4750 50  0001 C CNN
F 1 "+5V" H 2215 5073 50  0000 C CNN
F 2 "" H 2200 4900 50  0001 C CNN
F 3 "" H 2200 4900 50  0001 C CNN
	1    2200 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 4900 1300 5000
Wire Wire Line
	1600 4900 1600 5000
Wire Wire Line
	1900 4900 1900 5000
Wire Wire Line
	2200 4900 2200 5000
Wire Wire Line
	3050 4450 2950 4450
Wire Wire Line
	2950 4450 2950 5850
Wire Wire Line
	2950 5850 1300 5850
Wire Wire Line
	1300 5850 1300 5300
Wire Wire Line
	1600 5300 1600 5750
Wire Wire Line
	1600 5750 2850 5750
Wire Wire Line
	2850 5750 2850 4350
Wire Wire Line
	2850 4350 3050 4350
Wire Wire Line
	3050 4250 2750 4250
Wire Wire Line
	2750 4250 2750 5650
Wire Wire Line
	2750 5650 1900 5650
Wire Wire Line
	1900 5650 1900 5300
Wire Wire Line
	2200 5300 2200 5550
Wire Wire Line
	2200 5550 2650 5550
Wire Wire Line
	2650 5550 2650 4150
Wire Wire Line
	2650 4150 3050 4150
$Comp
L Switch:SW_SPST SW1
U 1 1 5DA65CB3
P 1300 6250
F 0 "SW1" V 1254 6348 50  0000 L CNN
F 1 "InputPullUp1" V 1345 6348 50  0000 L CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 1300 6250 50  0001 C CNN
F 3 "" H 1300 6250 50  0001 C CNN
	1    1300 6250
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_SPST SW2
U 1 1 5DA65E0C
P 1600 6250
F 0 "SW2" V 1554 6348 50  0000 L CNN
F 1 "InputPullUp2" V 1645 6348 50  0000 L CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 1600 6250 50  0001 C CNN
F 3 "" H 1600 6250 50  0001 C CNN
	1    1600 6250
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_SPST SW3
U 1 1 5DA65E5A
P 1900 6250
F 0 "SW3" V 1854 6348 50  0000 L CNN
F 1 "InputPullUp3" V 1945 6348 50  0000 L CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 1900 6250 50  0001 C CNN
F 3 "" H 1900 6250 50  0001 C CNN
	1    1900 6250
	0    1    1    0   
$EndComp
$Comp
L Switch:SW_SPST SW4
U 1 1 5DA65EAA
P 2200 6250
F 0 "SW4" V 2154 6348 50  0000 L CNN
F 1 "InputPullUp4" V 2245 6348 50  0000 L CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 2200 6250 50  0001 C CNN
F 3 "" H 2200 6250 50  0001 C CNN
	1    2200 6250
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR019
U 1 1 5DA660CC
P 1300 6700
F 0 "#PWR019" H 1300 6450 50  0001 C CNN
F 1 "GND" H 1305 6527 50  0000 C CNN
F 2 "" H 1300 6700 50  0001 C CNN
F 3 "" H 1300 6700 50  0001 C CNN
	1    1300 6700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR020
U 1 1 5DA660D2
P 1600 6700
F 0 "#PWR020" H 1600 6450 50  0001 C CNN
F 1 "GND" H 1605 6527 50  0000 C CNN
F 2 "" H 1600 6700 50  0001 C CNN
F 3 "" H 1600 6700 50  0001 C CNN
	1    1600 6700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR021
U 1 1 5DA660D8
P 1900 6700
F 0 "#PWR021" H 1900 6450 50  0001 C CNN
F 1 "GND" H 1905 6527 50  0000 C CNN
F 2 "" H 1900 6700 50  0001 C CNN
F 3 "" H 1900 6700 50  0001 C CNN
	1    1900 6700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR022
U 1 1 5DA660DE
P 2200 6700
F 0 "#PWR022" H 2200 6450 50  0001 C CNN
F 1 "GND" H 2205 6527 50  0000 C CNN
F 2 "" H 2200 6700 50  0001 C CNN
F 3 "" H 2200 6700 50  0001 C CNN
	1    2200 6700
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 5850 1300 6050
Connection ~ 1300 5850
Wire Wire Line
	1600 6050 1600 5750
Connection ~ 1600 5750
Wire Wire Line
	1900 5650 1900 6050
Connection ~ 1900 5650
Wire Wire Line
	2200 6050 2200 5550
Connection ~ 2200 5550
Wire Wire Line
	1300 6450 1300 6700
Wire Wire Line
	1600 6450 1600 6700
Wire Wire Line
	1900 6450 1900 6700
Wire Wire Line
	2200 6450 2200 6700
$Comp
L Connector_Generic:Conn_02x20_Odd_Even J7
U 1 1 5DAD101C
P 8200 3750
F 0 "J7" H 8250 4867 50  0000 C CNN
F 1 "Conn_Display" H 8250 4776 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x20_P2.54mm_Vertical" H 8200 3750 50  0001 C CNN
F 3 "~" H 8200 3750 50  0001 C CNN
	1    8200 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7800 2850 8000 2850
Wire Wire Line
	6100 3850 8000 3850
Wire Wire Line
	5400 3950 8000 3950
Wire Wire Line
	5400 4050 8000 4050
Wire Wire Line
	5400 4150 8000 4150
Wire Wire Line
	7700 2950 8000 2950
Wire Wire Line
	7400 3050 8000 3050
Wire Wire Line
	7400 3150 8000 3150
Wire Wire Line
	7500 3350 8000 3350
Wire Wire Line
	8500 2850 8000 2850
Connection ~ 8000 2850
Wire Wire Line
	8000 2950 8500 2950
Connection ~ 8000 2950
Wire Wire Line
	8500 3050 8000 3050
Connection ~ 8000 3050
Wire Wire Line
	8000 3150 8500 3150
Connection ~ 8000 3150
Wire Wire Line
	8500 3350 8000 3350
Connection ~ 8000 3350
Wire Wire Line
	8000 3850 8500 3850
Connection ~ 8000 3850
Wire Wire Line
	8000 3950 8500 3950
Connection ~ 8000 3950
Wire Wire Line
	8500 4050 8000 4050
Connection ~ 8000 4050
Wire Wire Line
	8000 4150 8500 4150
Connection ~ 8000 4150
Wire Wire Line
	550  3950 1050 3950
Wire Wire Line
	550  3850 1050 3850
Wire Wire Line
	550  3750 1050 3750
Wire Wire Line
	550  3450 1050 3450
Wire Wire Line
	550  3350 1050 3350
Wire Wire Line
	550  3250 1050 3250
$Comp
L Connector_Generic:Conn_02x08_Odd_Even J6
U 1 1 5DB2532C
P 850 3650
F 0 "J6" H 900 3025 50  0000 C CNN
F 1 "Conn_Teclado" H 900 3116 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x08_P2.54mm_Vertical" H 850 3650 50  0001 C CNN
F 3 "~" H 850 3650 50  0001 C CNN
	1    850  3650
	-1   0    0    1   
$EndComp
Wire Wire Line
	1050 3550 3050 3550
Wire Wire Line
	2250 3250 1050 3250
Connection ~ 1050 3250
Wire Wire Line
	1050 3350 2350 3350
Connection ~ 1050 3350
Wire Wire Line
	2450 3450 1050 3450
Connection ~ 1050 3450
Wire Wire Line
	1050 3650 2200 3650
Connection ~ 2200 3650
Wire Wire Line
	1900 3750 1050 3750
Connection ~ 1900 3750
Connection ~ 1050 3750
Wire Wire Line
	1050 3850 1600 3850
Connection ~ 1050 3850
Connection ~ 1600 3850
Wire Wire Line
	1300 3950 1050 3950
Connection ~ 1300 3950
Connection ~ 1050 3950
Wire Wire Line
	550  3550 1050 3550
Connection ~ 1050 3550
Wire Wire Line
	550  3650 1050 3650
Connection ~ 1050 3650
$Comp
L Connector_Generic:Conn_02x08_Odd_Even J8
U 1 1 5DBA325F
P 10500 3650
F 0 "J8" H 10550 4167 50  0000 C CNN
F 1 "Conn_RFID" H 10550 4076 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x08_P2.54mm_Vertical" H 10500 3650 50  0001 C CNN
F 3 "~" H 10500 3650 50  0001 C CNN
	1    10500 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	10100 3350 10300 3350
Wire Wire Line
	10100 3450 10300 3450
Wire Wire Line
	10100 3550 10300 3550
Wire Wire Line
	10100 3650 10300 3650
Wire Wire Line
	9800 3850 10300 3850
Wire Wire Line
	10200 3950 10300 3950
Wire Wire Line
	10200 4050 10300 4050
Wire Wire Line
	10800 3350 10300 3350
Connection ~ 10300 3350
Wire Wire Line
	10300 3450 10800 3450
Connection ~ 10300 3450
Wire Wire Line
	10800 3550 10300 3550
Connection ~ 10300 3550
Wire Wire Line
	10300 3650 10800 3650
Connection ~ 10300 3650
Wire Wire Line
	10800 3850 10300 3850
Connection ~ 10300 3850
Wire Wire Line
	10300 3950 10800 3950
Connection ~ 10300 3950
Wire Wire Line
	10800 4050 10300 4050
Connection ~ 10300 4050
NoConn ~ 3550 4750
NoConn ~ 3050 4750
$EndSCHEMATC
