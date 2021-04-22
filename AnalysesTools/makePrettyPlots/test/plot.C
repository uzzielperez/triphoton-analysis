#include "Comparisons.h"
#include "ATLASComparisons.h"
#include "Selections.h"

// Run as 'plot.C(true)' for local
// FIXME: Clean by putting in separate Actions header file
void compareATLAS(TFile *fNLO_atlas){
  // ATLAS Comparisons
  TriPhotons::atlasCompareMggg(fNLO_atlas);
  TriPhotons::atlasCompareMggDists(fNLO_atlas, "1", "2");
  TriPhotons::atlasCompareMggDists(fNLO_atlas, "1", "3");
  TriPhotons::atlasCompareMggDists(fNLO_atlas, "2", "3");
  TriPhotons::atlasComparePtDists(fNLO_atlas, "1");
  TriPhotons::atlasComparePtDists(fNLO_atlas, "2");
  TriPhotons::atlasComparePtDists(fNLO_atlas, "3");
  TriPhotons::atlasCompareDAbsEtaDists(fNLO_atlas, "1", "2");
  TriPhotons::atlasCompareDAbsEtaDists(fNLO_atlas, "1", "3");
  TriPhotons::atlasCompareDAbsEtaDists(fNLO_atlas, "2", "3");
  TriPhotons::atlasCompareDPhiDists(fNLO_atlas, "1", "2");
  TriPhotons::atlasCompareDPhiDists(fNLO_atlas, "1", "3");
  TriPhotons::atlasCompareDPhiDists(fNLO_atlas, "2", "3");
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
}

void plot(bool local=false, bool isHLT20=false, bool isHLT30_30_15=false) {
    // Run as 'plot.C(true)' for local
    // FIXME more intuitive local, HLT20, 30

  gROOT->SetStyle("Plain");
  gStyle->SetOptTitle(0);
  gStyle->SetPalette(1,0);
  gStyle->SetNdivisions(505);
  gStyle->SetOptStat("ourme");
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
  TFile *fNLO       = TFile::Open(mcfm_path+"rootfiles/"+fLOstr+".root");
  TFile *fLO        = TFile::Open(mcfm_path+"rootfiles/"+fNLOstr+".root");
  TFile *fNLO_atlas = TFile::Open(mcfm_path+"ATLASrootfiles/trigam_nlo_CT10.00_1.00_1.00_8TeV.root");

  // ACTIONS:
  //compareATLAS(fNLO_atlas);
  //compareMCFMSherpa(fAAA, fNLO, fLO, isHLT20, isHLT30_30_15);
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
