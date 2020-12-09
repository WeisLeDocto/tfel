/*!
 * \file   include/MFront/BehaviourBrick/PorosityEvolutionAlgorithm.hxx
 * \brief    
 * \author Thomas Helfer
 * \date   21/07/2020
 * \copyright Copyright (C) 2006-2018 CEA/DEN, EDF R&D. All rights
 * reserved.
 * This project is publicly released under either the GNU GPL Licence
 * or the CECILL-A licence. A copy of thoses licences are delivered
 * with the sources of TFEL. CEA or EDF may also distribute this
 * project under specific licensing conditions.
 */

#ifndef LIB_MFRONT_BBRICK_POROSITYEVOLUTIONALGORITHM_HXX
#define LIB_MFRONT_BBRICK_POROSITYEVOLUTIONALGORITHM_HXX

namespace mfront {

  namespace bbrick {

    /*!
     * \brief Algorithm used to handle the porosity evolution
     */
    enum struct PorosityEvolutionAlgorithm {
      STANDARD_IMPLICIT_SCHEME,  //!< \brief monolithich approach
      STAGGERED_SCHEME           //!< \brief staggered approach
    };  // end of enum struct PorosityEvolutionAlgorithm

  }  // end of namespace bbrick

} // end of namespace mfront

#endif /* LIB_MFRONT_BBRICK_POROSITYEVOLUTIONALGORITHM_HXX */