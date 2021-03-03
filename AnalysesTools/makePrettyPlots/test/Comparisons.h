#ifndef Comparisons_h
#define Comparisons_h

namespace TriPhotons
{
  void ComparePtDists(TFile *fSherpaSource, TFile *fMCFM_nlo, TFile *fMCFM_lo, TString phoNumStr){

    std::cout << "Get Pt for Photon " << phoNumStr <<  std::endl;
    std::cout << "h_pt"+phoNumStr << std::endl;
    TH1D *h_pt = (TH1D*) fSherpaSource->Get("h_pT"+phoNumStr);
    int phoNum = phoNumStr.Atoi();

    TString mcfmHistID = "id1";
    if (phoNum == 2) mcfmHistID = "id5";
    if (phoNum == 3) mcfmHistID = "id5";

    TH1F *h_pt_nlo = (TH1F*) fMCFM_nlo->Get(mcfmHistID);
    TH1F *h_pt_lo  = (TH1F*)  fMCFM_lo->Get(mcfmHistID);

    TCanvas *c1 = new TCanvas("c1","c1",800,600);

    h_pt_lo->Scale(0.0463964/h_pt_lo->GetEntries());
    h_pt_nlo->Scale(0.12550288/h_pt_nlo->GetEntries());
    float h_pt_binWidth = ((h_pt->GetXaxis()->GetXmax())-(h_pt->GetXaxis()->GetXmin()))/ (h_pt->GetNbinsX());
    h_pt->Scale(0.108607/h_pt->GetEntries());
    h_pt->Scale(1.0/h_pt_binWidth); // Cross-section weight in makeclass

    h_pt_nlo->Draw("E1, SAME");
    h_pt->SetLineColor(6);
    h_pt->Draw("E1, SAME");
    h_pt->SetMinimum(0.1);
    h_pt_lo->SetLineColor(12);
    h_pt_lo->Draw("E1, SAME");

    auto l1 = new TLegend(0.4,0.25,0.6,0.45);
    l1->SetBorderSize(0);
    l1->AddEntry(h_pt_nlo, "GGG mcfm NLO", "l");
    l1->AddEntry(h_pt_lo, "GGG mcfm LO", "l");
    l1->AddEntry(fSherpaSource, "GGGJetsSherpa", "l");
    l1->Draw();
    c1->SaveAs("plots/triphoton_Pt"+phoNumStr+"_sherpaVsMcfm.pdf");
  } // end Pt

  void CompareMggg(TFile *fSherpaSource, TFile *fMCFM_nlo, TFile *fMCFM_lo){
    /** Make baseline comparisons of Sherpa with MCFM **/
    /** Compares differential cross section measurements as a function of Mgg**/


    TString hminvstr = "h_minv";
    std::cout << "Get Minv " << hminvstr << std::endl;
    TH1D *h_mAAA = (TH1D*) fSherpaSource->Get(hminvstr); //just for debugging.
    //------- MCFM NLO vs LO
    TH1F *h_mAAA_nlo = (TH1F*) fMCFM_nlo->Get("id7");
    TH1F *h_mAAA_lo  = (TH1F*)  fMCFM_lo->Get("id7");

    TH1D *h_pT1  = (TH1D*) fSherpaSource->Get("h_pT1");
    TH1D *h_pT2  = (TH1D*) fSherpaSource->Get("h_pT2");
    TH1D *h_pT3  = (TH1D*) fSherpaSource->Get("h_pT3");

    TH1D *h_phi1  = (TH1D*) fSherpaSource->Get("h_phi1");
    TH1D *h_phi2  = (TH1D*) fSherpaSource->Get("h_phi2");
    TH1D *h_phi3  = (TH1D*) fSherpaSource->Get("h_phi3");

    //------- MCFM vs Sherpa
    TCanvas *canvas_sherpaVsMcfm = new TCanvas("canvas_sherpaVsMcfm","canvas_sherpaVsMcfm",800,600);
    //h_mAAA_nlo->Scale(1/h_mAAA_nlo->GetEntries());
    // Differential Cross section = Cross section / bin width
    h_mAAA_lo->Scale(0.0463964/h_mAAA_lo->GetEntries());
    h_mAAA_nlo->Scale(0.12550288/h_mAAA_nlo->GetEntries());
    float h_mAAA_binWidth = ((h_mAAA->GetXaxis()->GetXmax())-(h_mAAA->GetXaxis()->GetXmin()))/ (h_mAAA->GetNbinsX());
    h_mAAA->Scale(0.108607/h_mAAA->GetEntries());
    h_mAAA->Scale(1.0/h_mAAA_binWidth); // Cross-section weight in makeclass
    // h_mAAA->Scale(0.09981/h_mAAA->GetEntries()); // Cross-section weight in makeclass
    //h_mAAA->Scale(0.09981/h_mAAA->GetEntries()); // just for debugging. h_mAAA is unweighted in makeclass

    h_mAAA_nlo->Draw("E1, SAME");
    h_mAAA->SetLineColor(6);
    h_mAAA->Draw("E1, SAME");
    h_mAAA->SetMinimum(0.1);

    h_mAAA_lo->SetLineColor(12);
    h_mAAA_lo->Draw("E1, SAME");
    gPad->SetLogy();
    auto legsherpavsmcfm = new TLegend(0.4,0.25,0.6,0.45);
    legsherpavsmcfm->SetBorderSize(0);
    legsherpavsmcfm->AddEntry(h_mAAA_nlo, "GGG mcfm NLO", "l");
    legsherpavsmcfm->AddEntry(h_mAAA_lo, "GGG mcfm LO", "l");
    legsherpavsmcfm->AddEntry(h_mAAA, "GGGJetsSherpa", "l");
    legsherpavsmcfm->Draw();
    canvas_sherpaVsMcfm->SaveAs("plots/triphoton_Minv_sherpaVsMcfm.pdf");

    std::cout << h_mAAA->GetEntries() << std::endl;
    std::cout << h_mAAA_nlo->GetEntries() << std::endl;
    std::cout << h_mAAA_lo->GetEntries() << std::endl;

  }

} // end namespace

#endif
