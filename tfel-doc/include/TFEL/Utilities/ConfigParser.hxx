/*!
 * \file  tfel-doc/include/TFEL/Utilities/ConfigParser.hxx
 * \brief
 * \author Thomas Helfer
 * \brief 03 mai 2011
 * \copyright Copyright (C) 2006-2018 CEA/DEN, EDF R&D. All rights
 * reserved.
 * This project is publicly released under either the GNU GPL Licence
 * or the CECILL-A licence. A copy of thoses licences are delivered
 * with the sources of TFEL. CEA or EDF may also distribute this
 * project under specific licensing conditions.
 */

#ifndef LIB_TFEL_UTILITIES_CONFIGPARSER_HXX
#define LIB_TFEL_UTILITIES_CONFIGPARSER_HXX

#include <map>

#include "TFEL/Utilities/ParserBase.hxx"

namespace tfel {

  namespace utilities {

    struct ConfigParser : public ParserBase {
      /*!
       * \param m : configuration to be read
       * \param f : file name
       */
      void execute(std::map<std::string, std::map<std::string, std::string>>&,
                   const std::string&);
      //! desctructor
      virtual ~ConfigParser() noexcept;
    };  // end of struct ConfigParser

  }  // end of namespace utilities

}  // end of namespace tfel

#endif /* LIB_TFEL_UTILITIES_CONFIGPARSER_H */
