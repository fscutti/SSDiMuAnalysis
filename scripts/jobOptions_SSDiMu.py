import ROOT

from xAH_config import xAH_config
import sys, os

sys.path.insert(0, os.environ['ROOTCOREBIN']+"/user_scripts/SSDiLepAnalysis/")

from config_SSDiLep import *

c = xAH_config()

# Here order matters!
#
# NB: here users can update values in the dictionaries before setting them to the algorithm
#
c.setalg("BasicEventSelection", BasicEventSelectionDict)
c.setalg("JetCalibrator", JetCalibratorDict)
c.setalg("MuonCalibrator", MuonCalibratorDict)
c.setalg("ElectronCalibrator", ElectronCalibratorDict)
c.setalg("JetSelector", JetSelectorDict)
c.setalg("MuonSelector", MuonSelectorDict)
c.setalg("ElectronSelector", ElectronSelectorDict)
###->c.setalg("TauSelector", TauSelectorDict)
c.setalg("METConstructor", METConstructorDict)
c.setalg("OverlapRemover", OverlapRemoverDict)

c.setalg("MuonEfficiencyCorrector", MuonEfficiencyCorrectorLooseLooseDict)      
c.setalg("MuonEfficiencyCorrector", MuonEfficiencyCorrectorLooseGradientLooseDict)      
c.setalg("MuonEfficiencyCorrector", MuonEfficiencyCorrectorLooseGradientDict)      
c.setalg("MuonEfficiencyCorrector", MuonEfficiencyCorrectorLooseFixedCutTightTrackOnlyDict)      
c.setalg("MuonEfficiencyCorrector", MuonEfficiencyCorrectorMediumGradientDict)      
c.setalg("MuonEfficiencyCorrector", MuonEfficiencyCorrectorMediumFixedCutTightTrackOnlyDict)      
c.setalg("MuonEfficiencyCorrector", MuonEfficiencyCorrectorMediumGradientLooseDict)      

###c.setalg("ElectronEfficiencyCorrector", ElectronEfficiencyCorrectorDict)
##c.setalg("ElectronEfficiencyCorrector", ElectronEfficiencyCorrectorMediumDict)
###c.setalg("ElectronEfficiencyCorrector", ElectronEfficiencyCorrectorTightDict)

c.setalg("TruthMatchAlgo", TruthMatchAlgoDict)
c.setalg("SSDiLepTreeAlgo", SSDiLepTreeAlgoDict)

