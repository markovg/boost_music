#!/usr/bin/python

import sys

import boostmusic as music
import numpy
from math import floor,ceil

from time import time,sleep,asctime


setup = music.Setup(sys.argv)
from mpi4py.MPI import Wtime

stoptime = float(setup.config("stoptime"))
dt = float(setup.config("dt"))
mindelay = float(setup.config("mindelay"))

evport_dummyout = setup.publishEventOutput("dummy_out");

evport = setup.publishEventInput("in");

if not evport.isConnected():
    print "Error: eventreceiver - port 'in' not connected."
    comm.Abort(1)

# map dummy if required

if evport_dummyout.isConnected():
    print "Enabling port 'dummy_out'"
    index_map = music.LinearIndex(music.GlobalIndex(0),1)
    evport_dummyout.map(index_map,music.IndexType.GLOBAL)


nunits = evport.width()
print "Port 'in' has width %d" % nunits

events = []

class SimpleHandler(music.EventHandlerGlobalIndex):
    def __call__(self,f,idx):
        #print "receiver [%d] event at %f s" % (int(idx),f)
        events.append( (int(idx),f) )

evhandler = SimpleHandler()

index_map = music.LinearIndex(music.GlobalIndex(0),nunits)
evport.map(index_map,evhandler,mindelay)



runtime = music.Runtime(setup, dt)

print asctime()
t = runtime.time()
base_time = Wtime()

while t<stoptime:

    #print "rt%f" % t,

    for ev in events:
        print "receiver t=%f [%d] event t=%f" % ((t,)+ev)

    events = []

    runtime.tick()
    t = runtime.time()

    # "realtime" stuff
    cur_time = Wtime()-base_time
    Dt = t-cur_time
    if Dt>dt:
        s = floor(Dt / dt)*dt
        #print "Warning: recv lead of %f seconds, sleeping %f s" % (Dt,s)
        music.nanosleep(s)

    elif Dt<0:
        n = int(ceil(-Dt / dt))
        print "Warning: recv lag of %f seconds, skipping %d ticks" % (-Dt,n)
        for i in range(n):
            runtime.tick()
        t = runtime.time()



print "receiver done. elapsed t=%f s" % (Wtime()-base_time,)

runtime.finalize()

