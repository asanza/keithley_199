#!/usr/bin/env python

import serial
import time
import os
import datetime
import sys

from serial import SerialException

test = serial.Serial(port='/dev/ttyUSB0', baudrate=115200, timeout=0.5)
ref  = serial.Serial(port='/dev/ttyUSB1', baudrate=9600, timeout=0.5)
ref.write('T0B0P0R2Q0G1X\n')

while True:
	f = open('measurements.txt', 'ab+')
	try:
		ref.write('++read\n')
		refvar = ref.readline()
	except SerialException:
		time.sleep(1)
		print sys.exc_info()[0]
		continue
	if not any(c.isdigit() for c in refvar):
		time.sleep(1)
		continue
	try:
		test.write('meas:volt:dc?\n')
		testvar = test.readline()
	except SerialException:
		time.sleep(1)
		print sys.exc_info()[0]
		continue
	if not any(c.isdigit() for c in testvar):
		print "ERROR: " + testvar
		time.sleep(1)
		continue
	try:
		tval = float(testvar.rstrip())
		rval = float(refvar.rstrip())
	except ValueError:
		print sys.exc_info()[0]
		time.sleep(1)
		continue
	error = tval - rval;
	outstr = str(datetime.datetime.today()) + '; ' + testvar.rstrip() + "; " + refvar.rstrip() + "; " + str(error)
	print outstr
	f.write(outstr + '\n');
	f.flush()
	os.fsync(f.fileno())
	f.close();
	time.sleep(1)	