#ifndef SSDiMuAnalysis_SSDiMuTree_H
#define SSDiMuAnalysis_SSDiMuTree_H

// package include(s):
#include "xAODAnaHelpers/HelpTreeBase.h"

// EDM include(s):
#include "xAODEventInfo/EventInfo.h"
#include "xAODBase/IParticleContainer.h"
#include "xAODMuon/Muon.h"
#include "xAODEgamma/Electron.h"
#include "xAODJet/Jet.h"
#include "xAODTau/TauJet.h"
#include  "xAODCaloEvent/CaloCluster.h"

// Infrastructure include(s):
#include "xAODRootAccess/TEvent.h"

// ROOT include(s):
#include "TTree.h"
#include "TFile.h"

class SSDiMuTree : public HelpTreeBase
{

  private:

    /* event variables*/
    int               m_is_mc;
    std::vector<int>  m_HLpp_Daughters;
    std::vector<int>  m_HLmm_Daughters;
    std::vector<int>  m_HRpp_Daughters;
    std::vector<int>  m_HRmm_Daughters;
    
    /* jet variables */
    std::vector<float> m_jet_m;

    /* muon variables */
    std::vector<int> m_muon_isTruthMatched;
    std::vector<int> m_muon_truthType;
    std::vector<int> m_muon_truthPdgId;
    std::vector<int> m_muon_truthOrigin;
    std::vector<int> m_muon_truthStatus;

    /* electron variables */
    std::vector<int>   m_electron_isTruthMatched;
    std::vector<int>   m_electron_truthType;
    std::vector<int>   m_electron_truthPdgId;
    std::vector<int>   m_electron_truthOrigin;
    std::vector<int>   m_electron_truthStatus;
    
    std::vector<int>   m_electron_bkgTruthType;
    std::vector<int>   m_electron_bkgTruthOrigin;
    std::vector<int>   m_electron_bkgMotherPdgId;
    std::vector<int>   m_electron_firstEgMotherTruthType;
    std::vector<int>   m_electron_firstEgMotherTruthOrigin;
    std::vector<int>   m_electron_firstEgMotherPdgId;


  public:

    SSDiMuTree( TTree* tree, TFile* file, xAOD::TEvent* event, xAOD::TStore* store, const float units = 1e3, bool debug = false, bool DC14 = false );
    ~SSDiMuTree();

    void AddEventUser(const std::string detailStrUser = "");
    void AddMuonsUser(const std::string detailStrUser = "");
    void AddElectronsUser(const std::string detailStrUser = "");
    void AddJetsUser(const std::string detailStrUser = "", const std::string = "jet" );

    void ClearEventUser();
    void ClearMuonsUser();
    void ClearElectronsUser();
    void ClearJetsUser( const std::string = "jet" );

    void FillEventUser( const xAOD::EventInfo* );
    void FillMuonsUser( const xAOD::Muon*, const std::string /*muonName = "muon"*/ );
    void FillElectronsUser( const xAOD::Electron*  );
    void FillJetsUser( const xAOD::Jet*, const std::string = "jet" );
};
#endif
