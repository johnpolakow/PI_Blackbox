EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 5 7
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
L PI_Blackbox:RPI_3B+_Header PI1
U 1 1 604A1831
P 2700 1850
F 0 "PI1" H 2600 2821 60  0000 C CNN
F 1 "RPI_3B+_Header" H 2600 2723 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x20_P2.54mm_Vertical" H 2600 1650 60  0001 C CNN
F 3 "" H 2600 1650 60  0000 C CNN
	1    2700 1850
	1    0    0    -1  
$EndComp
Text GLabel 6000 3250 2    47   Input ~ 0
K11_RESET_SIGNL
Text GLabel 3150 3000 2    47   Input ~ 0
K11_SET_SIGNL
Text GLabel 6000 3350 2    47   Input ~ 0
K10_RESET_SIGNL
Text GLabel 1950 2900 0    47   Input ~ 0
K10_SET_SIGNL
Text GLabel 6000 3450 2    47   Input ~ 0
K9_RESET_SIGNL
Text GLabel 1950 2800 0    47   Input ~ 0
K9_SET_SIGNL
Text GLabel 6000 3550 2    47   Input ~ 0
K8_RESET_SIGNL
Text GLabel 1950 2700 0    47   Input ~ 0
K8_SET_SIGNL
Text GLabel 1950 1400 0    47   Input ~ 0
K1_SET_SGNL
Text GLabel 1950 1600 0    47   Input ~ 0
K1_RESET_SIGNL
Text GLabel 1950 1700 0    47   Input ~ 0
K2_SET_SIGNL
Text GLabel 5600 1350 2    47   Input ~ 0
K2_RESET_SIGNL
Text GLabel 1950 1800 0    47   Input ~ 0
K3_SET_SIGNL
Text GLabel 5600 1200 2    47   Input ~ 0
K3_RESET_SIGNL
Text GLabel 1950 2000 0    47   Input ~ 0
K4_SET_SIGNL
Text GLabel 5600 1050 2    47   Input ~ 0
K4_RESET_SIGNL
Text GLabel 1950 2100 0    47   Input ~ 0
K5_SET_SIGNL
Text GLabel 5600 900  2    47   Input ~ 0
K5_RESET_SIGNL
Text GLabel 1950 2200 0    47   Input ~ 0
K6_SET_SIGNL
Text GLabel 5600 750  2    47   Input ~ 0
K6_RESET_SIGNL
Text GLabel 1950 2500 0    47   Input ~ 0
K7_SET_SIGNL
Text GLabel 5600 600  2    47   Input ~ 0
K7_RESET_SIGNL
Text GLabel 3150 2900 2    47   Input ~ 0
K12_SET_SIGNL
Text GLabel 5900 5550 2    47   Input ~ 0
K12_RESET_SIGNL
Text GLabel 3150 2800 2    47   Input ~ 0
K13_SET_SIGNL
Text GLabel 5900 5650 2    47   Input ~ 0
K13_RESET_SIGNL
Text GLabel 3150 2600 2    47   Input ~ 0
K14_SET_SIGNL
Text GLabel 5900 5750 2    47   Input ~ 0
K14_RESET_SIGNL
Text GLabel 3150 2300 2    47   Input ~ 0
K15_SET_SIGNL
Text GLabel 5900 5850 2    47   Input ~ 0
K15_RESET_SIGNL
Text GLabel 1850 1500 0    50   Input ~ 0
PI_GND
Wire Wire Line
	1950 1400 2200 1400
Wire Wire Line
	1950 1600 2200 1600
Text GLabel 1850 2300 0    50   Input ~ 0
PI_GND
Text GLabel 2200 3000 0    50   Input ~ 0
PI_GND
Text GLabel 3450 2700 2    50   Input ~ 0
PI_GND
Text GLabel 3450 2500 2    50   Input ~ 0
PI_GND
Text GLabel 3450 2000 2    50   Input ~ 0
PI_GND
Text GLabel 3450 1700 2    50   Input ~ 0
PI_GND
Text GLabel 4000 1400 2    50   Input ~ 0
PI_GND
Text GLabel 3350 1100 2    50   Input ~ 0
PI_+5V
Text GLabel 4000 1200 2    50   Input ~ 0
PI_+5V
Text GLabel 5350 950  0    50   Input ~ 0
RES_ARRAY_RESET
Wire Wire Line
	5600 1350 5500 1350
Wire Wire Line
	5500 1350 5500 1200
Wire Wire Line
	5500 600  5600 600 
Wire Wire Line
	5600 750  5500 750 
Connection ~ 5500 750 
Wire Wire Line
	5500 750  5500 600 
Wire Wire Line
	5600 900  5500 900 
Connection ~ 5500 900 
Wire Wire Line
	5500 900  5500 750 
Wire Wire Line
	5600 1050 5500 1050
Connection ~ 5500 1050
Wire Wire Line
	5500 1050 5500 950 
Wire Wire Line
	5600 1200 5500 1200
Connection ~ 5500 1200
Wire Wire Line
	5500 1200 5500 1050
Wire Wire Line
	5500 950  5350 950 
Connection ~ 5500 950 
Wire Wire Line
	5500 950  5500 900 
Text GLabel 1950 2600 0    50   Input ~ 0
RES_ARRAY_RESET_SIGNL
Wire Wire Line
	1950 2500 2200 2500
Wire Wire Line
	1950 2600 2200 2600
Wire Wire Line
	1950 2200 2200 2200
Wire Wire Line
	1950 2100 2200 2100
Wire Wire Line
	1950 2000 2200 2000
Wire Wire Line
	1950 1700 2200 1700
Wire Wire Line
	1950 1800 2200 1800
Text GLabel 3150 2200 2    50   Input ~ 0
BANK_A_RESET_SIGNL
Text GLabel 3150 2100 2    50   Input ~ 0
BANK_B_RESET_SIGNL
Wire Wire Line
	1950 2700 2200 2700
Wire Wire Line
	1950 2800 2200 2800
Wire Wire Line
	1950 2900 2200 2900
Wire Wire Line
	3000 3000 3150 3000
Wire Wire Line
	3000 2800 3150 2800
Wire Wire Line
	3000 2600 3150 2600
Wire Wire Line
	3000 2100 3150 2100
Wire Wire Line
	3000 2200 3150 2200
Wire Wire Line
	3000 2300 3150 2300
Text GLabel 5700 3400 0    50   Input ~ 0
BANK_A_RESET
Text GLabel 5700 5700 0    50   Input ~ 0
BANK_B_RESET
Wire Wire Line
	5700 3400 5850 3400
Wire Wire Line
	5850 3400 5850 3450
Wire Wire Line
	5850 3550 6000 3550
Wire Wire Line
	5850 3400 5850 3350
Wire Wire Line
	5850 3250 6000 3250
Connection ~ 5850 3400
Wire Wire Line
	6000 3350 5850 3350
Connection ~ 5850 3350
Wire Wire Line
	5850 3350 5850 3250
Wire Wire Line
	6000 3450 5850 3450
Connection ~ 5850 3450
Wire Wire Line
	5850 3450 5850 3550
Wire Wire Line
	5900 5550 5700 5550
Wire Wire Line
	5700 5550 5700 5650
Wire Wire Line
	5700 5850 5900 5850
Wire Wire Line
	5900 5750 5700 5750
Connection ~ 5700 5750
Wire Wire Line
	5700 5750 5700 5850
Wire Wire Line
	5900 5650 5700 5650
Connection ~ 5700 5650
Wire Wire Line
	5700 5650 5700 5750
NoConn ~ 2200 2400
NoConn ~ 3000 2400
$Comp
L dk_Transistors-Bipolar-BJT-Single:MMBT2222A-7-F Q1
U 1 1 60E73212
P 1800 3550
F 0 "Q1" H 1988 3603 60  0000 L CNN
F 1 "MMBT2222A" H 1988 3497 60  0000 L CNN
F 2 "digikey-footprints:SOT-23-3" H 2000 3750 60  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 2000 3850 60  0001 L CNN
F 4 "MMBT2222A-FDICT-ND" H 2000 3950 60  0001 L CNN "Digi-Key_PN"
F 5 "MMBT2222A-7-F" H 2000 4050 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 2000 4150 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 2000 4250 60  0001 L CNN "Family"
F 8 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 2000 4350 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/diodes-incorporated/MMBT2222A-7-F/MMBT2222A-FDICT-ND/815723" H 2000 4450 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V 0.6A SMD SOT23-3" H 2000 4550 60  0001 L CNN "Description"
F 11 "Diodes Incorporated" H 2000 4650 60  0001 L CNN "Manufacturer"
F 12 "Active" H 2000 4750 60  0001 L CNN "Status"
	1    1800 3550
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R7
U 1 1 60E73AB0
P 1300 3550
F 0 "R7" V 1095 3550 50  0000 C CNN
F 1 "300R" V 1186 3550 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 1300 3550 50  0001 C CNN
F 3 "~" H 1300 3550 50  0001 C CNN
	1    1300 3550
	0    1    1    0   
$EndComp
Wire Wire Line
	1400 3550 1600 3550
Text GLabel 8450 2650 0    47   Input ~ 0
K10_SET
Text GLabel 8450 2000 0    47   Input ~ 0
K9_SET
Text GLabel 1900 3300 0    47   Input ~ 0
K1_SET
Text GLabel 3250 3300 2    47   Input ~ 0
K1_RESET
Text GLabel 1900 3950 0    47   Input ~ 0
K2_SET
Text GLabel 1900 4650 0    47   Input ~ 0
K3_SET
Text GLabel 1900 5350 0    47   Input ~ 0
K4_SET
Text GLabel 1900 6050 0    47   Input ~ 0
K5_SET
Text GLabel 1900 6850 0    47   Input ~ 0
K6_SET
Text GLabel 8450 700  0    47   Input ~ 0
K7_SET
Text GLabel 9800 3300 2    47   Input ~ 0
K11_RESET
Text GLabel 9800 2650 2    47   Input ~ 0
K10_RESET
Text GLabel 9800 2000 2    47   Input ~ 0
K9_RESET
Text GLabel 9800 1350 2    47   Input ~ 0
K8_RESET
Text GLabel 3250 4000 2    47   Input ~ 0
K2_RESET
Text GLabel 3250 4650 2    47   Input ~ 0
K3_RESET
Text GLabel 3250 5300 2    47   Input ~ 0
K4_RESET
Text GLabel 3250 6000 2    47   Input ~ 0
K5_RESET
Text GLabel 3250 6650 2    47   Input ~ 0
K6_RESET
Text GLabel 9800 700  2    47   Input ~ 0
K7_RESET
Text GLabel 9800 3950 2    47   Input ~ 0
K12_RESET
Text GLabel 9800 4700 2    47   Input ~ 0
K13_RESET
Text GLabel 9800 5300 2    47   Input ~ 0
K14_RESET
Text GLabel 9800 5950 2    47   Input ~ 0
K15_RESET
Text GLabel 7700 2900 0    47   Input ~ 0
K10_SET_SIGNL
Text GLabel 7700 2250 0    47   Input ~ 0
K9_SET_SIGNL
Text GLabel 7700 1600 0    47   Input ~ 0
K8_SET_SIGNL
Text GLabel 1150 3550 0    47   Input ~ 0
K1_SET_SGNL
Text GLabel 3950 3550 2    47   Input ~ 0
K1_RESET_SIGNL
Text GLabel 1150 4200 0    47   Input ~ 0
K2_SET_SIGNL
Text GLabel 1150 4900 0    47   Input ~ 0
K3_SET_SIGNL
Text GLabel 1150 5600 0    47   Input ~ 0
K4_SET_SIGNL
Text GLabel 1150 6300 0    47   Input ~ 0
K5_SET_SIGNL
Text GLabel 1150 7100 0    47   Input ~ 0
K6_SET_SIGNL
Text GLabel 7700 950  0    47   Input ~ 0
K7_SET_SIGNL
Text GLabel 7700 3550 0    47   Input ~ 0
K11_SET_SIGNL
Text GLabel 7700 4200 0    47   Input ~ 0
K12_SET_SIGNL
Text GLabel 7700 4900 0    47   Input ~ 0
K13_SET_SIGNL
Text GLabel 7700 5550 0    47   Input ~ 0
K14_SET_SIGNL
Text GLabel 7700 6200 0    47   Input ~ 0
K15_SET_SIGNL
Text GLabel 10500 3550 2    47   Input ~ 0
K11_RESET_SIGNL
Text GLabel 10500 2900 2    47   Input ~ 0
K10_RESET_SIGNL
Text GLabel 10500 2250 2    47   Input ~ 0
K9_RESET_SIGNL
Text GLabel 10500 1600 2    47   Input ~ 0
K8_RESET_SIGNL
Text GLabel 3950 4250 2    47   Input ~ 0
K2_RESET_SIGNL
Text GLabel 3950 4900 2    47   Input ~ 0
K3_RESET_SIGNL
Text GLabel 3950 5550 2    47   Input ~ 0
K4_RESET_SIGNL
Text GLabel 3950 6250 2    47   Input ~ 0
K5_RESET_SIGNL
Text GLabel 3950 6900 2    47   Input ~ 0
K6_RESET_SIGNL
Text GLabel 10500 950  2    47   Input ~ 0
K7_RESET_SIGNL
Text GLabel 10500 4200 2    47   Input ~ 0
K12_RESET_SIGNL
Text GLabel 10500 4900 2    47   Input ~ 0
K13_RESET_SIGNL
Text GLabel 10500 5550 2    47   Input ~ 0
K14_RESET_SIGNL
Text GLabel 10500 6200 2    47   Input ~ 0
K15_RESET_SIGNL
Text GLabel 1900 3800 0    50   Input ~ 0
PI_GND
$Comp
L dk_Transistors-Bipolar-BJT-Single:MMBT2222A-7-F Q7
U 1 1 60EB2A99
P 3350 3550
F 0 "Q7" H 3538 3603 60  0000 L CNN
F 1 "MMBT2222A" H 3538 3497 60  0000 L CNN
F 2 "digikey-footprints:SOT-23-3" H 3550 3750 60  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 3550 3850 60  0001 L CNN
F 4 "MMBT2222A-FDICT-ND" H 3550 3950 60  0001 L CNN "Digi-Key_PN"
F 5 "MMBT2222A-7-F" H 3550 4050 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 3550 4150 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 3550 4250 60  0001 L CNN "Family"
F 8 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 3550 4350 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/diodes-incorporated/MMBT2222A-7-F/MMBT2222A-FDICT-ND/815723" H 3550 4450 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V 0.6A SMD SOT23-3" H 3550 4550 60  0001 L CNN "Description"
F 11 "Diodes Incorporated" H 3550 4650 60  0001 L CNN "Manufacturer"
F 12 "Active" H 3550 4750 60  0001 L CNN "Status"
	1    3350 3550
	-1   0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R13
U 1 1 60EB2A9F
P 3850 3550
F 0 "R13" V 3645 3550 50  0000 C CNN
F 1 "300R" V 3736 3550 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 3850 3550 50  0001 C CNN
F 3 "~" H 3850 3550 50  0001 C CNN
	1    3850 3550
	0    -1   1    0   
$EndComp
Wire Wire Line
	3750 3550 3550 3550
Text GLabel 3250 3800 2    50   Input ~ 0
PI_GND
Wire Wire Line
	1900 3300 1900 3350
Wire Wire Line
	1900 3800 1900 3750
Wire Wire Line
	1150 3550 1200 3550
$Comp
L dk_Transistors-Bipolar-BJT-Single:MMBT2222A-7-F Q8
U 1 1 60EFD956
P 3350 4250
F 0 "Q8" H 3538 4303 60  0000 L CNN
F 1 "MMBT2222A" H 3538 4197 60  0000 L CNN
F 2 "digikey-footprints:SOT-23-3" H 3550 4450 60  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 3550 4550 60  0001 L CNN
F 4 "MMBT2222A-FDICT-ND" H 3550 4650 60  0001 L CNN "Digi-Key_PN"
F 5 "MMBT2222A-7-F" H 3550 4750 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 3550 4850 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 3550 4950 60  0001 L CNN "Family"
F 8 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 3550 5050 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/diodes-incorporated/MMBT2222A-7-F/MMBT2222A-FDICT-ND/815723" H 3550 5150 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V 0.6A SMD SOT23-3" H 3550 5250 60  0001 L CNN "Description"
F 11 "Diodes Incorporated" H 3550 5350 60  0001 L CNN "Manufacturer"
F 12 "Active" H 3550 5450 60  0001 L CNN "Status"
	1    3350 4250
	-1   0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R14
U 1 1 60EFD95C
P 3850 4250
F 0 "R14" V 3645 4250 50  0000 C CNN
F 1 "300R" V 3736 4250 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 3850 4250 50  0001 C CNN
F 3 "~" H 3850 4250 50  0001 C CNN
	1    3850 4250
	0    -1   1    0   
$EndComp
Wire Wire Line
	3750 4250 3550 4250
Text GLabel 3250 4500 2    50   Input ~ 0
PI_GND
$Comp
L dk_Transistors-Bipolar-BJT-Single:MMBT2222A-7-F Q9
U 1 1 60EFF39B
P 3350 4900
F 0 "Q9" H 3538 4953 60  0000 L CNN
F 1 "MMBT2222A" H 3538 4847 60  0000 L CNN
F 2 "digikey-footprints:SOT-23-3" H 3550 5100 60  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 3550 5200 60  0001 L CNN
F 4 "MMBT2222A-FDICT-ND" H 3550 5300 60  0001 L CNN "Digi-Key_PN"
F 5 "MMBT2222A-7-F" H 3550 5400 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 3550 5500 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 3550 5600 60  0001 L CNN "Family"
F 8 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 3550 5700 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/diodes-incorporated/MMBT2222A-7-F/MMBT2222A-FDICT-ND/815723" H 3550 5800 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V 0.6A SMD SOT23-3" H 3550 5900 60  0001 L CNN "Description"
F 11 "Diodes Incorporated" H 3550 6000 60  0001 L CNN "Manufacturer"
F 12 "Active" H 3550 6100 60  0001 L CNN "Status"
	1    3350 4900
	-1   0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R15
U 1 1 60EFF3A1
P 3850 4900
F 0 "R15" V 3645 4900 50  0000 C CNN
F 1 "300R" V 3736 4900 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 3850 4900 50  0001 C CNN
F 3 "~" H 3850 4900 50  0001 C CNN
	1    3850 4900
	0    -1   1    0   
$EndComp
Wire Wire Line
	3750 4900 3550 4900
Text GLabel 3250 5150 2    50   Input ~ 0
PI_GND
$Comp
L dk_Transistors-Bipolar-BJT-Single:MMBT2222A-7-F Q10
U 1 1 60F01200
P 3350 5550
F 0 "Q10" H 3538 5603 60  0000 L CNN
F 1 "MMBT2222A" H 3538 5497 60  0000 L CNN
F 2 "digikey-footprints:SOT-23-3" H 3550 5750 60  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 3550 5850 60  0001 L CNN
F 4 "MMBT2222A-FDICT-ND" H 3550 5950 60  0001 L CNN "Digi-Key_PN"
F 5 "MMBT2222A-7-F" H 3550 6050 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 3550 6150 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 3550 6250 60  0001 L CNN "Family"
F 8 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 3550 6350 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/diodes-incorporated/MMBT2222A-7-F/MMBT2222A-FDICT-ND/815723" H 3550 6450 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V 0.6A SMD SOT23-3" H 3550 6550 60  0001 L CNN "Description"
F 11 "Diodes Incorporated" H 3550 6650 60  0001 L CNN "Manufacturer"
F 12 "Active" H 3550 6750 60  0001 L CNN "Status"
	1    3350 5550
	-1   0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R16
U 1 1 60F01206
P 3850 5550
F 0 "R16" V 3645 5550 50  0000 C CNN
F 1 "300R" V 3736 5550 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 3850 5550 50  0001 C CNN
F 3 "~" H 3850 5550 50  0001 C CNN
	1    3850 5550
	0    -1   1    0   
$EndComp
Wire Wire Line
	3750 5550 3550 5550
Text GLabel 3250 5800 2    50   Input ~ 0
PI_GND
$Comp
L dk_Transistors-Bipolar-BJT-Single:MMBT2222A-7-F Q11
U 1 1 60F03ED6
P 3350 6250
F 0 "Q11" H 3538 6303 60  0000 L CNN
F 1 "MMBT2222A" H 3538 6197 60  0000 L CNN
F 2 "digikey-footprints:SOT-23-3" H 3550 6450 60  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 3550 6550 60  0001 L CNN
F 4 "MMBT2222A-FDICT-ND" H 3550 6650 60  0001 L CNN "Digi-Key_PN"
F 5 "MMBT2222A-7-F" H 3550 6750 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 3550 6850 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 3550 6950 60  0001 L CNN "Family"
F 8 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 3550 7050 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/diodes-incorporated/MMBT2222A-7-F/MMBT2222A-FDICT-ND/815723" H 3550 7150 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V 0.6A SMD SOT23-3" H 3550 7250 60  0001 L CNN "Description"
F 11 "Diodes Incorporated" H 3550 7350 60  0001 L CNN "Manufacturer"
F 12 "Active" H 3550 7450 60  0001 L CNN "Status"
	1    3350 6250
	-1   0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R17
U 1 1 60F03EDC
P 3850 6250
F 0 "R17" V 3645 6250 50  0000 C CNN
F 1 "300R" V 3736 6250 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 3850 6250 50  0001 C CNN
F 3 "~" H 3850 6250 50  0001 C CNN
	1    3850 6250
	0    -1   1    0   
$EndComp
Wire Wire Line
	3750 6250 3550 6250
Text GLabel 3250 6500 2    50   Input ~ 0
PI_GND
$Comp
L dk_Transistors-Bipolar-BJT-Single:MMBT2222A-7-F Q2
U 1 1 60F0AD61
P 1800 4200
F 0 "Q2" H 1988 4253 60  0000 L CNN
F 1 "MMBT2222A" H 1988 4147 60  0000 L CNN
F 2 "digikey-footprints:SOT-23-3" H 2000 4400 60  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 2000 4500 60  0001 L CNN
F 4 "MMBT2222A-FDICT-ND" H 2000 4600 60  0001 L CNN "Digi-Key_PN"
F 5 "MMBT2222A-7-F" H 2000 4700 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 2000 4800 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 2000 4900 60  0001 L CNN "Family"
F 8 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 2000 5000 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/diodes-incorporated/MMBT2222A-7-F/MMBT2222A-FDICT-ND/815723" H 2000 5100 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V 0.6A SMD SOT23-3" H 2000 5200 60  0001 L CNN "Description"
F 11 "Diodes Incorporated" H 2000 5300 60  0001 L CNN "Manufacturer"
F 12 "Active" H 2000 5400 60  0001 L CNN "Status"
	1    1800 4200
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R8
U 1 1 60F0AD67
P 1300 4200
F 0 "R8" V 1095 4200 50  0000 C CNN
F 1 "300R" V 1186 4200 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 1300 4200 50  0001 C CNN
F 3 "~" H 1300 4200 50  0001 C CNN
	1    1300 4200
	0    1    1    0   
$EndComp
Wire Wire Line
	1400 4200 1600 4200
Text GLabel 1900 4450 0    50   Input ~ 0
PI_GND
Wire Wire Line
	1900 3950 1900 4000
Wire Wire Line
	1900 4450 1900 4400
Wire Wire Line
	1150 4200 1200 4200
$Comp
L dk_Transistors-Bipolar-BJT-Single:MMBT2222A-7-F Q3
U 1 1 60F0E495
P 1800 4900
F 0 "Q3" H 1988 4953 60  0000 L CNN
F 1 "MMBT2222A" H 1988 4847 60  0000 L CNN
F 2 "digikey-footprints:SOT-23-3" H 2000 5100 60  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 2000 5200 60  0001 L CNN
F 4 "MMBT2222A-FDICT-ND" H 2000 5300 60  0001 L CNN "Digi-Key_PN"
F 5 "MMBT2222A-7-F" H 2000 5400 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 2000 5500 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 2000 5600 60  0001 L CNN "Family"
F 8 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 2000 5700 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/diodes-incorporated/MMBT2222A-7-F/MMBT2222A-FDICT-ND/815723" H 2000 5800 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V 0.6A SMD SOT23-3" H 2000 5900 60  0001 L CNN "Description"
F 11 "Diodes Incorporated" H 2000 6000 60  0001 L CNN "Manufacturer"
F 12 "Active" H 2000 6100 60  0001 L CNN "Status"
	1    1800 4900
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R9
U 1 1 60F0E49B
P 1300 4900
F 0 "R9" V 1095 4900 50  0000 C CNN
F 1 "300R" V 1186 4900 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 1300 4900 50  0001 C CNN
F 3 "~" H 1300 4900 50  0001 C CNN
	1    1300 4900
	0    1    1    0   
$EndComp
Wire Wire Line
	1400 4900 1600 4900
Text GLabel 1900 5150 0    50   Input ~ 0
PI_GND
Wire Wire Line
	1900 4650 1900 4700
Wire Wire Line
	1900 5150 1900 5100
Wire Wire Line
	1150 4900 1200 4900
$Comp
L dk_Transistors-Bipolar-BJT-Single:MMBT2222A-7-F Q4
U 1 1 60F1102E
P 1800 5600
F 0 "Q4" H 1988 5653 60  0000 L CNN
F 1 "MMBT2222A" H 1988 5547 60  0000 L CNN
F 2 "digikey-footprints:SOT-23-3" H 2000 5800 60  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 2000 5900 60  0001 L CNN
F 4 "MMBT2222A-FDICT-ND" H 2000 6000 60  0001 L CNN "Digi-Key_PN"
F 5 "MMBT2222A-7-F" H 2000 6100 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 2000 6200 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 2000 6300 60  0001 L CNN "Family"
F 8 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 2000 6400 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/diodes-incorporated/MMBT2222A-7-F/MMBT2222A-FDICT-ND/815723" H 2000 6500 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V 0.6A SMD SOT23-3" H 2000 6600 60  0001 L CNN "Description"
F 11 "Diodes Incorporated" H 2000 6700 60  0001 L CNN "Manufacturer"
F 12 "Active" H 2000 6800 60  0001 L CNN "Status"
	1    1800 5600
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R10
U 1 1 60F11034
P 1300 5600
F 0 "R10" V 1095 5600 50  0000 C CNN
F 1 "300R" V 1186 5600 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 1300 5600 50  0001 C CNN
F 3 "~" H 1300 5600 50  0001 C CNN
	1    1300 5600
	0    1    1    0   
$EndComp
Wire Wire Line
	1400 5600 1600 5600
Text GLabel 1900 5850 0    50   Input ~ 0
PI_GND
Wire Wire Line
	1900 5350 1900 5400
Wire Wire Line
	1900 5850 1900 5800
Wire Wire Line
	1150 5600 1200 5600
$Comp
L dk_Transistors-Bipolar-BJT-Single:MMBT2222A-7-F Q5
U 1 1 60F13C3F
P 1800 6300
F 0 "Q5" H 1988 6353 60  0000 L CNN
F 1 "MMBT2222A" H 1988 6247 60  0000 L CNN
F 2 "digikey-footprints:SOT-23-3" H 2000 6500 60  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 2000 6600 60  0001 L CNN
F 4 "MMBT2222A-FDICT-ND" H 2000 6700 60  0001 L CNN "Digi-Key_PN"
F 5 "MMBT2222A-7-F" H 2000 6800 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 2000 6900 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 2000 7000 60  0001 L CNN "Family"
F 8 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 2000 7100 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/diodes-incorporated/MMBT2222A-7-F/MMBT2222A-FDICT-ND/815723" H 2000 7200 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V 0.6A SMD SOT23-3" H 2000 7300 60  0001 L CNN "Description"
F 11 "Diodes Incorporated" H 2000 7400 60  0001 L CNN "Manufacturer"
F 12 "Active" H 2000 7500 60  0001 L CNN "Status"
	1    1800 6300
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R11
U 1 1 60F13C45
P 1300 6300
F 0 "R11" V 1095 6300 50  0000 C CNN
F 1 "300R" V 1186 6300 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 1300 6300 50  0001 C CNN
F 3 "~" H 1300 6300 50  0001 C CNN
	1    1300 6300
	0    1    1    0   
$EndComp
Wire Wire Line
	1400 6300 1600 6300
Text GLabel 1900 6550 0    50   Input ~ 0
PI_GND
Wire Wire Line
	1900 6050 1900 6100
Wire Wire Line
	1900 6550 1900 6500
Wire Wire Line
	1150 6300 1200 6300
$Comp
L Device:R_Small_US R12
U 1 1 60FA73F2
P 1300 7100
F 0 "R12" V 1095 7100 50  0000 C CNN
F 1 "300R" V 1186 7100 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 1300 7100 50  0001 C CNN
F 3 "~" H 1300 7100 50  0001 C CNN
	1    1300 7100
	0    1    1    0   
$EndComp
Wire Wire Line
	1400 7100 1600 7100
Text GLabel 1900 7350 0    50   Input ~ 0
PI_GND
Wire Wire Line
	1900 6850 1900 6900
Wire Wire Line
	1900 7350 1900 7300
Wire Wire Line
	1150 7100 1200 7100
$Comp
L dk_Transistors-Bipolar-BJT-Single:MMBT2222A-7-F Q6
U 1 1 60FA73EC
P 1800 7100
F 0 "Q6" H 1988 7153 60  0000 L CNN
F 1 "MMBT2222A" H 1988 7047 60  0000 L CNN
F 2 "digikey-footprints:SOT-23-3" H 2000 7300 60  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 2000 7400 60  0001 L CNN
F 4 "MMBT2222A-FDICT-ND" H 2000 7500 60  0001 L CNN "Digi-Key_PN"
F 5 "MMBT2222A-7-F" H 2000 7600 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 2000 7700 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 2000 7800 60  0001 L CNN "Family"
F 8 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 2000 7900 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/diodes-incorporated/MMBT2222A-7-F/MMBT2222A-FDICT-ND/815723" H 2000 8000 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V 0.6A SMD SOT23-3" H 2000 8100 60  0001 L CNN "Description"
F 11 "Diodes Incorporated" H 2000 8200 60  0001 L CNN "Manufacturer"
F 12 "Active" H 2000 8300 60  0001 L CNN "Status"
	1    1800 7100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 3750 3250 3800
Wire Wire Line
	3250 3300 3250 3350
Wire Wire Line
	3250 4000 3250 4050
Wire Wire Line
	3250 4500 3250 4450
Wire Wire Line
	3250 5150 3250 5100
Wire Wire Line
	3250 4700 3250 4650
Wire Wire Line
	3250 5350 3250 5300
Wire Wire Line
	3250 5800 3250 5750
Wire Wire Line
	3250 6050 3250 6000
Wire Wire Line
	3250 6450 3250 6500
$Comp
L dk_Transistors-Bipolar-BJT-Single:MMBT2222A-7-F Q12
U 1 1 6109140A
P 3350 6900
F 0 "Q12" H 3538 6953 60  0000 L CNN
F 1 "MMBT2222A" H 3538 6847 60  0000 L CNN
F 2 "digikey-footprints:SOT-23-3" H 3550 7100 60  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 3550 7200 60  0001 L CNN
F 4 "MMBT2222A-FDICT-ND" H 3550 7300 60  0001 L CNN "Digi-Key_PN"
F 5 "MMBT2222A-7-F" H 3550 7400 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 3550 7500 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 3550 7600 60  0001 L CNN "Family"
F 8 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 3550 7700 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/diodes-incorporated/MMBT2222A-7-F/MMBT2222A-FDICT-ND/815723" H 3550 7800 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V 0.6A SMD SOT23-3" H 3550 7900 60  0001 L CNN "Description"
F 11 "Diodes Incorporated" H 3550 8000 60  0001 L CNN "Manufacturer"
F 12 "Active" H 3550 8100 60  0001 L CNN "Status"
	1    3350 6900
	-1   0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R18
U 1 1 61091410
P 3850 6900
F 0 "R18" V 3645 6900 50  0000 C CNN
F 1 "300R" V 3736 6900 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 3850 6900 50  0001 C CNN
F 3 "~" H 3850 6900 50  0001 C CNN
	1    3850 6900
	0    -1   1    0   
$EndComp
Wire Wire Line
	3750 6900 3550 6900
Text GLabel 3250 7150 2    50   Input ~ 0
PI_GND
Wire Wire Line
	3250 6700 3250 6650
Wire Wire Line
	3250 7100 3250 7150
$Comp
L dk_Transistors-Bipolar-BJT-Single:MMBT2222A-7-F Q16
U 1 1 610E1BC8
P 8350 950
F 0 "Q16" H 8538 1003 60  0000 L CNN
F 1 "MMBT2222A" H 8538 897 60  0000 L CNN
F 2 "digikey-footprints:SOT-23-3" H 8550 1150 60  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 8550 1250 60  0001 L CNN
F 4 "MMBT2222A-FDICT-ND" H 8550 1350 60  0001 L CNN "Digi-Key_PN"
F 5 "MMBT2222A-7-F" H 8550 1450 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 8550 1550 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 8550 1650 60  0001 L CNN "Family"
F 8 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 8550 1750 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/diodes-incorporated/MMBT2222A-7-F/MMBT2222A-FDICT-ND/815723" H 8550 1850 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V 0.6A SMD SOT23-3" H 8550 1950 60  0001 L CNN "Description"
F 11 "Diodes Incorporated" H 8550 2050 60  0001 L CNN "Manufacturer"
F 12 "Active" H 8550 2150 60  0001 L CNN "Status"
	1    8350 950 
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R22
U 1 1 610E1BCE
P 7850 950
F 0 "R22" V 7645 950 50  0000 C CNN
F 1 "300R" V 7736 950 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 7850 950 50  0001 C CNN
F 3 "~" H 7850 950 50  0001 C CNN
	1    7850 950 
	0    1    1    0   
$EndComp
Wire Wire Line
	7950 950  8150 950 
Text GLabel 8450 1200 0    50   Input ~ 0
PI_GND
$Comp
L dk_Transistors-Bipolar-BJT-Single:MMBT2222A-7-F Q25
U 1 1 610E1BF7
P 9900 950
F 0 "Q25" H 10088 1003 60  0000 L CNN
F 1 "MMBT2222A" H 10088 897 60  0000 L CNN
F 2 "digikey-footprints:SOT-23-3" H 10100 1150 60  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 10100 1250 60  0001 L CNN
F 4 "MMBT2222A-FDICT-ND" H 10100 1350 60  0001 L CNN "Digi-Key_PN"
F 5 "MMBT2222A-7-F" H 10100 1450 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 10100 1550 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 10100 1650 60  0001 L CNN "Family"
F 8 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 10100 1750 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/diodes-incorporated/MMBT2222A-7-F/MMBT2222A-FDICT-ND/815723" H 10100 1850 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V 0.6A SMD SOT23-3" H 10100 1950 60  0001 L CNN "Description"
F 11 "Diodes Incorporated" H 10100 2050 60  0001 L CNN "Manufacturer"
F 12 "Active" H 10100 2150 60  0001 L CNN "Status"
	1    9900 950 
	-1   0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R31
U 1 1 610E1BFD
P 10400 950
F 0 "R31" V 10195 950 50  0000 C CNN
F 1 "300R" V 10286 950 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 10400 950 50  0001 C CNN
F 3 "~" H 10400 950 50  0001 C CNN
	1    10400 950 
	0    -1   1    0   
$EndComp
Wire Wire Line
	10300 950  10100 950 
Text GLabel 9800 1200 2    50   Input ~ 0
PI_GND
Wire Wire Line
	8450 700  8450 750 
Wire Wire Line
	8450 1200 8450 1150
Wire Wire Line
	7700 950  7750 950 
$Comp
L dk_Transistors-Bipolar-BJT-Single:MMBT2222A-7-F Q26
U 1 1 610E1C12
P 9900 1600
F 0 "Q26" H 10088 1653 60  0000 L CNN
F 1 "MMBT2222A" H 10088 1547 60  0000 L CNN
F 2 "digikey-footprints:SOT-23-3" H 10100 1800 60  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 10100 1900 60  0001 L CNN
F 4 "MMBT2222A-FDICT-ND" H 10100 2000 60  0001 L CNN "Digi-Key_PN"
F 5 "MMBT2222A-7-F" H 10100 2100 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 10100 2200 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 10100 2300 60  0001 L CNN "Family"
F 8 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 10100 2400 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/diodes-incorporated/MMBT2222A-7-F/MMBT2222A-FDICT-ND/815723" H 10100 2500 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V 0.6A SMD SOT23-3" H 10100 2600 60  0001 L CNN "Description"
F 11 "Diodes Incorporated" H 10100 2700 60  0001 L CNN "Manufacturer"
F 12 "Active" H 10100 2800 60  0001 L CNN "Status"
	1    9900 1600
	-1   0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R32
U 1 1 610E1C18
P 10400 1600
F 0 "R32" V 10195 1600 50  0000 C CNN
F 1 "300R" V 10286 1600 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 10400 1600 50  0001 C CNN
F 3 "~" H 10400 1600 50  0001 C CNN
	1    10400 1600
	0    -1   1    0   
$EndComp
Wire Wire Line
	10300 1600 10100 1600
Text GLabel 9800 1850 2    50   Input ~ 0
PI_GND
$Comp
L dk_Transistors-Bipolar-BJT-Single:MMBT2222A-7-F Q27
U 1 1 610E1C2A
P 9900 2250
F 0 "Q27" H 10088 2303 60  0000 L CNN
F 1 "MMBT2222A" H 10088 2197 60  0000 L CNN
F 2 "digikey-footprints:SOT-23-3" H 10100 2450 60  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 10100 2550 60  0001 L CNN
F 4 "MMBT2222A-FDICT-ND" H 10100 2650 60  0001 L CNN "Digi-Key_PN"
F 5 "MMBT2222A-7-F" H 10100 2750 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 10100 2850 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 10100 2950 60  0001 L CNN "Family"
F 8 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 10100 3050 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/diodes-incorporated/MMBT2222A-7-F/MMBT2222A-FDICT-ND/815723" H 10100 3150 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V 0.6A SMD SOT23-3" H 10100 3250 60  0001 L CNN "Description"
F 11 "Diodes Incorporated" H 10100 3350 60  0001 L CNN "Manufacturer"
F 12 "Active" H 10100 3450 60  0001 L CNN "Status"
	1    9900 2250
	-1   0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R33
U 1 1 610E1C30
P 10400 2250
F 0 "R33" V 10195 2250 50  0000 C CNN
F 1 "300R" V 10286 2250 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 10400 2250 50  0001 C CNN
F 3 "~" H 10400 2250 50  0001 C CNN
	1    10400 2250
	0    -1   1    0   
$EndComp
Wire Wire Line
	10300 2250 10100 2250
Text GLabel 9800 2500 2    50   Input ~ 0
PI_GND
$Comp
L dk_Transistors-Bipolar-BJT-Single:MMBT2222A-7-F Q28
U 1 1 610E1C42
P 9900 2900
F 0 "Q28" H 10088 2953 60  0000 L CNN
F 1 "MMBT2222A" H 10088 2847 60  0000 L CNN
F 2 "digikey-footprints:SOT-23-3" H 10100 3100 60  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 10100 3200 60  0001 L CNN
F 4 "MMBT2222A-FDICT-ND" H 10100 3300 60  0001 L CNN "Digi-Key_PN"
F 5 "MMBT2222A-7-F" H 10100 3400 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 10100 3500 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 10100 3600 60  0001 L CNN "Family"
F 8 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 10100 3700 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/diodes-incorporated/MMBT2222A-7-F/MMBT2222A-FDICT-ND/815723" H 10100 3800 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V 0.6A SMD SOT23-3" H 10100 3900 60  0001 L CNN "Description"
F 11 "Diodes Incorporated" H 10100 4000 60  0001 L CNN "Manufacturer"
F 12 "Active" H 10100 4100 60  0001 L CNN "Status"
	1    9900 2900
	-1   0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R34
U 1 1 610E1C48
P 10400 2900
F 0 "R34" V 10195 2900 50  0000 C CNN
F 1 "300R" V 10286 2900 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 10400 2900 50  0001 C CNN
F 3 "~" H 10400 2900 50  0001 C CNN
	1    10400 2900
	0    -1   1    0   
$EndComp
Wire Wire Line
	10300 2900 10100 2900
Text GLabel 9800 3150 2    50   Input ~ 0
PI_GND
$Comp
L dk_Transistors-Bipolar-BJT-Single:MMBT2222A-7-F Q29
U 1 1 610E1C5A
P 9900 3550
F 0 "Q29" H 10088 3603 60  0000 L CNN
F 1 "MMBT2222A" H 10088 3497 60  0000 L CNN
F 2 "digikey-footprints:SOT-23-3" H 10100 3750 60  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 10100 3850 60  0001 L CNN
F 4 "MMBT2222A-FDICT-ND" H 10100 3950 60  0001 L CNN "Digi-Key_PN"
F 5 "MMBT2222A-7-F" H 10100 4050 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 10100 4150 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 10100 4250 60  0001 L CNN "Family"
F 8 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 10100 4350 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/diodes-incorporated/MMBT2222A-7-F/MMBT2222A-FDICT-ND/815723" H 10100 4450 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V 0.6A SMD SOT23-3" H 10100 4550 60  0001 L CNN "Description"
F 11 "Diodes Incorporated" H 10100 4650 60  0001 L CNN "Manufacturer"
F 12 "Active" H 10100 4750 60  0001 L CNN "Status"
	1    9900 3550
	-1   0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R35
U 1 1 610E1C60
P 10400 3550
F 0 "R35" V 10195 3550 50  0000 C CNN
F 1 "300R" V 10286 3550 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 10400 3550 50  0001 C CNN
F 3 "~" H 10400 3550 50  0001 C CNN
	1    10400 3550
	0    -1   1    0   
$EndComp
Wire Wire Line
	10300 3550 10100 3550
Text GLabel 9800 3800 2    50   Input ~ 0
PI_GND
$Comp
L Device:R_Small_US R23
U 1 1 610E1C78
P 7850 1600
F 0 "R23" V 7645 1600 50  0000 C CNN
F 1 "300R" V 7736 1600 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 7850 1600 50  0001 C CNN
F 3 "~" H 7850 1600 50  0001 C CNN
	1    7850 1600
	0    1    1    0   
$EndComp
Wire Wire Line
	7950 1600 8150 1600
Text GLabel 8450 1850 0    50   Input ~ 0
PI_GND
Wire Wire Line
	8450 1350 8450 1400
Wire Wire Line
	8450 1850 8450 1800
Wire Wire Line
	7700 1600 7750 1600
$Comp
L dk_Transistors-Bipolar-BJT-Single:MMBT2222A-7-F Q18
U 1 1 610E1C8C
P 8350 2250
F 0 "Q18" H 8538 2303 60  0000 L CNN
F 1 "MMBT2222A" H 8538 2197 60  0000 L CNN
F 2 "digikey-footprints:SOT-23-3" H 8550 2450 60  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 8550 2550 60  0001 L CNN
F 4 "MMBT2222A-FDICT-ND" H 8550 2650 60  0001 L CNN "Digi-Key_PN"
F 5 "MMBT2222A-7-F" H 8550 2750 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 8550 2850 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 8550 2950 60  0001 L CNN "Family"
F 8 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 8550 3050 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/diodes-incorporated/MMBT2222A-7-F/MMBT2222A-FDICT-ND/815723" H 8550 3150 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V 0.6A SMD SOT23-3" H 8550 3250 60  0001 L CNN "Description"
F 11 "Diodes Incorporated" H 8550 3350 60  0001 L CNN "Manufacturer"
F 12 "Active" H 8550 3450 60  0001 L CNN "Status"
	1    8350 2250
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R24
U 1 1 610E1C92
P 7850 2250
F 0 "R24" V 7645 2250 50  0000 C CNN
F 1 "300R" V 7736 2250 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 7850 2250 50  0001 C CNN
F 3 "~" H 7850 2250 50  0001 C CNN
	1    7850 2250
	0    1    1    0   
$EndComp
Wire Wire Line
	7950 2250 8150 2250
Text GLabel 8450 2500 0    50   Input ~ 0
PI_GND
Wire Wire Line
	8450 2000 8450 2050
Wire Wire Line
	8450 2500 8450 2450
Wire Wire Line
	7700 2250 7750 2250
$Comp
L dk_Transistors-Bipolar-BJT-Single:MMBT2222A-7-F Q19
U 1 1 610E1CA6
P 8350 2900
F 0 "Q19" H 8538 2953 60  0000 L CNN
F 1 "MMBT2222A" H 8538 2847 60  0000 L CNN
F 2 "digikey-footprints:SOT-23-3" H 8550 3100 60  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 8550 3200 60  0001 L CNN
F 4 "MMBT2222A-FDICT-ND" H 8550 3300 60  0001 L CNN "Digi-Key_PN"
F 5 "MMBT2222A-7-F" H 8550 3400 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 8550 3500 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 8550 3600 60  0001 L CNN "Family"
F 8 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 8550 3700 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/diodes-incorporated/MMBT2222A-7-F/MMBT2222A-FDICT-ND/815723" H 8550 3800 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V 0.6A SMD SOT23-3" H 8550 3900 60  0001 L CNN "Description"
F 11 "Diodes Incorporated" H 8550 4000 60  0001 L CNN "Manufacturer"
F 12 "Active" H 8550 4100 60  0001 L CNN "Status"
	1    8350 2900
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R25
U 1 1 610E1CAC
P 7850 2900
F 0 "R25" V 7645 2900 50  0000 C CNN
F 1 "300R" V 7736 2900 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 7850 2900 50  0001 C CNN
F 3 "~" H 7850 2900 50  0001 C CNN
	1    7850 2900
	0    1    1    0   
$EndComp
Wire Wire Line
	7950 2900 8150 2900
Text GLabel 8450 3150 0    50   Input ~ 0
PI_GND
Wire Wire Line
	8450 2650 8450 2700
Wire Wire Line
	8450 3150 8450 3100
Wire Wire Line
	7700 2900 7750 2900
$Comp
L dk_Transistors-Bipolar-BJT-Single:MMBT2222A-7-F Q20
U 1 1 610E1CC0
P 8350 3550
F 0 "Q20" H 8538 3603 60  0000 L CNN
F 1 "MMBT2222A" H 8538 3497 60  0000 L CNN
F 2 "digikey-footprints:SOT-23-3" H 8550 3750 60  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 8550 3850 60  0001 L CNN
F 4 "MMBT2222A-FDICT-ND" H 8550 3950 60  0001 L CNN "Digi-Key_PN"
F 5 "MMBT2222A-7-F" H 8550 4050 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 8550 4150 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 8550 4250 60  0001 L CNN "Family"
F 8 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 8550 4350 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/diodes-incorporated/MMBT2222A-7-F/MMBT2222A-FDICT-ND/815723" H 8550 4450 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V 0.6A SMD SOT23-3" H 8550 4550 60  0001 L CNN "Description"
F 11 "Diodes Incorporated" H 8550 4650 60  0001 L CNN "Manufacturer"
F 12 "Active" H 8550 4750 60  0001 L CNN "Status"
	1    8350 3550
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R26
U 1 1 610E1CC6
P 7850 3550
F 0 "R26" V 7645 3550 50  0000 C CNN
F 1 "300R" V 7736 3550 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 7850 3550 50  0001 C CNN
F 3 "~" H 7850 3550 50  0001 C CNN
	1    7850 3550
	0    1    1    0   
$EndComp
Wire Wire Line
	7950 3550 8150 3550
Text GLabel 8450 3800 0    50   Input ~ 0
PI_GND
Wire Wire Line
	8450 3300 8450 3350
Wire Wire Line
	8450 3800 8450 3750
Wire Wire Line
	7700 3550 7750 3550
$Comp
L Device:R_Small_US R27
U 1 1 610E1CD1
P 7850 4200
F 0 "R27" V 7645 4200 50  0000 C CNN
F 1 "300R" V 7736 4200 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 7850 4200 50  0001 C CNN
F 3 "~" H 7850 4200 50  0001 C CNN
	1    7850 4200
	0    1    1    0   
$EndComp
Wire Wire Line
	7950 4200 8150 4200
Text GLabel 8450 4450 0    50   Input ~ 0
PI_GND
Wire Wire Line
	8450 3950 8450 4000
Wire Wire Line
	8450 4450 8450 4400
Wire Wire Line
	7700 4200 7750 4200
$Comp
L dk_Transistors-Bipolar-BJT-Single:MMBT2222A-7-F Q21
U 1 1 610E1CE5
P 8350 4200
F 0 "Q21" H 8538 4253 60  0000 L CNN
F 1 "MMBT2222A" H 8538 4147 60  0000 L CNN
F 2 "digikey-footprints:SOT-23-3" H 8550 4400 60  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 8550 4500 60  0001 L CNN
F 4 "MMBT2222A-FDICT-ND" H 8550 4600 60  0001 L CNN "Digi-Key_PN"
F 5 "MMBT2222A-7-F" H 8550 4700 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 8550 4800 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 8550 4900 60  0001 L CNN "Family"
F 8 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 8550 5000 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/diodes-incorporated/MMBT2222A-7-F/MMBT2222A-FDICT-ND/815723" H 8550 5100 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V 0.6A SMD SOT23-3" H 8550 5200 60  0001 L CNN "Description"
F 11 "Diodes Incorporated" H 8550 5300 60  0001 L CNN "Manufacturer"
F 12 "Active" H 8550 5400 60  0001 L CNN "Status"
	1    8350 4200
	1    0    0    -1  
$EndComp
Wire Wire Line
	9800 1150 9800 1200
Wire Wire Line
	9800 700  9800 750 
Wire Wire Line
	9800 1350 9800 1400
Wire Wire Line
	9800 1850 9800 1800
Wire Wire Line
	9800 2500 9800 2450
Wire Wire Line
	9800 2050 9800 2000
Wire Wire Line
	9800 2700 9800 2650
Wire Wire Line
	9800 3150 9800 3100
Wire Wire Line
	9800 3350 9800 3300
Wire Wire Line
	9800 3750 9800 3800
$Comp
L dk_Transistors-Bipolar-BJT-Single:MMBT2222A-7-F Q30
U 1 1 610E1CFE
P 9900 4200
F 0 "Q30" H 10088 4253 60  0000 L CNN
F 1 "MMBT2222A" H 10088 4147 60  0000 L CNN
F 2 "digikey-footprints:SOT-23-3" H 10100 4400 60  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 10100 4500 60  0001 L CNN
F 4 "MMBT2222A-FDICT-ND" H 10100 4600 60  0001 L CNN "Digi-Key_PN"
F 5 "MMBT2222A-7-F" H 10100 4700 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 10100 4800 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 10100 4900 60  0001 L CNN "Family"
F 8 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 10100 5000 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/diodes-incorporated/MMBT2222A-7-F/MMBT2222A-FDICT-ND/815723" H 10100 5100 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V 0.6A SMD SOT23-3" H 10100 5200 60  0001 L CNN "Description"
F 11 "Diodes Incorporated" H 10100 5300 60  0001 L CNN "Manufacturer"
F 12 "Active" H 10100 5400 60  0001 L CNN "Status"
	1    9900 4200
	-1   0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R36
U 1 1 610E1D04
P 10400 4200
F 0 "R36" V 10195 4200 50  0000 C CNN
F 1 "300R" V 10286 4200 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 10400 4200 50  0001 C CNN
F 3 "~" H 10400 4200 50  0001 C CNN
	1    10400 4200
	0    -1   1    0   
$EndComp
Wire Wire Line
	10300 4200 10100 4200
Text GLabel 9800 4450 2    50   Input ~ 0
PI_GND
Wire Wire Line
	9800 4000 9800 3950
Wire Wire Line
	9800 4400 9800 4450
$Comp
L dk_Transistors-Bipolar-BJT-Single:MMBT2222A-7-F Q17
U 1 1 610E1C72
P 8350 1600
F 0 "Q17" H 8538 1653 60  0000 L CNN
F 1 "MMBT2222A" H 8538 1547 60  0000 L CNN
F 2 "digikey-footprints:SOT-23-3" H 8550 1800 60  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 8550 1900 60  0001 L CNN
F 4 "MMBT2222A-FDICT-ND" H 8550 2000 60  0001 L CNN "Digi-Key_PN"
F 5 "MMBT2222A-7-F" H 8550 2100 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 8550 2200 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 8550 2300 60  0001 L CNN "Family"
F 8 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 8550 2400 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/diodes-incorporated/MMBT2222A-7-F/MMBT2222A-FDICT-ND/815723" H 8550 2500 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V 0.6A SMD SOT23-3" H 8550 2600 60  0001 L CNN "Description"
F 11 "Diodes Incorporated" H 8550 2700 60  0001 L CNN "Manufacturer"
F 12 "Active" H 8550 2800 60  0001 L CNN "Status"
	1    8350 1600
	1    0    0    -1  
$EndComp
Text GLabel 8450 1350 0    47   Input ~ 0
K8_SET
Text GLabel 8450 3300 0    47   Input ~ 0
K11_SET
Text GLabel 8450 3950 0    47   Input ~ 0
K12_SET
$Comp
L dk_Transistors-Bipolar-BJT-Single:MMBT2222A-7-F Q31
U 1 1 61381C1A
P 9900 4900
F 0 "Q31" H 10088 4953 60  0000 L CNN
F 1 "MMBT2222A" H 10088 4847 60  0000 L CNN
F 2 "digikey-footprints:SOT-23-3" H 10100 5100 60  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 10100 5200 60  0001 L CNN
F 4 "MMBT2222A-FDICT-ND" H 10100 5300 60  0001 L CNN "Digi-Key_PN"
F 5 "MMBT2222A-7-F" H 10100 5400 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 10100 5500 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 10100 5600 60  0001 L CNN "Family"
F 8 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 10100 5700 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/diodes-incorporated/MMBT2222A-7-F/MMBT2222A-FDICT-ND/815723" H 10100 5800 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V 0.6A SMD SOT23-3" H 10100 5900 60  0001 L CNN "Description"
F 11 "Diodes Incorporated" H 10100 6000 60  0001 L CNN "Manufacturer"
F 12 "Active" H 10100 6100 60  0001 L CNN "Status"
	1    9900 4900
	-1   0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R37
U 1 1 61381C20
P 10400 4900
F 0 "R37" V 10195 4900 50  0000 C CNN
F 1 "300R" V 10286 4900 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 10400 4900 50  0001 C CNN
F 3 "~" H 10400 4900 50  0001 C CNN
	1    10400 4900
	0    -1   1    0   
$EndComp
Wire Wire Line
	10300 4900 10100 4900
Text GLabel 9800 5150 2    50   Input ~ 0
PI_GND
$Comp
L dk_Transistors-Bipolar-BJT-Single:MMBT2222A-7-F Q32
U 1 1 61381C32
P 9900 5550
F 0 "Q32" H 10088 5603 60  0000 L CNN
F 1 "MMBT2222A" H 10088 5497 60  0000 L CNN
F 2 "digikey-footprints:SOT-23-3" H 10100 5750 60  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 10100 5850 60  0001 L CNN
F 4 "MMBT2222A-FDICT-ND" H 10100 5950 60  0001 L CNN "Digi-Key_PN"
F 5 "MMBT2222A-7-F" H 10100 6050 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 10100 6150 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 10100 6250 60  0001 L CNN "Family"
F 8 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 10100 6350 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/diodes-incorporated/MMBT2222A-7-F/MMBT2222A-FDICT-ND/815723" H 10100 6450 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V 0.6A SMD SOT23-3" H 10100 6550 60  0001 L CNN "Description"
F 11 "Diodes Incorporated" H 10100 6650 60  0001 L CNN "Manufacturer"
F 12 "Active" H 10100 6750 60  0001 L CNN "Status"
	1    9900 5550
	-1   0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R38
U 1 1 61381C38
P 10400 5550
F 0 "R38" V 10195 5550 50  0000 C CNN
F 1 "300R" V 10286 5550 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 10400 5550 50  0001 C CNN
F 3 "~" H 10400 5550 50  0001 C CNN
	1    10400 5550
	0    -1   1    0   
$EndComp
Wire Wire Line
	10300 5550 10100 5550
Text GLabel 9800 5800 2    50   Input ~ 0
PI_GND
$Comp
L dk_Transistors-Bipolar-BJT-Single:MMBT2222A-7-F Q22
U 1 1 61381C4A
P 8350 4900
F 0 "Q22" H 8538 4953 60  0000 L CNN
F 1 "MMBT2222A" H 8538 4847 60  0000 L CNN
F 2 "digikey-footprints:SOT-23-3" H 8550 5100 60  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 8550 5200 60  0001 L CNN
F 4 "MMBT2222A-FDICT-ND" H 8550 5300 60  0001 L CNN "Digi-Key_PN"
F 5 "MMBT2222A-7-F" H 8550 5400 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 8550 5500 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 8550 5600 60  0001 L CNN "Family"
F 8 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 8550 5700 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/diodes-incorporated/MMBT2222A-7-F/MMBT2222A-FDICT-ND/815723" H 8550 5800 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V 0.6A SMD SOT23-3" H 8550 5900 60  0001 L CNN "Description"
F 11 "Diodes Incorporated" H 8550 6000 60  0001 L CNN "Manufacturer"
F 12 "Active" H 8550 6100 60  0001 L CNN "Status"
	1    8350 4900
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R28
U 1 1 61381C50
P 7850 4900
F 0 "R28" V 7645 4900 50  0000 C CNN
F 1 "300R" V 7736 4900 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 7850 4900 50  0001 C CNN
F 3 "~" H 7850 4900 50  0001 C CNN
	1    7850 4900
	0    1    1    0   
$EndComp
Wire Wire Line
	7950 4900 8150 4900
Text GLabel 8450 5150 0    50   Input ~ 0
PI_GND
Wire Wire Line
	8450 5150 8450 5100
Wire Wire Line
	7700 4900 7750 4900
$Comp
L dk_Transistors-Bipolar-BJT-Single:MMBT2222A-7-F Q23
U 1 1 61381C63
P 8350 5550
F 0 "Q23" H 8538 5603 60  0000 L CNN
F 1 "MMBT2222A" H 8538 5497 60  0000 L CNN
F 2 "digikey-footprints:SOT-23-3" H 8550 5750 60  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 8550 5850 60  0001 L CNN
F 4 "MMBT2222A-FDICT-ND" H 8550 5950 60  0001 L CNN "Digi-Key_PN"
F 5 "MMBT2222A-7-F" H 8550 6050 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 8550 6150 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 8550 6250 60  0001 L CNN "Family"
F 8 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 8550 6350 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/diodes-incorporated/MMBT2222A-7-F/MMBT2222A-FDICT-ND/815723" H 8550 6450 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V 0.6A SMD SOT23-3" H 8550 6550 60  0001 L CNN "Description"
F 11 "Diodes Incorporated" H 8550 6650 60  0001 L CNN "Manufacturer"
F 12 "Active" H 8550 6750 60  0001 L CNN "Status"
	1    8350 5550
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R29
U 1 1 61381C69
P 7850 5550
F 0 "R29" V 7645 5550 50  0000 C CNN
F 1 "300R" V 7736 5550 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 7850 5550 50  0001 C CNN
F 3 "~" H 7850 5550 50  0001 C CNN
	1    7850 5550
	0    1    1    0   
$EndComp
Wire Wire Line
	7950 5550 8150 5550
Text GLabel 8450 5800 0    50   Input ~ 0
PI_GND
Wire Wire Line
	8450 5300 8450 5350
Wire Wire Line
	8450 5800 8450 5750
Wire Wire Line
	7700 5550 7750 5550
$Comp
L Device:R_Small_US R30
U 1 1 61381C74
P 7850 6200
F 0 "R30" V 7645 6200 50  0000 C CNN
F 1 "300R" V 7736 6200 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 7850 6200 50  0001 C CNN
F 3 "~" H 7850 6200 50  0001 C CNN
	1    7850 6200
	0    1    1    0   
$EndComp
Wire Wire Line
	7950 6200 8150 6200
Text GLabel 8450 6450 0    50   Input ~ 0
PI_GND
Wire Wire Line
	8450 5950 8450 6000
Wire Wire Line
	8450 6450 8450 6400
Wire Wire Line
	7700 6200 7750 6200
$Comp
L dk_Transistors-Bipolar-BJT-Single:MMBT2222A-7-F Q24
U 1 1 61381C88
P 8350 6200
F 0 "Q24" H 8538 6253 60  0000 L CNN
F 1 "MMBT2222A" H 8538 6147 60  0000 L CNN
F 2 "digikey-footprints:SOT-23-3" H 8550 6400 60  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 8550 6500 60  0001 L CNN
F 4 "MMBT2222A-FDICT-ND" H 8550 6600 60  0001 L CNN "Digi-Key_PN"
F 5 "MMBT2222A-7-F" H 8550 6700 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 8550 6800 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 8550 6900 60  0001 L CNN "Family"
F 8 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 8550 7000 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/diodes-incorporated/MMBT2222A-7-F/MMBT2222A-FDICT-ND/815723" H 8550 7100 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V 0.6A SMD SOT23-3" H 8550 7200 60  0001 L CNN "Description"
F 11 "Diodes Incorporated" H 8550 7300 60  0001 L CNN "Manufacturer"
F 12 "Active" H 8550 7400 60  0001 L CNN "Status"
	1    8350 6200
	1    0    0    -1  
$EndComp
Wire Wire Line
	9800 5150 9800 5100
Wire Wire Line
	9800 5350 9800 5300
Wire Wire Line
	9800 5750 9800 5800
$Comp
L dk_Transistors-Bipolar-BJT-Single:MMBT2222A-7-F Q33
U 1 1 61381C9A
P 9900 6200
F 0 "Q33" H 10088 6253 60  0000 L CNN
F 1 "MMBT2222A" H 10088 6147 60  0000 L CNN
F 2 "digikey-footprints:SOT-23-3" H 10100 6400 60  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 10100 6500 60  0001 L CNN
F 4 "MMBT2222A-FDICT-ND" H 10100 6600 60  0001 L CNN "Digi-Key_PN"
F 5 "MMBT2222A-7-F" H 10100 6700 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 10100 6800 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 10100 6900 60  0001 L CNN "Family"
F 8 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 10100 7000 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/diodes-incorporated/MMBT2222A-7-F/MMBT2222A-FDICT-ND/815723" H 10100 7100 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V 0.6A SMD SOT23-3" H 10100 7200 60  0001 L CNN "Description"
F 11 "Diodes Incorporated" H 10100 7300 60  0001 L CNN "Manufacturer"
F 12 "Active" H 10100 7400 60  0001 L CNN "Status"
	1    9900 6200
	-1   0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R39
U 1 1 61381CA0
P 10400 6200
F 0 "R39" V 10195 6200 50  0000 C CNN
F 1 "300R" V 10286 6200 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 10400 6200 50  0001 C CNN
F 3 "~" H 10400 6200 50  0001 C CNN
	1    10400 6200
	0    -1   1    0   
$EndComp
Wire Wire Line
	10300 6200 10100 6200
Text GLabel 9800 6450 2    50   Input ~ 0
PI_GND
Wire Wire Line
	9800 6000 9800 5950
Wire Wire Line
	9800 6400 9800 6450
Text GLabel 8450 4700 0    47   Input ~ 0
K13_SET
Text GLabel 8450 5300 0    47   Input ~ 0
K14_SET
Text GLabel 8450 5950 0    47   Input ~ 0
K15_SET
$Comp
L dk_Transistors-Bipolar-BJT-Single:MMBT2222A-7-F Q15
U 1 1 614D6B5F
P 6200 4000
F 0 "Q15" H 6388 4053 60  0000 L CNN
F 1 "MMBT2222A" H 6388 3947 60  0000 L CNN
F 2 "digikey-footprints:SOT-23-3" H 6400 4200 60  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 6400 4300 60  0001 L CNN
F 4 "MMBT2222A-FDICT-ND" H 6400 4400 60  0001 L CNN "Digi-Key_PN"
F 5 "MMBT2222A-7-F" H 6400 4500 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 6400 4600 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 6400 4700 60  0001 L CNN "Family"
F 8 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 6400 4800 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/diodes-incorporated/MMBT2222A-7-F/MMBT2222A-FDICT-ND/815723" H 6400 4900 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V 0.6A SMD SOT23-3" H 6400 5000 60  0001 L CNN "Description"
F 11 "Diodes Incorporated" H 6400 5100 60  0001 L CNN "Manufacturer"
F 12 "Active" H 6400 5200 60  0001 L CNN "Status"
	1    6200 4000
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R21
U 1 1 614D6B65
P 5850 4000
F 0 "R21" V 5645 4000 50  0000 C CNN
F 1 "100R" V 5736 4000 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 5850 4000 50  0001 C CNN
F 3 "~" H 5850 4000 50  0001 C CNN
	1    5850 4000
	0    1    1    0   
$EndComp
Wire Wire Line
	6300 3750 6300 3800
Wire Wire Line
	6300 4250 6300 4200
Wire Wire Line
	5700 4000 5750 4000
Wire Wire Line
	5950 4000 6000 4000
Text GLabel 6300 3750 0    50   Input ~ 0
+5V
Text GLabel 5700 4000 0    50   Input ~ 0
BANK_A_RESET_SIGNL
Text GLabel 6300 4250 2    50   Input ~ 0
BANK_A_RESET
$Comp
L dk_Transistors-Bipolar-BJT-Single:MMBT2222A-7-F Q14
U 1 1 6152F229
P 6150 6300
F 0 "Q14" H 6338 6353 60  0000 L CNN
F 1 "MMBT2222A" H 6338 6247 60  0000 L CNN
F 2 "digikey-footprints:SOT-23-3" H 6350 6500 60  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 6350 6600 60  0001 L CNN
F 4 "MMBT2222A-FDICT-ND" H 6350 6700 60  0001 L CNN "Digi-Key_PN"
F 5 "MMBT2222A-7-F" H 6350 6800 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 6350 6900 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 6350 7000 60  0001 L CNN "Family"
F 8 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 6350 7100 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/diodes-incorporated/MMBT2222A-7-F/MMBT2222A-FDICT-ND/815723" H 6350 7200 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V 0.6A SMD SOT23-3" H 6350 7300 60  0001 L CNN "Description"
F 11 "Diodes Incorporated" H 6350 7400 60  0001 L CNN "Manufacturer"
F 12 "Active" H 6350 7500 60  0001 L CNN "Status"
	1    6150 6300
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R20
U 1 1 6152F22F
P 5800 6300
F 0 "R20" V 5595 6300 50  0000 C CNN
F 1 "100R" V 5686 6300 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 5800 6300 50  0001 C CNN
F 3 "~" H 5800 6300 50  0001 C CNN
	1    5800 6300
	0    1    1    0   
$EndComp
Wire Wire Line
	6250 6050 6250 6100
Wire Wire Line
	6250 6550 6250 6500
Wire Wire Line
	5650 6300 5700 6300
Wire Wire Line
	5900 6300 5950 6300
Text GLabel 6250 6050 0    50   Input ~ 0
+5V
Text GLabel 5650 6300 0    50   Input ~ 0
BANK_B_RESET_SIGNL
Text GLabel 6250 6550 2    50   Input ~ 0
BANK_B_RESET
$Comp
L dk_Transistors-Bipolar-BJT-Single:MMBT2222A-7-F Q13
U 1 1 615363D8
P 5900 1800
F 0 "Q13" H 6088 1853 60  0000 L CNN
F 1 "MMBT2222A" H 6088 1747 60  0000 L CNN
F 2 "digikey-footprints:SOT-23-3" H 6100 2000 60  0001 L CNN
F 3 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 6100 2100 60  0001 L CNN
F 4 "MMBT2222A-FDICT-ND" H 6100 2200 60  0001 L CNN "Digi-Key_PN"
F 5 "MMBT2222A-7-F" H 6100 2300 60  0001 L CNN "MPN"
F 6 "Discrete Semiconductor Products" H 6100 2400 60  0001 L CNN "Category"
F 7 "Transistors - Bipolar (BJT) - Single" H 6100 2500 60  0001 L CNN "Family"
F 8 "https://www.diodes.com/assets/Datasheets/ds30041.pdf" H 6100 2600 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/diodes-incorporated/MMBT2222A-7-F/MMBT2222A-FDICT-ND/815723" H 6100 2700 60  0001 L CNN "DK_Detail_Page"
F 10 "TRANS NPN 40V 0.6A SMD SOT23-3" H 6100 2800 60  0001 L CNN "Description"
F 11 "Diodes Incorporated" H 6100 2900 60  0001 L CNN "Manufacturer"
F 12 "Active" H 6100 3000 60  0001 L CNN "Status"
	1    5900 1800
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R19
U 1 1 615363DE
P 5550 1800
F 0 "R19" V 5345 1800 50  0000 C CNN
F 1 "100R" V 5436 1800 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 5550 1800 50  0001 C CNN
F 3 "~" H 5550 1800 50  0001 C CNN
	1    5550 1800
	0    1    1    0   
$EndComp
Wire Wire Line
	6000 1550 6000 1600
Wire Wire Line
	6000 2050 6000 2000
Wire Wire Line
	5400 1800 5450 1800
Wire Wire Line
	5650 1800 5700 1800
Text GLabel 6000 1550 0    50   Input ~ 0
+5V
Text GLabel 5400 1800 0    50   Input ~ 0
RES_ARRAY_RESET_SIGNL
Text GLabel 6000 2050 2    50   Input ~ 0
RES_ARRAY_RESET
Text GLabel 5850 6800 0    50   Input ~ 0
+5V
Text GLabel 5900 7200 0    50   Input ~ 0
BANK_B_RESET
$Comp
L Device:C_Small C32
U 1 1 6163BA71
P 5900 7000
F 0 "C32" H 5992 7046 50  0000 L CNN
F 1 "10uF" H 5992 6955 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5900 7000 50  0001 C CNN
F 3 "~" H 5900 7000 50  0001 C CNN
	1    5900 7000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5850 6800 5900 6800
Wire Wire Line
	5900 6800 5900 6900
Wire Wire Line
	5900 7200 5900 7100
Text GLabel 6200 4450 0    50   Input ~ 0
+5V
Text GLabel 6250 4850 0    50   Input ~ 0
BANK_A_RESET
$Comp
L Device:C_Small C33
U 1 1 61662CE5
P 6250 4650
F 0 "C33" H 6342 4696 50  0000 L CNN
F 1 "10uF" H 6342 4605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6250 4650 50  0001 C CNN
F 3 "~" H 6250 4650 50  0001 C CNN
	1    6250 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 4450 6250 4450
Wire Wire Line
	6250 4450 6250 4550
Wire Wire Line
	6250 4850 6250 4750
Text GLabel 5650 2250 0    50   Input ~ 0
+5V
$Comp
L Device:C_Small C31
U 1 1 616AB4E0
P 5700 2450
F 0 "C31" H 5792 2496 50  0000 L CNN
F 1 "10uF" H 5792 2405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5700 2450 50  0001 C CNN
F 3 "~" H 5700 2450 50  0001 C CNN
	1    5700 2450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5650 2250 5700 2250
Wire Wire Line
	5700 2250 5700 2350
Wire Wire Line
	5700 2650 5700 2550
Text GLabel 5700 2650 0    50   Input ~ 0
RES_ARRAY_RESET
$Comp
L Device:C_Small C46
U 1 1 61AD78BC
P 3750 1300
F 0 "C46" H 3842 1346 50  0000 L CNN
F 1 "10uF" H 3842 1255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3750 1300 50  0001 C CNN
F 3 "~" H 3750 1300 50  0001 C CNN
	1    3750 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 1300 3550 1300
Wire Wire Line
	3750 1400 4000 1400
Connection ~ 3750 1400
Wire Wire Line
	3750 1200 4000 1200
Connection ~ 3750 1200
Text GLabel 4500 2300 2    50   Input ~ 0
PI_GND
$Comp
L power:GND #PWR0103
U 1 1 61F6B3B0
P 4450 2500
F 0 "#PWR0103" H 4450 2250 50  0001 C CNN
F 1 "GND" H 4455 2327 50  0000 C CNN
F 2 "" H 4450 2500 50  0001 C CNN
F 3 "" H 4450 2500 50  0001 C CNN
	1    4450 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 2300 4450 2300
Wire Wire Line
	4450 2300 4450 2500
Text GLabel 3150 1600 2    47   Input ~ 0
CAL_RESET_SIGNL
Text GLabel 3150 1900 2    47   Input ~ 0
K16_SET_SIGNL
Text GLabel 3150 1800 2    47   Input ~ 0
K17_SET_SIGNL
Wire Wire Line
	3000 1600 3150 1600
Wire Wire Line
	3000 1800 3150 1800
Wire Wire Line
	3000 1900 3150 1900
Text GLabel 3300 1400 2    50   Input ~ 0
TX
Text GLabel 3300 1500 2    50   Input ~ 0
RX
Text GLabel 1050 1000 0    50   Input ~ 0
TX
Text GLabel 1050 700  0    50   Input ~ 0
RX
$Comp
L Device:R_Small_US R53
U 1 1 5F03CEFB
P 1300 700
F 0 "R53" V 1100 700 50  0000 C CNN
F 1 "50R" V 1200 700 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 1300 700 50  0001 C CNN
F 3 "~" H 1300 700 50  0001 C CNN
	1    1300 700 
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small_US R54
U 1 1 5F03E662
P 1300 1000
F 0 "R54" V 1100 1000 50  0000 C CNN
F 1 "50R" V 1200 1000 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 1300 1000 50  0001 C CNN
F 3 "~" H 1300 1000 50  0001 C CNN
	1    1300 1000
	0    1    1    0   
$EndComp
Wire Wire Line
	1050 1000 1200 1000
Wire Wire Line
	1050 700  1200 700 
$Comp
L Connector:TestPoint TP15
U 1 1 5F0603AA
P 1500 700
F 0 "TP15" H 1558 818 50  0000 L CNN
F 1 "RX" H 1558 727 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D2.5mm" H 1700 700 50  0001 C CNN
F 3 "~" H 1700 700 50  0001 C CNN
	1    1500 700 
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 700  1400 700 
$Comp
L Connector:TestPoint TP16
U 1 1 5F069ED5
P 1500 1000
F 0 "TP16" H 1558 1118 50  0000 L CNN
F 1 "TX" H 1558 1027 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D2.5mm" H 1700 1000 50  0001 C CNN
F 3 "~" H 1700 1000 50  0001 C CNN
	1    1500 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1500 1000 1400 1000
NoConn ~ 2200 1300
NoConn ~ 2200 1100
Text GLabel 2200 1200 0    50   Input ~ 0
LTC2057_SHDN
NoConn ~ 2200 1900
Text Notes 2998 2204 0    50   ~ 0
24
Wire Wire Line
	3000 2500 3450 2500
Text Notes 3000 2600 0    50   ~ 0
32\n
Text Notes 3000 2500 0    50   ~ 0
30
Wire Wire Line
	3000 2700 3450 2700
Text Notes 3000 2700 0    50   ~ 0
34\n
Text Notes 3000 2800 0    50   ~ 0
36
Text Notes 3000 2900 0    50   ~ 0
38
Wire Wire Line
	3000 2900 3150 2900
Text Notes 3000 3000 0    50   ~ 0
40
Text Notes 3000 2300 0    50   ~ 0
26
Wire Wire Line
	3000 2000 3450 2000
Text Notes 3000 2100 0    50   ~ 0
22
Text Notes 3000 2000 0    50   ~ 0
20
Text Notes 3000 1900 0    50   ~ 0
18
Wire Wire Line
	3000 1700 3450 1700
Text Notes 3000 1800 0    50   ~ 0
16
Text Notes 3000 1700 0    50   ~ 0
14
Wire Wire Line
	3000 1200 3750 1200
Wire Wire Line
	3550 1400 3750 1400
Wire Wire Line
	3550 1300 3550 1400
Wire Wire Line
	3000 1400 3300 1400
Wire Wire Line
	3000 1500 3300 1500
Text Notes 3000 1600 0    50   ~ 0
12
Text Notes 3000 1500 0    50   ~ 0
10
Text Notes 3050 1400 0    50   ~ 0
8
Text Notes 3050 1300 0    50   ~ 0
6\n
Wire Wire Line
	2200 1500 1850 1500
Text Notes 2100 1400 0    50   ~ 0
7
Text Notes 2100 1500 0    50   ~ 0
9
Text Notes 2050 1600 0    50   ~ 0
11
Text Notes 2050 1700 0    50   ~ 0
13
Text Notes 2050 1800 0    50   ~ 0
15\n
Text Notes 2050 2000 0    50   ~ 0
19
Wire Wire Line
	1850 2300 2200 2300
Text Notes 2050 2100 0    50   ~ 0
21
Text Notes 2050 2200 0    50   ~ 0
23
Text Notes 2050 2300 0    50   ~ 0
25
Text Notes 2050 2500 0    50   ~ 0
29
Text Notes 2050 2600 0    50   ~ 0
31
Text Notes 2050 2700 0    50   ~ 0
33
Text Notes 2050 2800 0    50   ~ 0
35
Text Notes 2050 2900 0    50   ~ 0
37
Wire Wire Line
	3000 1100 3350 1100
Text Notes 3050 1200 0    50   ~ 0
4
$EndSCHEMATC
