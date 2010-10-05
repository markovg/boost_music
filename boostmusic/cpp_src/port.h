#ifndef PORT_H
#define PORT_H

#include "music/port.hh"
#include "music/index_map.hh"


BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(EvOutPort_map_ol, MUSIC::EventOutputPort::map, 2, 3)
BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(EvInPort_map_ol24, MUSIC::EventInputPort::map, 2, 4)
//BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(EvInPort_map_ol4, MUSIC::EventInputPort::map, 4, 4)

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(EvOutPort_insert_ol, MUSIC::EventOutputPort::insertEvent, 2, 2)

#define CLASSDEF_PORT \
  py::class_<MUSIC::Port>("Port",py::no_init)		  \
    .def("isConnected",&MUSIC::Port::isConnected) \
    .def("width",&MUSIC::Port::width) \
    .def("hasWidth",&MUSIC::Port::width) \
    ; 

/*
#define CLASSDEF_TICKINGPORT \
  py::class_<MUSIC::TickingPort, py::bases<MUSIC::Port> >("TickingPort")	\
    .def("tick",&MUSIC::TickingPort::tick) \
    ;
*/

#define CLASSDEF_INPUTPORT \
  py::class_<MUSIC::InputPort, py::bases<MUSIC::Port> >("InputPort",py::no_init)	\
    ;

#define CLASSDEF_OUTPUTPORT \
  py::class_<MUSIC::OutputPort, py::bases<MUSIC::Port> >("OutputPort",py::no_init)	\
    ;

#define CLASSDEF_REDISTRIBUTIONPORT \
  py::class_<MUSIC::RedistributionPort, py::bases<MUSIC::Port> >("RedistributionPort",py::no_init) \
    ;

#define CLASSDEF_INPUTREDISTRIBUTIONPORT \
  py::class_<MUSIC::InputRedistributionPort, py::bases<MUSIC::InputPort,MUSIC::RedistributionPort> >("InputRedistributionPort",py::no_init) \
    .def("setupCleanup",&MUSIC::InputRedistributionPort::setupCleanup) \
    ;

#define CLASSDEF_OUTPUTREDISTRIBUTIONPORT \
  py::class_<MUSIC::OutputRedistributionPort, py::bases<MUSIC::OutputPort,MUSIC::RedistributionPort> >("OutputRedistributionPort",py::no_init) \
    .def("setupCleanup",&MUSIC::OutputRedistributionPort::setupCleanup) \
    ;


// TODO: Input/Output RedistributionPort


#define CLASSDEF_CONTPORT \
  py::class_<MUSIC::ContPort, py::bases<MUSIC::Port> >("ContPort",py::no_init)	\
    ;

// TODO: ContInputPort, ContOutputPort


#define CLASSDEF_EVENTPORT \
  py::class_<MUSIC::EventPort, py::bases<MUSIC::Port> >("EventPort",py::no_init) \
    ;

//  .def("map",MUSIC::EventInputPort::map, map_overloads() )	\
 
#define CLASSDEF_EVENTINPUTPORT \
  py::class_<MUSIC::EventInputPort, py::bases<MUSIC::EventPort> >("EventInputPort",py::init<PySetup*,std::string>()) \
    .def("map", (void(MUSIC::EventInputPort::*)(MUSIC::IndexMap*, MUSIC::EventHandlerGlobalIndex*, double, int) const)0, \
EvInPort_map_ol24() ) \
    .def("map", (void(MUSIC::EventInputPort::*)(MUSIC::IndexMap*, MUSIC::EventHandlerLocalIndex*, double, int) const)0, \
EvInPort_map_ol24() ) \
 ;


//     .def("map",MUSIC::EventOutputPort::map, map_overloads() ) \


#define CLASSDEF_EVENTOUTPUTPORT \
  py::class_<MUSIC::EventOutputPort, py::bases<MUSIC::EventPort> >("EventOutputPort",py::init<PySetup*,std::string>()) \
    .def("map", (void(MUSIC::EventOutputPort::*)(MUSIC::IndexMap*, MUSIC::Index::Type, int) const)0, \
      EvOutPort_map_ol() ) \
    .def("insertEvent", (void(MUSIC::EventOutputPort::*)(double, MUSIC::GlobalIndex) const)0,EvOutPort_insert_ol() ) \
    .def("insertEvent", (void(MUSIC::EventOutputPort::*)(double, MUSIC::LocalIndex) const)0,EvOutPort_insert_ol() ) \
    ;

//X_f_overloads(args("self", "x", "y", "z"))
// py::args("indices","type","maxBuffered")), "TODO: docstring" 



#endif
