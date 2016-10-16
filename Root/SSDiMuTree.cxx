#include "SSDiMuAnalysis/SSDiMuTree.h"

SSDiMuTree :: SSDiMuTree( TTree* tree, TFile* file, xAOD::TEvent* event, xAOD::TStore* store, const float units, bool debug, bool DC14 ) :
  HelpTreeBase(tree, file, event, store, units, debug, DC14 )
{
  Info("SSDiMuTree", "Creating output TTree");
}

SSDiMuTree :: ~SSDiMuTree() {}

void SSDiMuTree::AddEventUser(const std::string detailStrUser)
{

  // to get rid of warning when detailString is not used
  if ( m_debug ) { Info("AddEventUser()", "Adding branches w/ detail: %s", detailStrUser.c_str()); }

  // event variables
  m_tree->Branch("isMC",              &m_is_mc, "isMC/I");
  
  if ( m_isMC ) {
    m_tree->Branch("HLpp_Daughters", &m_HLpp_Daughters);
    m_tree->Branch("HLmm_Daughters", &m_HLmm_Daughters);
    m_tree->Branch("HRpp_Daughters", &m_HRpp_Daughters);
    m_tree->Branch("HRmm_Daughters", &m_HRmm_Daughters);
  }
}

void SSDiMuTree::AddJetsUser(const std::string detailStrUser, const std::string jetName )
{

  // to get rid of warning when detailString is not used
  if ( m_debug ) { Info("AddJetsUser()", "Adding branches w/ detail: %s - Jet name: %s", detailStrUser.c_str(), jetName.c_str()); }

  // jet variables
  m_tree->Branch("jet_m",     &m_jet_m);
}

void SSDiMuTree::AddMuonsUser(const std::string detailStrUser)
{

  // to get rid of warning when detailString is not used
  if ( m_debug ) { Info("AddMuonsUser()", "Adding branches w/ detail: %s", detailStrUser.c_str()); }

  // muon variables
  m_tree->Branch("muon_isTruthMatchedToMuon",     &m_muon_isTruthMatched);
  m_tree->Branch("muon_truthType",                &m_muon_truthType);
  m_tree->Branch("muon_truthPdgId",               &m_muon_truthPdgId);
  m_tree->Branch("muon_truthOrigin",              &m_muon_truthOrigin);
  m_tree->Branch("muon_truthStatus",              &m_muon_truthStatus);
}

void SSDiMuTree::AddElectronsUser(const std::string detailStrUser)
{

  // to get rid of warning when detailString is not used
  if ( m_debug ) { Info("AddElectronsUser()", "Adding branches w/ detail: %s", detailStrUser.c_str()); }

  // electron variables
  m_tree->Branch("el_isTruthMatchedToElectron",   &m_electron_isTruthMatched);
  m_tree->Branch("el_truthType",	          &m_electron_truthType);
  m_tree->Branch("el_truthPdgId",	          &m_electron_truthPdgId);
  m_tree->Branch("el_truthOrigin",                &m_electron_truthOrigin);
  m_tree->Branch("el_truthStatus",                &m_electron_truthStatus);

  // background variables
  // computed with background electron classification https://twiki.cern.ch/twiki/bin/view/AtlasProtected/EGammaTruthRun2
  m_tree->Branch("el_bkgTruthType",               &m_electron_bkgTruthType);
  m_tree->Branch("el_bkgTruthOrigin",             &m_electron_bkgTruthOrigin);
  m_tree->Branch("el_bkgMotherPdgId",             &m_electron_bkgMotherPdgId);
  m_tree->Branch("el_firstEgMotherTruthType",     &m_electron_firstEgMotherTruthType);
  m_tree->Branch("el_firstEgMotherTruthOrigin",   &m_electron_firstEgMotherTruthOrigin);
  m_tree->Branch("el_firstEgMotherPdgId",         &m_electron_firstEgMotherPdgId);

}

void SSDiMuTree::ClearEventUser()
{
  if ( m_isMC ) {
    m_HLpp_Daughters.clear();
    m_HLmm_Daughters.clear();
    m_HRpp_Daughters.clear();
    m_HRmm_Daughters.clear();
  }
}

void SSDiMuTree::ClearMuonsUser()
{
  // muon variables
  m_muon_isTruthMatched.clear();
  m_muon_truthType.clear();
  m_muon_truthPdgId.clear();
  m_muon_truthOrigin.clear();
  m_muon_truthStatus.clear();
}

void SSDiMuTree::ClearElectronsUser()
{
  // electron variables
  m_electron_isTruthMatched.clear();
  m_electron_truthType.clear();
  m_electron_truthPdgId.clear();
  m_electron_truthOrigin.clear();
  m_electron_truthStatus.clear();

  m_electron_bkgTruthType.clear();
  m_electron_bkgTruthOrigin.clear();
  m_electron_bkgMotherPdgId.clear();
  m_electron_firstEgMotherTruthType.clear();
  m_electron_firstEgMotherTruthOrigin.clear();
  m_electron_firstEgMotherPdgId.clear();


}

void SSDiMuTree::ClearJetsUser( const std::string jetName )
{
  if ( m_debug ) { Info("ClearJetsUser()", "Clearing jet branches - Jet name: %s", jetName.c_str()); }

  // jet variables
  m_jet_m.clear();
  if ( m_debug ) { Info("ClearJetsUser()", "done with clearing"); }

}

void SSDiMuTree::FillEventUser( const xAOD::EventInfo* eventInfo )
{
  if ( m_debug ) { Info("FillEventUser()", "Filling event"); }

  static SG::AuxElement::Accessor< std::vector<int> > HLpp_DaughtersAcc("HLpp_Daughters");
  static SG::AuxElement::Accessor< std::vector<int> > HLmm_DaughtersAcc("HLmm_Daughters");
  static SG::AuxElement::Accessor< std::vector<int> > HRpp_DaughtersAcc("HRpp_Daughters");
  static SG::AuxElement::Accessor< std::vector<int> > HRmm_DaughtersAcc("HRmm_Daughters");
  
  std::vector<int> dummyCODE(1,-999); 
  
  if ( HLpp_DaughtersAcc.isAvailable( *eventInfo ) )   { m_HLpp_Daughters = HLpp_DaughtersAcc( *eventInfo ) ; }
  else   { m_HLpp_Daughters = dummyCODE; }
  if ( HLmm_DaughtersAcc.isAvailable( *eventInfo ) )   { m_HLmm_Daughters = HLmm_DaughtersAcc( *eventInfo ) ; }
  else   { m_HLmm_Daughters = dummyCODE; }
  if ( HRpp_DaughtersAcc.isAvailable( *eventInfo ) )   { m_HRpp_Daughters = HRpp_DaughtersAcc( *eventInfo ) ; }
  else   { m_HRpp_Daughters = dummyCODE; }
  if ( HRmm_DaughtersAcc.isAvailable( *eventInfo ) )   { m_HRmm_Daughters = HRmm_DaughtersAcc( *eventInfo ) ; }
  else   { m_HRmm_Daughters = dummyCODE; }
  
  m_is_mc                =  ( eventInfo->eventType( xAOD::EventInfo::IS_SIMULATION ) );
}

void SSDiMuTree::FillJetsUser( const xAOD::Jet* jet, const std::string jetName )
{
  if ( m_debug ) { Info("FillJetsUser()", "Filling jets - Jet name: %s", jetName.c_str()); }

  m_jet_m.push_back( jet->m() );
}

void SSDiMuTree::FillMuonsUser( const xAOD::Muon* muon, const std::string /*muonName = "muon"*/  )
{

  if ( m_debug ) { Info("FillMuonsUser()", "Filling muons"); }

  // access this info only to fill tag/probe branches

  static SG::AuxElement::Accessor< char > isTruthMatchedAcc("isTruthMatched");
  static SG::AuxElement::ConstAccessor< int >  truthTypeAcc("truthType");
  static SG::AuxElement::Accessor< int >  truthPdgIdAcc("truthPdgId");
  static SG::AuxElement::ConstAccessor< int >  truthOriginAcc("truthOrigin");
  static SG::AuxElement::Accessor< int >  truthStatusAcc("truthStatus");

  if ( isTruthMatchedAcc.isAvailable( *muon ) )   { m_muon_isTruthMatched.push_back( isTruthMatchedAcc( *muon ) ); }
  else   { m_muon_isTruthMatched.push_back(-1); }
   if ( truthPdgIdAcc.isAvailable( *muon ) )      { m_muon_truthPdgId.push_back( truthPdgIdAcc( *muon ) ); }
  else   { m_muon_truthPdgId.push_back(0); }
  if ( truthTypeAcc.isAvailable( *muon ) )        { m_muon_truthType.push_back( truthTypeAcc( *muon ) ); }
  else   { m_muon_truthType.push_back(-1); }
  if ( truthOriginAcc.isAvailable( *muon ) )      { m_muon_truthOrigin.push_back( truthOriginAcc( *muon ) ); }
  else   { m_muon_truthOrigin.push_back(0); }
  if ( truthStatusAcc.isAvailable( *muon ) )      { m_muon_truthStatus.push_back( truthStatusAcc( *muon ) ); }
  else   { m_muon_truthStatus.push_back(0); }

}

void SSDiMuTree::FillElectronsUser( const xAOD::Electron* electron )
{

  if ( m_debug ) { Info("FillElectronsUser()", "Filling electrons"); }

  // access this info only to fill tag/probe branches

  static SG::AuxElement::Accessor< char > isTruthMatchedAcc("isTruthMatched");
  static SG::AuxElement::ConstAccessor< int >  truthTypeAcc("truthType");
  static SG::AuxElement::Accessor< int >  truthPdgIdAcc("truthPdgId");
  static SG::AuxElement::ConstAccessor< int >  truthOriginAcc("truthOrigin");
  static SG::AuxElement::Accessor< int >  truthStatusAcc("truthStatus");

  static SG::AuxElement::Accessor< int >  bkgTruthTypeAcc("bkgTruthType");
  static SG::AuxElement::Accessor< int >  bkgTruthOriginAcc("bkgTruthOrigin");
  static SG::AuxElement::Accessor< int >  bkgMotherPdgIdAcc("bkgMotherPdgId");
  static SG::AuxElement::Accessor< int >  firstEgMotherTruthTypeAcc("firstEgMotherTruthType");
  static SG::AuxElement::Accessor< int >  firstEgMotherTruthOriginAcc("firstEgMotherTruthOrigin");
  static SG::AuxElement::Accessor< int >  firstEgMotherPdgIdAcc("firstEgMotherPdgId");

  if ( isTruthMatchedAcc.isAvailable( *electron ) )    { m_electron_isTruthMatched.push_back( isTruthMatchedAcc( *electron ) ); }
  else   { m_electron_isTruthMatched.push_back(-1); }
  if ( truthPdgIdAcc.isAvailable( *electron ) )        { m_electron_truthPdgId.push_back( truthPdgIdAcc( *electron ) ); }
  else   { m_electron_truthPdgId.push_back(0); }
  if ( truthTypeAcc.isAvailable( *electron ) )         { m_electron_truthType.push_back( truthTypeAcc( *electron ) ); }
  else   { m_electron_truthType.push_back(-1); }
  if ( truthOriginAcc.isAvailable( *electron ) )       { m_electron_truthOrigin.push_back( truthOriginAcc( *electron ) ); }
  else   { m_electron_truthOrigin.push_back(0); }
  if ( truthStatusAcc.isAvailable( *electron ) )       { m_electron_truthStatus.push_back( truthStatusAcc( *electron ) ); }
  else   { m_electron_truthStatus.push_back(0); }

  if ( bkgTruthTypeAcc.isAvailable( *electron ) )               { m_electron_bkgTruthType.push_back( bkgTruthTypeAcc( *electron ) ); }
  else   { m_electron_bkgTruthType.push_back(0);             }
  if ( bkgTruthOriginAcc.isAvailable( *electron ) )             { m_electron_bkgTruthOrigin.push_back( bkgTruthOriginAcc( *electron ) ); }
  else   { m_electron_bkgTruthOrigin.push_back(0);           }
  if ( bkgMotherPdgIdAcc.isAvailable( *electron ) )             { m_electron_bkgMotherPdgId.push_back( bkgMotherPdgIdAcc( *electron ) ); }
  else   { m_electron_bkgMotherPdgId.push_back(0);           }
  if ( firstEgMotherTruthTypeAcc.isAvailable( *electron ) )     { m_electron_firstEgMotherTruthType.push_back( firstEgMotherTruthTypeAcc( *electron ) ); }
  else   { m_electron_firstEgMotherTruthType.push_back(0);   }
  if ( firstEgMotherTruthOriginAcc.isAvailable( *electron ) )   { m_electron_firstEgMotherTruthOrigin.push_back( firstEgMotherTruthOriginAcc( *electron ) ); }
  else   { m_electron_firstEgMotherTruthOrigin.push_back(0); }
  if ( firstEgMotherPdgIdAcc.isAvailable( *electron ) )         { m_electron_firstEgMotherPdgId.push_back( firstEgMotherPdgIdAcc( *electron ) ); }
  else   { m_electron_firstEgMotherPdgId.push_back(0);       }


}

