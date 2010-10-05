#ifndef EVENT_H
#define EVENT_H

#include "music/event.hh"


/* Here we wrap 

EventHandlerGlobalIndex
EventHandlerLocalIndex

These are pure virtual functions, for which we must override operator() 
in Python!

Documentation how to do this in boost is provided here:

http://www.boost.org/doc/libs/1_40_0/libs/python/doc/tutorial/doc/html/python/exposing.html#python.class_virtual_functions

Under the section: "Class Virtual Functions"

*/

class PyEventHandlerGlobalIndex : public MUSIC::EventHandlerGlobalIndex, public py::wrapper<MUSIC::EventHandlerGlobalIndex> {

 public:

  void operator () (double t, MUSIC::GlobalIndex id);

};

#define CLASSDEF_EVHANDLER_GLOBAL \
  py::class_<PyEventHandlerGlobalIndex, boost::noncopyable>("EventHandlerGlobalIndex",py::init<>() ) \
    .def("__call__", py::pure_virtual(&MUSIC::EventHandlerGlobalIndex::operator()) ) \
    ;  
  //py::implicitly_convertible< PyEventHandlerGlobalIndex, MUSIC::EventHandlerGlobalIndex >();




#endif
