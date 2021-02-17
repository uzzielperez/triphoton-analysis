import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )

process.source = cms.Source("PoolSource",

    fileNames = cms.untracked.vstring(
        #'file:/uscms/home/cuperez/nobackup/tribosons/CMSSW_10_2_8/src/GGGJets_TuneCUETP8M1_13TeV_madgraphMLM_pythia8_spring.root'
	'file:/uscms/home/cuperez/nobackup/tribosons/Triphoton-Dev/CMSSW_10_6_12/src/datasets/GGGJets_Pt-15_13TeV-sherpa__25435464-A08F-B24F-8015-50F0ACB272A4.root'
    )

)

process.TFileService = cms.Service("TFileService",
                fileName = cms.string("DemoTriphotonInfo.root")
                            )
#FIXME GENPARTICLES input prunedGenParticles vs genParticles
process.demo = cms.EDAnalyzer('TriphotonAnalyzer',
    genparticles = cms.InputTag("prunedGenParticles"),
    genInfo = cms.InputTag("generator", "", "SIM"),
)

process.p = cms.Path(process.demo)
