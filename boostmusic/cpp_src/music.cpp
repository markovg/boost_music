/* Stuff for numpy */

// this goes first
#define PY_ARRAY_UNIQUE_SYMBOL BoostMusic4py
// this goes in all .cpp files of one module that 
// don't have the main BOOST_PYTHON_MODULE(...)
// with "import_array()" inside it
//#define NO_IMPORT_ARRAY

/* boost headers */

//#include <Python.h>
#include <boost/python.hpp>
#include <boost/python/make_constructor.hpp>
#include <boost/python/enum.hpp>
#include <boost/python/pure_virtual.hpp>
#include <boost/python/overloads.hpp>
#include <boost/python/operators.hpp>
#include <boost/operators.hpp>

#include <boost/python/operators.hpp>
#include <boost/python/class.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>

namespace py = boost::python;

#include "numpy/arrayobject.h"

#include <mpi.h>
#include <mpi4py/mpi4py.h>

#include <time.h>
#include <math.h> 
//#include <fenv.h>

/* music class wrappers */


#include "index.h"
#include "event.h"
#include "port.h"
#include "setup.h"
#include "runtime.h"

/*
struct timespec {
  time_t tv_sec;       //seconds
  long   tv_nsec;       // nanoseconds 
}; 

int nanosleep(const struct timespec *req, struct timespec *rem);

*/

int my_nanosleep(double dt) {
  // sleeps for 


  // round to negative infinity
  //fesetround(3);

  timespec ts;
  timespec rem;

  double ns, seconds;
  ns = modf(dt,&seconds)*1e9;

  ts.tv_sec = seconds;
  ts.tv_nsec = ns;
  
  return nanosleep(&ts,&rem);

}



BOOST_PYTHON_MODULE(_music)
{

  py::def("nanosleep",my_nanosleep, py::args("dt"),"high-resolution sleep for dt seconds. returns 0 on success");

  //import_array();
  //py::numeric::array::set_module_and_type("numpy", "ndarray");


  CLASSDEF_SETUP
  CLASSDEF_RUNTIME
  CLASSDEF_PORT
  CLASSDEF_INPUTPORT
  CLASSDEF_OUTPUTPORT
  CLASSDEF_REDISTRIBUTIONPORT
    // CLASSDEF_OUTPUTREDISTRIBUTIONPORT
    //CLASSDEF_INPUTREDISTRIBUTIONPORT
  CLASSDEF_CONTPORT
  CLASSDEF_EVENTPORT
  CLASSDEF_EVENTINPUTPORT
  CLASSDEF_EVENTOUTPUTPORT

  CLASSDEF_INDEX
  CLASSDEF_INDEXMAP
  ENUMDEF_INDEXTYPE
  CLASSDEF_GLOBALINDEX
  CLASSDEF_LOCALINDEX
  CLASSDEF_LINEARINDEX
  CLASSDEF_EVHANDLER_GLOBAL
  

}
