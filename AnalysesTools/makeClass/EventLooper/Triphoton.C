#define Triphoton_cxx
#include "Triphoton.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

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

   // def histograms
   TH1D *h_mAAA = new TH1D("h_minv", "", 80, 0, 400);
   //TH1D *h_mAAA = new TH1D("h_", "", 20, 0, 100); fAAA->Get("h_minv_unweighted"); //just for debugging.
   TH1D *h_pT1  = new TH1D("h_pT1", "", 20, 0, 200);
   TH1D *h_pT2  = new TH1D("h_pT2", "", 20, 0, 200);
   TH1D *h_pT3  = new TH1D("h_pT3", "", 20, 0, 200);
   TH1D *h_eta1  = new TH1D("h_eta1", "", 20, -2.5, 2.5);
   TH1D *h_eta2  = new TH1D("h_eta2", "", 20, -2.5, 2.5);
   TH1D *h_eta3  = new TH1D("h_eta3", "", 20, -2.5, 2.5);
   TH1D *h_phi1  = new TH1D("h_phi1", "", 20, -4, 4);
   TH1D *h_phi2  = new TH1D("h_phi2", "", 20, -4, 4);
   TH1D *h_phi3  = new TH1D("h_phi3", "", 20, -4, 4);
   h_mAAA->Sumw2();
   h_pT1->Sumw2();
   h_pT2->Sumw2();
   h_pT3->Sumw2();
   h_eta1->Sumw2();
   h_eta2->Sumw2();
   h_eta3->Sumw2();
   h_phi1->Sumw2();
   h_phi2->Sumw2();
   h_phi3->Sumw2();

   // Pairs
   TH1D *h_mA1A2 = new TH1D("h_mA1A2", "", 20, 0, 600);
   TH1D *h_mA1A3 = new TH1D("h_mA1A3", "", 20, 0, 600);
   TH1D *h_mA2A3 = new TH1D("h_mA2A3", "", 20, 0, 600);
   TH1D *h_dEta12 = new TH1D("h_dEta12", "", 5, 0, 5);
   TH1D *h_dEta23 = new TH1D("h_dEta23", "", 5, 0, 5);
   TH1D *h_dEta13 = new TH1D("h_dEta13", "", 5, 0, 5);
   TH1D *h_dPhi12 = new TH1D("h_dPhi12", "", 3, 0, 3);
   TH1D *h_dPhi23 = new TH1D("h_dPhi23", "", 3, 0, 3);
   TH1D *h_dPhi13 = new TH1D("h_dPhi13", "", 3, 0, 3);
   TH1D *h_dAbsEta12 = new TH1D("h_dAbsEta12", "", 5, 0, 5);
   TH1D *h_dAbsEta23 = new TH1D("h_dAbsEta23", "", 5, 0, 5);
   TH1D *h_dAbsEta13 = new TH1D("h_dAbsEta13", "", 5, 0, 5);

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

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      h_mAAA->Fill(GenTriPhoton_Minv);
      h_pT1->Fill(GenPhoton1_pt);
      h_pT2->Fill(GenPhoton2_pt);
      h_pT3->Fill(GenPhoton3_pt);
      h_eta1->Fill(GenPhoton1_eta);
      h_eta2->Fill(GenPhoton2_eta);
      h_eta3->Fill(GenPhoton3_eta);
      h_phi1->Fill(GenPhoton1_phi);
      h_phi2->Fill(GenPhoton2_phi);
      h_phi3->Fill(GenPhoton3_phi);

      h_mA1A2->Fill(GenDiPhoton12_Minv);
      h_mA1A3->Fill(GenDiPhoton13_Minv);
      h_mA2A3->Fill(GenDiPhoton23_Minv);
      h_dEta12->Fill(GenDiPhoton12_deltaEta);
      h_dEta23->Fill(GenDiPhoton23_deltaEta);
      h_dEta13->Fill(GenDiPhoton13_deltaEta);
      h_dPhi12->Fill(GenDiPhoton12_deltaPhi);
      h_dPhi23->Fill(GenDiPhoton23_deltaPhi);
      h_dPhi13->Fill(GenDiPhoton13_deltaPhi);
      h_dAbsEta12->Fill(GenDiPhoton12_deltaAbsEta);
      h_dAbsEta23->Fill(GenDiPhoton23_deltaAbsEta);
      h_dAbsEta13->Fill(GenDiPhoton13_deltaAbsEta);

   }
   TFile file_out("data/AAA_histograms.root", "RECREATE");
   // TFile file_out("GGJets_histograms.root", "RECREATE");
   // h_mAAA_weighted->Write();
   h_mAAA->Write();
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

   file_out.ls();
   file_out.Close();

}
