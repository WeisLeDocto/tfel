/*!
 * \file   mfront/include/MFront/AnsysInterface.hxx
 * \brief    
 * \author Thomas Helfer
 * \date   17 mars 2016
 * \copyright Copyright (C) 2006-2018 CEA/DEN, EDF R&D. All rights 
 * reserved. 
 * This project is publicly released under either the GNU GPL Licence 
 * or the CECILL-A licence. A copy of thoses licences are delivered 
 * with the sources of TFEL. CEA or EDF may also distribute this 
 * project under specific licensing conditions. 
 */

#ifndef LIB_MFRONT_ANSYSINTERFACE_HXX
#define LIB_MFRONT_ANSYSINTERFACE_HXX

#include<string>
#include<iosfwd>

#include"TFEL/Utilities/CxxTokenizer.hxx"
#include"MFront/UMATInterfaceBase.hxx"

namespace mfront{

  /*!
   * \brief This class provide an interface to the Ansys/APDL finite
   * element solver
   */
  struct AnsysInterface
    : public UMATInterfaceBase
  {
    //! name of finite strain strategy attribute
    static const char *const finiteStrainStrategy;
    /*!
     * \return the name of the interface
     */
    static std::string getName();
    std::pair<bool, tokens_iterator> treatKeyword(
        BehaviourDescription &,
        const std::string &,
        const std::vector<std::string> &,
        tokens_iterator,
        const tokens_iterator) override;
    void endTreatment(const BehaviourDescription&,
		      const FileDescription&) const override;
    void getTargetsDescription(TargetsDescription&,
			       const BehaviourDescription&) override;
    //! destructor
    ~AnsysInterface() override;
  protected:
    /*!
     * \brief return the state variable offset used for variables used
     * internally by the ansys interface
     * \param[in] mb: behaviour description
     * \param[in] h:  modelling hypothesis
     */
   virtual unsigned short getStateVariablesOffset(const BehaviourDescription &,
                                                  const Hypothesis) const;
   std::string getLibraryName(const BehaviourDescription &) const override;
   /*!
    * \brief write a  specialisation of the AnsysTraits class
    * \param[in] out : ouptut file
    * \param[in] mb  : behaviour description
    * \param[in] h   : modelling hypothesis
    */
   virtual void writeAnsysBehaviourTraits(std::ostream &,
                                          const BehaviourDescription &,
                                          const Hypothesis) const;
   void writeUMATxxAdditionalSymbols(std::ostream &,
                                     const std::string &,
                                     const Hypothesis,
                                     const BehaviourDescription &,
                                     const FileDescription &) const override;
   void writeUMATxxBehaviourTypeSymbols(
       std::ostream &,
       const std::string &,
       const BehaviourDescription &) const override;
   void writeUMATxxBehaviourKinematicSymbols(
       std::ostream &,
       const std::string &,
       const BehaviourDescription &) const override;
   void writeUMATxxSpecificSymbols(std::ostream &,
                                   const std::string &,
                                   const BehaviourDescription &,
                                   const FileDescription &) const override;
   void writeMTestFileGeneratorSetModellingHypothesis(
       std::ostream &) const override;
   std::string getModellingHypothesisTest(const Hypothesis) const override;
   std::map<UMATInterfaceBase::Hypothesis, std::string>
   gatherModellingHypothesesAndTests(
       const BehaviourDescription &) const override;
   std::string getFunctionNameBasis(const std::string &) const override;
   /*!
    * \return the name of the function generated by the interface
    * \param[in] n: name of the behaviour as defined by interface
    *               (generally taking into account the material
    *               and the behaviour name)
    * \param[in] h: modelling hypothesis
    */
   virtual std::string getFunctionNameForHypothesis(const std::string &,
                                                    const Hypothesis) const;
   std::set<Hypothesis> getModellingHypothesesToBeTreated(
       const BehaviourDescription &) const override;
   /*!
    * \return the input file example
    * \param[in] mb: behaviour description
    * \param[in] fd: file description
    */
   virtual void writeInputFileExample(const BehaviourDescription &,
                                      const FileDescription &) const;

   virtual std::string getInterfaceName() const override;
   void writeBehaviourDataMainVariablesSetters(
       std::ostream &, const BehaviourDescription &) const override;
   void writeBehaviourDataDrivingVariableSetter(
       std::ostream &,
       const DrivingVariable &,
       const SupportedTypes::TypeSize) const override;
   void writeIntegrationDataDrivingVariableSetter(
       std::ostream &,
       const DrivingVariable &,
       const SupportedTypes::TypeSize) const override;
   void exportThermodynamicForce(std::ostream &,
                                 const std::string &,
                                 const ThermodynamicForce &,
                                 const SupportedTypes::TypeSize) const override;
   void writeInterfaceSpecificIncludes(
       std::ostream &, const BehaviourDescription &) const override;
   void writeBehaviourDataThermodynamicForceSetter(
       std::ostream &,
       const ThermodynamicForce &,
       const SupportedTypes::TypeSize) const override;
   std::vector<std::pair<std::string, std::string>>
   getBehaviourDataConstructorAdditionalVariables() const override;
   void completeBehaviourDataConstructor(
       std::ostream &,
       const Hypothesis,
       const BehaviourDescription &) const override;
   /*!
    * \brief write the call to the base function
    * \param[in] out:  output file
    * \param[in] mb:   mechanical behaviour description
    * \param[in] name: name of the behaviour as defined by interface
    *                  (generally taking into account the material
    *                  and the behaviour name)
    * \param[in] sfeh: name of the function used to handle the stress
    *                  expansion
    * \param[in] h:    modelling hypothesis
    */
   virtual void writeFunctionBase(std::ostream &,
                                  const BehaviourDescription &,
                                  const std::string &,
                                  const std::string &,
                                  const Hypothesis) const;
   /*!
    * \brief write the call to the base function
    * \param[in] out:  output file
    * \param[in] mb:   mechanical behaviour description
    * \param[in] name: name of the behaviour as defined by interface
    *                  (generally taking into account the material
    *                  and the behaviour name)
    * \param[in] h:    modelling hypothesis
    */
   virtual void writeSmallStrainFunction(std::ostream &,
                                         const BehaviourDescription &,
                                         const std::string &,
                                         const Hypothesis) const;
   /*!
    * \brief write the call to the base function
    * \param[in] out:  output file
    * \param[in] mb:   mechanical behaviour description
    * \param[in] name: name of the behaviour as defined by interface
    *                  (generally taking into account the material
    *                  and the behaviour name)
    * \param[in] h:    modelling hypothesis
    */
   virtual void writeFiniteStrainFunction(std::ostream &,
                                          const BehaviourDescription &,
                                          const std::string &,
                                          const Hypothesis) const;
   /*!
    * \brief write the call to the base function
    * \param[in] out:  output file
    * \param[in] mb:   mechanical behaviour description
    * \param[in] name: name of the behaviour as defined by interface
    *                  (generally taking into account the material
    *                  and the behaviour name)
    * \param[in] h:    modelling hypothesis
    */
   virtual void writeFiniteRotationSmallStrainFunction(
       std::ostream &,
       const BehaviourDescription &,
       const std::string &,
       const Hypothesis) const;
   /*!
    * \brief write the call to the base function
    * \param[in] out:  output file
    * \param[in] mb:   mechanical behaviour description
    * \param[in] name: name of the behaviour as defined by interface
    *                  (generally taking into account the material
    *                  and the behaviour name)
    * \param[in] h:    modelling hypothesis
    */
   virtual void writeMieheApelLambrechtLogarithmicStrainFunction(
       std::ostream &,
       const BehaviourDescription &,
       const std::string &,
       const Hypothesis) const;
   //! \return true if the interface handles external state variables
   virtual bool areExternalStateVariablesSupported() const override;
   /*!
    * \brief boolean stating the we want a comparison of the user
    * defined tangent operator with a numerical approximation.
    */
   bool compareToNumericalTangentOperator = false;
   /*!
    * \brief perturbation value used for the computation of the
    * numerical approximation of the tangent operator
    */
   double strainPerturbationValue = 1.e-6;
   /*!
    * \brief comparison critera value used for comparing of the user
    * defined tangent operator with a numerical approximation.
    */
   double tangentOperatorComparisonCriterion = 1.e7;
  }; // end of struct AnsysInterface
  
} // end of namespace mfront

#endif /* LIB_MFRONT_ANSYSINTERFACE_HXX */
