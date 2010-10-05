#!/usr/bin/python

import yaml, numpy
import sys,os,os.path

import boostmusic as music
import vegl

import config as config_module



def main():

    # music setup
    setup = music.Setup (sys.argv)
    from mpi4py import MPI

    # parge commandline args,
    # and load configure yaml files
    config = config_module.do_config()
    dt = config.dt

    print "dt=%f" % dt

    # get music comm
    comm = setup.communicator ()
    myrank = comm.Get_rank()
    nprocs = comm.Get_size()
    msg = "Hello, World! I am process %d of %d.\n"
    print msg % (myrank, nprocs)

    if myrank>0:
        print "Error: rank>1 but currently supports only 1 music process."
        comm.Abort(1)

    # Entering runtime phase

    #def getconf(var):
    #    print "Config: %s=%s" % (var, setup.config(var))
    #getconf("foobar")
    #getconf("stoptime")

    evport = setup.publishEventInput("plot");
   
    if not evport.isConnected():
        print "Error: port 'plot' not connected."
        comm.Abort(1)
    else:
        print "Port 'plot' has width %d" % evport.width()
    
    #MUSIC::LinearIndex indexmap(0, evport->width());
    #evport->map (&indexmap, this, 0.0);


    runtime = music.Runtime (setup, dt)

    print "hello after"

    msg = "Time=%f" % runtime.time()

    sys.stderr.write(msg)





    # Must end with a call to finalize ()
    runtime.finalize ()


if __name__ == "__main__":
    main()
