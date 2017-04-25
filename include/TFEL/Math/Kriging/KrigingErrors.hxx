/*! 
 * \file  include/TFEL/Math/Kriging/KrigingErrors.hxx
 * \brief
 * \author Helfer Thomas
 * \brief 10 avr 2009
 * \copyright Copyright (C) 2006-2014 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#ifndef LIB_TFEL_MATH_KRINGINGERRORS_HXX
#define LIB_TFEL_MATH_KRINGINGERRORS_HXX 

#include<stdexcept>

#include"TFEL/Config/TFELConfig.hxx"

namespace tfel
{

  namespace math
  {

    struct TFELMATHKRIGING_VISIBILITY_EXPORT KrigingErrorInvalidLength
      : public std::runtime_error
    {
      KrigingErrorInvalidLength();
      KrigingErrorInvalidLength(const KrigingErrorInvalidLength&) = default;
      virtual ~KrigingErrorInvalidLength() noexcept;
    }; // end of struct KrigingErrorInvalidLength

    struct TFELMATHKRIGING_VISIBILITY_EXPORT KrigingErrorNoDataSpecified
      : public std::runtime_error
    {
      KrigingErrorNoDataSpecified();
      KrigingErrorNoDataSpecified(const KrigingErrorNoDataSpecified&) = default;
      virtual ~KrigingErrorNoDataSpecified() noexcept;
    }; // end of struct KrigingErrorNoDataSpecified

    struct TFELMATHKRIGING_VISIBILITY_EXPORT KrigingErrorInsufficientData
      : public std::runtime_error
    {
      KrigingErrorInsufficientData();
      KrigingErrorInsufficientData(const KrigingErrorInsufficientData&) = default;
      virtual ~KrigingErrorInsufficientData() noexcept;
    }; // end of struct KrigingErrorInsufficientData

  } // end of namespace math

} // end of namespace tfel

#endif /* LIB_TFEL_MATH_KRINGINGERRORS_HXX */

