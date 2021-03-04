#ifndef DerivedQuantities_h
#define DerivedQuantities_h

namespace TriPhotons
{

  //FIXME: Get Error. TH1F CalcError
  float CalcDeltaAbsEtaErr(float etaErr1, float etaErr2){
    float deltaAbsEtaErr = etaErr1 + etaErr2
    return deltaAbsEtaErr;
  }

  float CalcDeltaAbsEta (float eta1, float eta2 ){

    float deltaAbsEta  = fabs(eta1-eta2);
    return deltaAbsEta;

  }

  TH1F hDeltaAbsEta(TFile fHistSource, TString phoNumStr1, TString phoNumStr2){

    TString mcfmID1;
    TString mcfmID2;

    if (phoNumStr1 == "1" && phoNumStr2 == "2") mcfmID1 = "id2"; mcfmID2 = "id4";
    if (phoNumStr1 == "2" && phoNumStr2 == "3") mcfmID1 = "id4"; mcfmID2 = "id6";
    if (phoNumStr1 == "1" && phoNumStr2 == "3") mcfmID1 = "id2"; mcfmID2 = "id6";

    TH1F *hEtai = (TH1F*) fHistSource->Get(mcfmHistID1);
    TH1F *hEtaj = (TH1F*) fHistSource->Get(mcfmHistID2);
    TH1F *hDeltaAbsEta = new TH1F( "hDeltaAbsEta", "y("+phoNumStr1+phoNumStr2+")", 20, 0, 5 );

    int nbins1 = hEtai->GetXaxis()->GetNbins();

    hDeltaAbsEta->GetXaxis()->SetTitle("y("+phoNumStr1+phoNumStr2+")");
    hDeltaAbsEta->GetYaxis()->SetTitle(" d#sigma/dy("+phoNumStr1+phoNumStr2+") [fb]");

    hDeltaAbsEta->GetYaxis()->SetTitleOffset(1.2);
    hDeltaAbsEta->SetStats(false);


    for (int i = 0; i < nbins1; i++){

      eta1 = hEtai->GetBinContent(i);
      eta1Err = hEtai->GetBinErrorUp(i) - hEtai->GetBinErrorLow(i);

      eta2 = hEtaj->GetBinContent(i);
      eta2Err = hEtaj->GetBinErrorUp(i) - hEtaj->GetBinErrorLow(i);



    }


    return hDeltaAbsEta;
  } //

  // FIXME
  // TH1F CalculateDeltaPhi(TH1F ){
  //
  //   return hDeltaPhi;
  // } //

  // TH1F CalculatePhotonPairMinv( TH1F hE1, TH1F hE2, TH1F hE3 ){
  //
  //   return hPhotonPairMinv;
  // } //

} // end namespace

#endif
