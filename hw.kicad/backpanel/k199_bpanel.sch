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
LIBS:k199_bpanel-cache
EELAYER 25 0
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
L RJ45_LEDS J1
U 1 1 55FE9F9B
P 3585 2715
F 0 "J1" H 3585 2215 50  0000 C CNN
F 1 "RJ45_LEDS" H 3585 3115 50  0000 C CNN
F 2 "Connect:RJ45_TRANSFO" H 3585 2665 60  0001 C CNN
F 3 "" H 3585 2665 60  0000 C CNN
	1    3585 2715
	1    0    0    -1  
$EndComp
$Comp
L USB_A P1
U 1 1 55FEA0A0
P 4630 2890
F 0 "P1" H 4830 2690 50  0000 C CNN
F 1 "USB_A" H 4580 3090 50  0000 C CNN
F 2 "Connect:USB_B" V 4580 2790 60  0001 C CNN
F 3 "" V 4580 2790 60  0000 C CNN
	1    4630 2890
	1    0    0    -1  
$EndComp
$Comp
L BNC P2
U 1 1 55FEA3ED
P 5550 2750
F 0 "P2" H 5560 2870 50  0000 C CNN
F 1 "BNC" V 5660 2690 50  0000 C CNN
F 2 "w_conn_rf:sma_90_r300.124.403" H 5550 2750 60  0001 C CNN
F 3 "" H 5550 2750 60  0000 C CNN
	1    5550 2750
	1    0    0    -1  
$EndComp
$Comp
L BNC P3
U 1 1 5601B66C
P 6145 2740
F 0 "P3" H 6155 2860 50  0000 C CNN
F 1 "BNC" V 6255 2680 50  0000 C CNN
F 2 "w_conn_rf:sma_90_r300.124.403" H 6145 2740 60  0001 C CNN
F 3 "" H 6145 2740 60  0000 C CNN
	1    6145 2740
	1    0    0    -1  
$EndComp
$EndSCHEMATC
