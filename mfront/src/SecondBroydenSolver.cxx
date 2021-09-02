/*!
 * \file  mfront/src/SecondBroydenSolver.cxx
 * \brief
 * \author Thomas Helfer
 * \brief 22 août 2014
 * \copyright Copyright (C) 2006-2018 CEA/DEN, EDF R&D. All rights
 * reserved.
 * This project is publicly released under either the GNU GPL Licence
 * or the CECILL-A licence. A copy of thoses licences are delivered
 * with the sources of TFEL. CEA or EDF may also distribute this
 * project under specific licensing conditions.
 */

#include <ostream>
#include "MFront/MFrontDebugMode.hxx"
#include "MFront/BehaviourDescription.hxx"
#include "MFront/PerformanceProfiling.hxx"
#include "MFront/SecondBroydenSolver.hxx"

namespace mfront {

  std::vector<std::string> SecondBroydenSolver::getReservedNames() const {
    return {};
  }  // end of getReservedNames

  std::vector<std::string> SecondBroydenSolver::getSpecificHeaders() const {
    return {"TFEL/Math/TinyBroyden2Solver.hxx"};
  }  // end of getSpecificHeaders

  std::string SecondBroydenSolver::getExternalAlgorithmClassName(
      const BehaviourDescription& bd, const Hypothesis h) const {
    const auto hn = [&h]() -> std::string {
      if (h == tfel::material::ModellingHypothesis::UNDEFINEDHYPOTHESIS) {
        return "hypothesis";
      }
      return "ModellingHypothesis::" +
             tfel::material::ModellingHypothesis::toUpperCaseString(h);
    }();
    const auto n =
        mfront::getTypeSize(bd.getBehaviourData(h).getIntegrationVariables())
            .asString({"ModellingHypothesisToSpaceDimension<" + hn + ">::value",
                       "ModellingHypothesisToStensorSize<" + hn + ">::value",
                       "ModellingHypothesisToTensorSize<" + hn + ">::value"});
    const auto cn =
        bd.useQt() ? bd.getClassName() + "<" + hn + ", NumericType, true>"
                   : bd.getClassName() + "<" + hn + ", NumericType, false>";
    return "tfel::math::TinyBroyden2Solver<" + n + ", NumericType, " + cn + ">";
  }  // end of getExternalAlgorithmClassName

  bool SecondBroydenSolver::usesJacobian() const {
    return false;
  }  // end of usesJacobian

  bool SecondBroydenSolver::usesJacobianInvert() const {
    return true;
  }  // end of usesJacobianInvert

  bool SecondBroydenSolver::allowsJacobianInitialisation() const {
    return false;
  }  // end of allowsJacobianInitialisation

  bool SecondBroydenSolver::allowsJacobianInvertInitialisation() const {
    return true;
  }  // end of allowsJacobianInvertInitialisation

  bool SecondBroydenSolver::
      requiresJacobianToBeReinitialisedToIdentityAtEachIterations() const {
    return false;
  }  // end of allowsJacobianInitialisation

  bool SecondBroydenSolver::requiresNumericalJacobian() const { return false; }

  std::pair<bool, SecondBroydenSolver::tokens_iterator>
  SecondBroydenSolver::treatSpecificKeywords(BehaviourDescription&,
                                             const std::string&,
                                             const tokens_iterator p,
                                             const tokens_iterator) {
    return {false, p};
  }  // end of treatSpecificKeywords

  void SecondBroydenSolver::completeVariableDeclaration(
      BehaviourDescription&) const {}  // end of completeVariableDeclaration

  void SecondBroydenSolver::writeSpecificMembers(std::ostream&,
                                                 const BehaviourDescription&,
                                                 const Hypothesis) const {
  }  // end of writeSpecificMembers

  void SecondBroydenSolver::writeSpecificInitializeMethodPart(
      std::ostream& out,
      const BehaviourDescription& mb,
      const Hypothesis h) const {
    const auto& d = mb.getBehaviourData(h);
    const auto n = d.getIntegrationVariables().getTypeSize();
    if (mb.hasCode(h, BehaviourData::InitializeJacobianInvert)) {
      out << mb.getCode(h, BehaviourData::InitializeJacobianInvert);
    } else {
      out << "// setting the inverse of jacobian to identity\n"
          << "std::fill(this->inv_jacobian.begin(),this->inv_jacobian.end(),"
             "real(0));\n"
          << "for(unsigned short idx = 0; idx!= " << n << ";++idx){\n"
          << "this->inv_jacobian(idx,idx)= real(1);\n"
          << "}\n";
    }
  }  // end of writeSpecificInitializeMethodPart

  SecondBroydenSolver::~SecondBroydenSolver() = default;

}  // end of namespace mfront
