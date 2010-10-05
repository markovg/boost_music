/* Stuff for numpy */

// this goes first
#define PY_ARRAY_UNIQUE_SYMBOL BoostMusic4py
// this goes in all .cpp files of one module that 
// don't have the main BOOST_PYTHON_MODULE(...)
// with "import_array()" inside it
#define NO_IMPORT_ARRAY

/* boost headers */

#include <boost/python.hpp>

#include "music/setup.hh"


/* MPI headers */

#include <mpi.h>
#include <mpi4py/mpi4py.h>

namespace py = boost::python;

#include "setup.h"


PySetup* new_Setup(py::list argv_) {

  int argc = py::len(argv_);
  char* storage[100];
  char** argv=storage;
  int i,l;

  // extract<char*>

  // copy

  for(i=0;i<argc;i++) {
    argv[i] = py::extract<char*>(argv_[i]);
    //printf("%s\n",argv[i]);
  }
  
  PySetup* setup = new PySetup(argc,argv);
  char *s;

  // clear argv_

  l = py::len(argv_);

  for(i=0;i<l;i++) {
    argv_.pop();
  }
  
  // Fill argv with C array

  for(int i=0;i<argc;i++) {
    
    argv_.append( py::handle<>(PyString_FromString(argv[i])));
    //argv_.append( py::str(argv[i]) );

  }

  return setup;

}



PySetup::PySetup(int& argc, char**& argv) : MUSIC::Setup(argc, argv) {

}


py::object PySetup::config(std::string name, py::object def) {

  std::string value;
  MUSIC::Setup::config(name,&value);
  if (value=="")
    return def;
  else
    return py::str(value);

}


py::object PySetup::communicator() {

  using namespace py::numeric;

  MPI_Comm comm = MUSIC::Setup::communicator();

  import_mpi4py();

  PyObject* p_comm = PyMPIComm_New(comm);
  
  if (p_comm==NULL)
    return py::object();  //Py_None

  return py::object(py::handle<>(p_comm));

}



