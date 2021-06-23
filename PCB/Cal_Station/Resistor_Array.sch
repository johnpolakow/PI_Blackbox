EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 7
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Notes Line
	5550 700  4350 700 
Wire Notes Line
	4350 700  4350 6650
$Comp
L Device:R_Small_US R?
U 1 1 5EFB15DB
P 4900 950
AR Path="/5EFB15DB" Ref="R?"  Part="1" 
AR Path="/5EFA74C2/5EFB15DB" Ref="R5"  Part="1" 
AR Path="/5F851FE1/5F8CBC20/5EFB15DB" Ref="R?"  Part="1" 
F 0 "R5" H 4832 904 50  0000 R CNN
F 1 "120R" H 4832 995 50  0000 R CNN
F 2 "" H 4900 950 50  0001 C CNN
F 3 "~" H 4900 950 50  0001 C CNN
	1    4900 950 
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small_US R?
U 1 1 5EFB15E1
P 4900 2000
AR Path="/5EFB15E1" Ref="R?"  Part="1" 
AR Path="/5EFA74C2/5EFB15E1" Ref="R6"  Part="1" 
AR Path="/5F851FE1/5F8CBC20/5EFB15E1" Ref="R?"  Part="1" 
F 0 "R6" H 4832 1954 50  0000 R CNN
F 1 "60R" H 4832 2045 50  0000 R CNN
F 2 "" H 4900 2000 50  0001 C CNN
F 3 "~" H 4900 2000 50  0001 C CNN
	1    4900 2000
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small_US R?
U 1 1 5EFB15ED
P 4850 3050
AR Path="/5EFB15ED" Ref="R?"  Part="1" 
AR Path="/5EFA74C2/5EFB15ED" Ref="R1"  Part="1" 
AR Path="/5F851FE1/5F8CBC20/5EFB15ED" Ref="R?"  Part="1" 
F 0 "R1" H 4782 3004 50  0000 R CNN
F 1 "40R" H 4782 3095 50  0000 R CNN
F 2 "" H 4850 3050 50  0001 C CNN
F 3 "~" H 4850 3050 50  0001 C CNN
	1    4850 3050
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small_US R?
U 1 1 5EFB15F9
P 4850 4100
AR Path="/5EFB15F9" Ref="R?"  Part="1" 
AR Path="/5EFA74C2/5EFB15F9" Ref="R2"  Part="1" 
AR Path="/5F851FE1/5F8CBC20/5EFB15F9" Ref="R?"  Part="1" 
F 0 "R2" H 4782 4054 50  0000 R CNN
F 1 "30R" H 4782 4145 50  0000 R CNN
F 2 "" H 4850 4100 50  0001 C CNN
F 3 "~" H 4850 4100 50  0001 C CNN
	1    4850 4100
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small_US R?
U 1 1 5EFB160B
P 4850 5150
AR Path="/5EFB160B" Ref="R?"  Part="1" 
AR Path="/5EFA74C2/5EFB160B" Ref="R3"  Part="1" 
AR Path="/5F851FE1/5F8CBC20/5EFB160B" Ref="R?"  Part="1" 
F 0 "R3" H 4782 5104 50  0000 R CNN
F 1 "24R" H 4782 5195 50  0000 R CNN
F 2 "" H 4850 5150 50  0001 C CNN
F 3 "~" H 4850 5150 50  0001 C CNN
	1    4850 5150
	-1   0    0    1   
$EndComp
Text Notes 5600 1000 0    59   ~ 12
100mA\n
Text Notes 5600 2050 0    59   ~ 12
200mA\n
Text Notes 5600 3100 0    59   ~ 12
300mA
Text Notes 5600 4150 0    59   ~ 12
400mA
Text Notes 5600 5200 0    59   ~ 12
500mA
Text Notes 5600 6250 0    59   ~ 12
600mA
Text Notes 4600 650  0    59   ~ 12
Resistor Array
$Comp
L txs2:TXS2 K?
U 1 1 5EFB5EC7
P 3100 1100
AR Path="/5EFB5EC7" Ref="K?"  Part="1" 
AR Path="/5EFA74C2/5EFB5EC7" Ref="K2"  Part="1" 
AR Path="/5F851FE1/5F8CBC20/5EFB5EC7" Ref="K?"  Part="1" 
F 0 "K2" H 3150 1618 51  0000 C CNN
F 1 "2A Relay" H 3150 1526 50  0000 C CNN
F 2 "Footprints:Panasonic_TX2_2" V 4112 1955 50  0001 C CNN
F 3 "http://www.azettler.com/pdfs/az850.pdf" V 3150 850 50  0001 C CNN
	1    3100 1100
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3350 850  4900 850 
Wire Wire Line
	3350 1100 4900 1100
Wire Wire Line
	4900 1100 4900 1050
$Comp
L txs2:TXS2 K?
U 1 1 5EFC899D
P 3100 2150
AR Path="/5EFC899D" Ref="K?"  Part="1" 
AR Path="/5EFA74C2/5EFC899D" Ref="K3"  Part="1" 
AR Path="/5F851FE1/5F8CBC20/5EFC899D" Ref="K?"  Part="1" 
F 0 "K3" H 3450 2450 51  0000 C CNN
F 1 "2A Relay" H 2700 2450 50  0000 C CNN
F 2 "Footprints:Panasonic_TX2_2" V 4112 3005 50  0001 C CNN
F 3 "http://www.azettler.com/pdfs/az850.pdf" V 3150 1900 50  0001 C CNN
	1    3100 2150
	-1   0    0    -1  
$EndComp
$Comp
L txs2:TXS2 K?
U 1 1 5EFCA3FA
P 3100 3200
AR Path="/5EFCA3FA" Ref="K?"  Part="1" 
AR Path="/5EFA74C2/5EFCA3FA" Ref="K4"  Part="1" 
AR Path="/5F851FE1/5F8CBC20/5EFCA3FA" Ref="K?"  Part="1" 
F 0 "K4" H 3400 3500 51  0000 C CNN
F 1 "2A Relay" H 3500 3350 50  0000 C CNN
F 2 "Footprints:Panasonic_TX2_2" V 4112 4055 50  0001 C CNN
F 3 "http://www.azettler.com/pdfs/az850.pdf" V 3150 2950 50  0001 C CNN
	1    3100 3200
	-1   0    0    -1  
$EndComp
$Comp
L txs2:TXS2 K?
U 1 1 5EFCBE68
P 3100 4250
AR Path="/5EFCBE68" Ref="K?"  Part="1" 
AR Path="/5EFA74C2/5EFCBE68" Ref="K5"  Part="1" 
AR Path="/5F851FE1/5F8CBC20/5EFCBE68" Ref="K?"  Part="1" 
F 0 "K5" H 3400 4600 51  0000 C CNN
F 1 "2A Relay" H 3500 4400 50  0000 C CNN
F 2 "Footprints:Panasonic_TX2_2" V 4112 5105 50  0001 C CNN
F 3 "http://www.azettler.com/pdfs/az850.pdf" V 3150 4000 50  0001 C CNN
	1    3100 4250
	-1   0    0    -1  
$EndComp
$Comp
L txs2:TXS2 K?
U 1 1 5EFCCAF6
P 3100 5300
AR Path="/5EFCCAF6" Ref="K?"  Part="1" 
AR Path="/5EFA74C2/5EFCCAF6" Ref="K6"  Part="1" 
AR Path="/5F851FE1/5F8CBC20/5EFCCAF6" Ref="K?"  Part="1" 
F 0 "K6" H 3400 5600 51  0000 C CNN
F 1 "2A Relay" H 3500 5450 50  0000 C CNN
F 2 "Footprints:Panasonic_TX2_2" V 4112 6155 50  0001 C CNN
F 3 "http://www.azettler.com/pdfs/az850.pdf" V 3150 5050 50  0001 C CNN
	1    3100 5300
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3350 1900 4900 1900
Wire Wire Line
	3350 2150 4900 2150
Wire Wire Line
	4900 2150 4900 2100
Wire Wire Line
	3350 2950 4850 2950
Wire Wire Line
	3350 3200 4850 3200
Wire Wire Line
	4850 3200 4850 3150
Wire Wire Line
	3350 4000 4850 4000
Wire Wire Line
	4850 4200 4850 4250
Wire Wire Line
	4850 4250 3350 4250
Wire Wire Line
	3350 5050 4850 5050
Wire Wire Line
	3350 5300 4850 5300
Wire Wire Line
	4850 5300 4850 5250
$Comp
L Device:R_Small_US R?
U 1 1 5F04E5F8
P 4850 6200
AR Path="/5F04E5F8" Ref="R?"  Part="1" 
AR Path="/5EFA74C2/5F04E5F8" Ref="R4"  Part="1" 
AR Path="/5F851FE1/5F8CBC20/5F04E5F8" Ref="R?"  Part="1" 
F 0 "R4" H 4782 6154 50  0000 R CNN
F 1 "20R" H 4782 6245 50  0000 R CNN
F 2 "" H 4850 6200 50  0001 C CNN
F 3 "~" H 4850 6200 50  0001 C CNN
	1    4850 6200
	-1   0    0    1   
$EndComp
$Comp
L txs2:TXS2 K?
U 1 1 5F04E5FE
P 3100 6350
AR Path="/5F04E5FE" Ref="K?"  Part="1" 
AR Path="/5EFA74C2/5F04E5FE" Ref="K7"  Part="1" 
AR Path="/5F851FE1/5F8CBC20/5F04E5FE" Ref="K?"  Part="1" 
F 0 "K7" H 3450 6650 51  0000 C CNN
F 1 "2A Relay" H 3550 6500 50  0000 C CNN
F 2 "Footprints:Panasonic_TX2_2" V 4112 7205 50  0001 C CNN
F 3 "http://www.azettler.com/pdfs/az850.pdf" V 3150 6100 50  0001 C CNN
	1    3100 6350
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3350 6100 4850 6100
Wire Wire Line
	3350 6350 4850 6350
Wire Wire Line
	4850 6350 4850 6300
Wire Wire Line
	2750 6400 2100 6400
Text HLabel 1950 6400 0    59   Input ~ 12
RES_RTN
Text HLabel 1950 5350 0    59   Input ~ 12
RES_RTN
Text HLabel 1950 4300 0    59   Input ~ 12
RES_RTN
Text HLabel 1950 3250 0    59   Input ~ 12
RES_RTN
Text HLabel 1950 2200 0    59   Input ~ 12
RES_RTN
Text HLabel 1950 1150 0    59   Input ~ 12
RES_RTN
Wire Wire Line
	1950 5350 2100 5350
Wire Wire Line
	1950 4300 2100 4300
Wire Wire Line
	1950 3250 2100 3250
Wire Wire Line
	1950 2200 2100 2200
Wire Wire Line
	1950 1150 2100 1150
Text HLabel 1950 6150 0    59   Input ~ 12
RES_IN
Wire Wire Line
	1950 6150 2300 6150
Text HLabel 1950 5100 0    59   Input ~ 12
RES_IN
Wire Wire Line
	1950 5100 2300 5100
Text HLabel 1950 4050 0    59   Input ~ 12
RES_IN
Wire Wire Line
	1950 4050 2300 4050
Text HLabel 1950 3000 0    59   Input ~ 12
RES_IN
Wire Wire Line
	1950 3000 2300 3000
Text HLabel 1950 1950 0    59   Input ~ 12
RES_IN
Wire Wire Line
	1950 1950 2300 1950
Text HLabel 1950 900  0    59   Input ~ 12
RES_IN
Wire Wire Line
	1950 900  2300 900 
Wire Notes Line
	5550 700  5550 6650
Wire Notes Line
	5550 6650 4350 6650
Wire Wire Line
	2100 6400 2100 5350
Connection ~ 2100 6400
Wire Wire Line
	2100 6400 1950 6400
Connection ~ 2100 5350
Wire Wire Line
	2100 5350 2750 5350
Wire Wire Line
	2100 5350 2100 4300
Connection ~ 2100 4300
Wire Wire Line
	2100 4300 2750 4300
Wire Wire Line
	2100 4300 2100 3250
Connection ~ 2100 3250
Wire Wire Line
	2100 3250 2750 3250
Wire Wire Line
	2100 3250 2100 2200
Connection ~ 2100 2200
Wire Wire Line
	2100 2200 2750 2200
Wire Wire Line
	2100 2200 2100 1150
Connection ~ 2100 1150
Wire Wire Line
	2100 1150 2750 1150
Wire Wire Line
	2300 900  2300 1950
Connection ~ 2300 900 
Wire Wire Line
	2300 900  2750 900 
Connection ~ 2300 1950
Wire Wire Line
	2300 1950 2750 1950
Wire Wire Line
	2300 1950 2300 3000
Connection ~ 2300 3000
Wire Wire Line
	2300 3000 2750 3000
Wire Wire Line
	2300 3000 2300 4050
Connection ~ 2300 4050
Wire Wire Line
	2300 4050 2750 4050
Wire Wire Line
	2300 4050 2300 5100
Connection ~ 2300 5100
Wire Wire Line
	2300 5100 2750 5100
Wire Wire Line
	2300 5100 2300 6150
Connection ~ 2300 6150
Wire Wire Line
	2300 6150 2750 6150
Text GLabel 3600 1750 2    47   Input ~ 0
K2_SET
$Comp
L Diode:1N4148W D?
U 1 1 60822CF1
P 3450 1550
AR Path="/5F865273/60822CF1" Ref="D?"  Part="1" 
AR Path="/5EFA74C2/60822CF1" Ref="D9"  Part="1" 
F 0 "D9" V 3450 1750 50  0000 C CNN
F 1 "1N4148W" H 3450 1650 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 3450 1375 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 3450 1550 50  0001 C CNN
	1    3450 1550
	0    1    1    0   
$EndComp
Wire Wire Line
	3450 1700 3450 1750
Wire Wire Line
	3450 1400 3450 1350
Wire Wire Line
	3350 1350 3450 1350
Connection ~ 3450 1350
Wire Wire Line
	3350 1750 3450 1750
Wire Wire Line
	3450 1350 3600 1350
Wire Wire Line
	3450 1750 3600 1750
Connection ~ 3450 1750
Text GLabel 3600 1350 2    50   Input ~ 0
+5V
$Comp
L Diode:1N4148W D?
U 1 1 60864B8D
P 2650 1550
AR Path="/5F865273/60864B8D" Ref="D?"  Part="1" 
AR Path="/5EFA74C2/60864B8D" Ref="D3"  Part="1" 
F 0 "D3" V 2650 1350 50  0000 C CNN
F 1 "1N4148W" H 2650 1450 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 2650 1375 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 2650 1550 50  0001 C CNN
	1    2650 1550
	0    1    1    0   
$EndComp
Wire Wire Line
	2650 1400 2750 1400
Wire Wire Line
	2750 1700 2650 1700
Wire Wire Line
	2650 1700 2650 1800
Wire Wire Line
	2650 1800 2550 1800
Connection ~ 2650 1700
Wire Wire Line
	2650 1400 2650 1300
Wire Wire Line
	2650 1300 2500 1300
Connection ~ 2650 1400
Text GLabel 2500 1300 0    50   Input ~ 0
+5V
$Comp
L Diode:1N4148W D?
U 1 1 60869C1B
P 2650 3650
AR Path="/5F865273/60869C1B" Ref="D?"  Part="1" 
AR Path="/5EFA74C2/60869C1B" Ref="D5"  Part="1" 
F 0 "D5" V 2650 3450 50  0000 C CNN
F 1 "1N4148W" H 2650 3550 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 2650 3475 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 2650 3650 50  0001 C CNN
	1    2650 3650
	0    1    1    0   
$EndComp
Wire Wire Line
	2650 3500 2750 3500
Wire Wire Line
	2750 3800 2650 3800
Wire Wire Line
	2650 3800 2650 3900
Wire Wire Line
	2650 3900 2550 3900
Connection ~ 2650 3800
Wire Wire Line
	2650 3500 2650 3400
Wire Wire Line
	2650 3400 2500 3400
Connection ~ 2650 3500
Text GLabel 2500 3400 0    50   Input ~ 0
+5V
$Comp
L Diode:1N4148W D?
U 1 1 6086F142
P 2650 4700
AR Path="/5F865273/6086F142" Ref="D?"  Part="1" 
AR Path="/5EFA74C2/6086F142" Ref="D6"  Part="1" 
F 0 "D6" V 2650 4500 50  0000 C CNN
F 1 "1N4148W" H 2650 4600 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 2650 4525 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 2650 4700 50  0001 C CNN
	1    2650 4700
	0    1    1    0   
$EndComp
Wire Wire Line
	2650 4550 2750 4550
Wire Wire Line
	2750 4850 2650 4850
Wire Wire Line
	2650 4850 2650 4950
Wire Wire Line
	2650 4950 2550 4950
Connection ~ 2650 4850
Wire Wire Line
	2650 4550 2650 4450
Wire Wire Line
	2650 4450 2500 4450
Connection ~ 2650 4550
Text GLabel 2500 4450 0    50   Input ~ 0
+5V
$Comp
L Diode:1N4148W D?
U 1 1 608746AA
P 2650 5750
AR Path="/5F865273/608746AA" Ref="D?"  Part="1" 
AR Path="/5EFA74C2/608746AA" Ref="D7"  Part="1" 
F 0 "D7" V 2650 5550 50  0000 C CNN
F 1 "1N4148W" H 2650 5650 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 2650 5575 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 2650 5750 50  0001 C CNN
	1    2650 5750
	0    1    1    0   
$EndComp
Wire Wire Line
	2650 5600 2750 5600
Wire Wire Line
	2750 5900 2650 5900
Wire Wire Line
	2650 5900 2650 6000
Wire Wire Line
	2650 6000 2550 6000
Connection ~ 2650 5900
Wire Wire Line
	2650 5600 2650 5500
Wire Wire Line
	2650 5500 2500 5500
Connection ~ 2650 5600
Text GLabel 2500 5500 0    50   Input ~ 0
+5V
$Comp
L Diode:1N4148W D?
U 1 1 608789F3
P 2650 6800
AR Path="/5F865273/608789F3" Ref="D?"  Part="1" 
AR Path="/5EFA74C2/608789F3" Ref="D8"  Part="1" 
F 0 "D8" V 2650 6600 50  0000 C CNN
F 1 "1N4148W" H 2650 6700 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 2650 6625 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 2650 6800 50  0001 C CNN
	1    2650 6800
	0    1    1    0   
$EndComp
Wire Wire Line
	2650 6650 2750 6650
Wire Wire Line
	2750 6950 2650 6950
Wire Wire Line
	2650 6950 2650 7050
Wire Wire Line
	2650 7050 2550 7050
Connection ~ 2650 6950
Wire Wire Line
	2650 6650 2650 6550
Wire Wire Line
	2650 6550 2500 6550
Connection ~ 2650 6650
Text GLabel 2500 6550 0    50   Input ~ 0
+5V
Wire Wire Line
	2750 6950 2750 6900
Wire Wire Line
	2750 6650 2750 6700
Wire Wire Line
	2750 5600 2750 5650
Wire Wire Line
	2750 5900 2750 5850
Wire Wire Line
	2750 4550 2750 4600
Wire Wire Line
	2750 4850 2750 4800
Wire Wire Line
	2750 3500 2750 3550
Wire Wire Line
	2750 3800 2750 3750
$Comp
L Diode:1N4148W D?
U 1 1 608A245F
P 2650 2600
AR Path="/5F865273/608A245F" Ref="D?"  Part="1" 
AR Path="/5EFA74C2/608A245F" Ref="D4"  Part="1" 
F 0 "D4" V 2650 2400 50  0000 C CNN
F 1 "1N4148W" H 2650 2500 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 2650 2425 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 2650 2600 50  0001 C CNN
	1    2650 2600
	0    1    1    0   
$EndComp
Wire Wire Line
	2650 2450 2750 2450
Wire Wire Line
	2750 2750 2650 2750
Wire Wire Line
	2650 2750 2650 2850
Wire Wire Line
	2650 2850 2550 2850
Connection ~ 2650 2750
Wire Wire Line
	2650 2450 2650 2350
Connection ~ 2650 2450
Text GLabel 2450 2350 0    50   Input ~ 0
+5V
Wire Wire Line
	2750 2750 2750 2700
Wire Wire Line
	2750 2450 2750 2500
Wire Wire Line
	3350 1750 3350 1650
Wire Wire Line
	3350 1450 3350 1350
$Comp
L Diode:1N4148W D?
U 1 1 608DDC13
P 3450 2600
AR Path="/5F865273/608DDC13" Ref="D?"  Part="1" 
AR Path="/5EFA74C2/608DDC13" Ref="D10"  Part="1" 
F 0 "D10" V 3450 2800 50  0000 C CNN
F 1 "1N4148W" H 3450 2700 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 3450 2425 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 3450 2600 50  0001 C CNN
	1    3450 2600
	0    1    1    0   
$EndComp
Wire Wire Line
	3450 2750 3450 2800
Wire Wire Line
	3450 2450 3450 2400
Wire Wire Line
	3350 2400 3450 2400
Connection ~ 3450 2400
Wire Wire Line
	3350 2800 3450 2800
Wire Wire Line
	3450 2400 3600 2400
Wire Wire Line
	3450 2800 3600 2800
Connection ~ 3450 2800
Text GLabel 3600 2400 2    50   Input ~ 0
+5V
$Comp
L Diode:1N4148W D?
U 1 1 608E4B81
P 3450 3650
AR Path="/5F865273/608E4B81" Ref="D?"  Part="1" 
AR Path="/5EFA74C2/608E4B81" Ref="D11"  Part="1" 
F 0 "D11" V 3450 3850 50  0000 C CNN
F 1 "1N4148W" H 3450 3750 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 3450 3475 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 3450 3650 50  0001 C CNN
	1    3450 3650
	0    1    1    0   
$EndComp
Wire Wire Line
	3450 3800 3450 3850
Wire Wire Line
	3450 3500 3450 3450
Wire Wire Line
	3350 3450 3450 3450
Connection ~ 3450 3450
Wire Wire Line
	3350 3850 3450 3850
Wire Wire Line
	3450 3450 3600 3450
Wire Wire Line
	3450 3850 3600 3850
Connection ~ 3450 3850
Text GLabel 3600 3450 2    50   Input ~ 0
+5V
$Comp
L Diode:1N4148W D?
U 1 1 608F8E1F
P 3450 4700
AR Path="/5F865273/608F8E1F" Ref="D?"  Part="1" 
AR Path="/5EFA74C2/608F8E1F" Ref="D12"  Part="1" 
F 0 "D12" V 3450 4900 50  0000 C CNN
F 1 "1N4148W" H 3450 4800 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 3450 4525 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 3450 4700 50  0001 C CNN
	1    3450 4700
	0    1    1    0   
$EndComp
Wire Wire Line
	3450 4850 3450 4900
Wire Wire Line
	3450 4550 3450 4500
Wire Wire Line
	3350 4500 3450 4500
Connection ~ 3450 4500
Wire Wire Line
	3350 4900 3450 4900
Wire Wire Line
	3450 4500 3600 4500
Wire Wire Line
	3450 4900 3600 4900
Connection ~ 3450 4900
Text GLabel 3600 4500 2    50   Input ~ 0
+5V
$Comp
L Diode:1N4148W D?
U 1 1 6090040B
P 3450 5750
AR Path="/5F865273/6090040B" Ref="D?"  Part="1" 
AR Path="/5EFA74C2/6090040B" Ref="D13"  Part="1" 
F 0 "D13" V 3450 5950 50  0000 C CNN
F 1 "1N4148W" H 3450 5850 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 3450 5575 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 3450 5750 50  0001 C CNN
	1    3450 5750
	0    1    1    0   
$EndComp
Wire Wire Line
	3450 5900 3450 5950
Wire Wire Line
	3450 5600 3450 5550
Connection ~ 3450 5550
Wire Wire Line
	3350 5950 3450 5950
Wire Wire Line
	3450 5550 3600 5550
Wire Wire Line
	3450 5950 3600 5950
Connection ~ 3450 5950
Text GLabel 3600 5550 2    50   Input ~ 0
+5V
$Comp
L Diode:1N4148W D?
U 1 1 60907DB1
P 3450 6800
AR Path="/5F865273/60907DB1" Ref="D?"  Part="1" 
AR Path="/5EFA74C2/60907DB1" Ref="D14"  Part="1" 
F 0 "D14" V 3450 7000 50  0000 C CNN
F 1 "1N4148W" H 3450 6900 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 3450 6625 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 3450 6800 50  0001 C CNN
	1    3450 6800
	0    1    1    0   
$EndComp
Wire Wire Line
	3450 6950 3450 7000
Wire Wire Line
	3450 6650 3450 6600
Wire Wire Line
	3350 6600 3450 6600
Connection ~ 3450 6600
Wire Wire Line
	3350 7000 3450 7000
Wire Wire Line
	3450 6600 3600 6600
Wire Wire Line
	3450 7000 3600 7000
Connection ~ 3450 7000
Text GLabel 3600 6600 2    50   Input ~ 0
+5V
Wire Wire Line
	3350 7000 3350 6900
Wire Wire Line
	3350 6700 3350 6600
Wire Wire Line
	3350 5950 3350 5850
Wire Wire Line
	3350 5650 3350 5550
Wire Wire Line
	3350 5550 3450 5550
Wire Wire Line
	3350 4900 3350 4800
Wire Wire Line
	3350 4600 3350 4500
Wire Wire Line
	3350 3850 3350 3750
Wire Wire Line
	3350 3550 3350 3450
Wire Wire Line
	3350 2800 3350 2700
Wire Wire Line
	3350 2500 3350 2400
Text GLabel 2550 1800 0    47   Input ~ 0
K2_RESET
Text GLabel 2550 2850 0    47   Input ~ 0
K3_RESET
Text GLabel 2550 3900 0    47   Input ~ 0
K4_RESET
Text GLabel 2550 4950 0    47   Input ~ 0
K5_RESET
Text GLabel 2550 6000 0    47   Input ~ 0
K6_RESET
Text GLabel 2550 7050 0    47   Input ~ 0
K7_RESET
Wire Wire Line
	2450 2350 2650 2350
Text GLabel 3600 2800 2    47   Input ~ 0
K3_SET
Text GLabel 3600 3850 2    47   Input ~ 0
K4_SET
Text GLabel 3600 4900 2    47   Input ~ 0
K5_SET
Text GLabel 3600 5950 2    47   Input ~ 0
K6_SET
Text GLabel 3600 7000 2    47   Input ~ 0
K7_SET
Text GLabel 8550 1700 0    50   Input ~ 0
+5V
Text GLabel 9300 2000 0    47   Input ~ 0
K3_SET
Text GLabel 8550 2000 0    47   Input ~ 0
K3_RESET
$Comp
L Device:C_Small C?
U 1 1 60BA4E8B
P 8650 1850
AR Path="/60BA4E8B" Ref="C?"  Part="1" 
AR Path="/5EFA74C2/60BA4E8B" Ref="C4"  Part="1" 
F 0 "C4" H 8742 1896 50  0000 L CNN
F 1 "10uF" H 8742 1805 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 8650 1850 50  0001 C CNN
F 3 "~" H 8650 1850 50  0001 C CNN
	1    8650 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 1700 8650 1700
Wire Wire Line
	8650 1700 8650 1750
Wire Wire Line
	8550 2000 8650 2000
Wire Wire Line
	8650 2000 8650 1950
Text GLabel 9300 1700 0    50   Input ~ 0
+5V
$Comp
L Device:C_Small C?
U 1 1 60BA4E96
P 9400 1850
AR Path="/60BA4E96" Ref="C?"  Part="1" 
AR Path="/5EFA74C2/60BA4E96" Ref="C10"  Part="1" 
F 0 "C10" H 9492 1896 50  0000 L CNN
F 1 "10uF" H 9492 1805 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 9400 1850 50  0001 C CNN
F 3 "~" H 9400 1850 50  0001 C CNN
	1    9400 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	9300 1700 9400 1700
Wire Wire Line
	9400 1700 9400 1750
Wire Wire Line
	9300 2000 9400 2000
Wire Wire Line
	9400 2000 9400 1950
Text GLabel 8550 2250 0    50   Input ~ 0
+5V
Text GLabel 9300 2550 0    47   Input ~ 0
K4_SET
Text GLabel 8550 2550 0    47   Input ~ 0
K4_RESET
$Comp
L Device:C_Small C?
U 1 1 60BAB13C
P 8650 2400
AR Path="/60BAB13C" Ref="C?"  Part="1" 
AR Path="/5EFA74C2/60BAB13C" Ref="C5"  Part="1" 
F 0 "C5" H 8742 2446 50  0000 L CNN
F 1 "10uF" H 8742 2355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 8650 2400 50  0001 C CNN
F 3 "~" H 8650 2400 50  0001 C CNN
	1    8650 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 2250 8650 2250
Wire Wire Line
	8650 2250 8650 2300
Wire Wire Line
	8550 2550 8650 2550
Wire Wire Line
	8650 2550 8650 2500
Text GLabel 9300 2250 0    50   Input ~ 0
+5V
$Comp
L Device:C_Small C?
U 1 1 60BAB147
P 9400 2400
AR Path="/60BAB147" Ref="C?"  Part="1" 
AR Path="/5EFA74C2/60BAB147" Ref="C11"  Part="1" 
F 0 "C11" H 9492 2446 50  0000 L CNN
F 1 "10uF" H 9492 2355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 9400 2400 50  0001 C CNN
F 3 "~" H 9400 2400 50  0001 C CNN
	1    9400 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	9300 2250 9400 2250
Wire Wire Line
	9400 2250 9400 2300
Wire Wire Line
	9300 2550 9400 2550
Wire Wire Line
	9400 2550 9400 2500
Text GLabel 8550 2750 0    50   Input ~ 0
+5V
Text GLabel 9300 3050 0    47   Input ~ 0
K5_SET
Text GLabel 8550 3050 0    47   Input ~ 0
K5_RESET
$Comp
L Device:C_Small C?
U 1 1 60BB1ADF
P 8650 2900
AR Path="/60BB1ADF" Ref="C?"  Part="1" 
AR Path="/5EFA74C2/60BB1ADF" Ref="C6"  Part="1" 
F 0 "C6" H 8742 2946 50  0000 L CNN
F 1 "10uF" H 8742 2855 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 8650 2900 50  0001 C CNN
F 3 "~" H 8650 2900 50  0001 C CNN
	1    8650 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 2750 8650 2750
Wire Wire Line
	8650 2750 8650 2800
Wire Wire Line
	8550 3050 8650 3050
Wire Wire Line
	8650 3050 8650 3000
Text GLabel 9300 2750 0    50   Input ~ 0
+5V
$Comp
L Device:C_Small C?
U 1 1 60BB1AEA
P 9400 2900
AR Path="/60BB1AEA" Ref="C?"  Part="1" 
AR Path="/5EFA74C2/60BB1AEA" Ref="C12"  Part="1" 
F 0 "C12" H 9492 2946 50  0000 L CNN
F 1 "10uF" H 9492 2855 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 9400 2900 50  0001 C CNN
F 3 "~" H 9400 2900 50  0001 C CNN
	1    9400 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	9300 2750 9400 2750
Wire Wire Line
	9400 2750 9400 2800
Wire Wire Line
	9300 3050 9400 3050
Wire Wire Line
	9400 3050 9400 3000
Text GLabel 8550 3400 0    50   Input ~ 0
+5V
Text GLabel 9300 3700 0    47   Input ~ 0
K6_SET
Text GLabel 8550 3700 0    47   Input ~ 0
K6_RESET
$Comp
L Device:C_Small C?
U 1 1 60BB8CE0
P 8650 3550
AR Path="/60BB8CE0" Ref="C?"  Part="1" 
AR Path="/5EFA74C2/60BB8CE0" Ref="C7"  Part="1" 
F 0 "C7" H 8742 3596 50  0000 L CNN
F 1 "10uF" H 8742 3505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 8650 3550 50  0001 C CNN
F 3 "~" H 8650 3550 50  0001 C CNN
	1    8650 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 3400 8650 3400
Wire Wire Line
	8650 3400 8650 3450
Wire Wire Line
	8550 3700 8650 3700
Wire Wire Line
	8650 3700 8650 3650
Text GLabel 9300 3400 0    50   Input ~ 0
+5V
$Comp
L Device:C_Small C?
U 1 1 60BB8CEB
P 9400 3550
AR Path="/60BB8CEB" Ref="C?"  Part="1" 
AR Path="/5EFA74C2/60BB8CEB" Ref="C13"  Part="1" 
F 0 "C13" H 9492 3596 50  0000 L CNN
F 1 "10uF" H 9492 3505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 9400 3550 50  0001 C CNN
F 3 "~" H 9400 3550 50  0001 C CNN
	1    9400 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	9300 3400 9400 3400
Wire Wire Line
	9400 3400 9400 3450
Wire Wire Line
	9300 3700 9400 3700
Wire Wire Line
	9400 3700 9400 3650
Text GLabel 8550 3900 0    50   Input ~ 0
+5V
Text GLabel 9300 4200 0    47   Input ~ 0
K7_SET
Text GLabel 8550 4200 0    47   Input ~ 0
K7_RESET
$Comp
L Device:C_Small C?
U 1 1 60BC0741
P 8650 4050
AR Path="/60BC0741" Ref="C?"  Part="1" 
AR Path="/5EFA74C2/60BC0741" Ref="C8"  Part="1" 
F 0 "C8" H 8742 4096 50  0000 L CNN
F 1 "10uF" H 8742 4005 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 8650 4050 50  0001 C CNN
F 3 "~" H 8650 4050 50  0001 C CNN
	1    8650 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 3900 8650 3900
Wire Wire Line
	8650 3900 8650 3950
Wire Wire Line
	8550 4200 8650 4200
Wire Wire Line
	8650 4200 8650 4150
Text GLabel 9300 3900 0    50   Input ~ 0
+5V
$Comp
L Device:C_Small C?
U 1 1 60BC074C
P 9400 4050
AR Path="/60BC074C" Ref="C?"  Part="1" 
AR Path="/5EFA74C2/60BC074C" Ref="C14"  Part="1" 
F 0 "C14" H 9492 4096 50  0000 L CNN
F 1 "10uF" H 9492 4005 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 9400 4050 50  0001 C CNN
F 3 "~" H 9400 4050 50  0001 C CNN
	1    9400 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	9300 3900 9400 3900
Wire Wire Line
	9400 3900 9400 3950
Wire Wire Line
	9300 4200 9400 4200
Wire Wire Line
	9400 4200 9400 4150
Text GLabel 8550 1100 0    50   Input ~ 0
+5V
Text GLabel 9300 1400 0    47   Input ~ 0
K2_SET
Text GLabel 8550 1400 0    47   Input ~ 0
K2_RESET
$Comp
L Device:C_Small C?
U 1 1 60BC8AF4
P 8650 1250
AR Path="/60BC8AF4" Ref="C?"  Part="1" 
AR Path="/5EFA74C2/60BC8AF4" Ref="C3"  Part="1" 
F 0 "C3" H 8742 1296 50  0000 L CNN
F 1 "10uF" H 8742 1205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 8650 1250 50  0001 C CNN
F 3 "~" H 8650 1250 50  0001 C CNN
	1    8650 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 1100 8650 1100
Wire Wire Line
	8650 1100 8650 1150
Wire Wire Line
	8550 1400 8650 1400
Wire Wire Line
	8650 1400 8650 1350
Text GLabel 9300 1100 0    50   Input ~ 0
+5V
$Comp
L Device:C_Small C?
U 1 1 60BC8AFF
P 9400 1250
AR Path="/60BC8AFF" Ref="C?"  Part="1" 
AR Path="/5EFA74C2/60BC8AFF" Ref="C9"  Part="1" 
F 0 "C9" H 9492 1296 50  0000 L CNN
F 1 "10uF" H 9492 1205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 9400 1250 50  0001 C CNN
F 3 "~" H 9400 1250 50  0001 C CNN
	1    9400 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	9300 1100 9400 1100
Wire Wire Line
	9400 1100 9400 1150
Wire Wire Line
	9300 1400 9400 1400
Wire Wire Line
	9400 1400 9400 1350
$Comp
L Connector:TestPoint_Small TP12
U 1 1 619A4922
P 4900 1200
F 0 "TP12" H 4948 1200 50  0000 L CNN
F 1 "TestPoint_Small" H 4948 1155 50  0001 L CNN
F 2 "TestPoint:TestPoint_THTPad_D3.0mm_Drill1.5mm" H 5100 1200 50  0001 C CNN
F 3 "~" H 5100 1200 50  0001 C CNN
	1    4900 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 1200 4900 1100
Connection ~ 4900 1100
$Comp
L Connector:TestPoint_Small TP11
U 1 1 619B057E
P 4900 750
F 0 "TP11" H 4852 750 50  0000 R CNN
F 1 "TestPoint_Small" H 4948 705 50  0001 L CNN
F 2 "TestPoint:TestPoint_THTPad_D3.0mm_Drill1.5mm" H 5100 750 50  0001 C CNN
F 3 "~" H 5100 750 50  0001 C CNN
	1    4900 750 
	-1   0    0    1   
$EndComp
Wire Wire Line
	4900 750  4900 850 
$Comp
L Connector:TestPoint_Small TP14
U 1 1 619BE2D2
P 4900 2250
F 0 "TP14" H 4948 2250 50  0000 L CNN
F 1 "TestPoint_Small" H 4948 2205 50  0001 L CNN
F 2 "TestPoint:TestPoint_THTPad_D3.0mm_Drill1.5mm" H 5100 2250 50  0001 C CNN
F 3 "~" H 5100 2250 50  0001 C CNN
	1    4900 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 2250 4900 2150
$Comp
L Connector:TestPoint_Small TP4
U 1 1 619C7302
P 4850 3300
F 0 "TP4" H 4898 3300 50  0000 L CNN
F 1 "TestPoint_Small" H 4898 3255 50  0001 L CNN
F 2 "TestPoint:TestPoint_THTPad_D3.0mm_Drill1.5mm" H 5050 3300 50  0001 C CNN
F 3 "~" H 5050 3300 50  0001 C CNN
	1    4850 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 3300 4850 3200
$Comp
L Connector:TestPoint_Small TP6
U 1 1 619D3E44
P 4850 4350
F 0 "TP6" H 4898 4350 50  0000 L CNN
F 1 "TestPoint_Small" H 4898 4305 50  0001 L CNN
F 2 "TestPoint:TestPoint_THTPad_D3.0mm_Drill1.5mm" H 5050 4350 50  0001 C CNN
F 3 "~" H 5050 4350 50  0001 C CNN
	1    4850 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 4350 4850 4250
$Comp
L Connector:TestPoint_Small TP8
U 1 1 619DEA66
P 4850 5400
F 0 "TP8" H 4898 5400 50  0000 L CNN
F 1 "TestPoint_Small" H 4898 5355 50  0001 L CNN
F 2 "TestPoint:TestPoint_THTPad_D3.0mm_Drill1.5mm" H 5050 5400 50  0001 C CNN
F 3 "~" H 5050 5400 50  0001 C CNN
	1    4850 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 5400 4850 5300
$Comp
L Connector:TestPoint_Small TP10
U 1 1 619E7E9E
P 4850 6450
F 0 "TP10" H 4898 6450 50  0000 L CNN
F 1 "TestPoint_Small" H 4898 6405 50  0001 L CNN
F 2 "TestPoint:TestPoint_THTPad_D3.0mm_Drill1.5mm" H 5050 6450 50  0001 C CNN
F 3 "~" H 5050 6450 50  0001 C CNN
	1    4850 6450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 6450 4850 6350
$Comp
L Connector:TestPoint_Small TP13
U 1 1 619FA20D
P 4900 1800
F 0 "TP13" H 4852 1800 50  0000 R CNN
F 1 "TestPoint_Small" H 4948 1755 50  0001 L CNN
F 2 "TestPoint:TestPoint_THTPad_D3.0mm_Drill1.5mm" H 5100 1800 50  0001 C CNN
F 3 "~" H 5100 1800 50  0001 C CNN
	1    4900 1800
	-1   0    0    1   
$EndComp
Wire Wire Line
	4900 1800 4900 1900
$Comp
L Connector:TestPoint_Small TP3
U 1 1 61A068E2
P 4850 2850
F 0 "TP3" H 4802 2850 50  0000 R CNN
F 1 "TestPoint_Small" H 4898 2805 50  0001 L CNN
F 2 "TestPoint:TestPoint_THTPad_D3.0mm_Drill1.5mm" H 5050 2850 50  0001 C CNN
F 3 "~" H 5050 2850 50  0001 C CNN
	1    4850 2850
	-1   0    0    1   
$EndComp
Wire Wire Line
	4850 2850 4850 2950
$Comp
L Connector:TestPoint_Small TP5
U 1 1 61A1019B
P 4850 3900
F 0 "TP5" H 4802 3900 50  0000 R CNN
F 1 "TestPoint_Small" H 4898 3855 50  0001 L CNN
F 2 "TestPoint:TestPoint_THTPad_D3.0mm_Drill1.5mm" H 5050 3900 50  0001 C CNN
F 3 "~" H 5050 3900 50  0001 C CNN
	1    4850 3900
	-1   0    0    1   
$EndComp
Wire Wire Line
	4850 3900 4850 4000
$Comp
L Connector:TestPoint_Small TP7
U 1 1 61A1C535
P 4850 4950
F 0 "TP7" H 4802 4950 50  0000 R CNN
F 1 "TestPoint_Small" H 4898 4905 50  0001 L CNN
F 2 "TestPoint:TestPoint_THTPad_D3.0mm_Drill1.5mm" H 5050 4950 50  0001 C CNN
F 3 "~" H 5050 4950 50  0001 C CNN
	1    4850 4950
	-1   0    0    1   
$EndComp
Wire Wire Line
	4850 4950 4850 5050
$Comp
L Connector:TestPoint_Small TP9
U 1 1 61A2619D
P 4850 6000
F 0 "TP9" H 4802 6000 50  0000 R CNN
F 1 "TestPoint_Small" H 4898 5955 50  0001 L CNN
F 2 "TestPoint:TestPoint_THTPad_D3.0mm_Drill1.5mm" H 5050 6000 50  0001 C CNN
F 3 "~" H 5050 6000 50  0001 C CNN
	1    4850 6000
	-1   0    0    1   
$EndComp
Wire Wire Line
	4850 6000 4850 6100
Wire Wire Line
	2750 1700 2750 1650
Wire Wire Line
	2750 1400 2750 1450
NoConn ~ 3350 3350
NoConn ~ 3350 3100
NoConn ~ 3350 2300
NoConn ~ 3350 2050
NoConn ~ 3350 1250
NoConn ~ 3350 1000
NoConn ~ 3350 6500
NoConn ~ 3350 6250
NoConn ~ 3350 5450
NoConn ~ 3350 5200
NoConn ~ 3350 4400
NoConn ~ 3350 4150
$EndSCHEMATC
