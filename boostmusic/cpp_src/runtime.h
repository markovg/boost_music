#ifndef RUNTIME_H
#define RUNTIME_H

#include "music/runtime.hh"
#include "setup.h"

class PyRuntime : public MUSIC::Runtime {

public:
  
 PyRuntime(PySetup& setup, double dt) : MUSIC::Runtime(&setup,dt) {};
  
  // returns mpi4py comm object
  py::object communicator();


};



#define CLASSDEF_RUNTIME \
  py::class_<PyRuntime>("Runtime",py::init<PySetup&,double>())	\
    .def("communicator", &PyRuntime::communicator)  \
    .def("tick", &MUSIC::Runtime::tick) \
    .def("time", &MUSIC::Runtime::time) \
    .def("finalize", &MUSIC::Runtime::finalize) \
    ; \
   py::implicitly_convertible< PyRuntime, MUSIC::Runtime >();





#endif
