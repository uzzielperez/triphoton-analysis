#ifndef Ratio_h
#define Ratio_h
#include "Selections.h"
#include "Comparisons.h"

namespace TriPhotons
{

  void createRatio(TH1D* hNumerator, TH1D* hDenominator, double min = 0, double max = 0.3, TString xTitle = "m#gamma#gamma#gamma (GeV)", TString yTitle = "hPAT/hGEN"){
    TH1F *hRatio = (TH1F*) hNumerator->Clone("hNumerator");
    hRatio->SetLineColor(kBlack);
    hRatio->SetMarkerColor(kBlack);
    // hRatio->SetMinimum(0.4);
    // hRatio->SetMaximum(1.1);
    hRatio->SetStats(0);
    hRatio->Divide(hDenominator);
    hRatio->Draw("ep, SAME");
    hRatio->SetTitle("");
    hRatio->GetXaxis()->SetTitle(xTitle);
    // hRatio->GetYaxis()->SetTitleSize(25);
    hRatio->GetYaxis()->SetTitleOffset(0.4);
    hRatio->GetYaxis()->SetTitle(yTitle);
    hRatio->GetYaxis()->SetTitleSize(0.06); // default 0.04
    hRatio->GetYaxis()->SetTitle(yTitle);

    hRatio->GetXaxis()->SetTitleSize(20);
    hRatio->GetXaxis()->SetTitleFont(43);
    hRatio->GetXaxis()->SetTitleOffset(3);
    hRatio->GetXaxis()->SetLabelFont(43);
    hRatio->GetXaxis()->SetLabelSize(16);
    hRatio->SetMinimum(min);
    hRatio->SetMaximum(max);
  }

  void getRatioMggg(TFile *fGen, TFile *fData, bool isMinPt25 = true, bool isMinPt35_35_15 = false, bool isGenVSPat = true, TString simLegLabel = "GGGJets", TString dataLegLabel = "GGJets", bool showRatio=false, TString experiment="CMS"){
    /** getRatio differential cross section measurements as a function of Mgg**/
    /** We treat PAT Photons - gensim photons that went through detector simulation as DATA **/

    TString hDataMinv;
    TString hGenMinv;

    if (isMinPt25)       {hDataMinv = "h_PAT_pT25_minv"; hGenMinv = "h_pT25_minv";}
    if (isMinPt35_35_15) {hDataMinv = "h_PAT_pT35_35_15_minv"; hGenMinv = "h_pT35_35_15_minv";}
    if (!isGenVSPat) {hGenMinv = hDataMinv;}

    TH1D *h_data_mAAA = (TH1D*) fData->Get(hDataMinv); // Hist cross section as y-axis
    TH1D *h_gen_mAAA = (TH1D*) fGen->Get(hGenMinv);

    TriPhotons::convertToDiffXsec(h_data_mAAA, 17800); // FIXME: add correct number of sim events
    TriPhotons::convertToDiffXsec(h_gen_mAAA, 17800);

    //------- MCFM vs Sherpa
    TCanvas *c = new TCanvas("c","c",700,900);

    TPad *pad1 = new TPad("pad1", "", 0, 0.1, 1, 1.0);
    pad1->SetBottomMargin(0.3); // joins upper and lower plot
    pad1->Draw();
    pad1->cd();
    pad1->SetLogy();

    //h_gen_mAAA->Draw("E1, SAME");
    TH1D *hGenErr = (TH1D*) h_gen_mAAA->Clone();
    hGenErr->SetDirectory(0);
    hGenErr->SetMarkerSize(0);
    hGenErr->SetFillColor(14);
    hGenErr->SetFillStyle(3344);

    h_gen_mAAA->SetLineColor(kBlack);
    //h_gen_mAAA->SetFillColor(7);
    h_gen_mAAA->SetFillColor(kCyan-4);
    h_gen_mAAA->SetFillStyle(3144);
    h_gen_mAAA->Draw("hist, SAME");
    hGenErr->Draw("SAME, E2");

    TH1D *hDataErr = (TH1D*) h_data_mAAA->Clone();
    hDataErr->SetDirectory(0);
    hDataErr->SetMarkerSize(0);
    hDataErr->SetFillColor(14);
    hDataErr->SetFillStyle(3344);

    h_data_mAAA->SetLineColor(kBlack);
    // h_data_mAAA->SetMarkerStyle(20);
    h_data_mAAA->SetFillColor(kOrange+7);
    h_data_mAAA->SetFillStyle(3144);
    h_data_mAAA->Draw("hist, SAME");
    h_data_mAAA->SetMinimum(0.1);
    h_gen_mAAA->SetMaximum(2*std::max(h_data_mAAA->GetMaximum(), h_gen_mAAA->GetMaximum()));
    // gPad->SetLogy();
    hDataErr->Draw("SAME, E2");

    h_gen_mAAA->GetXaxis()->SetTitle("m_{#gamma#gamma#gamma} (GeV)");
    h_gen_mAAA->GetYaxis()->SetTitleOffset(0.8);
    h_gen_mAAA->GetYaxis()->SetTitle("d#sigma/dm_{#gamma#gamma#gamma}");

    TLatex *t_label = new TLatex();
    t_label->SetTextSize(0.03);
    t_label->SetTextAlign(12);
    t_label->SetTextAlign(12);
    t_label->DrawLatexNDC(0.32,0.52, experiment+ " Preliminary");
    t_label->DrawLatexNDC(0.32,0.48, "#sqrt{s}= 13 TeV, 80.94 fb^{-1}");
    t_label->SetTextFont(42);

    auto leg = new TLegend(0.32,0.35,0.52,0.45);
    leg->SetBorderSize(0);
    leg->AddEntry(h_gen_mAAA, simLegLabel, "f"); //FIXME: fixme label for PAT or DATA whenever it's available
    // leg->AddEntry(h_data_mAAA, dataLegLabel, "lep");
    leg->AddEntry(h_data_mAAA, dataLegLabel, "f");
    leg->Draw();

    TPad *pad2 = new TPad("pad2", "", 0, 0.0, 1, 0.3);
    pad2->SetTopMargin(0.1);
    pad2->SetBottomMargin(0.15);
    pad2->Draw();
    pad2->cd();
    pad2->SetGrid(0,1);
    createRatio(h_data_mAAA, h_gen_mAAA, 0.1, 0.8);

    c->Update();
    TString outFile = "triphoton_Minv";
    if (isGenVSPat) outFile += "_GenPat_comp";
    if (isMinPt25) outFile += "_25";
    if (isMinPt35_35_15) outFile += "_35";
    c->SaveAs("plots/"+outFile+".pdf");

  }

  void getRatioPt(TFile *fGen, TFile *fData, TString phoNumStr, bool isMinPt25 = true, bool isMinPt35_35_15 = false, bool isGenVSPat = true, TString simLegLabel = "GGGJets", TString dataLegLabel = "GGJets", bool showRatio=false, TString experiment="CMS"){
    /** getRatio differential cross section measurements as a function of Mgg**/
    /** We treat PAT Photons - gensim photons that went through detector simulation as DATA **/

    TString hData;
    TString hGen;

    if (isMinPt25)       {hData = "h_PAT_pT25_pT"+phoNumStr; hGen = "h_pT25_pT"+phoNumStr;}
    if (isMinPt35_35_15) {hData = "h_PAT_pT35_35_15_pT"+phoNumStr; hGen = "h_pT35_35_15_pT"+phoNumStr;}
    if (!isGenVSPat) hGen = hData;


    TH1D *h_data = (TH1D*) fData->Get(hData); // Hist cross section as y-axis
    TH1D *h_gen = (TH1D*) fGen->Get(hGen);

    TriPhotons::convertToDiffXsec(h_data, 17800); // FIXME: add correct number of sim events
    TriPhotons::convertToDiffXsec(h_gen, 17800);

    //------- MCFM vs Sherpa
    TCanvas *c = new TCanvas("c","c",700,900);

    TPad *pad1 = new TPad("pad1", "", 0, 0.1, 1, 1.0);
    pad1->SetBottomMargin(0.3); // joins upper and lower plot
    pad1->Draw();
    pad1->cd();
    pad1->SetLogy();

    //h_gen_mAAA->Draw("E1, SAME");
    TH1D *hGenErr = (TH1D*) h_gen->Clone();
    hGenErr->SetDirectory(0);
    hGenErr->SetMarkerSize(0);
    hGenErr->SetFillColor(14);
    hGenErr->SetFillStyle(3344);

    h_gen->SetLineColor(kBlack);
    //h_gen_mAAA->SetFillColor(7);
    h_gen->SetFillColor(kCyan-4);
    h_gen->SetFillStyle(3144);
    h_gen->Draw("hist, SAME");
    hGenErr->Draw("SAME, E2");

    TH1D *hDataErr = (TH1D*) h_data->Clone();
    hDataErr->SetDirectory(0);
    hDataErr->SetMarkerSize(0);
    hDataErr->SetFillColor(14);
    hDataErr->SetFillStyle(3344);

    h_data->SetLineColor(kBlack);
    // h_data_mAAA->SetMarkerStyle(20);
    h_data->SetFillColor(kOrange+7);
    h_data->SetFillStyle(3144);
    h_data->Draw("hist, SAME");
    h_data->SetMinimum(0.1);
    //h_gen->SetMaximum(2*std::max(h_data->GetMaximum(), h_gen->GetMaximum()));
    h_gen->SetMaximum(5);
    h_gen->SetMinimum(0.01);
    // gPad->SetLogy();
    hDataErr->Draw("SAME, E2");

    //const TString graphName(Form("fakeRate%s_%s", region.c_str(), iso.c_str()));

    // TString xTitle(Form("p_{T} #gamma_%s (GeV)", phoNumStr));
    // TString yTitle(Form("d#sigma/dp_{T} #gamma_%s (GeV)", phoNumStr));

    TString xTitle = "p_{T} #gamma"+phoNumStr+ " (GeV)";
    TString yTitle = "d#sigma/dp_{T} #gamma"+phoNumStr;


    h_gen->GetXaxis()->SetTitle(xTitle);
    h_gen->GetYaxis()->SetTitleOffset(0.8);
    h_gen->GetYaxis()->SetTitle(yTitle);

    TLatex *t_label = new TLatex();
    t_label->SetTextSize(0.03);
    t_label->SetTextAlign(12);
    t_label->SetTextAlign(12);
    t_label->DrawLatexNDC(0.6,0.82, experiment+ " Preliminary");
    t_label->DrawLatexNDC(0.6,0.78, "#sqrt{s}= 13 TeV, 80.94 fb^{-1}");
    t_label->SetTextFont(42);

    auto leg = new TLegend(0.6,0.68,0.8,0.75);
    leg->SetBorderSize(0);
    leg->AddEntry(h_gen, simLegLabel, "f"); //FIXME: fixme label for PAT or DATA whenever it's available
    // leg->AddEntry(h_data, dataLegLabel, "lep");
    leg->AddEntry(h_data, dataLegLabel, "f");
    leg->Draw();

    TPad *pad2 = new TPad("pad2", "", 0, 0.0, 1, 0.3);
    pad2->SetTopMargin(0.1);
    pad2->SetBottomMargin(0.15);
    pad2->Draw();
    pad2->cd();
    pad2->SetGrid(0,1);
    createRatio(h_data, h_gen, 0.1, 0.7, xTitle);

    c->Update();
    TString outFile = "triphoton_Pt"+phoNumStr;
    if (isGenVSPat) outFile += "_GenPat_comp";
    if (isMinPt25) outFile += "_25";
    if (isMinPt35_35_15) outFile += "_35";
    c->SaveAs("plots/"+outFile+".pdf");

  }


  void getRatioDiphotonMinv(TFile *fGen, TFile *fData, TString phoNumStr1,  TString phoNumStr2, bool isMinPt25 = true, bool isMinPt35_35_15 = false, bool isGenVSPat = true, TString simLegLabel = "GGGJets", TString dataLegLabel = "GGJets", bool showRatio=false, TString experiment="CMS"){
    /** getRatio differential cross section measurements as a function of Mgg**/
    /** We treat PAT Photons - gensim photons that went through detector simulation as DATA **/

    TString hData;
    TString hGen;

    if (isMinPt25)       {hData = "h_PAT_pT25_mA"+phoNumStr1+"A"+phoNumStr2; hGen = "h_pT25_mA"+phoNumStr1+"A"+phoNumStr2;}
    if (isMinPt35_35_15) {hData = "h_PAT_pT35_35_15_mA"+phoNumStr1+"A"+phoNumStr2; hGen = "h_pT35_35_15_mA"+phoNumStr1+"A"+phoNumStr2;}
    if (!isGenVSPat) hGen = hData;


    TH1D *h_data = (TH1D*) fData->Get(hData); // Hist cross section as y-axis
    TH1D *h_gen = (TH1D*) fGen->Get(hGen);

    TriPhotons::convertToDiffXsec(h_data, 17800); // FIXME: add correct number of sim events
    TriPhotons::convertToDiffXsec(h_gen, 17800);

    //------- MCFM vs Sherpa
    TCanvas *c = new TCanvas("c","c",700,900);

    TPad *pad1 = new TPad("pad1", "", 0, 0.1, 1, 1.0);
    pad1->SetBottomMargin(0.3); // joins upper and lower plot
    pad1->Draw();
    pad1->cd();
    pad1->SetLogy();

    //h_gen_mAAA->Draw("E1, SAME");
    TH1D *hGenErr = (TH1D*) h_gen->Clone();
    hGenErr->SetDirectory(0);
    hGenErr->SetMarkerSize(0);
    hGenErr->SetFillColor(14);
    hGenErr->SetFillStyle(3344);

    h_gen->SetLineColor(kBlack);
    //h_gen_mAAA->SetFillColor(7);
    h_gen->SetFillColor(kCyan-4);
    h_gen->SetFillStyle(3144);
    h_gen->Draw("hist, SAME");
    hGenErr->Draw("SAME, E2");

    TH1D *hDataErr = (TH1D*) h_data->Clone();
    hDataErr->SetDirectory(0);
    hDataErr->SetMarkerSize(0);
    hDataErr->SetFillColor(14);
    hDataErr->SetFillStyle(3344);

    h_data->SetLineColor(kBlack);
    // h_data_mAAA->SetMarkerStyle(20);
    h_data->SetFillColor(kOrange+7);
    h_data->SetFillStyle(3144);
    h_data->Draw("hist, SAME");
    h_data->SetMinimum(0.1);
    //h_gen->SetMaximum(2*std::max(h_data->GetMaximum(), h_gen->GetMaximum()));
    h_gen->SetMaximum(5);
    h_gen->SetMinimum(0.001);
    // gPad->SetLogy();
    hDataErr->Draw("SAME, E2");

    //const TString graphName(Form("fakeRate%s_%s", region.c_str(), iso.c_str()));
    //TString xTitle(Form("m_#gamma_%s#gamma_%s (GeV)", phoNumStr1, phoNumStr2));
    //TString yTitle(Form("d#sigma/dm_#gamma_%s#gamma_%s (GeV)", phoNumStr1, phoNumStr2));

    TString xTitle = "m#gamma"+phoNumStr1+"#gamma"+phoNumStr2+" (GeV)";
    TString yTitle = "d#sigma/dm#gamma"+phoNumStr1+"#gamma"+phoNumStr2;

    h_gen->GetXaxis()->SetTitle(xTitle);
    h_gen->GetYaxis()->SetTitleOffset(0.8);
    h_gen->GetYaxis()->SetTitle(yTitle);

    TLatex *t_label = new TLatex();
    t_label->SetTextSize(0.03);
    t_label->SetTextAlign(12);
    t_label->SetTextAlign(12);
    t_label->DrawLatexNDC(0.6,0.82, experiment+ " Preliminary");
    t_label->DrawLatexNDC(0.6,0.78, "#sqrt{s}= 13 TeV, 80.94 fb^{-1}");
    t_label->SetTextFont(42);

    auto leg = new TLegend(0.6,0.68,0.8,0.75);
    leg->SetBorderSize(0);
    leg->AddEntry(h_gen, simLegLabel, "f"); //FIXME: fixme label for PAT or DATA whenever it's available
    // leg->AddEntry(h_data, dataLegLabel, "lep");
    leg->AddEntry(h_data, dataLegLabel, "f");
    leg->Draw();

    TPad *pad2 = new TPad("pad2", "", 0, 0.0, 1, 0.3);
    pad2->SetTopMargin(0.1);
    pad2->SetBottomMargin(0.15);
    pad2->Draw();
    pad2->cd();
    pad2->SetGrid(0,1);
    createRatio(h_data, h_gen, 0.1, 0.8, xTitle);

    c->Update();
    TString outFile = "triphoton_DiphotonMinv"+phoNumStr1+phoNumStr2;
    if (isGenVSPat) outFile += "_GenPat_comp";
    if (isMinPt25) outFile += "_25";
    if (isMinPt35_35_15) outFile += "_35";
    c->SaveAs("plots/"+outFile+".pdf");

  }
  void getRatioDPhi(TFile *fGen, TFile *fData, TString phoNum1,  TString phoNum2, bool isMinPt25 = true, bool isMinPt35_35_15 = false, bool isGenVSPat = true, TString simLegLabel = "GGGJets", TString dataLegLabel = "GGJets", bool showRatio=false, TString experiment="CMS"){
    /** getRatio differential cross section measurements as a function of Mgg**/
    /** We treat PAT Photons - gensim photons that went through detector simulation as DATA **/

    TString hData;
    TString hGen;

    if (isMinPt25)       {hData = "h_PAT_pT25_dPhi"+phoNum1+phoNum2; hGen = "h_pT25_dPhi"+phoNum1+phoNum2;}
    if (isMinPt35_35_15) {hData = "h_PAT_pT35_35_15_dPhi"+phoNum1+phoNum2; hGen = "h_pT35_35_15_dPhi"+phoNum1+phoNum2;}
    if (!isGenVSPat) hGen = hData;


    TH1D *h_data = (TH1D*) fData->Get(hData); // Hist cross section as y-axis
    TH1D *h_gen = (TH1D*) fGen->Get(hGen);

    TriPhotons::convertToDiffXsec(h_data, 17800); // FIXME: add correct number of sim events
    TriPhotons::convertToDiffXsec(h_gen, 17800);

    //------- MCFM vs Sherpa
    TCanvas *c = new TCanvas("c","c",700,900);

    TPad *pad1 = new TPad("pad1", "", 0, 0.1, 1, 1.0);
    pad1->SetBottomMargin(0.3); // joins upper and lower plot
    pad1->Draw();
    pad1->cd();
    pad1->SetLogy();

    //h_gen_mAAA->Draw("E1, SAME");
    TH1D *hGenErr = (TH1D*) h_gen->Clone();
    hGenErr->SetDirectory(0);
    hGenErr->SetMarkerSize(0);
    hGenErr->SetFillColor(14);
    hGenErr->SetFillStyle(3344);

    h_gen->SetLineColor(kBlack);
    //h_gen_mAAA->SetFillColor(7);
    h_gen->SetFillColor(kCyan-4);
    h_gen->SetFillStyle(3144);
    h_gen->Draw("hist, SAME");
    hGenErr->Draw("SAME, E2");

    TH1D *hDataErr = (TH1D*) h_data->Clone();
    hDataErr->SetDirectory(0);
    hDataErr->SetMarkerSize(0);
    hDataErr->SetFillColor(14);
    hDataErr->SetFillStyle(3344);

    h_data->SetLineColor(kBlack);
    // h_data_mAAA->SetMarkerStyle(20);
    h_data->SetFillColor(kOrange+7);
    h_data->SetFillStyle(3144);
    h_data->Draw("hist, SAME");
    h_data->SetMinimum(0.1);
    //h_gen->SetMaximum(2*std::max(h_data->GetMaximum(), h_gen->GetMaximum()));
    h_gen->SetMaximum(100);
    h_gen->SetMinimum(0.001);
    // gPad->SetLogy();
    hDataErr->Draw("SAME, E2");

    //const TString graphName(Form("fakeRate%s_%s", region.c_str(), iso.c_str()));
    //TString xTitle(Form("m_#gamma_%s#gamma_%s (GeV)", phoNumStr1, phoNumStr2));
    //TString yTitle(Form("d#sigma/dm_#gamma_%s#gamma_%s (GeV)", phoNumStr1, phoNumStr2));

    TString xTitle = "#Delta#Phi"+phoNum1+phoNum2;
    TString yTitle = "d#sigma/d#Delta#Phi"+phoNum1+phoNum2;

    h_gen->GetXaxis()->SetTitle(xTitle);
    h_gen->GetYaxis()->SetTitleOffset(0.8);
    h_gen->GetYaxis()->SetTitle(yTitle);

    TLatex *t_label = new TLatex();
    t_label->SetTextSize(0.03);
    t_label->SetTextAlign(12);
    t_label->SetTextAlign(12);
    t_label->DrawLatexNDC(0.3,0.52, experiment+ " Preliminary");
    t_label->DrawLatexNDC(0.3,0.48, "#sqrt{s}= 13 TeV, 80.94 fb^{-1}");
    t_label->SetTextFont(42);

    auto leg = new TLegend(0.3,0.38,0.5,0.45);
    leg->SetBorderSize(0);
    leg->AddEntry(h_gen, simLegLabel, "f"); //FIXME: fixme label for PAT or DATA whenever it's available
    // leg->AddEntry(h_data, dataLegLabel, "lep");
    leg->AddEntry(h_data, dataLegLabel, "f");
    leg->Draw();

    TPad *pad2 = new TPad("pad2", "", 0, 0.0, 1, 0.3);
    pad2->SetTopMargin(0.1);
    pad2->SetBottomMargin(0.15);
    pad2->Draw();
    pad2->cd();
    pad2->SetGrid(0,1);
    createRatio(h_data, h_gen, 0.1, 0.4, xTitle);

    c->Update();
    TString outFile = "triphoton_DPhi"+phoNum1+phoNum2;
    if (isGenVSPat) outFile += "_GenPat_comp";
    if (isMinPt25) outFile += "_25";
    if (isMinPt35_35_15) outFile += "_35";
    c->SaveAs("plots/"+outFile+".pdf");

    // hstring
    // outputfile string
    // legendlabels
    //

  }

  void getRatioDEta(TFile *fGen, TFile *fData, TString phoNum1,  TString phoNum2, bool isMinPt25 = true, bool isMinPt35_35_15 = false, bool isGenVSPat = true, TString simLegLabel = "GGGJets", TString dataLegLabel = "GGJets", bool showRatio=false, TString experiment="CMS"){
    /** getRatio differential cross section measurements as a function of Mgg**/
    /** We treat PAT Photons - gensim photons that went through detector simulation as DATA **/

    TString hData;
    TString hGen;

    if (isMinPt25)       {hData = "h_PAT_pT25_dEta"+phoNum1+phoNum2; hGen = "h_pT25_dEta"+phoNum1+phoNum2;}
    if (isMinPt35_35_15) {hData = "h_PAT_pT35_35_15_dEta"+phoNum1+phoNum2; hGen = "h_pT35_35_15_dEta"+phoNum1+phoNum2;}
    if (!isGenVSPat) hGen = hData;


    TH1D *h_data = (TH1D*) fData->Get(hData); // Hist cross section as y-axis
    TH1D *h_gen = (TH1D*) fGen->Get(hGen);

    TriPhotons::convertToDiffXsec(h_data, 17800); // FIXME: add correct number of sim events
    TriPhotons::convertToDiffXsec(h_gen, 17800);

    //------- MCFM vs Sherpa
    TCanvas *c = new TCanvas("c","c",700,900);

    TPad *pad1 = new TPad("pad1", "", 0, 0.1, 1, 1.0);
    pad1->SetBottomMargin(0.3); // joins upper and lower plot
    pad1->Draw();
    pad1->cd();
    pad1->SetLogy();

    //h_gen_mAAA->Draw("E1, SAME");
    TH1D *hGenErr = (TH1D*) h_gen->Clone();
    hGenErr->SetDirectory(0);
    hGenErr->SetMarkerSize(0);
    hGenErr->SetFillColor(14);
    hGenErr->SetFillStyle(3344);

    h_gen->SetLineColor(kBlack);
    //h_gen_mAAA->SetFillColor(7);
    h_gen->SetFillColor(kCyan-4);
    h_gen->SetFillStyle(3144);
    h_gen->Draw("hist, SAME");
    hGenErr->Draw("SAME, E2");

    TH1D *hDataErr = (TH1D*) h_data->Clone();
    hDataErr->SetDirectory(0);
    hDataErr->SetMarkerSize(0);
    hDataErr->SetFillColor(14);
    hDataErr->SetFillStyle(3344);

    h_data->SetLineColor(kBlack);
    // h_data_mAAA->SetMarkerStyle(20);
    h_data->SetFillColor(kOrange+7);
    h_data->SetFillStyle(3144);
    h_data->Draw("hist, SAME");
    h_data->SetMinimum(0.1);
    //h_gen->SetMaximum(2*std::max(h_data->GetMaximum(), h_gen->GetMaximum()));
    h_gen->SetMaximum(100);
    h_gen->SetMinimum(0.001);
    // gPad->SetLogy();
    hDataErr->Draw("SAME, E2");

    //const TString graphName(Form("fakeRate%s_%s", region.c_str(), iso.c_str()));
    //TString xTitle(Form("m_#gamma_%s#gamma_%s (GeV)", phoNumStr1, phoNumStr2));
    //TString yTitle(Form("d#sigma/dm_#gamma_%s#gamma_%s (GeV)", phoNumStr1, phoNumStr2));

    TString xTitle = "|#Delta#eta"+phoNum1+phoNum2+"|";
    TString yTitle = "d#sigma/d|#Delta#eta"+phoNum1+phoNum2+"|";

    h_gen->GetXaxis()->SetTitle(xTitle);
    h_gen->GetYaxis()->SetTitleOffset(0.8);
    h_gen->GetYaxis()->SetTitle(yTitle);

    TLatex *t_label = new TLatex();
    t_label->SetTextSize(0.03);
    t_label->SetTextAlign(12);
    t_label->SetTextAlign(12);
    t_label->DrawLatexNDC(0.3,0.52, experiment+ " Preliminary");
    t_label->DrawLatexNDC(0.3,0.48, "#sqrt{s}= 13 TeV, 80.94 fb^{-1}");
    t_label->SetTextFont(42);

    auto leg = new TLegend(0.3,0.38,0.5,0.45);
    leg->SetBorderSize(0);
    leg->AddEntry(h_gen, simLegLabel, "f"); //FIXME: fixme label for PAT or DATA whenever it's available
    // leg->AddEntry(h_data, dataLegLabel, "lep");
    leg->AddEntry(h_data, dataLegLabel, "f");
    leg->Draw();

    TPad *pad2 = new TPad("pad2", "", 0, 0.0, 1, 0.3);
    pad2->SetTopMargin(0.1);
    pad2->SetBottomMargin(0.15);
    pad2->Draw();
    pad2->cd();
    pad2->SetGrid(0,1);
    createRatio(h_data, h_gen, 0.2, 0.8, xTitle);

    c->Update();
    TString outFile = "triphoton_absDEta"+phoNum1+phoNum2;
    if (isGenVSPat) outFile += "_GenPat_comp";
    if (isMinPt25) outFile += "_25";
    if (isMinPt35_35_15) outFile += "_35";
    c->SaveAs("plots/"+outFile+".pdf");

    // hstring
    // outputfile string
    // legendlabels
    //

  }

}
#endif
