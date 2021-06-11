#define Triphoton_cxx
#include "Triphoton.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <cmath>

void Triphoton::Loop()
{
//   In a ROOT session, you can do:
//      root> .L Triphoton.C
//      root> Triphoton t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   bool isSvsB = false;
   TString outFile = "data/AAA_histograms.root";
   //TString outFile = "data/GGJets_histograms.root";

   int minvNbins = (isSvsB == false) ? 80:10;
   int minMinv = 0;
   int maxMinv = (isSvsB == false) ? 400:1000;

   int qtNbins = 80;
   int minQt = 0;
   int maxQt = 400;

   int ptNbins = 40;
   int minPt = 0;
   int maxPt = 200;

   int etaNbins = 20;
   double minEta = -2.5;
   double maxEta = 2.5;

   int phiNbins  = 20;
   int minPhi = -4;
   int maxPhi = 4;

   int diPhoNbins = 60;
   int minDiPho = 0;
   int maxDiPho = 300;

   int dEtaNbins  = 40;
   int minDEta = 0;
   int maxDEta = 5;

   int dPhiNbins  = (isSvsB == false) ? 40:35;
   int minDPhi = 0;
   int maxDPhi = (isSvsB == false) ? 4:7;

   int absDetaNbins  = 40;
   int minAbsDeta = 0;
   int maxAbsDeta = 5;


   // def histograms
   TH1D *h_mAAA = new TH1D("h_minv", "", minvNbins, minMinv, maxMinv);
   TH1D *h_qt = new TH1D("h_qt", "", qtNbins, minQt, maxQt);
   //TH1D *h_mAAA = new TH1D("h_", "", 20, 0, 100); fAAA->Get("h_minv_unweighted"); //just for debugging.
   TH1D *h_pT1  = new TH1D("h_pT1", "", ptNbins, minPt, maxPt);
   TH1D *h_pT2  = new TH1D("h_pT2", "", ptNbins, minPt, maxPt);
   TH1D *h_pT3  = new TH1D("h_pT3", "", ptNbins, minPt, maxPt);
   TH1D *h_eta1  = new TH1D("h_eta1", "", etaNbins, minEta, maxEta);
   TH1D *h_eta2  = new TH1D("h_eta2", "", etaNbins, minEta, maxEta);
   TH1D *h_eta3  = new TH1D("h_eta3", "", etaNbins, minEta, maxEta);
   TH1D *h_phi1  = new TH1D("h_phi1", "", phiNbins, minPhi, minPhi);
   TH1D *h_phi2  = new TH1D("h_phi2", "", phiNbins, minPhi, minPhi);
   TH1D *h_phi3  = new TH1D("h_phi3", "", phiNbins, minPhi, minPhi);
   h_mAAA->Sumw2();
   h_qt->Sumw2();
   h_pT1->Sumw2();
   h_pT2->Sumw2();
   h_pT3->Sumw2();
   h_eta1->Sumw2();
   h_eta2->Sumw2();
   h_eta3->Sumw2();
   h_phi1->Sumw2();
   h_phi2->Sumw2();
   h_phi3->Sumw2();

   TH1D *h_mA1A2 = new TH1D("h_mA1A2", "", diPhoNbins, minDiPho, maxDiPho);
   TH1D *h_mA1A3 = new TH1D("h_mA1A3", "", diPhoNbins, minDiPho, maxDiPho);
   TH1D *h_mA2A3 = new TH1D("h_mA2A3", "", diPhoNbins, minDiPho, maxDiPho);
   TH1D *h_dEta12 = new TH1D("h_dEta12", "", dEtaNbins, minDEta, maxDEta);
   TH1D *h_dEta23 = new TH1D("h_dEta23", "", dEtaNbins, minDEta, maxDEta);
   TH1D *h_dEta13 = new TH1D("h_dEta13", "", dEtaNbins, minDEta, maxDEta);
   TH1D *h_dPhi12 = new TH1D("h_dPhi12", "", dPhiNbins, minDPhi, maxDPhi);
   TH1D *h_dPhi23 = new TH1D("h_dPhi23", "", dPhiNbins, minDPhi, maxDPhi);
   TH1D *h_dPhi13 = new TH1D("h_dPhi13", "", dPhiNbins, minDPhi, maxDPhi);
   TH1D *h_dAbsEta12 = new TH1D("h_dAbsEta12", "", absDetaNbins, minAbsDeta, maxAbsDeta);
   TH1D *h_dAbsEta23 = new TH1D("h_dAbsEta23", "", absDetaNbins, minAbsDeta, maxAbsDeta);
   TH1D *h_dAbsEta13 = new TH1D("h_dAbsEta13", "", absDetaNbins, minAbsDeta, maxAbsDeta);


   h_mA1A2->Sumw2();
   h_mA1A3->Sumw2();
   h_mA2A3->Sumw2();
   h_dEta12->Sumw2();
   h_dEta23->Sumw2();
   h_dEta13->Sumw2();
   h_dPhi12->Sumw2();
   h_dPhi23->Sumw2();
   h_dPhi13->Sumw2();
   h_dAbsEta12->Sumw2();
   h_dAbsEta23->Sumw2();
   h_dAbsEta13->Sumw2();

   // 25-25-25 pt cut

   // def histograms
   TH1D *h_pT25_mAAA = new TH1D("h_pT25_minv", "", minvNbins, minMinv, maxMinv);
   TH1D *h_pT25_qt = new TH1D("h_pT25_qt", "", qtNbins, minQt, maxQt);
   //TH1D *h_pT25_mAAA = new TH1D("h_pT25_", "", 20, 0, 100); fAAA->Get("h_pT25_minv_unweighted"); //just for debugging.
   TH1D *h_pT25_pT1  = new TH1D("h_pT25_pT1", "", ptNbins, minPt, maxPt);
   TH1D *h_pT25_pT2  = new TH1D("h_pT25_pT2", "", ptNbins, minPt, maxPt);
   TH1D *h_pT25_pT3  = new TH1D("h_pT25_pT3", "", ptNbins, minPt, maxPt);
   TH1D *h_pT25_eta1  = new TH1D("h_pT25_eta1", "", etaNbins, minEta, maxEta);
   TH1D *h_pT25_eta2  = new TH1D("h_pT25_eta2", "", etaNbins, minEta, maxEta);
   TH1D *h_pT25_eta3  = new TH1D("h_pT25_eta3", "", etaNbins, minEta, maxEta);
   TH1D *h_pT25_phi1  = new TH1D("h_pT25_phi1", "", phiNbins, minPhi, minPhi);
   TH1D *h_pT25_phi2  = new TH1D("h_pT25_phi2", "", phiNbins, minPhi, minPhi);
   TH1D *h_pT25_phi3  = new TH1D("h_pT25_phi3", "", phiNbins, minPhi, minPhi);
   h_pT25_mAAA->Sumw2();
   h_pT25_qt->Sumw2();
   h_pT25_pT1->Sumw2();
   h_pT25_pT2->Sumw2();
   h_pT25_pT3->Sumw2();
   h_pT25_eta1->Sumw2();
   h_pT25_eta2->Sumw2();
   h_pT25_eta3->Sumw2();
   h_pT25_phi1->Sumw2();
   h_pT25_phi2->Sumw2();
   h_pT25_phi3->Sumw2();

   TH1D *h_pT25_mA1A2 = new TH1D("h_pT25_mA1A2", "", diPhoNbins, minDiPho, maxDiPho);
   TH1D *h_pT25_mA1A3 = new TH1D("h_pT25_mA1A3", "", diPhoNbins, minDiPho, maxDiPho);
   TH1D *h_pT25_mA2A3 = new TH1D("h_pT25_mA2A3", "", diPhoNbins, minDiPho, maxDiPho);
   TH1D *h_pT25_dEta12 = new TH1D("h_pT25_dEta12", "", dEtaNbins, minDEta, maxDEta);
   TH1D *h_pT25_dEta23 = new TH1D("h_pT25_dEta23", "", dEtaNbins, minDEta, maxDEta);
   TH1D *h_pT25_dEta13 = new TH1D("h_pT25_dEta13", "", dEtaNbins, minDEta, maxDEta);
   TH1D *h_pT25_dPhi12 = new TH1D("h_pT25_dPhi12", "", dPhiNbins, minDPhi, maxDPhi);
   TH1D *h_pT25_dPhi23 = new TH1D("h_pT25_dPhi23", "", dPhiNbins, minDPhi, maxDPhi);
   TH1D *h_pT25_dPhi13 = new TH1D("h_pT25_dPhi13", "", dPhiNbins, minDPhi, maxDPhi);
   TH1D *h_pT25_dAbsEta12 = new TH1D("h_pT25_dAbsEta12", "", absDetaNbins, minAbsDeta, maxAbsDeta);
   TH1D *h_pT25_dAbsEta23 = new TH1D("h_pT25_dAbsEta23", "", absDetaNbins, minAbsDeta, maxAbsDeta);
   TH1D *h_pT25_dAbsEta13 = new TH1D("h_pT25_dAbsEta13", "", absDetaNbins, minAbsDeta, maxAbsDeta);


   h_pT25_mA1A2->Sumw2();
   h_pT25_mA1A3->Sumw2();
   h_pT25_mA2A3->Sumw2();
   h_pT25_dEta12->Sumw2();
   h_pT25_dEta23->Sumw2();
   h_pT25_dEta13->Sumw2();
   h_pT25_dPhi12->Sumw2();
   h_pT25_dPhi23->Sumw2();
   h_pT25_dPhi13->Sumw2();
   h_pT25_dAbsEta12->Sumw2();
   h_pT25_dAbsEta23->Sumw2();
   h_pT25_dAbsEta13->Sumw2();

   // 35-35-15 pt cut

   // def histograms
   TH1D *h_pT35_35_15_mAAA = new TH1D("h_pT35_35_15_minv", "", minvNbins, minMinv, maxMinv);
   TH1D *h_pT35_35_15_qt = new TH1D("h_pT35_35_15_qt", "", qtNbins, minQt, maxQt);
   //TH1D *h_pT35_35_15_mAAA = new TH1D("h_pT35_35_15_", "", 20, 0, 100); fAAA->Get("h_pT35_35_15_minv_unweighted"); //just for debugging.
   TH1D *h_pT35_35_15_pT1  = new TH1D("h_pT35_35_15_pT1", "", ptNbins, minPt, maxPt);
   TH1D *h_pT35_35_15_pT2  = new TH1D("h_pT35_35_15_pT2", "", ptNbins, minPt, maxPt);
   TH1D *h_pT35_35_15_pT3  = new TH1D("h_pT35_35_15_pT3", "", ptNbins, minPt, maxPt);
   TH1D *h_pT35_35_15_eta1  = new TH1D("h_pT35_35_15_eta1", "", etaNbins, minEta, maxEta);
   TH1D *h_pT35_35_15_eta2  = new TH1D("h_pT35_35_15_eta2", "", etaNbins, minEta, maxEta);
   TH1D *h_pT35_35_15_eta3  = new TH1D("h_pT35_35_15_eta3", "", etaNbins, minEta, maxEta);
   TH1D *h_pT35_35_15_phi1  = new TH1D("h_pT35_35_15_phi1", "", phiNbins, minPhi, minPhi);
   TH1D *h_pT35_35_15_phi2  = new TH1D("h_pT35_35_15_phi2", "", phiNbins, minPhi, minPhi);
   TH1D *h_pT35_35_15_phi3  = new TH1D("h_pT35_35_15_phi3", "", phiNbins, minPhi, minPhi);
   h_pT35_35_15_mAAA->Sumw2();
   h_pT35_35_15_qt->Sumw2();
   h_pT35_35_15_pT1->Sumw2();
   h_pT35_35_15_pT2->Sumw2();
   h_pT35_35_15_pT3->Sumw2();
   h_pT35_35_15_eta1->Sumw2();
   h_pT35_35_15_eta2->Sumw2();
   h_pT35_35_15_eta3->Sumw2();
   h_pT35_35_15_phi1->Sumw2();
   h_pT35_35_15_phi2->Sumw2();
   h_pT35_35_15_phi3->Sumw2();

   TH1D *h_pT35_35_15_mA1A2 = new TH1D("h_pT35_35_15_mA1A2", "", diPhoNbins, minDiPho, maxDiPho);
   TH1D *h_pT35_35_15_mA1A3 = new TH1D("h_pT35_35_15_mA1A3", "", diPhoNbins, minDiPho, maxDiPho);
   TH1D *h_pT35_35_15_mA2A3 = new TH1D("h_pT35_35_15_mA2A3", "", diPhoNbins, minDiPho, maxDiPho);
   TH1D *h_pT35_35_15_dEta12 = new TH1D("h_pT35_35_15_dEta12", "", dEtaNbins, minDEta, maxDEta);
   TH1D *h_pT35_35_15_dEta23 = new TH1D("h_pT35_35_15_dEta23", "", dEtaNbins, minDEta, maxDEta);
   TH1D *h_pT35_35_15_dEta13 = new TH1D("h_pT35_35_15_dEta13", "", dEtaNbins, minDEta, maxDEta);
   TH1D *h_pT35_35_15_dPhi12 = new TH1D("h_pT35_35_15_dPhi12", "", dPhiNbins, minDPhi, maxDPhi);
   TH1D *h_pT35_35_15_dPhi23 = new TH1D("h_pT35_35_15_dPhi23", "", dPhiNbins, minDPhi, maxDPhi);
   TH1D *h_pT35_35_15_dPhi13 = new TH1D("h_pT35_35_15_dPhi13", "", dPhiNbins, minDPhi, maxDPhi);
   TH1D *h_pT35_35_15_dAbsEta12 = new TH1D("h_pT35_35_15_dAbsEta12", "", absDetaNbins, minAbsDeta, maxAbsDeta);
   TH1D *h_pT35_35_15_dAbsEta23 = new TH1D("h_pT35_35_15_dAbsEta23", "", absDetaNbins, minAbsDeta, maxAbsDeta);
   TH1D *h_pT35_35_15_dAbsEta13 = new TH1D("h_pT35_35_15_dAbsEta13", "", absDetaNbins, minAbsDeta, maxAbsDeta);


   h_pT35_35_15_mA1A2->Sumw2();
   h_pT35_35_15_mA1A3->Sumw2();
   h_pT35_35_15_mA2A3->Sumw2();
   h_pT35_35_15_dEta12->Sumw2();
   h_pT35_35_15_dEta23->Sumw2();
   h_pT35_35_15_dEta13->Sumw2();
   h_pT35_35_15_dPhi12->Sumw2();
   h_pT35_35_15_dPhi23->Sumw2();
   h_pT35_35_15_dPhi13->Sumw2();
   h_pT35_35_15_dAbsEta12->Sumw2();
   h_pT35_35_15_dAbsEta23->Sumw2();
   h_pT35_35_15_dAbsEta13->Sumw2();

   // PAT Photons
   // def histograms
   TH1D *h_PAT_pT25_mAAA = new TH1D("h_PAT_pT25_minv", "", minvNbins, minMinv, maxMinv);
   TH1D *h_PAT_pT25_qt = new TH1D("h_PAT_pT25_qt", "", qtNbins, minQt, maxQt);
   //TH1D *h_PAT_pT25_mAAA = new TH1D("h_PAT_pT25_", "", 20, 0, 100); fAAA->Get("h_PAT_pT25_minv_unweighted"); //just for debugging.
   TH1D *h_PAT_pT25_pT1  = new TH1D("h_PAT_pT25_pT1", "", ptNbins, minPt, maxPt);
   TH1D *h_PAT_pT25_pT2  = new TH1D("h_PAT_pT25_pT2", "", ptNbins, minPt, maxPt);
   TH1D *h_PAT_pT25_pT3  = new TH1D("h_PAT_pT25_pT3", "", ptNbins, minPt, maxPt);
   TH1D *h_PAT_pT25_eta1  = new TH1D("h_PAT_pT25_eta1", "", etaNbins, minEta, maxEta);
   TH1D *h_PAT_pT25_eta2  = new TH1D("h_PAT_pT25_eta2", "", etaNbins, minEta, maxEta);
   TH1D *h_PAT_pT25_eta3  = new TH1D("h_PAT_pT25_eta3", "", etaNbins, minEta, maxEta);
   TH1D *h_PAT_pT25_phi1  = new TH1D("h_PAT_pT25_phi1", "", phiNbins, minPhi, minPhi);
   TH1D *h_PAT_pT25_phi2  = new TH1D("h_PAT_pT25_phi2", "", phiNbins, minPhi, minPhi);
   TH1D *h_PAT_pT25_phi3  = new TH1D("h_PAT_pT25_phi3", "", phiNbins, minPhi, minPhi);
   h_PAT_pT25_mAAA->Sumw2();
   h_PAT_pT25_qt->Sumw2();
   h_PAT_pT25_pT1->Sumw2();
   h_PAT_pT25_pT2->Sumw2();
   h_PAT_pT25_pT3->Sumw2();
   h_PAT_pT25_eta1->Sumw2();
   h_PAT_pT25_eta2->Sumw2();
   h_PAT_pT25_eta3->Sumw2();
   h_PAT_pT25_phi1->Sumw2();
   h_PAT_pT25_phi2->Sumw2();
   h_PAT_pT25_phi3->Sumw2();

   TH1D *h_PAT_pT25_mA1A2 = new TH1D("h_PAT_pT25_mA1A2", "", diPhoNbins, minDiPho, maxDiPho);
   TH1D *h_PAT_pT25_mA1A3 = new TH1D("h_PAT_pT25_mA1A3", "", diPhoNbins, minDiPho, maxDiPho);
   TH1D *h_PAT_pT25_mA2A3 = new TH1D("h_PAT_pT25_mA2A3", "", diPhoNbins, minDiPho, maxDiPho);
   TH1D *h_PAT_pT25_dEta12 = new TH1D("h_PAT_pT25_dEta12", "", dEtaNbins, minDEta, maxDEta);
   TH1D *h_PAT_pT25_dEta23 = new TH1D("h_PAT_pT25_dEta23", "", dEtaNbins, minDEta, maxDEta);
   TH1D *h_PAT_pT25_dEta13 = new TH1D("h_PAT_pT25_dEta13", "", dEtaNbins, minDEta, maxDEta);
   TH1D *h_PAT_pT25_dPhi12 = new TH1D("h_PAT_pT25_dPhi12", "", dPhiNbins, minDPhi, maxDPhi);
   TH1D *h_PAT_pT25_dPhi23 = new TH1D("h_PAT_pT25_dPhi23", "", dPhiNbins, minDPhi, maxDPhi);
   TH1D *h_PAT_pT25_dPhi13 = new TH1D("h_PAT_pT25_dPhi13", "", dPhiNbins, minDPhi, maxDPhi);
   TH1D *h_PAT_pT25_dAbsEta12 = new TH1D("h_PAT_pT25_dAbsEta12", "", absDetaNbins, minAbsDeta, maxAbsDeta);
   TH1D *h_PAT_pT25_dAbsEta23 = new TH1D("h_PAT_pT25_dAbsEta23", "", absDetaNbins, minAbsDeta, maxAbsDeta);
   TH1D *h_PAT_pT25_dAbsEta13 = new TH1D("h_PAT_pT25_dAbsEta13", "", absDetaNbins, minAbsDeta, maxAbsDeta);


   h_PAT_pT25_mA1A2->Sumw2();
   h_PAT_pT25_mA1A3->Sumw2();
   h_PAT_pT25_mA2A3->Sumw2();
   h_PAT_pT25_dEta12->Sumw2();
   h_PAT_pT25_dEta23->Sumw2();
   h_PAT_pT25_dEta13->Sumw2();
   h_PAT_pT25_dPhi12->Sumw2();
   h_PAT_pT25_dPhi23->Sumw2();
   h_PAT_pT25_dPhi13->Sumw2();
   h_PAT_pT25_dAbsEta12->Sumw2();
   h_PAT_pT25_dAbsEta23->Sumw2();
   h_PAT_pT25_dAbsEta13->Sumw2();

   // 35-35-15 pt cut

   // def histograms
   TH1D *h_PAT_pT35_35_15_mAAA = new TH1D("h_PAT_pT35_35_15_minv", "", minvNbins, minMinv, maxMinv);
   TH1D *h_PAT_pT35_35_15_qt = new TH1D("h_PAT_pT35_35_15_qt", "", qtNbins, minQt, maxQt);
   //TH1D *h_PAT_pT35_35_15_mAAA = new TH1D("h_PAT_pT35_35_15_", "", 20, 0, 100); fAAA->Get("h_PAT_pT35_35_15_minv_unweighted"); //just for debugging.
   TH1D *h_PAT_pT35_35_15_pT1  = new TH1D("h_PAT_pT35_35_15_pT1", "", ptNbins, minPt, maxPt);
   TH1D *h_PAT_pT35_35_15_pT2  = new TH1D("h_PAT_pT35_35_15_pT2", "", ptNbins, minPt, maxPt);
   TH1D *h_PAT_pT35_35_15_pT3  = new TH1D("h_PAT_pT35_35_15_pT3", "", ptNbins, minPt, maxPt);
   TH1D *h_PAT_pT35_35_15_eta1  = new TH1D("h_PAT_pT35_35_15_eta1", "", etaNbins, minEta, maxEta);
   TH1D *h_PAT_pT35_35_15_eta2  = new TH1D("h_PAT_pT35_35_15_eta2", "", etaNbins, minEta, maxEta);
   TH1D *h_PAT_pT35_35_15_eta3  = new TH1D("h_PAT_pT35_35_15_eta3", "", etaNbins, minEta, maxEta);
   TH1D *h_PAT_pT35_35_15_phi1  = new TH1D("h_PAT_pT35_35_15_phi1", "", phiNbins, minPhi, minPhi);
   TH1D *h_PAT_pT35_35_15_phi2  = new TH1D("h_PAT_pT35_35_15_phi2", "", phiNbins, minPhi, minPhi);
   TH1D *h_PAT_pT35_35_15_phi3  = new TH1D("h_PAT_pT35_35_15_phi3", "", phiNbins, minPhi, minPhi);
   h_PAT_pT35_35_15_mAAA->Sumw2();
   h_PAT_pT35_35_15_qt->Sumw2();
   h_PAT_pT35_35_15_pT1->Sumw2();
   h_PAT_pT35_35_15_pT2->Sumw2();
   h_PAT_pT35_35_15_pT3->Sumw2();
   h_PAT_pT35_35_15_eta1->Sumw2();
   h_PAT_pT35_35_15_eta2->Sumw2();
   h_PAT_pT35_35_15_eta3->Sumw2();
   h_PAT_pT35_35_15_phi1->Sumw2();
   h_PAT_pT35_35_15_phi2->Sumw2();
   h_PAT_pT35_35_15_phi3->Sumw2();

   TH1D *h_PAT_pT35_35_15_mA1A2 = new TH1D("h_PAT_pT35_35_15_mA1A2", "", diPhoNbins, minDiPho, maxDiPho);
   TH1D *h_PAT_pT35_35_15_mA1A3 = new TH1D("h_PAT_pT35_35_15_mA1A3", "", diPhoNbins, minDiPho, maxDiPho);
   TH1D *h_PAT_pT35_35_15_mA2A3 = new TH1D("h_PAT_pT35_35_15_mA2A3", "", diPhoNbins, minDiPho, maxDiPho);
   TH1D *h_PAT_pT35_35_15_dEta12 = new TH1D("h_PAT_pT35_35_15_dEta12", "", dEtaNbins, minDEta, maxDEta);
   TH1D *h_PAT_pT35_35_15_dEta23 = new TH1D("h_PAT_pT35_35_15_dEta23", "", dEtaNbins, minDEta, maxDEta);
   TH1D *h_PAT_pT35_35_15_dEta13 = new TH1D("h_PAT_pT35_35_15_dEta13", "", dEtaNbins, minDEta, maxDEta);
   TH1D *h_PAT_pT35_35_15_dPhi12 = new TH1D("h_PAT_pT35_35_15_dPhi12", "", dPhiNbins, minDPhi, maxDPhi);
   TH1D *h_PAT_pT35_35_15_dPhi23 = new TH1D("h_PAT_pT35_35_15_dPhi23", "", dPhiNbins, minDPhi, maxDPhi);
   TH1D *h_PAT_pT35_35_15_dPhi13 = new TH1D("h_PAT_pT35_35_15_dPhi13", "", dPhiNbins, minDPhi, maxDPhi);
   TH1D *h_PAT_pT35_35_15_dAbsEta12 = new TH1D("h_PAT_pT35_35_15_dAbsEta12", "", absDetaNbins, minAbsDeta, maxAbsDeta);
   TH1D *h_PAT_pT35_35_15_dAbsEta23 = new TH1D("h_PAT_pT35_35_15_dAbsEta23", "", absDetaNbins, minAbsDeta, maxAbsDeta);
   TH1D *h_PAT_pT35_35_15_dAbsEta13 = new TH1D("h_PAT_pT35_35_15_dAbsEta13", "", absDetaNbins, minAbsDeta, maxAbsDeta);


   h_PAT_pT35_35_15_mA1A2->Sumw2();
   h_PAT_pT35_35_15_mA1A3->Sumw2();
   h_PAT_pT35_35_15_mA2A3->Sumw2();
   h_PAT_pT35_35_15_dEta12->Sumw2();
   h_PAT_pT35_35_15_dEta23->Sumw2();
   h_PAT_pT35_35_15_dEta13->Sumw2();
   h_PAT_pT35_35_15_dPhi12->Sumw2();
   h_PAT_pT35_35_15_dPhi23->Sumw2();
   h_PAT_pT35_35_15_dPhi13->Sumw2();
   h_PAT_pT35_35_15_dAbsEta12->Sumw2();
   h_PAT_pT35_35_15_dAbsEta23->Sumw2();
   h_PAT_pT35_35_15_dAbsEta13->Sumw2();

   //counters
   int nSimEvents = 0;
   int n353515gen = 0;
   int n252525gen = 0;
   int n353515pat = 0;
   int n252525pat = 0;
   int n353515genCMSCrack = 0;
   int n353515gen_ = 0;
   int nExcCMSCrack = 0;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      double evtwt = Event_weightAll;
      nSimEvents++;
      bool CMScrackGen1 = GenPhoton1_eta > 1.37 && GenPhoton1_eta < 1.56;
      bool CMScrackGen2 = GenPhoton2_eta > 1.37 && GenPhoton2_eta < 1.56;
      bool CMScrackGen3 = GenPhoton3_eta > 1.37 && GenPhoton3_eta < 1.56;
      bool CMScrackGen = CMScrackGen1 && CMScrackGen2 && CMScrackGen3;
      bool CMScrack1 = Photon1_eta > 1.37 && Photon1_eta < 1.56;
      bool CMScrack2 = Photon2_eta > 1.37 && Photon2_eta < 1.56;
      bool CMScrack3 = Photon3_eta > 1.37 && Photon3_eta < 1.56;
      bool CMScrack = CMScrack1 && CMScrack2 && CMScrack3;
      bool phoPt353515 = (GenPhoton1_pt > 35) && (GenPhoton2_pt > 35) && (GenPhoton3_pt > 15);

      if (phoPt353515) n353515gen_++;
      if (!CMScrackGen) nExcCMSCrack++;

      if (!CMScrackGen){

      h_mAAA->Fill(GenTriPhoton_Minv, evtwt);
      h_qt->Fill(GenTriPhoton_qt, evtwt);
      h_pT1->Fill(GenPhoton1_pt, evtwt);
      h_pT2->Fill(GenPhoton2_pt, evtwt);
      h_pT3->Fill(GenPhoton3_pt, evtwt);
      h_eta1->Fill(GenPhoton1_eta, evtwt);
      h_eta2->Fill(GenPhoton2_eta, evtwt);
      h_eta3->Fill(GenPhoton3_eta, evtwt);
      h_phi1->Fill(GenPhoton1_phi, evtwt);
      h_phi2->Fill(GenPhoton2_phi, evtwt);
      h_phi3->Fill(GenPhoton3_phi, evtwt);

      h_mA1A2->Fill(GenDiPhoton12_Minv, evtwt);
      h_mA1A3->Fill(GenDiPhoton13_Minv, evtwt);
      h_mA2A3->Fill(GenDiPhoton23_Minv, evtwt);
      h_dEta12->Fill(GenDiPhoton12_deltaEta, evtwt);
      h_dEta23->Fill(GenDiPhoton23_deltaEta, evtwt);
      h_dEta13->Fill(GenDiPhoton13_deltaEta, evtwt);
      h_dPhi12->Fill(fabs(GenDiPhoton12_deltaPhi), evtwt);
      h_dPhi23->Fill(fabs(GenDiPhoton23_deltaPhi), evtwt);
      h_dPhi13->Fill(fabs(GenDiPhoton13_deltaPhi), evtwt);
      h_dAbsEta12->Fill(GenDiPhoton12_deltaAbsEta, evtwt);
      h_dAbsEta23->Fill(GenDiPhoton23_deltaAbsEta, evtwt);
      h_dAbsEta13->Fill(GenDiPhoton13_deltaAbsEta, evtwt);

      if ( (GenPhoton1_pt > 25) && (GenPhoton2_pt > 25) && (GenPhoton3_pt > 25) ){
        n252525gen++;
        h_pT25_mAAA->Fill(GenTriPhoton_Minv, evtwt);
        h_pT25_qt->Fill(GenTriPhoton_qt, evtwt);
        h_pT25_pT1->Fill(GenPhoton1_pt, evtwt);
        h_pT25_pT2->Fill(GenPhoton2_pt, evtwt);
        h_pT25_pT3->Fill(GenPhoton3_pt, evtwt);
        h_pT25_eta1->Fill(GenPhoton1_eta, evtwt);
        h_pT25_eta2->Fill(GenPhoton2_eta, evtwt);
        h_pT25_eta3->Fill(GenPhoton3_eta, evtwt);
        h_pT25_phi1->Fill(GenPhoton1_phi, evtwt);
        h_pT25_phi2->Fill(GenPhoton2_phi, evtwt);
        h_pT25_phi3->Fill(GenPhoton3_phi, evtwt);

        h_pT25_mA1A2->Fill(GenDiPhoton12_Minv, evtwt);
        h_pT25_mA1A3->Fill(GenDiPhoton13_Minv, evtwt);
        h_pT25_mA2A3->Fill(GenDiPhoton23_Minv, evtwt);
        h_pT25_dEta12->Fill(GenDiPhoton12_deltaEta, evtwt);
        h_pT25_dEta23->Fill(GenDiPhoton23_deltaEta, evtwt);
        h_pT25_dEta13->Fill(GenDiPhoton13_deltaEta, evtwt);
        h_pT25_dPhi12->Fill(fabs(GenDiPhoton12_deltaPhi), evtwt);
        h_pT25_dPhi23->Fill(fabs(GenDiPhoton23_deltaPhi), evtwt);
        h_pT25_dPhi13->Fill(fabs(GenDiPhoton13_deltaPhi), evtwt);
        h_pT25_dAbsEta12->Fill(GenDiPhoton12_deltaAbsEta, evtwt);
        h_pT25_dAbsEta23->Fill(GenDiPhoton23_deltaAbsEta, evtwt);
        h_pT25_dAbsEta13->Fill(GenDiPhoton13_deltaAbsEta, evtwt);
      }

      if ( (GenPhoton1_pt > 35) && (GenPhoton2_pt > 35) && (GenPhoton3_pt > 15) ){
        n353515gen++;
        // subset of 15_15_15 sample
        // MCFM reports in fb, the Event_weightAll is
        // FIXME: Event_weightAll

        h_pT35_35_15_mAAA->Fill(GenTriPhoton_Minv, evtwt);
        h_pT35_35_15_qt->Fill(GenTriPhoton_qt, evtwt);
        h_pT35_35_15_pT1->Fill(GenPhoton1_pt, evtwt);
        h_pT35_35_15_pT2->Fill(GenPhoton2_pt, evtwt);
        h_pT35_35_15_pT3->Fill(GenPhoton3_pt, evtwt);
        h_pT35_35_15_eta1->Fill(GenPhoton1_eta, evtwt);
        h_pT35_35_15_eta2->Fill(GenPhoton2_eta, evtwt);
        h_pT35_35_15_eta3->Fill(GenPhoton3_eta, evtwt);
        h_pT35_35_15_phi1->Fill(GenPhoton1_phi, evtwt);
        h_pT35_35_15_phi2->Fill(GenPhoton2_phi, evtwt);
        h_pT35_35_15_phi3->Fill(GenPhoton3_phi, evtwt);

        h_pT35_35_15_mA1A2->Fill(GenDiPhoton12_Minv, evtwt);
        h_pT35_35_15_mA1A3->Fill(GenDiPhoton13_Minv, evtwt);
        h_pT35_35_15_mA2A3->Fill(GenDiPhoton23_Minv, evtwt);
        h_pT35_35_15_dEta12->Fill(GenDiPhoton12_deltaEta, evtwt);
        h_pT35_35_15_dEta23->Fill(GenDiPhoton23_deltaEta, evtwt);
        h_pT35_35_15_dEta13->Fill(GenDiPhoton13_deltaEta, evtwt);
        h_pT35_35_15_dPhi12->Fill(fabs(GenDiPhoton12_deltaPhi), evtwt);
        h_pT35_35_15_dPhi23->Fill(fabs(GenDiPhoton23_deltaPhi), evtwt);
        h_pT35_35_15_dPhi13->Fill(fabs(GenDiPhoton13_deltaPhi), evtwt);
        h_pT35_35_15_dAbsEta12->Fill(GenDiPhoton12_deltaAbsEta, evtwt);
        h_pT35_35_15_dAbsEta23->Fill(GenDiPhoton23_deltaAbsEta, evtwt);
        h_pT35_35_15_dAbsEta13->Fill(GenDiPhoton13_deltaAbsEta, evtwt);
      }
      }//end CMScrackGen

      // PAT Photons
      if (!CMScrack){
      if ( (Photon1_pt > 25) && (Photon2_pt > 25) && (Photon3_pt > 25) ){
        n252525pat++;
        h_PAT_pT25_mAAA->Fill(TriPhoton_Minv, evtwt);
        h_PAT_pT25_qt->Fill(TriPhoton_qt, evtwt);
        h_PAT_pT25_pT1->Fill(Photon1_pt, evtwt);
        h_PAT_pT25_pT2->Fill(Photon2_pt, evtwt);
        h_PAT_pT25_pT3->Fill(Photon3_pt, evtwt);
        h_PAT_pT25_eta1->Fill(Photon1_eta, evtwt);
        h_PAT_pT25_eta2->Fill(Photon2_eta, evtwt);
        h_PAT_pT25_eta3->Fill(Photon3_eta, evtwt);
        h_PAT_pT25_phi1->Fill(Photon1_phi, evtwt);
        h_PAT_pT25_phi2->Fill(Photon2_phi, evtwt);
        h_PAT_pT25_phi3->Fill(Photon3_phi, evtwt);

        h_PAT_pT25_mA1A2->Fill(DiPhoton12_Minv, evtwt);
        h_PAT_pT25_mA1A3->Fill(DiPhoton13_Minv, evtwt);
        h_PAT_pT25_mA2A3->Fill(DiPhoton23_Minv, evtwt);
        h_PAT_pT25_dEta12->Fill(DiPhoton12_deltaEta, evtwt);
        h_PAT_pT25_dEta23->Fill(DiPhoton23_deltaEta, evtwt);
        h_PAT_pT25_dEta13->Fill(DiPhoton13_deltaEta, evtwt);
        h_PAT_pT25_dPhi12->Fill(DiPhoton12_deltaPhi, evtwt);
        h_PAT_pT25_dPhi23->Fill(DiPhoton23_deltaPhi, evtwt);
        h_PAT_pT25_dPhi13->Fill(DiPhoton13_deltaPhi, evtwt);
        h_PAT_pT25_dAbsEta12->Fill(DiPhoton12_deltaAbsEta, evtwt);
        h_PAT_pT25_dAbsEta23->Fill(DiPhoton23_deltaAbsEta, evtwt);
        h_PAT_pT25_dAbsEta13->Fill(DiPhoton13_deltaAbsEta, evtwt);
      }

      if ( (Photon1_pt > 35) && (Photon2_pt > 35) && (Photon3_pt > 15) ){
        // MCFM reports in fb, the Event_weightAll is
        n353515pat++;
        h_PAT_pT35_35_15_mAAA->Fill(TriPhoton_Minv, evtwt);
        h_PAT_pT35_35_15_qt->Fill(TriPhoton_qt, evtwt);
        h_PAT_pT35_35_15_pT1->Fill(Photon1_pt, evtwt);
        h_PAT_pT35_35_15_pT2->Fill(Photon2_pt, evtwt);
        h_PAT_pT35_35_15_pT3->Fill(Photon3_pt, evtwt);
        h_PAT_pT35_35_15_eta1->Fill(Photon1_eta, evtwt);
        h_PAT_pT35_35_15_eta2->Fill(Photon2_eta, evtwt);
        h_PAT_pT35_35_15_eta3->Fill(Photon3_eta, evtwt);
        h_PAT_pT35_35_15_phi1->Fill(Photon1_phi, evtwt);
        h_PAT_pT35_35_15_phi2->Fill(Photon2_phi, evtwt);
        h_PAT_pT35_35_15_phi3->Fill(Photon3_phi, evtwt);

        h_PAT_pT35_35_15_mA1A2->Fill(DiPhoton12_Minv, evtwt);
        h_PAT_pT35_35_15_mA1A3->Fill(DiPhoton13_Minv, evtwt);
        h_PAT_pT35_35_15_mA2A3->Fill(DiPhoton23_Minv, evtwt);
        h_PAT_pT35_35_15_dEta12->Fill(DiPhoton12_deltaEta, evtwt);
        h_PAT_pT35_35_15_dEta23->Fill(DiPhoton23_deltaEta, evtwt);
        h_PAT_pT35_35_15_dEta13->Fill(DiPhoton13_deltaEta, evtwt);
        h_PAT_pT35_35_15_dPhi12->Fill(DiPhoton12_deltaPhi, evtwt);
        h_PAT_pT35_35_15_dPhi23->Fill(DiPhoton23_deltaPhi, evtwt);
        h_PAT_pT35_35_15_dPhi13->Fill(DiPhoton13_deltaPhi, evtwt);
        h_PAT_pT35_35_15_dAbsEta12->Fill(DiPhoton12_deltaAbsEta, evtwt);
        h_PAT_pT35_35_15_dAbsEta23->Fill(DiPhoton23_deltaAbsEta, evtwt);
        h_PAT_pT35_35_15_dAbsEta13->Fill(DiPhoton13_deltaAbsEta, evtwt);
      }
    }//end CMScrack

   }

   TFile file_out(outFile, "RECREATE");
   //TFile file_out("data/GGJets_histograms.root", "RECREATE");
   // h_mAAA_weighted->Write();
   h_mAAA->Write();
   h_qt->Write();
   h_pT1->Write();
   h_pT2->Write();
   h_pT3->Write();
   h_eta1->Write();
   h_eta2->Write();
   h_eta3->Write();
   h_phi1->Write();
   h_phi2->Write();
   h_phi3->Write();

   h_mA1A2->Write();
   h_mA1A3->Write();
   h_mA2A3->Write();
   h_dEta12->Write();
   h_dEta23->Write();
   h_dEta13->Write();
   h_dPhi12->Write();
   h_dPhi23->Write();
   h_dPhi13->Write();

   h_dAbsEta12->Write();
   h_dAbsEta23->Write();
   h_dAbsEta13->Write();

   // pt 25-25-25 cut

   h_pT25_mAAA->Write();
   h_pT25_qt->Write();
   h_pT25_pT1->Write();
   h_pT25_pT2->Write();
   h_pT25_pT3->Write();
   h_pT25_eta1->Write();
   h_pT25_eta2->Write();
   h_pT25_eta3->Write();
   h_pT25_phi1->Write();
   h_pT25_phi2->Write();
   h_pT25_phi3->Write();

   h_pT25_mA1A2->Write();
   h_pT25_mA1A3->Write();
   h_pT25_mA2A3->Write();
   h_pT25_dEta12->Write();
   h_pT25_dEta23->Write();
   h_pT25_dEta13->Write();
   h_pT25_dPhi12->Write();
   h_pT25_dPhi23->Write();
   h_pT25_dPhi13->Write();

   h_pT25_dAbsEta12->Write();
   h_pT25_dAbsEta23->Write();
   h_pT25_dAbsEta13->Write();

   // pt 35-35-15 cut

   h_pT35_35_15_mAAA->Write();
   h_pT35_35_15_qt->Write();
   h_pT35_35_15_pT1->Write();
   h_pT35_35_15_pT2->Write();
   h_pT35_35_15_pT3->Write();
   h_pT35_35_15_eta1->Write();
   h_pT35_35_15_eta2->Write();
   h_pT35_35_15_eta3->Write();
   h_pT35_35_15_phi1->Write();
   h_pT35_35_15_phi2->Write();
   h_pT35_35_15_phi3->Write();

   h_pT35_35_15_mA1A2->Write();
   h_pT35_35_15_mA1A3->Write();
   h_pT35_35_15_mA2A3->Write();
   h_pT35_35_15_dEta12->Write();
   h_pT35_35_15_dEta23->Write();
   h_pT35_35_15_dEta13->Write();
   h_pT35_35_15_dPhi12->Write();
   h_pT35_35_15_dPhi23->Write();
   h_pT35_35_15_dPhi13->Write();

   h_pT35_35_15_dAbsEta12->Write();
   h_pT35_35_15_dAbsEta23->Write();
   h_pT35_35_15_dAbsEta13->Write();

   h_PAT_pT25_mAAA->Write();
   h_PAT_pT25_qt->Write();
   h_PAT_pT25_pT1->Write();
   h_PAT_pT25_pT2->Write();
   h_PAT_pT25_pT3->Write();
   h_PAT_pT25_eta1->Write();
   h_PAT_pT25_eta2->Write();
   h_PAT_pT25_eta3->Write();
   h_PAT_pT25_phi1->Write();
   h_PAT_pT25_phi2->Write();
   h_PAT_pT25_phi3->Write();

   h_PAT_pT25_mA1A2->Write();
   h_PAT_pT25_mA1A3->Write();
   h_PAT_pT25_mA2A3->Write();
   h_PAT_pT25_dEta12->Write();
   h_PAT_pT25_dEta23->Write();
   h_PAT_pT25_dEta13->Write();
   h_PAT_pT25_dPhi12->Write();
   h_PAT_pT25_dPhi23->Write();
   h_PAT_pT25_dPhi13->Write();
   h_PAT_pT25_dAbsEta12->Write();
   h_PAT_pT25_dAbsEta23->Write();
   h_PAT_pT25_dAbsEta13->Write();

   h_PAT_pT35_35_15_mAAA->Write();
   h_PAT_pT35_35_15_qt->Write();
   h_PAT_pT35_35_15_pT1->Write();
   h_PAT_pT35_35_15_pT2->Write();
   h_PAT_pT35_35_15_pT3->Write();
   h_PAT_pT35_35_15_eta1->Write();
   h_PAT_pT35_35_15_eta2->Write();
   h_PAT_pT35_35_15_eta3->Write();
   h_PAT_pT35_35_15_phi1->Write();
   h_PAT_pT35_35_15_phi2->Write();
   h_PAT_pT35_35_15_phi3->Write();

   h_PAT_pT35_35_15_mA1A2->Write();
   h_PAT_pT35_35_15_mA1A3->Write();
   h_PAT_pT35_35_15_mA2A3->Write();
   h_PAT_pT35_35_15_dEta12->Write();
   h_PAT_pT35_35_15_dEta23->Write();
   h_PAT_pT35_35_15_dEta13->Write();
   h_PAT_pT35_35_15_dPhi12->Write();
   h_PAT_pT35_35_15_dPhi23->Write();
   h_PAT_pT35_35_15_dPhi13->Write();
   h_PAT_pT35_35_15_dAbsEta12->Write();
   h_PAT_pT35_35_15_dAbsEta23->Write();
   h_PAT_pT35_35_15_dAbsEta13->Write();

   std::cout << "nSimEvents: " << nSimEvents << std::endl;
   std::cout << "n353515gen: " << n353515gen << std::endl;
   std::cout << "n252525gen: " << n252525gen << std::endl;
   std::cout << "n353515pat: " << n353515pat << std::endl;
   std::cout << "n252525pat: " << n252525pat << std::endl;
   std::cout << "========== DEBUGGING ===========" << std::endl;
   std::cout << "n353515gen: " << n353515gen_ << std::endl;
   std::cout << "nCMScrack: " << nExcCMSCrack << std::endl;

   file_out.ls();
   file_out.Close();

}
