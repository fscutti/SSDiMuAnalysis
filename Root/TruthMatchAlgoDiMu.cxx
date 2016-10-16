/****************************************************************************************
 *
 * An algorithm that performs truth matching and truth-match classification for leptons
 *
 ****************************************************************************************/

// c++ include(s):
#include <iostream>
#include <typeinfo>
#include <sstream>
#include <typeinfo>

// EL include(s):
#include <EventLoop/Job.h>
#include <EventLoop/StatusCode.h>
#include <EventLoop/Worker.h>

// EDM include(s):
#include "xAODEventInfo/EventInfo.h"
#include "xAODEgamma/Electron.h"
#include "xAODEgamma/ElectronContainer.h"
#include "xAODMuon/Muon.h"
#include "xAODMuon/MuonContainer.h"
#include "xAODBase/IParticleContainer.h"
#include "xAODBase/IParticle.h"
#include "xAODBase/ObjectType.h"
#include "xAODTruth/TruthEventContainer.h"
#include "xAODTruth/TruthParticle.h"
#include "xAODTruth/TruthVertex.h"

// package include(s):
#include "SSDiMuAnalysis/TruthMatchAlgoDiMu.h"
#include "xAODAnaHelpers/HelperClasses.h"
#include "xAODAnaHelpers/HelperFunctions.h"
#include <xAODAnaHelpers/tools/ReturnCheck.h>
#include <xAODAnaHelpers/tools/ReturnCheckConfig.h>

// ROOT include(s):
#include "TEnv.h"
#include "TFile.h"
#include "TSystem.h"

// How to retrieve 
// Muon info: https://twiki.cern.ch/twiki/bin/view/Atlas/XAODMuon
// Electron info https://twiki.cern.ch/twiki/bin/view/AtlasProtected/EGammaTruthRun2#egammaTruthParticles


// Another truth matching example
// https://svnweb.cern.ch/trac/atlasphys-hsg8/browser/Physics/Higgs/HSG8/AnalysisCode/multileptons/xAOD/ttHMultiAna/trunk/Root/TruthMatchAlgoDiMu.cxx



// this is needed to distribute the algorithm to the workers
ClassImp(TruthMatchAlgoDiMu)


TruthMatchAlgoDiMu :: TruthMatchAlgoDiMu () :
  m_cutflowHist(nullptr),
  m_cutflowHistW(nullptr)
{
  // Here you put any code for the base initialization of variables,
  // e.g. initialize all pointers to 0.  Note that you should only put
  // the most basic initialization here, since this method will be
  // called on both the submission and the worker node.  Most of your
  // initialization code will go into histInitialize() and
  // initialize().

  Info("TruthMatchAlgoDiMu()", "Calling constructor");

  m_inContainerName_Electrons   = "";
  m_inContainerName_Muons       = "";
  //m_inContainerName_Leptons     = "";

  m_doMuonTruthContMatching     = false;
  m_doMuonTrackMatching         = false;
}

TruthMatchAlgoDiMu::~TruthMatchAlgoDiMu() {}


EL::StatusCode TruthMatchAlgoDiMu :: setupJob (EL::Job& job)
{
  // Here you put code that sets up the job on the submission object
  // so that it is ready to work with your algorithm, e.g. you can
  // request the D3PDReader service or add output files.  Any code you
  // put here could instead also go into the submission script.  The
  // sole advantage of putting it here is that it gets automatically
  // activated/deactivated when you add/remove the algorithm from your
  // job, which may or may not be of value to you.

  Info("setupJob()", "Calling setupJob");

  job.useXAOD ();
  xAOD::Init( "TruthMatchAlgoDiMu" ).ignore(); // call before opening first file

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthMatchAlgoDiMu :: histInitialize ()
{
  // Here you do everything that needs to be done at the very
  // beginning on each worker node, e.g. create histograms and output
  // trees.  This method gets called before any input files are
  // connected.

  Info("histInitialize()", "Calling histInitialize");

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthMatchAlgoDiMu :: fileExecute ()
{
  // Here you do everything that needs to be done exactly once for every
  // single file, e.g. collect a list of all lumi-blocks processed

  Info("fileExecute()", "Calling fileExecute");

  // Get the MetaData tree once a new file is opened,
  // and check if file is from a DxAOD
  //
  TTree *MetaData = dynamic_cast<TTree*>( wk()->inputFile()->Get("MetaData") );
  if ( !MetaData ) {
    Error("fileExecute()", "MetaData not found! Exiting.");
    return EL::StatusCode::FAILURE;
  }
  MetaData->LoadTree(0);

  m_isDerivation = !MetaData->GetBranch("StreamAOD");

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthMatchAlgoDiMu :: changeInput (bool /*firstFile*/)
{
  // Here you do everything you need to do when we change input files,
  // e.g. resetting branch addresses on trees.  If you are using
  // D3PDReader or a similar service this method is not needed.

  Info("changeInput()", "Calling changeInput");

  return EL::StatusCode::SUCCESS;
}


EL::StatusCode TruthMatchAlgoDiMu :: initialize ()
{
  // Here you do everything that you need to do after the first input
  // file has been connected and before the first event is processed,
  // e.g. create additional histograms based on which variables are
  // available in the input files.  You can also create all of your
  // histograms and trees in here, but be aware that this method
  // doesn't get called if no events are processed.  So any objects
  // you create here won't be available in the output if you have no
  // input events.

  Info("initialize()", "Initializing TruthMatchAlgoDiMu Interface...");

  m_event = wk()->xaodEvent();
  m_store = wk()->xaodStore();

  const xAOD::EventInfo* eventInfo(nullptr);
  RETURN_CHECK("TruthMatchAlgoDiMu::execute()", HelperFunctions::retrieve(eventInfo, "EventInfo", m_event, m_store, m_verbose) , "");

  m_isMC = ( eventInfo->eventType( xAOD::EventInfo::IS_SIMULATION ) );

  if ( m_useCutFlow ) {
    TFile *file = wk()->getOutputFile("cutflow");
    m_cutflowHist  = (TH1D*)file->Get("cutflow");
    m_cutflowHistW = (TH1D*)file->Get("cutflow_weighted");
    m_cutflow_bin  = m_cutflowHist->GetXaxis()->FindBin(m_name.c_str());
    m_cutflowHistW->GetXaxis()->FindBin(m_name.c_str());
  }

  Info("initialize()", "Number of events: %lld ", m_event->getEntries() );

  m_numEvent            = 0;
  m_numObject           = 0;
  m_numEventPass        = 0;
  m_weightNumEventPass  = 0;
  m_numObjectPass       = 0;
  
  // signal classification (doubly charged Higgs)
  m_HLpp_DaughtersDecor = nullptr          ; m_HLpp_DaughtersDecor	    = new SG::AuxElement::Decorator< std::vector<int> >("HLpp_Daughters");
  m_HLmm_DaughtersDecor = nullptr          ; m_HLmm_DaughtersDecor	    = new SG::AuxElement::Decorator< std::vector<int> >("HLmm_Daughters");
  m_HRpp_DaughtersDecor = nullptr          ; m_HRpp_DaughtersDecor	    = new SG::AuxElement::Decorator< std::vector<int> >("HRpp_Daughters");
  m_HRmm_DaughtersDecor = nullptr          ; m_HRmm_DaughtersDecor	    = new SG::AuxElement::Decorator< std::vector<int> >("HRmm_Daughters");

  m_isTruthMatchedDecor = nullptr          ; m_isTruthMatchedDecor          = new SG::AuxElement::Decorator< char >("isTruthMatched");	        // has a lepton truth match
  m_truthPdgIdDecor = nullptr	           ; m_truthPdgIdDecor              = new SG::AuxElement::Decorator< int >("truthPdgId");		// pdgId of the match particle
  m_truthTypeDecor = nullptr	           ; m_truthTypeDecor               = new SG::AuxElement::Decorator< int >("truthType"); 	        // type of the parent particle (according to MCTruthClassifier) - this decorates only muons 
  m_truthOriginDecor = nullptr	           ; m_truthOriginDecor             = new SG::AuxElement::Decorator< int >("truthOrigin"); 	        // origin of the parent particle - this decorates only muons 
  m_truthStatusDecor = nullptr	           ; m_truthStatusDecor             = new SG::AuxElement::Decorator< int >("truthStatus"); 	        // status of the match particle

  m_mcEvtWeightAcc = nullptr		   ; m_mcEvtWeightAcc		    = new SG::AuxElement::Accessor< float >("mcEventWeight");
  m_isTruthMatchedAcc = nullptr		   ; m_isTruthMatchedAcc	    = new SG::AuxElement::Accessor< char >("isTruthMatched");
  m_truthPLAcc = nullptr  		   ; m_truthPLAcc		    = new SG::AuxElement::Accessor< TruthLink_t >("truthParticleLink");
  m_truthTypeAcc = nullptr		   ; m_truthTypeAcc		    = new SG::AuxElement::ConstAccessor< int >("truthType");
  m_truthOriginAcc = nullptr		   ; m_truthOriginAcc		    = new SG::AuxElement::ConstAccessor< int >("truthOrigin");
  m_truthMatchProbabilityAcc = nullptr     ; m_truthMatchProbabilityAcc     = new SG::AuxElement::Accessor<float>("truthMatchProbability");

  // initialise MCTruthClassifier
  //
  m_MCTClassifier = new MCTruthClassifier("MCTruthClassifier");
  RETURN_CHECK( "TruthMatchAlgoDiMu::initialize()", m_MCTClassifier->initialize(), "Failed to properly initialize MCTruthClassifier" );

  Info("initialize()", "TruthMatchAlgoDiMu Interface succesfully initialized!" );

  return EL::StatusCode::SUCCESS;
}


EL::StatusCode TruthMatchAlgoDiMu :: execute ()
{
  // Here you do everything that needs to be done on every single
  // events, e.g. read input variables, apply cuts, and fill
  // histograms and trees.  This is where most of your actual analysis
  // code will go.

  if ( m_debug ) { Info("execute()", "Applying TruthMatchAlgoDiMu..."); }

  // retrieve event
  //
  const xAOD::EventInfo* eventInfo(nullptr);
  RETURN_CHECK("TruthMatchAlgoDiMu::execute()", HelperFunctions::retrieve(eventInfo, "EventInfo", m_event, m_store, m_verbose) , "");

  // MC event weight
  //
  float mcEvtWeight(1.0);
  if ( ! (*m_mcEvtWeightAcc).isAvailable( *eventInfo ) ) {
    Error("execute()", "mcEventWeight is not available as decoration! Aborting" );
    return EL::StatusCode::FAILURE;
  }
  mcEvtWeight = (*m_mcEvtWeightAcc)( *eventInfo );

  m_numEvent++;
  
  const xAOD::MuonContainer* inputMuons(nullptr);
  RETURN_CHECK("TruthMatchAlgoDiMu::execute()", HelperFunctions::retrieve(inputMuons, m_inContainerName_Muons, m_event, m_store, m_verbose) ,"");
  if ( m_debug ) { Info( "execute", "Number of muons: %i", static_cast<int>(inputMuons->size()) ); }
  
  const xAOD::ElectronContainer* inputElectrons(nullptr);
  RETURN_CHECK("TruthMatchAlgoDiMu::execute()", HelperFunctions::retrieve(inputElectrons, m_inContainerName_Electrons, m_event, m_store, m_verbose) ,"");
  if ( m_debug ) { Info( "execute", "Number of electrons: %i", static_cast<int>(inputElectrons->size()) ); }
  

  if ( m_isMC ) {
    
    if ( this->applySignalTruthMatching( eventInfo ) != EL::StatusCode::SUCCESS ) {
      Error("execute()", "Problem with applySignalTruthMatching()! Aborting" );
      return EL::StatusCode::FAILURE;
    }
    
    for ( auto muon_itr : *(inputMuons) ) {
      if ( muon_itr->type() == xAOD::Type::Muon ) {
       if ( m_debug ) { Info("execute()"," truth matching reco muon, pT = %2f ", muon_itr->pt() / 1e3 ); }
       
       if ( this->applyTruthMatchingMuon( muon_itr ) != EL::StatusCode::SUCCESS ) {
    	 Error("execute()", "Problem with applyTruthMatchingMuon()! Aborting" );
	 return EL::StatusCode::FAILURE;
       }
      }

    } // end loop over muons
    
    for ( auto el_itr : *(inputElectrons) ) {
      if ( el_itr->type() == xAOD::Type::Electron ) {
       if ( m_debug ) { Info("execute()"," truth matching reco electron, pT = %2f ", el_itr->pt() / 1e3 ); }
      
        if ( this->applyTruthMatchingElectron( el_itr ) != EL::StatusCode::SUCCESS ) {
         Error("execute()", "Problem with applyTruthMatchingElectron()! Aborting" );
         return EL::StatusCode::FAILURE;
        }
      } 
    
    } // end loop over electrons
  
  } // end check isMC


  m_numEventPass++;
  m_weightNumEventPass += mcEvtWeight;

  return EL::StatusCode::SUCCESS;
}

EL::StatusCode TruthMatchAlgoDiMu :: postExecute ()
{
  // Here you do everything that needs to be done after the main event
  // processing.  This is typically very rare, particularly in user
  // code.  It is mainly used in implementing the NTupleSvc.

  if ( m_debug ) { Info("postExecute()", "Calling postExecute"); }

  return EL::StatusCode::SUCCESS;
}

EL::StatusCode TruthMatchAlgoDiMu :: finalize ()
{
  // This method is the mirror image of initialize(), meaning it gets
  // called after the last event has been processed on the worker node
  // and allows you to finish up any objects you created in
  // initialize() before they are written to disk.  This is actually
  // fairly rare, since this happens separately for each worker node.
  // Most of the time you want to do your post-processing on the
  // submission node after all your histogram outputs have been
  // merged.  This is different from histFinalize() in that it only
  // gets called on worker nodes that processed input events.

  Info("finalize()", "Deleting pointers...");

  delete m_HLpp_DaughtersDecor;      m_HLpp_DaughtersDecor = nullptr;
  delete m_HLmm_DaughtersDecor;      m_HLmm_DaughtersDecor = nullptr;
  delete m_HRpp_DaughtersDecor;      m_HRpp_DaughtersDecor = nullptr;
  delete m_HRmm_DaughtersDecor;      m_HRmm_DaughtersDecor = nullptr;

  delete m_isTruthMatchedDecor;      m_isTruthMatchedDecor = nullptr;
  delete m_truthTypeDecor;           m_truthTypeDecor = nullptr;
  delete m_truthPdgIdDecor;          m_truthPdgIdDecor = nullptr;
  delete m_truthOriginDecor;         m_truthOriginDecor = nullptr;
  delete m_truthStatusDecor;         m_truthStatusDecor = nullptr;

  delete m_mcEvtWeightAcc;           m_mcEvtWeightAcc = nullptr;
  delete m_isTruthMatchedAcc;        m_isTruthMatchedAcc = nullptr;
  delete m_truthTypeAcc;             m_truthTypeAcc = nullptr;
  delete m_truthOriginAcc;           m_truthOriginAcc = nullptr;
  delete m_truthPLAcc;               m_truthPLAcc = nullptr;
  delete m_truthMatchProbabilityAcc; m_truthMatchProbabilityAcc = nullptr;

  if ( m_useCutFlow ) {
    Info("finalize()", "Filling cutflow");
    m_cutflowHist ->SetBinContent( m_cutflow_bin, m_numEventPass        );
    m_cutflowHistW->SetBinContent( m_cutflow_bin, m_weightNumEventPass  );
  }

  return EL::StatusCode::SUCCESS;
}

EL::StatusCode TruthMatchAlgoDiMu :: histFinalize ()
{
  // This method is the mirror image of histInitialize(), meaning it
  // gets called after the last event has been processed on the worker
  // node and allows you to finish up any objects you created in
  // histInitialize() before they are written to disk.  This is
  // actually fairly rare, since this happens separately for each
  // worker node.  Most of the time you want to do your
  // post-processing on the submission node after all your histogram
  // outputs have been merged.  This is different from finalize() in
  // that it gets called on all worker nodes regardless of whether
  // they processed input events.

  Info("histFinalize()", "Calling histFinalize");

  return EL::StatusCode::SUCCESS;
}



EL::StatusCode TruthMatchAlgoDiMu ::  applyTruthMatchingElectron ( const xAOD::IParticle* recoPart )
{

  // return immediately if input particle is not an electron
  //
  if ( !( recoPart->type() == xAOD::Type::Electron ) ) {
      Warning("applyTruthMatchingElectron()", "Not passing an electron! Won't try anything");
      return StatusCode::SUCCESS;
  }

  // truth particle types are defined in SSDiMuAnalysis/MCTruthClassifierDefs.h:
  //
  // further explaination can be found in: https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/MCTruthClassifier
  //

  // decorate reconstructed particle with default values
  //
  (*m_isTruthMatchedDecor)( *recoPart )	         = -1;
  (*m_truthPdgIdDecor)( *recoPart )              = 0;
  (*m_truthStatusDecor)( *recoPart )	         = -1;

  // Now try to do the matching
  //
  // For electrons, the link to truth matching particle (and some useful info) is already saved in ElectronCollection
  //
  if ( ! (*m_truthPLAcc).isAvailable( *recoPart ) ) {
     Warning("applyTruthMatchingElectron()", "No link available to truth match for this reco electron. This shouldn't happen. Returning");
     return StatusCode::SUCCESS;
  }
  if ( ! (*m_truthPLAcc)( *recoPart ).isValid() ) {
     Warning("applyTruthMatchingElectron()", "Link to truth match for this reco electron is invalid. This shouldn't happen. Returning");
     return StatusCode::SUCCESS;
  }
  const xAOD::TruthParticle* matchTruthEl = *( (*m_truthPLAcc)(*recoPart) );

  // if there's no matching truth electron, return.
  //
  if ( !matchTruthEl ) {
     Warning( "applyTruthMatchingElectron()", "This reco electron is not matched to a generic truth particle. This shouldn't happen. Returning");
     return StatusCode::SUCCESS;
  }

  // decorate with true if the truth match is an electron
  //
  if ( matchTruthEl->isElectron() ) {
     (*m_isTruthMatchedDecor)( *recoPart ) = 1;
  } else {
     (*m_isTruthMatchedDecor)( *recoPart ) = 0;
  }

  // store the pdgId of the match
  //
  static SG::AuxElement::Accessor< int > pdgIdAcc("pdgId");
  if ( pdgIdAcc.isAvailable( *matchTruthEl ) ) {

    if ( m_debug ) { Info( "applyTruthMatchingElectron()", "decorating truthPdgId with value: %i", matchTruthEl->pdgId() ); }
    (*m_truthPdgIdDecor)( *recoPart ) = matchTruthEl->pdgId();

  }
  // store the status of the match
  //
  static SG::AuxElement::Accessor< int > statusAcc("status");
  if ( statusAcc.isAvailable( *matchTruthEl ) ) {

    if ( m_debug ) { Info( "applyTruthMatchingElectron()", "decorating truthStatus with value: %i", matchTruthEl->status() ); }
    (*m_truthStatusDecor)( *recoPart ) = matchTruthEl->status();

  }
   
  return EL::StatusCode::SUCCESS;
}


EL::StatusCode TruthMatchAlgoDiMu ::  applyTruthMatchingMuon ( const xAOD::IParticle* recoPart )
{

  // return immediately if input particle is not a muon
  //
  if ( !( recoPart->type() == xAOD::Type::Muon ) ) {
    Warning("applyTruthMatchingMuon()", "Not passing a muon! Won't try anything");
    return EL::StatusCode::SUCCESS;
  }

  // Now try to do the matching
  //
  // It can be either done by finding the link to MuonTruthParticles container, or by matching the muon track (default for |eta| < 2.5)
  // See the header file for more info.
  //
  const xAOD::TruthParticleContainer* muonTruthPartContainer(nullptr);
  RETURN_CHECK("TruthMatchAlgoDiMu::applyTruthMatchingMuon()", HelperFunctions::retrieve(muonTruthPartContainer, "MuonTruthParticles", m_event, m_store, m_verbose) , "");
  
  // Use the MuonTruthParticles container to decorate the recoPart with 
  // type and origin from MCTruthClassifier 
  bool useMuonTruthContainer = m_doMuonTruthContMatching;
  
  if ( this->doMuonTruthMatching( recoPart, useMuonTruthContainer ) != EL::StatusCode::SUCCESS ) {
    Error("applyTruthMatchingMuon()", "Problem with doMuonTruthMatching(). Aborting");
    return EL::StatusCode::FAILURE;
  }
  
  return EL::StatusCode::SUCCESS;
}

EL::StatusCode TruthMatchAlgoDiMu :: doMuonTruthMatching ( const xAOD::IParticle* recoPart, bool useTruthContainer)
{
   // decorate reconstructed particle with default values
   //
   (*m_isTruthMatchedDecor)( *recoPart )	  = 0;
   (*m_truthPdgIdDecor)( *recoPart )              = 0;
   (*m_truthStatusDecor)( *recoPart )	          = -1;
   
   if ( useTruthContainer ) {

     (*m_truthTypeDecor)( *recoPart )               = 0; 
     (*m_truthOriginDecor)( *recoPart )             = 0; 
   
   }
   
   
   // get the truth muon matching the reco muon
   //
   const xAOD::TruthParticle* matchTruthMu(nullptr);
   
   if ( ! (*m_truthPLAcc).isAvailable( *recoPart ) ) {
      Warning("doMuonTruthMatching()", "No link available to truth match for this reco muon. This shouldn't happen. Returning");
      return StatusCode::SUCCESS;
   }
   if ( ! (*m_truthPLAcc)( *recoPart ).isValid() ) {
      Warning("doMuonTruthMatching()", "Link to truth match for this reco muon is invalid. This shouldn't happen. Returning");
      return StatusCode::SUCCESS;
   }
   
   matchTruthMu = *( (*m_truthPLAcc)(*recoPart) );

   
   // if there is no matching truth muon, return
   //
   if ( !matchTruthMu ) {
      Warning("doMuonTruthMatching()", "No truth matching for this reco muon. This shouldn't happen. Returning");
      return StatusCode::SUCCESS;
   }
  
   // decorate with this if the truth match is a muon
   // ( should ALWAYS be the case, since the truth we are getting is in the "MuonTruthParticles" container.! )
   //
   if ( matchTruthMu->isMuon() ) {
     (*m_isTruthMatchedDecor)( *recoPart ) = 1;
   } else {
     (*m_isTruthMatchedDecor)( *recoPart ) = 0;
   }
   
   
   
   // store the pdgId of the match
   //
   static SG::AuxElement::Accessor< int > pdgIdAcc("pdgId");
   if ( pdgIdAcc.isAvailable( *matchTruthMu ) ) {
     
     if ( m_debug ) { Info( "doMuonTruthMatching()", "decorating truthPdgId with value: %i", matchTruthMu->pdgId() ); }
     (*m_truthPdgIdDecor)( *recoPart ) = matchTruthMu->pdgId();

   }

   // store the status of the match
   //
   static SG::AuxElement::Accessor< int > statusAcc("status");
   if ( statusAcc.isAvailable( *matchTruthMu ) ) {

     if ( m_debug ) { Info( "doMuonTruthMatching()", "decorating truthStatus with value: %i", matchTruthMu->status() ); }
     (*m_truthStatusDecor)( *recoPart ) = matchTruthMu->status();

   }
   
   if ( useTruthContainer ) {

      // store the type of the match: pass the truth muon type info to the reco muon
      //
      if ( ! (*m_truthTypeAcc).isAvailable( *matchTruthMu ) ) {
        Warning("doMuonTruthMatching()", "No truth type info available for this muon's matching truth particle. This shouldn't happen. Returning");
        return StatusCode::SUCCESS;
      }
      int truthMatchType = (*m_truthTypeAcc)(*matchTruthMu);
      (*m_truthTypeDecor)( *recoPart ) = truthMatchType;
      
      // store the pdgId of the parent particle of the match: pass the truth muon origin info to the reco muon
      //
      if ( ! (*m_truthOriginAcc).isAvailable( *matchTruthMu ) ) {
        Warning("doMuonTruthMatching()", "No truth origin info available for this muon's matching truth particle. This shouldn't happen. Returning");
        return StatusCode::SUCCESS;
      }
      int truthMatchOrigin = (*m_truthOriginAcc)(*matchTruthMu);
      (*m_truthOriginDecor)( *recoPart ) = truthMatchOrigin;
      return EL::StatusCode::SUCCESS;

   } 

  return EL::StatusCode::SUCCESS;
}

EL::StatusCode TruthMatchAlgoDiMu :: applySignalTruthMatching ( const xAOD::EventInfo* eventInfo )
{

  (*m_HLpp_DaughtersDecor)( *eventInfo ) = std::vector<int>();
  (*m_HLmm_DaughtersDecor)( *eventInfo ) = std::vector<int>();
  (*m_HRpp_DaughtersDecor)( *eventInfo ) = std::vector<int>();
  (*m_HRmm_DaughtersDecor)( *eventInfo ) = std::vector<int>();
  
  (*m_HLpp_DaughtersDecor)( *eventInfo ).push_back(0);
  (*m_HLmm_DaughtersDecor)( *eventInfo ).push_back(0);
  (*m_HRpp_DaughtersDecor)( *eventInfo ).push_back(0);
  (*m_HRmm_DaughtersDecor)( *eventInfo ).push_back(0);

  const xAOD::TruthParticleContainer* TruthPartContainer(nullptr);
  RETURN_CHECK("TruthMatchAlgoDiMu::applyTruthMatchingMuon()", HelperFunctions::retrieve(TruthPartContainer, "TruthParticles", m_event, m_store, m_verbose) , "");

  //std::cout << "signal truth matching " << &TruthPartContainer << std::endl;

  for ( auto truth_itr : *(TruthPartContainer) ) {
    //std::cout << "inside the loop " << &truth_itr << std::endl;
    
    //std::cout << "truth_itr->status() " << truth_itr->status() << std::endl;
    
    if( truth_itr->status() == 62 ) {
       
       std::vector<int> bosonVect;
       
       if ( truth_itr->hasDecayVtx() ) {
         if ( truth_itr->decayVtx()->nOutgoingParticles() > 0) {
           
           const std::vector< ElementLink<xAOD::TruthParticleContainer> >& outPart = truth_itr->decayVtx()->outgoingParticleLinks();
           
           
           for(unsigned int k=0; k<outPart.size(); ++k){
             if ( ! (outPart[k]).isValid() ) {
               std::cout << " out particle not valid " << std::endl;
               continue;
             }
             
             const xAOD::TruthParticle* kid = *(outPart[k]);
             
             bosonVect.push_back(kid->pdgId());
             
           }
           
           if ( truth_itr->pdgId() == 9900041  ) { (*m_HLpp_DaughtersDecor)( *eventInfo ) = bosonVect ; }
           if ( truth_itr->pdgId() == -9900041 ) { (*m_HLmm_DaughtersDecor)( *eventInfo ) = bosonVect ; }
           if ( truth_itr->pdgId() == 9900042  ) { (*m_HRpp_DaughtersDecor)( *eventInfo ) = bosonVect ; }
           if ( truth_itr->pdgId() == -9900042 ) { (*m_HRmm_DaughtersDecor)( *eventInfo ) = bosonVect ; }
           else { continue; } 
           
         }
         else{
           std::cout << " no outgoing particles " << std::endl;
         }
       }
       else{
         std::cout << " no decay vtx " << std::endl;
       }
     }
   }
  
  return EL::StatusCode::SUCCESS;
}
