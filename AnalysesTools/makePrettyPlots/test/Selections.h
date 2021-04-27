#ifndef Selections_h
#define Selections_h

namespace TriPhotons
{
  TCut ptEB              = "Photon.pt > 10 && Photon.isEB==1";
  TCut ptEE              = "Photon.pt > 10 && Photon.isEE==1";
  TCut genPtEB           = "GenPhoton.pt > 10 && GenPhoton.eta > -1.44442 && GenPhoton.eta < 1.44442";
  TCut genPtEE           = "GenPhoton.pt > 10 && fabs(GenPhoton.eta) > 1.566 && fabs(GenPhoton.eta) < 2.5";
  TCut isGenMatchedToPat = "GenPhoton.minDeltaR < 0.5";

  TCut IDcut(TString IDcat){
    TCut IDcuts;
    if (IDcat == "loose")  IDcuts = "Photon.passEGMLooseID==1";
    if (IDcat == "medium") IDcuts = "Photon.passEGMMediumID==1";
    if (IDcat == "tight")  IDcuts = "Photon.passEGMTightID==1";
    if (IDcat == "highPT") IDcuts = "Photon.passHighPtID==1";
    if (IDcat == "lowPT")  IDcuts = "Photon.passLowPtID==1";
    return IDcuts;
  };

  void ratioPlot(TH1F *h1, TH1F *h2, TCanvas *c){
    gStyle->SetOptStat(0);
    auto rp = new TRatioPlot(h1, h2);
    c->SetTicks(0,1);
    rp->Draw();
    c->Update();
    c->SaveAs("plots/ratioPlot.pdf");
  }

  void createRatio(TH1F* hNumerator, TH1F* hDenominator,
                   Color_t color, float min=-1.2, float max=1.2, TString yTitle="efficiency",
                   TString xTitle="p_{t} (GeV)", bool showRatio=false, TString experiment="CMS"){
    TH1F *hRatio = (TH1F*) hNumerator->Clone("hNumerator");
    hRatio->SetLineColor(color);
    hRatio->SetMarkerColor(color);
    // hRatio->SetMinimum(0.4);
    // hRatio->SetMaximum(1.1);
    hRatio->SetStats(0);
    hRatio->Divide(hDenominator);
    hRatio->Draw("ep, SAME");
    hRatio->SetTitle("");
    hRatio->GetYaxis()->SetTitle(xTitle);
    // hRatio->GetYaxis()->SetTitleSize(25);
    hRatio->GetYaxis()->SetTitleOffset(0.8);
    hRatio->GetXaxis()->SetTitle(yTitle);
    hRatio->GetXaxis()->SetTitleSize(25);
    hRatio->GetXaxis()->SetTitleFont(43);
    hRatio->GetXaxis()->SetTitleOffset(4.5);
    hRatio->GetXaxis()->SetLabelFont(43);
    hRatio->GetXaxis()->SetLabelSize(16);
    // hRatio->SetMinimum(min);
    // hRatio->SetMaximum(max);
  }

  void efficiency(TString Ntuple, TString matchOrSelEff = "matching", TString region = "EB",  TString IDcat = "loose" ,double pTmin = 0, double pTmax = 200){
    TFile f(Ntuple);
    f.ls();
    TTree *fTree = (TTree *) f.Get("demo/fSinglePhoTree");
    gStyle->SetOptStat(0);

    TString label;
    TCut numeratorCut;
    TCut denominatorCut;

    if (matchOrSelEff == "matching"){
      if (region == "EB"){
        std::cout << "Doing Matching Efficiency for Barrell" << std::endl;
        denominatorCut = genPtEB;
        numeratorCut   = genPtEB && isGenMatchedToPat;
        label = "matchingEB";
      }
      if (region == "EE"){
        std::cout << "Doing Matching Efficiency for Endcaps" << std::endl;
        denominatorCut = genPtEE;
        numeratorCut   = genPtEE && isGenMatchedToPat;
        label = "matchingEE";
      }

    }
    if (matchOrSelEff == "selection"){
      if (region == "EB"){
        TCut photonID = IDcut(IDcat);
        std::cout << "Doing Selection Efficiency for Barrell" << std::endl;
        denominatorCut = genPtEB && isGenMatchedToPat;
        numeratorCut   = genPtEB && isGenMatchedToPat && photonID;
        label = "selectionEB";
      }
      if (region == "EE"){
        TCut photonID = IDcut(IDcat);
        std::cout << "Doing Selection Efficiency for Endcaps" << std::endl;
        denominatorCut = genPtEE && isGenMatchedToPat;
        numeratorCut   = genPtEE && isGenMatchedToPat && photonID;
        label = "selectionEE";
      }

    }
    //FIXME: Do for EE & return if categories are not available

    TH1F *hDenPt = new TH1F("hDenPt", "hDenPt"+label, 25, pTmin, pTmax);
    TH1F *hNumPt = new TH1F("hNumPt", "hNumPt"+label, 25, pTmin, pTmax);

    TCanvas *c = new TCanvas("c", "c", 500, 500);
    c->SetLogy();

    fTree->Draw("GenPhoton.pt>>hNumPt", numeratorCut, "goff");
    fTree->Draw("GenPhoton.pt>>hDenPt", denominatorCut, "goff");

    hNumPt->Draw("hist");
    hDenPt->SetLineColor(2);
    hDenPt->Draw("hist, SAME");

    hNumPt->GetXaxis()->SetTitle("pT (GeV)");
    hNumPt->GetXaxis()->SetLabelSize(0.2);
    c->Clear();

    // https://root.cern.ch/doc/v610/classTRatioPlot.html
    auto rp = new TRatioPlot(hNumPt, hDenPt);
    // c->SetTicks(0, 1);
    rp->Draw();
    gPad->Modified(); gPad->Update();
    TPad *p = rp->GetUpperPad();
    auto leg = new TLegend(0.6,0.6,0.8,0.63);
    leg->SetHeader("ID "+IDcat+region,"C");
    leg->SetBorderSize(0);
    leg->AddEntry(hNumPt, "Gen Pt > 10, dR > 0.5 match", "l");
    leg->AddEntry(hDenPt, "Gen Pt > 10", "l");
    leg->Draw();
    p->Modified(); p->Update();

    rp->GetLowerRefGraph()->SetMinimum(0);
    rp->GetLowerRefGraph()->SetMaximum(2);
    rp->GetLowerRefYaxis()->SetTitle("ratio");
    rp->GetLowerRefYaxis()->SetLabelSize(0.02);

    rp->GetUpperRefYaxis()->SetTitle("entries");
    rp->GetUpperRefYaxis()->SetLabelSize(0.02);

    c->Update();
    TString outputName = region+label;
    if (matchOrSelEff == "selection") outputName + IDcat;
    c->SaveAs("plots/"+outputName+"Efficiency.pdf");
    f.Close();

  }

// ------ Test
  // void analyzeSinglePhoEff(TString Ntuple, TString matchOrSelEff = "matching", TString region = "EB",
  //                          double pTmin = 0, double pTmax = 200){
  //
  //   TFile f(Ntuple);
  //   f.ls();
  //   TTree *fTree = (TTree *) f.Get("demo/fSinglePhoTree");
  //   fTree->Print();
  //
  //   TString label;
  //   TCut numeratorCut;
  //   TCut denominatorCut;
  //
  //   if (matchOrSelEff == "matching" && region == "EB"){
  //     std::cout << "Doing Matching Efficiency for Barrell" << std::endl;
  //     denominatorCut = genPtEB;
  //     numeratorCut   = genPtEB && isGenMatchedToPat;
  //     label = "matchingEB";
  //   }
  //
  //   TH1F *hDenPt = new TH1F("hDenPt", "hDenPt"+label, 25, pTmin, pTmax);
  //   TH1F *hNumPt = new TH1F("hNumPt", "hNumPt"+label, 25, pTmin, pTmax);
  //
  //   TCanvas *c = new TCanvas("c", "c", 600, 300);
  //   c->SetLogy();
  //
  //   TPad *padMainPlot = new TPad("padMainPlot", "", 0, 0.3, 1, 1.0);
  //   padMainPlot->SetBottomMargin(0.2); // joins upper and lower plot
  //   padMainPlot->Draw();
  //   padMainPlot->cd();
  //   padMainPlot->SetLogy();
  //
  //   fTree->Draw("GenPhoton.pt>>hNumPt", numeratorCut, "goff");
  //   fTree->Draw("GenPhoton.pt>>hDenPt", denominatorCut, "goff");
  //
  //   hNumPt->Draw("hist");
  //   hDenPt->SetLineColor(2);
  //   hDenPt->Draw("hist, SAME");
  //
  //   auto leg = new TLegend(0.4,0.35,0.6,0.45);
  //   leg->SetBorderSize(0);
  //   leg->AddEntry(hNumPt, "Gen Pt > 10, dR > 0.5 match", "l");
  //   leg->AddEntry(hDenPt, "Gen Pt > 10", "l");
  //   leg->Draw();
  //
  //   TPad *padRatio = new TPad("padRatio", "", 0, 0.05, 1, 0.3);
  //   padRatio->SetTopMargin(0);
  //   padRatio->SetBottomMargin(0.4);
  //   padRatio->Draw();
  //   padRatio->cd();
  //   padRatio->SetGrid(0,1);
  //   createRatio(hNumPt, hDenPt, kBlack);
  //
  //   // ratioPlot(hNumPt, hDenPt, c);
  //
  //   c->Update();
  //   c->SaveAs("plots/test"+label+"Efficiency.pdf");
  //
  //   }


// Some Examples from: https://root.cern.ch/doc/v608/classTRatioPlot.html
  void ratioplot1() {
       gStyle->SetOptStat(0);
       auto c1 = new TCanvas("c1", "A ratio example");
       auto h1 = new TH1D("h1", "h1", 50, 0, 10);
       auto h2 = new TH1D("h2", "h2", 50, 0, 10);
       auto f1 = new TF1("f1", "exp(- x/[0] )");
       f1->SetParameter(0, 3);
       h1->FillRandom("f1", 1900);
       h2->FillRandom("f1", 2000);
       h1->Sumw2();
       h2->Scale(1.9 / 2.);
       h1->GetXaxis()->SetTitle("x");
       h1->GetYaxis()->SetTitle("y");
       auto rp = new TRatioPlot(h1, h2);
       c1->SetTicks(0, 1);
       rp->Draw();
       c1->Update();
       c1->SaveAs("plots/sampleRatio1.pdf");
  }

  void ratioplot2() {
   gStyle->SetOptStat(0);
   auto c1 = new TCanvas("c1", "fit residual simple");
   auto h1 = new TH1D("h1", "h1", 50, -5, 5);
   h1->FillRandom("gaus", 2000);
   h1->Fit("gaus");
   h1->GetXaxis()->SetTitle("x");
   c1->Clear(); // Fit does not draw into correct pad
   auto rp1 = new TRatioPlot(h1);
   rp1->Draw();
   rp1->GetLowerRefYaxis()->SetTitle("ratio");
   rp1->GetUpperRefYaxis()->SetTitle("entries");
   c1->Update();
   c1->SaveAs("plots/sampleRatio2.pdf");
 }

  // // Global TCuts (FIXME: does string substitution work for TCuts)
  // TCut pT3_EB = "Photon3.pt > 10 && Photon3.isEB==1";
  // TCut pT2_EB = "Photon2.pt > 10 && Photon2.isEB==1";
  // TCut pT1_EB = "Photon1.pt > 10 && Photon1.isEB==1";
  //
  // TCut genpT3_EB = "GenPhoton3.pt > 10 && GenPhoton3.eta > -1.442 && GenPhoton3.eta < 1.442";
  // TCut genpT2_EB = "GenPhoton2.pt > 10 && GenPhoton2.eta > -1.442 && GenPhoton2.eta < 1.442";
  // TCut genpT1_EB = "GenPhoton1.pt > 10 && GenPhoton1.eta > -1.442 && GenPhoton1.eta < 1.442";
  //
  // TCut isGen3Matched = " GenPhoton3.minDeltaR < 0.5 ";
  // TCut isGen2Matched = " GenPhoton2.minDeltaR < 0.5 ";
  // TCut isGen1Matched = " GenPhoton1.minDeltaR < 0.5 ";
  //
  // TCut IDcuts1 = "Photon1.passLowPtID==1";
  // TCut IDcuts2 = "Photon2.passLowPtID==1";
  // TCut IDcuts3 = "Photon3.passLowPtID==1";
  //
  // void analyzeEff(TString ntupleName, TString matchOrSelection = "matching"){
  //     // Matching only
  //
  //     TFile f(ntupleName);
  //     f.ls();
  //     TTree *fTree = (TTree *) f.Get("demo/fSinglePhoTree");
  //     fTree->Print();
  //
  //     TString histname = "matching";
  //     bool matchOnly   = true;
  //     if ( matchOrSelection == "selection" ) matchOnly = false;
  //     if ( matchOrSelection != "selection" and matchOrSelection != "matching" ){
  //       std::cout << "Only 'selection' and 'matching' are allowed. " << std::endl;
  //       return -1;
  //     }
  //     std::cout << "Doing matchOnly efficiency: " << matchOnly << std::endl;
  //
  //     //------ Histograms to fill and divide:
  //     TH1F *hden3_pt = new TH1F("hden3_pt", "h3_" + histname, 20, 0, 100);
  //     TH1F *hnum3_pt = new TH1F("hnum3_pt", "h3_gen" + histname, 20, 0, 100);
  //     TH1F *hden2_pt = new TH1F("hden2_pt", "h2_", 20, 0, 100);
  //     TH1F *hnum2_pt = new TH1F("hnum2_pt", "h2_gen" + histname, 20, 0, 100);
  //     TH1F *hden1_pt = new TH1F("hden1_pt", "h1_", 20, 0, 100);
  //     TH1F *hnum1_pt = new TH1F("hnum1_pt", "h1_gen" + histname, 20, 0, 100);
  //
  //     //----- Matching Efficiency Cuts
  //     // Denominator: Pass Pt cut
  //     TCut matchEffDen1 = genpT1_EB;
  //     TCut matchEffDen2 = genpT2_EB;
  //     TCut matchEffDen3 = genpT3_EB;
  //
  //     // Numerator: Pass Pt cut, and Matched
  //     TCut matchEffNum1 = matchEffDen1 && isGen1Matched;
  //     TCut matchEffNum2 = matchEffDen2 && isGen2Matched;
  //     TCut matchEffNum3 = matchEffDen3 && isGen3Matched;
  //
  //     // FIXME: Is there a way we could do this just specifying the number in Selections
  //     TCut numCut1;
  //     TCut numCut2;
  //     TCut numCut3;
  //     TCut denCut1;
  //     TCut denCut2;
  //     TCut denCut3;
  //
  //     numCut1 = matchEffNum1;
  //     numCut2 = matchEffNum2;
  //     numCut3 = matchEffNum3;
  //     denCut1 = matchEffDen1;
  //     denCut2 = matchEffDen2;
  //     denCut3 = matchEffDen3;
  //
  //     //------- Fill Hist
  //     // Efficiency of Passing LowPT ID for a matched object
  //     fTree->Draw("GenPhoton3.pt>>hnum3_pt", numCut3, "goff");
  //     fTree->Draw("GenPhoton3.pt>>hden3_pt", denCut3, "goff"); //den
  //     fTree->Draw("GenPhoton2.pt>>hnum2_pt", numCut2, "goff");
  //     fTree->Draw("GenPhoton2.pt>>hden2_pt", denCut2, "goff");
  //     fTree->Draw("GenPhoton1.pt>>hnum1_pt", numCut1, "goff");
  //     fTree->Draw("GenPhoton1.pt>>hden1_pt", denCut1, "goff");
  //
  //     //------ Draw Efficiency
  //     TCanvas *c1 =  new TCanvas("c1", "c1", 600, 300);
  //     c1->SetLogy();
  //
  //     hnum3_pt->Draw("hist");
  //     hden3_pt->SetLineColor(2);
  //     hden3_pt->Draw("hist, SAME");
  //
  //     TString label = "minDR_0p5";
  //     TString study;
  //
  //     //----- Bookkeeping
  //     if (matchOnly)    study = "Matching Efficiency";
  //     else {
  //       study = "Selection Efficiency";
  //       label = label + "_sel";
  //       histname = histname + "_LowpTID";
  //     }
  //
  //     c1->Update();
  //     c1->SaveAs("plots/efficiencyPho3" + label + ".pdf");
  //
  // }

} // end namespace

#endif
