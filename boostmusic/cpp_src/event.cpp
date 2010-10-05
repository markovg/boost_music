
#include <boost/python.hpp>
#include <boost/python/pure_virtual.hpp>
#include "music/index_map.hh"

namespace py = boost::python;

#include "event.h"



void PyEventHandlerGlobalIndex::operator () (double t, MUSIC::GlobalIndex id)
{
  this->get_override("__call__")(t, id);
}
