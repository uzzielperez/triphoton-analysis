#ifndef DataComparisons_h
#define DataComparisons_h
#include "Selections.h"
#include "Comparisons.h"

namespace TriPhotons
{

  void compareDataMggg(TFile *fData, TFile *fGen, bool isMinPt25 = true, bool isMinPt35_35_15 = false, bool showRatio=false, TString experiment="CMS"){
    /** compareData differential cross section measurements as a function of Mgg**/
    /** We treat PAT Photons - gensim photons that went through detector simulation as DATA **/

    TString hDataMinv;
    TString hGenMinv;

    if (isMinPt25)       {hDataMinv = "h_PAT_pT25_minv"; hGenMinv = "h_pT25_minv";}
    if (isMinPt35_35_15) {hDataMinv = "h_PAT_pT35_35_15_minv"; hGenMinv = "h_pT35_35_15_minv";}

    TH1D *h_data_mAAA = (TH1D*) fData->Get(hDataMinv); // Hist cross section as y-axis
    TH1D *h_gen_mAAA = (TH1D*) fGen->Get(hGenMinv);

    TriPhotons::convertToDiffXsec(h_data_mAAA);
    TriPhotons::convertToDiffXsec(h_gen_mAAA);

    //------- MCFM vs Sherpa
    TCanvas *c = new TCanvas("c","c",600,600);

    h_gen_mAAA->Draw("E1, SAME");
    h_data_mAAA->SetLineColor(6);
    h_data_mAAA->Draw("E1, SAME");
    h_data_mAAA->SetMinimum(0.1);
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
    leg->AddEntry(h_gen_mAAA, "GEN", "l"); //FIXME: fixme label for PAT or DATA whenever it's available
    leg->AddEntry(h_data_mAAA, "PAT", "l");
    leg->Draw();

    TString outFile = "triphoton_Minv_GenPat_comp";
    if (isMinPt25) outFile += "_25";
    if (isMinPt35_35_15) outFile += "_35";
    c->SaveAs("plots/"+outFile+".pdf");

  }


  void compareDataPt(TFile *fData, TFile *fGen, TString phoNumStr, bool isMinPt25 = true, bool isMinPt35_35_15 = false, bool showRatio=false, TString experiment="CMS"){
    /** compareData differential cross section measurements as a function of Mgg**/
    /** We treat PAT Photons - gensim photons that went through detector simulation as DATA **/

    TString hDataPt;
    TString hGenPt;

    if (isMinPt25)       {hDataPt = "h_PAT_pT25_pT"+phoNumStr; hGenPt = "h_pT25_pT"+phoNumStr;}
    if (isMinPt35_35_15) {hDataPt = "h_PAT_pT35_35_15_pT"+phoNumStr; hGenPt = "h_pT35_35_15_pT"+phoNumStr;}

    TH1D *h_data_pt = (TH1D*) fData->Get(hDataPt); // Hist cross section as y-axis
    TH1D *h_gen_pt = (TH1D*) fGen->Get(hGenPt);

    TriPhotons::convertToDiffXsec(h_data_pt);
    TriPhotons::convertToDiffXsec(h_gen_pt);

    //------- MCFM vs Sherpa
    TCanvas *c = new TCanvas("c","c",600,600);

    h_gen_pt->Draw("E1, SAME");
    h_data_pt->SetLineColor(6);
    h_data_pt->Draw("E1, SAME");
    h_data_pt->SetMinimum(0.1);
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
    leg->AddEntry(h_gen_pt, "GEN", "l"); //FIXME: fixme label for PAT or DATA whenever it's available
    leg->AddEntry(h_data_pt, "PAT", "l");
    leg->Draw();

    TString outFile = "triphoton_Pt"+phoNumStr+"_GenPat_comp";
    if (isMinPt25) outFile += "_25";
    if (isMinPt35_35_15) outFile += "_35";
    c->SaveAs("plots/"+outFile+".pdf");

  }

  void compareDataDiphotonMinv(TFile *fData, TFile *fGen, TString phoNum1, TString phoNum2, bool isMinPt25 = true, bool isMinPt35_35_15 = false, bool showRatio=false, TString experiment="CMS"){
    /** compareData differential cross section measurements as a function of Mgg**/
    /** We treat PAT Photons - gensim photons that went through detector simulation as DATA **/

    TString hDataMgg;
    TString hGenMgg;

    if (isMinPt25)       {hDataMgg = "h_PAT_pT25_mA"+phoNum1+"A"+phoNum2; hGenMgg = "h_pT25_mA"+phoNum1+"A"+phoNum2;}
    if (isMinPt35_35_15) {hDataMgg = "h_PAT_pT35_35_15_mA"+phoNum1+"A"+phoNum2; hGenMgg = "h_pT35_35_15_mA"+phoNum1+"A"+phoNum2;}

    TH1D *h_data_mAA = (TH1D*) fData->Get(hDataMgg); // Hist cross section as y-axis
    TH1D *h_gen_mAA = (TH1D*) fGen->Get(hGenMgg);

    TriPhotons::convertToDiffXsec(h_data_mAA);
    TriPhotons::convertToDiffXsec(h_gen_mAA);

    //------- MCFM vs Sherpa
    TCanvas *c = new TCanvas("c","c",600,600);

    h_gen_mAA->Draw("E1, SAME");
    h_data_mAA->SetLineColor(6);
    h_data_mAA->Draw("E1, SAME");
    h_data_mAA->SetMinimum(0.1);
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
    leg->AddEntry(h_gen_mAA, "GEN", "l"); //FIXME: fixme label for PAT or DATA whenever it's available
    leg->AddEntry(h_data_mAA, "PAT", "l");
    leg->Draw();

    TString outFile = "triphoton_DiphotonMinv"+phoNum1+phoNum2+"_GenPat_comp";
    if (isMinPt25) outFile += "_25";
    if (isMinPt35_35_15) outFile += "_35";
    c->SaveAs("plots/"+outFile+".pdf");

  }

  void compareDataDPhi(TFile *fData, TFile *fGen, TString phoNum1, TString phoNum2, bool isMinPt25 = false, bool isMinPt35_35_15 = false, bool showRatio=false, TString experiment="CMS"){

    TString hDataDPhi;
    TString hGenDPhi;

    if (isMinPt25)       {hDataDPhi = "h_PAT_pT25_dPhi"+phoNum1+phoNum2; hGenDPhi = "h_pT25_dPhi"+phoNum1+phoNum2;}
    if (isMinPt35_35_15) {hDataDPhi = "h_PAT_pT35_35_15_dPhi"+phoNum1+phoNum2; hGenDPhi = "h_pT35_35_15_dPhi"+phoNum1+phoNum2;}

    TH1D *h_data_DPhi = (TH1D*) fData->Get(hDataDPhi); // Hist cross section as y-axis
    TH1D *h_gen_DPhi = (TH1D*) fGen->Get(hGenDPhi);

    TriPhotons::convertToDiffXsec(h_data_DPhi);
    TriPhotons::convertToDiffXsec(h_gen_DPhi);

    //------- MCFM vs Sherpa
    TCanvas *c = new TCanvas("c","c",600,600);

    h_gen_DPhi->Draw("E1, SAME");
    h_data_DPhi->SetLineColor(6);
    h_data_DPhi->Draw("E1, SAME");
    h_data_DPhi->SetMinimum(0.1);
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
    leg->AddEntry(h_gen_DPhi, "GEN", "l"); //FIXME: fixme label for PAT or DATA whenever it's available
    leg->AddEntry(h_data_DPhi, "PAT", "l");
    leg->Draw();

    TString outFile = "triphoton_DPhi"+phoNum1+phoNum2+"_GenPat_comp";
    if (isMinPt25) outFile += "_25";
    if (isMinPt35_35_15) outFile += "_35";
    c->SaveAs("plots/"+outFile+".pdf");

  }

  void compareDataDEta(TFile *fData, TFile *fGen, TString phoNum1, TString phoNum2, bool isMinPt25 = false, bool isMinPt35_35_15 = false, bool showRatio=false, TString experiment="CMS"){

    TString hDataDEta;
    TString hGenDEta;

    if (isMinPt25)       {hDataDEta = "h_PAT_pT25_dEta"+phoNum1+phoNum2; hGenDEta = "h_pT25_dEta"+phoNum1+phoNum2;}
    if (isMinPt35_35_15) {hDataDEta = "h_PAT_pT35_35_15_dEta"+phoNum1+phoNum2; hGenDEta = "h_pT35_35_15_dEta"+phoNum1+phoNum2;}

    TH1D *h_data_DEta = (TH1D*) fData->Get(hDataDEta); // Hist cross section as y-axis
    TH1D *h_gen_DEta = (TH1D*) fGen->Get(hGenDEta);

    TriPhotons::convertToDiffXsec(h_data_DEta);
    TriPhotons::convertToDiffXsec(h_gen_DEta);

    //------- MCFM vs Sherpa
    TCanvas *c = new TCanvas("c","c",600,600);

    h_gen_DEta->Draw("E1, SAME");
    h_data_DEta->SetLineColor(6);
    h_data_DEta->Draw("E1, SAME");
    h_data_DEta->SetMinimum(0.1);
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
    leg->AddEntry(h_gen_DEta, "GEN", "l"); //FIXME: fixme label for PAT or DATA whenever it's available
    leg->AddEntry(h_data_DEta, "PAT", "l");
    leg->Draw();

    TString outFile = "triphoton_DEta"+phoNum1+phoNum2+"_GenPat_comp";
    if (isMinPt25) outFile += "_25";
    if (isMinPt35_35_15) outFile += "_35";
    c->SaveAs("plots/"+outFile+".pdf");

  }
}
#endif
