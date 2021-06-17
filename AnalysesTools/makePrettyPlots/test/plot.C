#include "Comparisons.h"
#include "ATLASComparisons.h"
#include "Selections.h"
#include "DataComparisons.h"
#include "Ratio.h"

// Run as 'plot.C(true)' for local
// FIXME: Clean by putting in separate Actions header file
void compareATLAS(TFile *fNLO_atlas, TFile *fNLO_atlas13TeV){
  // ATLAS Comparisons
  TriPhotons::atlasCompareMggg(fNLO_atlas, fNLO_atlas13TeV);
  TriPhotons::atlasCompareMggDists(fNLO_atlas, fNLO_atlas13TeV, "1", "2");
  TriPhotons::atlasCompareMggDists(fNLO_atlas, fNLO_atlas13TeV, "1", "3");
  TriPhotons::atlasCompareMggDists(fNLO_atlas, fNLO_atlas13TeV, "2", "3");
  TriPhotons::atlasComparePtDists(fNLO_atlas, fNLO_atlas13TeV, "1");
  TriPhotons::atlasComparePtDists(fNLO_atlas, fNLO_atlas13TeV, "2");
  TriPhotons::atlasComparePtDists(fNLO_atlas, fNLO_atlas13TeV, "3");
  TriPhotons::atlasCompareDAbsEtaDists(fNLO_atlas, fNLO_atlas13TeV, "1", "2");
  TriPhotons::atlasCompareDAbsEtaDists(fNLO_atlas, fNLO_atlas13TeV, "1", "3");
  TriPhotons::atlasCompareDAbsEtaDists(fNLO_atlas, fNLO_atlas13TeV, "2", "3");
  TriPhotons::atlasCompareDPhiDists(fNLO_atlas, fNLO_atlas13TeV, "1", "2");
  TriPhotons::atlasCompareDPhiDists(fNLO_atlas, fNLO_atlas13TeV, "1", "3");
  TriPhotons::atlasCompareDPhiDists(fNLO_atlas, fNLO_atlas13TeV, "2", "3");
}

void compareMCFMSherpa(TFile *fAAA, TFile *fNLO, TFile *fLO,  bool isHLT20 = false, bool isHLT30_30_15 = false){
  // HLT CMS
  // Signal Comparisons MCFM vs Sherpa
  TriPhotons::CompareMggg(fAAA, fNLO, fLO, isHLT20, isHLT30_30_15);
  TriPhotons::ComparePtDists(fAAA, fNLO, fLO, "1", isHLT20, isHLT30_30_15);
  TriPhotons::ComparePtDists(fAAA, fNLO, fLO, "2", isHLT20, isHLT30_30_15);
  TriPhotons::ComparePtDists(fAAA, fNLO, fLO, "3", isHLT20, isHLT30_30_15);
  TriPhotons::CompareMggDists(fAAA, fNLO, fLO, "1", "2", isHLT20, isHLT30_30_15);
  TriPhotons::CompareMggDists(fAAA, fNLO, fLO, "2", "3", isHLT20, isHLT30_30_15);
  TriPhotons::CompareMggDists(fAAA, fNLO, fLO, "1", "3", isHLT20, isHLT30_30_15);
  TriPhotons::CompareDPhiDists(fAAA, fNLO, fLO, "1", "2", isHLT20, isHLT30_30_15);
  TriPhotons::CompareDPhiDists(fAAA, fNLO, fLO, "1", "3", isHLT20, isHLT30_30_15);
  TriPhotons::CompareDPhiDists(fAAA, fNLO, fLO, "2", "3", isHLT20, isHLT30_30_15);
  TriPhotons::CompareDAbsEtaDists(fAAA, fNLO, fLO, "1", "2", isHLT20, isHLT30_30_15);
  TriPhotons::CompareDAbsEtaDists(fAAA, fNLO, fLO, "1", "3", isHLT20, isHLT30_30_15);
  TriPhotons::CompareDAbsEtaDists(fAAA, fNLO, fLO, "2", "3", isHLT20, isHLT30_30_15);

  // FIXME: Only works for isHLT30_30_15
  TriPhotons::CompareEtaDists(fAAA, fNLO, fLO, "1", isHLT20, isHLT30_30_15);
  TriPhotons::CompareEtaDists(fAAA, fNLO, fLO, "2", isHLT20, isHLT30_30_15);
  TriPhotons::CompareEtaDists(fAAA, fNLO, fLO, "3", isHLT20, isHLT30_30_15);
  TriPhotons::CompareQt(fAAA, fNLO, fLO, "1", isHLT20, isHLT30_30_15);
  TriPhotons::CompareQt(fAAA, fNLO, fLO, "2", isHLT20, isHLT30_30_15);
  TriPhotons::CompareQt(fAAA, fNLO, fLO, "3", isHLT20, isHLT30_30_15);


}

void singlePhoEff(TString fSherpaNtuple){
  //TriPhotons::efficiency(fSherpaNtuple, "matching", "EB");
  //TriPhotons::efficiency(fSherpaNtuple, "selection", "EB", "loose");
  //TriPhotons::efficiency(fSherpaNtuple, "selection", "EB", "medium");
  //TriPhotons::efficiency(fSherpaNtuple, "selection", "EB", "tight");

  //TriPhotons::efficiency(fSherpaNtuple, "matching", "EE");
  //TriPhotons::efficiency(fSherpaNtuple, "selection", "EE", "loose");
  //TriPhotons::efficiency(fSherpaNtuple, "selection", "EE", "medium");
  TriPhotons::efficiency(fSherpaNtuple, "selection", "EE", "tight");
  //FIXME: why can't I run both matching and selection efficiency all at once
  // Put some title

  // Tests:
  // TriPhotons::analyzeSinglePhoEff(fSherpaNtuple, "matching", "EB");
  // TriPhotons::ratioplot1();
  // TriPhotons::ratioplot2();
}

void compareData(TFile *fSim, TFile *fData, bool isHLT20=false, bool isHLT30_30_15=true, bool isGenVsPat = true, TString simLegLabel = "GGGJets", TString dataLegLabel = "GGJets"){
  TriPhotons::compareDataMggg(fSim, fData, isHLT20, isHLT30_30_15, isGenVsPat, simLegLabel, dataLegLabel);
  TriPhotons::compareDataPt(fSim, fData, "1", isHLT20, isHLT30_30_15, isGenVsPat, simLegLabel, dataLegLabel);
  TriPhotons::compareDataPt(fSim, fData, "2", isHLT20, isHLT30_30_15, isGenVsPat, simLegLabel, dataLegLabel);
  TriPhotons::compareDataPt(fSim, fData, "3", isHLT20, isHLT30_30_15, isGenVsPat, simLegLabel, dataLegLabel);
  TriPhotons::compareDataDiphotonMinv(fSim, fData, "1","2", isHLT20, isHLT30_30_15, isGenVsPat, simLegLabel, dataLegLabel);
  TriPhotons::compareDataDiphotonMinv(fSim, fData, "1","3", isHLT20, isHLT30_30_15, isGenVsPat, simLegLabel, dataLegLabel);
  TriPhotons::compareDataDiphotonMinv(fSim, fData, "2","3", isHLT20, isHLT30_30_15, isGenVsPat, simLegLabel, dataLegLabel);
  TriPhotons::compareDataDPhi(fSim, fData, "1","2", isHLT20, isHLT30_30_15, isGenVsPat, simLegLabel, dataLegLabel);
  TriPhotons::compareDataDPhi(fSim, fData, "1","3", isHLT20, isHLT30_30_15, isGenVsPat, simLegLabel, dataLegLabel);
  TriPhotons::compareDataDPhi(fSim, fData, "2","3", isHLT20, isHLT30_30_15, isGenVsPat, simLegLabel, dataLegLabel);
  TriPhotons::compareDataDEta(fSim, fData, "1","2", isHLT20, isHLT30_30_15, isGenVsPat, simLegLabel, dataLegLabel);
  TriPhotons::compareDataDEta(fSim, fData, "1","3", isHLT20, isHLT30_30_15, isGenVsPat, simLegLabel, dataLegLabel);
  TriPhotons::compareDataDEta(fSim, fData, "2","3", isHLT20, isHLT30_30_15, isGenVsPat, simLegLabel, dataLegLabel);
}

void getRatio(TFile *fSim, TFile *fData, bool isHLT20=false, bool isHLT30_30_15=true, bool isGenVsPat = true, TString simLegLabel = "GEN #gamma", TString dataLegLabel = "Tight PAT #gamma"){
  TriPhotons::getRatioMggg(fSim, fData, isHLT20, isHLT30_30_15, isGenVsPat, simLegLabel, dataLegLabel);
  TriPhotons::getRatioPt(fSim, fData, "1", isHLT20, isHLT30_30_15, isGenVsPat, simLegLabel, dataLegLabel);
  TriPhotons::getRatioPt(fSim, fData, "2", isHLT20, isHLT30_30_15, isGenVsPat, simLegLabel, dataLegLabel);
  TriPhotons::getRatioPt(fSim, fData, "3", isHLT20, isHLT30_30_15, isGenVsPat, simLegLabel, dataLegLabel);
  TriPhotons::getRatioDiphotonMinv(fSim, fData, "1","2", isHLT20, isHLT30_30_15, isGenVsPat, simLegLabel, dataLegLabel);
  TriPhotons::getRatioDiphotonMinv(fSim, fData, "1","3", isHLT20, isHLT30_30_15, isGenVsPat, simLegLabel, dataLegLabel);
  TriPhotons::getRatioDiphotonMinv(fSim, fData, "2","3", isHLT20, isHLT30_30_15, isGenVsPat, simLegLabel, dataLegLabel);
  TriPhotons::getRatioDPhi(fSim, fData, "1","2", isHLT20, isHLT30_30_15, isGenVsPat, simLegLabel, dataLegLabel);
  TriPhotons::getRatioDPhi(fSim, fData, "1","3", isHLT20, isHLT30_30_15, isGenVsPat, simLegLabel, dataLegLabel);
  TriPhotons::getRatioDPhi(fSim, fData, "2","3", isHLT20, isHLT30_30_15, isGenVsPat, simLegLabel, dataLegLabel);
  TriPhotons::getRatioDEta(fSim, fData, "1","2", isHLT20, isHLT30_30_15, isGenVsPat, simLegLabel, dataLegLabel);
  TriPhotons::getRatioDEta(fSim, fData, "1","3", isHLT20, isHLT30_30_15, isGenVsPat, simLegLabel, dataLegLabel);
  TriPhotons::getRatioDEta(fSim, fData, "2","3", isHLT20, isHLT30_30_15, isGenVsPat, simLegLabel, dataLegLabel);
}

void plot(bool local=true, bool isHLT20=false, bool isHLT30_30_15=true){
    // Run as 'plot.C(true)' for local
    // Set local to default so we work with ntuples in local computer
    // FIXME more intuitive local, HLT20, 30
  gROOT->SetStyle("Plain");

  gStyle->SetOptTitle(0);
  gStyle->SetPalette(1,0);
  gStyle->SetNdivisions(505);
  //gStyle->SetOptStat("ourme");
  gStyle->SetOptStat(0); // no stat box
  gROOT->SetBatch();

  // FIXME: do this as input in CLI
  TString mcfm_path      = "/uscms/home/cuperez/nobackup/tribosons/CMSSW_10_2_8/src/MCFM-8.3/Bin/";
  TString makeClass_path = "/uscms/home/cuperez/nobackup/tribosons/Triphoton-Dev/CMSSW_10_6_12/src/triphoton-analysis/AnalysesTools/";
  TString fLOstr         = "trigam_nlo_CT10.00_1.00_1.00_13TeV";
  TString fNLOstr        = "trigam_lo_cteq6l1_1.00_1.00_13TeV";
  TString fSherpaNtuple  = "../../../data/out_GGGJets_Pt-15_13TeV-sherpa_evt17800.root"; // FIXME: this is local

  if (local)         {mcfm_path = "../../../data/"; makeClass_path = "../../";}
  if (isHLT20)       {fLOstr += "_25"; fNLOstr += "_25";}
  if (isHLT30_30_15) {fLOstr += "_35"; fNLOstr += "_35";}
  std::cout << fNLOstr << std::endl;

  TFile *fAAA       = TFile::Open(makeClass_path+"makeClass/EventLooper/data/AAA_histograms.root");
  TFile *fAAAExt    = TFile::Open(makeClass_path+"makeClass/EventLooper/data/AAA_histogramsExt.root");
  TFile *fGGJets    = TFile::Open(makeClass_path+"makeClass/EventLooper/data/GGJets_histograms.root");
  TFile *fNLO       = TFile::Open(mcfm_path+"rootfiles/"+fLOstr+".root");
  TFile *fLO        = TFile::Open(mcfm_path+"rootfiles/"+fNLOstr+".root");
  TFile *fNLO_atlas      = TFile::Open(mcfm_path+"ATLASrootfiles/trigam_nlo_CT10.00_1.00_1.00_8TeV.root");
  TFile *fNLO_atlas13TeV = TFile::Open(mcfm_path+"ATLASrootfiles/trigam_nlo_CT10.00_1.00_1.00_13TeVATLAS.root");

  // ACTIONS:
  // compareATLAS(fNLO_atlas, fNLO_atlas13TeV);
  // compareMCFMSherpa(fAAA, fNLO, fLO, isHLT20, isHLT30_30_15);
  //singlePhoEff(fSherpaNtuple);

  // Compare PAT vs GEN
  getRatio(fAAA, fAAA, isHLT20, isHLT30_30_15);

  // Compare Signal vs Background
  // compareData(fAAA, fGGJets, isHLT20, isHLT30_30_15, false);
  compareData(fAAAExt, fGGJets, isHLT20, isHLT30_30_15, false);

}
