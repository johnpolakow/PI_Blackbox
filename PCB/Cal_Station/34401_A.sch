EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 3 7
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Wire Wire Line
	4000 3200 3900 3200
$Comp
L txs2:TXS2 K?
U 1 1 5F8CBC49
P 4250 3600
AR Path="/5F8CBC49" Ref="K?"  Part="1" 
AR Path="/5F851FE1/5F8CBC49" Ref="K9"  Part="1" 
F 0 "K9" V 4254 2920 51  0000 R CNN
F 1 "TXS2" V 4346 2920 50  0000 R CNN
F 2 "Footprints:Panasonic_TX2_2" V 5262 4455 50  0001 C CNN
F 3 "http://www.azettler.com/pdfs/az850.pdf" V 4300 3350 50  0001 C CNN
	1    4250 3600
	0    -1   1    0   
$EndComp
Wire Wire Line
	4600 1200 4500 1200
$Comp
L txs2:TXS2 K?
U 1 1 5F8CBC77
P 4850 1550
AR Path="/5F8CBC77" Ref="K?"  Part="1" 
AR Path="/5F851FE1/5F8CBC77" Ref="K8"  Part="1" 
F 0 "K8" V 4854 870 51  0000 R CNN
F 1 "TXS2" V 4946 870 50  0000 R CNN
F 2 "Footprints:Panasonic_TX2_2" V 5862 2405 50  0001 C CNN
F 3 "http://www.azettler.com/pdfs/az850.pdf" V 4900 1300 50  0001 C CNN
	1    4850 1550
	0    -1   1    0   
$EndComp
Text HLabel 4600 7150 0    47   Input ~ 9
GNDA
Wire Wire Line
	4600 7150 4900 7150
Text HLabel 4600 7300 0    47   Input ~ 9
COOLERV_div4
Wire Wire Line
	4600 7300 5150 7300
Text HLabel 2150 5550 0    47   Input ~ 9
GNDA
Text HLabel 2150 5650 0    47   Input ~ 9
diode_sns-
Wire Wire Line
	2150 5550 2250 5550
Text HLabel 2150 5800 0    47   Input ~ 9
DAC_AUX_BUF
Text HLabel 2150 5900 0    47   Input ~ 9
diode_sns+
Wire Wire Line
	2150 5900 2250 5900
Wire Wire Line
	2250 5800 2150 5800
Wire Wire Line
	2250 5800 2250 5850
Connection ~ 2250 5850
Wire Wire Line
	2250 5850 2250 5900
Text HLabel 3850 4050 0    47   Input ~ 9
GNDA
Text HLabel 3850 4200 0    47   Input ~ 9
2V5_filt
Wire Wire Line
	3850 4050 4050 4050
Wire Wire Line
	4050 4050 4050 3950
Wire Wire Line
	3850 4200 4300 4200
Wire Wire Line
	4300 4200 4300 3950
Text HLabel 4450 1950 0    47   Input ~ 9
LOAD_RTN
Text HLabel 4450 2100 0    47   Input ~ 9
LOAD+
Wire Wire Line
	4450 1950 4650 1950
Wire Wire Line
	4650 1950 4650 1900
Wire Wire Line
	4450 2100 4900 2100
Wire Wire Line
	4900 2100 4900 1900
Text HLabel 4500 1200 0    47   Input ~ 9
34401A_RTN
Text HLabel 3900 3200 0    47   Input ~ 9
34401A_RTN
Text HLabel 4500 1000 0    47   Input ~ 9
34401A_V+
Text HLabel 3900 3000 0    47   Input ~ 9
34401A_V+
Text GLabel 4900 3100 1    47   Input ~ 0
K9_SET
Text GLabel 4950 4200 3    47   Input ~ 0
K9_RESET
Text GLabel 5500 1050 1    47   Input ~ 0
K8_SET
Text GLabel 5750 6250 1    47   Input ~ 0
K11_SET
Text GLabel 3400 4800 1    47   Input ~ 0
K10_SET
Text GLabel 3450 5850 3    47   Input ~ 0
K10_RESET
Text GLabel 5800 7300 3    47   Input ~ 0
K11_RESET
Text GLabel 5550 2100 3    47   Input ~ 0
K8_RESET
Text HLabel 2350 4550 0    55   Input ~ 11
34401A_V+
$Comp
L txs2:TXS2 K?
U 1 1 60721C07
P 2750 5300
AR Path="/60721C07" Ref="K?"  Part="1" 
AR Path="/5F865273/60721C07" Ref="K?"  Part="1" 
AR Path="/5F851FE1/60721C07" Ref="K10"  Part="1" 
F 0 "K10" V 2754 4620 51  0000 R CNN
F 1 "TXS2" V 2846 4620 50  0000 R CNN
F 2 "Footprints:Panasonic_TX2_2" V 3762 6155 50  0001 C CNN
F 3 "http://www.azettler.com/pdfs/az850.pdf" V 2800 5050 50  0001 C CNN
	1    2750 5300
	0    -1   1    0   
$EndComp
Text HLabel 2400 4800 0    55   Input ~ 11
34401A_RTN
Wire Wire Line
	2400 4800 2500 4800
Wire Wire Line
	2500 4800 2500 5050
Wire Wire Line
	2350 4550 2750 4550
Wire Wire Line
	2750 4550 2750 5050
$Comp
L Diode:1N4148W D?
U 1 1 60721C15
P 3200 5750
AR Path="/5F865273/60721C15" Ref="D?"  Part="1" 
AR Path="/5F851FE1/60721C15" Ref="D16"  Part="1" 
F 0 "D16" H 3200 5550 50  0000 C CNN
F 1 "1N4148W" H 3200 5650 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 3200 5575 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 3200 5750 50  0001 C CNN
	1    3200 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 5750 3050 5650
Wire Wire Line
	3050 5650 3100 5650
Wire Wire Line
	3300 5650 3350 5650
Wire Wire Line
	3350 5650 3350 5750
Wire Wire Line
	3350 5750 3450 5750
Wire Wire Line
	3450 5750 3450 5850
Connection ~ 3350 5750
Wire Wire Line
	3050 5750 2950 5750
Wire Wire Line
	2950 5750 2950 5900
Connection ~ 3050 5750
Text GLabel 2950 5900 3    50   Input ~ 0
+5V
$Comp
L Diode:1N4148W D?
U 1 1 60721C26
P 3200 4950
AR Path="/5F865273/60721C26" Ref="D?"  Part="1" 
AR Path="/5F851FE1/60721C26" Ref="D15"  Part="1" 
F 0 "D15" H 3200 5150 50  0000 C CNN
F 1 "1N4148W" H 3200 5050 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 3200 4775 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 3200 4950 50  0001 C CNN
	1    3200 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3350 4950 3400 4950
Wire Wire Line
	3050 4950 3000 4950
Wire Wire Line
	3100 5050 3000 5050
Wire Wire Line
	3000 5050 3000 4950
Connection ~ 3000 4950
Wire Wire Line
	3300 5050 3400 5050
Wire Wire Line
	3400 5050 3400 4950
Wire Wire Line
	3000 4950 3000 4800
Wire Wire Line
	3400 4950 3400 4800
Connection ~ 3400 4950
Text GLabel 3000 4800 1    50   Input ~ 0
+5V
Wire Wire Line
	2250 5550 2250 5650
Wire Wire Line
	2150 5650 2250 5650
Connection ~ 2250 5650
Wire Wire Line
	2250 5650 2550 5650
Wire Wire Line
	2250 5850 2800 5850
Wire Wire Line
	2800 5650 2800 5850
Text HLabel 4700 6000 0    55   Input ~ 11
34401A_V+
$Comp
L txs2:TXS2 K?
U 1 1 607852BF
P 5100 6750
AR Path="/607852BF" Ref="K?"  Part="1" 
AR Path="/5F865273/607852BF" Ref="K?"  Part="1" 
AR Path="/5F851FE1/607852BF" Ref="K11"  Part="1" 
F 0 "K11" V 5104 6070 51  0000 R CNN
F 1 "TXS2" V 5196 6070 50  0000 R CNN
F 2 "Footprints:Panasonic_TX2_2" V 6112 7605 50  0001 C CNN
F 3 "http://www.azettler.com/pdfs/az850.pdf" V 5150 6500 50  0001 C CNN
	1    5100 6750
	0    -1   1    0   
$EndComp
Text HLabel 4750 6250 0    55   Input ~ 11
34401A_RTN
Wire Wire Line
	4750 6250 4850 6250
Wire Wire Line
	4850 6250 4850 6500
Wire Wire Line
	4700 6000 5100 6000
Wire Wire Line
	5100 6000 5100 6500
$Comp
L Diode:1N4148W D?
U 1 1 607852CA
P 5550 7200
AR Path="/5F865273/607852CA" Ref="D?"  Part="1" 
AR Path="/5F851FE1/607852CA" Ref="D22"  Part="1" 
F 0 "D22" H 5550 7000 50  0000 C CNN
F 1 "1N4148W" H 5550 7100 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 5550 7025 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 5550 7200 50  0001 C CNN
	1    5550 7200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 7200 5400 7100
Wire Wire Line
	5400 7100 5450 7100
Wire Wire Line
	5650 7100 5700 7100
Wire Wire Line
	5700 7100 5700 7200
Wire Wire Line
	5700 7200 5800 7200
Wire Wire Line
	5800 7200 5800 7300
Connection ~ 5700 7200
Wire Wire Line
	5400 7200 5300 7200
Wire Wire Line
	5300 7200 5300 7350
Connection ~ 5400 7200
Text GLabel 5300 7350 3    50   Input ~ 0
+5V
$Comp
L Diode:1N4148W D?
U 1 1 607852DB
P 5550 6400
AR Path="/5F865273/607852DB" Ref="D?"  Part="1" 
AR Path="/5F851FE1/607852DB" Ref="D21"  Part="1" 
F 0 "D21" H 5550 6600 50  0000 C CNN
F 1 "1N4148W" H 5550 6500 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 5550 6225 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 5550 6400 50  0001 C CNN
	1    5550 6400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5700 6400 5750 6400
Wire Wire Line
	5400 6400 5350 6400
Wire Wire Line
	5450 6500 5350 6500
Wire Wire Line
	5350 6500 5350 6400
Connection ~ 5350 6400
Wire Wire Line
	5650 6500 5750 6500
Wire Wire Line
	5750 6500 5750 6400
Wire Wire Line
	5350 6400 5350 6250
Wire Wire Line
	5750 6400 5750 6250
Connection ~ 5750 6400
Text GLabel 5350 6250 1    50   Input ~ 0
+5V
Wire Wire Line
	5150 7100 5150 7300
Wire Wire Line
	4900 7100 4900 7150
$Comp
L Diode:1N4148W D?
U 1 1 60A7638F
P 4700 3250
AR Path="/5F865273/60A7638F" Ref="D?"  Part="1" 
AR Path="/5F851FE1/60A7638F" Ref="D17"  Part="1" 
F 0 "D17" H 4700 3450 50  0000 C CNN
F 1 "1N4148W" H 4700 3350 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 4700 3075 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 4700 3250 50  0001 C CNN
	1    4700 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 3250 4900 3250
Wire Wire Line
	4550 3250 4500 3250
Wire Wire Line
	4500 3350 4500 3250
Connection ~ 4500 3250
Wire Wire Line
	4900 3350 4900 3250
Wire Wire Line
	4500 3250 4500 3100
Wire Wire Line
	4900 3250 4900 3100
Connection ~ 4900 3250
Text GLabel 4500 3100 1    50   Input ~ 0
+5V
Wire Wire Line
	4000 3200 4000 3350
Wire Wire Line
	4250 3000 4250 3350
Wire Wire Line
	3900 3000 4250 3000
Wire Wire Line
	4500 3350 4600 3350
Wire Wire Line
	4800 3350 4900 3350
Wire Wire Line
	4600 1200 4600 1300
Wire Wire Line
	4500 1000 4850 1000
Wire Wire Line
	4850 1000 4850 1300
$Comp
L Diode:1N4148W D?
U 1 1 60AAB549
P 5300 1200
AR Path="/5F865273/60AAB549" Ref="D?"  Part="1" 
AR Path="/5F851FE1/60AAB549" Ref="D19"  Part="1" 
F 0 "D19" H 5300 1400 50  0000 C CNN
F 1 "1N4148W" H 5300 1300 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 5300 1025 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 5300 1200 50  0001 C CNN
	1    5300 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 1200 5500 1200
Wire Wire Line
	5150 1200 5100 1200
Wire Wire Line
	5100 1300 5100 1200
Connection ~ 5100 1200
Wire Wire Line
	5500 1300 5500 1200
Wire Wire Line
	5100 1200 5100 1050
Wire Wire Line
	5500 1200 5500 1050
Connection ~ 5500 1200
Text GLabel 5100 1050 1    50   Input ~ 0
+5V
$Comp
L Diode:1N4148W D?
U 1 1 60AD6FDA
P 4700 4100
AR Path="/5F865273/60AD6FDA" Ref="D?"  Part="1" 
AR Path="/5F851FE1/60AD6FDA" Ref="D18"  Part="1" 
F 0 "D18" H 4700 3900 50  0000 C CNN
F 1 "1N4148W" H 4700 4000 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 4700 3925 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 4700 4100 50  0001 C CNN
	1    4700 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 4100 4950 4100
Wire Wire Line
	4950 4100 4950 4200
Connection ~ 4850 4100
Wire Wire Line
	4550 4100 4450 4100
Wire Wire Line
	4450 4100 4450 4250
Connection ~ 4550 4100
Text GLabel 4450 4250 3    50   Input ~ 0
+5V
Wire Wire Line
	4550 3950 4600 3950
Wire Wire Line
	4550 3950 4550 4100
Wire Wire Line
	4800 3950 4850 3950
Wire Wire Line
	4850 3950 4850 4100
$Comp
L Diode:1N4148W D?
U 1 1 60ADF491
P 5300 2000
AR Path="/5F865273/60ADF491" Ref="D?"  Part="1" 
AR Path="/5F851FE1/60ADF491" Ref="D20"  Part="1" 
F 0 "D20" H 5300 1800 50  0000 C CNN
F 1 "1N4148W" H 5300 1900 50  0000 C CNN
F 2 "Diode_SMD:D_SOD-123" H 5300 1825 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 5300 2000 50  0001 C CNN
	1    5300 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 2000 5150 1900
Wire Wire Line
	5450 1900 5450 2000
Wire Wire Line
	5450 2000 5550 2000
Wire Wire Line
	5550 2000 5550 2100
Connection ~ 5450 2000
Wire Wire Line
	5150 2000 5050 2000
Wire Wire Line
	5050 2000 5050 2150
Connection ~ 5150 2000
Text GLabel 5050 2150 3    50   Input ~ 0
+5V
Wire Wire Line
	5150 1900 5200 1900
Wire Wire Line
	5400 1900 5450 1900
Wire Wire Line
	5100 1300 5200 1300
Wire Wire Line
	5400 1300 5500 1300
Text GLabel 8550 2400 0    50   Input ~ 0
+5V
$Comp
L Device:C_Small C?
U 1 1 60C457ED
P 8650 2550
AR Path="/60C457ED" Ref="C?"  Part="1" 
AR Path="/5EFA74C2/60C457ED" Ref="C?"  Part="1" 
AR Path="/5F851FE1/60C457ED" Ref="C16"  Part="1" 
F 0 "C16" H 8742 2596 50  0000 L CNN
F 1 "10uF" H 8742 2505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 8650 2550 50  0001 C CNN
F 3 "~" H 8650 2550 50  0001 C CNN
	1    8650 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 2400 8650 2400
Wire Wire Line
	8650 2400 8650 2450
Wire Wire Line
	8550 2700 8650 2700
Wire Wire Line
	8650 2700 8650 2650
Text GLabel 9300 2400 0    50   Input ~ 0
+5V
$Comp
L Device:C_Small C?
U 1 1 60C457F8
P 9400 2550
AR Path="/60C457F8" Ref="C?"  Part="1" 
AR Path="/5EFA74C2/60C457F8" Ref="C?"  Part="1" 
AR Path="/5F851FE1/60C457F8" Ref="C20"  Part="1" 
F 0 "C20" H 9492 2596 50  0000 L CNN
F 1 "10uF" H 9492 2505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 9400 2550 50  0001 C CNN
F 3 "~" H 9400 2550 50  0001 C CNN
	1    9400 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	9300 2400 9400 2400
Wire Wire Line
	9400 2400 9400 2450
Wire Wire Line
	9300 2700 9400 2700
Wire Wire Line
	9400 2700 9400 2650
Text GLabel 8550 2950 0    50   Input ~ 0
+5V
$Comp
L Device:C_Small C?
U 1 1 60C45805
P 8650 3100
AR Path="/60C45805" Ref="C?"  Part="1" 
AR Path="/5EFA74C2/60C45805" Ref="C?"  Part="1" 
AR Path="/5F851FE1/60C45805" Ref="C17"  Part="1" 
F 0 "C17" H 8742 3146 50  0000 L CNN
F 1 "10uF" H 8742 3055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 8650 3100 50  0001 C CNN
F 3 "~" H 8650 3100 50  0001 C CNN
	1    8650 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 2950 8650 2950
Wire Wire Line
	8650 2950 8650 3000
Wire Wire Line
	8550 3250 8650 3250
Wire Wire Line
	8650 3250 8650 3200
Text GLabel 9300 2950 0    50   Input ~ 0
+5V
$Comp
L Device:C_Small C?
U 1 1 60C45810
P 9400 3100
AR Path="/60C45810" Ref="C?"  Part="1" 
AR Path="/5EFA74C2/60C45810" Ref="C?"  Part="1" 
AR Path="/5F851FE1/60C45810" Ref="C21"  Part="1" 
F 0 "C21" H 9492 3146 50  0000 L CNN
F 1 "10uF" H 9492 3055 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 9400 3100 50  0001 C CNN
F 3 "~" H 9400 3100 50  0001 C CNN
	1    9400 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	9300 2950 9400 2950
Wire Wire Line
	9400 2950 9400 3000
Wire Wire Line
	9300 3250 9400 3250
Wire Wire Line
	9400 3250 9400 3200
Text GLabel 8600 3600 0    50   Input ~ 0
+5V
$Comp
L Device:C_Small C?
U 1 1 60C45835
P 8700 3750
AR Path="/60C45835" Ref="C?"  Part="1" 
AR Path="/5EFA74C2/60C45835" Ref="C?"  Part="1" 
AR Path="/5F851FE1/60C45835" Ref="C18"  Part="1" 
F 0 "C18" H 8792 3796 50  0000 L CNN
F 1 "10uF" H 8792 3705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 8700 3750 50  0001 C CNN
F 3 "~" H 8700 3750 50  0001 C CNN
	1    8700 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	8600 3600 8700 3600
Wire Wire Line
	8700 3600 8700 3650
Wire Wire Line
	8600 3900 8700 3900
Wire Wire Line
	8700 3900 8700 3850
Text GLabel 9350 3600 0    50   Input ~ 0
+5V
$Comp
L Device:C_Small C?
U 1 1 60C45840
P 9450 3750
AR Path="/60C45840" Ref="C?"  Part="1" 
AR Path="/5EFA74C2/60C45840" Ref="C?"  Part="1" 
AR Path="/5F851FE1/60C45840" Ref="C22"  Part="1" 
F 0 "C22" H 9542 3796 50  0000 L CNN
F 1 "10uF" H 9542 3705 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 9450 3750 50  0001 C CNN
F 3 "~" H 9450 3750 50  0001 C CNN
	1    9450 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	9350 3600 9450 3600
Wire Wire Line
	9450 3600 9450 3650
Wire Wire Line
	9350 3900 9450 3900
Wire Wire Line
	9450 3900 9450 3850
Text GLabel 8550 1800 0    50   Input ~ 0
+5V
$Comp
L Device:C_Small C?
U 1 1 60C45865
P 8650 1950
AR Path="/60C45865" Ref="C?"  Part="1" 
AR Path="/5EFA74C2/60C45865" Ref="C?"  Part="1" 
AR Path="/5F851FE1/60C45865" Ref="C15"  Part="1" 
F 0 "C15" H 8742 1996 50  0000 L CNN
F 1 "10uF" H 8742 1905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 8650 1950 50  0001 C CNN
F 3 "~" H 8650 1950 50  0001 C CNN
	1    8650 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 1800 8650 1800
Wire Wire Line
	8650 1800 8650 1850
Wire Wire Line
	8550 2100 8650 2100
Wire Wire Line
	8650 2100 8650 2050
Text GLabel 9300 1800 0    50   Input ~ 0
+5V
$Comp
L Device:C_Small C?
U 1 1 60C45870
P 9400 1950
AR Path="/60C45870" Ref="C?"  Part="1" 
AR Path="/5EFA74C2/60C45870" Ref="C?"  Part="1" 
AR Path="/5F851FE1/60C45870" Ref="C19"  Part="1" 
F 0 "C19" H 9492 1996 50  0000 L CNN
F 1 "10uF" H 9492 1905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 9400 1950 50  0001 C CNN
F 3 "~" H 9400 1950 50  0001 C CNN
	1    9400 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	9300 1800 9400 1800
Wire Wire Line
	9400 1800 9400 1850
Wire Wire Line
	9300 2100 9400 2100
Wire Wire Line
	9400 2100 9400 2050
Text GLabel 9300 2100 0    47   Input ~ 0
K8_RESET
Text GLabel 8550 2100 0    47   Input ~ 0
K8_SET
Text GLabel 8550 2700 0    47   Input ~ 0
K9_SET
Text GLabel 9300 2700 0    47   Input ~ 0
K9_RESET
Text GLabel 8550 3250 0    47   Input ~ 0
K10_SET
Text GLabel 9300 3250 0    47   Input ~ 0
K10_RESET
Text GLabel 8600 3900 0    47   Input ~ 0
K11_SET
Text GLabel 9350 3900 0    47   Input ~ 0
K11_RESET
NoConn ~ 5000 6500
NoConn ~ 5250 6500
NoConn ~ 2650 5050
NoConn ~ 2900 5050
NoConn ~ 4150 3350
NoConn ~ 4400 3350
NoConn ~ 4750 1300
NoConn ~ 5000 1300
$EndSCHEMATC
