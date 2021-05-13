#ifndef Comparisons_h
#define Comparisons_h
#include "Selections.h"

namespace TriPhotons
{

  double lumiTotal            = 80.94;     // for HLT Triggers 2017 and 2018
  double xsec_nlo_15_15_15    = 125.50288; // fb
  double xsec_lo_15_15_15     = 46.3964;   // fb
  double xsec_sherpa_15_15_15 = 108.607;   // fb
  double sherpa_th_lumi       = 165.726;   // fb which is greater than 150 fb-1;

  double xsec_lo     = xsec_lo_15_15_15;
  double xsec_nlo    = xsec_nlo_15_15_15;
  double xsec_sherpa = xsec_sherpa_15_15_15;

  // MCFM
  // 25_25_25 lo xsec: 8.641 fb
  // 35_35_15 lo xsec: 15.20 fb
  //
  // 25_25_25 nlo xsec: 21.74 fb
  // 35_35_15 nlo xsec: 36.20 fb

  void convertToDiffXsec(TH1D* hist, double nSimEvents = 17800){
    // Each event here has weight 1
    // If the Event_weightAll is already built-in, you don't have to use this except for the bin-width normalization

    // uniform binning
    float binWidth = ((hist->GetXaxis()->GetXmax())-(hist->GetXaxis()->GetXmin()))/ (hist->GetNbinsX());

    // Fraction of simulated Events
    //hist->Scale(1.0/hist->GetEntries()); // hist->Integral() better if the event weights aren't 1
    hist->Scale(1.0/nSimEvents); // Telling us the fraction of all events

    // Normalize to unit Lumi
    // N = xsec * Lumi -> Lumi = 1 unit luminosity normalization
    hist->Scale(xsec_sherpa); // For the same lumi, this is the number of events we expect from the sim
                              // Compare to a predicted data yield, put in a lumi that's realistic for data
    // Turn to differential cross-section (yield per unit lumi)

    // FIXME: Bin Width normalization after Event_weightAll when that's fixed
    hist->Scale(1.0/binWidth); // prediction per unit bin width
    // FIXME: Loop over bins, set bin content, divide by bin width (get bin width) for that bin for variable binning...
    std::cout << "nSimEvents: " << nSimEvents << "; Entries:" << hist->GetEntries() << "; histInt xsec: " << hist->Integral()<<std::endl;
  }

// FIXME Moved to Selections.h
  // void createRatio(TH1F* hNumerator, TH1F* hDenominator, Color_t color, float min=-1, float max=4, TString yTitle="Pred./LO", TString xTitle="m_{#gamma #gamma #gamma} (GeV)", bool showRatio=false, TString experiment="CMS"){
  //   TH1F *hRatio = (TH1F*) hNumerator->Clone("hNumerator");
  //   hRatio->SetLineColor(color);
  //   hRatio->SetMarkerColor(color);
  //   // hRatio->SetMinimum(0.4);
  //   // hRatio->SetMaximum(1.1);
  //   hRatio->SetStats(0);
  //   hRatio->Divide(hDenominator);
  //   hRatio->Draw("ep, SAME");
  //   hRatio->SetTitle("");
  //   hRatio->GetYaxis()->SetTitle("Pred./Data (LO)");
  //   // hRatio->GetYaxis()->SetTitleSize(25);
  //   hRatio->GetYaxis()->SetTitleOffset(0.8);
  //   hRatio->GetXaxis()->SetTitle("m_{#gamma #gamma #gamma} (GeV)");
  //   hRatio->GetXaxis()->SetTitleSize(25);
  //   hRatio->GetXaxis()->SetTitleFont(43);
  //   hRatio->GetXaxis()->SetTitleOffset(4.5);
  //   hRatio->GetXaxis()->SetLabelFont(43);
  //   hRatio->GetXaxis()->SetLabelSize(16);
  //   hRatio->SetMinimum(min);
  //   hRatio->SetMaximum(max);
  // }
  //
  // void createRatio(TH1F* hNumerator, TH1D* hDenominator, Color_t color, float min=-1, float max=3.5, TString yTitle="Pred./LO", TString xTitle="m_{#gamma #gamma #gamma} (GeV)", bool showRatio=false, TString experiment="CMS"){
  //   TH1F *hRatio = (TH1F*) hNumerator->Clone("hNumerator");
  //   hRatio->SetLineColor(color);
  //   hRatio->SetMarkerColor(color);
  //   // hRatio->SetMinimum(0.4);
  //   // hRatio->SetMaximum(1.1);
  //   hRatio->SetStats(0);
  //   hRatio->Divide(hDenominator);
  //   hRatio->Draw("ep");
  //   hRatio->SetTitle("");
  //   hRatio->GetYaxis()->SetTitle("Pred./Data (LO)");
  //   // hRatio->GetYaxis()->SetTitleSize(25);
  //   hRatio->GetYaxis()->SetTitleOffset(0.8);
  //   hRatio->GetXaxis()->SetTitle("m_{#gamma #gamma #gamma} (GeV)");
  //   hRatio->GetXaxis()->SetTitleSize(25);
  //   hRatio->GetXaxis()->SetTitleFont(43);
  //   hRatio->GetXaxis()->SetTitleOffset(4.5);
  //   hRatio->GetXaxis()->SetLabelFont(43);
  //   hRatio->GetXaxis()->SetLabelSize(16);
  // }

  void CompareMggg(TFile *fSherpaSource, TFile *fMCFM_nlo, TFile *fMCFM_lo, bool isMinPt25 = false, bool isMinPt35_35_15 = false, bool showRatio=false, TString experiment="CMS"){
    /** Make baseline comparisons of Sherpa with MCFM **/
    /** Compares differential cross section measurements as a function of Mgg**/

    TString hminvstr;
    if (!isMinPt25 && !isMinPt35_35_15) hminvstr = "h_minv";
    if (isMinPt25)       hminvstr = "h_pT25_minv";
    if (isMinPt35_35_15) hminvstr = "h_pT35_35_15_minv";

    TH1D *h_mAAA = (TH1D*) fSherpaSource->Get(hminvstr); // Hist cross section as y-axis
    TH1F *h_mAAA_nlo = (TH1F*) fMCFM_nlo->Get("id29");
    TH1F *h_mAAA_lo  = (TH1F*)  fMCFM_lo->Get("id29");
    convertToDiffXsec(h_mAAA);

    //------- MCFM vs Sherpa
    TCanvas *c = new TCanvas("c","c",600,600);

    // if (showRatio) {
    //   TPad *padMainPlot = new TPad("padMainPlot", "", 0, 0.3, 1, 1.0);
    //   padMainPlot->SetBottomMargin(0.2); // joins upper and lower plot
    //   padMainPlot->Draw();
    //   padMainPlot->cd();
    // }

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

    // //ratio Pad
    // if (showRatio) {
    //     c->cd(); // return to main canvas before defining ratio pad.
    //     TPad *padRatio = new TPad("padRatio", "", 0, 0.05, 1, 0.3);
    //     padRatio->SetTopMargin(0);
    //     padRatio->SetBottomMargin(0.4);
    //     padRatio->Draw();
    //     padRatio->cd();
    //     padRatio->SetGrid(0,1);
    //
    //     // createRatio(h_mAAA_nlo, h_mAAA,kBlue);
    //     createRatio(h_mAAA_lo, h_mAAA, kMagenta);
    // }

    TString outFile = "triphoton_Minv_sherpaVsMcfm";
    if (isMinPt25) outFile += "_25";
    if (isMinPt35_35_15) outFile += "_35";
    c->SaveAs("plots/"+outFile+".pdf");

    std::cout << h_mAAA->GetEntries() << std::endl;

  }

  void ComparePtDists(TFile *fSherpaSource, TFile *fMCFM_nlo, TFile *fMCFM_lo, TString phoNumStr, bool isMinPt25 = false, bool isMinPt35_35_15 = false, bool showRatio=false, TString experiment="CMS"){

    std::cout << "Get Pt for Photon " << phoNumStr <<  std::endl;

    TString histStr;
    if (!isMinPt25 && !isMinPt35_35_15) histStr = "h_pT"+phoNumStr;
    if (isMinPt25)       histStr = "h_pT25_pT"+phoNumStr;
    if (isMinPt35_35_15) histStr = "h_pT35_35_15_pT"+phoNumStr;
    std::cout << histStr << std::endl;

    TH1D *h_pt = (TH1D*) fSherpaSource->Get(histStr);
    convertToDiffXsec(h_pt);
    int phoNum = phoNumStr.Atoi();

    TString mcfmHistID = "id11";
    if (phoNum == 2) mcfmHistID = "id13";
    if (phoNum == 3) mcfmHistID = "id15";

    TH1F *h_pt_nlo = (TH1F*) fMCFM_nlo->Get(mcfmHistID);
    TH1F *h_pt_lo  = (TH1F*)  fMCFM_lo->Get(mcfmHistID);

    TCanvas *c1 = new TCanvas("c1","c1",800,600);
    gPad->SetLogy();

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

    TString outFile = "triphoton_Pt"+phoNumStr+"_sherpaVsMcfm";
    if (isMinPt25) outFile += "_25";
    if (isMinPt35_35_15) outFile += "_35";
    c1->SaveAs("plots/"+outFile+".pdf");

    std::cout << h_pt->GetEntries() << std::endl;

  } // end Pt


  void CompareDPhiDists(TFile *fSherpaSource, TFile *fMCFM_nlo, TFile *fMCFM_lo, TString phoNum1, TString phoNum2, bool isMinPt25 = false, bool isMinPt35_35_15 = false, bool showRatio=false, TString experiment="CMS")
  {

    TString phoPairStr = phoNum1+phoNum2;
    std::cout << "PhotonPair " << phoNum1 << phoNum2 <<  std::endl;
    std::cout << "h_dPhi"+phoNum1+phoNum2 << std::endl;
    TH1D *h_dPhi;
    if (!isMinPt25 && !isMinPt35_35_15) h_dPhi = (TH1D*) fSherpaSource->Get("h_dPhi"+phoNum1+phoNum2);
    if (isMinPt25) h_dPhi = (TH1D*) fSherpaSource->Get("h_pT25_dPhi"+phoNum1+phoNum2);
    if (isMinPt35_35_15) h_dPhi = (TH1D*) fSherpaSource->Get("h_pT35_35_15_dPhi"+phoNum1+phoNum2);
    convertToDiffXsec(h_dPhi);

    TString mcfmHistID = "id7";
    if (phoPairStr == "13") mcfmHistID = "id8";
    if (phoPairStr == "23") mcfmHistID = "id9";

    TH1F *h_dPhi_nlo = (TH1F*) fMCFM_nlo->Get(mcfmHistID);
    TH1F *h_dPhi_lo  = (TH1F*)  fMCFM_lo->Get(mcfmHistID);

    TCanvas *c1 = new TCanvas("c1","c1",800,600);

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

    TString outFile = "triphoton_DPhi"+phoPairStr+"_sherpaVsMcfm";
    if (isMinPt25) outFile += "_25";
    if (isMinPt35_35_15) outFile += "_35";
    c1->SaveAs("plots/"+outFile+".pdf");

  } // end dPhi

  void CompareMggDists(TFile *fSherpaSource, TFile *fMCFM_nlo, TFile *fMCFM_lo, TString phoNum1, TString phoNum2, bool isMinPt25 = false, bool isMinPt35_35_15 = false, bool showRatio=false, TString experiment="CMS"){
      TString phoPairStr = phoNum1+phoNum2;
      std::cout << "PhotonPair " << phoPairStr <<  std::endl;
      std::cout << "h_mA" << phoNum1 << "A" << phoNum2 << std::endl;
      TH1D *h_mAA;
      if (!isMinPt25 && !isMinPt35_35_15) h_mAA = (TH1D*) fSherpaSource->Get("h_mA"+phoNum1+"A"+phoNum2);
      if (isMinPt25) h_mAA = (TH1D*) fSherpaSource->Get("h_pT25_mA"+phoNum1+"A"+phoNum2);
      if (isMinPt35_35_15) h_mAA = (TH1D*) fSherpaSource->Get("h_pT35_35_15_mA"+phoNum1+"A"+phoNum2);
      convertToDiffXsec(h_mAA);

      TString mcfmHistID = "id17";
      if (phoPairStr == "13") mcfmHistID = "id21";
      if (phoPairStr == "23") mcfmHistID = "id25";

      TH1F *h_mAA_nlo = (TH1F*) fMCFM_nlo->Get(mcfmHistID);
      TH1F *h_mAA_lo  = (TH1F*)  fMCFM_lo->Get(mcfmHistID);

      TCanvas *c1 = new TCanvas("c1","c1",600,600);
      gPad->SetLogy();

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

      TString outFile = "triphoton_mAA"+phoPairStr+"_sherpaVsMcfm";
      if (isMinPt25) outFile += "_25";
      if (isMinPt35_35_15) outFile += "_35";
      c1->SaveAs("plots/"+outFile+".pdf");
  }

  void CompareDAbsEtaDists(TFile *fSherpaSource, TFile *fMCFM_nlo, TFile *fMCFM_lo, TString phoNum1, TString phoNum2, bool isMinPt25 = false, bool isMinPt35_35_15 = false, bool showRatio=false, TString experiment="CMS")
  {

    TString phoPairStr = phoNum1+phoNum2;
    std::cout << "PhotonPair " << phoNum1 << phoNum2 <<  std::endl;
    std::cout << "h_dAbsEta"+phoNum1+phoNum2 << std::endl;

    TH1D *h_dAbsEta;
    if (!isMinPt25 && !isMinPt35_35_15) h_dAbsEta = (TH1D*) fSherpaSource->Get("h_dAbsEta"+phoNum1+phoNum2);
    if (isMinPt25) h_dAbsEta = (TH1D*) fSherpaSource->Get("h_pT25_dAbsEta"+phoNum1+phoNum2);
    if (isMinPt35_35_15) h_dAbsEta = (TH1D*) fSherpaSource->Get("h_pT35_35_15_dAbsEta"+phoNum1+phoNum2);
    convertToDiffXsec(h_dAbsEta);

    // 
    // TString mcfmHistID = "id20";
    // if (phoPairStr == "13") mcfmHistID = "id24";
    // if (phoPairStr == "23") mcfmHistID = "id28";


    TString mcfmHistID = "id4";
    if (phoPairStr == "13") mcfmHistID = "id5"; //FIXME: call id4, 5, 6 instead
    if (phoPairStr == "23") mcfmHistID = "id6";

    TH1F *h_dAbsEta_nlo = (TH1F*) fMCFM_nlo->Get(mcfmHistID);
    TH1F *h_dAbsEta_lo  = (TH1F*)  fMCFM_lo->Get(mcfmHistID);

    TCanvas *c1 = new TCanvas("c1","c1",800,600);

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

    TString outFile = "triphoton_DAbsEta"+phoPairStr+"_sherpaVsMcfm";
    if (isMinPt25) outFile += "_25";
    if (isMinPt35_35_15) outFile += "_35";
    c1->SaveAs("plots/"+outFile+".pdf");

  } // end h_dAbsEta

  void CompareEtaDists(TFile *fSherpaSource, TFile *fMCFM_nlo, TFile *fMCFM_lo, TString phoNum, bool showRatio=false, TString experiment="CMS")
  {

    std::cout << "Get Eta for Photon " << phoNum <<  std::endl;
    std::cout << "h_eta"+phoNum << std::endl;
    TH1D *h_eta = (TH1D*) fSherpaSource->Get("h_eta"+phoNum);
    convertToDiffXsec(h_eta);

    TString mcfmHistID = "id12";
    if (phoNum == "2") mcfmHistID = "id14";
    if (phoNum == "3") mcfmHistID = "id16";

    TH1F *h_eta_nlo = (TH1F*) fMCFM_nlo->Get(mcfmHistID);
    TH1F *h_eta_lo  = (TH1F*)  fMCFM_lo->Get(mcfmHistID);

    TCanvas *c1 = new TCanvas("c1","c1",800,600);

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
  } // eta
} // end namespace

#endif
