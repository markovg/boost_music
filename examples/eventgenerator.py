#!/usr/bin/python

import sys

import boostmusic as music
import numpy
from math import floor,ceil

from time import time,sleep

setup = music.Setup (sys.argv)
from mpi4py.MPI import Wtime

stoptime = float(setup.config("stoptime"))
dt = float(setup.config("dt"))
mindelay = float(setup.config("mindelay"))

maxbuffered = int(setup.config("maxbuffered",0))

evport_dummyin = setup.publishEventInput("dummy_in");

evport = setup.publishEventOutput("out");

if not evport.isConnected():
    print "Error: eventgenerator - port 'out' not connected."
    comm.Abort(1)


# map dummy if required

class SimpleHandler(music.EventHandlerGlobalIndex):
    def __call__(self,f,idx):
        print "generator dummy [%d] event at %f s" % (int(idx),f)

if evport_dummyin.isConnected():
    print "Enabling port 'dummy_in'"
    evhandler = SimpleHandler()
    index_map = music.LinearIndex(music.GlobalIndex(0),1)
    evport_dummyin.map(index_map,evhandler,mindelay)



nunits = evport.width()
print "Port 'out' has width %d" % nunits

index_map = music.LinearIndex(music.GlobalIndex(0),nunits)
if maxbuffered>0:
    evport.map(index_map,music.IndexType.GLOBAL,maxbuffered)
else:
    evport.map(index_map,music.IndexType.GLOBAL)


rate = 0.5
nextTime = numpy.random.exponential(1.0/rate,size=nunits)


runtime = music.Runtime(setup, dt)

t = runtime.time()
base_time = Wtime()

while t<stoptime:

    for i in range(nunits):
        if nextTime[i]<t:
            print "generator [%d] event at %f s" % (i,t)
            evport.insertEvent(t,music.GlobalIndex(i))
            nextTime[i]+=numpy.random.exponential(1.0/rate)


    runtime.tick()
    t = runtime.time()

    # "realtime" stuff
    cur_time = Wtime()-base_time
    Dt = t-cur_time
    if Dt>dt:
        s = floor(Dt / dt)*dt
        #print "Warning: gen lead of %f seconds, sleeping %f s" % (Dt,s)
        music.nanosleep(s)
    elif Dt<0:
        n = int(ceil(-Dt / dt))
        print "Warning: gen lag of %f seconds, skipping %d ticks" % (-Dt,n)
        for i in range(n):
            runtime.tick()
        t = runtime.time()


print "generator done. elapsed t=%f s" % (Wtime()-base_time,)
    


runtime.finalize()






