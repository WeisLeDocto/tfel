/*!
 * \file   include/TFEL/Math/Tensor/tensor.ixx
 * \brief  This file implements the methods of the class tensor.
 * \author Helfer Thomas
 * \date   02 jun 2006
 * \copyright Copyright (C) 2006-2014 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#ifndef LIB_TFEL_TENSOR_IXX_
#define LIB_TFEL_TENSOR_IXX_ 

#include <cmath>
#include <iterator>

#include"TFEL/FSAlgorithm/FSAlgorithm.hxx"

#include"TFEL/TypeTraits/IsSafelyReinterpretCastableTo.hxx"
#include"TFEL/Math/General/Abs.hxx"
#include"TFEL/Math/General/ConstExprMathFunctions.hxx"
#include"TFEL/Math/Vector/VectorUtilities.hxx"
#include"TFEL/Math/Tensor/TensorChangeBasis.hxx"

namespace tfel{

  namespace math {

    namespace internals{
      
      /*!
       * An helper struct used to defined a tensor from the fortran
       * matrix
       */
      template<unsigned short N>
      struct BuildTensorFromFortranMatrix;

      /*!
       * Partial specialisation in 1D
       */
      template<>
      struct BuildTensorFromFortranMatrix<1u>
      {
	/*!
	 * \param[in] t : tensor
	 * \param[in] v : fortran values
	 */
	template<typename T>
	TFEL_MATH_INLINE2 static
	void exe(T* const t,
		 const typename tfel::typetraits::BaseType<T>::type* const v)
	{
	  t[0] = T(v[0]);
	  t[1] = T(v[4]);
	  t[2] = T(v[8]);
	} // end of exe
      }; // end of struct BuildTensorFromFortranMatrix<1u>

      /*!
       * Partial specialisation in 2D
       */
      template<>
      struct BuildTensorFromFortranMatrix<2u>
      {
	/*!
	 * \param[in] t : tensor
	 * \param[in] v : fortran values
	 */
	template<typename T>
	TFEL_MATH_INLINE2 static
	void exe(T* const t,
		 const typename tfel::typetraits::BaseType<T>::type* const v)
	{
	  BuildTensorFromFortranMatrix<1u>::exe(t,v);
	  t[3] = T(v[3]);
	  t[4] = T(v[1]);
	} // end of exe
      }; // end of struct BuildTensorFromFortranMatrix<1u>

      /*!
       * Partial specialisation in 3D
       */
      template<>
      struct BuildTensorFromFortranMatrix<3u>
      {
	/*!
	 * \param[in] t : tensor
	 * \param[in] v : fortran values
	 */
	template<typename T>
	TFEL_MATH_INLINE2 static
	void exe(T* const t,
		 const typename tfel::typetraits::BaseType<T>::type* const v)
	{
	  BuildTensorFromFortranMatrix<2u>::exe(t,v);
	  t[5] = T(v[6]);
	  t[6] = T(v[2]);
	  t[7] = T(v[7]);
	  t[8] = T(v[5]);
	} // end of exe
      }; // end of struct BuildTensorFromFortranMatrix<1u>
      
      template<unsigned short N>
      struct TensorMatrixAccessOperator;

      template<>
      struct TensorMatrixAccessOperator<1u>
      {
	template<typename T>
	TFEL_MATH_INLINE static T
	exe(const tfel::math::tensor<1u,T>& t,
	    const unsigned short i,
	    const unsigned short j)
	{
	  if((i>2)||(j>2)){
	    throw(TensorInvalidIndexesException());
	  }
	  return (i==j) ? t(i) : T(0);
	}
      };
      
      template<>
      struct TensorMatrixAccessOperator<2u>
      {
	template<typename T>
	TFEL_MATH_INLINE static T
	exe(const tfel::math::tensor<2u,T>& t,
	    const unsigned short i,
	    const unsigned short j)
	{
	  if((i>2)||(j>2)){
	    throw(TensorInvalidIndexesException());
	  }
	  if(i==j){
	    return t(i);
	  } else if((i==0)&&(j==1)){
	    return t(3);
	  } else if((i==1)&&(j==0)){
	    return t(4);
	  }
	  return T(0);
	}
      };

      template<>
      struct TensorMatrixAccessOperator<3u>
      {
	template<typename T>
	TFEL_MATH_INLINE static T
	exe(const tfel::math::tensor<3u,T>& t,
	    const unsigned short i,
	    const unsigned short j)
	{
	  if((i==j)&&(i<3)){
	    return t(i);
	  } else if((i==0)&&(j==1)){
	    return t(3);
	  } else if((i==1)&&(j==0)){
	    return t(4);
	  } else if((i==0)&&(j==2)){
	    return t(5);
	  } else if((i==2)&&(j==0)){
	    return t(6);
	  } else if((i==1)&&(j==2)){
	    return t(7);
	  } else if((i==2)&&(j==1)){
	    return t(8);
	  }
	  throw(TensorInvalidIndexesException());
	}
      };

    } // end of namespace internals

    template<typename Child>
    template<typename TensorType>
    typename std::enable_if<
      tfel::meta::Implements<TensorType,TensorConcept>::cond &&
      TensorTraits<Child>::dime==TensorTraits<TensorType>::dime &&
      tfel::typetraits::IsAssignableTo<typename TensorTraits<TensorType>::NumType,
				       typename TensorTraits<Child>::NumType>::cond,
      Child&>::type
    tensor_base<Child>::operator=(const TensorType& src){
      auto& child = static_cast<Child&>(*this);
      vectorToTab<TensorDimeToSize<TensorTraits<Child>::dime>::value>::exe(src,child);
      return child;
    }

    template<typename Child>
    template<typename TensorType>
    typename std::enable_if<
      tfel::meta::Implements<TensorType,TensorConcept>::cond &&
      TensorTraits<Child>::dime==TensorTraits<TensorType>::dime &&
      tfel::typetraits::IsAssignableTo<typename TensorTraits<TensorType>::NumType,
				       typename TensorTraits<Child>::NumType>::cond,
      Child&>::type
    tensor_base<Child>::operator+=(const TensorType& src){
      auto& child = static_cast<Child&>(*this);
      VectorUtilities<TensorDimeToSize<TensorTraits<Child>::dime>::value>::PlusEqual(child,src);
      return child;
    }

    template<typename Child>
    template<typename TensorType>
    typename std::enable_if<
      tfel::meta::Implements<TensorType,TensorConcept>::cond &&
      TensorTraits<Child>::dime==TensorTraits<TensorType>::dime &&
      tfel::typetraits::IsAssignableTo<typename TensorTraits<TensorType>::NumType,
				       typename TensorTraits<Child>::NumType>::cond,
      Child&>::type
    tensor_base<Child>::operator-=(const TensorType& src){
      auto& child = static_cast<Child&>(*this);
      VectorUtilities<TensorDimeToSize<TensorTraits<Child>::dime>::value>::MinusEqual(child,src);
      return child;
    }

    // *= operator
    template<typename Child>
    template<typename T2>
    typename std::enable_if<
      tfel::typetraits::IsScalar<T2>::cond&&
      std::is_same<typename ResultType<typename TensorTraits<Child>::NumType,
						 T2,OpMult>::type,
			     typename TensorTraits<Child>::NumType>::value,
      Child&>::type
    tensor_base<Child>::operator*=(const T2 s)
    {
      auto& child = static_cast<Child&>(*this);
      VectorUtilities<TensorDimeToSize<TensorTraits<Child>::dime>::value>::scale(child,s);
      return child;
    }

    // /= operator
    template<typename Child>
    template<typename T2>
    typename std::enable_if<
      tfel::typetraits::IsScalar<T2>::cond&&
      std::is_same<typename ResultType<typename TensorTraits<Child>::NumType,
						 T2,OpDiv>::type,
			     typename TensorTraits<Child>::NumType>::value,
      Child&>::type
    tensor_base<Child>::operator/=(const T2 s)
    {
      auto& child = static_cast<Child&>(*this);
      VectorUtilities<TensorDimeToSize<TensorTraits<Child>::dime>::value>::scale(child,(static_cast<typename tfel::typetraits::BaseType<T2>::type>(1u))/s);
      return child;
    }

    template<unsigned short N, typename T>
    void tensor<N,T>::buildFromFortranMatrix(tensor<N,T>& t,
					     const typename tfel::typetraits::BaseType<T>::type* const v)
    {
      using tfel::math::internals::BuildTensorFromFortranMatrix;
      BuildTensorFromFortranMatrix<N>::template exe<T>(t.begin(),v);
    } // end of void tensor<N,T>::buildFromFortranMatrix

    template<unsigned short N, typename T>
    template<typename T2,
	     typename std::enable_if<tfel::typetraits::IsAssignableTo<T2,T>::cond,bool>::type>
    constexpr tensor<N,T>::tensor(const T2& init)
      : fsarray<TensorDimeToSize<N>::value,T>(init)
    {}

    template<unsigned short N, typename T>
    T& 
    tensor<N,T>::operator()(const unsigned short i){
      return this->v[i];
    }

    template<unsigned short N, typename T>
    constexpr const T& 
    tensor<N,T>::operator()(const unsigned short i) const{
      return this->v[i];
    }

    template<unsigned short N, typename T>
    T
    tensor<N,T>::operator()(const unsigned short i,
			    const unsigned short j) const
    {
      using tfel::math::internals::TensorMatrixAccessOperator;
      return TensorMatrixAccessOperator<N>::exe(*this,i,j);
    }

    template<unsigned short N, typename T>
    constexpr typename tensor<N,T>::RunTimeProperties
    tensor<N,T>::getRunTimeProperties(void) const{
      return RunTimeProperties();
    }

    // Import from values
    template<unsigned short N,typename T>
    template<typename T2>
    typename std::enable_if<
      tfel::typetraits::IsSafelyReinterpretCastableTo<T2,typename tfel::typetraits::BaseType<T>::type>::cond,
      void>::type
    tensor<N,T>::import(const T2 * const src)
    {
      typedef typename tfel::typetraits::BaseType<T>::type base;
      typedef tfel::fsalgo::copy<TensorDimeToSize<N>::value> Copy;
      TFEL_STATIC_ASSERT((tfel::typetraits::IsSafelyReinterpretCastableTo<T,base>::cond));
      Copy::exe(src,reinterpret_cast<base*>(this->v));
    }

    // Write to Tab
    template<unsigned short N, typename T>
    void tensor<N,T>::write(typename tfel::typetraits::BaseType<T>::type* const t) const
    {
      typedef typename tfel::typetraits::BaseType<T>::type base;
      typedef tfel::fsalgo::copy<TensorDimeToSize<N>::value> Copy;
      TFEL_STATIC_ASSERT((tfel::typetraits::IsSafelyReinterpretCastableTo<T,base>::cond));
      Copy::exe(reinterpret_cast<const base*>(this->v),t);
    }

    // ChangeBasis
    template<unsigned short N,typename T>
    void 
    tensor<N,T>::changeBasis(const tmatrix<3u,3u,typename tfel::typetraits::BaseType<T>::type>& m)
    {
      TensorChangeBasis<N,T>::exe(this->v,m);
    }

    // Return Id
    template<unsigned short N,typename T>
    const tensor<N,T>&
    tensor<N,T>::Id(void)
    {
      typedef typename tfel::typetraits::BaseType<T>::type base;
      constexpr base zero{0};
      constexpr base one{1};
      constexpr base IdCoef[]  = {one,one,one,
				  zero,zero,zero,
				  zero,zero,zero};
      static const tensor<N,T> id(IdCoef);
      return id;
    } // end of tensor<N,T>::Id

    template<unsigned short N, typename T>
    template<typename InputIterator>
    void 
    tensor<N,T>::copy(const InputIterator src)
    {
      tfel::fsalgo::copy<TensorDimeToSize<N>::value>::exe(src,*this);
    }

    template<unsigned short N, typename T,
	     typename OutputIterator>
    TFEL_MATH_INLINE2
    typename std::enable_if<
      tfel::typetraits::IsScalar<T>::cond,
      void>::type
    exportToBaseTypeArray(const tensor<N,T>& t,
			  OutputIterator p)
    {    
      typedef typename tfel::typetraits::BaseType<T>::type base;
      typedef tfel::fsalgo::copy<TensorDimeToSize<N>::value> Copy;
      TFEL_STATIC_ASSERT((tfel::typetraits::IsSafelyReinterpretCastableTo<T,base>::cond));
      Copy::exe(reinterpret_cast<const base*>(&t[0]),p);
    }

    template<typename TensorType>
    typename std::enable_if<
      tfel::meta::Implements<TensorType,TensorConcept>::cond &&
      TensorTraits<TensorType>::dime == 1u,
      tensor<1u,typename ComputeBinaryResult<typename tfel::typetraits::BaseType<typename TensorTraits<TensorType>::NumType>::type,
					     typename TensorTraits<TensorType>::NumType,OpDiv>::Result>
      >::type
    invert(const TensorType& t){
      typedef typename TensorTraits<TensorType>::NumType T;
      typedef typename tfel::typetraits::BaseType<T>::type base;
      typedef typename ComputeBinaryResult<base,T,OpDiv>::Result T2;
      tensor<1u,T2> t2;
      t2(0) = base(1)/t(0);
      t2(1) = base(1)/t(1);
      t2(2) = base(1)/t(2);
      return t2;
    }
    
    template<typename TensorType>
    typename std::enable_if<
      tfel::meta::Implements<TensorType,TensorConcept>::cond &&
      TensorTraits<TensorType>::dime == 2u,
      tensor<2u,typename ComputeBinaryResult<typename tfel::typetraits::BaseType<typename TensorTraits<TensorType>::NumType>::type,
					     typename TensorTraits<TensorType>::NumType,OpDiv>::Result>
      >::type
    invert(const TensorType& t){
      typedef typename TensorTraits<TensorType>::NumType T;
      typedef typename tfel::typetraits::BaseType<T>::type base;
      typedef typename ComputeUnaryResult<typename TensorTraits<TensorType>::NumType,
					  Power<2> >::Result T2;
      typedef typename ComputeBinaryResult<base,T,OpDiv>::Result T3;
      tensor<2u,T3> t2;
      T2 det = t(0)*t(1)-t(3)*t(4);
      t2(0) = t(1)/det;
      t2(1) = t(0)/det;
      t2(3) = -t(3)/det;
      t2(4) = -t(4)/det;
      t2(2) = base(1)/t(2);
      return t2;
    }

    template<typename TensorType>
    typename std::enable_if<
      tfel::meta::Implements<TensorType,TensorConcept>::cond &&
      TensorTraits<TensorType>::dime == 3u,
      tensor<3u,typename ComputeBinaryResult<typename tfel::typetraits::BaseType<typename TensorTraits<TensorType>::NumType>::type,
    					     typename TensorTraits<TensorType>::NumType,OpDiv>::Result>
      >::type
    invert(const TensorType& t){
      typedef typename TensorTraits<TensorType>::NumType T;
      typedef typename tfel::typetraits::BaseType<T>::type base;
      typedef typename ComputeUnaryResult<typename TensorTraits<TensorType>::NumType,
					  Power<3> >::Result T2;
      typedef typename ComputeBinaryResult<base,T2,OpDiv>::Result T3;
      typedef typename ComputeBinaryResult<base,T,OpDiv>::Result  T4;
      tensor<3u,T4> t2;
      const T3 id = base(1)/det(t);
      t2(0) = (t(1)*t(2)-t(7)*t(8))*id;
      t2(1) = (t(0)*t(2)-t(5)*t(6))*id;
      t2(2) = (t(0)*t(1)-t(3)*t(4))*id;
      t2(3) = (t(5)*t(8)-t(2)*t(3))*id;
      t2(4) = (t(6)*t(7)-t(2)*t(4))*id;
      t2(5) = (t(3)*t(7)-t(1)*t(5))*id;
      t2(6) = (t(4)*t(8)-t(1)*t(6))*id;
      t2(7) = (t(4)*t(5)-t(0)*t(7))*id;
      t2(8) = (t(3)*t(6)-t(0)*t(8))*id;
      return t2;
    }

    template<typename TensorType>
    typename std::enable_if<
      tfel::meta::Implements<TensorType,TensorConcept>::cond,
      tensor<TensorTraits<TensorType>::dime,
	      typename TensorTraits<TensorType>::NumType>
      >::type
    change_basis(const TensorType& t,
		 const tmatrix<3u,3u,typename tfel::typetraits::BaseType<typename TensorTraits<TensorType>::NumType>::type>& r){
      tensor<TensorTraits<TensorType>::dime,
	      typename TensorTraits<TensorType>::NumType> nt{t};
      nt.changeBasis(r);
      return nt;
    } // end of change_basis

    template<class T>
    typename std::enable_if<
      ((tfel::meta::Implements<T,StensorConcept>::cond) &&
       (StensorTraits<T>::dime==1u)),
      tensor<1u,typename StensorTraits<T>::NumType>
      >::type
    unsyme(const T& s){
      tensor<1u,typename StensorTraits<T>::NumType> r;
      r[0] = s[0];
      r[1] = s[1];
      r[2] = s[2];
      return r;
    }

    template<class T>
    typename std::enable_if<
      ((tfel::meta::Implements<T,StensorConcept>::cond) &&
       (StensorTraits<T>::dime==2u)),
      tensor<2u,typename StensorTraits<T>::NumType>
      >::type
    unsyme(const T& s){
      using value_type = typename StensorTraits<T>::NumType;
      using base_type  = typename tfel::typetraits::BaseType<value_type>::type;
      constexpr base_type cste = base_type(1)/constexpr_fct::sqrt(base_type(2));
      tensor<2u,value_type> r;
      r[0] = s[0];
      r[1] = s[1];
      r[2] = s[2];
      r[3] = r[4] = s[3]*cste;
      return r;
    }

    template<class T>
    typename std::enable_if<
      ((tfel::meta::Implements<T,StensorConcept>::cond) &&
       (StensorTraits<T>::dime==3u)),
      tensor<3u,typename StensorTraits<T>::NumType>
      >::type
    unsyme(const T& s){
      using value_type = typename StensorTraits<T>::NumType;
      using base_type  = typename tfel::typetraits::BaseType<value_type>::type;
      constexpr base_type cste = base_type(1)/constexpr_fct::sqrt(base_type(2));
      tensor<3u,value_type> r;
      r[0] = s[0];
      r[1] = s[1];
      r[2] = s[2];
      r[3] = r[4] = s[3]*cste;
      r[5] = r[6] = s[4]*cste;
      r[7] = r[8] = s[5]*cste;
      return r;
    }

  } //end of namespace math

} // end of namespace tfel

#endif /* LIB_TFEL_TENSOR_IXX_ */

