#!/usr/bin/env python
"""
MUSIC Hello World
"""

import sys
import boostmusic as music

print "1:", sys.argv
setup = music.Setup (sys.argv)
from mpi4py import MPI
print "2:", sys.argv


msg = "Hello, World! I am process %d of %d.\n"
comm = setup.communicator ()
myrank = comm.Get_rank()
nprocs = comm.Get_size()
sys.stdout.write(msg % (myrank, nprocs))

port_id = sys.argv[1]
mode = sys.argv[2]

class X(music.EventHandlerGlobalIndex):
    def __call__(self,f,idx):
        print f,int(idx)

if mode=="out":
    evport = setup.publishEventOutput(port_id);

    evh = X()

    #index_map = music.LinearIndex(music.GlobalIndex(0),evport->width() )
    index_map = music.LinearIndex(music.GlobalIndex(0),27)

    evport.map(index_map,music.IndexType.GLOBAL)


if mode=="in":
    evport = setup.publishEventInput(port_id);


    evh = X()

    #index_map = music.LinearIndex(music.GlobalIndex(0),evport->width() )
    index_map = music.LinearIndex(music.GlobalIndex(0),27)

    evport.map(index_map,evh,0.0)


print "Connected?: ", evport.isConnected()



def getconf(var):
    print "Config: %s=%s" % (var, setup.config(var))
getconf("foobar")
getconf("stoptime")
getconf("myint")





# Entering runtime phase
runtime = music.Runtime (setup, 1e-4)

print "Time=%f" % runtime.time()
runtime.tick()
print "Time=%f" % runtime.time()


# Must end with a call to finalize ()
runtime.finalize ()
