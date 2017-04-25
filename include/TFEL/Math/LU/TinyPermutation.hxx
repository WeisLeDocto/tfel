/*!
 * \file   include/TFEL/Math/LU/TinyPermutation.hxx
 * 
 * \brief    
 * \author Helfer Thomas
 * \date   01 Aug 2006
 * \copyright Copyright (C) 2006-2014 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#ifndef LIB_TFEL_MATH_TINYPERMUTATION_HXX
#define LIB_TFEL_MATH_TINYPERMUTATION_HXX 

#include"TFEL/Math/tvector.hxx"

namespace tfel{

  namespace math{

    template<unsigned short N>
    struct TinyPermutation
      : protected tvector<N,unsigned short>
    {
      //! default constructor
      TinyPermutation();
      //! disabling default constructors and assignement operators
      TinyPermutation(const TinyPermutation&) = delete;
      TinyPermutation(TinyPermutation&&) = delete;
      TinyPermutation&
      operator=(const TinyPermutation&) = delete;
      TinyPermutation&
      operator=(TinyPermutation&&) = delete;
      //! apply the permutation to the given vector
      template<typename T>
      TFEL_MATH_INLINE void exe(tvector<N,T>&) const;

      using tvector<N,unsigned short>::operator[];
      using tvector<N,unsigned short>::operator();
      using tvector<N,unsigned short>::size;
            
      TFEL_MATH_INLINE void
      swap(const unsigned short,
	   const unsigned short);

      TFEL_MATH_INLINE bool
      isIdentity() const;
      
    protected:

      bool is_identity;

    };

  } // end of namespace math

} // end of namespace tfel

#include"TFEL/Math/LU/TinyPermutation.ixx"

#endif /* LIB_TFEL_MATH_TINYPERMUTATION_HXX */

