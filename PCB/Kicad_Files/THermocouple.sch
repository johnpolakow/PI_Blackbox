EESchema Schematic File Version 4
LIBS:Pi_Blackbox-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 3
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
L Sensor:LTC2990 U?
U 1 1 5CC2E7A4
P 8200 2600
AR Path="/5CC2E7A4" Ref="U?"  Part="1" 
AR Path="/5CC2E26B/5CC2E7A4" Ref="U?"  Part="1" 
F 0 "U?" H 8200 2750 50  0000 C CNN
F 1 "LTC2990" H 8200 2600 50  0000 C CNN
F 2 "Package_SO:MSOP-10_3x3mm_P0.5mm" H 8200 2600 50  0001 C CNN
F 3 "http://cds.linear.com/docs/en/datasheet/2990fe.pdf" H 7600 3100 50  0001 C CNN
	1    8200 2600
	-1   0    0    -1  
$EndComp
$Comp
L Sensor:LTC2990 U?
U 1 1 5CC2E7AB
P 8200 4350
AR Path="/5CC2E7AB" Ref="U?"  Part="1" 
AR Path="/5CC2E26B/5CC2E7AB" Ref="U?"  Part="1" 
F 0 "U?" H 8200 4500 50  0000 C CNN
F 1 "LTC2990" H 8200 4350 50  0000 C CNN
F 2 "Package_SO:MSOP-10_3x3mm_P0.5mm" H 8200 4350 50  0001 C CNN
F 3 "http://cds.linear.com/docs/en/datasheet/2990fe.pdf" H 7600 4850 50  0001 C CNN
	1    8200 4350
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8200 5000 8200 4950
Wire Wire Line
	7600 4550 7500 4550
Wire Wire Line
	7500 4550 7500 4600
Wire Wire Line
	7500 4650 7600 4650
Wire Wire Line
	7500 4600 7450 4600
Wire Wire Line
	7450 4600 7450 5000
Wire Wire Line
	7450 5000 7850 5000
Connection ~ 7500 4600
Wire Wire Line
	7500 4600 7500 4650
$Comp
L Device:R_Small_US R?
U 1 1 5CC2E7BB
P 6850 4150
AR Path="/5CC2E7BB" Ref="R?"  Part="1" 
AR Path="/5CC2E26B/5CC2E7BB" Ref="R?"  Part="1" 
F 0 "R?" V 6645 4150 50  0000 C CNN
F 1 "20R" V 6736 4150 50  0000 C CNN
F 2 "" H 6850 4150 50  0001 C CNN
F 3 "~" H 6850 4150 50  0001 C CNN
	1    6850 4150
	0    -1   1    0   
$EndComp
$Comp
L Device:R_Small_US R?
U 1 1 5CC2E7C2
P 6850 4450
AR Path="/5CC2E7C2" Ref="R?"  Part="1" 
AR Path="/5CC2E26B/5CC2E7C2" Ref="R?"  Part="1" 
F 0 "R?" V 6750 4450 50  0000 C CNN
F 1 "20R" V 6950 4450 50  0000 C CNN
F 2 "" H 6850 4450 50  0001 C CNN
F 3 "~" H 6850 4450 50  0001 C CNN
	1    6850 4450
	0    -1   1    0   
$EndComp
Wire Wire Line
	7600 4250 7250 4250
Wire Wire Line
	7250 4250 7250 4150
Wire Wire Line
	7600 4350 7250 4350
Wire Wire Line
	7250 4350 7250 4450
Text Label 7550 4250 2    50   ~ 0
U5_SDA
Text Label 7550 4350 2    50   ~ 0
U5_SCL
$Comp
L Device:R_Small_US R?
U 1 1 5CC2E7D1
P 6900 2400
AR Path="/5CC2E7D1" Ref="R?"  Part="1" 
AR Path="/5CC2E26B/5CC2E7D1" Ref="R?"  Part="1" 
F 0 "R?" V 6695 2400 50  0000 C CNN
F 1 "20R" V 6786 2400 50  0000 C CNN
F 2 "" H 6900 2400 50  0001 C CNN
F 3 "~" H 6900 2400 50  0001 C CNN
	1    6900 2400
	0    -1   1    0   
$EndComp
$Comp
L Device:R_Small_US R?
U 1 1 5CC2E7D8
P 6900 2700
AR Path="/5CC2E7D8" Ref="R?"  Part="1" 
AR Path="/5CC2E26B/5CC2E7D8" Ref="R?"  Part="1" 
F 0 "R?" V 6800 2700 50  0000 C CNN
F 1 "20R" V 7000 2700 50  0000 C CNN
F 2 "" H 6900 2700 50  0001 C CNN
F 3 "~" H 6900 2700 50  0001 C CNN
	1    6900 2700
	0    -1   1    0   
$EndComp
Wire Wire Line
	7600 2500 7250 2500
Wire Wire Line
	7250 2500 7250 2400
Wire Wire Line
	7600 2600 7250 2600
Wire Wire Line
	7250 2600 7250 2700
Text Label 7550 2500 2    50   ~ 0
U4_SDA
Text Label 7550 2600 2    50   ~ 0
U4_SCL
Wire Wire Line
	8200 2000 8200 1600
$Comp
L Transistor_BJT:2N3904 Q?
U 1 1 5CC2E7EC
P 9450 1800
AR Path="/5CC2E7EC" Ref="Q?"  Part="1" 
AR Path="/5CC2E26B/5CC2E7EC" Ref="Q?"  Part="1" 
F 0 "Q?" H 9641 1846 50  0000 L CNN
F 1 "2N2222" H 9641 1755 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 9650 1725 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N3904.pdf" H 9450 1800 50  0001 L CNN
	1    9450 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	9250 1800 9250 1600
Connection ~ 9250 1600
Wire Wire Line
	9250 1600 9550 1600
$Comp
L Transistor_BJT:2N3904 Q?
U 1 1 5CC2E7F8
P 9450 2600
AR Path="/5CC2E7F8" Ref="Q?"  Part="1" 
AR Path="/5CC2E26B/5CC2E7F8" Ref="Q?"  Part="1" 
F 0 "Q?" H 9641 2646 50  0000 L CNN
F 1 "2N2222" H 9641 2555 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 9650 2525 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N3904.pdf" H 9450 2600 50  0001 L CNN
	1    9450 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	9250 2600 9250 2400
Wire Wire Line
	9250 2400 9550 2400
Wire Wire Line
	8800 2800 8900 2800
Wire Wire Line
	8800 2400 8900 2400
Connection ~ 9250 2400
$Comp
L Transistor_BJT:2N3904 Q?
U 1 1 5CC2E804
P 9450 3550
AR Path="/5CC2E804" Ref="Q?"  Part="1" 
AR Path="/5CC2E26B/5CC2E804" Ref="Q?"  Part="1" 
F 0 "Q?" H 9641 3596 50  0000 L CNN
F 1 "2N2222" H 9641 3505 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 9650 3475 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N3904.pdf" H 9450 3550 50  0001 L CNN
	1    9450 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 3350 8650 3350
Wire Wire Line
	9250 3550 9250 3350
Connection ~ 9250 3350
Wire Wire Line
	9250 3350 9550 3350
Wire Wire Line
	8500 3750 8650 3750
$Comp
L Transistor_BJT:2N3904 Q?
U 1 1 5CC2E810
P 9450 4350
AR Path="/5CC2E810" Ref="Q?"  Part="1" 
AR Path="/5CC2E26B/5CC2E810" Ref="Q?"  Part="1" 
F 0 "Q?" H 9641 4396 50  0000 L CNN
F 1 "2N2222" H 9641 4305 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 9650 4275 50  0001 L CIN
F 3 "https://www.fairchildsemi.com/datasheets/2N/2N3904.pdf" H 9450 4350 50  0001 L CNN
	1    9450 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	9250 4350 9250 4150
Wire Wire Line
	9250 4150 9550 4150
Wire Wire Line
	8800 4550 8900 4550
Wire Wire Line
	8800 4150 8900 4150
Connection ~ 9250 4150
Wire Wire Line
	8200 3750 8200 3350
Wire Wire Line
	7600 2900 7600 3200
Wire Wire Line
	7600 3200 7850 3200
$Comp
L Device:C_Small C?
U 1 1 5CC2E832
P 7550 3650
AR Path="/5CC2E832" Ref="C?"  Part="1" 
AR Path="/5CC2E26B/5CC2E832" Ref="C?"  Part="1" 
F 0 "C?" H 7400 3650 50  0000 C CNN
F 1 ".1uF" H 7400 3550 50  0000 C CNN
F 2 "" H 7550 3650 50  0001 C CNN
F 3 "~" H 7550 3650 50  0001 C CNN
	1    7550 3650
	1    0    0    -1  
$EndComp
Text GLabel 7450 1600 0    50   Input ~ 0
PI_3V3
Text GLabel 7350 3500 0    50   Input ~ 0
PI_3V3
$Comp
L Device:C_Small C?
U 1 1 5CC2E848
P 8850 1800
AR Path="/5CC2E848" Ref="C?"  Part="1" 
AR Path="/5CC2E26B/5CC2E848" Ref="C?"  Part="1" 
F 0 "C?" H 8942 1846 50  0000 L CNN
F 1 "1000pF" H 8942 1755 50  0000 L CNN
F 2 "" H 8850 1800 50  0001 C CNN
F 3 "~" H 8850 1800 50  0001 C CNN
	1    8850 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	8850 1700 8850 1600
Wire Wire Line
	8850 1900 8850 2000
$Comp
L Device:C_Small C?
U 1 1 5CC2E855
P 8900 2600
AR Path="/5CC2E855" Ref="C?"  Part="1" 
AR Path="/5CC2E26B/5CC2E855" Ref="C?"  Part="1" 
F 0 "C?" H 8992 2646 50  0000 L CNN
F 1 "1000pF" H 8992 2555 50  0000 L CNN
F 2 "" H 8900 2600 50  0001 C CNN
F 3 "~" H 8900 2600 50  0001 C CNN
	1    8900 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	8900 2500 8900 2400
Wire Wire Line
	8900 2700 8900 2800
$Comp
L Device:C_Small C?
U 1 1 5CC2E85E
P 8650 3550
AR Path="/5CC2E85E" Ref="C?"  Part="1" 
AR Path="/5CC2E26B/5CC2E85E" Ref="C?"  Part="1" 
F 0 "C?" H 8742 3596 50  0000 L CNN
F 1 "1000pF" H 8742 3505 50  0000 L CNN
F 2 "" H 8650 3550 50  0001 C CNN
F 3 "~" H 8650 3550 50  0001 C CNN
	1    8650 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	8650 3450 8650 3350
Wire Wire Line
	8650 3650 8650 3750
$Comp
L Device:C_Small C?
U 1 1 5CC2E867
P 8900 4350
AR Path="/5CC2E867" Ref="C?"  Part="1" 
AR Path="/5CC2E26B/5CC2E867" Ref="C?"  Part="1" 
F 0 "C?" H 8992 4396 50  0000 L CNN
F 1 "1000pF" H 8992 4305 50  0000 L CNN
F 2 "" H 8900 4350 50  0001 C CNN
F 3 "~" H 8900 4350 50  0001 C CNN
	1    8900 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	8900 4250 8900 4150
Wire Wire Line
	8900 4450 8900 4550
Connection ~ 8650 3350
Wire Wire Line
	8650 3350 9250 3350
Connection ~ 8650 3750
Wire Wire Line
	8650 3750 9550 3750
Connection ~ 8900 4150
Wire Wire Line
	8900 4150 9250 4150
Connection ~ 8900 4550
Wire Wire Line
	8900 4550 9550 4550
Connection ~ 8900 2800
Wire Wire Line
	8900 2800 9550 2800
Connection ~ 8900 2400
Wire Wire Line
	8900 2400 9250 2400
Text Notes 9850 2200 0    50   ~ 0
Temp Diodes
Text Notes 9800 4000 0    50   ~ 0
Temp Diodes
Text GLabel 5650 2700 0    50   Input ~ 0
Therm_SDA
Text GLabel 5650 2400 0    50   Input ~ 0
Therm_SCL
$Comp
L Device:R_Small_US R?
U 1 1 5CC305D4
P 6100 2700
F 0 "R?" V 6305 2700 50  0000 C CNN
F 1 "20R" V 6214 2700 50  0000 C CNN
F 2 "" H 6100 2700 50  0001 C CNN
F 3 "~" H 6100 2700 50  0001 C CNN
	1    6100 2700
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small_US R?
U 1 1 5CC305DB
P 6100 2400
F 0 "R?" V 6200 2400 50  0000 C CNN
F 1 "20R" V 6000 2400 50  0000 C CNN
F 2 "" H 6100 2400 50  0001 C CNN
F 3 "~" H 6100 2400 50  0001 C CNN
	1    6100 2400
	0    1    1    0   
$EndComp
Text Label 6650 2700 2    50   ~ 0
Therm_SDA
Text Label 6650 2400 2    50   ~ 0
Therm_SCL
Wire Wire Line
	5650 2400 6000 2400
Wire Wire Line
	5650 2700 6000 2700
Wire Wire Line
	6200 2700 6800 2700
Wire Wire Line
	6200 2400 6800 2400
Text GLabel 5500 4450 0    50   Input ~ 0
Therm_SDA
Text GLabel 5500 4150 0    50   Input ~ 0
Therm_SCL
$Comp
L Device:R_Small_US R?
U 1 1 5CC4ABB8
P 5950 4450
F 0 "R?" V 6155 4450 50  0000 C CNN
F 1 "20R" V 6064 4450 50  0000 C CNN
F 2 "" H 5950 4450 50  0001 C CNN
F 3 "~" H 5950 4450 50  0001 C CNN
	1    5950 4450
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small_US R?
U 1 1 5CC4ABBF
P 5950 4150
F 0 "R?" V 6050 4150 50  0000 C CNN
F 1 "20R" V 5850 4150 50  0000 C CNN
F 2 "" H 5950 4150 50  0001 C CNN
F 3 "~" H 5950 4150 50  0001 C CNN
	1    5950 4150
	0    1    1    0   
$EndComp
Text Label 6500 4450 2    50   ~ 0
Therm_SDA
Text Label 6500 4150 2    50   ~ 0
Therm_SCL
Wire Wire Line
	5500 4150 5850 4150
Wire Wire Line
	5500 4450 5850 4450
$Comp
L power:GND #PWR?
U 1 1 5CC57C89
P 7850 5000
F 0 "#PWR?" H 7850 4750 50  0001 C CNN
F 1 "GND" H 7855 4827 50  0000 C CNN
F 2 "" H 7850 5000 50  0001 C CNN
F 3 "" H 7850 5000 50  0001 C CNN
	1    7850 5000
	1    0    0    -1  
$EndComp
Connection ~ 7850 5000
Wire Wire Line
	7850 5000 8200 5000
$Comp
L power:GND #PWR?
U 1 1 5CC5991E
P 7850 3200
F 0 "#PWR?" H 7850 2950 50  0001 C CNN
F 1 "GND" H 7855 3027 50  0000 C CNN
F 2 "" H 7850 3200 50  0001 C CNN
F 3 "" H 7850 3200 50  0001 C CNN
	1    7850 3200
	1    0    0    -1  
$EndComp
Connection ~ 7850 3200
Wire Wire Line
	7850 3200 8200 3200
Wire Wire Line
	7900 3500 7900 3750
$Comp
L power:GND #PWR?
U 1 1 5CC60AF7
P 7550 3750
F 0 "#PWR?" H 7550 3500 50  0001 C CNN
F 1 "GND" H 7555 3577 50  0000 C CNN
F 2 "" H 7550 3750 50  0001 C CNN
F 3 "" H 7550 3750 50  0001 C CNN
	1    7550 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7550 3500 7550 3550
Wire Wire Line
	7550 3500 7900 3500
Wire Wire Line
	7350 3500 7550 3500
Connection ~ 7550 3500
Text GLabel 7600 2800 0    50   Input ~ 0
PI_3V3
Wire Wire Line
	7000 2400 7250 2400
Wire Wire Line
	7000 2700 7250 2700
Wire Wire Line
	6950 4150 7250 4150
Wire Wire Line
	6950 4450 7250 4450
Wire Wire Line
	6050 4150 6750 4150
Wire Wire Line
	6050 4450 6750 4450
Wire Wire Line
	7450 1600 7900 1600
Wire Wire Line
	7900 1600 7900 2000
$Comp
L Device:C_Small C?
U 1 1 5CC8919C
P 7600 1700
AR Path="/5CC8919C" Ref="C?"  Part="1" 
AR Path="/5CC2E26B/5CC8919C" Ref="C?"  Part="1" 
F 0 "C?" H 7450 1700 50  0000 C CNN
F 1 ".1uF" H 7450 1600 50  0000 C CNN
F 2 "" H 7600 1700 50  0001 C CNN
F 3 "~" H 7600 1700 50  0001 C CNN
	1    7600 1700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5CC8AAAC
P 7600 1800
F 0 "#PWR?" H 7600 1550 50  0001 C CNN
F 1 "GND" H 7605 1627 50  0000 C CNN
F 2 "" H 7600 1800 50  0001 C CNN
F 3 "" H 7600 1800 50  0001 C CNN
	1    7600 1800
	1    0    0    -1  
$EndComp
Connection ~ 8850 2000
Wire Wire Line
	8850 2000 9550 2000
Wire Wire Line
	8500 2000 8850 2000
Connection ~ 8850 1600
Wire Wire Line
	8850 1600 9250 1600
Wire Wire Line
	8200 1600 8850 1600
$EndSCHEMATC
