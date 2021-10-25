/*!
 * \file tfel-check/src/NoInterpolation.cxx
 *
 *  Created on: 14 mai 2013
 *      Author: rp238441
 * \copyright Copyright (C) 2006-2018 CEA/DEN, EDF R&D. All rights
 * reserved.
 * This project is publicly released under either the GNU GPL Licence
 * or the CECILL-A licence. A copy of thoses licences are delivered
 * with the sources of TFEL. CEA or EDF may also distribute this
 * project under specific licensing conditions.
 */

#include "TFEL/Check/NoInterpolation.hxx"

namespace tfel {

  namespace check {

    NoInterpolation::NoInterpolation() = default;
    NoInterpolation::NoInterpolation(NoInterpolation&&) = default;
    NoInterpolation::NoInterpolation(const NoInterpolation&) = default;
    NoInterpolation& NoInterpolation::operator=(NoInterpolation&&) = default;
    NoInterpolation& NoInterpolation::operator=(const NoInterpolation&) =
        default;
    NoInterpolation::~NoInterpolation() = default;

    void NoInterpolation::interpolate(const std::vector<double>&,
                                      const std::vector<double>&) {}

    double NoInterpolation::getValue(const double) const { return 0; }

    std::string NoInterpolation::getType() const { return "none"; }

    bool NoInterpolation::isConform() const { return false; }

    std::shared_ptr<Interpolation> NoInterpolation::clone() const {
      return std::make_shared<NoInterpolation>(*this);
    }

  }  // end of namespace check

}  // end of namespace tfel
