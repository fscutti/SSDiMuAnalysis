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
  
  /* 
  m_tree->Branch("ystar",             &m_ystar, "ystar/F");
  m_tree->Branch("categoryFlag",      &m_categoryFlag, "categoryFlag/i");
  m_tree->Branch("isSS01",            &m_isSS01, "isSS01/I");
  m_tree->Branch("isSS12",            &m_isSS12, "isSS12/I");

  m_tree->Branch("MMWeight",          &m_MMWeight);
  m_tree->Branch("FFWeight",          &m_FFWeight);
  m_tree->Branch("QMisIDWeight",      &m_QMisIDWeight);

  m_tree->Branch("mll01",             &m_mll01, "mll01/F");
  m_tree->Branch("mll02",             &m_mll02, "mll02/F");
  m_tree->Branch("mll12",             &m_mll12, "mll12/F");
  m_tree->Branch("mlll012",           &m_mlll012, "mlll012/F");

  m_tree->Branch("mOSPair01",         &m_mOSPair01, "mOSPair01/F");
  m_tree->Branch("mOSPair02",         &m_mOSPair02, "mOSPair02/F");
  m_tree->Branch("isOSPairSF01",      &m_isOSPairSF01, "isOSPairSF01/I");
  m_tree->Branch("isOSPairSF02",      &m_isOSPairSF02, "isOSPairSF02/I");

  m_tree->Branch("mT_lep0MET",        &m_mT_lep0MET, "mT_lep0MET/F");
  m_tree->Branch("mT_lep1MET",        &m_mT_lep1MET, "mT_lep1MET/F");

  m_tree->Branch("HT",                &m_HT, "m_HT/F");

  m_tree->Branch("is_T_T",            &m_is_T_T, "is_T_T/I");
  m_tree->Branch("is_T_AntiT",        &m_is_T_AntiT, "is_T_AntiT/I");
  m_tree->Branch("is_AntiT_T",        &m_is_AntiT_T, "is_AntiT_T/I");
  m_tree->Branch("is_AntiT_AntiT",    &m_is_AntiT_AntiT, "is_AntiT_AntiT/I");

  m_tree->Branch("is_T_MAntiT",       &m_is_T_MAntiT, "is_T_MAntiT/I");
  m_tree->Branch("is_MAntiT_T",       &m_is_MAntiT_T, "is_MAntiT_T/I");
  m_tree->Branch("is_MAntiT_MAntiT",  &m_is_MAntiT_MAntiT, "is_MAntiT_MAntiT/I");

  m_tree->Branch("is_M_M",            &m_is_M_M,   "is_M_M/I");
  m_tree->Branch("is_T_AntiM",        &m_is_T_AntiM,   "is_T_AntiM/I");
  m_tree->Branch("is_AntiM_T",        &m_is_AntiM_T,   "is_AntiM_T/I");
  m_tree->Branch("is_M_AntiM",        &m_is_M_AntiM,   "is_M_AntiM/I");
  m_tree->Branch("is_AntiM_M",        &m_is_AntiM_M,   "is_AntiM_M/I");
  m_tree->Branch("is_AntiM_AntiM",    &m_is_AntiM_AntiM,   "is_AntiM_AntiM/I");

  m_tree->Branch("is_Tel_AntiTmu",    &m_is_Tel_AntiTmu, "is_Tel_AntiTmu/I");
  m_tree->Branch("is_AntiTel_Tmu",    &m_is_AntiTel_Tmu, "is_AntiTel_Tmu/I");
  m_tree->Branch("is_Tmu_AntiTel",    &m_is_Tmu_AntiTel, "is_Tmu_AntiTel/I");
  m_tree->Branch("is_AntiTmu_Tel",    &m_is_AntiTmu_Tel, "is_AntiTmu_Tel/I");

  m_tree->Branch("is_Tel_MAntiTmu",   &m_is_Tel_MAntiTmu, "is_Tel_MAntiTmu/I");
  m_tree->Branch("is_MAntiTel_Tmu",   &m_is_MAntiTel_Tmu, "is_MAntiTel_Tmu/I");
  m_tree->Branch("is_Tmu_MAntiTel",   &m_is_Tmu_MAntiTel, "is_Tmu_MAntiTel/I");
  m_tree->Branch("is_MAntiTmu_Tel",   &m_is_MAntiTmu_Tel, "is_MAntiTmu_Tel/I");

  m_tree->Branch("is_Mel_AntiMmu",    &m_is_Mel_AntiMmu, "is_Mel_AntiMmu/I");
  m_tree->Branch("is_AntiMel_Mmu",    &m_is_AntiMel_Mmu, "is_AntiMel_Mmu/I");
  m_tree->Branch("is_Mmu_AntiMel",    &m_is_Mmu_AntiMel, "is_Mmu_AntiMel/I");
  m_tree->Branch("is_AntiMmu_Mel",    &m_is_AntiMmu_Mel, "is_AntiMmu_Mel/I");

  m_tree->Branch("is_Tel_AntiMmu",    &m_is_Tel_AntiMmu, "is_Tel_AntiMmu/I");
  m_tree->Branch("is_AntiMel_Tmu",    &m_is_AntiMel_Tmu, "is_AntiMel_Tmu/I");
  m_tree->Branch("is_Tmu_AntiMel",    &m_is_Tmu_AntiMel, "is_Tmu_AntiMel/I");
  m_tree->Branch("is_AntiMmu_Tel",    &m_is_AntiMmu_Tel, "is_AntiMmu_Tel/I");

  m_tree->Branch("isNonTightEvent",   &m_isNonTightEvent,    "isNonTightEvent/I");
  m_tree->Branch("isProbeElEvent",    &m_isProbeElEvent,     "isProbeElEvent/I");
  m_tree->Branch("isProbeMuEvent",    &m_isProbeMuEvent,     "isProbeMuEvent/I");

  if ( m_isMC ) {
    m_tree->Branch("weight_lepton_trig_HTop", &m_weight_lepton_trig_HTop);
    m_tree->Branch("weight_lepton_reco_HTop", &m_weight_lepton_reco_HTop);
    m_tree->Branch("weight_lepton_iso_HTop",  &m_weight_lepton_iso_HTop);
    m_tree->Branch("weight_lepton_ID_HTop",   &m_weight_lepton_ID_HTop);
    m_tree->Branch("weight_lepton_TTVA_HTop", &m_weight_lepton_TTVA_HTop);
    m_tree->Branch("weight_jet_JVT_HTop",     &m_weight_jet_JVT_HTop);
  }
  */
}

/*
void SSDiMuTree::AddTriggerUser(const std::string detailStrUser)
{

  // to get rid of warning when detailString is not used
  if ( m_debug ) { Info("AddTriggerUser()", "Adding branches w/ detail: %s", detailStrUser.c_str()); }

  // trigger variables
}
*/

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
  //m_tree->Branch("muon_isTightSelected",               &m_muon_isTight);
  //m_tree->Branch("muon_isMediumSelected",              &m_muon_isMedium);
  //m_tree->Branch("muon_isTag",                         &m_muon_isTag);
  //m_tree->Branch("muon_isOS",                          &m_muon_isOS);
  //m_tree->Branch("muon_isClosestSS",                   &m_muon_isClosestSS);
  m_tree->Branch("muon_isTruthMatchedToMuon",          &m_muon_isTruthMatched);
  m_tree->Branch("muon_isChFlip",	               &m_muon_isChFlip);
  m_tree->Branch("muon_isBrem",	                       &m_muon_isBrem);
  m_tree->Branch("muon_truthType",                     &m_muon_truthType);
  m_tree->Branch("muon_truthPdgId",                    &m_muon_truthPdgId);
  m_tree->Branch("muon_truthOrigin",                   &m_muon_truthOrigin);
  m_tree->Branch("muon_truthStatus",                   &m_muon_truthStatus);
  m_tree->Branch("muon_ancestorTruthType",             &m_muon_ancestorTruthType);
  m_tree->Branch("muon_ancestorTruthPdgId",            &m_muon_ancestorTruthPdgId);
  m_tree->Branch("muon_ancestorTruthOrigin",           &m_muon_ancestorTruthOrigin);
  m_tree->Branch("muon_ancestorTruthStatus",           &m_muon_ancestorTruthStatus);
}

void SSDiMuTree::AddElectronsUser(const std::string detailStrUser)
{

  // to get rid of warning when detailString is not used
  if ( m_debug ) { Info("AddElectronsUser()", "Adding branches w/ detail: %s", detailStrUser.c_str()); }

  // electron variables
  //m_tree->Branch("el_crack",                           &m_electron_crack);
  //m_tree->Branch("el_isTightSelected",                 &m_electron_isTight);
  //m_tree->Branch("el_isMediumSelected",                &m_electron_isMedium);
  //m_tree->Branch("el_isTag",                           &m_electron_isTag);
  //m_tree->Branch("el_isOS",	                       &m_electron_isOS);
  //m_tree->Branch("el_isClosestSS",                     &m_electron_isClosestSS);
  m_tree->Branch("el_isTruthMatchedToElectron",        &m_electron_isTruthMatched);
  m_tree->Branch("el_isChFlip",                        &m_electron_isChFlip);
  m_tree->Branch("el_isBrem",                          &m_electron_isBrem);
  m_tree->Branch("el_truthType",	               &m_electron_truthType);
  m_tree->Branch("el_truthPdgId",	               &m_electron_truthPdgId);
  m_tree->Branch("el_truthOrigin",                     &m_electron_truthOrigin);
  m_tree->Branch("el_truthStatus",                     &m_electron_truthStatus);
  m_tree->Branch("el_ancestorTruthType",	       &m_electron_ancestorTruthType);
  m_tree->Branch("el_ancestorTruthPdgId",	       &m_electron_ancestorTruthPdgId);
  m_tree->Branch("el_ancestorTruthOrigin",	       &m_electron_ancestorTruthOrigin);
  m_tree->Branch("el_ancestorTruthStatus",	       &m_electron_ancestorTruthStatus);
}

//void SSDiMuTree::AddTausUser(const std::string detailStrUser)
//{

//  // to get rid of warning when detailString is not used
//  if ( m_debug ) { Info("AddTausUser()", "Adding branches w/ detail: %s", detailStrUser.c_str()); }

//  m_tree->Branch("tau_isBDTTight",	                &m_tau_isBDTTight );
//}


/*
void SSDiMuTree::AddMETUser(const std::string detailStrUser)
{

  // to get rid of warning when detailString is not used
  if ( m_debug ) { Info("AddMETUser()", "Adding branches w/ detail: %s", detailStrUser.c_str()); }

}
*/

void SSDiMuTree::ClearEventUser()
{/*
  m_MMWeight.clear();
  m_FFWeight.clear();
  m_QMisIDWeight.clear();
  if ( m_isMC ) {
    m_weight_lepton_trig_HTop.clear();
    m_weight_lepton_trig_HTop.clear();
    m_weight_lepton_reco_HTop.clear();
    m_weight_lepton_iso_HTop.clear();
    m_weight_lepton_ID_HTop.clear();
    m_weight_lepton_TTVA_HTop.clear();
    m_weight_jet_JVT_HTop.clear();
  }*/
  if ( m_isMC ) {
    m_HLpp_Daughters.clear();
    m_HLmm_Daughters.clear();
    m_HRpp_Daughters.clear();
    m_HRmm_Daughters.clear();
  }
}

/*
void SSDiMuTree::ClearTriggerUser() {}
*/

void SSDiMuTree::ClearMuonsUser()
{
  // muon variables
  //m_muon_isTight.clear();
  //m_muon_isMedium.clear();
  //m_muon_isOS.clear();
  //m_muon_isClosestSS.clear();
  //m_muon_isTag.clear();
  m_muon_isTruthMatched.clear();
  m_muon_isChFlip.clear();
  m_muon_isBrem.clear();
  m_muon_truthType.clear();
  m_muon_truthPdgId.clear();
  m_muon_truthOrigin.clear();
  m_muon_truthStatus.clear();
  m_muon_ancestorTruthType.clear();
  m_muon_ancestorTruthPdgId.clear();
  m_muon_ancestorTruthOrigin.clear();
  m_muon_ancestorTruthStatus.clear();
}

void SSDiMuTree::ClearElectronsUser()
{
  // electron variables
  //m_electron_crack.clear();
  //m_electron_isTight.clear();
  //m_electron_isMedium.clear();
  //m_electron_isOS.clear();
  //m_electron_isClosestSS.clear();
  //m_electron_isTag.clear();
  m_electron_isTruthMatched.clear();
  m_electron_isChFlip.clear();
  m_electron_isBrem.clear();
  m_electron_truthType.clear();
  m_electron_truthPdgId.clear();
  m_electron_truthOrigin.clear();
  m_electron_truthStatus.clear();
  m_electron_ancestorTruthType.clear();
  m_electron_ancestorTruthPdgId.clear();
  m_electron_ancestorTruthOrigin.clear();
  m_electron_ancestorTruthStatus.clear();
}

void SSDiMuTree::ClearJetsUser( const std::string jetName )
{
  if ( m_debug ) { Info("ClearJetsUser()", "Clearing jet branches - Jet name: %s", jetName.c_str()); }

  // jet variables
  m_jet_m.clear();
  if ( m_debug ) { Info("ClearJetsUser()", "done with clearing"); }

}

//void SSDiMuTree::ClearTausUser()
//{

// if ( m_debug ) { Info("ClearTausUser()", "Clearing tau branches"); }

//  m_tau_isBDTTight.clear();
//}

/*
void SSDiMuTree::ClearMETUser() {}
*/

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

/*
void SSDiMuTree::FillTriggerUser( const xAOD::EventInfo* eventInfo ) { }
*/

void SSDiMuTree::FillJetsUser( const xAOD::Jet* jet, const std::string jetName )
{
  if ( m_debug ) { Info("FillJetsUser()", "Filling jets - Jet name: %s", jetName.c_str()); }

  m_jet_m.push_back( jet->m() );
}

void SSDiMuTree::FillMuonsUser( const xAOD::Muon* muon, const std::string /*muonName = "muon"*/  )
{

  if ( m_debug ) { Info("FillMuonsUser()", "Filling muons"); }

  // access this info only to fill tag/probe branches

  //static SG::AuxElement::Accessor<float> d0SigAcc ("d0sig");
  //float d0_significance =  ( d0SigAcc.isAvailable( *muon ) ) ? fabs( d0SigAcc( *muon ) ) : -1.0;
  //static SG::AuxElement::Accessor<float> z0sinthetaAcc("z0sintheta");
  //float z0sintheta =  ( z0sinthetaAcc.isAvailable( *muon ) ) ? z0sinthetaAcc( *muon ) : -999.0;
  //static SG::AuxElement::Accessor<char> isIsoLooseAcc ("isIsolated_Loose");
  //static SG::AuxElement::Accessor<char> isIsoFixedCutTightTrackOnlyAcc ("isIsolated_FixedCutTightTrackOnly");
  //static SG::AuxElement::Accessor< char > isTightAcc("isTight");
  //static SG::AuxElement::Accessor< char > isMediumAcc("isMedium");
  //static SG::AuxElement::Accessor< char > isOSlepAcc("isOSlep");
  //static SG::AuxElement::Accessor< char > isClosestSSlepAcc("isClosestSSlep");
  //static SG::AuxElement::Accessor< char > isTagAcc("isTag");
  static SG::AuxElement::Accessor< char > isTruthMatchedAcc("isTruthMatched");
  static SG::AuxElement::Accessor< char > isChFlipAcc("isChFlip");
  static SG::AuxElement::Accessor< char > isBremAcc("isBrem");
  static SG::AuxElement::ConstAccessor< int >  truthTypeAcc("truthType");
  static SG::AuxElement::Accessor< int >  truthPdgIdAcc("truthPdgId");
  static SG::AuxElement::ConstAccessor< int >  truthOriginAcc("truthOrigin");
  static SG::AuxElement::Accessor< int >  truthStatusAcc("truthStatus");
  static SG::AuxElement::Accessor< int >  ancestorTruthTypeAcc("ancestorTruthType");
  static SG::AuxElement::Accessor< int >  ancestorTruthPdgIdAcc("ancestorTruthPdgId");
  static SG::AuxElement::Accessor< int >  ancestorTruthOriginAcc("ancestorTruthOrigin");
  static SG::AuxElement::Accessor< int >  ancestorTruthStatusAcc("ancestorTruthStatus");

  //if (  isTightAcc.isAvailable( *muon ) )         {  m_muon_isTight.push_back( isTightAcc( *muon ) ); }
  //else {  m_muon_isTight.push_back(-1); }
  //if (  isMediumAcc.isAvailable( *muon ) )         {  m_muon_isMedium.push_back( isMediumAcc( *muon ) ); }
  //else {  m_muon_isMedium.push_back(-1); }
  //if (  isOSlepAcc.isAvailable( *muon ) )         { m_muon_isOS.push_back( isOSlepAcc( *muon ) ); }
  //else  { m_muon_isOS.push_back(-1); }
  //if (  isClosestSSlepAcc.isAvailable( *muon ) )  { m_muon_isClosestSS.push_back( isClosestSSlepAcc( *muon ) ); }
  //else  { m_muon_isClosestSS.push_back(-1); }
  if ( isTruthMatchedAcc.isAvailable( *muon ) )   { m_muon_isTruthMatched.push_back( isTruthMatchedAcc( *muon ) ); }
  else   { m_muon_isTruthMatched.push_back(-1); }
  if ( isChFlipAcc.isAvailable( *muon ) )         { m_muon_isChFlip.push_back( isChFlipAcc( *muon ) ); }
  else   { m_muon_isChFlip.push_back(-1); }
  if ( isBremAcc.isAvailable( *muon ) )           { m_muon_isBrem.push_back( isBremAcc( *muon ) ); }
  else   { m_muon_isBrem.push_back(-1); }
   if ( truthPdgIdAcc.isAvailable( *muon ) )      { m_muon_truthPdgId.push_back( truthPdgIdAcc( *muon ) ); }
  else   { m_muon_truthPdgId.push_back(0); }
  if ( truthTypeAcc.isAvailable( *muon ) )        { m_muon_truthType.push_back( truthTypeAcc( *muon ) ); }
  else   { m_muon_truthType.push_back(-1); }
  if ( truthOriginAcc.isAvailable( *muon ) )      { m_muon_truthOrigin.push_back( truthOriginAcc( *muon ) ); }
  else   { m_muon_truthOrigin.push_back(0); }
  if ( truthStatusAcc.isAvailable( *muon ) )      { m_muon_truthStatus.push_back( truthStatusAcc( *muon ) ); }
  else   { m_muon_truthStatus.push_back(0); }
  if ( ancestorTruthTypeAcc.isAvailable( *muon ) )      { m_muon_ancestorTruthType.push_back( ancestorTruthTypeAcc( *muon ) ); }
  else   { m_muon_ancestorTruthType.push_back(0); }
  if ( ancestorTruthPdgIdAcc.isAvailable( *muon ) )     { m_muon_ancestorTruthPdgId.push_back( ancestorTruthPdgIdAcc( *muon ) ); }
  else   { m_muon_ancestorTruthPdgId.push_back(0); }
  if ( ancestorTruthOriginAcc.isAvailable( *muon ) )    { m_muon_ancestorTruthOrigin.push_back( ancestorTruthOriginAcc( *muon ) ); }
  else   { m_muon_ancestorTruthOrigin.push_back(0); }
  if ( ancestorTruthStatusAcc.isAvailable( *muon ) )    { m_muon_ancestorTruthStatus.push_back( ancestorTruthStatusAcc( *muon ) ); }
  else   { m_muon_ancestorTruthStatus.push_back(0); }

}

void SSDiMuTree::FillElectronsUser( const xAOD::Electron* electron )
{

  if ( m_debug ) { Info("FillElectronsUser()", "Filling electrons"); }

  // access this info only to fill tag/probe branches

  //static SG::AuxElement::Accessor<float> d0SigAcc ("d0sig");
  //float d0_significance =  ( d0SigAcc.isAvailable( *electron ) ) ? fabs( d0SigAcc( *electron ) ) : -1.0;
  //static SG::AuxElement::Accessor<float> z0sinthetaAcc("z0sintheta");
  //float z0sintheta =  ( z0sinthetaAcc.isAvailable( *electron ) ) ? z0sinthetaAcc( *electron ) : -999.0;
  //static SG::AuxElement::Accessor<char> LHLooseAcc ("LHLoose");
  //static SG::AuxElement::Accessor<char> LHMediumAcc ("LHMedium");
  //static SG::AuxElement::Accessor<char> LHTightAcc ("LHTight");
  //static SG::AuxElement::Accessor<char> EMLooseAcc ("Loose");
  //static SG::AuxElement::Accessor<char> EMMediumAcc ("Medium");
  //static SG::AuxElement::Accessor<char> EMTightAcc ("Tight");
  //static SG::AuxElement::Accessor<char> isIsoLooseAcc ("isIsolated_Loose");
  //static SG::AuxElement::Accessor<char> isIsoFixedCutTightAcc ("isIsolated_FixedCutTight");

  //static SG::AuxElement::Accessor< char > isTightAcc("isTight");
  //static SG::AuxElement::Accessor< char > isMediumAcc("isMedium");
  //jstatic SG::AuxElement::Accessor< char > isOSlepAcc("isOSlep");
  //static SG::AuxElement::Accessor< char > isClosestSSlepAcc("isClosestSSlep");
  //static SG::AuxElement::Accessor< char > isTagAcc("isTag");

  static SG::AuxElement::Accessor< char > isTruthMatchedAcc("isTruthMatched");
  static SG::AuxElement::Accessor< char > isChFlipAcc("isChFlip");
  static SG::AuxElement::Accessor< char > isBremAcc("isBrem");
  static SG::AuxElement::ConstAccessor< int >  truthTypeAcc("truthType");
  static SG::AuxElement::Accessor< int >  truthPdgIdAcc("truthPdgId");
  static SG::AuxElement::ConstAccessor< int >  truthOriginAcc("truthOrigin");
  static SG::AuxElement::Accessor< int >  truthStatusAcc("truthStatus");
  static SG::AuxElement::Accessor< int >  ancestorTruthTypeAcc("ancestorTruthType");
  static SG::AuxElement::Accessor< int >  ancestorTruthPdgIdAcc("ancestorTruthPdgId");
  static SG::AuxElement::Accessor< int >  ancestorTruthOriginAcc("ancestorTruthOrigin");
  static SG::AuxElement::Accessor< int >  ancestorTruthStatusAcc("ancestorTruthStatus");

  //float calo_eta = ( electron->caloCluster() ) ? electron->caloCluster()->etaBE(2) : -999.0;

  //if ( electron->caloCluster() ) {
  //  if ( fabs( calo_eta ) > 1.37 && fabs( calo_eta ) < 1.52 ) {
  //    m_electron_crack.push_back(1);
  //  } else {
  //    m_electron_crack.push_back(0);
  //  }
  //} else {
  //  m_electron_crack.push_back(-1);
  //}

  //if (  isTightAcc.isAvailable( *electron ) )          {  m_electron_isTight.push_back( isTightAcc( *electron ) ); }
  //else {  m_electron_isTight.push_back(-1); }
  //if (  isMediumAcc.isAvailable( *electron ) )         {  m_electron_isMedium.push_back( isMediumAcc( *electron ) ); }
  //else {  m_electron_isMedium.push_back(-1); }
  //if (  isOSlepAcc.isAvailable( *electron ) )          { m_electron_isOS.push_back( isOSlepAcc( *electron ) ); }
  //jelse  { m_electron_isOS.push_back(-1); }
  //if (  isClosestSSlepAcc.isAvailable( *electron ) )   { m_electron_isClosestSS.push_back( isClosestSSlepAcc( *electron ) ); }
  //else  { m_electron_isClosestSS.push_back(-1); }
  if ( isTruthMatchedAcc.isAvailable( *electron ) )    { m_electron_isTruthMatched.push_back( isTruthMatchedAcc( *electron ) ); }
  else   { m_electron_isTruthMatched.push_back(-1); }
  if ( isChFlipAcc.isAvailable( *electron ) )          { m_electron_isChFlip.push_back( isChFlipAcc( *electron ) ); }
  else   { m_electron_isChFlip.push_back(-1); }
  if ( isBremAcc.isAvailable( *electron ) )            { m_electron_isBrem.push_back( isBremAcc( *electron ) ); }
  else   { m_electron_isBrem.push_back(-1); }
  if ( truthPdgIdAcc.isAvailable( *electron ) )        { m_electron_truthPdgId.push_back( truthPdgIdAcc( *electron ) ); }
  else   { m_electron_truthPdgId.push_back(0); }
  if ( truthTypeAcc.isAvailable( *electron ) )         { m_electron_truthType.push_back( truthTypeAcc( *electron ) ); }
  else   { m_electron_truthType.push_back(-1); }
  if ( truthOriginAcc.isAvailable( *electron ) )       { m_electron_truthOrigin.push_back( truthOriginAcc( *electron ) ); }
  else   { m_electron_truthOrigin.push_back(0); }
  if ( truthStatusAcc.isAvailable( *electron ) )       { m_electron_truthStatus.push_back( truthStatusAcc( *electron ) ); }
  else   { m_electron_truthStatus.push_back(0); }
  if ( ancestorTruthTypeAcc.isAvailable( *electron ) )      { m_electron_ancestorTruthType.push_back( ancestorTruthTypeAcc( *electron ) ); }
  else   { m_electron_ancestorTruthType.push_back(0); }
  if ( ancestorTruthPdgIdAcc.isAvailable( *electron ) )     { m_electron_ancestorTruthPdgId.push_back( ancestorTruthPdgIdAcc( *electron ) ); }
  else   { m_electron_ancestorTruthPdgId.push_back(0); }
  if ( ancestorTruthOriginAcc.isAvailable( *electron ) )    { m_electron_ancestorTruthOrigin.push_back( ancestorTruthOriginAcc( *electron ) ); }
  else   { m_electron_ancestorTruthOrigin.push_back(0); }
  if ( ancestorTruthStatusAcc.isAvailable( *electron ) )    { m_electron_ancestorTruthStatus.push_back( ancestorTruthStatusAcc( *electron ) ); }
  else   { m_electron_ancestorTruthStatus.push_back(0); }

}

//void SSDiMuTree::FillTausUser( const xAOD::TauJet* tau )
//{

//  if ( m_debug ) { Info("FillTausUser()", "Filling taus"); }

//  static SG::AuxElement::Accessor< char > isTauBDTTightAcc("isTauBDTTight");

//  if ( isTauBDTTightAcc.isAvailable( *tau ) ) { m_tau_isBDTTight.push_back( isTauBDTTightAcc( *tau ) ); }
//  else { m_tau_isBDTTight.push_back(-1); }

//}

/*
void SSDiMuTree::FillMETUser( const xAOD::MissingETContainer* met ) {}
*/

