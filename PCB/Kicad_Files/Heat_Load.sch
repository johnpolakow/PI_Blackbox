EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 2 15
Title "PI BLACKBOX"
Date "2020-01-10"
Rev "3"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Pi_Blackbox-rescue:LT1010-Linear_Technology U2
U 1 1 5CBFDF91
P 5050 3900
F 0 "U2" H 5150 3800 50  0000 L CNN
F 1 "LT1010" H 5050 3700 50  0000 L CNN
F 2 "Package_DIP:DIP-8_W7.62mm_LongPads" H 5750 3550 50  0001 C CNN
F 3 "http://www.analog.com/media/en/technical-documentation/data-sheets/1010fe.pdf" H 5050 3900 50  0001 C CNN
F 4 "Analog Devices" H 5350 4250 50  0001 C CNN "MFN"
F 5 "LT1010" H 5450 4350 50  0001 C CNN "MFP"
	1    5050 3900
	1    0    0    -1  
$EndComp
$Comp
L Transistor_BJT:2N3055 Q2
U 1 1 5CBFDF9F
P 6600 4250
F 0 "Q2" H 6791 4296 50  0000 L CNN
F 1 "2N3055" H 6791 4205 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-3" H 6800 4175 50  0001 L CIN
F 3 "http://www.onsemi.com/pub_link/Collateral/2N3055-D.PDF" H 6600 4250 50  0001 L CNN
	1    6600 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 3900 4750 3900
Wire Wire Line
	4950 4200 4950 4400
Wire Wire Line
	5350 3900 5500 3900
$Comp
L Device:R_Small_US R9
U 1 1 5CBFDFB7
P 5600 3900
F 0 "R9" V 5395 3900 50  0000 C CNN
F 1 "200 Ω" V 5486 3900 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 5600 3900 50  0001 C CNN
F 3 "~" H 5600 3900 50  0001 C CNN
	1    5600 3900
	0    1    1    0   
$EndComp
Wire Wire Line
	5750 3900 5700 3900
Wire Wire Line
	6050 4100 6050 4250
Wire Wire Line
	6050 4250 6200 4250
Wire Wire Line
	4150 4200 4150 4400
Connection ~ 4150 4400
$Comp
L Device:R_Small_US R10
U 1 1 5CBFDFCA
P 6050 3600
F 0 "R10" H 6118 3646 50  0000 L CNN
F 1 "1KΩ" H 6118 3555 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 6050 3600 50  0001 C CNN
F 3 "~" H 6050 3600 50  0001 C CNN
	1    6050 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 3350 4150 3600
Wire Wire Line
	4950 3350 4950 3600
Text Label 6500 2300 2    50   ~ 0
Shunt_P
Text Label 6500 2500 2    50   ~ 0
Shunt_N
$Comp
L Device:C_Small C11
U 1 1 5CBFDFDE
P 7050 2400
F 0 "C11" H 6850 2450 50  0000 L CNN
F 1 ".1uF" H 6800 2350 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7050 2400 50  0001 C CNN
F 3 "~" H 7050 2400 50  0001 C CNN
	1    7050 2400
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7050 2300 7050 2200
Wire Wire Line
	7050 2200 6700 2200
Wire Wire Line
	7050 2500 7050 2600
Wire Wire Line
	7050 2600 6700 2600
Text Notes 6200 6300 2    50   ~ 0
Heat \nLoad
Wire Wire Line
	3900 4000 3950 4000
Text GLabel 5950 3300 0    50   Input ~ 0
LOAD_PS
Wire Wire Line
	5950 3300 6050 3300
Text Label 4000 2450 0    50   ~ 0
V_Feedback
Wire Notes Line style solid
	6450 4000 6450 4500
Wire Notes Line style solid
	6450 4500 7150 4500
Wire Notes Line style solid
	7150 4500 7150 4000
Wire Notes Line style solid
	7150 4000 6450 4000
Wire Wire Line
	4150 4400 4950 4400
$Comp
L power:GND #PWR?
U 1 1 5CBFE015
P 4150 4500
AR Path="/5CBFE015" Ref="#PWR?"  Part="1" 
AR Path="/5CBFDC2A/5CBFE015" Ref="#PWR03"  Part="1" 
F 0 "#PWR03" H 4150 4250 50  0001 C CNN
F 1 "GND" H 4155 4327 50  0000 C CNN
F 2 "" H 4150 4500 50  0001 C CNN
F 3 "" H 4150 4500 50  0001 C CNN
	1    4150 4500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 4500 4150 4400
Text GLabel 3400 3800 0    50   Input ~ 0
V_DAC
Text Notes 3100 3650 0    50   ~ 0
From \nDAC8552
$Comp
L power:GND #PWR09
U 1 1 5CC0D223
P 6700 6550
F 0 "#PWR09" H 6700 6300 50  0001 C CNN
F 1 "GND" H 6705 6377 50  0000 C CNN
F 2 "" H 6700 6550 50  0001 C CNN
F 3 "" H 6700 6550 50  0001 C CNN
	1    6700 6550
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C6
U 1 1 5CA6D345
P 5050 5150
F 0 "C6" H 4800 5200 50  0000 L CNN
F 1 "1uF" H 4800 5100 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5050 5150 50  0001 C CNN
F 3 "~" H 5050 5150 50  0001 C CNN
	1    5050 5150
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C5
U 1 1 5CA6D4E0
P 3200 5200
F 0 "C5" H 2950 5250 50  0000 L CNN
F 1 ".1uF" H 2950 5150 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 3200 5200 50  0001 C CNN
F 3 "~" H 3200 5200 50  0001 C CNN
	1    3200 5200
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C9
U 1 1 5CA70EB4
P 5150 1900
F 0 "C9" H 4900 1950 50  0000 L CNN
F 1 ".1uF" H 4900 1850 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 5150 1900 50  0001 C CNN
F 3 "~" H 5150 1900 50  0001 C CNN
	1    5150 1900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 5CA73702
P 5150 2000
F 0 "#PWR06" H 5150 1750 50  0001 C CNN
F 1 "GND" H 5155 1827 50  0000 C CNN
F 2 "" H 5150 2000 50  0001 C CNN
F 3 "" H 5150 2000 50  0001 C CNN
	1    5150 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 3300 6050 3500
Text Notes 4247 4332 0    50   ~ 0
Autozero OPA
Text Notes 3450 2300 0    50   ~ 0
AD8417 provides feedback \nto LTC2057 -> biases  2N3055 \nto  a current level matching DAC out
Text Notes 5700 6300 2    50   ~ 0
70mA \nmax
$Comp
L Device:R_Small_US R11
U 1 1 5CBFDFBF
P 6300 4250
F 0 "R11" V 6200 4250 50  0000 C CNN
F 1 "50 Ω" V 6400 4250 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 6300 4250 50  0001 C CNN
F 3 "~" H 6300 4250 50  0001 C CNN
	1    6300 4250
	0    1    1    0   
$EndComp
$Comp
L Device:Polyfuse F1
U 1 1 5CE037D4
P 5350 1250
F 0 "F1" V 5450 1200 50  0000 L CNN
F 1 "PTC .15A" V 5250 1050 50  0000 L CNN
F 2 "Resistor_SMD:R_1812_4532Metric_Pad1.30x3.40mm_HandSolder" H 5400 1050 50  0001 L CNN
F 3 "~" H 5350 1250 50  0001 C CNN
	1    5350 1250
	0    -1   -1   0   
$EndComp
$Comp
L Device:C_Small C8
U 1 1 5CE0A5B7
P 5950 1400
F 0 "C8" H 6042 1446 50  0000 L CNN
F 1 "47uF" H 6042 1355 50  0000 L CNN
F 2 "Pi_BlackBox_V4:T495X476K035ATE300" H 5950 1400 50  0001 C CNN
F 3 "~" H 5950 1400 50  0001 C CNN
	1    5950 1400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR05
U 1 1 5CE0C5CF
P 5950 1500
F 0 "#PWR05" H 5950 1250 50  0001 C CNN
F 1 "GND" H 5955 1327 50  0000 C CNN
F 2 "" H 5950 1500 50  0001 C CNN
F 3 "" H 5950 1500 50  0001 C CNN
	1    5950 1500
	1    0    0    -1  
$EndComp
$Comp
L Device:L_Core_Ferrite L1
U 1 1 5CE0E769
P 4850 1250
F 0 "L1" V 4950 1200 50  0000 L CNN
F 1 "100uH" V 4800 1150 50  0000 L CNN
F 2 "Inductor_SMD:L_Wuerth_WE-PD-Typ-LS_Handsoldering" H 4850 1250 50  0001 C CNN
F 3 "~" H 4850 1250 50  0001 C CNN
	1    4850 1250
	0    -1   -1   0   
$EndComp
Text Notes 4750 1400 0    50   ~ 0
1A
Text Notes 5150 1100 0    50   ~ 0
Fuse temp \nsensitive \n0-50C ambient
$Comp
L Device:R_Small_US R12
U 1 1 5CE2FAF9
P 6300 5050
F 0 "R12" V 6226 5036 50  0000 C CNN
F 1 "20KΩ" V 6378 5050 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 6300 5050 50  0001 C CNN
F 3 "~" H 6300 5050 50  0001 C CNN
	1    6300 5050
	0    1    1    0   
$EndComp
Wire Wire Line
	6400 5050 6700 5050
$Comp
L power:GND #PWR08
U 1 1 5CE343D0
P 6000 5100
F 0 "#PWR08" H 6000 4850 50  0001 C CNN
F 1 "GND" H 6005 4927 50  0000 C CNN
F 2 "" H 6000 5100 50  0001 C CNN
F 3 "" H 6000 5100 50  0001 C CNN
	1    6000 5100
	1    0    0    -1  
$EndComp
Wire Notes Line
	6300 6050 6300 6400
Wire Notes Line style solid
	6300 6400 5700 6400
Wire Notes Line style solid
	5700 6400 5700 6050
Wire Notes Line style solid
	5700 6050 6300 6050
Wire Wire Line
	5950 1300 5950 1250
Text Label 7200 5600 0    50   ~ 0
VShunt_P
Text Label 7200 5800 0    50   ~ 0
VShunt_N
$Comp
L Device:C_Small C10
U 1 1 5CE7452C
P 6450 5700
F 0 "C10" H 6250 5750 50  0000 L CNN
F 1 ".1uF" H 6200 5650 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 6450 5700 50  0001 C CNN
F 3 "~" H 6450 5700 50  0001 C CNN
	1    6450 5700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6450 5600 6450 5500
Wire Wire Line
	6450 5800 6450 5900
Wire Wire Line
	6000 5050 6200 5050
$Comp
L Device:C_Small C3
U 1 1 5D1A3813
P 4350 5150
F 0 "C3" H 4100 5200 50  0000 L CNN
F 1 ".1uF" H 4100 5100 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 4350 5150 50  0001 C CNN
F 3 "~" H 4350 5150 50  0001 C CNN
	1    4350 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 5250 4350 5400
Wire Wire Line
	4350 5050 4350 4950
Wire Wire Line
	4500 3100 4500 3350
Wire Notes Line style solid
	6000 6100 6000 6350
Wire Notes Line style solid
	6000 6350 5900 6350
Wire Notes Line style solid
	5900 6350 5900 6100
Wire Notes Line style solid
	5900 6100 6000 6100
Text Notes 5900 6300 1    47   ~ 0
200R
Wire Wire Line
	6300 6250 6300 6400
Wire Wire Line
	6300 6400 5950 6400
Wire Wire Line
	6300 6150 6300 6050
Wire Wire Line
	6300 6050 5950 6050
Text Label 6700 5400 1    47   ~ 0
HLoad
Text Label 6700 4000 1    47   ~ 0
2N3055
Text Label 5480 3900 2    47   ~ 0
buf_out
Text Label 4750 3900 2    47   ~ 0
2057
Text GLabel 6700 1550 2    47   Input ~ 0
LOAD_PS
Text GLabel 4500 3100 0    47   Input ~ 0
LOAD_PS
Text Notes 7919 1727 0    79   ~ 16
Programmable \nCurrent Source 
Wire Wire Line
	6000 5050 6000 5100
Text Label 6200 1250 0    50   ~ 0
HLoad_PS
Text Notes 5800 6900 0    50   ~ 0
Load Current\nvs Power
$Bitmap
Pos 6012 7237
Scale 1.000000
Data
89 50 4E 47 0D 0A 1A 0A 00 00 00 0D 49 48 44 52 00 00 00 8F 00 00 00 D1 08 02 00 00 00 7A 85 76 
43 00 00 00 03 73 42 49 54 08 08 08 DB E1 4F E0 00 00 00 09 70 48 59 73 00 00 0A F0 00 00 0A F0 
01 42 AC 34 98 00 00 16 FB 49 44 41 54 78 9C ED 9D 79 7C 53 55 FA 87 DF 9B BD 4D D3 A4 7B 4B 17 
CA 52 36 29 08 CA 22 B2 88 2C 22 8B C3 BE C8 2A E3 20 FE 44 41 1D 16 41 54 9C F9 31 EC 22 8E AC 
CA 8C 8E 32 28 EB 20 0E 02 95 1D 19 E4 A6 E9 DE 52 E8 5E DA 34 69 93 66 6B D2 24 F7 9E F9 A3 4D 
DB 40 6B 9B 96 34 39 9D F3 7C F8 83 CF C9 4D 72 DF 7C 73 6E EF F2 E4 BD 14 42 08 08 98 C0 F1 F4 
0A 10 5C 80 A4 85 13 24 2D 9C 20 69 E1 04 49 0B 27 48 5A 38 41 D2 C2 09 92 16 4E 90 B4 70 82 A4 
85 13 24 2D 9C 20 69 E1 04 49 0B 27 48 5A 38 41 D2 C2 09 92 16 4E 90 B4 70 82 A4 85 13 ED 95 96 
C5 BC BE AB 9C A2 E4 41 0B F5 BA 76 7A 4B 0F 61 AB DE 19 2F A7 A8 CC BD 05 4E 0A 05 52 6B C7 0B 
E4 94 6F CE 59 AD F3 E2 77 95 BD 29 39 35 B4 BC 88 69 FE B5 DB 29 2D C3 7F CA 0E E5 01 C5 05 CD 
F1 B2 0B AA F6 79 4F 0F C1 17 4C 98 29 04 A8 FA EE BA 9D 6D 30 AC 4F D4 DE B2 01 98 0D DF 27 37 
1C 46 A5 97 B5 59 00 FD E6 4A 22 B8 CD BF 76 BB A4 C5 DA 2F EC D0 96 73 FD B6 EF F2 17 59 F4 3B 
4F 58 ED ED F1 AE 9E 82 EA 36 45 16 03 F0 EB 51 53 65 FD EC 62 53 8F 19 8C FE 3E 7D C5 CC CF 27 
CD E6 BA 61 C4 DC 3A 66 06 10 CD 7A 41 C0 6B C1 4B BB 92 16 6B FB FA 19 39 15 59 F4 F3 7F D4 4B 
06 A5 F0 29 39 45 25 F5 7C A9 F4 5A 39 93 FE F7 C2 E7 BA 28 28 4A 4E F9 A5 BD F8 A1 5E E5 3C A9 
ED 45 DA ED FF 66 45 E3 43 17 CC 0F 9D 2C 81 DB 9F 56 64 5B 5D 78 5B CF E3 62 E1 A2 5E 01 13 C3 
C0 72 43 AB 30 3A 5E C1 62 39 7D D1 2E 1C 16 FA E6 10 AA E4 9C 2E A7 DA 31 AE 33 7D 77 1B 41 AC 
6C 72 17 AA 45 6B 82 5A 0E 6B 3B 3A 9C 06 4E 72 EF 27 73 3F BB 5E AD D1 54 5F DD 9C 25 04 5A 3A 
30 B3 CF 0B 25 E7 EE DA B4 CA AA AF E6 25 01 24 2D FA D9 DE F0 69 69 1F A5 01 28 E6 9D B7 B3 88 
B9 BE 2C 09 20 79 C5 2D C6 85 F7 F5 38 2E 17 6E BF B4 40 01 90 FC BA A3 CC EA CC D2 5E 40 0F 3E 
68 C9 FE 34 1D 20 FD 93 1C B6 66 DC 78 2D 2F 18 E8 88 37 8C 55 2D 5B 11 D7 D2 FA 6E 38 0D A0 98 
7B CE 5E FB 6E 95 95 53 44 34 40 E6 FE 82 DA 01 B3 A2 38 16 E8 CE 6B 4C E6 BA 67 19 0D CB C3 69 
88 28 B8 65 42 08 21 4B 52 71 17 A0 A5 73 74 1A D6 85 77 F6 30 AE 17 AE FD F1 BE 18 E8 2E EF 55 
59 10 42 88 CD FF 3C 03 20 6D CB 5D D6 92 F2 A0 1B D0 C3 FE 66 65 10 42 88 91 BF 9B 02 90 B4 E4 
6A 4B BF BB AD F8 BB 25 9A 3C 90 5B 3B 6F F9 BC 48 29 40 17 C9 D0 B0 DA 01 9E 8C 2F 03 30 A8 D8 
BA 6D 61 C5 A5 B2 6F 94 D0 FD 0F 21 03 7C 01 00 84 7D 82 DF E8 0F BA 53 65 E7 CA 5C 7F 67 0F E3 
42 E1 D2 C1 41 23 84 90 77 46 5F 68 03 60 ED 37 BE 37 43 8C 74 7C 0C 25 EC 26 1D 17 06 F4 51 93 
06 01 D8 AC E7 7F B4 82 44 32 B7 7F 4B 53 70 3D 2D 2E 57 2A 6C F0 7C 0A C0 87 EB EB 78 19 8A 43 
51 00 A8 6E AF 87 B1 9E D9 AE 33 82 68 FE 44 9E 5E 6D 57 AB ED EA 4A CE 98 45 BE 60 D5 EF FC BE 
1A B3 7D 0D 57 0A A7 02 C5 F3 87 00 A4 6B 2F 2B 11 D2 55 1D FD 15 05 8F 95 F5 10 01 F8 8A A6 8F 
E2 5A 7F D1 24 1A 80 29 35 9C CC 02 D1 88 C0 A7 FD 5B BA 0A EE DD 27 B4 DE D3 EC B8 8E 00 2C 9B 
86 A6 84 86 26 87 86 26 87 86 A6 0C 78 B7 0A 00 12 3F AD C8 A8 6E F6 05 B0 85 C3 1B F9 B2 18 A0 
EA FB 5B 8C 31 45 FB 8B 99 33 62 A6 8F 18 00 80 3B 60 B6 58 60 30 9E CE 60 2B 6E 69 93 80 1A 3A 
5F 1C D0 B2 3D 0C 00 68 C9 7E 63 AB 61 93 F6 A9 32 80 33 6E 47 97 77 9E 68 F8 B5 60 B3 F7 E5 AF 
3C A3 FE FC 4E F8 81 E1 1D F5 64 0A 15 31 26 20 1E 4C F4 69 53 72 AC 51 C3 13 CF 7E AA F6 78 2A 
60 48 C0 00 D0 5F 4A 30 4F 4A A9 B2 83 EF FC 91 BC 96 7F 04 6E 4C 0B 55 1A 3F F9 CA 06 11 21 9B 
96 CB 9E 11 3B 3D F4 5C 68 F0 CE 33 65 47 3E 31 FC E5 59 69 60 8B BF 59 78 C1 8F 91 CE EC 51 FC 
E1 75 CD 3F 52 AA E1 C9 B0 61 41 B5 E3 DC 30 C9 F4 3E B0 F6 94 E6 48 19 03 FD 03 9F 0F 77 A1 7E 
37 7E B5 95 67 95 27 75 10 B7 2C 64 A0 F8 E1 87 44 F1 C1 2B E2 C1 78 A6 EC 87 92 8E FB 0B 17 81 
60 CA EF 04 50 AC 39 98 0E BD A6 49 C2 EB 4E 55 F0 F9 E3 27 0B 20 51 75 E4 01 F4 9A ED 1F E5 CA 
7C 71 5B 5A B6 EA 7F EE 34 58 C1 F7 AD C5 22 E1 A3 8F F2 85 F3 DE F6 E3 DA 0D BB FE 69 B5 B9 6B 
0D 3C 0E A7 E7 74 69 38 00 80 60 E2 0B 02 41 83 F1 B8 29 FE C1 00 00 C2 69 93 84 82 C6 9F DB 38 
14 22 BF DF C2 87 8E FA 47 BE 63 42 D2 C2 09 92 16 4E 50 83 81 F6 F4 3A 10 5A 0A 99 5B 38 41 D2 
C2 09 92 16 4E 90 E3 2D 9C 20 73 0B 27 48 5A 38 41 D2 C2 09 92 16 4E 90 B4 70 A2 F5 69 59 8B 74 
1B 9F 4F A6 28 79 9F AD 96 47 AF 7A 98 32 35 AB 27 65 84 0A E4 14 25 F7 8D CA 9C FB 67 5D 31 5E 
0E E1 6F 81 34 B7 D5 6F 8C 4F 0F E6 C9 29 4A CE 0B 4A 1F F3 9A FA 97 72 A7 5D 6B 77 95 DF 2A 63 
CB 9E F2 B7 FC 78 3E 4D C9 12 01 E8 DE 5B CC 56 E7 C7 AD 79 EA F1 62 1A 24 99 4B 3F 56 1D FE B2 
6C C3 9C 34 3E D0 91 4B 75 E5 58 59 84 4D A1 BD 5C D8 0D 68 90 66 2E DA A0 DC 7F A0 6C E3 FC 74 
11 D0 D0 F7 81 DC 54 BB 80 FB CA 6F 4D 5A 96 A4 E2 AE A0 78 76 6D 65 E6 E5 FC D0 46 D2 B2 5F 9C 
AF 00 48 7B 3F D1 B1 76 8C ED DC E2 24 80 D4 0D C9 18 49 84 4D 60 B3 7C 3A 80 06 2A 73 D7 5D 47 
2D AC FD CA B2 64 00 C5 DC 84 5A F5 D3 7D E5 B7 66 4B C8 09 96 6C BD D9 F7 CA 16 69 4C 23 57 85 
01 0C 55 5F FC C0 C0 80 D0 DF C7 3B 5E 9C C3 1B B5 22 30 12 AA BF 3D 62 B6 B4 7E 2B E0 25 70 E2 
57 44 6D 3B 18 BD B8 BB C3 A7 A0 B8 FD 5F 14 51 C0 E4 15 B1 2C B8 B7 FC D6 58 34 FC 48 FF 99 91 
00 00 8D 6E 8A AD 25 A6 64 3D 84 3C ED 13 DA E0 B5 7D BA 4A 7A 72 54 97 6E 58 F4 C8 57 84 B5 36 
C3 E3 8F 5E 1A 36 DA 69 08 15 25 5A 11 F0 FA 76 E7 72 DC 5C FE E3 DF 27 B4 6B AC 1A 80 80 68 9E 
D3 17 41 C8 8B 92 02 54 58 35 1D 4E C3 B0 64 AA DF D8 5A CD 1D 1C BE 7A 30 07 DC 5C FE E3 4F 0B 
D9 58 1B 00 5F 44 39 7D 87 28 CA 87 0F 60 63 6D 1D EB AC A4 29 4D 3D 67 64 D1 75 59 C0 D7 C7 42 
7B 0A 00 DC 5C FE E3 4F 8B E2 73 04 00 56 B3 F3 D9 62 C4 56 D9 00 04 1C 41 C7 39 C0 43 85 27 0B 
87 3C 59 78 26 28 E4 38 DD E5 E5 98 DA 74 DC 5A FE E3 FF F0 F8 41 82 20 00 4D BE BD E1 A4 47 66 
7B 61 25 50 21 C2 40 B7 CA C1 ED 06 62 E8 AD F7 FA CE 50 97 4D 88 A6 7F 8D 99 11 5D 3F 91 DC 5A 
BE 1B D2 EA 24 7E 3A 10 2A EE 98 4A 1B AC 6F D5 5D 7D 26 82 B8 B1 3E 52 AC 77 31 6A 40 4C E2 B6 
FB 23 D7 19 63 57 76 4F 3E 1D FA 94 F3 6F 0E DC 5A BE 1B 36 4C 7E E2 3F CC E4 43 9A 6A EF 1D A6 
76 6B C0 D8 CE 6E D3 AA C0 E7 0F 73 5C 93 1D BD 13 F5 D9 C2 09 EB 8C 51 2B E3 AE EC 92 76 7A 74 
AE B8 B3 FC 56 CC 4C A4 BA A9 3D 99 CC B0 00 D6 1C B3 0E 80 B9 A1 D9 2F E1 73 01 44 DD A4 0B 5F 
10 F0 81 F3 CC 47 D1 B3 4E E4 7E 32 36 5B BD 3A 68 64 27 74 F7 47 D5 CE 1F 98 DE 6B 3A BF 16 87 
FF CC AA 32 6D 7E 43 A3 A6 7C 66 44 59 8E EE 77 3A 7C 12 F7 94 BD 3C 86 EF DE F2 5D 3F A0 66 6E 
2D 4F 06 A0 1F FD C7 7F B1 52 E7 58 C8 9C AB DD 38 2D 23 4C 40 03 D0 7E 5D B2 7E BF C7 A0 B6 FF 
D6 8B E2 02 53 5A 3E A4 B1 DA 01 68 F1 0C 9D DE B1 98 9B CA 27 57 FA 71 A2 E3 EC 50 FF 2F 40 D2 
C2 09 92 16 4E 90 B4 70 82 A4 85 13 24 2D 9C 20 69 E1 04 49 0B 27 48 5A 38 D1 BA B4 3C A7 68 79 
03 88 CD 3A 56 32 73 50 AA 1F 25 A7 28 39 2F 30 6D C4 22 E5 B9 42 6F 35 D4 3C A8 68 79 01 6C CE 
BE BB 22 A0 83 C7 15 ED 3F A9 BB 7C A9 F2 C8 F6 FC 01 42 1A 82 72 4F 95 D5 2E E1 4D 86 9A 47 15 
2D CF 53 6D DE 14 47 83 7F CE 4F 95 75 43 6C FE 5F 33 00 E8 11 47 6C 2C 42 DE 66 A8 79 52 D1 F2 
06 B8 1C 00 1E 47 54 DF 06 97 12 FA 53 00 14 BF E6 EA 93 3B CB 77 3D 2D 1E 7F F4 D2 B0 D5 AF 8A 
03 EB 9F DA 42 45 0B F2 6F 58 F4 B8 9F F1 17 08 17 BE 27 95 68 34 6F AE D7 28 4A 18 8B 99 29 B8 
55 BE FA 7D 13 74 0E DE 30 96 47 B9 B9 FC C7 A0 49 38 14 AD A8 16 2A 5A A1 78 5F 3F A6 62 16 77 
4B 91 14 CF 98 9F 37 F0 B3 DA A1 90 B1 9D 2E 1F 09 7F 2E 00 C0 CD E5 B7 75 0F BE 9D 15 2D 6F 40 
73 B5 64 C6 3C 55 56 7C C8 EE E3 71 D7 AE C4 7D B3 39 30 E4 6A C9 A4 69 CA 3B 06 00 37 97 DF 96 
B9 85 0A 4F 16 4D 9C AD 4E EF 1E 72 FC 62 74 9D F7 D3 C1 0D 35 B3 E9 E3 05 CA C4 E0 90 AB 09 31 
23 6B FC 99 51 FE E3 FB A0 EE 53 4B 96 EE 0D 90 AF 15 79 A5 A1 E6 21 45 CB E3 58 0B 0D E7 8B 41 
36 3A 60 60 03 D5 29 78 98 AC 2F 40 DA D9 2A 1D F2 42 43 CD 73 8A 96 E7 41 08 01 30 CE 2D 81 91 
1D D5 0D 78 9D A1 E6 41 45 CB E3 08 22 FD 06 07 82 E1 AA 56 AE AF 1F 54 DF D0 A6 01 C4 3D EF E3 
4F B9 B7 7C D7 2D 9A 2A D3 DB BD B2 76 17 FB 2C DF 16 12 EF EB F4 88 43 D1 02 A6 54 3B 2F 3E F7 
58 95 EF 82 7A 45 CB DA 7B 4D AF DB 5B C4 12 DC E7 16 A0 9C FD F7 FB BD AE A7 06 05 6F 5A 25 EB 
17 02 4A B9 76 FB 07 15 A9 01 81 27 93 63 A7 85 53 E0 D6 F2 5D 3D 9C F6 AC A2 E5 15 B0 4C CE E9 
92 D9 83 53 FC 80 06 A0 39 B2 D4 91 AF 28 13 4A 9C CE 53 10 43 8D 40 AE 98 60 05 49 0B 27 48 5A 
38 41 D2 C2 09 92 16 4E 90 B4 70 82 A4 85 13 24 2D 9C 20 69 E1 44 2B 0D B5 92 84 B2 C5 23 D2 A4 
1C 39 45 C9 45 E1 19 93 DF AE 50 38 DF 74 1A 77 43 ED B7 3A C4 61 65 A8 B1 A5 27 73 C3 80 86 E8 
EC B7 B6 A8 BE 38 A0 5C 37 2B 8D 07 34 77 50 69 BA A5 76 09 BC 0D B5 66 3A C4 E1 65 A8 59 AA D6 
77 A5 41 9A 73 42 E9 18 61 6C 67 E7 2A 00 92 5E B9 5E B3 3A 78 1B 6A CD 74 88 C3 CE 50 1B F4 56 
A7 FF DF D3 E9 C5 B0 BA 01 DE A0 C9 22 00 FB BD 12 16 01 F6 86 5A 33 1D E2 30 33 D4 84 C2 A9 2B 
23 D6 2F 12 F9 D4 0F B1 B9 B7 AD 00 FC 27 63 39 EE 56 B4 DA 01 7E A4 FF CC 61 BC 26 AF C8 E3 6A 
A8 D9 99 B2 52 BB 56 6D A5 4F 2A DF F9 CC D6 E9 E5 AE EB 06 12 43 CD BD E5 B7 3E 2D 6B B6 6A C4 
13 25 F7 00 00 78 23 FE D8 ED C8 66 59 24 0F E0 7F C7 50 EB 1F B2 7B AD 6C 60 30 14 FE 52 B1 F9 
C3 92 49 D3 E0 CA B9 88 41 12 6F 35 D4 78 31 81 07 FE E5 A3 D6 D9 EE DF AE 3C B0 23 A7 FB CF 61 
67 CE 47 8E 0F A1 88 A1 E6 7D 86 1A 00 C7 4F 38 FA 25 D9 EC 85 21 EB FF 1A A7 F8 29 48 AA 28 5B 
FC 41 55 15 31 D4 BC CA 50 B3 AB 8C DF EC 29 DB 7F C9 D6 50 D2 0A 18 E8 1F 07 A0 4C B2 E8 59 62 
A8 79 93 A1 46 55 5B 3E 5F 55 FC FA 72 55 92 A9 7E B0 FC 56 65 3A 40 50 2F A1 84 43 0C 35 AF 32 
D4 10 73 E3 8F 59 23 76 59 F8 3D 65 2B 96 F8 F7 0E 44 CA 64 DD 17 7B F5 85 02 BF 4F 52 7A AC EA 
E9 66 45 CB ED 34 EC 10 57 B1 6E 97 C9 6F 72 C4 87 2F 36 EC 10 87 95 A1 86 10 42 8C 9D 3E 5C 34 
B1 6F 92 A0 C6 4D F3 4B 19 34 A3 F8 68 3A D3 F0 48 1D 5B 43 AD 05 1D E2 88 A1 46 68 09 B8 EF 50 
FF 6F 41 D2 C2 09 92 16 4E 90 B4 70 82 A4 85 13 24 2D 9C 20 69 E1 04 49 0B 27 48 5A 38 D1 D6 B4 
58 8D FE D5 08 39 45 A5 AE 4D 62 1B 8E E3 6C A8 35 EB DF E1 75 97 CF 3A 18 DB F9 DF D7 9C 55 4B 
59 A3 A8 F7 AF 70 36 D4 9A F7 EF 30 BB CB 67 1D 15 E7 F3 C3 41 31 74 62 8A 73 5A 38 1B 6A CD FA 
77 D8 DD E5 B3 06 56 A3 5F BD B8 DC 38 29 7A E7 8B CE 17 44 F1 36 D4 9A F3 EF B0 BB CB 27 00 00 
6B 4F 58 9D 7F D8 E0 FF F7 7D 81 D1 3F AA 1A 3E 82 F7 5D 3E 85 C2 A9 2B 23 A6 3A 0D 39 F9 77 9E 
BD CB 67 2B D3 D2 24 3C 58 7C 98 19 F7 65 E7 F9 D1 50 EA FC 50 07 31 D4 9A F0 EF 1E A5 3D 5B C8 
B5 26 AD 9A 6D 60 E5 98 CE 07 17 09 78 F0 F0 E5 B1 8E 61 A8 35 E5 DF 3D 84 29 4D FD F2 E8 A2 EB 
B2 80 6F DB A5 85 9C EB 69 B1 F6 8B AB F3 0F 6B 25 FB 0F 05 C5 36 F6 EC 8E 61 A8 35 E5 DF 35 58 
C4 03 2D E4 5C 4E 4B 73 F1 C1 E2 C3 F6 91 BB A3 67 85 20 A3 11 01 20 63 35 02 00 AB 89 35 1A C1 
C7 8F 53 A3 68 95 E5 DB 6D 00 75 93 BE 56 D1 8A C7 C6 50 E3 F8 09 47 BF 24 04 00 58 18 B2 7C 4A 
7E EF 09 65 8B 3F 08 C8 D9 27 AE ED 95 84 18 7A 5B CE F3 EB 0C C2 49 D1 F4 11 A7 BE 64 6E 2D DF 
D5 AC D9 CC 63 95 65 80 AE AD CA 08 92 28 24 12 85 44 92 D4 67 95 19 C0 BA 7B 78 B2 44 72 EF 94 
06 6F 43 AD 59 FF 0E C0 A3 2D E4 5C DD E5 D7 DD 33 5E BD A2 BF D2 E0 DF 77 AB 52 01 92 E6 1C D4 
5D B9 5E 55 6E 43 08 31 D7 97 25 03 A4 BC 7D D3 5E 7B 7C 61 B7 1E 7D 49 01 90 BE FD AE B7 1F 6F 
D9 0B D5 43 29 1A E2 8A EF 18 EB 07 55 FF CA 91 01 1D B4 C4 50 33 A6 3A 93 1B 02 74 DC 4A 7D 45 
E3 47 BB 6E 2C BF ED 16 0D 2A DA 9F 15 F3 BA 7D 8D E2 89 AD 4F D6 CE 54 8C 0D B5 66 FD 3B CF B6 
90 6B 63 DA 08 B1 85 FB 32 1E 3A F3 84 30 36 D4 9A F1 EF C8 5D 3E 09 2D 05 93 1D 6A 02 00 90 B4 
F0 82 A4 85 13 24 2D 9C 20 69 E1 04 49 0B 27 48 5A 38 41 D2 C2 09 92 16 4E B4 22 2D 94 BD 35 9D 
A2 E4 8F FC BB 7B 5C 53 BF 10 B6 86 DA E3 A9 CE 4D E5 B7 E2 7A 0B 32 AA 59 00 FE AC 3F 85 3F 17 
D8 E0 24 A5 40 F0 94 B8 F6 BF B6 FC F2 E9 83 0A 2E 70 C4 4B 37 C6 0C 8F 44 39 17 D4 DB 36 DE BF 
91 17 97 7C C8 3F C8 DB 27 F3 63 A8 CE 8D E5 B7 E2 AC E7 D5 45 49 00 59 47 54 4D 2D 80 B3 A1 F6 
18 AA F3 2E 43 0D 19 CB 19 10 70 A5 4D B4 18 C3 DC 50 6B 73 75 DE D5 43 0D A1 CA 4A 04 62 9E 98 
0B 80 90 C5 C4 DA 9D 4F E2 E3 DD 43 AD CD D5 B9 B5 7C D7 D3 62 98 72 23 80 D5 72 60 41 66 28 27 
D1 C7 4F C1 E7 24 F5 9A 54 FC 7D 76 8D 1C D9 BC A2 E5 D5 B4 B9 3A B7 96 EF FA 5E 06 C3 AA 8D 00 
26 D3 2F D5 A1 EF FD 23 A2 A7 94 BD 7F A9 62 CB EE B2 39 D7 2C A6 B4 6E AF 74 A6 F0 36 D4 DA 5C 
9D 97 19 6A 02 D1 3B 57 FB 2E 05 6E 64 24 4F 50 B3 46 53 02 A6 0F B8 DF 63 B1 6E FD B6 AA 39 9F 
8B F1 36 D4 DA 5C 9D 97 F5 50 A3 A8 80 28 61 97 28 47 31 00 00 54 D4 A4 E0 21 14 28 6F 9B 35 0C 
E6 3D D4 DA 5C 9D 77 F5 50 03 00 9B C1 5E 56 E9 F4 DD 61 AD AC 19 01 88 38 02 0E DE 86 1A B4 B9 
3A EF EA A1 66 CF 53 0D F5 4F 8E 18 AF CA AE AE 2F 27 E3 2B D5 6D 80 7E 53 7D 03 DC DC 44 CC DD 
3C 86 EA DC 5A BE CB 47 68 8C ED C2 F2 14 00 5A 3A 24 EF 83 4F D5 5F 1E 50 AE 9D 9D 2E 02 1A 7A 
17 5D D3 3A 0E 20 4B 34 B3 82 68 F0 C9 58 F0 41 D9 C1 FD CA 77 A7 A4 00 D0 BD D7 18 F5 18 1C 1C 
3F 86 EA DC 57 7E AB 0C 35 9B ED DA 9E 82 B1 BD 92 F8 40 03 D0 BE 91 19 53 D7 54 24 E9 9C 16 C1 
D8 50 7B 1C D5 11 43 8D 40 AE 98 60 05 49 0B 27 48 5A 38 41 D2 C2 09 92 16 4E 90 B4 70 82 A4 85 
13 24 2D 9C 20 69 E1 04 49 0B 27 5A 9B 96 CD 76 65 67 FE B3 9D 15 14 25 A7 7C 53 87 2C 28 BB 5C 
D6 2E 2D DF DC 0C 52 6B 9E 6D 44 26 94 53 94 DC 6F A6 DE E0 58 CA 53 1D EF 5A 75 9E 90 B1 FF F8 
5A E6 E4 2F AD 5D A7 86 BF 35 49 68 4B D1 6C FB CC A0 EE 13 21 BF D3 69 A0 2F 00 80 2D BF 7C 72 
DF 82 0B 1C F1 D2 D5 41 B5 42 DD 77 96 D0 A5 38 F8 84 96 EA 1F BE D1 17 39 7F B2 D6 3C CD 86 1D 
C6 D8 4D 7D 12 3F F0 11 02 54 5E 29 7A 7A B4 2A 47 2A 5E B4 22 60 58 0C F5 E0 5A F9 F6 6F CD 96 
BE 11 F2 DB EE 2F BF 15 67 82 0D 37 0A 22 80 EE B4 4C E7 68 41 C0 A6 FF 25 43 16 96 F5 91 A2 23 
DC 93 F5 61 AC 96 CF 9E 95 43 6C D1 CD 9A 9F 80 7B B4 E3 5D 2B D2 B2 27 BC AC 00 C8 D8 9B DF C4 
7B EB F5 73 FC 69 18 A0 CA B3 D5 8F 55 DD 29 8C 04 3A 76 AD C9 DC BA D5 F4 18 6C FE 17 77 45 90 
FC 6A 82 A3 F9 85 CD 7A E9 4B E5 B6 43 C6 86 CD 32 B4 A7 EE 52 40 0F F9 9B 95 41 EE 2D DF 75 4F 
A0 DA 7A E9 16 03 71 B2 91 11 14 00 00 02 44 41 C3 EB D7 78 77 BC 73 86 55 E9 DE 7D D7 C0 FF 5D 
D7 3F 8F E6 D6 AE B5 47 3B DE B9 BE 1D AD B6 A5 94 00 84 0B B4 DF 15 8D 8B 53 50 1C 39 87 52 74 
1B 53 F4 55 5A 87 F0 09 9D 60 E5 DB 8A 4E E8 7C 37 6E 95 85 35 FD 39 39 3A DE 85 B7 B0 E3 5D 5B 
70 3D 2D 3B A3 AB 06 A0 1F 4C DD 64 1D B2 A6 CB 4F 09 DD BF DD 12 E0 73 4D B5 64 48 CE E1 7C 04 
1D A5 E3 1D 00 30 A5 95 1B 3F B7 FA CF EC B4 B4 47 93 D3 C1 94 A6 9E 33 B2 E8 BA 2C E0 6B 2F ED 
78 C7 A1 F8 1C 00 AB 70 F3 CF 5D 97 75 A6 00 00 C6 48 C7 F5 64 BB 4F D3 7E B4 C7 3C 7F 97 2F DE 
3E 61 3D 28 F7 5B E5 79 0B FF CD 3F 4A 82 1A 0F CB 03 1D EF 5C 7F 36 9F 17 23 03 88 95 0C 0B AF 
2F 22 64 64 C0 40 0A 8A FF 63 D1 BB F9 A6 A4 ED 47 B5 E5 9B 03 66 88 09 7C A5 7F 63 1F 11 62 E8 
AD F7 FA CE 50 97 4D 88 A6 7F 8D A9 8B 0A DC 7C 4B 5A D7 D3 F2 11 8E EA 05 A0 A9 2E 6F B0 3A C8 
8E 6C 08 28 21 C5 75 B3 50 D7 6E D8 0A 74 C7 EF 43 C8 78 59 0F D1 23 8F 79 AE E3 9D EB 69 71 78 
E3 96 49 04 DA CA 1D A7 AD 8E 26 7E A8 E8 87 F2 3B 00 7D 27 FA F8 03 DE 3E 61 1D 1A 5A 97 09 D0 
7B AC C8 F7 91 87 D4 67 0B 27 AC 33 46 AD 8C BB B2 4B DA E9 D1 B9 E2 CE F2 5B 31 33 A9 C8 39 D1 
7F 3E 90 B9 66 61 D6 84 5F C3 E6 3E C5 D5 26 6A 77 ED 31 58 A3 82 B7 2D 15 F1 01 00 38 CF 7C 14 
3D EB 44 EE 27 63 B3 D5 F5 2D DF 98 DE 6B 3A BF 16 87 C9 CC 02 F6 41 A2 15 01 FF 89 CE 9C 87 D7 
B8 CA B4 F9 0D 8D 9A F2 99 11 65 39 BA DF E9 E7 58 8E 8E 77 EE 2C BF 75 87 69 8C BE EA EB 55 D9 
BD 03 E5 00 34 F8 A5 0E 5F A2 BC AC 6C 8F 9B 92 B6 17 CC A5 79 0A 80 D4 8D A9 0F 9F 01 20 1D EF 
08 2D 05 9B 1D 6A 02 90 B4 F0 82 A4 85 13 24 2D 9C 20 69 E1 04 49 0B 27 48 5A 38 41 D2 C2 09 92 
16 4E B8 9C 56 CB 1C 2E 5C 0D 35 00 A8 B9 27 EB 12 C7 3D 59 A5 DD B3 97 1F 30 55 36 BC E1 2C 62 
B3 8E 95 CC 1C 94 EA 47 C9 29 4A CE 0B 4C 1B B1 48 79 AE B0 3D 0C 35 97 CF EA 52 12 F1 BA 43 31 
8D 3A 5C 9D FB F1 6B CE 31 63 DD F1 4E 79 2A 7F E0 74 4D 59 84 FF 8A 2D E1 4F C9 EC 77 FE 59 B6 
77 79 D6 1D 55 EF EB 1B 7D 7D 01 00 50 EE 81 FB 03 5E 37 F8 8D 0B DB 79 D2 BF A7 0C 95 CA 2B B7 
BF FF 60 E2 BF CD A7 32 BA 4C 0D 05 F0 B2 8E 77 8F F0 90 C3 85 B5 A1 66 A9 7A AF 0B 0D 3E D9 5F 
15 39 56 D5 6A 39 38 5A 0E BC BB 87 6B 46 AA CD 9B E2 68 F0 CF F9 A9 B2 EE 39 6C FE 5F 33 00 E8 
11 47 6C 2C 42 DE D6 F1 EE E1 B8 0B BE 2E 58 7D 93 F7 EA 17 11 CF 48 00 00 EF 8E 77 6C 85 29 21 
0F 78 C3 43 26 47 39 AE 6E F0 85 B3 57 4B C5 76 C3 E1 CB F6 9A CD 21 97 03 C0 E3 88 B8 75 4F A2 
84 FE 14 00 C5 AF D9 4E 79 57 C7 3B 67 1C 0E 57 74 9D C3 85 75 C7 3B 64 47 76 00 9E 0F A7 E1 5F 
08 61 B8 30 08 20 FB A6 D5 02 00 02 E1 C2 F7 A4 12 8D E6 CD F5 1A 45 09 63 31 33 05 B7 CA 57 BF 
6F 82 CE C1 1B C6 F2 28 37 97 DF C6 B4 1A 71 B8 B0 36 D4 B8 81 3E FD 02 C1 22 D7 65 98 EA C6 90 
3A D1 F4 00 A0 B2 C8 6E 07 00 A0 62 16 77 4B 39 11 C2 3F 94 37 30 32 C9 C7 37 29 76 58 C1 F9 1E 
9D 2E DF 89 7E 3E 00 C0 EB 0C B5 06 34 EA 70 E1 6D A8 F9 F9 BE F3 A6 08 1E A8 66 2E 2E BB 98 65 
53 3F B0 5C 3E 54 F8 BB 35 66 06 80 B1 D6 DE 7E 56 73 B5 64 C6 3C 55 56 7C C8 EE E3 71 D7 AE C4 
7D B3 39 30 E4 6A C9 A4 69 CA 3B 06 00 AF 33 D4 EA 69 DC E1 C2 DC 50 E3 F4 5B 1F 77 42 9B FB CA 
9E E2 F1 27 8A 01 80 1B 2B FD F8 40 04 77 56 71 56 00 87 0B 00 66 D3 C7 0B 94 89 C1 21 57 13 62 
46 D6 F8 33 A3 FC C7 F7 41 DD A7 96 2C DD 1B 20 5F 2B F2 32 43 AD 8E 26 1C 2E EC 0D 35 81 60 FA 
A7 BD 2A 2A E3 93 6F F7 4A CC EE 6F CA ED FE 76 AC 55 09 D0 A9 1F 5F 00 60 2D 34 9C 2F 06 D9 E8 
80 81 0D 54 A7 E0 61 B2 BE 00 69 67 AB 74 6E 16 F4 5A 9F 56 53 0E 57 C7 30 D4 78 52 41 BF C1 E2 
01 71 3C 21 85 0A 2E EA 8B 81 F7 EC 28 81 00 00 10 42 00 8C DD 69 E1 9A 7D 93 1A BC CC 50 73 D0 
A4 C3 85 B5 A1 C6 DA 4F CF 4D 15 06 DE 3F AA 74 AC BB 4A F7 A7 9D 16 E8 1C F4 7F 4F 71 00 40 10 
E9 37 38 10 0C 57 B5 72 7D FD 93 D4 37 B4 69 00 71 CF FB F8 BB BB E1 5F 6B 0F D4 18 F9 BB 29 00 
C9 AF DF 6A E4 36 B2 18 77 BC 43 48 F5 AF DC 40 A0 B9 3D 73 36 EC 51 1F DA 55 34 29 86 06 48 7D 
33 C1 E6 A8 93 BD BF 2F DB 17 68 F1 A0 FC 1D DF 56 5E B8 50 F9 F5 5F F2 E2 F9 34 84 E6 9E 2C 75 
DC 31 D7 BB 3A DE 21 F4 1B 0E 57 0D 18 1B 6A 2C 93 75 A4 68 42 2F 05 05 34 80 A2 EB A8 FC CF 6E 
DA EC CE 0B E4 9C 2E 99 3D 38 C5 0F 68 00 9A 23 4B 1D F9 8A 32 A1 A4 3D 04 3D 62 A8 E1 84 B7 EF 
50 13 1A 42 D2 C2 09 92 16 4E 90 B4 70 82 A4 85 13 24 2D 9C 20 69 E1 04 49 0B 27 48 5A 38 41 D2 
C2 89 FF 02 9B 54 4A 87 38 5B 80 4F 00 00 00 00 49 45 4E 44 AE 42 60 82 
EndData
$EndBitmap
$Comp
L Device:C_Small C2
U 1 1 5D453DD7
P 3500 4050
F 0 "C2" H 3250 4100 50  0000 L CNN
F 1 "1uF" H 3250 4000 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3500 4050 50  0001 C CNN
F 3 "~" H 3500 4050 50  0001 C CNN
	1    3500 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 3950 3500 3800
Wire Wire Line
	3200 5100 3200 5000
Wire Wire Line
	5050 5050 5050 4950
Wire Wire Line
	3200 5300 3200 5450
Wire Wire Line
	5050 5250 5050 5400
$Comp
L power:GND #PWR04
U 1 1 5DC67D86
P 4900 5500
F 0 "#PWR04" H 4900 5250 50  0001 C CNN
F 1 "GND" H 4905 5327 50  0000 C CNN
F 2 "" H 4900 5500 50  0001 C CNN
F 3 "" H 4900 5500 50  0001 C CNN
	1    4900 5500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 5500 4900 5400
Connection ~ 4900 5400
Wire Wire Line
	4900 5400 5050 5400
Text GLabel 4700 4700 0    47   Input ~ 0
LOAD_PS
Wire Wire Line
	4700 4700 4900 4700
Wire Wire Line
	4900 4700 4900 4950
Connection ~ 4900 4950
Wire Wire Line
	4900 4950 5050 4950
Text Notes 3500 5250 0    51   ~ 0
Decoupling for\nU1 & U2
Wire Notes Line
	5045 6040 5345 6190
Wire Notes Line
	5345 6190 5245 6190
Wire Notes Line
	5345 6190 5295 6115
Text Notes 4820 6015 0    55   ~ 0
DEWAR
Wire Wire Line
	6700 2600 6700 4050
Text Notes 7150 4300 0    51   ~ 0
2N3055 = gain of 20
Text Notes 4650 2450 0    51   ~ 0
Gain of 60
Wire Wire Line
	6850 5500 6850 5600
$Comp
L Device:R_Small_US R14
U 1 1 5D162BDE
P 6700 5700
F 0 "R14" H 6800 5750 50  0000 L CNN
F 1 "390 mΩ" H 6750 5650 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 6700 5700 50  0001 C CNN
F 3 "~" H 6700 5700 50  0001 C CNN
	1    6700 5700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 5600 6700 5500
Wire Wire Line
	6700 5800 6700 5900
Connection ~ 6700 5900
Wire Wire Line
	6700 5900 6850 5900
Wire Wire Line
	6850 5900 6850 5800
$Comp
L Device:R_Small_US R13
U 1 1 5D1A01FD
P 6700 2400
F 0 "R13" H 6768 2446 50  0000 L CNN
F 1 "1R" H 6768 2355 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" H 6700 2400 50  0001 C CNN
F 3 "~" H 6700 2400 50  0001 C CNN
	1    6700 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6100 2300 6700 2300
Wire Wire Line
	6700 2300 6700 2200
Connection ~ 6700 2300
Connection ~ 6700 2200
Wire Wire Line
	6100 2500 6700 2500
Wire Wire Line
	6700 2500 6700 2600
Connection ~ 6700 2500
Connection ~ 6700 2600
$Comp
L power:GNDA #PWR?
U 1 1 5E3C3FD3
P 4400 7000
AR Path="/5D35BFAB/5E3C3FD3" Ref="#PWR?"  Part="1" 
AR Path="/5CBFDC2A/5E3C3FD3" Ref="#PWR0113"  Part="1" 
F 0 "#PWR0113" H 4400 6750 50  0001 C CNN
F 1 "GNDA" H 4405 6827 50  0000 C CNN
F 2 "" H 4400 7000 50  0001 C CNN
F 3 "" H 4400 7000 50  0001 C CNN
	1    4400 7000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0117
U 1 1 5E3C8717
P 4050 7000
F 0 "#PWR0117" H 4050 6750 50  0001 C CNN
F 1 "GND" H 4055 6827 50  0000 C CNN
F 2 "" H 4050 7000 50  0001 C CNN
F 3 "" H 4050 7000 50  0001 C CNN
	1    4050 7000
	1    0    0    -1  
$EndComp
$Comp
L Device:Ferrite_Bead_Small FB10
U 1 1 5E3C879D
P 4200 6850
F 0 "FB10" V 4055 6850 50  0000 C CNN
F 1 "FB" V 4054 6850 50  0001 C CNN
F 2 "Inductor_SMD:L_1210_3225Metric_Pad1.42x2.65mm_HandSolder" V 4130 6850 50  0001 C CNN
F 3 "~" H 4200 6850 50  0001 C CNN
	1    4200 6850
	0    1    1    0   
$EndComp
Wire Wire Line
	4100 6850 4050 6850
Wire Wire Line
	4050 6850 4050 7000
Wire Wire Line
	4300 6850 4400 6850
Wire Wire Line
	4400 6850 4400 7000
NoConn ~ 5050 3650
NoConn ~ 4250 3650
NoConn ~ 4250 4150
$Sheet
S 7650 5500 1200 900 
U 5E1246BD
F0 "HLoad_Power_Meas" 51
F1 "HLoad_Power_Meas.sch" 51
F2 "VShunt_P" I L 7650 5600 51 
F3 "VShunt_N" I L 7650 5800 51 
F4 "V_HLoad_P" I L 7650 6150 51 
F5 "V_HLoad_N" I L 7650 6300 51 
$EndSheet
Wire Wire Line
	7150 6300 7200 6300
Wire Wire Line
	7150 6150 7200 6150
Wire Wire Line
	6850 5600 7650 5600
Wire Wire Line
	6850 5800 7650 5800
Wire Wire Line
	3500 3800 3950 3800
Wire Wire Line
	3500 4150 3500 4400
Wire Wire Line
	3400 3800 3500 3800
Connection ~ 3500 3800
$Comp
L Device:C_Small C12
U 1 1 5E311ACB
P 6500 1400
F 0 "C12" H 6250 1450 50  0000 L CNN
F 1 ".1uF" H 6250 1350 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 6500 1400 50  0001 C CNN
F 3 "~" H 6500 1400 50  0001 C CNN
	1    6500 1400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR011
U 1 1 5E311AD1
P 6500 1500
F 0 "#PWR011" H 6500 1250 50  0001 C CNN
F 1 "GND" H 6505 1327 50  0000 C CNN
F 2 "" H 6500 1500 50  0001 C CNN
F 3 "" H 6500 1500 50  0001 C CNN
	1    6500 1500
	1    0    0    -1  
$EndComp
$Comp
L Device:L_Core_Ferrite L15
U 1 1 5E356ED3
P 6700 4800
F 0 "L15" H 6788 4846 50  0000 L CNN
F 1 "1mH" H 6788 4755 50  0000 L CNN
F 2 "Pi_BlackBox_V4:RLB9012-222KL" H 6700 4800 50  0001 C CNN
F 3 "~" H 6700 4800 50  0001 C CNN
	1    6700 4800
	1    0    0    -1  
$EndComp
Text Notes 6400 4900 0    50   ~ 0
240 mA\nrated
Connection ~ 6700 5500
Wire Wire Line
	6700 5500 6850 5500
Text Notes 7350 4950 0    47   ~ 0
R12 protects 2N3055 in case \nheat load is open circuit, and\nalso improves current regulation
Text Label 7200 6150 0    51   ~ 0
V_HLoad_P
Wire Wire Line
	6700 4650 6700 4450
$Comp
L Device:C_Small C178
U 1 1 5DFD95D3
P 6950 5150
F 0 "C178" H 7042 5196 50  0000 L CNN
F 1 "1uF" H 7042 5105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6950 5150 50  0001 C CNN
F 3 "~" H 6950 5150 50  0001 C CNN
	1    6950 5150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR044
U 1 1 5DFD9C33
P 6950 5250
F 0 "#PWR044" H 6950 5000 50  0001 C CNN
F 1 "GND" H 6955 5077 50  0000 C CNN
F 2 "" H 6950 5250 50  0001 C CNN
F 3 "" H 6950 5250 50  0001 C CNN
	1    6950 5250
	1    0    0    -1  
$EndComp
Connection ~ 6700 5050
Wire Wire Line
	6700 5050 6700 4950
Wire Wire Line
	6700 5050 6700 5500
Wire Wire Line
	6700 5050 6950 5050
Text Notes 7350 5250 0    47   ~ 0
R12/C78 absorbs stored energy from \nchoke when current source is turned\noff
$Comp
L PI_Blackbox:LTC2057 U1
U 1 1 5E074AF4
P 4250 3900
F 0 "U1" H 4350 4050 50  0000 L CNN
F 1 "LTC2057" H 4350 3750 50  0000 L CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 4200 4000 50  0001 C CNN
F 3 "" H 4300 4100 50  0000 C CNN
F 4 "Linear Technology" H 4850 4200 60  0001 C CNN "MFN"
F 5 "LTC2057" H 4650 4300 60  0001 C CNN "MFP"
	1    4250 3900
	1    0    0    -1  
$EndComp
$Comp
L Device:Ferrite_Bead_Small FB29
U 1 1 5E112E04
P 4700 3350
F 0 "FB29" V 4845 3350 50  0000 C CNN
F 1 "Ferrite" V 4846 3350 50  0001 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 4630 3350 50  0001 C CNN
F 3 "~" H 4700 3350 50  0001 C CNN
	1    4700 3350
	0    -1   -1   0   
$EndComp
$Comp
L Device:Ferrite_Bead_Small FB27
U 1 1 5E118E8A
P 4300 3350
F 0 "FB27" V 4445 3350 50  0000 C CNN
F 1 "Ferrite" V 4446 3350 50  0001 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 4230 3350 50  0001 C CNN
F 3 "~" H 4300 3350 50  0001 C CNN
	1    4300 3350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4150 3350 4200 3350
Wire Wire Line
	4400 3350 4500 3350
Wire Wire Line
	4500 3350 4600 3350
Connection ~ 4500 3350
Wire Wire Line
	4800 3350 4950 3350
$Comp
L Device:R_Small_US R68
U 1 1 5E132D67
P 3900 3250
F 0 "R68" H 4100 3200 50  0000 R CNN
F 1 "100 Ω" H 4200 3300 50  0000 R CNN
F 2 "Resistor_SMD:R_0402_1005Metric" H 3900 3250 50  0001 C CNN
F 3 "~" H 3900 3250 50  0001 C CNN
	1    3900 3250
	-1   0    0    1   
$EndComp
$Comp
L dk_Transistors-Bipolar-BJT-Single:MMBT2222A-7-F Q1
U 1 1 5E18136B
P 5950 3900
F 0 "Q1" H 5700 3750 60  0000 L CNN
F 1 "MMBT2222A" H 5500 3650 60  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23_Handsoldering" H 6150 4100 60  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 6150 4200 60  0001 L CNN
F 4 "MMBT2222A-FDICT-ND" H 6150 4300 60  0001 L CNN "Digi-Key_PN"
F 5 "MMBT2222A-7-F" H 6150 4400 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 6150 4500 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 6150 4600 60  0001 L CNN "Family"
F 8 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 6150 4700 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/diodes-incorporated/MMBT2222A-7-F/MMBT2222A-FDICT-ND/815723" H 6150 4800 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V 0.6A SMD SOT23-3" H 6150 4900 60  0001 L CNN "Description"
F 11 "Diodes Incorporated" H 6150 5000 60  0001 L CNN "Manufacturer"
F 12 "Active" H 6150 5100 60  0001 L CNN "Status"
	1    5950 3900
	1    0    0    -1  
$EndComp
$Comp
L PI_Blackbox:AD8417 U3
U 1 1 5DFC8403
P 5700 2450
F 0 "U3" H 5900 2850 50  0000 C CNN
F 1 "AD8417" H 5550 2850 50  0000 C CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 5750 2100 50  0001 C CNN
F 3 "" H 6350 1750 50  0001 C CNN
	1    5700 2450
	-1   0    0    -1  
$EndComp
Wire Wire Line
	6700 1250 6700 2200
Wire Wire Line
	3900 2450 3900 3150
Wire Wire Line
	5150 1800 5150 1750
Wire Wire Line
	5150 1750 5700 1750
Wire Wire Line
	5700 1750 5700 2000
Connection ~ 5950 1250
Wire Wire Line
	5950 1250 6500 1250
Wire Wire Line
	5000 1250 5200 1250
Wire Wire Line
	4600 1250 4700 1250
Wire Wire Line
	3900 2450 5300 2450
$Comp
L power:GND #PWR0101
U 1 1 5E0839AF
P 5700 2850
F 0 "#PWR0101" H 5700 2600 50  0001 C CNN
F 1 "GND" H 5705 2677 50  0000 C CNN
F 2 "" H 5700 2850 50  0001 C CNN
F 3 "" H 5700 2850 50  0001 C CNN
	1    5700 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 2850 6100 2850
Wire Wire Line
	6100 2850 6100 2650
Connection ~ 5700 2850
Wire Wire Line
	5700 2850 5300 2850
Wire Wire Line
	5300 2850 5300 2650
Wire Wire Line
	6500 1300 6500 1250
Connection ~ 6500 1250
Wire Wire Line
	6500 1250 6700 1250
Wire Wire Line
	6450 5500 6700 5500
Wire Wire Line
	6450 5900 6700 5900
Wire Wire Line
	5500 1250 5700 1250
$Comp
L Device:Ferrite_Bead_Small FB2
U 1 1 5E38CA99
P 5700 1500
F 0 "FB2" H 5845 1500 50  0000 C CNN
F 1 "FB" V 5846 1500 50  0001 C CNN
F 2 "Inductor_SMD:L_0603_1608Metric_Pad1.05x0.95mm_HandSolder" V 5630 1500 50  0001 C CNN
F 3 "~" H 5700 1500 50  0001 C CNN
	1    5700 1500
	-1   0    0    1   
$EndComp
Wire Wire Line
	5700 1400 5700 1250
Connection ~ 5700 1250
Wire Wire Line
	5700 1250 5950 1250
Wire Wire Line
	5700 1600 5700 1750
Connection ~ 5700 1750
$Comp
L Device:C_Small C7
U 1 1 5E3A772B
P 5250 3450
F 0 "C7" H 5050 3450 50  0000 L CNN
F 1 "1uF" H 5050 3350 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5250 3450 50  0001 C CNN
F 3 "~" H 5250 3450 50  0001 C CNN
	1    5250 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 6150 6700 6150
Wire Wire Line
	6300 6250 6700 6250
Wire Wire Line
	6700 5900 6700 6000
Wire Wire Line
	6700 6550 6700 6400
Text Label 7200 6300 0    51   ~ 0
V_HLoad_N
Text GLabel 7150 6150 0    51   Input ~ 0
Kelvin_P
Text GLabel 7150 6300 0    51   Input ~ 0
Kelvin_N
$Comp
L power:GND #PWR?
U 1 1 5EA380E9
P 5250 3550
AR Path="/5EA380E9" Ref="#PWR?"  Part="1" 
AR Path="/5CBFDC2A/5EA380E9" Ref="#PWR0276"  Part="1" 
F 0 "#PWR0276" H 5250 3300 50  0001 C CNN
F 1 "GND" H 5255 3377 50  0000 C CNN
F 2 "" H 5250 3550 50  0001 C CNN
F 3 "" H 5250 3550 50  0001 C CNN
	1    5250 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4950 3350 5250 3350
Connection ~ 4950 3350
Wire Wire Line
	4350 4950 4900 4950
Wire Wire Line
	4350 5400 4900 5400
$Comp
L power:GND #PWR0277
U 1 1 5EA6FDB0
P 3200 5450
F 0 "#PWR0277" H 3200 5200 50  0001 C CNN
F 1 "GND" H 3205 5277 50  0000 C CNN
F 2 "" H 3200 5450 50  0001 C CNN
F 3 "" H 3200 5450 50  0001 C CNN
	1    3200 5450
	1    0    0    -1  
$EndComp
Text GLabel 3200 5000 0    51   Input ~ 0
U1
Text GLabel 4150 3350 0    51   Input ~ 0
U1
Wire Wire Line
	3500 4400 4150 4400
Wire Wire Line
	3900 4000 3900 3350
Text GLabel 5900 5950 0    51   Input ~ 0
HEAT_LOAD_P
Wire Wire Line
	5900 5950 5950 5950
Wire Wire Line
	5950 5950 5950 6050
Wire Wire Line
	6700 6400 7200 6400
Wire Wire Line
	7200 6400 7200 6300
Connection ~ 6700 6400
Wire Wire Line
	6700 6400 6700 6250
Connection ~ 7200 6300
Wire Wire Line
	7200 6300 7650 6300
Wire Wire Line
	6700 6000 7200 6000
Wire Wire Line
	7200 6000 7200 6150
Connection ~ 6700 6000
Wire Wire Line
	6700 6000 6700 6150
Connection ~ 7200 6150
Wire Wire Line
	7200 6150 7650 6150
Text GLabel 5900 6500 0    51   Input ~ 0
HEAT_LOAD_N
Wire Wire Line
	5900 6500 5950 6500
Wire Wire Line
	5950 6500 5950 6400
Text GLabel 4600 1250 0    50   Input ~ 0
+VIN_FILT
$EndSCHEMATC