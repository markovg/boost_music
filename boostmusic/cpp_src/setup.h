#ifndef SETUP_H
#define SETUP_H

#include "music/setup.hh"

class PySetup : public MUSIC::Setup {

public:
  
  PySetup(int& argc, char**& argv);

  
  // returns mpi4py comm object
  py::object communicator();
  py::object config(std::string name, py::object def=py::str(""));


};


// factory function for 
PySetup* new_Setup(py::list argv_);

/*
    .def("publishEventInput", &MUSIC::Setup::publishEventInput,\
	 py::return_value_policy<py::manage_new_object>()) \
  .def("publishEventOutput", &MUSIC::Setup::publishEventOutput, \
	 py::return_value_policy<py::manage_new_object>()) \
    ; \
*/

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(setup_config_ol,PySetup::config, 1,2)


#define CLASSDEF_SETUP \
  py::class_<PySetup>("Setup",py::no_init)    \
    .def("communicator", &PySetup::communicator)  \
    .def("__init__", py::make_constructor(new_Setup)) \
    .def("publishEventInput", &MUSIC::Setup::publishEventInput,\
	 py::return_value_policy<py::manage_new_object>()) \
    .def("publishEventOutput", &MUSIC::Setup::publishEventOutput, \
	 py::return_value_policy<py::manage_new_object>()) \
  .def("config",&PySetup::config, setup_config_ol(py::args("name","default"), "lookup music config 'name' and return 'default' if not found") ) \
    ; \
  ;\
  py::implicitly_convertible< PySetup, MUSIC::Setup >();




#endif
