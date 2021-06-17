/*!
 * \file   include/TFEL/Math/LU/LUDecomp.ixx
 * \brief
 * \author Thomas Helfer
 * \date   25/03/2019
 * \copyright Copyright (C) 2006-2018 CEA/DEN, EDF R&D. All rights
 * reserved.
 * This project is publicly released under either the GNU GPL Licence
 * or the CECILL-A licence. A copy of thoses licences are delivered
 * with the sources of TFEL. CEA or EDF may also distribute this
 * project under specific licensing conditions.
 */

#ifndef LIB_TFEL_MATH_LUDECOMP_IXX
#define LIB_TFEL_MATH_LUDECOMP_IXX

namespace tfel::math {

  template <typename MatrixType, typename PermutationType>
  int LUDecomp::exe(MatrixType& m,
                    PermutationType& p,
                    const numeric_type<MatrixType> eps) {
    using namespace std;
    using size_type = index_type<MatrixType>;
    using real = numeric_type<MatrixType>;
    constexpr const auto c = real(1) / 10;
    if (m.getNbRows() != m.getNbCols()) {
      throw(LUMatrixNotSquare());
    }
    if (m.getNbRows() != p.size()) {
      throw(LUUnmatchedSize());
    }
    if (m.getNbRows() == 0) {
      throw(LUInvalidMatrixSize());
    }
    const size_type n = m.getNbRows();
    int d = 1;
    for (size_type i = 0; i != n; ++i) {
      // L update (column)
      if (p.isIdentity()) {
        for (size_type j = i; j != n; ++j) {
          real v = real(0);
          for (size_type k = 0; k != i; ++k) {
            v += m(j, k) * m(k, i);
          }
          m(j, i) -= v;
        }
      } else {
        for (size_type j = i; j != n; ++j) {
          size_type pj = p(j);
          real v = real(0);
          for (size_type k = 0; k != i; ++k) {
            v += m(pj, k) * m(p(k), i);
          }
          m(pj, i) -= v;
        }
      }
      // search for pivot
      size_type piv = i;
      if (p.isIdentity()) {
        auto cmax = std::abs(m(i, i));
        for (size_type j = static_cast<size_type>(i + 1u); j != n; ++j) {
          if (std::abs(m(j, i)) > cmax) {
            cmax = std::abs(m(j, i));
            piv = j;
          }
        }
        if (piv != i) {
          if (!((std::abs(m(i, i)) > c * cmax) && (std::abs(m(i, i)) > eps))) {
            d *= -1;
            p.swap(piv, i);
          }
        }
      } else {
        auto cmax = std::abs(m(p(i), i));
        for (size_type j = static_cast<size_type>(i + 1u); j != n; ++j) {
          size_type pj = p(j);
          if (std::abs(m(pj, i)) > cmax) {
            cmax = std::abs(m(pj, i));
            piv = j;
          }
        }
        if (piv != i) {
          if (!((std::abs(m(p(i), i)) > c * cmax) &&
                (std::abs(m(p(i), i)) > eps))) {
            d *= -1;
            p.swap(piv, i);
          }
        }
      }
      if (std::abs(m(p(i), i)) < eps) {
        throw(LUNullPivot());
      }
      if (p.isIdentity()) {
        auto j = i;
        for (++j; j != n; ++j) {
          auto v = real(0);
          for (size_type k = 0; k != i; ++k) {
            v += m(i, k) * m(k, j);
          }
          m(i, j) -= v;
          m(i, j) /= m(i, i);
        }
      } else {
        size_type pi = p(i);
        // U update
        auto j = i;
        for (++j; j != n; ++j) {
          for (size_type k = 0; k != i; ++k) {
            m(pi, j) -= m(pi, k) * m(p(k), j);
          }
          m(pi, j) /= m(pi, i);
        }
      }
    }
    return d;
  }  // end of LUDecomp::exe

}  // end of namespace tfel::math

#endif /* LIB_TFEL_MATH_LUDECOMP_IXX */
