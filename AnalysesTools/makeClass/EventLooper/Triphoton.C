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
   // TH1D *h_mA1A2 = new TH1D("h_mA1A2", "", 20, 0, 600);
   // TH1D *h_mA1A3 = new TH1D("h_mA1A3", "", 20, 0, 600);
   // TH1D *h_mA2A3 = new TH1D("h_mA2A3", "", 20, 0, 600);
   // TH1D *h_dEta12 = new TH1D("h_dEta12", "", 5, 0, 5);
   // TH1D *h_dEta23 = new TH1D("h_dEta23", "", 5, 0, 5);
   // TH1D *h_dEta13 = new TH1D("h_dEta13", "", 5, 0, 5);
   // TH1D *h_dPhi12 = new TH1D("h_dPhi12", "", 3, 0, 3);
   // TH1D *h_dPhi23 = new TH1D("h_dPhi23", "", 3, 0, 3);
   // TH1D *h_dPhi13 = new TH1D("h_dPhi13", "", 3, 0, 3);
   // TH1D *h_dAbsEta12 = new TH1D("h_dAbsEta12", "", 5, 0, 5);
   // TH1D *h_dAbsEta23 = new TH1D("h_dAbsEta23", "", 5, 0, 5);
   // TH1D *h_dAbsEta13 = new TH1D("h_dAbsEta13", "", 5, 0, 5);

   TH1D *h_mA1A2 = new TH1D("h_mA1A2", "", 60, 0, 300);
   TH1D *h_mA1A3 = new TH1D("h_mA1A3", "", 60, 0, 300);
   TH1D *h_mA2A3 = new TH1D("h_mA2A3", "", 60, 0, 300);
   TH1D *h_dEta12 = new TH1D("h_dEta12", "", 40, 0, 4);
   TH1D *h_dEta23 = new TH1D("h_dEta23", "", 40, 0, 4);
   TH1D *h_dEta13 = new TH1D("h_dEta13", "", 40, 0, 4);
   TH1D *h_dPhi12 = new TH1D("h_dPhi12", "", 40, 0, 4);
   TH1D *h_dPhi23 = new TH1D("h_dPhi23", "", 40, 0, 4);
   TH1D *h_dPhi13 = new TH1D("h_dPhi13", "", 40, 0, 4);
   TH1D *h_dAbsEta12 = new TH1D("h_dAbsEta12", "", 12, 0, 4);
   TH1D *h_dAbsEta23 = new TH1D("h_dAbsEta23", "", 12, 0, 4);
   TH1D *h_dAbsEta13 = new TH1D("h_dAbsEta13", "", 12, 0, 4);


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
   TH1D *h_pT25_mAAA = new TH1D("h_pT25_minv", "", 80, 0, 400);
   //TH1D *h_pT25_mAAA = new TH1D("h_pT25_", "", 20, 0, 100); fAAA->Get("h_pT25_minv_unweighted"); //just for debugging.
   TH1D *h_pT25_pT1  = new TH1D("h_pT25_pT1", "", 20, 0, 200);
   TH1D *h_pT25_pT2  = new TH1D("h_pT25_pT2", "", 20, 0, 200);
   TH1D *h_pT25_pT3  = new TH1D("h_pT25_pT3", "", 20, 0, 200);
   TH1D *h_pT25_eta1  = new TH1D("h_pT25_eta1", "", 20, -2.5, 2.5);
   TH1D *h_pT25_eta2  = new TH1D("h_pT25_eta2", "", 20, -2.5, 2.5);
   TH1D *h_pT25_eta3  = new TH1D("h_pT25_eta3", "", 20, -2.5, 2.5);
   TH1D *h_pT25_phi1  = new TH1D("h_pT25_phi1", "", 20, -4, 4);
   TH1D *h_pT25_phi2  = new TH1D("h_pT25_phi2", "", 20, -4, 4);
   TH1D *h_pT25_phi3  = new TH1D("h_pT25_phi3", "", 20, -4, 4);
   h_pT25_mAAA->Sumw2();
   h_pT25_pT1->Sumw2();
   h_pT25_pT2->Sumw2();
   h_pT25_pT3->Sumw2();
   h_pT25_eta1->Sumw2();
   h_pT25_eta2->Sumw2();
   h_pT25_eta3->Sumw2();
   h_pT25_phi1->Sumw2();
   h_pT25_phi2->Sumw2();
   h_pT25_phi3->Sumw2();

   TH1D *h_pT25_mA1A2 = new TH1D("h_pT25_mA1A2", "", 60, 0, 300);
   TH1D *h_pT25_mA1A3 = new TH1D("h_pT25_mA1A3", "", 60, 0, 300);
   TH1D *h_pT25_mA2A3 = new TH1D("h_pT25_mA2A3", "", 60, 0, 300);
   TH1D *h_pT25_dEta12 = new TH1D("h_pT25_dEta12", "", 40, 0, 4);
   TH1D *h_pT25_dEta23 = new TH1D("h_pT25_dEta23", "", 40, 0, 4);
   TH1D *h_pT25_dEta13 = new TH1D("h_pT25_dEta13", "", 40, 0, 4);
   TH1D *h_pT25_dPhi12 = new TH1D("h_pT25_dPhi12", "", 40, 0, 4);
   TH1D *h_pT25_dPhi23 = new TH1D("h_pT25_dPhi23", "", 40, 0, 4);
   TH1D *h_pT25_dPhi13 = new TH1D("h_pT25_dPhi13", "", 40, 0, 4);
   TH1D *h_pT25_dAbsEta12 = new TH1D("h_pT25_dAbsEta12", "", 12, 0, 4);
   TH1D *h_pT25_dAbsEta23 = new TH1D("h_pT25_dAbsEta23", "", 12, 0, 4);
   TH1D *h_pT25_dAbsEta13 = new TH1D("h_pT25_dAbsEta13", "", 12, 0, 4);


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
   TH1D *h_pT35_35_15_mAAA = new TH1D("h_pT35_35_15_minv", "", 80, 0, 400);
   //TH1D *h_pT35_35_15_mAAA = new TH1D("h_pT35_35_15_", "", 20, 0, 100); fAAA->Get("h_pT35_35_15_minv_unweighted"); //just for debugging.
   TH1D *h_pT35_35_15_pT1  = new TH1D("h_pT35_35_15_pT1", "", 20, 0, 200);
   TH1D *h_pT35_35_15_pT2  = new TH1D("h_pT35_35_15_pT2", "", 20, 0, 200);
   TH1D *h_pT35_35_15_pT3  = new TH1D("h_pT35_35_15_pT3", "", 20, 0, 200);
   TH1D *h_pT35_35_15_eta1  = new TH1D("h_pT35_35_15_eta1", "", 20, -2.5, 2.5);
   TH1D *h_pT35_35_15_eta2  = new TH1D("h_pT35_35_15_eta2", "", 20, -2.5, 2.5);
   TH1D *h_pT35_35_15_eta3  = new TH1D("h_pT35_35_15_eta3", "", 20, -2.5, 2.5);
   TH1D *h_pT35_35_15_phi1  = new TH1D("h_pT35_35_15_phi1", "", 20, -4, 4);
   TH1D *h_pT35_35_15_phi2  = new TH1D("h_pT35_35_15_phi2", "", 20, -4, 4);
   TH1D *h_pT35_35_15_phi3  = new TH1D("h_pT35_35_15_phi3", "", 20, -4, 4);
   h_pT35_35_15_mAAA->Sumw2();
   h_pT35_35_15_pT1->Sumw2();
   h_pT35_35_15_pT2->Sumw2();
   h_pT35_35_15_pT3->Sumw2();
   h_pT35_35_15_eta1->Sumw2();
   h_pT35_35_15_eta2->Sumw2();
   h_pT35_35_15_eta3->Sumw2();
   h_pT35_35_15_phi1->Sumw2();
   h_pT35_35_15_phi2->Sumw2();
   h_pT35_35_15_phi3->Sumw2();

   TH1D *h_pT35_35_15_mA1A2 = new TH1D("h_pT35_35_15_mA1A2", "", 60, 0, 300);
   TH1D *h_pT35_35_15_mA1A3 = new TH1D("h_pT35_35_15_mA1A3", "", 60, 0, 300);
   TH1D *h_pT35_35_15_mA2A3 = new TH1D("h_pT35_35_15_mA2A3", "", 60, 0, 300);
   TH1D *h_pT35_35_15_dEta12 = new TH1D("h_pT35_35_15_dEta12", "", 40, 0, 4);
   TH1D *h_pT35_35_15_dEta23 = new TH1D("h_pT35_35_15_dEta23", "", 40, 0, 4);
   TH1D *h_pT35_35_15_dEta13 = new TH1D("h_pT35_35_15_dEta13", "", 40, 0, 4);
   TH1D *h_pT35_35_15_dPhi12 = new TH1D("h_pT35_35_15_dPhi12", "", 40, 0, 4);
   TH1D *h_pT35_35_15_dPhi23 = new TH1D("h_pT35_35_15_dPhi23", "", 40, 0, 4);
   TH1D *h_pT35_35_15_dPhi13 = new TH1D("h_pT35_35_15_dPhi13", "", 40, 0, 4);
   TH1D *h_pT35_35_15_dAbsEta12 = new TH1D("h_pT35_35_15_dAbsEta12", "", 12, 0, 4);
   TH1D *h_pT35_35_15_dAbsEta23 = new TH1D("h_pT35_35_15_dAbsEta23", "", 12, 0, 4);
   TH1D *h_pT35_35_15_dAbsEta13 = new TH1D("h_pT35_35_15_dAbsEta13", "", 12, 0, 4);


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

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      double evtwt = Event_weightAll;

    if ()
      h_mAAA->Fill(GenTriPhoton_Minv, evtwt);
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
      h_dPhi12->Fill(GenDiPhoton12_deltaPhi, evtwt);
      h_dPhi23->Fill(GenDiPhoton23_deltaPhi, evtwt);
      h_dPhi13->Fill(GenDiPhoton13_deltaPhi, evtwt);
      h_dAbsEta12->Fill(GenDiPhoton12_deltaAbsEta, evtwt);
      h_dAbsEta23->Fill(GenDiPhoton23_deltaAbsEta, evtwt);
      h_dAbsEta13->Fill(GenDiPhoton13_deltaAbsEta, evtwt);

      if ( (GenPhoton1_pt > 25) && (GenPhoton2_pt > 25) && (GenPhoton3_pt > 25) ){
        h_pT25_mAAA->Fill(GenTriPhoton_Minv, evtwt);
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
        h_pT25_dPhi12->Fill(GenDiPhoton12_deltaPhi, evtwt);
        h_pT25_dPhi23->Fill(GenDiPhoton23_deltaPhi, evtwt);
        h_pT25_dPhi13->Fill(GenDiPhoton13_deltaPhi, evtwt);
        h_pT25_dAbsEta12->Fill(GenDiPhoton12_deltaAbsEta, evtwt);
        h_pT25_dAbsEta23->Fill(GenDiPhoton23_deltaAbsEta, evtwt);
        h_pT25_dAbsEta13->Fill(GenDiPhoton13_deltaAbsEta, evtwt);
      }

      if ( (GenPhoton1_pt > 35) && (GenPhoton2_pt > 35) && (GenPhoton3_pt > 15) ){
        // MCFM reports in fb, the Event_weightAll is
        h_pT35_35_15_mAAA->Fill(GenTriPhoton_Minv, evtwt);
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
        h_pT35_35_15_dPhi12->Fill(GenDiPhoton12_deltaPhi, evtwt);
        h_pT35_35_15_dPhi23->Fill(GenDiPhoton23_deltaPhi, evtwt);
        h_pT35_35_15_dPhi13->Fill(GenDiPhoton13_deltaPhi, evtwt);
        h_pT35_35_15_dAbsEta12->Fill(GenDiPhoton12_deltaAbsEta, evtwt);
        h_pT35_35_15_dAbsEta23->Fill(GenDiPhoton23_deltaAbsEta, evtwt);
        h_pT35_35_15_dAbsEta13->Fill(GenDiPhoton13_deltaAbsEta, evtwt);
      }
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

   // pt 25-25-25 cut

   h_pT25_mAAA->Write();
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

   file_out.ls();
   file_out.Close();

}
