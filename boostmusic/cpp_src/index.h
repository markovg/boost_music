#ifndef INDEX_H
#define INDEX_H

#include "music/index_map.hh"
#include "music/linear_index.hh"


//BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS(map_overloads, map , 2, 4)

#define ENUMDEF_INDEXTYPE \
  py::enum_<MUSIC::Index::Type>("IndexType") \
  .value("LOCAL", MUSIC::Index::LOCAL)	     \
  .value("GLOBAL", MUSIC::Index::GLOBAL)     \
  ;

#define CLASSDEF_INDEX \
  py::class_<MUSIC::Index>("Index",py::no_init) \
    ;

#define CLASSDEF_GLOBALINDEX \
  py::class_<MUSIC::GlobalIndex, py::bases<MUSIC::Index> >("GlobalIndex",py::init<int>()) \
    .def(py::init<>())  \
    .def(py::self_ns::int_(py::self))		\
    ;

#define CLASSDEF_LOCALINDEX \
  py::class_<MUSIC::LocalIndex, py::bases<MUSIC::Index> >("LocalIndex",py::init<int>()) \
    .def(py::init<>())  \
    .def(py::self_ns::int_(py::self))		\
    ;

#define CLASSDEF_INDEXMAP \
  py::class_<MUSIC::IndexMap,boost::noncopyable >("IndexMap",py::no_init)		\
  .def("copy",py::pure_virtual(&MUSIC::IndexMap::copy), py::return_value_policy<py::manage_new_object>())	\
    ; 


#define CLASSDEF_LINEARINDEX \
  py::class_<MUSIC::LinearIndex, py::bases<MUSIC::IndexMap> >("LinearIndex",py::init<MUSIC::GlobalIndex, int>()) \
    ; 



#endif
