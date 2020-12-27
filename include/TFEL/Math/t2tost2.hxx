/*!
 * \file   include/TFEL/Math/t2tost2.hxx
 * \brief
 * \author Thomas Helfer
 * \date   19 November 2013
 * \copyright Copyright (C) 2006-2018 CEA/DEN, EDF R&D. All rights
 * reserved.
 * This project is publicly released under either the GNU GPL Licence
 * or the CECILL-A licence. A copy of thoses licences are delivered
 * with the sources of TFEL. CEA or EDF may also distribute this
 * project under specific licensing conditions.
 */

#ifndef LIB_TFEL_MATH_T2TOST2_HXX
#define LIB_TFEL_MATH_T2TOST2_HXX

#include <cstddef>

#include "TFEL/Config/TFELConfig.hxx"
#include "TFEL/TypeTraits/IsScalar.hxx"
#include "TFEL/TypeTraits/BaseType.hxx"
#include "TFEL/TypeTraits/IsInvalid.hxx"
#include "TFEL/TypeTraits/IsAssignableTo.hxx"
#include "TFEL/TypeTraits/IsSafelyReinterpretCastableTo.hxx"
#include "TFEL/Math/fsarray.hxx"
#include "TFEL/Math/tensor.hxx"
#include "TFEL/Math/stensor.hxx"
#include "TFEL/Math/General/BasicOperations.hxx"
#include "TFEL/Math/General/EmptyRunTimeProperties.hxx"
#include "TFEL/Math/Forward/t2tost2.hxx"
#include "TFEL/Math/Stensor/StensorSizeToDime.hxx"
#include "TFEL/Math/Tensor/TensorSizeToDime.hxx"
#include "TFEL/Math/Tensor/TensorConcept.hxx"
#include "TFEL/Math/T2toT2/T2toT2Concept.hxx"
#include "TFEL/Math/T2toST2/T2toST2Concept.hxx"
#include "TFEL/Math/T2toST2/T2toST2ConceptOperations.hxx"

namespace tfel::math {

  //! forward declaration
  template <unsigned short>
  struct RightCauchyGreenTensorDerivativeExpr;

  //! forward declaration
  template <unsigned short>
  struct LeftCauchyGreenTensorDerivativeExpr;

  /*
   * Partial specialisation for t2tost2
   */
  template <unsigned short N, typename T>
  struct T2toST2Traits<t2tost2<N, T>> {
    typedef T NumType;
    typedef unsigned short IndexType;
    static constexpr unsigned short dime = N;
  };

  /*!
   * \brief partial specialisation of the `DerivativeTypeDispatcher`
   * metafunction.
   */
  template <typename StensorType1, typename TensorType2>
  struct DerivativeTypeDispatcher<StensorTag,
                                  TensorTag,
                                  StensorType1,
                                  TensorType2> {
    static_assert(tfel::meta::Implements<StensorType1, StensorConcept>::cond,
                  "template argument StensorType1 is not a symmetric tensor");
    static_assert(tfel::meta::Implements<TensorType2, TensorConcept>::cond,
                  "template argument TensorType2 is not a tensor");
    static_assert(StensorTraits<StensorType1>::dime ==
                      TensorTraits<TensorType2>::dime,
                  "symmetric tensor types don't have the same dimension");
    static_assert(
        tfel::typetraits::IsScalar<StensorNumType<StensorType1>>::cond,
        "the first tensor type does not hold a scalar");
    static_assert(tfel::typetraits::IsScalar<TensorNumType<TensorType2>>::cond,
                  "the second tensor type does not hold a scalar");
    //! \brief result
    using type = t2tost2<StensorTraits<StensorType1>::dime,
                         derivative_type<StensorNumType<StensorType1>,
                                         TensorNumType<TensorType2>>>;
  };  // end of struct DerivativeTypeDispatcher

  /*!
   * \brief a base for stensor or classes acting like stensor.
   * \param Child : child class
   * \param N     : spatial dimension
   * \param T     : numerical type
   */
  template <typename Child>
  struct t2tost2_base {
    /*!
     * Assignement operator
     */
    template <typename T2toST2Type>
    TFEL_MATH_INLINE std::enable_if_t<
        tfel::meta::Implements<T2toST2Type, tfel::math::T2toST2Concept>::cond &&
            T2toST2Traits<Child>::dime == T2toST2Traits<T2toST2Type>::dime &&
            tfel::typetraits::IsAssignableTo<
                typename T2toST2Traits<T2toST2Type>::NumType,
                typename T2toST2Traits<Child>::NumType>::cond,
        Child&>
    operator=(const T2toST2Type&);
    //! Assignement operator
    template <typename T2toST2Type>
    TFEL_MATH_INLINE std::enable_if_t<
        tfel::meta::Implements<T2toST2Type, tfel::math::T2toST2Concept>::cond &&
            T2toST2Traits<Child>::dime == T2toST2Traits<T2toST2Type>::dime &&
            tfel::typetraits::IsAssignableTo<
                typename T2toST2Traits<T2toST2Type>::NumType,
                typename T2toST2Traits<Child>::NumType>::cond,
        Child&>
    operator+=(const T2toST2Type&);
    //! Assignement operator
    template <typename T2toST2Type>
    TFEL_MATH_INLINE std::enable_if_t<
        tfel::meta::Implements<T2toST2Type, tfel::math::T2toST2Concept>::cond &&
            T2toST2Traits<Child>::dime == T2toST2Traits<T2toST2Type>::dime &&
            tfel::typetraits::IsAssignableTo<
                typename T2toST2Traits<T2toST2Type>::NumType,
                typename T2toST2Traits<Child>::NumType>::cond,
        Child&>
    operator-=(const T2toST2Type&);
    /*!
     * operator*=
     */
    template <typename T2>
    TFEL_MATH_INLINE std::enable_if_t<
        tfel::typetraits::IsScalar<T2>::cond &&
            std::is_same<
                typename ResultType<typename T2toST2Traits<Child>::NumType,
                                    T2,
                                    OpMult>::type,
                typename T2toST2Traits<Child>::NumType>::value,
        Child&>
    operator*=(const T2);
    /*!
     * operator/=
     */
    template <typename T2>
    TFEL_MATH_INLINE std::enable_if_t<
        tfel::typetraits::IsScalar<T2>::cond &&
            std::is_same<
                typename ResultType<typename T2toST2Traits<Child>::NumType,
                                    T2,
                                    OpDiv>::type,
                typename T2toST2Traits<Child>::NumType>::value,
        Child&>
    operator/=(const T2);
  };  // end of struct t2tost2_base

  template <unsigned short N, typename T>
  struct t2tost2
      : public T2toST2Concept<t2tost2<N, T>>,
        public fsarray<StensorDimeToSize<N>::value * TensorDimeToSize<N>::value,
                       T>,
        public t2tost2_base<t2tost2<N, T>> {
    /*!
     * \param[in] F : deformation gradient
     * \return the derivative of the Cauchy right symmetric tensor
     * with respect to the deformation gradient
     */
    template <typename TensorType>
    static TFEL_MATH_INLINE std::enable_if_t<
        tfel::meta::Implements<TensorType, TensorConcept>::cond &&
            TensorTraits<TensorType>::dime == N &&
            tfel::typetraits::IsAssignableTo<
                typename TensorTraits<TensorType>::NumType,
                T>::cond,
        Expr<t2tost2<N, T>, RightCauchyGreenTensorDerivativeExpr<N>>>
    dCdF(const TensorType&);
    /*!
     * \param[in] F : deformation gradient
     * \return the derivative of the Cauchy left symmetric tensor
     * with respect to the deformation gradient
     */
    template <typename TensorType>
    static TFEL_MATH_INLINE std::enable_if_t<
        tfel::meta::Implements<TensorType, TensorConcept>::cond &&
            TensorTraits<TensorType>::dime == N &&
            tfel::typetraits::IsAssignableTo<
                typename TensorTraits<TensorType>::NumType,
                T>::cond,
        Expr<t2tost2<N, T>, LeftCauchyGreenTensorDerivativeExpr<N>>>
    dBdF(const TensorType&);
    /*!
     * This is a StensorConcept requirement.
     */
    typedef EmptyRunTimeProperties RunTimeProperties;
    /*!
     * \brief Default Constructor
     */
    TFEL_MATH_INLINE explicit constexpr t2tost2();
    /*!
     * \brief Default Constructor
     * \param T, value used to initialise the components of the t2tost2
     */
    template <typename T2,
              std::enable_if_t<tfel::typetraits::IsAssignableTo<T2, T>::cond,
                               bool> = true>
    TFEL_MATH_INLINE constexpr explicit t2tost2(const T2&);
    /*!
     * \brief default constructor
     * \param[in] init : values used to initialise the components of the
     * st2tost2
     */
    template <typename T2,
              std::enable_if_t<tfel::typetraits::IsAssignableTo<T2, T>::cond,
                               bool> = true>
    TFEL_MATH_INLINE constexpr t2tost2(const std::initializer_list<T2>&);
    /*!
     * \brief Copy Constructor
     */
    TFEL_MATH_INLINE constexpr t2tost2(const t2tost2<N, T>&);
    // Copy Constructor
    template <typename T2, typename Op>
    TFEL_MATH_INLINE t2tost2(const Expr<t2tost2<N, T2>, Op>&);
    //! assignement operator
    TFEL_MATH_INLINE t2tost2& operator=(const t2tost2&);
    /*!
     * Import values
     */
    template <typename T2>
    TFEL_MATH_INLINE2 std::enable_if_t<
        tfel::typetraits::IsSafelyReinterpretCastableTo<
            T2,
            typename tfel::typetraits::BaseType<T>::type>::cond,
        void>
    import(const T2* const);
    /*!
     * Assignement operator
     */
    using t2tost2_base<t2tost2>::operator=;
    //! access operator
    TFEL_MATH_INLINE constexpr const T& operator()(const unsigned short,
                                                   const unsigned short) const;
    //! access operator
    TFEL_MATH_INLINE T& operator()(const unsigned short, const unsigned short);
    /*!
     * Return the RunTimeProperties of the tvector
     * \return tvector::RunTimeProperties
     */
    TFEL_MATH_INLINE RunTimeProperties getRunTimeProperties() const;

    template <typename InputIterator>
    TFEL_MATH_INLINE2 void copy(const InputIterator src);

  };  // end of struct t2tost2

  /*!
   * \return change the basis of a 1D t2tost2
   * \param[in] s: t2tost2
   * \param[in] r: rotation matrix
   */
  template <typename T2toST2Type>
  std::enable_if_t<
      ((tfel::meta::Implements<T2toST2Type, T2toST2Concept>::cond) &&
       (T2toST2Traits<T2toST2Type>::dime == 1u)),
      t2tost2<1u, T2toST2NumType<T2toST2Type>>>
  change_basis(const T2toST2Type&,
               const rotation_matrix<T2toST2NumType<T2toST2Type>>&);
  /*!
   * \return change the basis of a 2D or 3D t2tost2
   * \param[in] s: t2tost2
   * \param[in] r: rotation matrix
   */
  template <typename T2toST2Type>
  std::enable_if_t<
      ((tfel::meta::Implements<T2toST2Type, T2toST2Concept>::cond) &&
       (T2toST2Traits<T2toST2Type>::dime != 1u)),
      t2tost2<T2toST2Traits<T2toST2Type>::dime, T2toST2NumType<T2toST2Type>>>
  change_basis(const T2toST2Type& s,
               const rotation_matrix<T2toST2NumType<T2toST2Type>>&);

  /*!
   * convert a t2tot2 tensor to a t2tost2
   */
  template <typename T2toT2Type>
  TFEL_MATH_INLINE std::enable_if_t<
      ((T2toT2Traits<T2toT2Type>::dime == 1u) &&
       tfel::meta::Implements<T2toT2Type, tfel::math::T2toT2Concept>::cond),
      t2tost2<1u, typename T2toT2Traits<T2toT2Type>::NumType>>
  convertToT2toST2(const T2toT2Type&);

  /*!
   * convert a t2tot2 tensor to a t2tost2
   */
  template <typename T2toT2Type>
  TFEL_MATH_INLINE std::enable_if_t<
      ((T2toT2Traits<T2toT2Type>::dime == 2u) &&
       tfel::meta::Implements<T2toT2Type, tfel::math::T2toT2Concept>::cond),
      t2tost2<2u, typename T2toT2Traits<T2toT2Type>::NumType>>
  convertToT2toST2(const T2toT2Type&);

  /*!
   * convert a t2tot2 tensor to a t2tost2
   */
  template <typename T2toT2Type>
  TFEL_MATH_INLINE std::enable_if_t<
      ((T2toT2Traits<T2toT2Type>::dime == 3u) &&
       tfel::meta::Implements<T2toT2Type, tfel::math::T2toT2Concept>::cond),
      t2tost2<3u, typename T2toT2Traits<T2toT2Type>::NumType>>
  convertToT2toST2(const T2toT2Type&);

  /*!
   * \return compute the "derivative" of the rate of deformation
   * \delta D = dD_dF:\delta F with \delta D = ((delta F).F^{-1}+F^{-T}.(delta
   * F)^{T})/2
   * \param[in] F : deformation gradient
   */
  template <typename TensorType>
  TFEL_MATH_INLINE2 std::enable_if_t<
      (tfel::meta::Implements<TensorType, TensorConcept>::cond) &&
          (TensorTraits<TensorType>::dime == 1u),
      t2tost2<1u, typename TensorTraits<TensorType>::NumType>>
  computeRateOfDeformationDerivative(const TensorType&);
  /*!
   * \return compute the derivative of the rate of deformation
   * \param[in] F : deformation gradient
   */
  template <typename TensorType>
  TFEL_MATH_INLINE2 std::enable_if_t<
      (tfel::meta::Implements<TensorType, TensorConcept>::cond) &&
          (TensorTraits<TensorType>::dime == 2u),
      t2tost2<2u, typename TensorTraits<TensorType>::NumType>>
  computeRateOfDeformationDerivative(const TensorType&);
  /*!
   * \return compute the derivative of the rate of deformation
   * \param[in] F : deformation gradient
   */
  template <typename TensorType>
  TFEL_MATH_INLINE2 std::enable_if_t<
      (tfel::meta::Implements<TensorType, TensorConcept>::cond) &&
          (TensorTraits<TensorType>::dime == 1u),
      t2tost2<1u, typename TensorTraits<TensorType>::NumType>>
  computeRateOfDeformationDerivative(const TensorType&);
  /*!
   * \brief compute the Cauchy stress derivative from the Kirchhoff stress
   * derivative
   * \param[in]  dt: Kirchhoff stress derivative
   * \param[in]  s:  Cauchy stress
   * \param[in]  F:  deformation gradient
   */
  template <typename T2toST2Type, typename StensorType, typename TensorType>
  std::enable_if_t<
      tfel::meta::Implements<T2toST2Type, T2toST2Concept>::cond &&
          tfel::meta::Implements<StensorType, StensorConcept>::cond &&
          tfel::meta::Implements<TensorType, TensorConcept>::cond &&
          T2toST2Traits<T2toST2Type>::dime ==
              StensorTraits<StensorType>::dime &&
          T2toST2Traits<T2toST2Type>::dime == TensorTraits<TensorType>::dime &&
          tfel::typetraits::IsFundamentalNumericType<
              typename TensorTraits<TensorType>::NumType>::cond,
      t2tost2<T2toST2Traits<T2toST2Type>::dime,
              typename ComputeBinaryResult<
                  typename T2toST2Traits<T2toST2Type>::NumType,
                  typename StensorTraits<StensorType>::NumType,
                  OpPlus>::Result>>
  computeCauchyStressDerivativeFromKirchhoffStressDerivative(const T2toST2Type&,
                                                             const StensorType&,
                                                             const TensorType&);
  /*!
   * \brief compute the Cauchy stress derivative from the Kirchhoff stress
   * derivative
   * \param[in]  dt: Kirchhoff stress derivative
   * \param[in]  s:  Cauchy stress
   * \param[in]  F:  deformation gradient
   */
  template <typename T2toST2Type, typename StensorType, typename TensorType>
  std::enable_if_t<
      tfel::meta::Implements<T2toST2Type, T2toST2Concept>::cond &&
          tfel::meta::Implements<StensorType, StensorConcept>::cond &&
          tfel::meta::Implements<TensorType, TensorConcept>::cond &&
          T2toST2Traits<T2toST2Type>::dime ==
              StensorTraits<StensorType>::dime &&
          T2toST2Traits<T2toST2Type>::dime == TensorTraits<TensorType>::dime &&
          tfel::typetraits::IsFundamentalNumericType<
              typename TensorTraits<TensorType>::NumType>::cond,
      t2tost2<T2toST2Traits<T2toST2Type>::dime,
              typename ComputeBinaryResult<
                  typename T2toST2Traits<T2toST2Type>::NumType,
                  typename StensorTraits<StensorType>::NumType,
                  OpPlus>::Result>>
  computeKirchhoffStressDerivativeFromCauchyStressDerivative(const T2toST2Type&,
                                                             const StensorType&,
                                                             const TensorType&);

}  // end of namespace tfel::math

namespace tfel::typetraits {

  template <unsigned short N, typename T2, typename T>
  struct IsAssignableTo<tfel::math::t2tost2<N, T2>, tfel::math::t2tost2<N, T>> {
    /*!
     *  Result
     */
    static constexpr bool cond = IsAssignableTo<T2, T>::cond;
  };

}  // end of namespace tfel::typetraits

#include "TFEL/Math/T2toST2/t2tost2.ixx"
#include "TFEL/Math/T2toST2/t2tost2ResultType.hxx"

#endif /* LIB_TFEL_MATH_T2TOST2_HXX */
