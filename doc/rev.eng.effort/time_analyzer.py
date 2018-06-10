#!/usr/bin/env python
import csv
import sys
print sys.argv
with open(sys.argv[1]) as csvfile:
	reader = csv.reader(csvfile, delimiter = ',')
	actual_packet = 0
	last_time = 0.0
	deltat = 0.0
	lastdelta = 0.0
	errsum = 0.0
	nsampl = 0
	row_counter = 0;
	for row in reader:
		row_counter += 1
		if actual_packet!=row[1]:
			actual_packet = row[1]
			try:
				deltat = float(row[0]) - last_time
				last_time = float(row[0])
			except:
				pass
			if deltat > .010:
				err = deltat - lastdelta;
				#print "{0:.3g}".format(err)
				lastdelta = deltat
				if err < 0.001:
					errsum += err
					nsampl += 1
				else:
					if row_counter > 10:
						print 'Ups! out of tolerance' + ' ' + str(row_counter) + ' ' + str(err)
					
		else:
			print row[2]

	print "average error: " + "{0:.3g}".format(errsum/nsampl)
