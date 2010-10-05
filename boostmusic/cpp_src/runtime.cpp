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
#include "music/runtime.hh"


/* MPI headers */

#include <mpi.h>
#include <mpi4py/mpi4py.h>

namespace py = boost::python;

#include "runtime.h"


py::object PyRuntime::communicator() {

  using namespace py::numeric;

  MPI_Comm comm = MUSIC::Runtime::communicator();

  import_mpi4py();

  PyObject* p_comm = PyMPIComm_New(comm);
  
  if (p_comm==NULL)
    return py::object();  //Py_None

  return py::object(py::handle<>(p_comm));

}



