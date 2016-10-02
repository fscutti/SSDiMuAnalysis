#!/bin/bash

username=fscutti

prodtag=HIGG3D3_v3_p2689

infilepath="/home/fscutti/Analysis/SSDiLepAnalysis/doc/all_DAOD_HIGG3D3_p2689.txt"
#infilepath="/home/fscutti/Analysis/SSDiLepAnalysis/doc/failed_jobs.txt"

configpath="$ROOTCOREBIN/user_scripts/SSDiLepAnalysis/jobOptions_FF.py"

current_time="$(date +'%d-%m-%Y-%T')"
outdir=output_grid_DxAOD-2016-13TeV_${current_time}

#inSE=INFN-T1_DATADISK,MWT2_DATADISK

destSE=AUSTRALIA-ATLAS_LOCALGROUPDISK

exclSE=RU-Protvino-IHEP

gridDSname="user.${username}.SSDiLep.${prodtag}.%in:name[2]%.%in:name[3]%"

#xAH_run.py -vv --files ${infilepath} --config ${configpath} --inputList --inputDQ2 --submitDir ${outdir} prun --optGridMergeOutput=1 --optGridNFilesPerJob=1.0 --optGridDestSE=${destSE} --optGridOutputSampleName=${gridDSname} --optGridExcludedSite=${exclSE} #--optGridSite=${inSE} 

xAH_run.py -vv --files ${infilepath} --config ${configpath} --inputList --inputDQ2 --submitDir ${outdir} prun --optGridMergeOutput=1 --optGridNFilesPerJob=1.0 --optGridOutputSampleName=${gridDSname} ##--optGridExcludedSite=${exclSE} 





