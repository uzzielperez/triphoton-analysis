#include "Comparisons.h"

void plot() {
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1,0);
  gStyle->SetNdivisions(505);
  gStyle->SetOptStat("ourme");
  gROOT->SetBatch();

  TString mcfm_path = "/uscms/home/cuperez/nobackup/tribosons/CMSSW_10_2_8/src/MCFM-8.3/Bin/triphoton_15_15_15/rootfiles/";
  TFile *fAAA = TFile::Open("../../makeClass/EventLooper/data/AAA_histograms.root");
  TFile *fNLO = TFile::Open(mcfm_path+"trigam_nlo_CT10.00_1.00_1.00_13TeV.root");
  TFile *fLO  = TFile::Open(mcfm_path+"trigam_lo_cteq6l1_1.00_1.00_13TeV.root");

  TriPhotons::CompareMggg(fAAA, fNLO, fLO);
  TriPhotons::ComparePtDists(fAAA, fNLO, fLO, "1");
  TriPhotons::ComparePtDists(fAAA, fNLO, fLO, "2");
  TriPhotons::ComparePtDists(fAAA, fNLO, fLO, "3");

}
