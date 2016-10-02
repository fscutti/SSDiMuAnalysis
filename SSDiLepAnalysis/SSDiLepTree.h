#ifndef SSDiLepAnalysis_SSDiLepTree_H
#define SSDiLepAnalysis_SSDiLepTree_H

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

class SSDiLepTree : public HelpTreeBase
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
    //std::vector<int> m_muon_isTight;
    //std::vector<int> m_muon_isMedium;
    //std::vector<int> m_muon_isOS;
    //std::vector<int> m_muon_isClosestSS;
    //std::vector<int> m_muon_isTag;

    std::vector<int> m_muon_isTruthMatched;
    std::vector<int> m_muon_isChFlip;
    std::vector<int> m_muon_isBrem;
    std::vector<int> m_muon_truthType;
    std::vector<int> m_muon_truthPdgId;
    std::vector<int> m_muon_truthOrigin;
    std::vector<int> m_muon_truthStatus;
    std::vector<int> m_muon_ancestorTruthType;
    std::vector<int> m_muon_ancestorTruthPdgId;
    std::vector<int> m_muon_ancestorTruthOrigin;
    std::vector<int> m_muon_ancestorTruthStatus;

    /* electron variables */
    //std::vector<int>   m_electron_crack;
    //std::vector<int>   m_electron_isTight;
    //std::vector<int>   m_electron_isMedium;
    //std::vector<int>   m_electron_isOS;
    //std::vector<int>   m_electron_isClosestSS;
    //std::vector<int>   m_electron_isTag;
    std::vector<int>   m_electron_isTruthMatched;
    std::vector<int>   m_electron_isChFlip;
    std::vector<int>   m_electron_isBrem;
    std::vector<int>   m_electron_truthType;
    std::vector<int>   m_electron_truthPdgId;
    std::vector<int>   m_electron_truthOrigin;
    std::vector<int>   m_electron_truthStatus;
    std::vector<int>   m_electron_ancestorTruthType;
    std::vector<int>   m_electron_ancestorTruthPdgId;
    std::vector<int>   m_electron_ancestorTruthOrigin;
    std::vector<int>   m_electron_ancestorTruthStatus;

    /* tau variables */
    //std::vector<int>   m_tau_isBDTTight;

  public:

    SSDiLepTree( TTree* tree, TFile* file, xAOD::TEvent* event, xAOD::TStore* store, const float units = 1e3, bool debug = false, bool DC14 = false );
    ~SSDiLepTree();

    void AddEventUser(const std::string detailStrUser = "");
    /*void AddTriggerUser(const std::string detailStrUser = "");*/
    void AddMuonsUser(const std::string detailStrUser = "");
    void AddElectronsUser(const std::string detailStrUser = "");
    void AddJetsUser(const std::string detailStrUser = "", const std::string = "jet" );
    //void AddTausUser(const std::string detailStrUser = "");
    /*void AddMETUser(const std::string detailStrUser = "");*/

    void ClearEventUser();
    /*void ClearTriggerUser();*/
    void ClearMuonsUser();
    void ClearElectronsUser();
    void ClearJetsUser( const std::string = "jet" );
    //void ClearTausUser();
    /*void ClearMETUser();*/

    void FillEventUser( const xAOD::EventInfo* );
    /*void FillTriggerUser( const xAOD::EventInfo*  );*/
    void FillMuonsUser( const xAOD::Muon*, const std::string /*muonName = "muon"*/ );
    void FillElectronsUser( const xAOD::Electron*  );
    void FillJetsUser( const xAOD::Jet*, const std::string = "jet" );
    //void FillTausUser( const xAOD::TauJet* );
    /*void FillMETUser( const xAOD::MissingETContainer*  );*/
};
#endif
