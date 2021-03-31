#include "Comparisons.h"
#include "ATLASComparisons.h"

void plot() {
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1,0);
  gStyle->SetNdivisions(505);
  gStyle->SetOptStat("ourme");
  gROOT->SetBatch();

  TString mcfm_path = "/uscms/home/cuperez/nobackup/tribosons/CMSSW_10_2_8/src/MCFM-8.3/Bin/";
  TFile *fAAA       = TFile::Open("../../makeClass/EventLooper/data/AAA_histograms.root");
  TFile *fNLO       = TFile::Open(mcfm_path+"rootfiles/trigam_nlo_CT10.00_1.00_1.00_13TeV.root");
  TFile *fLO        = TFile::Open(mcfm_path+"rootfiles/trigam_lo_cteq6l1_1.00_1.00_13TeV.root");
  TFile *fNLO_atlas = TFile::Open(mcfm_path+"ATLASrootfiles/trigam_nlo_CT10.00_1.00_1.00_8TeV.root");;

  // Signal Comparisons MCFM vs Sherpa
  TriPhotons::CompareMggg(fAAA, fNLO, fLO);
  TriPhotons::ComparePtDists(fAAA, fNLO, fLO, "1");
  TriPhotons::ComparePtDists(fAAA, fNLO, fLO, "2");
  TriPhotons::ComparePtDists(fAAA, fNLO, fLO, "3");
  TriPhotons::CompareDAbsEtaDists(fAAA, fNLO, fLO, "1", "2");
  TriPhotons::CompareDAbsEtaDists(fAAA, fNLO, fLO, "1", "3");
  TriPhotons::CompareDAbsEtaDists(fAAA, fNLO, fLO, "2", "3");
  TriPhotons::CompareMggDists(fAAA, fNLO, fLO, "1", "2");
  TriPhotons::CompareMggDists(fAAA, fNLO, fLO, "2", "3");
  TriPhotons::CompareMggDists(fAAA, fNLO, fLO, "1", "3");
  TriPhotons::CompareDPhiDists(fAAA, fNLO, fLO, "1", "2");
  TriPhotons::CompareDPhiDists(fAAA, fNLO, fLO, "1", "3");
  TriPhotons::CompareDPhiDists(fAAA, fNLO, fLO, "2", "3");
  TriPhotons::CompareEtaDists(fAAA, fNLO, fLO, "1");
  TriPhotons::CompareEtaDists(fAAA, fNLO, fLO, "2");
  TriPhotons::CompareEtaDists(fAAA, fNLO, fLO, "3");

  // ATLAS Comparisons
  TriPhotons::atlasCompareMggg(fNLO_atlas);
  TriPhotons::atlasCompareMggDists(fNLO_atlas, "1", "2");
  TriPhotons::atlasCompareMggDists(fNLO_atlas, "1", "3");
  TriPhotons::atlasCompareMggDists(fNLO_atlas, "2", "3");

}
