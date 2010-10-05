#!/usr/bin/python

import yaml

import sys,os,os.path


if len(sys.argv)<2:
    usage = """
data2yaml - convert music viewevents configfile to yaml for python version

usage:

data2yaml infile.data outfile.yaml

"""

    print usage

    sys.exit(0)


infile = sys.argv[1]
outfile = sys.argv[2]

if not os.path.exists(infile):
    print "error: infile does not exist."
    sys.exit(1)

if os.path.exists(outfile):
    print "error: outfile exists."


f = file(infile,'r')

lines = f.readlines()

f.close()

# line iterator
il = lines.__iter__()

def numbers2list(s,type=float):
    l = s.split(" ")
    return [type(x) for x in l]

d = {}

num_neurons = int(il.next())

assert num_neurons >= 1

neuron_types = []

for n in xrange(num_neurons):
    type = {}
    type['baseline_RGB'] = numbers2list(il.next())
    type['excited_RGB'] = numbers2list(il.next())
    neuron_types.append(type)

d['neuron_types'] = neuron_types

neurons = []

for l in il:
    neuron = {}
    tmp = numbers2list(l)
    neuron['type_index'] = int(tmp[-1])
    neuron['xyzr'] = tmp[:-1]
    neurons.append(neuron)

d['neurons'] = neurons


f = file(outfile,'w')

yaml.dump(d,f)

f.close()    

print "success."
