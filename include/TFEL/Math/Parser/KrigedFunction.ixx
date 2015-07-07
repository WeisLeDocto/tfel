/*!
 * \file   include/TFEL/Math/Parser/KrigedFunction.ixx
 * \brief  
 * 
 * \author Helfer Thomas
 * \date   02 oct 2007
 * \copyright Copyright (C) 2006-2014 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#ifndef LIB_TFEL_MATH_PARSER_KRIGEDFUNCTION_IXX_
#define LIB_TFEL_MATH_PARSER_KRIGEDFUNCTION_IXX_ 

namespace tfel
{

  namespace math
  {

    namespace parser
    {

      template<unsigned short N>
      KrigedFunction<N>::KrigedFunction(const std::vector<typename KrigedFunction<N>::Point>& points,
					const double n)
	: k(new Kriging<N>())
      {
	using namespace std;
	typename vector<Point>::const_iterator p;
	for(p=points.begin();p!=points.end();++p){
	  this->k->addValue(p->first,p->second);
	}
	this->k->setNuggetEffect(n);
	this->k->buildInterpolation();
      } // end of KrigedFunction<N>::KrigedFunction

      template<unsigned short N>
      KrigedFunction<N>::KrigedFunction(const KrigedFunction<N>& src)
	: ExternalFunction(src),
	  k(src.k),
	  v(src.v)
      {} // end of KrigedFunction<N>::KrigedFunction

      template<unsigned short N>
      double
      KrigedFunction<N>::getValue(void) const
      {
	return this->k->operator()(this->v);
      } // end of KrigedFunction<N>::getValue(void)

      template<unsigned short N>
      void
      KrigedFunction<N>::setVariableValue(const std::vector<double>::size_type i_,
					  const double v_)
      {
	typename Variable::size_type i(static_cast<typename Variable::size_type>(i_));
	if(i>=N){
	  KrigedFunctionBase::throwInvalidIndexException(i,N);
	}
	this->v(i) = v_;
      } // end of KrigedFunction<N>::setVariableValue

      template<>
      void
      KrigedFunction<1u>::setVariableValue(const std::vector<double>::size_type,
					   const double);

      template<unsigned short N>
      std::vector<double>::size_type
      KrigedFunction<N>::getNumberOfVariables(void) const
      {
	return N;
      } // end of KrigedFunction<N>::getNumberOfVariables

      template<unsigned short N>
      void
      KrigedFunction<N>::getParametersNames(std::set<std::string>&) const
      {} // end of KrigedFunction<N>::getParametersNames

      template<unsigned short N>
      void
      KrigedFunction<N>::checkCyclicDependency(const std::string&) const
      {} // end of KrigedFunction<N>::checkCyclicDependency

      template<unsigned short N>
      void
      KrigedFunction<N>::checkCyclicDependency(std::vector<std::string>&) const
      {} // end of KrigedFunction<N>::checkCyclicDependency

      template<unsigned short N>
      std::shared_ptr<ExternalFunction>
      KrigedFunction<N>::differentiate(const std::vector<double>::size_type) const
      {
	KrigedFunctionBase::throwUnimplementedDifferentiateFunctionException();
	return {};
      } // end of KrigedFunction<N>::differentiate

      template<unsigned short N>
      std::shared_ptr<ExternalFunction>
      KrigedFunction<N>::differentiate(const std::string&) const
      {
	KrigedFunctionBase::throwUnimplementedDifferentiateFunctionException();
	return {};
      } // end of KrigedFunction<N>::differentiate

      template<unsigned short N>
      std::shared_ptr<ExternalFunction>
      KrigedFunction<N>::resolveDependencies(void) const
      {
	return std::shared_ptr<ExternalFunction>(new KrigedFunction<N>(*this));
      } // end of KrigedFunction<N>::resolveDependencies

      template<unsigned short N>
      std::shared_ptr<ExternalFunction>
      KrigedFunction<N>::createFunctionByChangingParametersIntoVariables(const std::vector<std::string>&) const
      {
	KrigedFunctionBase::throwInvalidCreateFunctionByChangingParametersIntoVariables();
	return {};
      } // end of KrigedFunction<N>::createFunctionByChangingParametersIntoVariables

      template<unsigned short N>
      std::shared_ptr<ExternalFunction>
      KrigedFunction<N>::createFunctionByChangingParametersIntoVariables(std::vector<std::string>& vnames,
									 const std::vector<double>&,
									 const std::vector<std::string>&,
									 const std::map<std::string,
									 std::vector<double>::size_type>&) const
      {
	vnames.clear();
	return this->resolveDependencies();
      } // end of KrigedFunction<N>::createFunctionByChangingParametersIntoVariables

      template<unsigned short N>
      KrigedFunction<N>::~KrigedFunction()
      {} // end of KrigedFunction<N>::~KrigedFunction()

    } // end of namespace parser

  } // end of namespace math

} // end of namespace tfel

#endif /* LIB_TFEL_MATH_PARSER_KRIGEDFUNCTION_IXX_ */
