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
F 2 "Pin_Headers:Pin_Header_Straight_2x25_Pitch2.54mm" H 3250 3550 50  0001 C CNN
F 3 "~" H 3250 3550 50  0001 C CNN
	1    3250 3550
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x25_Odd_Even J2
U 1 1 5C33EFD9
P 5100 3550
F 0 "J2" H 5150 4967 50  0000 C CNN
F 1 "STM32_P2" H 5150 4876 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_2x25_Pitch2.54mm" H 5100 3550 50  0001 C CNN
F 3 "~" H 5100 3550 50  0001 C CNN
	1    5100 3550
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x16 J6
U 1 1 5C33F278
P 8200 3550
F 0 "J6" H 8279 3542 50  0000 L CNN
F 1 "Display_16x2" H 8279 3451 50  0000 L CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x16_Pitch2.54mm" H 8200 3550 50  0001 C CNN
F 3 "~" H 8200 3550 50  0001 C CNN
	1    8200 3550
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x08 J4
U 1 1 5C33F443
P 850 4050
F 0 "J4" H 770 3425 50  0000 C CNN
F 1 "Teclado" H 770 3516 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x08_Pitch2.54mm" H 850 4050 50  0001 C CNN
F 3 "~" H 850 4050 50  0001 C CNN
	1    850  4050
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J3
U 1 1 5C33F63F
P 1050 2000
F 0 "J3" H 970 1675 50  0000 C CNN
F 1 "Sensor_Golpes" H 970 1766 50  0000 C CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_bornier-3_P5.08mm" H 1050 2000 50  0001 C CNN
F 3 "~" H 1050 2000 50  0001 C CNN
	1    1050 2000
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J5
U 1 1 5C33F6D3
P 6950 2000
F 0 "J5" H 7030 2042 50  0000 L CNN
F 1 "Sensor_Unidades" H 7030 1951 50  0000 L CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_bornier-3_P5.08mm" H 6950 2000 50  0001 C CNN
F 3 "~" H 6950 2000 50  0001 C CNN
	1    6950 2000
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J7
U 1 1 5C33F7CB
P 6900 4650
F 0 "J7" H 6979 4692 50  0000 L CNN
F 1 "Lector_RFID" H 6979 4601 50  0000 L CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_bornier-3_P5.08mm" H 6900 4650 50  0001 C CNN
F 3 "~" H 6900 4650 50  0001 C CNN
	1    6900 4650
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D1
U 1 1 5C33F9B2
P 10100 2300
F 0 "D1" V 10138 2182 50  0000 R CNN
F 1 "LED_Power" V 10047 2182 50  0000 R CNN
F 2 "LEDs:LED_D5.0mm" H 10100 2300 50  0001 C CNN
F 3 "~" H 10100 2300 50  0001 C CNN
	1    10100 2300
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R1
U 1 1 5C33FB26
P 10100 2750
F 0 "R1" H 10170 2796 50  0000 L CNN
F 1 "330" H 10170 2705 50  0000 L CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 10030 2750 50  0001 C CNN
F 3 "~" H 10100 2750 50  0001 C CNN
	1    10100 2750
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 J8
U 1 1 5C34038E
P 10050 600
F 0 "J8" V 10016 412 50  0000 R CNN
F 1 "IN_Alimentación" V 9925 412 50  0000 R CNN
F 2 "Connectors_Terminal_Blocks:TerminalBlock_bornier-2_P5.08mm" H 10050 600 50  0001 C CNN
F 3 "~" H 10050 600 50  0001 C CNN
	1    10050 600 
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR01
U 1 1 5C3408C2
P 10000 1500
F 0 "#PWR01" H 10000 1250 50  0001 C CNN
F 1 "GND" H 10005 1327 50  0000 C CNN
F 2 "" H 10000 1500 50  0001 C CNN
F 3 "" H 10000 1500 50  0001 C CNN
	1    10000 1500
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR02
U 1 1 5C340901
P 10400 1500
F 0 "#PWR02" H 10400 1350 50  0001 C CNN
F 1 "+5V" H 10415 1673 50  0000 C CNN
F 2 "" H 10400 1500 50  0001 C CNN
F 3 "" H 10400 1500 50  0001 C CNN
	1    10400 1500
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR03
U 1 1 5C340B5D
P 10100 2000
F 0 "#PWR03" H 10100 1850 50  0001 C CNN
F 1 "+5V" H 10115 2173 50  0000 C CNN
F 2 "" H 10100 2000 50  0001 C CNN
F 3 "" H 10100 2000 50  0001 C CNN
	1    10100 2000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 5C340BD3
P 10100 3050
F 0 "#PWR04" H 10100 2800 50  0001 C CNN
F 1 "GND" H 10105 2877 50  0000 C CNN
F 2 "" H 10100 3050 50  0001 C CNN
F 3 "" H 10100 3050 50  0001 C CNN
	1    10100 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	10100 2000 10100 2150
Wire Wire Line
	10100 2450 10100 2600
Wire Wire Line
	10050 800  10050 850 
Wire Wire Line
	10050 850  10000 850 
Wire Wire Line
	10150 800  10150 850 
Wire Wire Line
	10150 850  10200 850 
Wire Wire Line
	10200 1600 10400 1600
Wire Wire Line
	10400 1600 10400 1500
$Comp
L Device:R R7
U 1 1 5C341751
P 6450 1800
F 0 "R7" H 6520 1846 50  0000 L CNN
F 1 "4,7k" H 6520 1755 50  0000 L CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 6380 1800 50  0001 C CNN
F 3 "~" H 6450 1800 50  0001 C CNN
	1    6450 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	6750 2000 6450 2000
Wire Wire Line
	6450 2000 6450 1950
Wire Wire Line
	6450 1650 6450 1600
Wire Wire Line
	6450 1600 6700 1600
Wire Wire Line
	6700 1600 6700 1900
Wire Wire Line
	6700 1900 6750 1900
$Comp
L power:+5V #PWR011
U 1 1 5C341FBD
P 6450 1500
F 0 "#PWR011" H 6450 1350 50  0001 C CNN
F 1 "+5V" H 6465 1673 50  0000 C CNN
F 2 "" H 6450 1500 50  0001 C CNN
F 3 "" H 6450 1500 50  0001 C CNN
	1    6450 1500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR012
U 1 1 5C341FFE
P 6450 2200
F 0 "#PWR012" H 6450 1950 50  0001 C CNN
F 1 "GND" H 6455 2027 50  0000 C CNN
F 2 "" H 6450 2200 50  0001 C CNN
F 3 "" H 6450 2200 50  0001 C CNN
	1    6450 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 1500 6450 1600
Connection ~ 6450 1600
Wire Wire Line
	6750 2100 6450 2100
Wire Wire Line
	6450 2100 6450 2200
$Comp
L Device:R R3
U 1 1 5C34337C
P 1650 1800
F 0 "R3" H 1720 1846 50  0000 L CNN
F 1 "4,7k" H 1720 1755 50  0000 L CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 1580 1800 50  0001 C CNN
F 3 "~" H 1650 1800 50  0001 C CNN
	1    1650 1800
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1650 2000 1650 1950
Wire Wire Line
	1650 1650 1650 1600
Wire Wire Line
	1650 1600 1400 1600
$Comp
L power:+5V #PWR06
U 1 1 5C343386
P 1650 1500
F 0 "#PWR06" H 1650 1350 50  0001 C CNN
F 1 "+5V" H 1665 1673 50  0000 C CNN
F 2 "" H 1650 1500 50  0001 C CNN
F 3 "" H 1650 1500 50  0001 C CNN
	1    1650 1500
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR07
U 1 1 5C34338C
P 1650 2200
F 0 "#PWR07" H 1650 1950 50  0001 C CNN
F 1 "GND" H 1655 2027 50  0000 C CNN
F 2 "" H 1650 2200 50  0001 C CNN
F 3 "" H 1650 2200 50  0001 C CNN
	1    1650 2200
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1650 1500 1650 1600
Connection ~ 1650 1600
Wire Wire Line
	1650 2100 1650 2200
Wire Wire Line
	1250 2100 1650 2100
Wire Wire Line
	1250 2000 1650 2000
Wire Wire Line
	1250 1900 1400 1900
Wire Wire Line
	1400 1900 1400 1600
$Comp
L power:GND #PWR014
U 1 1 5C345A89
P 6600 4850
F 0 "#PWR014" H 6600 4600 50  0001 C CNN
F 1 "GND" H 6605 4677 50  0000 C CNN
F 2 "" H 6600 4850 50  0001 C CNN
F 3 "" H 6600 4850 50  0001 C CNN
	1    6600 4850
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR013
U 1 1 5C345ACC
P 6600 4450
F 0 "#PWR013" H 6600 4300 50  0001 C CNN
F 1 "+5V" H 6615 4623 50  0000 C CNN
F 2 "" H 6600 4450 50  0001 C CNN
F 3 "" H 6600 4450 50  0001 C CNN
	1    6600 4450
	1    0    0    -1  
$EndComp
$Comp
L Device:R R2
U 1 1 5C346EA8
P 1300 4550
F 0 "R2" H 1370 4596 50  0000 L CNN
F 1 "4,7k" H 1370 4505 50  0000 L CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 1230 4550 50  0001 C CNN
F 3 "~" H 1300 4550 50  0001 C CNN
	1    1300 4550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R4
U 1 1 5C346F12
P 1600 4550
F 0 "R4" H 1670 4596 50  0000 L CNN
F 1 "4,7k" H 1670 4505 50  0000 L CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 1530 4550 50  0001 C CNN
F 3 "~" H 1600 4550 50  0001 C CNN
	1    1600 4550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R5
U 1 1 5C347090
P 1900 4550
F 0 "R5" H 1970 4596 50  0000 L CNN
F 1 "4,7k" H 1970 4505 50  0000 L CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 1830 4550 50  0001 C CNN
F 3 "~" H 1900 4550 50  0001 C CNN
	1    1900 4550
	1    0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 5C347096
P 2200 4550
F 0 "R6" H 2270 4596 50  0000 L CNN
F 1 "4,7k" H 2270 4505 50  0000 L CNN
F 2 "Resistors_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2130 4550 50  0001 C CNN
F 3 "~" H 2200 4550 50  0001 C CNN
	1    2200 4550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR05
U 1 1 5C34D857
P 1300 4800
F 0 "#PWR05" H 1300 4550 50  0001 C CNN
F 1 "GND" H 1305 4627 50  0000 C CNN
F 2 "" H 1300 4800 50  0001 C CNN
F 3 "" H 1300 4800 50  0001 C CNN
	1    1300 4800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR08
U 1 1 5C34D89B
P 1600 4800
F 0 "#PWR08" H 1600 4550 50  0001 C CNN
F 1 "GND" H 1605 4627 50  0000 C CNN
F 2 "" H 1600 4800 50  0001 C CNN
F 3 "" H 1600 4800 50  0001 C CNN
	1    1600 4800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR09
U 1 1 5C34D91E
P 1900 4800
F 0 "#PWR09" H 1900 4550 50  0001 C CNN
F 1 "GND" H 1905 4627 50  0000 C CNN
F 2 "" H 1900 4800 50  0001 C CNN
F 3 "" H 1900 4800 50  0001 C CNN
	1    1900 4800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR010
U 1 1 5C34D962
P 2200 4800
F 0 "#PWR010" H 2200 4550 50  0001 C CNN
F 1 "GND" H 2205 4627 50  0000 C CNN
F 2 "" H 2200 4800 50  0001 C CNN
F 3 "" H 2200 4800 50  0001 C CNN
	1    2200 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	1050 4350 1300 4350
Wire Wire Line
	1300 4350 1300 4400
Wire Wire Line
	1050 4250 1600 4250
Wire Wire Line
	1600 4250 1600 4400
Wire Wire Line
	1050 4150 1900 4150
Wire Wire Line
	1900 4150 1900 4400
Wire Wire Line
	1050 4050 2200 4050
Wire Wire Line
	2200 4050 2200 4400
Wire Wire Line
	1300 4700 1300 4800
Wire Wire Line
	1600 4700 1600 4800
Wire Wire Line
	1900 4700 1900 4800
Wire Wire Line
	2200 4700 2200 4800
Connection ~ 1300 4350
$Comp
L Device:R_POT_TRIM_US RV1
U 1 1 5C34C0C8
P 7250 3050
F 0 "RV1" H 7182 3096 50  0000 R CNN
F 1 "Display_Brillo" H 7182 3005 50  0000 R CNN
F 2 "Potentiometers:Potentiometer_Trimmer_Bourns_3266Y" H 7250 3050 50  0001 C CNN
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
	8000 2850 7800 2850
Wire Wire Line
	7800 2850 7800 3550
Wire Wire Line
	8000 2950 7700 2950
Wire Wire Line
	7700 2950 7700 2700
Wire Wire Line
	8000 3050 7400 3050
NoConn ~ 8000 3250
NoConn ~ 8000 3450
NoConn ~ 8000 3550
NoConn ~ 8000 3650
NoConn ~ 8000 3750
NoConn ~ 8000 4250
NoConn ~ 8000 4350
Wire Wire Line
	4700 2000 4700 2850
Wire Wire Line
	4700 2850 4900 2850
Wire Wire Line
	4700 2000 6450 2000
Connection ~ 6450 2000
NoConn ~ 3050 4050
NoConn ~ 3050 4150
NoConn ~ 3050 4250
NoConn ~ 3050 4350
NoConn ~ 3050 4450
NoConn ~ 3050 4550
NoConn ~ 3050 4650
NoConn ~ 3050 4750
NoConn ~ 3550 4750
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
NoConn ~ 3550 3150
NoConn ~ 3550 3050
NoConn ~ 3550 2950
NoConn ~ 3550 2850
NoConn ~ 3550 2750
NoConn ~ 3550 2650
NoConn ~ 3550 2550
NoConn ~ 3550 2450
NoConn ~ 3050 3450
NoConn ~ 3050 3150
NoConn ~ 3050 3050
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
NoConn ~ 5400 2550
NoConn ~ 5400 2450
NoConn ~ 5400 2350
NoConn ~ 4900 2750
NoConn ~ 4900 2650
NoConn ~ 4900 2550
NoConn ~ 4900 2450
NoConn ~ 4900 2350
NoConn ~ 4900 3450
NoConn ~ 4900 3350
NoConn ~ 4900 3250
NoConn ~ 4900 3150
NoConn ~ 4900 3050
NoConn ~ 4900 2950
NoConn ~ 5400 3650
Wire Wire Line
	6700 4750 6600 4750
Wire Wire Line
	6600 4750 6600 4850
Wire Wire Line
	6700 4550 6600 4550
Wire Wire Line
	6600 4550 6600 4450
Wire Wire Line
	10100 2900 10100 3050
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5C449653
P 9800 1350
F 0 "#FLG0101" H 9800 1425 50  0001 C CNN
F 1 "PWR_FLAG" H 9800 1524 50  0000 C CNN
F 2 "" H 9800 1350 50  0001 C CNN
F 3 "~" H 9800 1350 50  0001 C CNN
	1    9800 1350
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 5C449689
P 10750 1500
F 0 "#FLG0102" H 10750 1575 50  0001 C CNN
F 1 "PWR_FLAG" H 10750 1674 50  0000 C CNN
F 2 "" H 10750 1500 50  0001 C CNN
F 3 "~" H 10750 1500 50  0001 C CNN
	1    10750 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	9800 1450 10000 1450
Wire Wire Line
	9800 1350 9800 1450
Connection ~ 10000 1450
Wire Wire Line
	10000 1450 10000 1500
Wire Wire Line
	10400 1600 10750 1600
Wire Wire Line
	10750 1600 10750 1500
Connection ~ 10400 1600
Wire Wire Line
	10000 850  10000 1450
Wire Wire Line
	10200 850  10200 1600
Wire Wire Line
	2950 4350 2950 3950
Wire Wire Line
	2950 3950 3050 3950
Wire Wire Line
	1300 4350 2950 4350
Wire Wire Line
	2850 3850 3050 3850
Wire Wire Line
	1600 4250 2850 4250
Connection ~ 1600 4250
Wire Wire Line
	2850 3850 2850 4250
Wire Wire Line
	1900 4150 2750 4150
Wire Wire Line
	2750 4150 2750 3750
Wire Wire Line
	2750 3750 3050 3750
Connection ~ 1900 4150
Wire Wire Line
	2200 4050 2650 4050
Wire Wire Line
	2650 4050 2650 3650
Wire Wire Line
	2650 3650 3050 3650
Connection ~ 2200 4050
Wire Wire Line
	1050 3950 2550 3950
Wire Wire Line
	2550 3950 2550 3550
Wire Wire Line
	2550 3550 3050 3550
Wire Wire Line
	1050 3850 2450 3850
Wire Wire Line
	2450 3850 2450 3350
Wire Wire Line
	2450 3350 3050 3350
Wire Wire Line
	1050 3750 2350 3750
Wire Wire Line
	2350 3750 2350 3250
Wire Wire Line
	2350 3250 3050 3250
Wire Wire Line
	2250 3650 1050 3650
Wire Wire Line
	5400 3450 6300 3450
Wire Wire Line
	6300 3450 6300 3600
Wire Wire Line
	6300 3600 7400 3600
Wire Wire Line
	7400 3600 7400 3150
Wire Wire Line
	7400 3150 8000 3150
Wire Wire Line
	5400 3550 6200 3550
Wire Wire Line
	6200 3550 6200 3700
Wire Wire Line
	6200 3700 7500 3700
Wire Wire Line
	7500 3700 7500 3350
Wire Wire Line
	7500 3350 8000 3350
Wire Wire Line
	5400 3750 6100 3750
Wire Wire Line
	6100 3750 6100 3850
Wire Wire Line
	6100 3850 8000 3850
Wire Wire Line
	5400 4050 8000 4050
Wire Wire Line
	5400 3950 8000 3950
Wire Wire Line
	5400 4150 8000 4150
Wire Wire Line
	5400 4650 6700 4650
Wire Wire Line
	2250 2850 3050 2850
Wire Wire Line
	2250 2850 2250 3650
Wire Wire Line
	3550 3250 3700 3250
Connection ~ 1650 2000
Wire Wire Line
	1650 2000 3700 2000
Wire Wire Line
	3700 2000 3700 3250
NoConn ~ 3050 2950
NoConn ~ 3550 3550
NoConn ~ 3550 3650
NoConn ~ 3550 3750
NoConn ~ 3550 3850
NoConn ~ 4900 3750
NoConn ~ 4900 3650
NoConn ~ 4900 3550
NoConn ~ 5400 3850
$EndSCHEMATC
