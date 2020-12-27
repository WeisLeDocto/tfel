/*!
 * \file   include/TFEL/Math/T2toST2/T2toST2ConceptOperations.hxx
 * \brief  This file implements operations that can be applied to t2tost2.
 * \author Thomas Helfer
 * \date   19 November 2013
 * \copyright Copyright (C) 2006-2018 CEA/DEN, EDF R&D. All rights
 * reserved.
 * This project is publicly released under either the GNU GPL Licence
 * or the CECILL-A licence. A copy of thoses licences are delivered
 * with the sources of TFEL. CEA or EDF may also distribute this
 * project under specific licensing conditions.
 */

#ifndef LIB_TFEL_T2TOST2_CONCEPT_OPERATIONS_HXX
#define LIB_TFEL_T2TOST2_CONCEPT_OPERATIONS_HXX

#include <cmath>
#include "TFEL/Config/TFELConfig.hxx"
#include "TFEL/Metaprogramming/Implements.hxx"
#include "TFEL/Metaprogramming/HasRandomAccessConstIterator.hxx"
#include "TFEL/TypeTraits/IsScalar.hxx"
#include "TFEL/Math/General/ResultType.hxx"
#include "TFEL/Math/General/BasicOperations.hxx"
#include "TFEL/Math/General/ComputeObjectTag.hxx"
#include "TFEL/Math/General/ComputeBinaryResult.hxx"
#include "TFEL/Math/General/ComputeUnaryResult.hxx"
#include "TFEL/Math/Stensor/StensorConcept.hxx"
#include "TFEL/Math/ExpressionTemplates/Expr.hxx"
#include "TFEL/Math/ExpressionTemplates/StandardOperations.hxx"
#include "TFEL/Math/T2toT2/T2toT2Concept.hxx"
#include "TFEL/Math/T2toST2/StensorT2toST2ProductExpr.hxx"
#include "TFEL/Math/T2toST2/T2toST2TensorProductExpr.hxx"
#include "TFEL/Math/T2toST2/ST2toST2T2toST2ProductExpr.hxx"
#include "TFEL/Math/T2toST2/T2toST2T2toT2ProductExpr.hxx"

namespace tfel::math {

  template <typename T_type, typename Operation>
  struct T2toST2Traits<Expr<T_type, Operation>> {
    using NumType = typename T2toST2Traits<T_type>::NumType;
    static constexpr unsigned short dime = T2toST2Traits<T_type>::dime;
  };

  /*
   * Partial Specialisation of ComputeBinaryResult_ for t2tost2's operation
   */
  template <typename A, typename B, typename Op>
  class ComputeBinaryResult_<T2toST2Tag, T2toST2Tag, A, B, Op> {
    struct DummyHandle {};
    //! \brief a simple alias
    using T2toST2TypeA = EvaluationResult<A>;
    //! \brief a simple alias
    using T2toST2TypeB = EvaluationResult<B>;

   public:
    using Result = typename ResultType<T2toST2TypeA, T2toST2TypeB, Op>::type;
    using Handle = std::conditional_t<tfel::typetraits::IsInvalid<Result>::cond,
                                      DummyHandle,
                                      Expr<Result, BinaryOperation<A, B, Op>>>;
  };

  /*!
   * Partial Specialisation of ComputeBinaryResult_ for the
   * multiplication of object of type st2tost2 by object of type
   * t2tost2.
   */
  template <typename A, typename B>
  class ComputeBinaryResult_<ST2toST2Tag, T2toST2Tag, A, B, OpMult> {
    struct DummyHandle {};
    using ST2toST2TypeA = EvaluationResult<A>;
    using T2toST2TypeB = EvaluationResult<B>;

   public:
    using Result =
        typename ResultType<ST2toST2TypeA, T2toST2TypeB, OpMult>::type;
    using Handle = std::conditional_t<
        tfel::typetraits::IsInvalid<Result>::cond,
        DummyHandle,
        Expr<Result, ST2toST2T2toST2ProductExpr<T2toST2Traits<Result>::dime>>>;
  };

  /*
   * Partial Specialisation of ComputeBinaryResult_ for t2tost2-t2tot2
   * operations
   */
  template <typename A, typename B>
  class ComputeBinaryResult_<T2toST2Tag, T2toT2Tag, A, B, OpMult> {
    struct DummyHandle {};
    using T2toST2TypeA = EvaluationResult<A>;
    using T2toT2TypeB = EvaluationResult<B>;

   public:
    using Result = typename ResultType<T2toST2TypeA, T2toT2TypeB, OpMult>::type;
    using Handle = std::conditional_t<
        tfel::typetraits::IsInvalid<Result>::cond,
        DummyHandle,
        Expr<Result, T2toST2T2toT2ProductExpr<T2toST2Traits<Result>::dime>>>;
  };

  /*!
   * Partial Specialisation of ComputeBinaryResult_ for stensor's operation
   */
  template <typename A, typename B>
  class ComputeBinaryResult_<StensorTag, TensorTag, A, B, OpDiadicProduct> {
    struct DummyHandle {};
    //! \brief a simple alias
    using StensorTypeA = EvaluationResult<A>;
    using TensorTypeB = EvaluationResult<B>;

   public:
    using Result =
        typename ResultType<StensorTypeA, TensorTypeB, OpDiadicProduct>::type;
    using Handle =
        std::conditional_t<tfel::typetraits::IsInvalid<Result>::cond,
                           DummyHandle,
                           Expr<Result, DiadicProductOperation<A, B>>>;
  };

  /*
   * Partial Specialisation of ComputeBinaryResult_ for T2toST2-Tensor
   * operations
   */
  template <typename A, typename B>
  class ComputeBinaryResult_<T2toST2Tag, TensorTag, A, B, OpMult> {
    struct DummyHandle {};
    using T2toST2TypeA = EvaluationResult<A>;
    using TensorTypeB = EvaluationResult<B>;

   public:
    using Result = typename ResultType<T2toST2TypeA, TensorTypeB, OpMult>::type;
    using Handle = std::conditional_t<
        tfel::typetraits::IsInvalid<Result>::cond,
        DummyHandle,
        Expr<Result, T2toST2TensorProductExpr<StensorTraits<Result>::dime>>>;
  };

  /*
   * Partial Specialisation of ComputeBinaryResult_ for Stensor-T2toST2
   * operations
   */
  template <typename A, typename B>
  class ComputeBinaryResult_<StensorTag, T2toST2Tag, A, B, OpMult> {
    struct DummyHandle {};
    using StensorTypeA = EvaluationResult<A>;
    using T2toST2TypeB = EvaluationResult<B>;

   public:
    using Result =
        typename ResultType<StensorTypeA, T2toST2TypeB, OpMult>::type;
    using Handle = std::conditional_t<
        tfel::typetraits::IsInvalid<Result>::cond,
        DummyHandle,
        Expr<Result, StensorT2toST2ProductExpr<TensorTraits<Result>::dime>>>;
  };

  /*
   * Partial Specialisation of ComputeBinaryResult_ for scalar-t2tost2
   * operations
   */
  template <typename A, typename B, typename Op>
  class ComputeBinaryResult_<ScalarTag, T2toST2Tag, A, B, Op> {
    struct DummyHandle {};
    typedef std::decay_t<A> ScalarA;
    using T2toST2TypeB = EvaluationResult<B>;

   public:
    using Result = typename ResultType<ScalarA, T2toST2TypeB, Op>::type;
    using Handle =
        std::conditional_t<tfel::typetraits::IsInvalid<Result>::cond,
                           DummyHandle,
                           Expr<Result, ScalarObjectOperation<A, B, Op>>>;
  };

  /*
   * Partial Specialisation of ComputeBinaryResult_ for t2tost2-scalar
   * operations
   */
  template <typename A, typename B, typename Op>
  class ComputeBinaryResult_<T2toST2Tag, ScalarTag, A, B, Op> {
    struct DummyHandle {};
    using T2toST2TypeA = EvaluationResult<A>;

   public:
    using Result = typename ResultType<T2toST2TypeA, B, Op>::type;
    using Handle =
        std::conditional_t<tfel::typetraits::IsInvalid<Result>::cond,
                           DummyHandle,
                           Expr<Result, ObjectScalarOperation<A, B, Op>>>;
  };

  /*
   * Partial Specialisation of ComputeUnaryResult_ for t2tost2s
   */
  template <typename A>
  struct ComputeUnaryResult_<T2toST2Tag, UnaryOperatorTag, A, OpNeg> {
    struct DummyHandle {};
    using T2toST2TypeA = EvaluationResult<A>;

   public:
    using Result = typename UnaryResultType<T2toST2TypeA, OpNeg>::type;
    typedef
        typename std::conditional<tfel::typetraits::IsInvalid<Result>::cond,
                                  DummyHandle,
                                  Expr<Result, UnaryOperation<A, OpNeg>>>::type
            Handle;
  };

  template <typename T1, typename T2>
  TFEL_MATH_INLINE typename std::enable_if<
      tfel::meta::Implements<T1, StensorConcept>::cond &&
          tfel::meta::Implements<T2, T2toST2Concept>::cond &&
          !tfel::typetraits::IsInvalid<
              typename ComputeBinaryResult<T1, T2, OpMult>::Result>::cond,
      typename ComputeBinaryResult<T1, T2, OpMult>::Handle>::type
  operator|(const T1& a, const T2& b) {
    typedef typename ComputeBinaryResult<T1, T2, OpMult>::Handle Handle;
    return Handle(a, b);
  }

}  // end of namespace tfel::math

#endif /* LIB_TFEL_T2TOST2_CONCEPT_OPERATIONS_HXX */
