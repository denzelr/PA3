#!/usr/bin/python

import os
import subprocess

sched = ""
forks = ""
command = ""

for i in range(0, 3):
	if (i == 0):
		sched = "SCHED_OTHER"
	elif(i == 1):
		sched = "SCHED_RR"
	else:
		sched = "SCHED_FIFO"
	for j in range(0, 3):
		if(j == 0):
			forks = "5"
		elif(j == 1):
			forks = "50"
		else:
			forks = "500"
		for k in range(0, 3):

			if(k == 0):
				subprocess.call("rm pi" + sched + forks + ".txt", shell = True)
				subprocess.call("rm rw" + sched + forks + ".txt", shell = True)
				subprocess.call("rm rw_pi" + sched + forks + ".txt", shell = True)
				command = "{ time ./pi-sched-test " + "1000 " + sched + " " + forks + " " + "; } 2>> pi" + sched + forks + ".txt"
			elif(k == 1):
				command = "{ time ./rw_test " + "1024 " + "1024 " + "/dev/urandom " + "/dev/null " + sched + " " + forks + " " + "; } 2>> rw" + sched + forks + ".txt"
			else:
				command = "{ time ./rwpi_test " + "1024 " + "1024 " + "/dev/urandom " + "/dev/null " + sched + " " + forks + " " + "1000 " +  "; } 2>> rw_pi" + sched + forks + ".txt"
			
			for l in range(0, 3):
				subprocess.call(command, shell = True)
