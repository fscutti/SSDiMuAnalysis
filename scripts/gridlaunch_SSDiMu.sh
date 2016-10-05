#!/bin/bash

# check downtime calendar for sites here:
# http://atlas-agis.cern.ch/agis/downtime/calendar/

username=fscutti

prodtag=EXOT12_v3_l3_p2689

#infilepath="/home/fscutti/Analysis/SSDiMuAnalysis/doc/all_DAOD_EXOT12_p2689.txt"
infilepath="/home/fscutti/Analysis/SSDiMuAnalysis/doc/failed_jobs.txt"

configpath="$ROOTCOREBIN/user_scripts/SSDiMuAnalysis/jobOptions_SSDiMu.py"

current_time="$(date +'%d-%m-%Y-%T')"
outdir=output_grid_DxAOD-2016-13TeV_${current_time}

#inSE=INFN-T1_DATADISK,MWT2_DATADISK

destSE=AUSTRALIA-ATLAS_LOCALGROUPDISK

exclSE=RU-Protvino-IHEP

gridDSname="user.${username}.SSDiMu.${prodtag}.%in:name[2]%.%in:name[3]%"

#xAH_run.py -vv --files ${infilepath} --config ${configpath} --inputList --inputDQ2 --submitDir ${outdir} prun --optGridMergeOutput=1 --optGridNFilesPerJob=1.0 --optGridDestSE=${destSE} --optGridOutputSampleName=${gridDSname} --optGridExcludedSite=${exclSE} #--optGridSite=${inSE} 

xAH_run.py -vv --files ${infilepath} --config ${configpath} --inputList --inputDQ2 --submitDir ${outdir} prun --optGridMergeOutput=1 --optGridNFilesPerJob=1.0 --optGridOutputSampleName=${gridDSname} ##--optGridExcludedSite=${exclSE} 





