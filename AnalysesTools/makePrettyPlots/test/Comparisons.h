#ifndef Comparisons_h
#define Comparisons_h

namespace TriPhotons
{

  void CompareDPhiDists(TFile *fSherpaSource, TFile *fMCFM_nlo, TFile *fMCFM_lo, TString phoNum1, TString phoNum2)
  {

    TString phoPairStr = phoNum1+phoNum2;
    std::cout << "PhotonPair " << phoNum1 << phoNum2 <<  std::endl;
    std::cout << "h_dPhi"+phoNum1+phoNum2 << std::endl;
    TH1D *h_dPhi = (TH1D*) fSherpaSource->Get("h_dPhi"+phoNum1+phoNum2);

    TString mcfmHistID = "id7";
    if (phoPairStr == 13) mcfmHistID = "id8";
    if (phoPairStr == 23) mcfmHistID = "id9";

    TH1F *h_dPhi_nlo = (TH1F*) fMCFM_nlo->Get(mcfmHistID);
    TH1F *h_dPhi_lo  = (TH1F*)  fMCFM_lo->Get(mcfmHistID);

    TCanvas *c1 = new TCanvas("c1","c1",800,600);

    h_dPhi_lo->Scale(0.0463964/h_dPhi_lo->GetEntries());
    h_dPhi_nlo->Scale(0.12550288/h_dPhi_nlo->GetEntries());
    float h_dPhi_binWidth = ((h_dPhi->GetXaxis()->GetXmax())-(h_dPhi->GetXaxis()->GetXmin()))/ (h_dPhi->GetNbinsX());
    h_dPhi->Scale(0.108607/h_dPhi->GetEntries());
    h_dPhi->Scale(1.0/h_dPhi_binWidth); // Cross-section weight in makeclass

    h_dPhi_nlo->Draw("E1, SAME");
    h_dPhi->SetLineColor(6);
    h_dPhi->Draw("E1, SAME");
    h_dPhi->SetMinimum(0.1);
    h_dPhi_lo->SetLineColor(12);
    h_dPhi_lo->Draw("E1, SAME");

    auto l1 = new TLegend(0.4,0.25,0.6,0.45);
    l1->SetBorderSize(0);
    l1->AddEntry(h_dPhi_nlo, "GGG mcfm NLO", "l");
    l1->AddEntry(h_dPhi_lo, "GGG mcfm LO", "l");
    l1->AddEntry(h_dPhi, "GGGJetsSherpa", "l");
    l1->Draw();
    c1->SaveAs("plots/triphoton_DPhi"+phoPairStr+"_sherpaVsMcfm.pdf");
  } // end Pt

  void CompareMggDists(TFile *fSherpaSource, TFile *fMCFM_nlo, TFile *fMCFM_lo, TString phoNum1, TString phoNum2){
      TString phoPairStr = phoNum1+phoNum2;
      std::cout << "PhotonPair " << phoPairStr <<  std::endl;
      std::cout << "h_mA" << phoNum1 << "A" << phoNum2 << std::endl;
      TH1D *h_mAA = (TH1D*) fSherpaSource->Get("h_mA"+phoNum1+"A"+phoNum2);

      TString mcfmHistID = "id17";
      if (phoPairStr == 13) mcfmHistID = "id21";
      if (phoPairStr == 23) mcfmHistID = "id25";

      TH1F *h_mAA_nlo = (TH1F*) fMCFM_nlo->Get(mcfmHistID);
      TH1F *h_mAA_lo  = (TH1F*)  fMCFM_lo->Get(mcfmHistID);

      TCanvas *c1 = new TCanvas("c1","c1",600,600);

      h_mAA_lo->Scale(0.0463964/h_mAA_lo->GetEntries());
      h_mAA_nlo->Scale(0.12550288/h_mAA_nlo->GetEntries());
      float h_mAA_binWidth = ((h_mAA->GetXaxis()->GetXmax())-(h_mAA->GetXaxis()->GetXmin()))/ (h_mAA->GetNbinsX());
      h_mAA->Scale(0.108607/h_mAA->GetEntries());
      h_mAA->Scale(1.0/h_mAA_binWidth); // Cross-section weight in makeclass

      h_mAA_nlo->Draw("E1, SAME");
      h_mAA->SetLineColor(6);
      h_mAA->Draw("E1, SAME");
      h_mAA->SetMinimum(0.1);
      h_mAA_lo->SetLineColor(12);
      h_mAA_lo->Draw("E1, SAME");

      auto l1 = new TLegend(0.4,0.25,0.6,0.45);
      l1->SetBorderSize(0);
      l1->AddEntry(h_mAA_nlo, "GGG mcfm NLO", "l");
      l1->AddEntry(h_mAA_lo, "GGG mcfm LO", "l");
      l1->AddEntry(h_mAA, "GGGJetsSherpa", "l");
      l1->Draw();
      c1->SaveAs("plots/triphoton_mAA"+phoPairStr+"_sherpaVsMcfm.pdf");
  }

  void CompareDAbsEtaDists(TFile *fSherpaSource, TFile *fMCFM_nlo, TFile *fMCFM_lo, TString phoNum1, TString phoNum2)
  {

    TString phoPairStr = phoNum1+phoNum2;
    std::cout << "PhotonPair " << phoNum1 << phoNum2 <<  std::endl;
    std::cout << "h_dAbsEta"+phoNum1+phoNum2 << std::endl;
    TH1D *h_dAbsEta = (TH1D*) fSherpaSource->Get("h_dAbsEta"+phoNum1+phoNum2);

    TString mcfmHistID = "id20";
    if (phoPairStr == 13) mcfmHistID = "id24";
    if (phoPairStr == 23) mcfmHistID = "id27";

    TH1F *h_dAbsEta_nlo = (TH1F*) fMCFM_nlo->Get(mcfmHistID);
    TH1F *h_dAbsEta_lo  = (TH1F*)  fMCFM_lo->Get(mcfmHistID);

    TCanvas *c1 = new TCanvas("c1","c1",800,600);

    h_dAbsEta_lo->Scale(0.0463964/h_dAbsEta_lo->GetEntries());
    h_dAbsEta_nlo->Scale(0.12550288/h_dAbsEta_nlo->GetEntries());
    float h_dAbsEta_binWidth = ((h_dAbsEta->GetXaxis()->GetXmax())-(h_dAbsEta->GetXaxis()->GetXmin()))/ (h_dAbsEta->GetNbinsX());
    h_dAbsEta->Scale(0.108607/h_dAbsEta->GetEntries());
    h_dAbsEta->Scale(1.0/h_dAbsEta_binWidth); // Cross-section weight in makeclass

    h_dAbsEta_nlo->Draw("E1, SAME");
    h_dAbsEta->SetLineColor(6);
    h_dAbsEta->Draw("E1, SAME");
    h_dAbsEta->SetMinimum(0.1);
    h_dAbsEta_lo->SetLineColor(12);
    h_dAbsEta_lo->Draw("E1, SAME");

    auto l1 = new TLegend(0.4,0.25,0.6,0.45);
    l1->SetBorderSize(0);
    l1->AddEntry(h_dAbsEta_nlo, "GGG mcfm NLO", "l");
    l1->AddEntry(h_dAbsEta_lo, "GGG mcfm LO", "l");
    l1->AddEntry(h_dAbsEta, "GGGJetsSherpa", "l");
    l1->Draw();
    c1->SaveAs("plots/triphoton_DAbsEta"+phoPairStr+"_sherpaVsMcfm.pdf");
  } // end Pt


  void ComparePtDists(TFile *fSherpaSource, TFile *fMCFM_nlo, TFile *fMCFM_lo, TString phoNumStr){

    std::cout << "Get Pt for Photon " << phoNumStr <<  std::endl;
    std::cout << "h_pt"+phoNumStr << std::endl;
    TH1D *h_pt = (TH1D*) fSherpaSource->Get("h_pT"+phoNumStr);
    int phoNum = phoNumStr.Atoi();

    TString mcfmHistID = "id11";
    if (phoNum == 2) mcfmHistID = "id13";
    if (phoNum == 3) mcfmHistID = "id15";

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
    l1->AddEntry(h_pt, "GGGJetsSherpa", "l");
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
    TH1F *h_mAAA_nlo = (TH1F*) fMCFM_nlo->Get("id29");
    TH1F *h_mAAA_lo  = (TH1F*)  fMCFM_lo->Get("id29");

    //------- MCFM vs Sherpa
    TCanvas *c = new TCanvas("c","c",800,600);

    TPad *padMainPlot = new TPad("padMainPlot", "", 0, 0.3, 1, 1.0);
    padMainPlot->SetBottomMargin(0); // joins upper and lower plot
    padMainPlot->Draw();
    padMainPlot->cd();

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

    //ratio Pad
    c->cd(); // return to main canvas before defining ratio pad.
    TPad *padRatio = new TPad("padRatio", "", 0, 0.05, 1, 0.3);
    padRatio->SetTopMargin(0);
    padRatio->SetBottomMargin(0.4);
    padRatio->Draw();
    padRatio->cd();
    padRatio->SetGrid(0,1);

    TH1D *h_ratio_nlo = (TH1D*) h_mAAA_nlo->Clone("h_mAAA_nlo");
    h_ratio_nlo->SetLineColor(kBlack);
    h_ratio_nlo->SetMarkerColor(kBlack);
    // h_ratio_nlo->SetMinimum(0.4);
    // h_ratio_nlo->SetMaximum(1.1);
    h_ratio_nlo->SetStats(0);
    h_ratio_nlo->Divide(h_mAAA_lo);
    h_ratio_nlo->Draw("ep");
    h_ratio_nlo->SetTitle("");
    h_ratio_nlo->GetYaxis()->SetTitle("Pred./Data (LO)");
    // h_ratio_nlo->GetYaxis()->SetTitleSize(25);
    h_ratio_nlo->GetYaxis()->SetTitleOffset(0.8);
    // h_ratio_nlo->GetYaxis()->SetNdivisions(505);

    // h_ratio_nlo->GetYaxis()->CenterTitle();
    // h_ratio_nlo->GetYaxis()->SetTitleFont(43);

    // h_ratio_nlo->GetYaxis()->SetLabelSize(16);

    //FIXME: Set Xaxis Title
    // if (name == "pt") {
    //   h_ratio_nlo->GetXaxis()->SetTitle("p_{T} (GeV)");
    //   h_ratio_nlo->GetXaxis()->SetRangeUser(0,1500);
    // }
    // if (name == "eta") {
    //   h_ratio_nlo->GetXaxis()->SetTitle("#eta");
    //   h_ratio_nlo->GetXaxis()->SetRangeUser(-3,3);
    // }
    // if (name == "phi") {
    //   h_ratio_nlo->GetXaxis()->SetTitle("#phi");
    //   h_ratio_nlo->GetXaxis()->SetRangeUser(-4,4);
    // }
    // if (name == "phi" || name == "eta") h_ratio_nlo->GetXaxis()->CenterTitle();

    h_ratio_nlo->GetXaxis()->SetTitle("m_{#gamma #gamma #gamma} (GeV)");
    h_ratio_nlo->GetXaxis()->SetTitleSize(25);
    h_ratio_nlo->GetXaxis()->SetTitleFont(43);
    h_ratio_nlo->GetXaxis()->SetTitleOffset(4.5);
    h_ratio_nlo->GetXaxis()->SetLabelFont(43);
    h_ratio_nlo->GetXaxis()->SetLabelSize(16);

    c->SaveAs("plots/triphoton_Minv_sherpaVsMcfm.pdf");

    std::cout << h_mAAA->GetEntries() << std::endl;
    std::cout << h_mAAA_nlo->GetEntries() << std::endl;
    std::cout << h_mAAA_lo->GetEntries() << std::endl;


  }

} // end namespace

#endif
