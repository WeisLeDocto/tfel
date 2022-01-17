/*!
 * \file   Data.hxx
 * \brief
 * \author Thomas Helfer
 * \date   12 sept. 2016
 * \copyright Copyright (C) 2006-2018 CEA/DEN, EDF R&D. All rights
 * reserved.
 * This project is publicly released under either the GNU GPL Licence
 * or the CECILL-A licence. A copy of thoses licences are delivered
 * with the sources of TFEL. CEA or EDF may also distribute this
 * project under specific licensing conditions.
 */

#ifndef LIB_TFEL_UTILITIES_DATA_HXX
#define LIB_TFEL_UTILITIES_DATA_HXX

#include <map>
#include <string>
#include <vector>
#include <utility>
#include <functional>
#include <string_view>
#include "TFEL/Config/TFELConfig.hxx"
#include "TFEL/Utilities/GenTypeBase.hxx"
#include "TFEL/Utilities/CxxTokenizer.hxx"

namespace tfel::utilities {

  // forward declaration
  struct Data;
  //! \brief a simple alias
  using DataMap = std::map<std::string, Data, std::less<>>;

  /*!
   * \brief a structure in charge of containing a complex data structure.
   */
  struct TFELUTILITIES_VISIBILITY_EXPORT DataStructure {
    //! default constructor
    DataStructure();
    //! move constructor
    DataStructure(DataStructure&&);
    //! copy constructor
    DataStructure(const DataStructure&);
    //! move assignement
    DataStructure& operator=(DataStructure&&);
    //! assignement
    DataStructure& operator=(const DataStructure&);
    //! destructor
    ~DataStructure();
    //! name of the structure
    std::string name;
    //! name of the structure
    DataMap data;
  };  // end of struct DataStructure

  struct TFELUTILITIES_VISIBILITY_EXPORT DataParsingOptions {
    //! default constructor
    DataParsingOptions();
    //! move constructor
    DataParsingOptions(DataParsingOptions&&);
    //! copy constructor
    DataParsingOptions(const DataParsingOptions&);
    //! move assignement
    DataParsingOptions& operator=(DataParsingOptions&&);
    //! assignement
    DataParsingOptions& operator=(const DataParsingOptions&);
    //! destructor
    ~DataParsingOptions();
    //!
    bool allowMultipleKeysInMap = false;
  };  // end of struct DataParsingOptions

  //! list of all type handled by the Data structure
  using DataTypes = tfel::meta::GenerateTypeList<bool,
                                                 int,
                                                 double,
                                                 std::string,
                                                 std::vector<Data>,
                                                 std::map<double, double>,
                                                 DataMap,
                                                 DataStructure>::type;

  namespace internals {

    /*!
     * \brief a simple meta function to the check if the given type
     * is part of the `DataTypes` type list.
     * \tparam T: type to be checked
     */
    template <typename T>
    struct isDataTypeCheck {
      //! \brief result type
      static constexpr bool value =
          tfel::meta::TLCountNbrOfT<typename std::decay<T>::type,
                                    tfel::utilities::DataTypes>::value == 1;
    };

  }  // end of namespace internals

  //! a simple alias
  template <typename T>
  using isDataType = tfel::utilities::internals::isDataTypeCheck<T>;

  /*!
   * \brief A structure able to contain values extracted from a
   * JSON-like file.
   * \see the `DataTypes` list of types for all the values that a
   * Data can contain.
   */
  struct TFELUTILITIES_VISIBILITY_EXPORT Data : public GenTypeBase<DataTypes> {
    //! a simple alias
    using CallBack = std::function<void(const Data&)>;
    //! constructor from a value
    template <typename T1,
              std::enable_if_t<tfel::meta::TLCountNbrOfT<std::decay_t<T1>,
                                                         DataTypes>::value == 1,
                               bool> = true>
    TFEL_INLINE Data(T1&& v) : GenTypeBase<DataTypes>(std::forward<T1>(v)) {}
    /*!
     * \brief read a JSON-like structure
     * \return the values read
     * \param[in,out] p:  current position in the tokens stream
     * \param[in]     pe: past-the-end iterator
     * \param[in]     o: parsing options
     */
    static Data read(CxxTokenizer::const_iterator&,
                     const CxxTokenizer::const_iterator,
                     const DataParsingOptions& = {});
    /*!
     * \brief read a map. For each read key, a callback must
     * available to treat the associated data. The result of the
     * treatment is stored in the returned value.
     * \return treated values
     * \param[in,out] p:  current position in the tokens stream
     * \param[in]     pe: past-the-end iterator
     * \param[in]     callbacks: list of call-backs
     * \param[in]     o: parsing options
     */
    static void parse(CxxTokenizer::const_iterator&,
                      const CxxTokenizer::const_iterator,
                      const std::map<std::string, CallBack>&,
                      const DataParsingOptions& = {});
    /*!
     * \brief read a standard value (string,double,int)
     * \return the values read
     * \param[in,out] p:  current position in the tokens stream
     * \param[in]     pe: past-the-end iterator
     * \param[in]     o: parsing options
     */
    static Data read_value(CxxTokenizer::const_iterator&,
                           const CxxTokenizer::const_iterator,
                           const DataParsingOptions& = {});
    /*!
     * \brief read a map
     * \return the values read
     * \param[in,out] p:  current position in the tokens stream
     * \param[in]     pe: past-the-end iterator
     * \param[in]     o: parsing options
     */
    static Data read_vector(CxxTokenizer::const_iterator&,
                            const CxxTokenizer::const_iterator,
                            const DataParsingOptions& = {});
    /*!
     * \brief read a map
     * \return the values read
     * \param[in,out] p: current position in the tokens stream
     * \param[in]     pe: past-the-end iterator
     * \param[in]     o: parsing options
     */
    static Data read_map(CxxTokenizer::const_iterator&,
                         const CxxTokenizer::const_iterator,
                         const DataParsingOptions& = {});
    //! default constructor
    Data();
    //! move constructor
    Data(Data&&);
    //! copy constructor
    Data(const Data&);
    //! move assignement
    Data& operator=(Data&&);
    //! assignement
    Data& operator=(const Data&);
    //! destructor
    ~Data();
  };  // end of struct Data

  //! \brief comparison operator
  TFELUTILITIES_VISIBILITY_EXPORT bool operator==(const Data&, const Data&);

  /*!
   * \brief extract a value of the given type from a Data structure
   * \param[in] d: data
   * \return the extracted value
   */
  template <typename T>
  T convert(const Data&);

  /*!
   * \param[in] d: data
   * \return true if the Data can be converted to the given type
   */
  template <typename T>
  bool is_convertible(const Data&);

  /*!
   * \brief an helper structure used to validate a data map.
   */
  struct TFELUTILITIES_VISIBILITY_EXPORT DataMapValidator {
    //! \brief function used to validate a
    using DataValidator = std::function<void(const Data&)>;
    //! \brief constructor
    DataMapValidator();
    //! \brief move constructor
    DataMapValidator(DataMapValidator&&);
    //! \brief move constructor
    DataMapValidator(const DataMapValidator&);
    //! \brief move assignement
    DataMapValidator& operator=(DataMapValidator&&);
    //! \brief standard assignement
    DataMapValidator& operator=(const DataMapValidator&);
    //!
    DataMapValidator& addDataValidator(const std::string&,
                                       const DataValidator&);
    //!
    template <typename T1>
    std::enable_if_t<
        tfel::meta::TLCountNbrOfT<std::decay_t<T1>, DataTypes>::value == 1,
        DataMapValidator&>
    addDataTypeValidator(const std::string& k);
    //! \brief validate a data-map
    void validate(const DataMap&) const;
    //! \brief destructor
    ~DataMapValidator();

   private:
    //! \brief validators, sorted by keywords
    std::map<std::string, std::vector<DataValidator>> validators;
  };

  /*!
   * \brief throw an exception stating that the parameter type is not the
   * expected one.
   */
  TFELUTILITIES_VISIBILITY_EXPORT [[noreturn]] void raiseUnmatchedDataType(
      const std::string_view);
  /*!
   * \return true if the given data exists
   * \param[in] m: data map
   * \param[in] n: name
   */
  TFELUTILITIES_VISIBILITY_EXPORT bool contains(const DataMap&,
                                                std::string_view);
  /*!
   * \return true if the given data has the given type
   * \param[in] m: data map
   * \param[in] n: name
   * \throws if the data does not exists
   */
  template <typename ResultType>
  bool is(const DataMap&, std::string_view);
  /*!
   * \return the data associated with the given name
   * \param[in] m: data map
   * \param[in] n: name
   */
  TFELUTILITIES_VISIBILITY_EXPORT const Data& get(const DataMap&,
                                                  std::string_view);
  /*!
   * \return value of the data
   * \tparam ResultType: expected type of the data
   * \param[in] m: data map
   * \param[in] n: name
   * \throws if the data does not exists or does not have the good type.
   */
  template <typename ResultType>
  const ResultType& get(const DataMap&, std::string_view);
  /*!
   * \return value of the data if present, a default value otherwise
   * \tparam ResultType: expected type of the data
   * \param[in] m: data map
   * \param[in] n: name
   * \param[in] v: default value
   * \throws if the data exists but does not have the good type.
   */
  template <typename ResultType>
  ResultType get_if(const DataMap&, std::string_view, const ResultType&);
  /*!
   * \return value of the data if present, a default value otherwise
   * \param[in] m: data map
   * \param[in] n: name
   * \param[in] v: default value
   */
  TFELUTILITIES_VISIBILITY_EXPORT Data get_if(const DataMap&,
                                              std::string_view,
                                              const Data&);
  /*!
   * \return a data map containing only data with the given names
   * \param[in] m: data map
   * \param[in] names: list of names of data to be extracted
   */
  TFELUTILITIES_VISIBILITY_EXPORT DataMap
  extract(const DataMap&, const std::vector<std::string>&);

}  // end of namespace tfel::utilities

#include "TFEL/Utilities/Data.ixx"

#endif /* LIB_TFEL_UTILITIES_DATA_HXX */
