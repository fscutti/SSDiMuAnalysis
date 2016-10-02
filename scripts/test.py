import ROOT

from xAH_config import xAH_config
c = xAH_config()
c.setalg("BasicEventSelection", {"m_name" : "test", 
                                 "m_useMetaData" : False, 
                                 "m_applyGRLCut" : False, 
                                 "m_applyPrimaryVertexCut" : True,
                                 "m_vertexContainerName" : "PrimaryVertices", 
                                 "m_PVNTrack" : 3,
                                 "m_applyTriggerCut" : True,
                                 ##"m_triggerSelection" : "HLT_j360",
                                 "m_storeTrigDecisions" : True,
                                 })

"""
c.setalg("MuonCalibrator", { "m_name"                : "muonCalib",
                             "m_debug"               : False,
                             "m_inContainerName"     : "Muons",
                             "m_outContainerName"    : "Muons_Calib",
                             "m_inputAlgoSystNames"  : "",
                             "m_outputAlgoSystNames" : "MuonCalibrator_Syst",
                             ##"m_release"             : "Recs2015_11_15",
                             "m_systName"            : "",
                             "m_systVal"             : 0.0,
                           })
"""
"""

c.setalg("MuonSelector" , { 
                     "m_name"                      : "muonSelect_selection",
                     "m_debug"                     :  False,
                     "m_inContainerName"           : "Muons_Calib",
                     "m_outContainerName"          : "Muons_Selected",
                     "m_inputAlgoSystNames"        : "MuonCalibrator_Syst",
                     "m_outputAlgoSystNames"       : "MuonSelector_Syst",
                     "m_createSelectedContainer"   : True,
                     "m_decorateSelectedObjects"   : True,
                     #"m_pass_min"                  : 0,
                     #"m_pass_max"                  : 1000,
                     "m_pT_min"                    : 12e3,
                     #"m_eta_max"                   : 2.5,
                     #"m_muonQualityStr"            : "Loose",
                     #"m_d0sig_max"                 : 10.0,
                     #"m_z0sintheta_max"            : 2.0,
                     #"m_MinIsoWPCut"               : "Loose",
                     #"m_IsoWPList"                 : "Loose,GradientLoose,Gradient,FixedCutLoose,FixedCutTightTrackOnly,UserDefinedCut",
                     #"m_CaloIsoEff"                : "0.1*x",
                     #"m_TrackIsoEff"               : "0.1*x",
                     #"m_CaloBasedIsoType"          : "topoetcone20",
                     #"m_TrackBasedIsoType"         : "ptvarcone30",
                     "m_singleMuTrigChains"        : "HLT_mu50",
                     #"m_diMuTrigChains"            : "",
                   })
"""

c.setalg("TreeAlgo" , { "m_name"                  : "skimmer",
                             "m_debug"                 : False,
                             ##"m_muContainerName"       : "Muons_Calib",
                             #"m_outHistDir"            : True,
                             #"m_evtDetailStr"          : "pileup",
                             "m_trigDetailStr"         : "basic passTriggers",
                             ##"m_muDetailStr"           : "kinematic trigger isolation quality trackparams effSF",
                           })

"""
HTopMultilepTreeAlgoDict = { "m_name"                  : "physics",
                             "m_debug"                 : False,
                             "m_muContainerName"       : "Muons_OR",
                             "m_elContainerName"       : "Electrons_OR",
                             "m_jetContainerName"      : "AntiKt4EMTopoJets_OR",
                             "m_tauContainerName"      : "Taus_OR",
                             "m_lepContainerName"      : "Leptons_OR" ,
                             "m_METContainerName"      : "RefFinal_HTopMultilep",
                             "m_outHistDir"            : True,
                             "m_evtDetailStr"          : "pileup",
                             "m_trigDetailStr"         : "basic passTriggers",
                             "m_muDetailStr"           : "kinematic trigger isolation quality trackparams effSF",
                             "m_elDetailStr"           : "kinematic trigger isolation PID trackparams effSF",
                             "m_tauDetailStr"          : "kinematic",
                             "m_jetDetailStr"          : "kinematic energy flavorTag sfFTagFix77 truth",
                             "m_METDetailStr"          : "all",
                           }
"""



