import FWCore.ParameterSet.Config as cms
from FWCore.ParameterSet.VarParsing import VarParsing
from os.path import basename

#####################
# Options
#
#####################
options = VarParsing ('python')

options.register('nEventsSample',
                 100,
                 VarParsing.multiplicity.singleton,
                 VarParsing.varType.int,
                 "Total number of events in dataset for event weight calculation.")
## 'maxEvents' is already registered by the Framework, changing default value
options.setDefault('maxEvents', 100)

options.parseArguments()

outName = options.outputFile
print "Default output name: " + outName
if "output" in outName: # if an input file name is specified, event weights can be determined
    outName = "out_" + basename(options.inputFiles[0])
    print "Output root file name: " + outName
else:
    options.inputFiles = "file:GGJets_M-1000To2000_Pt-50_13TeV-sherpa.root"
#    outName = "ExoDiphotonAnalyzer.root"


#####################
# Process Definition
#
#####################
process = cms.Process("Demo")
process.load("FWCore.MessageService.MessageLogger_cfi")


#####################
# maxEvents
#
#####################
# process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32( options.maxEvents ) )

#####################
# Input
#
#####################
process.source = cms.Source("PoolSource",

    fileNames = cms.untracked.vstring(
        options.inputFiles
        #'file:/uscms/home/cuperez/nobackup/tribosons/CMSSW_10_2_8/src/GGGJets_TuneCUETP8M1_13TeV_madgraphMLM_pythia8_spring.root'
	#'file:/uscms/home/cuperez/nobackup/tribosons/Triphoton-Dev/CMSSW_10_6_12/src/datasets/GGGJets_Pt-15_13TeV-sherpa__25435464-A08F-B24F-8015-50F0ACB272A4.root'
    #'file:../../../SamplesSubsets/GGGJets_Pt-15_13TeV-sherpa_evt17999.root' #old download
    #'file:../../../SamplesSubsets/GGJets_Pt-15_13TeV-sherpa_evt22000.root' #old download
    #'file:../../../SamplesSubsets/GGGJets_TuneCUETP8M1_13TeV_madgraphMLM_pythia8_evt13433.root'
    )

)

#####################
# Output Filename
#
#####################
process.TFileService = cms.Service("TFileService",
                fileName = cms.string(outName))
                # fileName = cms.string("DemoTriphotonInfo.root")
                # fileName = cms.string("TriphotonBasicNtuples.root")
                # fileName = cms.string("GGJetsBasicNtuples.root")
                # fileName = cms.string("DemoTriphotonInfo.root")

################
# EGM Tools
#
################
# from EgammaUser.EgammaPostRecoTools import setupEgammaPostRecoSeq
from RecoEgamma.EgammaTools.EgammaPostRecoTools import setupEgammaPostRecoSeq
setupEgammaPostRecoSeq(process,
                       runVID=True,
                       #era='2018-Prompt',
                       era='2017-Nov17ReReco',
                       phoIDModules=['RecoEgamma.PhotonIdentification.Identification.mvaPhotonID_Fall17_94X_V2_cff',
                       'RecoEgamma.PhotonIdentification.Identification.cutBasedPhotonID_Fall17_94X_V2_cff']
                       )

process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '102X_upgrade2018_realistic_v18')


################
# Input Tags
#
################                      )
#FIXME GENPARTICLES input prunedGenParticles vs genParticles
process.demo = cms.EDAnalyzer('TriphotonAnalyzer',
    genparticles = cms.InputTag("prunedGenParticles"),
    #genInfo = cms.InputTag("generator", "", "SIM"),
    genInfo = cms.InputTag("generator", "", "GEN"), # For sherpa GGJets
    photonsMiniAOD = cms.InputTag("slimmedPhotons"),
    # For calculation of Event Weights
    outputFile = cms.string(outName),
    nEventsSample = cms.uint32(options.nEventsSample),
)

process.p = cms.Path(process.egammaPostRecoSeq*process.demo)
