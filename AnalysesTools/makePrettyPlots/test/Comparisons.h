#ifndef Comparisons_h
#define Comparisons_h

namespace TriPhotons
{
  // double lumi2017 = 80.94; // fb-1 for HLT_20_20_20 and HLT_30_30_10
  // double lumi2018 = 80.94; // fb-1 for HLT 20_20_20 and HLT_30_30_10
  double lumiTotal            = 80.94; // for HLT Triggers 2017 and 2018
  double xsec_nlo_15_15_15    = 125.50288; // fb
  double xsec_lo_15_15_15     = 46.3964; //fb
  double xsec_sherpa_15_15_15 = 108.607; //fb

  // bool is15_15_15 = true;

  // if is15_15_15
  double xsec_lo     = xsec_lo_15_15_15;
  double xsec_nlo    = xsec_nlo_15_15_15;
  double xsec_sherpa = xsec_sherpa_15_15_15;

  void createRatio(TH1F* hNumerator, TH1F* hDenominator, Color_t color, float min=-1, float max=4, TString yTitle="Pred./LO", TString xTitle="m_{#gamma #gamma #gamma} (GeV)", bool showRatio=false, TString experiment="CMS"){
    TH1F *hRatio = (TH1F*) hNumerator->Clone("hNumerator");
    hRatio->SetLineColor(color);
    hRatio->SetMarkerColor(color);
    // hRatio->SetMinimum(0.4);
    // hRatio->SetMaximum(1.1);
    hRatio->SetStats(0);
    hRatio->Divide(hDenominator);
    hRatio->Draw("ep, SAME");
    hRatio->SetTitle("");
    hRatio->GetYaxis()->SetTitle("Pred./Data (LO)");
    // hRatio->GetYaxis()->SetTitleSize(25);
    hRatio->GetYaxis()->SetTitleOffset(0.8);
    hRatio->GetXaxis()->SetTitle("m_{#gamma #gamma #gamma} (GeV)");
    hRatio->GetXaxis()->SetTitleSize(25);
    hRatio->GetXaxis()->SetTitleFont(43);
    hRatio->GetXaxis()->SetTitleOffset(4.5);
    hRatio->GetXaxis()->SetLabelFont(43);
    hRatio->GetXaxis()->SetLabelSize(16);
    hRatio->SetMinimum(min);
    hRatio->SetMaximum(max);
  }

  void createRatio(TH1F* hNumerator, TH1D* hDenominator, Color_t color, float min=-1, float max=3.5, TString yTitle="Pred./LO", TString xTitle="m_{#gamma #gamma #gamma} (GeV)", bool showRatio=false, TString experiment="CMS"){
    TH1F *hRatio = (TH1F*) hNumerator->Clone("hNumerator");
    hRatio->SetLineColor(color);
    hRatio->SetMarkerColor(color);
    // hRatio->SetMinimum(0.4);
    // hRatio->SetMaximum(1.1);
    hRatio->SetStats(0);
    hRatio->Divide(hDenominator);
    hRatio->Draw("ep");
    hRatio->SetTitle("");
    hRatio->GetYaxis()->SetTitle("Pred./Data (LO)");
    // hRatio->GetYaxis()->SetTitleSize(25);
    hRatio->GetYaxis()->SetTitleOffset(0.8);
    hRatio->GetXaxis()->SetTitle("m_{#gamma #gamma #gamma} (GeV)");
    hRatio->GetXaxis()->SetTitleSize(25);
    hRatio->GetXaxis()->SetTitleFont(43);
    hRatio->GetXaxis()->SetTitleOffset(4.5);
    hRatio->GetXaxis()->SetLabelFont(43);
    hRatio->GetXaxis()->SetLabelSize(16);
  }

  void CompareDPhiDists(TFile *fSherpaSource, TFile *fMCFM_nlo, TFile *fMCFM_lo, TString phoNum1, TString phoNum2, bool showRatio=false, TString experiment="CMS")
  {

    TString phoPairStr = phoNum1+phoNum2;
    std::cout << "PhotonPair " << phoNum1 << phoNum2 <<  std::endl;
    std::cout << "h_dPhi"+phoNum1+phoNum2 << std::endl;
    TH1D *h_dPhi = (TH1D*) fSherpaSource->Get("h_dPhi"+phoNum1+phoNum2);

    TString mcfmHistID = "id7";
    if (phoPairStr == "13") mcfmHistID = "id8";
    if (phoPairStr == "23") mcfmHistID = "id9";

    TH1F *h_dPhi_nlo = (TH1F*) fMCFM_nlo->Get(mcfmHistID);
    TH1F *h_dPhi_lo  = (TH1F*)  fMCFM_lo->Get(mcfmHistID);

    TCanvas *c1 = new TCanvas("c1","c1",800,600);

    h_dPhi_lo->Scale(lumiTotal*xsec_lo/h_dPhi_lo->GetEntries());
    h_dPhi_nlo->Scale(lumiTotal*xsec_nlo/h_dPhi_nlo->GetEntries());
    float h_dPhi_binWidth = ((h_dPhi->GetXaxis()->GetXmax())-(h_dPhi->GetXaxis()->GetXmin()))/ (h_dPhi->GetNbinsX());
    h_dPhi->Scale(lumiTotal*xsec_sherpa/h_dPhi->GetEntries());
    h_dPhi->Scale(1.0/h_dPhi_binWidth); // Cross-section weight in makeclass

    h_dPhi_nlo->Draw("E1, SAME");
    h_dPhi->SetLineColor(6);
    h_dPhi->Draw("E1, SAME");
    h_dPhi->SetMinimum(0.1);
    h_dPhi_lo->SetLineColor(12);
    h_dPhi_lo->Draw("E1, SAME");

    TLatex *t_label = new TLatex();
    t_label->SetTextSize(0.03);
    t_label->SetTextAlign(12);
    t_label->SetTextAlign(12);
    t_label->DrawLatexNDC(0.15,0.78, experiment);
    t_label->DrawLatexNDC(0.15,0.74, "#sqrt{s}= 13 TeV, 80.94 fb^{-1}");
    t_label->SetTextFont(42);

    auto l1 = new TLegend(0.15,0.61,0.35,0.71);
    l1->SetBorderSize(0);
    l1->AddEntry(h_dPhi_nlo, "GGG mcfm NLO", "l");
    l1->AddEntry(h_dPhi_lo, "GGG mcfm LO", "l");
    l1->AddEntry(h_dPhi, "GGGJetsSherpa", "l");
    l1->Draw();
    c1->SaveAs("plots/triphoton_DPhi"+phoPairStr+"_sherpaVsMcfm.pdf");
  } // end Pt

  void CompareMggDists(TFile *fSherpaSource, TFile *fMCFM_nlo, TFile *fMCFM_lo, TString phoNum1, TString phoNum2, bool showRatio=false, TString experiment="CMS"){
      TString phoPairStr = phoNum1+phoNum2;
      std::cout << "PhotonPair " << phoPairStr <<  std::endl;
      std::cout << "h_mA" << phoNum1 << "A" << phoNum2 << std::endl;
      TH1D *h_mAA = (TH1D*) fSherpaSource->Get("h_mA"+phoNum1+"A"+phoNum2);

      TString mcfmHistID = "id17";
      if (phoPairStr == "13") mcfmHistID = "id21";
      if (phoPairStr == "23") mcfmHistID = "id25";

      TH1F *h_mAA_nlo = (TH1F*) fMCFM_nlo->Get(mcfmHistID);
      TH1F *h_mAA_lo  = (TH1F*)  fMCFM_lo->Get(mcfmHistID);

      TCanvas *c1 = new TCanvas("c1","c1",600,600);
      gPad->SetLogy();

      h_mAA_lo->Scale(lumiTotal*xsec_lo/h_mAA_lo->GetEntries());
      h_mAA_nlo->Scale(lumiTotal*xsec_nlo/h_mAA_nlo->GetEntries());
      float h_mAA_binWidth = ((h_mAA->GetXaxis()->GetXmax())-(h_mAA->GetXaxis()->GetXmin()))/ (h_mAA->GetNbinsX());
      h_mAA->Scale(lumiTotal*xsec_sherpa/h_mAA->GetEntries());
      h_mAA->Scale(1.0/h_mAA_binWidth); // Cross-section weight in makeclass

      h_mAA_nlo->Draw("E1, SAME");
      h_mAA->SetLineColor(6);
      h_mAA->Draw("E1, SAME");
      h_mAA->SetMinimum(0.1);
      h_mAA_lo->SetLineColor(12);
      h_mAA_lo->Draw("E1, SAME");

      TLatex *t_label = new TLatex();
      t_label->SetTextSize(0.03);
      t_label->SetTextAlign(12);
      t_label->SetTextAlign(12);
      t_label->DrawLatexNDC(0.65,0.78, experiment);
      t_label->DrawLatexNDC(0.65,0.74, "#sqrt{s}= 13 TeV, 80.94 fb^{-1}");
      t_label->SetTextFont(42);

      auto l1 = new TLegend(0.65,0.61,0.85,0.71);
      l1->SetBorderSize(0);
      l1->AddEntry(h_mAA_nlo, "GGG mcfm NLO", "l");
      l1->AddEntry(h_mAA_lo, "GGG mcfm LO", "l");
      l1->AddEntry(h_mAA, "GGGJetsSherpa", "l");
      l1->Draw();
      c1->SaveAs("plots/triphoton_mAA"+phoPairStr+"_sherpaVsMcfm.pdf");
  }

  void CompareDAbsEtaDists(TFile *fSherpaSource, TFile *fMCFM_nlo, TFile *fMCFM_lo, TString phoNum1, TString phoNum2, bool showRatio=false, TString experiment="CMS")
  {

    TString phoPairStr = phoNum1+phoNum2;
    std::cout << "PhotonPair " << phoNum1 << phoNum2 <<  std::endl;
    std::cout << "h_dAbsEta"+phoNum1+phoNum2 << std::endl;
    TH1D *h_dAbsEta = (TH1D*) fSherpaSource->Get("h_dAbsEta"+phoNum1+phoNum2);

    TString mcfmHistID = "id20";
    if (phoPairStr == "13") mcfmHistID = "id24";
    if (phoPairStr == "23") mcfmHistID = "id27";

    TH1F *h_dAbsEta_nlo = (TH1F*) fMCFM_nlo->Get(mcfmHistID);
    TH1F *h_dAbsEta_lo  = (TH1F*)  fMCFM_lo->Get(mcfmHistID);

    TCanvas *c1 = new TCanvas("c1","c1",800,600);

    h_dAbsEta_lo->Scale(lumiTotal*xsec_lo/h_dAbsEta_lo->GetEntries());
    h_dAbsEta_nlo->Scale(lumiTotal*xsec_nlo/h_dAbsEta_nlo->GetEntries());
    float h_dAbsEta_binWidth = ((h_dAbsEta->GetXaxis()->GetXmax())-(h_dAbsEta->GetXaxis()->GetXmin()))/ (h_dAbsEta->GetNbinsX());
    h_dAbsEta->Scale(lumiTotal*xsec_sherpa/h_dAbsEta->GetEntries());
    h_dAbsEta->Scale(1.0/h_dAbsEta_binWidth); // Cross-section weight in makeclass

    h_dAbsEta_nlo->Draw("E1, SAME");
    h_dAbsEta->SetLineColor(6);
    h_dAbsEta->Draw("E1, SAME");
    h_dAbsEta->SetMinimum(0.1);
    h_dAbsEta_lo->SetLineColor(12);
    h_dAbsEta_lo->Draw("E1, SAME");

    TLatex *t_label = new TLatex();
    t_label->SetTextSize(0.03);
    t_label->SetTextAlign(12);
    t_label->SetTextAlign(12);
    t_label->DrawLatexNDC(0.65,0.78, experiment);
    t_label->DrawLatexNDC(0.65,0.74, "#sqrt{s}= 13 TeV, 80.94 fb^{-1}");
    t_label->SetTextFont(42);

    auto l1 = new TLegend(0.65,0.61,0.85,0.71);
    l1->SetBorderSize(0);
    l1->AddEntry(h_dAbsEta_nlo, "GGG mcfm NLO", "l");
    l1->AddEntry(h_dAbsEta_lo, "GGG mcfm LO", "l");
    l1->AddEntry(h_dAbsEta, "GGGJetsSherpa", "l");
    l1->Draw();
    c1->SaveAs("plots/triphoton_DAbsEta"+phoPairStr+"_sherpaVsMcfm.pdf");
  } // end Pt

  void CompareEtaDists(TFile *fSherpaSource, TFile *fMCFM_nlo, TFile *fMCFM_lo, TString phoNum, bool showRatio=false, TString experiment="CMS")
  {

    std::cout << "Get Eta for Photon " << phoNum <<  std::endl;
    std::cout << "h_eta"+phoNum << std::endl;
    TH1D *h_eta = (TH1D*) fSherpaSource->Get("h_eta"+phoNum);

    TString mcfmHistID = "id12";
    if (phoNum == "2") mcfmHistID = "id14";
    if (phoNum == "3") mcfmHistID = "id16";

    TH1F *h_eta_nlo = (TH1F*) fMCFM_nlo->Get(mcfmHistID);
    TH1F *h_eta_lo  = (TH1F*)  fMCFM_lo->Get(mcfmHistID);

    TCanvas *c1 = new TCanvas("c1","c1",800,600);

    h_eta_lo->Scale(lumiTotal*xsec_lo/h_eta_lo->GetEntries());
    h_eta_nlo->Scale(lumiTotal*xsec_nlo/h_eta_nlo->GetEntries());
    float h_eta_binWidth = ((h_eta->GetXaxis()->GetXmax())-(h_eta->GetXaxis()->GetXmin()))/ (h_eta->GetNbinsX());
    h_eta->Scale(lumiTotal*xsec_sherpa/h_eta->GetEntries());
    h_eta->Scale(1.0/h_eta_binWidth); // Cross-section weight in makeclass

    h_eta_nlo->Draw("E1, SAME");
    h_eta->SetLineColor(6);
    h_eta->Draw("E1, SAME");
    h_eta->SetMinimum(0.1);
    h_eta_lo->SetLineColor(12);
    h_eta_lo->Draw("E1, SAME");

    TLatex *t_label = new TLatex();
    t_label->SetTextSize(0.03);
    t_label->SetTextAlign(12);
    t_label->SetTextAlign(12);
    t_label->DrawLatexNDC(0.65,0.78, experiment);
    t_label->DrawLatexNDC(0.65,0.74, "#sqrt{s}= 13 TeV, 80.94 fb^{-1}");
    t_label->SetTextFont(42);

    auto l1 = new TLegend(0.65,0.61,0.85,0.71);
    l1->SetBorderSize(0);
    l1->AddEntry(h_eta_nlo, "GGG mcfm NLO", "l");
    l1->AddEntry(h_eta_lo, "GGG mcfm LO", "l");
    l1->AddEntry(h_eta, "GGGJetsSherpa", "l");
    l1->Draw();
    c1->SaveAs("plots/triphoton_eta"+phoNum+"_sherpaVsMcfm.pdf");
  } // end Pt


  void ComparePtDists(TFile *fSherpaSource, TFile *fMCFM_nlo, TFile *fMCFM_lo, TString phoNumStr, bool showRatio=false, TString experiment="CMS"){

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
    gPad->SetLogy();

    h_pt_lo->Scale(lumiTotal*xsec_lo/h_pt_lo->GetEntries());
    h_pt_nlo->Scale(lumiTotal*xsec_nlo/h_pt_nlo->GetEntries());
    float h_pt_binWidth = ((h_pt->GetXaxis()->GetXmax())-(h_pt->GetXaxis()->GetXmin()))/ (h_pt->GetNbinsX());
    h_pt->Scale(lumiTotal*xsec_sherpa/h_pt->GetEntries());
    h_pt->Scale(1.0/h_pt_binWidth); // Cross-section weight in makeclass

    h_pt_nlo->Draw("E1, SAME");
    h_pt->SetLineColor(6);
    h_pt->Draw("E1, SAME");
    h_pt->SetMinimum(0.1);
    h_pt_lo->SetLineColor(12);
    h_pt_lo->Draw("E1, SAME");

    TLatex *t_label = new TLatex();
    t_label->SetTextSize(0.03);
    t_label->SetTextAlign(12);
    t_label->SetTextAlign(12);
    t_label->DrawLatexNDC(0.65,0.78, experiment);
    t_label->DrawLatexNDC(0.65,0.74, "#sqrt{s}= 13 TeV, 80.94 fb^{-1}");
    t_label->SetTextFont(42);

    auto l1 = new TLegend(0.65,0.61,0.85,0.71);
    l1->SetBorderSize(0);
    l1->AddEntry(h_pt_nlo, "GGG mcfm NLO", "l");
    l1->AddEntry(h_pt_lo, "GGG mcfm LO", "l");
    l1->AddEntry(h_pt, "GGGJetsSherpa", "l");
    l1->Draw();
    c1->SaveAs("plots/triphoton_Pt"+phoNumStr+"_sherpaVsMcfm.pdf");
  } // end Pt

  void CompareMggg(TFile *fSherpaSource, TFile *fMCFM_nlo, TFile *fMCFM_lo, bool showRatio=false, TString experiment="CMS"){
    /** Make baseline comparisons of Sherpa with MCFM **/
    /** Compares differential cross section measurements as a function of Mgg**/

    TString hminvstr = "h_minv";
    std::cout << "Get Minv " << hminvstr << std::endl;
    TH1D *h_mAAA = (TH1D*) fSherpaSource->Get(hminvstr); //just for debugging.
    //------- MCFM NLO vs LO
    TH1F *h_mAAA_nlo = (TH1F*) fMCFM_nlo->Get("id29");
    TH1F *h_mAAA_lo  = (TH1F*)  fMCFM_lo->Get("id29");

    //------- MCFM vs Sherpa
    TCanvas *c = new TCanvas("c","c",600,600);

    if (showRatio) {
      TPad *padMainPlot = new TPad("padMainPlot", "", 0, 0.3, 1, 1.0);
      padMainPlot->SetBottomMargin(0.2); // joins upper and lower plot
      padMainPlot->Draw();
      padMainPlot->cd();
    }

    //h_mAAA_nlo->Scale(1/h_mAAA_nlo->GetEntries());
    // Differential Cross section = Cross section / bin width

    // Already a differential cross-section!
    // h_mAAA_lo->Scale(lumiTotal*xsec_lo/h_mAAA_lo->GetEntries());
    // h_mAAA_nlo->Scale(lumiTotal*xsec_nlo/h_mAAA_nlo->GetEntries());
    // h_mAAA_lo->Scale(lumiTotal*xsec_lo);
    // h_mAAA_nlo->Scale(lumiTotal*xsec_nlo);

    float h_mAAA_binWidth = ((h_mAAA->GetXaxis()->GetXmax())-(h_mAAA->GetXaxis()->GetXmin()))/ (h_mAAA->GetNbinsX()); // uniform
    // if it's not, get bin content and get bin width for ith bin
    h_mAAA->Scale(1.0/h_mAAA->GetEntries()); // Fraction of simulated events FIXME: check event weight in sherpa sample
    h_mAAA->Scale(xsec_sherpa);
    h_mAAA->Scale(1.0/h_mAAA_binWidth); //Cross-section weight in makeclass


    // h_mAAA->Scale(0.09981/h_mAAA->GetEntries()); // Cross-section weight in makeclass
    //h_mAAA->Scale(0.09981/h_mAAA->GetEntries()); // just for debugging. h_mAAA is unweighted in makeclass

    h_mAAA_nlo->Draw("E1, SAME");
    h_mAAA->SetLineColor(6);
    h_mAAA->Draw("E1, SAME");
    h_mAAA->SetMinimum(0.1);

    h_mAAA_lo->SetLineColor(12);
    h_mAAA_lo->Draw("E1, SAME");
    gPad->SetLogy();

    TLatex *t_label = new TLatex();
    t_label->SetTextSize(0.03);
    t_label->SetTextAlign(12);
    t_label->SetTextAlign(12);
    t_label->DrawLatexNDC(0.4,0.52, experiment);
    t_label->DrawLatexNDC(0.4,0.48, "#sqrt{s}= 13 TeV, 80.94 fb^{-1}");
    t_label->SetTextFont(42);

    auto legsherpavsmcfm = new TLegend(0.4,0.35,0.6,0.45);
    legsherpavsmcfm->SetBorderSize(0);
    legsherpavsmcfm->AddEntry(h_mAAA_nlo, "GGG mcfm NLO", "l");
    legsherpavsmcfm->AddEntry(h_mAAA_lo, "GGG mcfm LO", "l");
    legsherpavsmcfm->AddEntry(h_mAAA, "GGGJetsSherpa", "l");
    legsherpavsmcfm->Draw();

    //ratio Pad

    if (showRatio) {
        c->cd(); // return to main canvas before defining ratio pad.
        TPad *padRatio = new TPad("padRatio", "", 0, 0.05, 1, 0.3);
        padRatio->SetTopMargin(0);
        padRatio->SetBottomMargin(0.4);
        padRatio->Draw();
        padRatio->cd();
        padRatio->SetGrid(0,1);

        // createRatio(h_mAAA_nlo, h_mAAA,kBlue);
        createRatio(h_mAAA_lo, h_mAAA, kMagenta);
    }

    c->SaveAs("plots/triphoton_Minv_sherpaVsMcfm.pdf");

    std::cout << h_mAAA->GetEntries() << std::endl;
    std::cout << h_mAAA_nlo->GetEntries() << std::endl;
    std::cout << h_mAAA_lo->GetEntries() << std::endl;

  }

} // end namespace

#endif
