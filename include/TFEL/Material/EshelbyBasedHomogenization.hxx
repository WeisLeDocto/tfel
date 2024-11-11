/*!
 * \file   include/TFEL/Material/EshelbyBasedHomogenization.hxx
 * \author Antoine Martin
 * \date   24 October 2024
 * \brief  This file declares some homogenization schemes based on solution of Eshelby problem.
 * \copyright Copyright (C) 2006-2018 CEA/DEN, EDF R&D. All rights
 * reserved.
 * This project is publicly released under either the GNU GPL Licence
 * or the CECILL-A licence. A copy of thoses licences are delivered
 * with the sources of TFEL. CEA or EDF may also distribute this
 * project under specific licensing conditions.
 */

#ifndef LIB_TFEL_MATERIAL_ESHELBYBASEDHOMOGENIZATION_HXX
#define LIB_TFEL_MATERIAL_ESHELBYBASEDHOMOGENIZATION_HXX

#include "TFEL/Math/st2tost2.hxx"
#include "TFEL/Material/Eshelby.hxx"


namespace tfel::material {
   /*!
   * This function gives the homogenized stiffness for a dilute scheme, knowing the strain localisation tensor.
   * \tparam real: underlying type
   * \tparam StressType: type of the elastic constants related to the matrix and the inclusions
   * \return an object of type st2tost2<3u,StressType>
   * \param [in] young,nu: Young modulus and Poisson's ratio of the matrix
   * \param [in] f: volumic fraction of inclusions
   * \param [in] C_i: elastic tensor of the inclusions (may be anisotropic).
   * \param [in] A: mean strain localisation tensor of inclusions
   */
   template <typename real, typename StressType>
  TFEL_HOST_DEVICE const tfel::math::st2tost2<3u,StressType> diluteScheme(
      const StressType&,
      const real&,
      const real&,
      const tfel::math::st2tost2<3u,StressType>&,
      const tfel::math::st2tost2<3u,real>&);
      
 /*!
   * This function gives the homogenized stiffness for a Mori-Tanaka scheme knowing the strain localisation tensor.
   * \tparam real: underlying type
   * \tparam StressType: type of the elastic constants related to the matrix and the inclusions
   * \return an object of type st2tost2<3u,StressType>
   * \param [in] young,nu: Young modulus and Poisson's ratio of the matrix
   * \param [in] f: volumic fraction of inclusions
   * \param [in] C_i: elastic tensor of the inclusions (may be anisotropic).
   * \param [in] A: mean strain localisation tensor of inclusions
   */
  template <typename real, typename StressType>
  TFEL_HOST_DEVICE const tfel::math::st2tost2<3u,StressType> moriTanakaScheme(
      const StressType&,
      const real&,
      const real&,
      const tfel::math::st2tost2<3u,StressType>&,
      const tfel::math::st2tost2<3u,real>&);
      
    /*!
   * This function gives the homogenized stiffness for a dilute scheme, for spheres
   * \tparam real: underlying type
   * \tparam StressType: type of the elastic constants related to the matrix and the spheres
   * \return an object of type st2tost2<3u,StressType>
   * \param [in] young,nu: Young modulus and Poisson's ratio of the matrix
   * \param [in] f: volumic fraction of spheres
   * \param [in] C_i: elastic tensor of the spheres (may be anisotropic).
   */
  template <typename real, typename StressType>
  TFEL_HOST_DEVICE const tfel::math::st2tost2<3u,StressType> sphereDiluteScheme(
      const StressType&,
      const real&,
      const real&,
      const tfel::math::st2tost2<3u,StressType>&);


  /*!
   * This function gives the homogenized stiffness for a Mori-Tanaka scheme, for spheres
   * \tparam real: underlying type
   * \tparam StressType: type of the elastic constants related to the matrix and the spheres
   * \return an object of type st2tost2<3u,StressType>
   * \param [in] young,nu: Young modulus and Poisson's ratio of the matrix
   * \param [in] f: volumic fraction of spheres
   * \param [in] C_i: elastic tensor of the spheres (may be anisotropic).
   */
  template <typename real, typename StressType>
  TFEL_HOST_DEVICE const tfel::math::st2tost2<3u,StressType> sphereMoriTanakaScheme(
      const StressType&,
      const real&,
      const real&,
      const tfel::math::st2tost2<3u,StressType>&);
      

   /*!
   * This function gives the homogenized stiffness for a dilute scheme, for an isotropic distribution of ellipsoids
   * \tparam real: underlying type
   * \tparam StressType: type of the elastic constants related to the matrix and the ellipsoids
   * \tparam LengthType: type of the dimensions of the ellipsoids
   * \return an object of type st2tost2<3u,StressType>
   * \param [in] young,nu: Young modulus and Poisson's ratio of the matrix
   * \param [in] f: volumic fraction of ellipsoids
   * \param [in] C_i: elastic tensor of the ellipsoids (may be anisotropic).
   * \param[in] a: length of the first semi-axis
   * \param[in] b: length of the second semi-axis
   * \param[in] c: length of the third semi-axis
   */
   template <typename real, typename StressType, typename LengthType>
  TFEL_HOST_DEVICE const tfel::math::st2tost2<3u,StressType> isotropicDiluteScheme(
      const StressType&,
      const real&,
      const real&,
      const tfel::math::st2tost2<3u,StressType>&,
      const LengthType&,
      const LengthType&,
      const LengthType&);
      
     
     /*!
   * This function gives the homogenized stiffness for a dilute scheme, for a transverse isotropic distribution of ellipsoids. One principal axis (the same principal axis for all ellipsoids) is oriented in a fixed direction n. The distribution of the other axes are in the plane normal to n, and the distribution of these axes inside this plane is isotropic.
   * \tparam real: underlying type
   * \tparam StressType: type of the elastic constants related to the matrix and the ellipsoids
   * \tparam LengthType: type of the dimensions of the ellipsoids
   * \return an object of type st2tost2<3u,StressType>
   * \param [in] young,nu: Young modulus and Poisson's ratio of the matrix
   * \param [in] f: volumic fraction of ellipsoids
   * \param [in] C_i: elastic tensor of the ellipsoids (may be anisotropic).
   * \param [in] n_a: direction of the principal axis which has a fixed orientation and a semi-length \f$a\f$
   * \param[in] a: length of semi-axis relative to the direction \f$n_a\f$
   * \param[in] b: length of the second semi-axis
   * \param[in] c: length of the third semi-axis
   */
    template <typename real, typename StressType, typename LengthType>
  TFEL_HOST_DEVICE const tfel::math::st2tost2<3u,StressType> transverseIsotropicDiluteScheme(
      const StressType&,
      const real&,
      const real&,
      const tfel::math::st2tost2<3u,StressType>&,
      const tfel::math::tvector<3u,real>&,
      const LengthType&,
      const LengthType&,
      const LengthType&);
     
     /*!
   * This function gives the homogenized stiffness for a dilute scheme, for a distribution of oriented ellipsoids : all principal axes have the same fixed orientation.
   * \tparam real: underlying type
   * \tparam StressType: type of the elastic constants related to the matrix and the ellipsoids
   * \tparam LengthType: type of the dimensions of the ellipsoids
   * \return an object of type st2tost2<3u,StressType>
   * \param [in] young,nu: Young modulus and Poisson's ratio of the matrix
   * \param [in] f: volumic fraction of ellipsoids
   * \param [in] C_i: elastic tensor of the ellipsoids (may be anisotropic).
   * \param [in] n_a: direction of the principal axis whose semi-length is \f$a\f$
   * \param[in] a: length of semi-axis relative to the direction \f$n_a\f$
   * \param [in] n_b: direction of the principal axis whose semi-length is \f$b\f$
   * \param[in] b: length of the semi-axis relative to the direction \f$n_b\f$
   * \param[in] c: length of the third semi-axis
   */ 
     template <typename real, typename StressType, typename LengthType>
  TFEL_HOST_DEVICE const tfel::math::st2tost2<3u,StressType> orientedDiluteScheme(
      const StressType&,
      const real&,
      const real&,
      const tfel::math::st2tost2<3u,StressType>&,
      const tfel::math::tvector<3u,real>&,
      const LengthType&,
      const tfel::math::tvector<3u,real>&,
      const LengthType&,
      const LengthType&);
      
  /*!
   * This function gives the homogenized stiffness for a Mori-Tanaka scheme, for an isotropic distribution of ellipsoids
   * \tparam real: underlying type
   * \tparam StressType: type of the elastic constants related to the matrix and the ellipsoids
   * \tparam LengthType: type of the dimensions of the ellipsoids
   * \return an object of type st2tost2<3u,StressType>
   * \param [in] young,nu: Young modulus and Poisson's ratio of the matrix
   * \param [in] f: volumic fraction of ellipsoids
   * \param [in] C_i: elastic tensor of the ellipsoids (may be anisotropic).
   * \param[in] a: length of the first semi-axis
   * \param[in] b: length of the second semi-axis
   * \param[in] c: length of the third semi-axis
   */
     template <typename real, typename StressType, typename LengthType>
  TFEL_HOST_DEVICE const tfel::math::st2tost2<3u,StressType> isotropicMoriTanakaScheme(
      const StressType&,
      const real&,
      const real&,
      const tfel::math::st2tost2<3u,StressType>&,
      const LengthType&,
      const LengthType&,
      const LengthType&);
      
   /*!
   * This function gives the homogenized stiffness for a Mori-Tanaka scheme, for a transverse isotropic distribution of ellipsoids. One principal axis (the same principal axis for all ellipsoids) is oriented in a fixed direction n. The distribution of the other axes are in the plane normal to n, and the distribution of these axes inside this plane is isotropic.
   * \tparam real: underlying type
   * \tparam StressType: type of the elastic constants related to the matrix and the ellipsoids
   * \tparam LengthType: type of the dimensions of the ellipsoids
   * \return an object of type st2tost2<3u,StressType>
   * \param [in] young,nu: Young modulus and Poisson's ratio of the matrix
   * \param [in] f: volumic fraction of ellipsoids
   * \param [in] C_i: elastic tensor of the ellipsoids (may be anisotropic).
   * \param [in] n_a: direction of the principal axis which has a fixed orientation and a semi-length \f$a\f$
   * \param[in] a: length of semi-axis relative to the direction \f$n_a\f$
   * \param[in] b: length of the second semi-axis
   * \param[in] c: length of the third semi-axis
   */
    template <typename real, typename StressType, typename LengthType>
  TFEL_HOST_DEVICE const tfel::math::st2tost2<3u,StressType> transverseIsotropicMoriTanakaScheme(
      const StressType&,
      const real&,
      const real&,
      const tfel::math::st2tost2<3u,StressType>&,
      const tfel::math::tvector<3u,real>&,
      const LengthType&,
      const LengthType&,
      const LengthType&);
      
      /*!
   * This function gives the homogenized stiffness for a Mori-Tanaka scheme, for a distribution of oriented ellipsoids : all principal axes have the same fixed orientation.
   * \tparam real: underlying type
   * \tparam StressType: type of the elastic constants related to the matrix and the ellipsoids
   * \tparam LengthType: type of the dimensions of the ellipsoids
   * \return an object of type st2tost2<3u,StressType>
   * \param [in] young,nu: Young modulus and Poisson's ratio of the matrix
   * \param [in] f: volumic fraction of ellipsoids
   * \param [in] C_i: elastic tensor of the ellipsoids (may be anisotropic).
   * \param [in] n_a: direction of the principal axis whose semi-length is \f$a\f$
   * \param[in] a: length of semi-axis relative to the direction \f$n_a\f$
   * \param [in] n_b: direction of the principal axis whose semi-length is \f$b\f$
   * \param[in] b: length of the semi-axis relative to the direction \f$n_b\f$
   * \param[in] c: length of the third semi-axis
   */ 
    template <typename real, typename StressType, typename LengthType>
  TFEL_HOST_DEVICE const tfel::math::st2tost2<3u,StressType> orientedMoriTanakaScheme(
      const StressType&,
      const real&,
      const real&,
      const tfel::math::st2tost2<3u,StressType>&,
      const tfel::math::tvector<3u,real>&,
      const LengthType&,
      const tfel::math::tvector<3u,real>&,
      const LengthType&,
      const LengthType&);

}  // end of namespace tfel::material

#include "TFEL/Material/EshelbyBasedHomogenization.ixx"

#endif /* LIB_TFEL_MATERIAL_ESHELBYBASEDHOMOGENIZATION_HXX */
