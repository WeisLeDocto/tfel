/*! 
 * \file  stl.cxx
 * \brief
 * \author Helfer Thomas
 * \brief 30 avr 2010
 */

#include<string>
#include<map>

#include<boost/python.hpp>
#include<boost/python/suite/indexing/map_indexing_suite.hpp>

BOOST_PYTHON_MODULE(_stl_map)
{
  using namespace std;
  using namespace boost;
  using namespace boost::python;
  using boost::shared_ptr;
  class_<map<string,double>,shared_ptr<map<string,double> > >("StringDoubleMap")
    .def(map_indexing_suite<map<string,double> >());

  class_<map<string,string>,shared_ptr<map<string,string> > >("StringStringMap")
    .def(map_indexing_suite<map<string,string> >());

}

