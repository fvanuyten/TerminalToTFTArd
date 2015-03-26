##
##This program is not perfect but it works for me, just 
##want to share it and if you like it or have some problems
##e-mail me ad fvanuyten@gmail.com

##I tested it with my Raspberry py, arduino and a tft 1.77" 
##This program connects to you arduino with pyserial
##and send most of the basics inputs and outputs of you Terminal
##Don't send command that make large inputs like ls -l
## U can use it to run a python script  for time
## This code can be extended to scroll up and down


import serial
import time
from subprocess import call
import subprocess


ser = serial.Serial("/dev/ttyUSB0",9600)
time.sleep(5)
tell = -1
delay = 0.3  ##change delay to make it faster if your chip is faster
             ##For UNO max time 0.05 If you make it faster send me the code PLS.

def terminal():
        while True:
                ser.write("Type exit() or BashCmd: ")
                bashcmd = raw_input("Type exit()|| clrall() or a bashCmd: ")
                ser.write(bashcmd)
                ser.write('\n')
                if bashcmd == "exit()":
                        break
                if bashcmd == "clrall()":
                        ser.write('\clr')
                
                cmd = bashcmd.split()
                call(cmd)
                output = subprocess.Popen( cmd, stdout=subprocess.PIPE ).communicate()[0]
                print "from output: "+ output


                if len(output) > 100:
                        ser.write("Output is big press enter togo next: ")
                        for i in range(len(output)):
                                print output[i]
                                ser.write(output[i])
                                time.sleep(delay)
                                global tell
                                tell += 1
                                if tell == 100:
                                        ser.write("/Press enter or clrall()/")
                                        raw_input("/Press enter or clrall()/")
                                        
                                
                                
                elif len(output)< 100:
                        ser.write("output: ")
                        ser.write(output)
                time.sleep(1)
                ser.write('\n')

                         
terminal()
