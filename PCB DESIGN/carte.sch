EESchema Schematic File Version 4
LIBS:carte-cache
EELAYER 29 0
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
L Connector:Screw_Terminal_01x02 BTN3
U 1 1 5D0A019F
P 2600 2650
F 0 "BTN3" H 2680 2642 50  0000 L CNN
F 1 "reset" H 2680 2551 50  0000 L CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 2600 2650 50  0001 C CNN
F 3 "~" H 2600 2650 50  0001 C CNN
	1    2600 2650
	-1   0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 POWER1
U 1 1 5D0BB052
P 900 1000
F 0 "POWER1" H 818 1217 50  0000 C CNN
F 1 "5V - GND" H 818 1126 50  0000 C CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 900 1000 50  0001 C CNN
F 3 "~" H 900 1000 50  0001 C CNN
	1    900  1000
	-1   0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0101
U 1 1 5D0C75F0
P 1300 1000
F 0 "#PWR0101" H 1300 850 50  0001 C CNN
F 1 "+5V" H 1315 1173 50  0000 C CNN
F 2 "" H 1300 1000 50  0001 C CNN
F 3 "" H 1300 1000 50  0001 C CNN
	1    1300 1000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 5D0C7E96
P 1300 1100
F 0 "#PWR0102" H 1300 850 50  0001 C CNN
F 1 "GND" H 1305 927 50  0000 C CNN
F 2 "" H 1300 1100 50  0001 C CNN
F 3 "" H 1300 1100 50  0001 C CNN
	1    1300 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	1100 1000 1300 1000
Wire Wire Line
	1100 1100 1300 1100
$Comp
L power:GND #PWR0105
U 1 1 5D0CAB42
P 2800 2750
F 0 "#PWR0105" H 2800 2500 50  0001 C CNN
F 1 "GND" H 2805 2577 50  0000 C CNN
F 2 "" H 2800 2750 50  0001 C CNN
F 3 "" H 2800 2750 50  0001 C CNN
	1    2800 2750
	1    0    0    -1  
$EndComp
Text Notes 4050 2500 0    50   ~ 0
CLK
Text Notes 4050 2600 0    50   ~ 0
D0
Text Notes 4050 2700 0    50   ~ 0
D1
Text Notes 4050 2800 0    50   ~ 0
15
Text Notes 4050 2900 0    50   ~ 0
2
Text Notes 4050 3000 0    50   ~ 0
0
Text Notes 4050 3100 0    50   ~ 0
4
Text Notes 4050 3200 0    50   ~ 0
16
Text Notes 4050 3300 0    50   ~ 0
17
Text Notes 4050 3400 0    50   ~ 0
5
Text Notes 4050 3500 0    50   ~ 0
18
Text Notes 4050 3600 0    50   ~ 0
19
Text Notes 4050 3700 0    50   ~ 0
GND
Text Notes 4050 3800 0    50   ~ 0
21
Text Notes 4050 3900 0    50   ~ 0
RX
Text Notes 4050 4000 0    50   ~ 0
TX
Text Notes 4050 4100 0    50   ~ 0
22
Text Notes 4050 4200 0    50   ~ 0
23
Text Notes 4050 4300 0    50   ~ 0
GND
Text Notes 4600 2500 0    50   ~ 0
5V
Text Notes 4600 2600 0    50   ~ 0
CMD
Text Notes 4600 2700 0    50   ~ 0
D3
Text Notes 4600 2800 0    50   ~ 0
D2
Text Notes 4600 2900 0    50   ~ 0
13
Text Notes 4600 3000 0    50   ~ 0
GND
Text Notes 4600 3100 0    50   ~ 0
12
Text Notes 4600 3200 0    50   ~ 0
14
Text Notes 4600 3300 0    50   ~ 0
27
Text Notes 4600 3400 0    50   ~ 0
26
Text Notes 4600 3500 0    50   ~ 0
25
Text Notes 4600 3600 0    50   ~ 0
33
Text Notes 4600 3700 0    50   ~ 0
32
Text Notes 4600 3800 0    50   ~ 0
35
Text Notes 4600 3900 0    50   ~ 0
34
Text Notes 4600 4000 0    50   ~ 0
VN
Text Notes 4600 4100 0    50   ~ 0
VP
Text Notes 4600 4200 0    50   ~ 0
EN
Text Notes 4600 4300 0    50   ~ 0
3V3
$Comp
L Connector_Generic:Conn_01x19 ESP32-L1
U 1 1 5D0B299A
P 3950 3400
F 0 "ESP32-L1" H 3819 4488 50  0000 L CNN
F 1 "Left" H 3819 4409 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x19_P2.54mm_Vertical" H 3950 3400 50  0001 C CNN
F 3 "~" H 3950 3400 50  0001 C CNN
	1    3950 3400
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x03 WS1
U 1 1 5D0AE523
P 2600 1450
F 0 "WS1" H 2518 1767 50  0000 C CNN
F 1 "Led Strip" H 2518 1676 50  0000 C CNN
F 2 "TerminalBlock:TerminalBlock_bornier-3_P5.08mm" H 2600 1450 50  0001 C CNN
F 3 "~" H 2600 1450 50  0001 C CNN
	1    2600 1450
	-1   0    0    -1  
$EndComp
Text GLabel 3750 3100 0    50   Input ~ 0
Btn1
Text GLabel 2800 2250 2    50   Input ~ 0
Btn2
Text GLabel 2800 2650 2    50   Input ~ 0
Btn3
$Comp
L Connector:Screw_Terminal_01x02 BTN1
U 1 1 5D0AA559
P 2600 1850
F 0 "BTN1" H 2680 1842 50  0000 L CNN
F 1 "Yes" H 2680 1751 50  0000 L CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 2600 1850 50  0001 C CNN
F 3 "~" H 2600 1850 50  0001 C CNN
	1    2600 1850
	-1   0    0    -1  
$EndComp
Text GLabel 2800 1850 2    50   Input ~ 0
Btn1
Text GLabel 3750 3200 0    50   Input ~ 0
Btn2
Text GLabel 3750 3300 0    50   Input ~ 0
Btn3
Text GLabel 2800 1450 2    50   Input ~ 0
WS
Text GLabel 3750 3000 0    50   Input ~ 0
WS
$Comp
L power:+5V #PWR0106
U 1 1 5D0C3DDE
P 2800 1350
F 0 "#PWR0106" H 2800 1200 50  0001 C CNN
F 1 "+5V" V 2815 1478 50  0000 L CNN
F 2 "" H 2800 1350 50  0001 C CNN
F 3 "" H 2800 1350 50  0001 C CNN
	1    2800 1350
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 5D0C508C
P 2800 1550
F 0 "#PWR0107" H 2800 1300 50  0001 C CNN
F 1 "GND" V 2805 1422 50  0000 R CNN
F 2 "" H 2800 1550 50  0001 C CNN
F 3 "" H 2800 1550 50  0001 C CNN
	1    2800 1550
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 5D0C7C73
P 2800 1950
F 0 "#PWR0108" H 2800 1700 50  0001 C CNN
F 1 "GND" H 2805 1777 50  0000 C CNN
F 2 "" H 2800 1950 50  0001 C CNN
F 3 "" H 2800 1950 50  0001 C CNN
	1    2800 1950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0109
U 1 1 5D0C832A
P 2800 2350
F 0 "#PWR0109" H 2800 2100 50  0001 C CNN
F 1 "GND" H 2805 2177 50  0000 C CNN
F 2 "" H 2800 2350 50  0001 C CNN
F 3 "" H 2800 2350 50  0001 C CNN
	1    2800 2350
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0110
U 1 1 5D0CEADA
P 5050 2500
F 0 "#PWR0110" H 5050 2350 50  0001 C CNN
F 1 "+5V" V 5065 2628 50  0000 L CNN
F 2 "" H 5050 2500 50  0001 C CNN
F 3 "" H 5050 2500 50  0001 C CNN
	1    5050 2500
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0111
U 1 1 5D0D128E
P 3750 4300
F 0 "#PWR0111" H 3750 4050 50  0001 C CNN
F 1 "GND" H 3755 4127 50  0000 C CNN
F 2 "" H 3750 4300 50  0001 C CNN
F 3 "" H 3750 4300 50  0001 C CNN
	1    3750 4300
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x19 ESP32-R1
U 1 1 5D0B4D2B
P 4850 3400
F 0 "ESP32-R1" H 4768 4488 50  0000 C CNN
F 1 "Right" H 4768 4409 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x19_P2.54mm_Vertical" H 4850 3400 50  0001 C CNN
F 3 "~" H 4850 3400 50  0001 C CNN
	1    4850 3400
	-1   0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x02 BTN2
U 1 1 5D0A97D6
P 2600 2250
F 0 "BTN2" H 2680 2242 50  0000 L CNN
F 1 "No" H 2680 2151 50  0000 L CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 2600 2250 50  0001 C CNN
F 3 "~" H 2600 2250 50  0001 C CNN
	1    2600 2250
	-1   0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0103
U 1 1 5D0DD303
P 2800 4000
F 0 "#PWR0103" H 2800 3850 50  0001 C CNN
F 1 "+5V" V 2815 4128 50  0000 L CNN
F 2 "" H 2800 4000 50  0001 C CNN
F 3 "" H 2800 4000 50  0001 C CNN
	1    2800 4000
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0104
U 1 1 5D0DC67B
P 2800 3800
F 0 "#PWR0104" H 2800 3550 50  0001 C CNN
F 1 "GND" V 2805 3672 50  0000 R CNN
F 2 "" H 2800 3800 50  0001 C CNN
F 3 "" H 2800 3800 50  0001 C CNN
	1    2800 3800
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x08 MicroSD1
U 1 1 5D0D15F9
P 2600 3700
F 0 "MicroSD1" H 2518 3075 50  0000 C CNN
F 1 "Conn_01x08" H 2518 3166 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x08_P2.54mm_Vertical" H 2600 3700 50  0001 C CNN
F 3 "~" H 2600 3700 50  0001 C CNN
	1    2600 3700
	-1   0    0    1   
$EndComp
Text Notes 2400 4000 0    50   ~ 0
5V
Text Notes 2400 3900 0    50   ~ 0
3V3
Text Notes 2400 3800 0    50   ~ 0
GND
Text Notes 2400 3700 0    50   ~ 0
CLK
Text Notes 2400 3600 0    50   ~ 0
DO
Text Notes 2400 3500 0    50   ~ 0
DI
Text Notes 2400 3400 0    50   ~ 0
CS
Text Notes 2400 3300 0    50   ~ 0
C0
Wire Wire Line
	3600 3700 3600 3800
Wire Wire Line
	3600 3800 3750 3800
Wire Wire Line
	2800 3400 3750 3400
Wire Wire Line
	2800 3500 3750 3500
Wire Wire Line
	2800 3600 3750 3600
Wire Wire Line
	2800 3700 3600 3700
$Comp
L Connector:Screw_Terminal_01x04 Display2
U 1 1 5D0BA843
P 6100 3500
F 0 "Display2" H 6180 3610 50  0000 L CNN
F 1 "Screw_Terminal_01x04" H 6180 3519 50  0000 L CNN
F 2 "TerminalBlock:TerminalBlock_bornier-4_P5.08mm" H 6100 3500 50  0001 C CNN
F 3 "~" H 6100 3500 50  0001 C CNN
	1    6100 3500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0112
U 1 1 5D0BB9A4
P 5900 2950
F 0 "#PWR0112" H 5900 2700 50  0001 C CNN
F 1 "GND" V 5905 2822 50  0000 R CNN
F 2 "" H 5900 2950 50  0001 C CNN
F 3 "" H 5900 2950 50  0001 C CNN
	1    5900 2950
	0    1    1    0   
$EndComp
$Comp
L power:+5V #PWR0113
U 1 1 5D0BC3C2
P 5900 2850
F 0 "#PWR0113" H 5900 2700 50  0001 C CNN
F 1 "+5V" V 5915 2978 50  0000 L CNN
F 2 "" H 5900 2850 50  0001 C CNN
F 3 "" H 5900 2850 50  0001 C CNN
	1    5900 2850
	0    -1   -1   0   
$EndComp
$Comp
L power:+5V #PWR0114
U 1 1 5D0BD29F
P 5900 3400
F 0 "#PWR0114" H 5900 3250 50  0001 C CNN
F 1 "+5V" V 5915 3528 50  0000 L CNN
F 2 "" H 5900 3400 50  0001 C CNN
F 3 "" H 5900 3400 50  0001 C CNN
	1    5900 3400
	0    -1   -1   0   
$EndComp
$Comp
L power:GND #PWR0115
U 1 1 5D0BDE1B
P 5900 3500
F 0 "#PWR0115" H 5900 3250 50  0001 C CNN
F 1 "GND" V 5905 3372 50  0000 R CNN
F 2 "" H 5900 3500 50  0001 C CNN
F 3 "" H 5900 3500 50  0001 C CNN
	1    5900 3500
	0    1    1    0   
$EndComp
$Comp
L Connector:Screw_Terminal_01x04 Display1
U 1 1 5D0B93C7
P 6100 2950
F 0 "Display1" H 6180 3060 50  0000 L CNN
F 1 "Screw_Terminal_01x04" H 6180 2969 50  0000 L CNN
F 2 "TerminalBlock:TerminalBlock_bornier-4_P5.08mm" H 6100 2950 50  0001 C CNN
F 3 "~" H 6100 2950 50  0001 C CNN
	1    6100 2950
	1    0    0    -1  
$EndComp
Text Notes 6200 3650 0    50   ~ 0
DIO
Text Notes 6200 3750 0    50   ~ 0
CLK
Text Notes 6200 3100 0    50   ~ 0
DIO
Text Notes 6200 3200 0    50   ~ 0
CLK
Wire Wire Line
	5900 3700 5050 3700
Wire Wire Line
	5900 3600 5050 3600
Wire Wire Line
	5900 3150 5500 3150
Wire Wire Line
	5500 3150 5500 3400
Wire Wire Line
	5500 3400 5050 3400
Wire Wire Line
	5900 3050 5400 3050
Wire Wire Line
	5400 3050 5400 3300
Wire Wire Line
	5400 3300 5050 3300
$EndSCHEMATC
