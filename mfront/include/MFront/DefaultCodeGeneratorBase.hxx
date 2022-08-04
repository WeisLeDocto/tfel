/*!
 * \file   mfront/include/MFront/DefaultCodeGeneratorBase.hxx
 * \brief    
 * \author Thomas Helfer
 * \date   03/08/2022
 * \copyright Copyright (C) 2006-2018 CEA/DEN, EDF R&D. All rights
 * reserved.
 * This project is publicly released under either the GNU GPL Licence
 * or the CECILL-A licence. A copy of thoses licences are delivered
 * with the sources of TFEL. CEA or EDF may also distribute this
 * project under specific licensing conditions.
 */

#ifndef LIB_MFRONT_DEFAULTCODEGENERATORBASE_HXX
#define LIB_MFRONT_DEFAULTCODEGENERATORBASE_HXX

#include "MFront/BehaviourCodeGeneratorBase.hxx"

namespace mfront{

  struct DefaultCodeGeneratorBase : BehaviourCodeGeneratorBase {
    /*!
     * \brief constructor
     * \param[in] f: file description
     * \param[in] d: behaviour description
     * \param[in] bim: behaviour interfaces
     */
    DefaultCodeGeneratorBase(const FileDescription&,
                             const BehaviourDescription&,
                             const BehaviourInterfaceMap&);
    //! \brief destructor
    ~DefaultCodeGeneratorBase() override;

   protected:
    void writeBehaviourParserSpecificIncludes(std::ostream&) const override;
    void writeBehaviourLocalVariablesInitialisation(
        std::ostream&, const Hypothesis) const override;
  };  // end of DefaultCodeGeneratorBase

} // end of namespace mfront

#endif /* LIB_MFRONT_DEFAULTCODEGENERATORBASE_HXX */
