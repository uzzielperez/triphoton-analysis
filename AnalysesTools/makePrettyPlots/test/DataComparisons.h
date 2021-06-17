#ifndef DataComparisons_h
#define DataComparisons_h
#include "Selections.h"
#include "Comparisons.h"

namespace TriPhotons
{

  TString simLegLabel = "GEN";
  TString dataLegLabel = "PAT";

  void setDataCompareStyle(TH1D *hGen, TH1D *hData, TString xTitle = "x", TString yTitle = "y", double min=0.001, double max=-1){
    //h_gen_mAAA->Draw("E1, SAME");
    if (max == -1) max = 1.5*std::max(hData->GetMaximum(), hGen->GetMaximum());

    TH1D *hGenErr = (TH1D*) hGen->Clone();
    hGenErr->SetDirectory(0);
    hGenErr->SetMarkerSize(0);
    hGenErr->SetFillColor(14);
    hGenErr->SetFillStyle(3344);

    hGen->SetLineColor(kBlack);
    //hGen->SetFillColor(7);
    hGen->SetFillColor(kOrange+7);
    hGen->SetFillStyle(3144);
    hGen->Draw("hist, SAME");
    hGenErr->Draw("SAME, E2");

    hData->SetLineColor(kBlack);
    hData->SetMarkerStyle(20);
    hData->Draw("E1, SAME");
    hData->SetMinimum(min);
    hGen->SetMaximum(max);
    //
    // hGen->GetXaxis()->SetTitle("m_{#gamma#gamma#gamma} (GeV)");
    // hGen->GetYaxis()->SetTitleOffset(0.8);
    // hGen->GetYaxis()->SetTitle("d#sigma/dm_{#gamma#gamma#gamma}");

    hGen->GetXaxis()->SetTitle(xTitle);
    hGen->GetYaxis()->SetTitleOffset(0.8);
    hGen->GetYaxis()->SetTitle(yTitle);

  }

  void compareDataMggg(TFile *fGen, TFile *fData, bool isMinPt25 = true, bool isMinPt35_35_15 = false, bool isGenVSPat = true, TString simLegLabel = "GGGJets", TString dataLegLabel = "GGJets", bool showRatio=false, TString experiment="CMS"){
    /** compareData differential cross section measurements as a function of Mgg**/
    /** We treat PAT Photons - gensim photons that went through detector simulation as DATA **/

    TString hDataMinv;
    TString hGenMinv;

    if (isMinPt25)       {hDataMinv = "h_PAT_pT25_minv"; hGenMinv = "h_pT25_minv";}
    if (isMinPt35_35_15) {hDataMinv = "h_PAT_pT35_35_15_minv"; hGenMinv = "h_pT35_35_15_minv";}
    if (!isGenVSPat) {hGenMinv = hDataMinv;}

    TH1D *h_data_mAAA = (TH1D*) fData->Get(hDataMinv); // Hist cross section as y-axis
    TH1D *h_gen_mAAA = (TH1D*) fGen->Get(hGenMinv);

    TriPhotons::convertToDiffXsec(h_data_mAAA, 71900); // FIXME: add correct number of sim events
    TriPhotons::convertToDiffXsec(h_gen_mAAA, 17800);

    //------- MCFM vs Sherpa
    TCanvas *c = new TCanvas("c","c",700,600);

    TString xTitle = "m_{#gamma#gamma#gamma} (GeV)";
    TString yTitle = "d#sigma/dm_{#gamma#gamma#gamma}";
    //h_gen_mAAA->Draw("E1, SAME");
    setDataCompareStyle(h_gen_mAAA, h_data_mAAA, xTitle, yTitle,  0.1, 0.6);
    // TH1D *hGenErr = (TH1D*) h_gen_mAAA->Clone();
    // hGenErr->SetDirectory(0);
    // hGenErr->SetMarkerSize(0);
    // hGenErr->SetFillColor(14);
    // hGenErr->SetFillStyle(3344);
    //
    //
    // h_gen_mAAA->SetLineColor(kBlack);
    // //h_gen_mAAA->SetFillColor(7);
    // h_gen_mAAA->SetFillColor(kOrange+7);
    // h_gen_mAAA->SetFillStyle(3144);
    // h_gen_mAAA->Draw("hist, SAME");
    // hGenErr->Draw("SAME, E2");
    //
    // h_data_mAAA->SetLineColor(kBlack);
    // h_data_mAAA->SetMarkerStyle(20);
    // h_data_mAAA->Draw("E1, SAME");
    // h_data_mAAA->SetMinimum(0.1);
    // h_gen_mAAA->SetMaximum(1.5*std::max(h_data_mAAA->GetMaximum(), h_gen_mAAA->GetMaximum()));
    gPad->SetLogy();

    h_gen_mAAA->GetXaxis()->SetTitle("m_{#gamma#gamma#gamma} (GeV)");
    h_gen_mAAA->GetYaxis()->SetTitleOffset(0.8);
    h_gen_mAAA->GetYaxis()->SetTitle("d#sigma/dm_{#gamma#gamma#gamma}");

    TLatex *t_label = new TLatex();
    t_label->SetTextSize(0.03);
    t_label->SetTextAlign(12);
    t_label->SetTextAlign(12);
    t_label->DrawLatexNDC(0.6,0.82, experiment+ " Preliminary");
    t_label->DrawLatexNDC(0.6,0.78, "#sqrt{s}= 13 TeV, 80.94 fb^{-1}");
    t_label->SetTextFont(42);

    auto leg = new TLegend(0.6,0.65,0.8,0.75);
    leg->SetBorderSize(0);
    leg->AddEntry(h_gen_mAAA, simLegLabel, "f"); //FIXME: fixme label for PAT or DATA whenever it's available
    leg->AddEntry(h_data_mAAA, dataLegLabel, "lep");
    leg->Draw();

    TString outFile = "triphoton_Minv";
    if (isGenVSPat) outFile += "_GenPat_comp";
    if (isMinPt25) outFile += "_25";
    if (isMinPt35_35_15) outFile += "_35";
    c->SaveAs("plots/"+outFile+".pdf");

  }


  void compareDataPt(TFile *fGen, TFile *fData, TString phoNumStr, bool isMinPt25 = true, bool isMinPt35_35_15 = false, bool isGenVSPat = true, TString simLegLabel = "GGGJets", TString dataLegLabel = "GGJets", bool showRatio=false, TString experiment="CMS"){
    /** compareData differential cross section measurements as a function of Mgg**/
    /** We treat PAT Photons - gensim photons that went through detector simulation as DATA **/

    TString hDataPt;
    TString hGenPt;

    if (isMinPt25)       {hDataPt = "h_PAT_pT25_pT"+phoNumStr; hGenPt = "h_pT25_pT"+phoNumStr;}
    if (isMinPt35_35_15) {hDataPt = "h_PAT_pT35_35_15_pT"+phoNumStr; hGenPt = "h_pT35_35_15_pT"+phoNumStr;}
    if (!isGenVSPat) hGenPt = hDataPt;
    std::cout << hGenPt << " : " << hDataPt << std::endl;

    TH1D *hData = (TH1D*) fData->Get(hDataPt); // Hist cross section as y-axis
    TH1D *hGen = (TH1D*) fGen->Get(hGenPt);

    TriPhotons::convertToDiffXsec(hData, 71900);
    TriPhotons::convertToDiffXsec(hGen, 17800);

    //------- MCFM vs Sherpa
    TCanvas *c = new TCanvas("c","c",600,600);
    TString xTitle = "p_{T} #gamma"+phoNumStr+ " (GeV)";
    TString yTitle = "d#sigma/dp_{T} #gamma"+phoNumStr+ " (GeV)";
    // setDataCompareStyle(hGen, hData, 0.0001, 50, xTitle, yTitle);
    setDataCompareStyle(hGen, hData, xTitle, yTitle);
    // hGen->Draw("E1, SAME");
    // hData->SetLineColor(6);
    // hData->Draw("E1, SAME");
    // hData->SetMinimum(0.1);

    // TH1D *hGenErr = (TH1D*) hGen->Clone();
    // hGenErr->SetDirectory(0);
    // hGenErr->SetMarkerSize(0);
    // hGenErr->SetFillColor(14);
    // hGenErr->SetFillStyle(3344);
    //
    //
    // hGen->SetLineColor(kBlack);
    // //hGen->SetFillColor(7);
    // hGen->SetFillColor(kOrange+7);
    // hGen->SetFillStyle(3144);
    // hGen->Draw("hist, SAME");
    // hGenErr->Draw("SAME, E2");
    //
    // hData->SetLineColor(kBlack);
    // hData->SetMarkerStyle(20);
    // hData->Draw("E1, SAME");
    // hData->SetMinimum(0.1);
    // hGen->SetMaximum(1.5*std::max(hData->GetMaximum(), hGen->GetMaximum()));

    gPad->SetLogy();

    TLatex *t_label = new TLatex();
    t_label->SetTextSize(0.03);
    t_label->SetTextAlign(12);
    t_label->SetTextAlign(12);
    t_label->DrawLatexNDC(0.6,0.72, experiment);
    t_label->DrawLatexNDC(0.6,0.68, "#sqrt{s}= 13 TeV, 80.94 fb^{-1}");
    t_label->SetTextFont(42);

    auto leg = new TLegend(0.6,0.55,0.8,0.65);
    leg->SetBorderSize(0);
    leg->AddEntry(hGen, simLegLabel, "f"); //FIXME: fixme label for PAT or DATA whenever it's available
    leg->AddEntry(hData, dataLegLabel, "lep");
    leg->Draw();

    TString outFile = "triphoton_Pt"+phoNumStr;
    if (isGenVSPat) outFile += "_GenPat_comp";
    if (isMinPt25) outFile += "_25";
    if (isMinPt35_35_15) outFile += "_35";
    c->SaveAs("plots/"+outFile+".pdf");

  }

  void compareDataDiphotonMinv(TFile *fGen, TFile *fData, TString phoNum1, TString phoNum2, bool isMinPt25 = true, bool isMinPt35_35_15 = false, bool isGenVSPat = true, TString simLegLabel = "GGGJets", TString dataLegLabel = "GGJets", bool showRatio=false, TString experiment="CMS"){
    /** compareData differential cross section measurements as a function of Mgg**/
    /** We treat PAT Photons - gensim photons that went through detector simulation as DATA **/

    TString hDataMgg;
    TString hGenMgg;

    if (isMinPt25)       {hDataMgg = "h_PAT_pT25_mA"+phoNum1+"A"+phoNum2; hGenMgg = "h_pT25_mA"+phoNum1+"A"+phoNum2;}
    if (isMinPt35_35_15) {hDataMgg = "h_PAT_pT35_35_15_mA"+phoNum1+"A"+phoNum2; hGenMgg = "h_pT35_35_15_mA"+phoNum1+"A"+phoNum2;}
    if (!isGenVSPat) hGenMgg = hDataMgg;

    TH1D *h_data_mAA = (TH1D*) fData->Get(hDataMgg); // Hist cross section as y-axis
    TH1D *h_gen_mAA = (TH1D*) fGen->Get(hGenMgg);

    TriPhotons::convertToDiffXsec(h_data_mAA, 71900);
    TriPhotons::convertToDiffXsec(h_gen_mAA, 17800);

    //------- MCFM vs Sherpa
    TCanvas *c = new TCanvas("c","c",600,600);

    TString xTitle = "m#gamma"+phoNum1+"#gamma"+phoNum2+" (GeV)";
    TString yTitle = "d#sigma/dm#gamma"+phoNum1+"#gamma"+phoNum2;
    setDataCompareStyle(h_gen_mAA, h_data_mAA, xTitle, yTitle);
    // h_gen_mAA->Draw("E1, SAME");
    // h_data_mAA->SetLineColor(6);
    // h_data_mAA->Draw("E1, SAME");
    // h_data_mAA->SetMinimum(0.1);
    gPad->SetLogy();

    TLatex *t_label = new TLatex();
    t_label->SetTextSize(0.03);
    t_label->SetTextAlign(12);
    t_label->SetTextAlign(12);
    t_label->DrawLatexNDC(0.4,0.52, experiment);
    t_label->DrawLatexNDC(0.4,0.48, "#sqrt{s}= 13 TeV, 80.94 fb^{-1}");
    t_label->SetTextFont(42);

    auto leg = new TLegend(0.4,0.35,0.6,0.45);
    leg->SetBorderSize(0);
    leg->AddEntry(h_gen_mAA, simLegLabel, "f"); //FIXME: fixme label for PAT or DATA whenever it's available
    leg->AddEntry(h_data_mAA, dataLegLabel, "lep");
    leg->Draw();

    TString outFile = "triphoton_DiphotonMinv"+phoNum1+phoNum2;
    if (isGenVSPat) outFile += "_GenPat_comp";
    if (isMinPt25) outFile += "_25";
    if (isMinPt35_35_15) outFile += "_35";
    c->SaveAs("plots/"+outFile+".pdf");

  }

  void compareDataDPhi(TFile *fGen, TFile *fData, TString phoNum1, TString phoNum2, bool isMinPt25 = false, bool isMinPt35_35_15 = false, bool isGenVSPat = true, TString simLegLabel = "GGGJets", TString dataLegLabel = "GGJets", bool showRatio=false, TString experiment="CMS"){

    TString hDataDPhi;
    TString hGenDPhi;

    if (isMinPt25)       {hDataDPhi = "h_PAT_pT25_dPhi"+phoNum1+phoNum2; hGenDPhi = "h_pT25_dPhi"+phoNum1+phoNum2;}
    if (isMinPt35_35_15) {hDataDPhi = "h_PAT_pT35_35_15_dPhi"+phoNum1+phoNum2; hGenDPhi = "h_pT35_35_15_dPhi"+phoNum1+phoNum2;}
    if (!isGenVSPat) hGenDPhi = hDataDPhi;

    TH1D *h_data_DPhi = (TH1D*) fData->Get(hDataDPhi); // Hist cross section as y-axis
    TH1D *h_gen_DPhi = (TH1D*) fGen->Get(hGenDPhi);

    TriPhotons::convertToDiffXsec(h_data_DPhi, 71900);
    TriPhotons::convertToDiffXsec(h_gen_DPhi, 17800);

    //------- MCFM vs Sherpa
    TCanvas *c = new TCanvas("c","c",600,600);

    TString xTitle = "#Delta#Phi"+phoNum1+phoNum2;
    TString yTitle = "d#sigma/d#Delta#Phi"+phoNum1+phoNum2;

    setDataCompareStyle(h_gen_DPhi, h_data_DPhi, xTitle, yTitle);
    // h_gen_DPhi->Draw("E1, SAME");
    // h_data_DPhi->SetLineColor(6);
    // h_data_DPhi->Draw("E1, SAME");
    // h_data_DPhi->SetMinimum(0.1);
    gPad->SetLogy();

    TLatex *t_label = new TLatex();
    t_label->SetTextSize(0.03);
    t_label->SetTextAlign(12);
    t_label->SetTextAlign(12);
    t_label->DrawLatexNDC(0.2,0.72, experiment);
    t_label->DrawLatexNDC(0.2,0.68, "#sqrt{s}= 13 TeV, 80.94 fb^{-1}");
    t_label->SetTextFont(42);

    auto leg = new TLegend(0.2,0.55,0.6,0.65);
    leg->SetBorderSize(0);
    leg->AddEntry(h_gen_DPhi, simLegLabel, "f"); //FIXME: fixme label for PAT or DATA whenever it's available
    leg->AddEntry(h_data_DPhi, dataLegLabel, "lep");
    leg->Draw();

    TString outFile = "triphoton_DPhi"+phoNum1+phoNum2;
    if (isGenVSPat) outFile += "_GenPat_comp";
    if (isMinPt25) outFile += "_25";
    if (isMinPt35_35_15) outFile += "_35";
    c->SaveAs("plots/"+outFile+".pdf");

  }

  void compareDataDEta(TFile *fGen, TFile *fData, TString phoNum1, TString phoNum2, bool isMinPt25 = false, bool isMinPt35_35_15 = false, bool isGenVSPat = true, TString simLegLabel = "GGGJets", TString dataLegLabel = "GGJets", bool showRatio=false, TString experiment="CMS"){

    TString hDataDEta;
    TString hGenDEta;

    if (isMinPt25)       {hDataDEta = "h_PAT_pT25_dEta"+phoNum1+phoNum2; hGenDEta = "h_pT25_dEta"+phoNum1+phoNum2;}
    if (isMinPt35_35_15) {hDataDEta = "h_PAT_pT35_35_15_dEta"+phoNum1+phoNum2; hGenDEta = "h_pT35_35_15_dEta"+phoNum1+phoNum2;}
    if (!isGenVSPat) hGenDEta = hDataDEta;

    TH1D *h_data_DEta = (TH1D*) fData->Get(hDataDEta); // Hist cross section as y-axis
    TH1D *h_gen_DEta = (TH1D*) fGen->Get(hGenDEta);

    TriPhotons::convertToDiffXsec(h_data_DEta, 71900);
    TriPhotons::convertToDiffXsec(h_gen_DEta, 17800);

    //------- MCFM vs Sherpa
    TCanvas *c = new TCanvas("c","c",600,600);

    TString xTitle = "|#Delta#eta"+phoNum1+phoNum2+"|";
    TString yTitle = "d#sigma/d|#Delta#eta"+phoNum1+phoNum2+"|";

    setDataCompareStyle(h_gen_DEta, h_data_DEta, xTitle, yTitle);
    // h_gen_DEta->Draw("E1, SAME");
    // h_data_DEta->SetLineColor(6);
    // h_data_DEta->Draw("E1, SAME");
    // h_data_DEta->SetMinimum(0.1);
    gPad->SetLogy();

    TLatex *t_label = new TLatex();
    t_label->SetTextSize(0.03);
    t_label->SetTextAlign(12);
    t_label->SetTextAlign(12);
    t_label->DrawLatexNDC(0.2,0.72, experiment);
    t_label->DrawLatexNDC(0.2,0.68, "#sqrt{s}= 13 TeV, 80.94 fb^{-1}");
    t_label->SetTextFont(42);

    auto leg = new TLegend(0.2,0.55,0.6,0.65);
    leg->SetBorderSize(0);
    leg->AddEntry(h_gen_DEta, simLegLabel, "f"); //FIXME: fixme label for PAT or DATA whenever it's available
    leg->AddEntry(h_data_DEta, dataLegLabel, "lep");
    leg->Draw();

    TString outFile = "triphoton_DEta"+phoNum1+phoNum2;
    if (isGenVSPat) outFile += "_GenPat_comp";
    if (isMinPt25) outFile += "_25";
    if (isMinPt35_35_15) outFile += "_35";
    c->SaveAs("plots/"+outFile+".pdf");

  }
}
#endif
