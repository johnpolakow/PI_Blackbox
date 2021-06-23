EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 7
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
L txs2:TXS2 K?
U 1 1 5FB7B66F
P 2900 6650
AR Path="/5FB7B66F" Ref="K?"  Part="1" 
AR Path="/5F865273/5FB7B66F" Ref="K12"  Part="1" 
F 0 "K12" V 2904 5970 51  0000 R CNN
F 1 "TXS2" V 2996 5970 50  0000 R CNN
F 2 "Footprints:Panasonic_TX2_2" V 3912 7505 50  0001 C CNN
F 3 "http://www.azettler.com/pdfs/az850.pdf" V 2950 6400 50  0001 C CNN
	1    2900 6650
	0    -1   1    0   
$EndComp
Text HLabel 2400 7000 0    55   Input ~ 11
LOAD_RTN
Wire Wire Line
	2400 7000 2700 7000
Text HLabel 2400 7150 0    55   Input ~ 11
I_LOAD
Wire Wire Line
	2400 7150 2950 7150
Wire Wire Line
	2950 7150 2950 7000
Text HLabel 2550 6150 0    55   Input ~ 11
34401B_RTN
Wire Wire Line
	2550 6150 2650 6150
Wire Wire Line
	2650 6150 2650 6400
Text HLabel 2500 5900 0    55   Input ~ 11
34401B_I+
Wire Wire Line
	2500 5900 2900 5900
Wire Wire Line
	2900 5900 2900 6400
Text HLabel 4550 5400 0    55   Input ~ 11
VLoad_div8
Text HLabel 4650 4150 0    55   Input ~ 11
34401B_V+
Text HLabel 1400 3950 0    55   Input ~ 11
GND
Text HLabel 1400 4100 0    55   Input ~ 11
CoolerV
Text HLabel 3800 1950 0    55   Input ~ 11
REF100_RTN
Text HLabel 3800 2100 0    55   Input ~ 11
REF100+
Text HLabel 3900 850  0    55   Input ~ 11
34401B_I+
Text GLabel 5000 2150 3    47   Input ~ 0
K14_RESET
Text GLabel 4950 1100 1    47   Input ~ 0
K14_SET
Text GLabel 5700 4400 1    47   Input ~ 0
K15_SET
Text GLabel 2550 3100 1    47   Input ~ 0
K13_SET
Text GLabel 3550 6150 1    50   Input ~ 0
K12_SET
Text GLabel 2600 4150 3    47   Input ~ 0
K13_RESET
Text GLabel 5750 5450 3    47   Input ~ 0
K15_RESET
Text GLabel 3600 7200 3    47   Input ~ 0
K12_RESET
$Comp
L Diode:1N4148W D26
U 1 1 605C3B63
P 3350 7100
F 0 "D26" H 3350 6900 50  0000 C CNN
F 1 "1N4148W" H 3350 7000 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 3350 6925 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 3350 7100 50  0001 C CNN
	1    3350 7100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 7100 3200 7000
Wire Wire Line
	3200 7000 3250 7000
Wire Wire Line
	3450 7000 3500 7000
Wire Wire Line
	3500 7000 3500 7100
Wire Wire Line
	3500 7100 3600 7100
Wire Wire Line
	3600 7100 3600 7200
Connection ~ 3500 7100
Wire Wire Line
	3200 7100 3100 7100
Wire Wire Line
	3100 7100 3100 7250
Connection ~ 3200 7100
Text GLabel 3100 7250 3    50   Input ~ 0
+5V
$Comp
L Diode:1N4148W D25
U 1 1 605EDB4F
P 3350 6300
F 0 "D25" H 3350 6500 50  0000 C CNN
F 1 "1N4148W" H 3350 6400 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 3350 6125 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 3350 6300 50  0001 C CNN
	1    3350 6300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 6300 3550 6300
Wire Wire Line
	3200 6300 3150 6300
Wire Wire Line
	3250 6400 3150 6400
Wire Wire Line
	3150 6400 3150 6300
Connection ~ 3150 6300
Wire Wire Line
	3450 6400 3550 6400
Wire Wire Line
	3550 6400 3550 6300
Wire Wire Line
	3150 6300 3150 6150
Wire Wire Line
	3550 6300 3550 6150
Connection ~ 3550 6300
Text GLabel 3150 6150 1    50   Input ~ 0
+5V
$Comp
L txs2:TXS2 K?
U 1 1 60614C91
P 5050 4900
AR Path="/60614C91" Ref="K?"  Part="1" 
AR Path="/5F865273/60614C91" Ref="K15"  Part="1" 
F 0 "K15" V 5054 4220 51  0000 R CNN
F 1 "TXS2" V 5146 4220 50  0000 R CNN
F 2 "Footprints:Panasonic_TX2_2" V 6062 5755 50  0001 C CNN
F 3 "http://www.azettler.com/pdfs/az850.pdf" V 5100 4650 50  0001 C CNN
	1    5050 4900
	0    -1   1    0   
$EndComp
Text HLabel 4550 5250 0    55   Input ~ 11
LOAD_RTN
Wire Wire Line
	4550 5250 4850 5250
Wire Wire Line
	4550 5400 5100 5400
Wire Wire Line
	5100 5400 5100 5250
Text HLabel 4700 4400 0    55   Input ~ 11
34401B_RTN
Wire Wire Line
	4700 4400 4800 4400
Wire Wire Line
	4800 4400 4800 4650
Wire Wire Line
	4650 4150 5050 4150
Wire Wire Line
	5050 4150 5050 4650
$Comp
L Diode:1N4148W D30
U 1 1 60614CA4
P 5500 5350
F 0 "D30" H 5500 5150 50  0000 C CNN
F 1 "1N4148W" H 5500 5250 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 5500 5175 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 5500 5350 50  0001 C CNN
	1    5500 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 5350 5350 5250
Wire Wire Line
	5350 5250 5400 5250
Wire Wire Line
	5600 5250 5650 5250
Wire Wire Line
	5650 5250 5650 5350
Wire Wire Line
	5650 5350 5750 5350
Wire Wire Line
	5750 5350 5750 5450
Connection ~ 5650 5350
Wire Wire Line
	5350 5350 5250 5350
Wire Wire Line
	5250 5350 5250 5500
Connection ~ 5350 5350
Text GLabel 5250 5500 3    50   Input ~ 0
+5V
$Comp
L Diode:1N4148W D29
U 1 1 60614CB5
P 5500 4550
F 0 "D29" H 5500 4750 50  0000 C CNN
F 1 "1N4148W" H 5500 4650 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 5500 4375 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 5500 4550 50  0001 C CNN
	1    5500 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 4550 5700 4550
Wire Wire Line
	5350 4550 5300 4550
Wire Wire Line
	5400 4650 5300 4650
Wire Wire Line
	5300 4650 5300 4550
Connection ~ 5300 4550
Wire Wire Line
	5600 4650 5700 4650
Wire Wire Line
	5700 4650 5700 4550
Wire Wire Line
	5300 4550 5300 4400
Wire Wire Line
	5700 4550 5700 4400
Connection ~ 5700 4550
Text GLabel 5300 4400 1    50   Input ~ 0
+5V
Text HLabel 1500 2850 0    55   Input ~ 11
34401B_V+
$Comp
L txs2:TXS2 K?
U 1 1 6065E41E
P 1900 3600
AR Path="/6065E41E" Ref="K?"  Part="1" 
AR Path="/5F865273/6065E41E" Ref="K13"  Part="1" 
F 0 "K13" V 1904 2920 51  0000 R CNN
F 1 "TXS2" V 1996 2920 50  0000 R CNN
F 2 "Footprints:Panasonic_TX2_2" V 2912 4455 50  0001 C CNN
F 3 "http://www.azettler.com/pdfs/az850.pdf" V 1950 3350 50  0001 C CNN
	1    1900 3600
	0    -1   1    0   
$EndComp
Wire Wire Line
	1400 3950 1700 3950
Wire Wire Line
	1400 4100 1950 4100
Wire Wire Line
	1950 4100 1950 3950
Text HLabel 1550 3100 0    55   Input ~ 11
34401B_RTN
Wire Wire Line
	1550 3100 1650 3100
Wire Wire Line
	1650 3100 1650 3350
Wire Wire Line
	1500 2850 1900 2850
Wire Wire Line
	1900 2850 1900 3350
$Comp
L Diode:1N4148W D24
U 1 1 6065E42D
P 2350 4050
F 0 "D24" H 2350 3850 50  0000 C CNN
F 1 "1N4148W" H 2350 3950 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 2350 3875 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 2350 4050 50  0001 C CNN
	1    2350 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2200 4050 2200 3950
Wire Wire Line
	2200 3950 2250 3950
Wire Wire Line
	2450 3950 2500 3950
Wire Wire Line
	2500 3950 2500 4050
Wire Wire Line
	2500 4050 2600 4050
Wire Wire Line
	2600 4050 2600 4150
Connection ~ 2500 4050
Wire Wire Line
	2200 4050 2100 4050
Wire Wire Line
	2100 4050 2100 4200
Connection ~ 2200 4050
Text GLabel 2100 4200 3    50   Input ~ 0
+5V
$Comp
L Diode:1N4148W D23
U 1 1 6065E43E
P 2350 3250
F 0 "D23" H 2350 3450 50  0000 C CNN
F 1 "1N4148W" H 2350 3350 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 2350 3075 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 2350 3250 50  0001 C CNN
	1    2350 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 3250 2550 3250
Wire Wire Line
	2200 3250 2150 3250
Wire Wire Line
	2250 3350 2150 3350
Wire Wire Line
	2150 3350 2150 3250
Connection ~ 2150 3250
Wire Wire Line
	2450 3350 2550 3350
Wire Wire Line
	2550 3350 2550 3250
Wire Wire Line
	2150 3250 2150 3100
Wire Wire Line
	2550 3250 2550 3100
Connection ~ 2550 3250
Text GLabel 2150 3100 1    50   Input ~ 0
+5V
$Comp
L txs2:TXS2 K?
U 1 1 606BF3E4
P 4300 1600
AR Path="/606BF3E4" Ref="K?"  Part="1" 
AR Path="/5F865273/606BF3E4" Ref="K14"  Part="1" 
F 0 "K14" V 4304 920 51  0000 R CNN
F 1 "TXS2" V 4396 920 50  0000 R CNN
F 2 "Footprints:Panasonic_TX2_2" V 5312 2455 50  0001 C CNN
F 3 "http://www.azettler.com/pdfs/az850.pdf" V 4350 1350 50  0001 C CNN
	1    4300 1600
	0    -1   1    0   
$EndComp
Wire Wire Line
	3800 1950 4100 1950
Wire Wire Line
	3800 2100 4350 2100
Wire Wire Line
	4350 2100 4350 1950
Text HLabel 3950 1100 0    55   Input ~ 11
34401B_RTN
Wire Wire Line
	3950 1100 4050 1100
Wire Wire Line
	4050 1100 4050 1350
Wire Wire Line
	3900 850  4300 850 
Wire Wire Line
	4300 850  4300 1350
$Comp
L Diode:1N4148W D28
U 1 1 606BF3F2
P 4750 2050
F 0 "D28" H 4750 1850 50  0000 C CNN
F 1 "1N4148W" H 4750 1950 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 4750 1875 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 4750 2050 50  0001 C CNN
	1    4750 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4600 2050 4600 1950
Wire Wire Line
	4600 1950 4650 1950
Wire Wire Line
	4850 1950 4900 1950
Wire Wire Line
	4900 1950 4900 2050
Wire Wire Line
	4900 2050 5000 2050
Wire Wire Line
	5000 2050 5000 2150
Connection ~ 4900 2050
Wire Wire Line
	4600 2050 4500 2050
Wire Wire Line
	4500 2050 4500 2200
Connection ~ 4600 2050
Text GLabel 4500 2200 3    50   Input ~ 0
+5V
$Comp
L Diode:1N4148W D27
U 1 1 606BF403
P 4750 1250
F 0 "D27" H 4750 1450 50  0000 C CNN
F 1 "1N4148W" H 4750 1350 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 4750 1075 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 4750 1250 50  0001 C CNN
	1    4750 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 1250 4950 1250
Wire Wire Line
	4600 1250 4550 1250
Wire Wire Line
	4650 1350 4550 1350
Wire Wire Line
	4550 1350 4550 1250
Connection ~ 4550 1250
Wire Wire Line
	4850 1350 4950 1350
Wire Wire Line
	4950 1350 4950 1250
Wire Wire Line
	4550 1250 4550 1100
Wire Wire Line
	4950 1250 4950 1100
Connection ~ 4950 1250
Text GLabel 4550 1100 1    50   Input ~ 0
+5V
Text GLabel 8900 2550 0    50   Input ~ 0
+5V
$Comp
L Device:C_Small C?
U 1 1 60D7E240
P 9000 2700
AR Path="/60D7E240" Ref="C?"  Part="1" 
AR Path="/5EFA74C2/60D7E240" Ref="C?"  Part="1" 
AR Path="/5F865273/60D7E240" Ref="C24"  Part="1" 
F 0 "C24" H 9092 2746 50  0000 L CNN
F 1 "10uF" H 9092 2655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 9000 2700 50  0001 C CNN
F 3 "~" H 9000 2700 50  0001 C CNN
	1    9000 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	8900 2550 9000 2550
Wire Wire Line
	9000 2550 9000 2600
Wire Wire Line
	8900 2850 9000 2850
Wire Wire Line
	9000 2850 9000 2800
Text GLabel 9650 2550 0    50   Input ~ 0
+5V
$Comp
L Device:C_Small C?
U 1 1 60D7E24B
P 9750 2700
AR Path="/60D7E24B" Ref="C?"  Part="1" 
AR Path="/5EFA74C2/60D7E24B" Ref="C?"  Part="1" 
AR Path="/5F865273/60D7E24B" Ref="C28"  Part="1" 
F 0 "C28" H 9842 2746 50  0000 L CNN
F 1 "10uF" H 9842 2655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 9750 2700 50  0001 C CNN
F 3 "~" H 9750 2700 50  0001 C CNN
	1    9750 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	9650 2550 9750 2550
Wire Wire Line
	9750 2550 9750 2600
Wire Wire Line
	9650 2850 9750 2850
Wire Wire Line
	9750 2850 9750 2800
Text GLabel 8900 3100 0    50   Input ~ 0
+5V
$Comp
L Device:C_Small C?
U 1 1 60D7E256
P 9000 3250
AR Path="/60D7E256" Ref="C?"  Part="1" 
AR Path="/5EFA74C2/60D7E256" Ref="C?"  Part="1" 
AR Path="/5F865273/60D7E256" Ref="C25"  Part="1" 
F 0 "C25" H 9092 3296 50  0000 L CNN
F 1 "10uF" H 9092 3205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 9000 3250 50  0001 C CNN
F 3 "~" H 9000 3250 50  0001 C CNN
	1    9000 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	8900 3100 9000 3100
Wire Wire Line
	9000 3100 9000 3150
Wire Wire Line
	8900 3400 9000 3400
Wire Wire Line
	9000 3400 9000 3350
Text GLabel 9650 3100 0    50   Input ~ 0
+5V
$Comp
L Device:C_Small C?
U 1 1 60D7E261
P 9750 3250
AR Path="/60D7E261" Ref="C?"  Part="1" 
AR Path="/5EFA74C2/60D7E261" Ref="C?"  Part="1" 
AR Path="/5F865273/60D7E261" Ref="C29"  Part="1" 
F 0 "C29" H 9842 3296 50  0000 L CNN
F 1 "10uF" H 9842 3205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 9750 3250 50  0001 C CNN
F 3 "~" H 9750 3250 50  0001 C CNN
	1    9750 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	9650 3100 9750 3100
Wire Wire Line
	9750 3100 9750 3150
Wire Wire Line
	9650 3400 9750 3400
Wire Wire Line
	9750 3400 9750 3350
Text GLabel 8950 3750 0    50   Input ~ 0
+5V
$Comp
L Device:C_Small C?
U 1 1 60D7E26C
P 9050 3900
AR Path="/60D7E26C" Ref="C?"  Part="1" 
AR Path="/5EFA74C2/60D7E26C" Ref="C?"  Part="1" 
AR Path="/5F865273/60D7E26C" Ref="C26"  Part="1" 
F 0 "C26" H 9142 3946 50  0000 L CNN
F 1 "10uF" H 9142 3855 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 9050 3900 50  0001 C CNN
F 3 "~" H 9050 3900 50  0001 C CNN
	1    9050 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	8950 3750 9050 3750
Wire Wire Line
	9050 3750 9050 3800
Wire Wire Line
	8950 4050 9050 4050
Wire Wire Line
	9050 4050 9050 4000
Text GLabel 9700 3750 0    50   Input ~ 0
+5V
$Comp
L Device:C_Small C?
U 1 1 60D7E277
P 9800 3900
AR Path="/60D7E277" Ref="C?"  Part="1" 
AR Path="/5EFA74C2/60D7E277" Ref="C?"  Part="1" 
AR Path="/5F865273/60D7E277" Ref="C30"  Part="1" 
F 0 "C30" H 9892 3946 50  0000 L CNN
F 1 "10uF" H 9892 3855 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 9800 3900 50  0001 C CNN
F 3 "~" H 9800 3900 50  0001 C CNN
	1    9800 3900
	1    0    0    -1  
$EndComp
Wire Wire Line
	9700 3750 9800 3750
Wire Wire Line
	9800 3750 9800 3800
Wire Wire Line
	9700 4050 9800 4050
Wire Wire Line
	9800 4050 9800 4000
Text GLabel 8900 1950 0    50   Input ~ 0
+5V
$Comp
L Device:C_Small C?
U 1 1 60D7E282
P 9000 2100
AR Path="/60D7E282" Ref="C?"  Part="1" 
AR Path="/5EFA74C2/60D7E282" Ref="C?"  Part="1" 
AR Path="/5F865273/60D7E282" Ref="C23"  Part="1" 
F 0 "C23" H 9092 2146 50  0000 L CNN
F 1 "10uF" H 9092 2055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 9000 2100 50  0001 C CNN
F 3 "~" H 9000 2100 50  0001 C CNN
	1    9000 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	8900 1950 9000 1950
Wire Wire Line
	9000 1950 9000 2000
Wire Wire Line
	8900 2250 9000 2250
Wire Wire Line
	9000 2250 9000 2200
Text GLabel 9650 1950 0    50   Input ~ 0
+5V
$Comp
L Device:C_Small C?
U 1 1 60D7E28D
P 9750 2100
AR Path="/60D7E28D" Ref="C?"  Part="1" 
AR Path="/5EFA74C2/60D7E28D" Ref="C?"  Part="1" 
AR Path="/5F865273/60D7E28D" Ref="C27"  Part="1" 
F 0 "C27" H 9842 2146 50  0000 L CNN
F 1 "10uF" H 9842 2055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 9750 2100 50  0001 C CNN
F 3 "~" H 9750 2100 50  0001 C CNN
	1    9750 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	9650 1950 9750 1950
Wire Wire Line
	9750 1950 9750 2000
Wire Wire Line
	9650 2250 9750 2250
Wire Wire Line
	9750 2250 9750 2200
Text GLabel 8900 2250 0    47   Input ~ 0
K13_SET
Text GLabel 9650 2250 0    47   Input ~ 0
K13_RESET
Text GLabel 8900 2850 0    47   Input ~ 0
K14_SET
Text GLabel 9650 2850 0    47   Input ~ 0
K14_RESET
Text GLabel 8900 3400 0    47   Input ~ 0
K15_SET
Text GLabel 9650 3400 0    47   Input ~ 0
K15_RESET
Text GLabel 8950 4050 0    50   Input ~ 0
K12_SET
Text GLabel 9700 4050 0    47   Input ~ 0
K12_RESET
NoConn ~ 2800 6400
NoConn ~ 3050 6400
NoConn ~ 1800 3350
NoConn ~ 2050 3350
NoConn ~ 4950 4650
NoConn ~ 5200 4650
NoConn ~ 4200 1350
NoConn ~ 4450 1350
$EndSCHEMATC
