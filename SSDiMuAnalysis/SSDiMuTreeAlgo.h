#ifndef SSDiLepAnalysis_SSDiLepTreeAlgo_H
#define SSDiLepAnalysis_SSDiLepTreeAlgo_H

// EL include(s)
#include <EventLoop/Algorithm.h>

// package include(s):
#include <xAODAnaHelpers/TreeAlgo.h>
#include <SSDiLepAnalysis/SSDiLepTree.h>

class SSDiLepTreeAlgo : public TreeAlgo
{
  // put your configuration variables here as public variables.
  // that way they can be set directly from CINT and python.

public:

  // additional data members which are not already in xAH::TreeAlgo.h
  //std::string m_lepContainerName;

  // this is a standard constructor
  SSDiLepTreeAlgo () :
    TreeAlgo()
  {
    Info("SSDiLepTreeAlgo::SSDiLepTreeAlgo()","Forcing energy/momentum units to MeV...");
    m_units = 1e0;
  };

  // these are the functions inherited from Algorithm

  // overload only the ones that somehow differ from the original methods in TreeAlgo
  virtual EL::StatusCode execute ();

  // these are the functions not inherited from Algorithm

  // this is needed to distribute the algorithm to the workers
  ClassDef(SSDiLepTreeAlgo, 1);
};

#endif
