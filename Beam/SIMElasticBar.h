// $Id$
//==============================================================================
//!
//! \file SIMElasticBar.h
//!
//! \date Aug 11 2013
//!
//! \author Knut Morten Okstad / SINTEF
//!
//! \brief Solution driver for NURBS-based FE analysis of elastic bars & beams.
//!
//==============================================================================

#ifndef _SIM_ELASTIC_BAR_H
#define _SIM_ELASTIC_BAR_H

#include "SIM1D.h"

class ElasticBar;
class ElasticBeam;


/*!
  \brief Driver class for isogeometric FEM analysis of elastic bars and beams.
*/

class SIMElasticBar : public SIM1D
{
  //! Nodal point load container
  typedef std::map<std::pair<int,int>,ScalarFunc*> LoadMap;

public:
  //! \brief Default constructor.
  //! \param[in] n Number of consequtive solution vectors in core
  SIMElasticBar(unsigned char n = 1) : SIM1D(3) { nsd = 3; nsv = n; }
  //! \brief The destructor deletes the nodal point load functions.
  virtual ~SIMElasticBar();

  //! \brief Returns the current rotation tensor for the specified global node.
  Tensor getNodeRotation(int inod) const;

protected:
  //! \brief Returns the actual beam problem integrand.
  virtual ElasticBar* getBarIntegrand(const std::string&);
  //! \brief Returns the actual beam problem integrand.
  virtual ElasticBeam* getBeamIntegrand(const std::string&);

  using SIM1D::parse;
  //! \brief Parses a data section from an XML element.
  virtual bool parse(const TiXmlElement* elem);

  //! \brief Preprocessing performed before the FEM model generation.
  virtual void preprocessA();

  //! \brief Assembles the nodal point loads, if any.
  virtual bool assembleDiscreteTerms(const IntegrandBase* itg,
                                     const TimeDomain& time);

private:
  LoadMap myLoads; //!< Nodal point loads

protected:
  unsigned char nsv; //!< Number of consequtive solution vectors in core
};

#endif
