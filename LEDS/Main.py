'''
Created on 06.04.2015

@author: Christoph
'''
import sys
import glob
import serial


import serial
from Tkinter import *
from threading import Timer, Thread, Event
from math import pow
from decimal import Decimal
import time
from time import sleep, clock






"""
Findet die Ports
"""
def serial_ports():
    """Lists serial ports

    :raises EnvironmentError:
        On unsupported or unknown platforms
    :returns:
        A list of available serial ports
    """
    if sys.platform.startswith('win'):
        ports = ['COM' + str(i + 1) for i in range(256)]

    elif sys.platform.startswith('linux') or sys.platform.startswith('cygwin'):
        # this is to exclude your current terminal "/dev/tty"
        ports = glob.glob('/dev/tty[A-Za-z]*')

    elif sys.platform.startswith('darwin'):
        ports = glob.glob('/dev/tty.*')

    else:
        raise EnvironmentError('Unsupported platform')

    result = []
    for port in ports:
        try:
            s = serial.Serial(port)
            s.close()
            result.append(port)
        except (OSError, serial.SerialException):
            pass
    return result

'''
Schliessen des Fensters
'''
def closeHandler():
    readerStarted.clear()
    running.clear()
    if Port.isOpen():
        Port.close()
    root.destroy()


"""
Sendet Event
"""
def sendEvent():
    status=[]
    sendbyte.append(0)
    sendbyte.append(0)
    k = len(sendbyte)
    for i in range(0,8):
        sendbyte[k-1] = sendbyte[k-1] + cbEventVars[i].get() * int(pow(2,i))
    
    status.append("Identifier: ")
    status.append(sendbyte[k-2])
    status.append(" Data: ")
    status.append(sendbyte[k-1])
    status.append("Position: ")
    status.append(k-2)
    print status
        
def sendPattern():
    status=[]
    sendbyte.append(1)
    sendbyte.append(0)
    k = len(sendbyte)
    for i in range(0,8):
        sendbyte[k-1] = sendbyte[k-1] + cbPatternVars[i].get() * int(pow(2,i))
    
    status.append("Identifier: ")
    status.append(sendbyte[k-2])
    status.append(" Data: ")
    status.append(sendbyte[k-1])
    status.append("Position: ")
    status.append(k-2)
    print status
        
def sendBPM():
    status=[]
    sendbyte.append(2)
    sendbyte.append(int(tBPM.get()))
    k = len(sendbyte)
    status.append("Identifier: ")
    status.append(sendbyte[k-2])
    status.append(" Data: ")
    status.append(sendbyte[k-1])
    status.append("Position: ")
    status.append(k-2)
    
    print status
    
def sendParam1():
    status = []
    sendbyte.append(int(lbP1.get())*3 + 4)
    sendbyte.append(int(tP11.get()))
    k = len(sendbyte)
    status.append("Identifier: ")
    status.append(sendbyte[k-2])
    status.append(" Data: ")
    status.append(sendbyte[k-1])
    status.append("Position: ")
    status.append(k-2)
    print status
    
def sendParam2():
    status=[]
    sendbyte.append(int(lbP1.get())*3 + 5)
    sendbyte.append(int(tP12.get()))
    k = len(sendbyte)
    status.append("Identifier: ")
    status.append(sendbyte[k-2])
    status.append(" Data: ")
    status.append(sendbyte[k-1])
    status.append("Position: ")
    status.append(k-2)
        
    print status

def sendParam3():
    status=[]
    sendbyte.append(int(lbP1.get())*3 + 6)
    sendbyte.append(int(tP13.get()))
    k = len(sendbyte)
    status.append("Identifier: ")
    status.append(sendbyte[k-2])
    status.append(" Data: ")
    status.append(sendbyte[k-1])
    status.append("Position: ")
    status.append(k-2)
        
    print status
    
def sendAll():
    sendParam1()
    sendParam2()
    sendParam3()    
    
def initPort():
    if Port.isOpen():
        Port.close()
    if lbConfig.get(1) != "" and lbConfig.get(1)!="No ports":
        
        lbConfig.delete(7,END)
        
        #print lbConfig.get(1)
        Port.port = lbConfig.get(1)
        Port.baudrate = lbConfig.get(3)
        print Port
        Port.open()
        Port.flushInput();
        lbConfig.delete(5)
        lbConfig.insert(5, "Open")
        readerStarted.set()
    else:
        lbConfig.delete(5)
        lbConfig.insert(5, "Impossible")

def deinitPort():
    readerStarted.clear()
    if Port.isOpen():
        Port.close()
    lbConfig.delete(5)
    started.clear()
    lbConfig.insert(5, "Closed")
def chosePort():
    if not Port.isOpen():
        if(len(lbPorts.curselection())>0):
            lbConfig.delete(1, 1)
            lbConfig.insert(1, lbPorts.get(lbPorts.curselection()))
def choseRate():
    if not Port.isOpen():
        if(len(lbBaud.curselection())>0):
            lbConfig.delete(3, 3)
            lbConfig.insert(3, lbBaud.get(lbBaud.curselection()))
def listPorts():
    lbPorts.delete(0,END)
    ports = serial_ports()
    for i in ports:
        lbPorts.insert(END, i)
    if len(ports) == 0:
        lbPorts.insert(END, "No Ports")
        lbConfig.insert(END, "No Ports available")  

def timer():
    buf = 1
    while running.isSet():
        
        while(started.isSet()):
            sendEvent()
            if(eTimer.get() != "" and float(eTimer.get()) != 0):
                buf = float(eTimer.get())
            time.sleep(buf)
        
        while(not started.isSet()):
            sleep(0.2)
    return 

def startTimer():
    started.set()
    if not eventThread.isAlive():
        eventThread.start()

def stopTimer():
    started.clear()

def reader():
    timeOld = float(0)
    timeDelta = float(0)
    timeDeltaNew = float(0)
    offset = 0
    while running.isSet():
        
        if readerStarted.isSet():
            sleep(0.001)
            if Port.inWaiting()>0:
                b = list(bytearray(Port.read(), "hex"))
                if int(b[0]) == 1 and len(sendbyte)>0:
                    Port.write(sendbyte)
                    length = len(sendbyte)
                    temp = int(lbStatistics.get(5))+length
                    lbStatistics.delete(5)
                    lbStatistics.insert(5,temp)
                    del sendbyte[0:length]
                if int(b[0]) == 1:
                    temp = int(lbStatistics.get(1))+1
                    lbStatistics.delete(1)
                    lbStatistics.insert(1,temp)
                
                    timeDeltaNew = time.clock()-timeOld
                    if(timeDelta < timeDeltaNew and offset > 200):
                        lbStatistics.delete(3)
                        lbStatistics.insert(3, timeDeltaNew)
                        timeDelta = timeDeltaNew;
                    timeOld = time.clock()
                    if(offset < 202):
                        offset+=1
                        
                if int(b[0]) != 1:
                    print int(b[0])
        if not  readerStarted.isSet():
            timeOld = float(0)
            timeDelta = float(0)
            timeDeltaNew = float(0)
            offset = 0
            
            lbStatistics.delete(1)
            lbStatistics.insert(1, 0)
            lbStatistics.delete(3)
            lbStatistics.insert(3,0)
            lbStatistics.delete(5)
            lbStatistics.insert(5,0)
        while not readerStarted.isSet() or not Port.isOpen():
            sleep(0.01)
            



running = Event()
running.set()
started = Event()               #Timer laeuft
sendbyte = bytearray()         #Sendebuffer
readerStarted = Event()         #SerialListener gestarted



ready = Event()                 #Arduino bereit schreibzugriff auf sendbytes nicht gestattet
available = Event()             #Neue Daten im Sendebuffer
root = Tk()
root.protocol("WM_DELETE_WINDOW", closeHandler)
root.title("Serial Protocoll Tester")
eventThread = Thread(target = timer)
readThread = Thread(target = reader)

Port = serial.Serial()

#PortChoice
ports = []
ports = serial_ports()
lPorts = Label(root, text="Available Ports")
lBaud = Label(root, text="Baudrates")
lChose = Label(root, text ="Port Status")
lbPorts = Listbox(root,exportselection=0)
lbBaud = Listbox(root,exportselection=0)
lbConfig = Listbox(root,exportselection=0)
lbStatistics = Listbox(root, exportselection=0)
for i in [0.5,1,2,4,6,8,10,12]:
    lbBaud.insert(END,int( i*9600))
for i in ports:
    lbPorts.insert(END, i)
if len(ports) == 0:
    lbPorts.insert(END, "No Ports")
lbConfig.insert(0, "Portname:")
lbConfig.insert(1, "")
lbConfig.insert(2, "Baurate:")
lbConfig.insert(3, "115200")
lbConfig.insert(4, "Status:")
lbConfig.insert(5, "Closed")
lbConfig.insert(6,"Errors:")
lbStatistics.insert(0,"Arduino Loops:")
lbStatistics.insert(1,"0")
lbStatistics.insert(2,"Max Looptime:")
lbStatistics.insert(3,"0")
lbStatistics.insert(4,"Parameters send:")
lbStatistics.insert(5,"0")
bcheck = Button(root, text="List Ports", command = listPorts)
bOpen = Button(root, text ="Open Port", command = initPort)
bClose = Button(root, text = "Close Port", command = deinitPort)
bInit = Button(root, text = "Chose Port", command = chosePort)
bDeinit = Button(root, text = "Chose Rate", command = choseRate)
lPorts.grid(row = 0, column = 0)
lBaud.grid(row = 0, column = 1, columnspan = 3)
lChose.grid(row = 0, column = 4, columnspan = 3)
lbPorts.grid(row = 1, column = 0, rowspan = 5, sticky = W+E)
lbBaud.grid(row = 1, column = 1, columnspan = 3, rowspan = 5, sticky = W+E)
lbConfig.grid(row = 1, column = 4, columnspan = 3, rowspan = 5, sticky = W+E)
lbStatistics.grid(row =1, column = 10, columnspan = 3, rowspan = 5, sticky = W+E)
bInit.grid(row=7, column = 0, sticky= W+E)
bDeinit.grid(row=7, column = 1, columnspan = 3, sticky= W+E)
bcheck.grid(row = 1, column = 7, columnspan = 3, sticky = W+E+N+S)
bOpen.grid(row = 2, column = 7, columnspan = 3, sticky = W+E+N+S)
bClose.grid(row = 3, column = 7, columnspan = 3, sticky = W+E+N+S)
#EventMessage    
lEvent = Label(root, text="Event")
bEvent = Button(root, text="Send Event", command = sendEvent)
bTimer = Button(root, text="Send Every:", command = startTimer)
bTimSt = Button(root, text="Stop Sending", command = stopTimer)
eTimer = Entry(root)
lEvent.grid(row = 9, column = 0)
bEvent.grid(row = 10, column = 0, sticky = W+E)
bTimer.grid(row = 10, column = 1, columnspan = 3, sticky = W+E)
bTimSt.grid(row = 10, column = 7, columnspan = 3, sticky = W+E)
eTimer.grid(row = 10, column = 4, columnspan = 3, sticky = W+E)
lEvents = []
cbEvent = []
cbEventVars = [0,0,0,0,0,0,0,0]
for i in range(0,8):
    cbEventVars[i] = IntVar()
    lEvents.append(Label(root, text = 2**i))
    cbEvent.append(Checkbutton(root, variable = cbEventVars[i]))
    lEvents[i].grid(row = 8, column = i+1)
    cbEvent[i].grid(row = 9, column = i+1)


#PatternMessage
lPattern = Label(root, text="Pattern")
bPattern = Button(root, text="Send Pattern", command = sendPattern)
lPattern.grid(row = 12, column = 0)
bPattern.grid(row = 13, column = 0, sticky = W+E)
lPatterns = []
cbPattern = []
cbPatternVars = [0,0,0,0,0,0,0,0]
for i in range(0,8):
    cbPatternVars[i] = IntVar()
    lPatterns.append(Label(root, text = 2**i))
    cbPattern.append(Checkbutton(root, variable = cbPatternVars[i]))
    lPatterns[i].grid(row = 11, column = i+1)
    cbPattern[i].grid(row = 12, column = i+1)

#BPMMessage
bpm = StringVar()
lBPM = Label(root, text="BPM")
lBPM2 = Label(root, text= "Song BPM")
bBPM = Button(root, text="Send BPM", command = sendBPM)
tBPM = Spinbox(root, values=range(0,256))
lBPM2.grid(row = 14, column = 1, columnspan= 3)
lBPM.grid(row = 15, column = 0)
bBPM.grid(row = 16, column = 0, sticky = W+E)
tBPM.grid(row = 15, column = 1, columnspan = 3)
#PatternConfig
paramlist = []
paramlist.append("");
paramlist.append("");
paramlist.append("");
paramlist[0] = StringVar()
paramlist[1] = StringVar()
paramlist[2] = StringVar()

lDist = Label(root, text = "  ")
lP1 = Label(root, text="Pattern Configuration")
lbP1 = Spinbox(root, values=range(0,8))
tP11 = Entry(root, textvariable = paramlist[0])
tP12 = Entry(root, textvariable = paramlist[1])
tP13 = Entry(root, textvariable = paramlist[2])
lP11 = Label(root, text = "Parameter1")
lP12 = Label(root, text = "Parameter2")
lP13 = Label(root, text = "Parameter3")
bPall = Button(root, text = "Send All", command = sendAll)
bP11 = Button(root, text = "Send Param1", command = sendParam1)
bP12 = Button(root, text = "Send Param2", command = sendParam2)
bP13 = Button(root, text = "Send Param3", command = sendParam3)
#for pattern in patterns:
#    lbP1.insert(END, pattern)
lDist.grid(row = 17, column = 0)
lP1.grid(row = 18, column = 0)
lbP1.grid(row = 19, column = 0)
tP11.grid(row = 19, column = 1, columnspan = 3)
tP12.grid(row = 19, column = 4, columnspan = 3)
tP13.grid(row = 19, column = 7, columnspan = 3)
lP11.grid(row = 18, column = 1, columnspan = 3)
lP12.grid(row = 18, column = 4, columnspan = 3)
lP13.grid(row = 18, column = 7, columnspan = 3)
bPall.grid(row = 20, column = 0, columnspan = 1, sticky=W+E)
bP11.grid(row = 20, column = 1, columnspan = 3, sticky=W+E)
bP12.grid(row = 20, column = 4, columnspan = 3, sticky=W+E)
bP13.grid(row = 20, column = 7, columnspan = 3, sticky=W+E)
readThread.start()
readerStarted.set()
root.mainloop()
