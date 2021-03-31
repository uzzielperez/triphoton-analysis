#ifndef ATLASComparisons_h
#define ATLASComparisons_h

namespace TriPhotons
{
  double atlasLumi8TeV       = 20.2;    // fb
  double atlasXsecPaperMCFM8TeV  = 31.5;    // fb -1
  double atlasXsecMCFMnlo8TeV    = 28.36;   // FIXME(?) low priority m345 cut in src/User/gencuts.f and isolation or ask MCFM authors

  void atlasCompareMggg(TFile *fMCFM_nlo, TString experiment="ATLAS", double lumi_nlo = atlasLumi8TeV){

    //------- MCFM NLO vs LO
    TH1F *h_mAAA_nlo = (TH1F*) fMCFM_nlo->Get("id29");

    //------- MCFM vs Sherpa
    TCanvas *c = new TCanvas("c","c",600,600);

    // h_mAAA_nlo->Scale(lumi_nlo*atlasXsecMCFMnlo8TeV/h_mAAA_nlo->GetEntries());

    h_mAAA_nlo->Draw("E1, SAME");
    h_mAAA_nlo->SetAxisRange(50, 10.,"X");
    h_mAAA_nlo->SetAxisRange(0.001, 10.,"Y");
    gPad->SetLogy();

    TLatex *t_label = new TLatex();
    t_label->SetTextSize(0.03);
    t_label->SetTextAlign(12);
    t_label->SetTextAlign(12);
    t_label->DrawLatexNDC(0.6,0.72, experiment);
    t_label->DrawLatexNDC(0.6,0.68, "#sqrt{s}= 8 TeV, 20.2 fb^{-1}"); //FIXME add option to pickup right numbers
    t_label->SetTextFont(42);

    auto legsherpavsmcfm = new TLegend(0.6,0.55,0.8,0.65);
    legsherpavsmcfm->SetBorderSize(0);
    legsherpavsmcfm->AddEntry(h_mAAA_nlo, "GGG mcfm NLO", "l");
    legsherpavsmcfm->Draw();

    c->SaveAs("plots/atlasTriphotonMinv.pdf");

    std::cout << h_mAAA_nlo->GetEntries() << std::endl;

  }

  void atlasCompareMggDists(TFile *fMCFM_nlo, TString phoNum1, TString phoNum2, TString experiment="ATLAS", double lumi_nlo = atlasLumi8TeV){
      TString phoPairStr = phoNum1+phoNum2;
      std::cout << "PhotonPair " << phoPairStr <<  std::endl;

      TString mcfmHistID = "id17";
      double Xmax = 600;
      if (phoPairStr == "13") mcfmHistID = "id21"; Xmax = 300;
      if (phoPairStr == "23") mcfmHistID = "id25"; Xmax = 200;

      TH1F *h_mAA_nlo = (TH1F*) fMCFM_nlo->Get(mcfmHistID);

      TCanvas *c1 = new TCanvas("c1","c1",600,600);
      gPad->SetLogy();

      h_mAA_nlo->SetAxisRange(50, 10.,"X");
      h_mAA_nlo->SetAxisRange(0.001, 10.,"Y");
      h_mAA_nlo->Draw("E1, SAME");

      TLatex *t_label = new TLatex();
      t_label->SetTextSize(0.03);
      t_label->SetTextAlign(12);
      t_label->SetTextAlign(12);
      t_label->DrawLatexNDC(0.65,0.78, experiment);
      t_label->DrawLatexNDC(0.65,0.74, "#sqrt{s}= 8 TeV, 20.2 fb^{-1}");
      t_label->SetTextFont(42);

      auto l1 = new TLegend(0.65,0.61,0.85,0.71);
      l1->SetBorderSize(0);
      l1->AddEntry(h_mAA_nlo, "MCFM NLO", "l");
      l1->Draw();
      c1->SaveAs("plots/atlasDiphoton"+phoPairStr+".pdf");
  }

  void atlasComparePtDists(TFile *fMCFM_nlo, TString phoNumStr, bool showRatio=false, TString experiment="ATLAS",  double lumi_nlo = atlasLumi8TeV){

    std::cout << "Get Pt for Photon " << phoNumStr <<  std::endl;
    int phoNum = phoNumStr.Atoi();

    TString mcfmHistID = "id11";
    if (phoNum == 2) mcfmHistID = "id13";
    if (phoNum == 3) mcfmHistID = "id15";

    TH1F *h_pt_nlo = (TH1F*) fMCFM_nlo->Get(mcfmHistID);
    TH1F *h_pt_lo  = (TH1F*)  fMCFM_lo->Get(mcfmHistID);

    TCanvas *c1 = new TCanvas("c1","c1",800,600);
    gPad->SetLogy();

    h_pt_nlo->Draw("E1, SAME");

    TLatex *t_label = new TLatex();
    t_label->SetTextSize(0.03);
    t_label->SetTextAlign(12);
    t_label->SetTextAlign(12);
    t_label->DrawLatexNDC(0.65,0.78, experiment);
    t_label->DrawLatexNDC(0.65,0.74, "#sqrt{s}= 8 TeV, 20.2 fb^{-1}");
    t_label->SetTextFont(42);

    auto l1 = new TLegend(0.65,0.61,0.85,0.71);
    l1->SetBorderSize(0);
    l1->AddEntry(h_pt_nlo, "MCFM NLO", "l");
    l1->Draw();
    c1->SaveAs("plots/triphoton_Pt"+phoNumStr+"_sherpaVsMcfm.pdf");
  } // end Pt




  // void atlasCompareDAbsEtaDists(TFile *fMCFM_nlo, TString phoNum1, TString phoNum2, TString experiment="ATLAS")
  // {
  //
  //   TString phoPairStr = phoNum1+phoNum2;
  //   std::cout << "PhotonPair " << phoNum1 << phoNum2 <<  std::endl;
  //
  //   TString mcfmHistID = "id20";
  //   if (phoPairStr == "13") mcfmHistID = "id24";
  //   if (phoPairStr == "23") mcfmHistID = "id27";
  //
  //   TH1F *h_dAbsEta_nlo = (TH1F*) fMCFM_nlo->Get(mcfmHistID);
  //
  //   TCanvas *c1 = new TCanvas("c1","c1",800,600);
  //
  //   h_dAbsEta_nlo->Scale(lumi_nlo*atlasMCFMnlo8TeV/h_dAbsEta_nlo->GetEntries());
  //
  //   h_dAbsEta_nlo->Draw("E1, SAME");
  //   h_dAbsEta->SetLineColor(6);
  //   h_dAbsEta->Draw("E1, SAME");
  //   h_dAbsEta->SetMinimum(0.1);
  //   h_dAbsEta_lo->SetLineColor(12);
  //   h_dAbsEta_lo->Draw("E1, SAME");
  //
  //   TLatex *t_label = new TLatex();
  //   t_label->SetTextSize(0.03);
  //   t_label->SetTextAlign(12);
  //   t_label->SetTextAlign(12);
  //   t_label->DrawLatexNDC(0.65,0.78, experiment);
  //   t_label->DrawLatexNDC(0.65,0.74, "#sqrt{s}= 8 TeV, 20.2 fb^{-1}");
  //   t_label->SetTextFont(42);
  //
  //   auto l1 = new TLegend(0.65,0.61,0.85,0.71);
  //   l1->SetBorderSize(0);
  //   l1->AddEntry(h_dAbsEta_nlo, "GGG mcfm NLO", "l");
  //   l1->Draw();
  //   c1->SaveAs("plots/atlasTriphoton_DAbsEta"+phoPairStr+".pdf");
  // } // end Pt

  // void atlascreateRatio(TH1F* hNumerator, TH1F* hDenominator, Color_t color, float min=-1, float max=4, TString yTitle="Pred./LO", TString xTitle="m_{#gamma #gamma #gamma} (GeV)", bool showRatio=false, TString experiment="CMS"){
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
  // void atlascreateRatio(TH1F* hNumerator, TH1D* hDenominator, Color_t color, float min=-1, float max=3.5, TString yTitle="Pred./LO", TString xTitle="m_{#gamma #gamma #gamma} (GeV)", bool showRatio=false, TString experiment="CMS"){
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
  //
  // void atlasCompareDPhiDists(TFile *fSherpaSource, TFile *fMCFM_nlo, TFile *fMCFM_lo, TString phoNum1, TString phoNum2, bool showRatio=false, TString experiment="CMS")
  // {
  //
  //   TString phoPairStr = phoNum1+phoNum2;
  //   std::cout << "PhotonPair " << phoNum1 << phoNum2 <<  std::endl;
  //   std::cout << "h_dPhi"+phoNum1+phoNum2 << std::endl;
  //   TH1D *h_dPhi = (TH1D*) fSherpaSource->Get("h_dPhi"+phoNum1+phoNum2);
  //
  //   TString mcfmHistID = "id7";
  //   if (phoPairStr == "13") mcfmHistID = "id8";
  //   if (phoPairStr == "23") mcfmHistID = "id9";
  //
  //   TH1F *h_dPhi_nlo = (TH1F*) fMCFM_nlo->Get(mcfmHistID);
  //   TH1F *h_dPhi_lo  = (TH1F*)  fMCFM_lo->Get(mcfmHistID);
  //
  //   TCanvas *c1 = new TCanvas("c1","c1",800,600);
  //
  //   h_dPhi_lo->Scale(lumiTotal*0.0463964/h_dPhi_lo->GetEntries());
  //   h_dPhi_nlo->Scale(lumiTotal*0.12550288/h_dPhi_nlo->GetEntries());
  //   float h_dPhi_binWidth = ((h_dPhi->GetXaxis()->GetXmax())-(h_dPhi->GetXaxis()->GetXmin()))/ (h_dPhi->GetNbinsX());
  //   h_dPhi->Scale(lumiTotal*0.108607/h_dPhi->GetEntries());
  //   h_dPhi->Scale(1.0/h_dPhi_binWidth); // Cross-section weight in makeclass
  //
  //   h_dPhi_nlo->Draw("E1, SAME");
  //   h_dPhi->SetLineColor(6);
  //   h_dPhi->Draw("E1, SAME");
  //   h_dPhi->SetMinimum(0.1);
  //   h_dPhi_lo->SetLineColor(12);
  //   h_dPhi_lo->Draw("E1, SAME");
  //
  //   TLatex *t_label = new TLatex();
  //   t_label->SetTextSize(0.03);
  //   t_label->SetTextAlign(12);
  //   t_label->SetTextAlign(12);
  //   t_label->DrawLatexNDC(0.15,0.78, experiment);
  //   t_label->DrawLatexNDC(0.15,0.74, "#sqrt{s}= 13 TeV, 161.88 fb^{-1}");
  //   t_label->SetTextFont(42);
  //
  //   auto l1 = new TLegend(0.15,0.61,0.35,0.71);
  //   l1->SetBorderSize(0);
  //   l1->AddEntry(h_dPhi_nlo, "GGG mcfm NLO", "l");
  //   l1->AddEntry(h_dPhi_lo, "GGG mcfm LO", "l");
  //   l1->AddEntry(h_dPhi, "GGGJetsSherpa", "l");
  //   l1->Draw();
  //   c1->SaveAs("plots/triphoton_DPhi"+phoPairStr+"_sherpaVsMcfm.pdf");
  // } // end Pt
  //

  //
  // void atlasCompareDAbsEtaDists(TFile *fSherpaSource, TFile *fMCFM_nlo, TFile *fMCFM_lo, TString phoNum1, TString phoNum2, bool showRatio=false, TString experiment="CMS")
  // {
  //
  //   TString phoPairStr = phoNum1+phoNum2;
  //   std::cout << "PhotonPair " << phoNum1 << phoNum2 <<  std::endl;
  //   std::cout << "h_dAbsEta"+phoNum1+phoNum2 << std::endl;
  //   TH1D *h_dAbsEta = (TH1D*) fSherpaSource->Get("h_dAbsEta"+phoNum1+phoNum2);
  //
  //   TString mcfmHistID = "id20";
  //   if (phoPairStr == "13") mcfmHistID = "id24";
  //   if (phoPairStr == "23") mcfmHistID = "id27";
  //
  //   TH1F *h_dAbsEta_nlo = (TH1F*) fMCFM_nlo->Get(mcfmHistID);
  //   TH1F *h_dAbsEta_lo  = (TH1F*)  fMCFM_lo->Get(mcfmHistID);
  //
  //   TCanvas *c1 = new TCanvas("c1","c1",800,600);
  //
  //   h_dAbsEta_lo->Scale(lumiTotal*0.0463964/h_dAbsEta_lo->GetEntries());
  //   h_dAbsEta_nlo->Scale(lumiTotal*0.12550288/h_dAbsEta_nlo->GetEntries());
  //   float h_dAbsEta_binWidth = ((h_dAbsEta->GetXaxis()->GetXmax())-(h_dAbsEta->GetXaxis()->GetXmin()))/ (h_dAbsEta->GetNbinsX());
  //   h_dAbsEta->Scale(lumiTotal*0.108607/h_dAbsEta->GetEntries());
  //   h_dAbsEta->Scale(1.0/h_dAbsEta_binWidth); // Cross-section weight in makeclass
  //
  //   h_dAbsEta_nlo->Draw("E1, SAME");
  //   h_dAbsEta->SetLineColor(6);
  //   h_dAbsEta->Draw("E1, SAME");
  //   h_dAbsEta->SetMinimum(0.1);
  //   h_dAbsEta_lo->SetLineColor(12);
  //   h_dAbsEta_lo->Draw("E1, SAME");
  //
  //   TLatex *t_label = new TLatex();
  //   t_label->SetTextSize(0.03);
  //   t_label->SetTextAlign(12);
  //   t_label->SetTextAlign(12);
  //   t_label->DrawLatexNDC(0.65,0.78, experiment);
  //   t_label->DrawLatexNDC(0.65,0.74, "#sqrt{s}= 13 TeV, 161.88 fb^{-1}");
  //   t_label->SetTextFont(42);
  //
  //   auto l1 = new TLegend(0.65,0.61,0.85,0.71);
  //   l1->SetBorderSize(0);
  //   l1->AddEntry(h_dAbsEta_nlo, "GGG mcfm NLO", "l");
  //   l1->AddEntry(h_dAbsEta_lo, "GGG mcfm LO", "l");
  //   l1->AddEntry(h_dAbsEta, "GGGJetsSherpa", "l");
  //   l1->Draw();
  //   c1->SaveAs("plots/triphoton_DAbsEta"+phoPairStr+"_sherpaVsMcfm.pdf");
  // } // end Pt
  //
  // void atlasCompareEtaDists(TFile *fSherpaSource, TFile *fMCFM_nlo, TFile *fMCFM_lo, TString phoNum, bool showRatio=false, TString experiment="CMS")
  // {
  //
  //   std::cout << "Get Eta for Photon " << phoNum <<  std::endl;
  //   std::cout << "h_eta"+phoNum << std::endl;
  //   TH1D *h_eta = (TH1D*) fSherpaSource->Get("h_eta"+phoNum);
  //
  //   TString mcfmHistID = "id12";
  //   if (phoNum == "2") mcfmHistID = "id14";
  //   if (phoNum == "3") mcfmHistID = "id16";
  //
  //   TH1F *h_eta_nlo = (TH1F*) fMCFM_nlo->Get(mcfmHistID);
  //   TH1F *h_eta_lo  = (TH1F*)  fMCFM_lo->Get(mcfmHistID);
  //
  //   TCanvas *c1 = new TCanvas("c1","c1",800,600);
  //
  //   h_eta_lo->Scale(lumiTotal*0.0463964/h_eta_lo->GetEntries());
  //   h_eta_nlo->Scale(lumiTotal*0.12550288/h_eta_nlo->GetEntries());
  //   float h_eta_binWidth = ((h_eta->GetXaxis()->GetXmax())-(h_eta->GetXaxis()->GetXmin()))/ (h_eta->GetNbinsX());
  //   h_eta->Scale(lumiTotal*0.108607/h_eta->GetEntries());
  //   h_eta->Scale(1.0/h_eta_binWidth); // Cross-section weight in makeclass
  //
  //   h_eta_nlo->Draw("E1, SAME");
  //   h_eta->SetLineColor(6);
  //   h_eta->Draw("E1, SAME");
  //   h_eta->SetMinimum(0.1);
  //   h_eta_lo->SetLineColor(12);
  //   h_eta_lo->Draw("E1, SAME");
  //
  //   TLatex *t_label = new TLatex();
  //   t_label->SetTextSize(0.03);
  //   t_label->SetTextAlign(12);
  //   t_label->SetTextAlign(12);
  //   t_label->DrawLatexNDC(0.65,0.78, experiment);
  //   t_label->DrawLatexNDC(0.65,0.74, "#sqrt{s}= 13 TeV, 161.88 fb^{-1}");
  //   t_label->SetTextFont(42);
  //
  //   auto l1 = new TLegend(0.65,0.61,0.85,0.71);
  //   l1->SetBorderSize(0);
  //   l1->AddEntry(h_eta_nlo, "GGG mcfm NLO", "l");
  //   l1->AddEntry(h_eta_lo, "GGG mcfm LO", "l");
  //   l1->AddEntry(h_eta, "GGGJetsSherpa", "l");
  //   l1->Draw();
  //   c1->SaveAs("plots/triphoton_eta"+phoNum+"_sherpaVsMcfm.pdf");
  // } // end Pt
  //
  //



} // end namespace

#endif
