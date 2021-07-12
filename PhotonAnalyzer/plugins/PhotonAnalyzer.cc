#include "triphoton-analysis/PhotonAnalyzer/interface/PhotonAnalyzer.h"
#include <iostream>
#include <fstream>

PhotonAnalyzer::PhotonAnalyzer(const edm::ParameterSet& ps)
{
  usesResource("TFileService");
  edm::Service<TFileService> fs;

  genParticlesToken_        = consumes<edm::View<reco::GenParticle> > (ps.getParameter<InputTag>("genparticles"));
  nEventsSample_            =                                         (ps.getParameter<uint32_t>("nEventsSample"));
  genInfoToken_             = consumes<GenEventInfoProduct>           (ps.getParameter<edm::InputTag>("genInfo"));
  photonsMiniAODToken_      = consumes<edm::View<pat::Photon> >       (ps.getParameter<edm::InputTag>("photonsMiniAOD"));
  //FIXME IDtype specify in config file:

  fTree = fs->make<TTree>("fTree", "DiphotonTree");
  fTree->Branch("Event",         &fEventInfo,       ExoDiPhotons::eventBranchDefString.c_str());
  fTree->Branch("GenPhoton",     &fGenPhotonInfo,   ExoDiPhotons::genParticleBranchDefString.c_str());
  fTree->Branch("GenPhotonNum",  &fGenPhotonNumber, "num/I");
  fTree->Branch("Photon",        &fPhotonInfo,      ExoDiPhotons::photonBranchDefString.c_str());
  fTree->Branch("PhotonNum",     &fPhotonNumber,    "num/I");
}


PhotonAnalyzer::~PhotonAnalyzer()
{

  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)

}

//
// member functions
//

// ------------ method called for each event  ------------
void
PhotonAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  using namespace std;
  using namespace pat;

  edm::Handle<GenEventInfoProduct>     genInfo;
  edm::Handle< edm::View<pat::Jet> >   jets;
  edm::Handle<edm::View<pat::Photon> > photons;
  edm::Handle<edm::View<reco::GenParticle> > genParticles;

  iEvent.getByToken(genInfoToken_,        genInfo);
  iEvent.getByToken(photonsMiniAODToken_, photons);
  iEvent.getByToken(genParticlesToken_,    genParticles);

  //---Initialize
  ExoDiPhotons::InitEventInfo(fEventInfo);
  ExoDiPhotons::InitGenParticleInfo(fGenPhotonInfo);
  ExoDiPhotons::InitPhotonInfo(fPhotonInfo);
  fGenPhotonNumber = -1;
  fPhotonNumber    = -1;

  std::string IDtype = "cutBasedPhotonID-Fall17-94X-V1-loose";
  bool verbose = true;

  if (verbose){
    outfile.open(logfile, ios::app);
  }


  //-- Actions or Update Structs

  //FIXME: Make a vector of selectedIDdPhotons and pass to doDeltaRMatching
  if (isTriphotonEvent(photons, IDtype)) doDeltaRMatching(genParticles, photons, IDtype, verbose);
  outfile.close();

  //doDeltaRMatching(genParticles, photons, true);


  // digGenAncestry(genParticles);
  // FIXME: doDeltaRMatchingfor photonCollection with at least three Photons passing the ID
  // doDeltaRMatching(genParticles, passedIDphotonCollection)

#ifdef THIS_IS_AN_EVENT_EXAMPLE
  Handle<ExampleData> pIn;
  iEvent.getByLabel("example",pIn);
#endif

#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  ESHandle<SetupData> pSetup;
  iSetup.get<SetupRecord>().get(pSetup);
#endif
}

// ------------ method called once each job just before starting event loop  ------------
void
PhotonAnalyzer::beginJob()
{

}

// ------------ method called once each job just after ending the event loop  ------------
void
PhotonAnalyzer::endJob()
{

}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
PhotonAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);

  //Specify that only 'tracks' is allowed
  //To use, remove the default given above and uncomment below
  //ParameterSetDescription desc;
  //desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
  //descriptions.addDefault(desc);
}

bool PhotonAnalyzer::passPhoID(const edm::Ptr<pat::Photon> pho, std::string IDtype){

  //str IDtype = "cutBasedPhotonID-Fall17-94X-V1-tight"
  bool passPhotonID  = pho->photonID(IDtype);
  // Store information in tree so that we can do some plots
  return passPhotonID;
}

bool PhotonAnalyzer::isTriphotonEvent(const edm::Handle<edm::View<pat::Photon> >& photons, std::string IDtype){

  int nPassPhotonID = 0;
  bool hasTriphotonPassID = false;

  for (size_t i = 0; i < photons->size(); ++i){
      const auto pho = photons->ptrAt(i);
      if (passPhoID(pho, IDtype)) nPassPhotonID++;
  }
  if (nPassPhotonID == 3) hasTriphotonPassID = true;

  return hasTriphotonPassID;
}

void PhotonAnalyzer::fillPassPhoID(const edm::Ptr<pat::Photon> pho, ExoDiPhotons::photonInfo_t& photonInfo){
   photonInfo.passEGMLooseID  = pho->photonID("cutBasedPhotonID-Fall17-94X-V1-loose");
   photonInfo.passEGMMediumID = pho->photonID("cutBasedPhotonID-Fall17-94X-V1-medium");
   photonInfo.passEGMTightID  = pho->photonID("cutBasedPhotonID-Fall17-94X-V1-tight");
}

void PhotonAnalyzer::dumpMatchInfoToFile(const reco::GenParticle *genMatch, double deltaR, double deltaRcut =0.1){
 //FIXME: check line - check the information
 // Photon matchpdgID
 // Photon matchpdgID
// if (genMatch->pdgId() !=22) {
  outfile << "Dumping GenMatchInfo for dRcut " << deltaRcut
            << "; PDG ID: " << genMatch->pdgId() // FIXME: Create Map to print out actual particle name
            << "; isHardInteraction: " << genMatch->isHardProcess()
            << "; status: " << genMatch->status()
            << "; pt: "   << genMatch->pt()
            << "; eta: "  << genMatch->eta()
            << "; phi: "  << genMatch->phi()
            << "; dR: "   << deltaR << std::endl;
  // dumpPromptStatusToFile(genMatch, true);

  //FIXME: make a function of the
// }

}

void PhotonAnalyzer::dumpMatchInfo(const reco::GenParticle *genMatch, double deltaR, double deltaRcut =0.1){
 //FIXME: check line - check the information
 // Photon matchpdgID
 // Photon matchpdgID
// if (genMatch->pdgId() !=22) {


  std::cout << "Dumping GenMatchInfo for dRcut " << deltaRcut
            << "; PDG ID: " << genMatch->pdgId() // FIXME: Create Map to print out actual particle name
            << "; isHardInteraction: " << genMatch->isHardProcess()
            << "; status: " << genMatch->status()
            << "; pt: "   << genMatch->pt()
            << "; eta: "  << genMatch->eta()
            << "; phi: "  << genMatch->phi()
            << "; dR: "   << deltaR << std::endl;
  dumpMatchInfoToFile(genMatch, deltaR);
  dumpPromptStatus(genMatch, true);
  dumpPromptStatusToFile(genMatch, true);
  digGenAncestry(genMatch);
  //FIXME: make a function of the
// }

}




void PhotonAnalyzer::doDeltaRMatching(const edm::Handle<edm::View<reco::GenParticle> > genParticles,
                                      const edm::Handle<edm::View<pat::Photon> >& photons,
                                      std::string IDtype="cutBasedPhotonID-Fall17-94X-V1-tight",
                                      bool debug=true)
{
  if (debug) outfile << "====== New Event =====" << std::endl;
  const reco::GenParticle *photon_gen_match         = NULL;
  //const reco::GenParticle *photon_gen_realMatch     = NULL;
  // const pat::Photon       *photon_reco_match        = NULL;

  // edm::Ptr<reco::GenParticle> genPhotonMatchDRp1;

  double deltaR_cut  = 0.1;
  // double deltaR_Real = 99999.99;
  //bool   isFake      = true;

  for (size_t i = 0; i < photons->size(); ++i){
    const auto pho = photons->ptrAt(i);
    double minDeltaR   = 99999.99;

    if ( !passPhoID( pho, IDtype ) ) return; // FIXME: just pass selectedPhotons

    outfile << "Finding match for: "
            << "\t PAT Pho pt:" << pho->pt()
            << " eta: " << pho->eta()
            << " phi: " << pho->phi()
            << std::endl;


    for (size_t i = 0; i < genParticles->size(); ++i){
      const auto gen       = genParticles->ptrAt(i);

      double deltaR        = reco::deltaR(pho->eta(), pho->phi(), gen->eta(), gen->phi());

      bool isGenFinalState = ( gen->status()==1 ) ? true : false;
      bool isGenPhoton     = ( gen->pdgId()==22 ) ? true : false;


      if (deltaR < minDeltaR){

         minDeltaR         = deltaR;
         // photon_reco_match = &(*pho);
         photon_gen_match  = &(*gen);


         if ( deltaR <= deltaR_cut ){


           if ( debug ) dumpMatchInfo(photon_gen_match, deltaR); // any match dumpInfo
           //if ( isGenFinalState && isGenPhoton ){ // Why do we need to check if isGenFinalState
           if ( isGenPhoton ){

             //isFake               = false;
             // deltaR_Real          = deltaR;
             // photon_gen_realMatch = &(*gen);

             if (isGenFinalState) std::cout << "isGenFinalState GenPhoton" << std::endl;
             digGenAncestry(photon_gen_match);
             // FixMe: Trace back parentage to check if Real or fake:
             //checkPhotonRealness(photon_gen_realMatch, deltaR_Real); // FixMe Maybe not necessary
             //isGenMatchFromPartonShower(gen, deltaR);
           } // check is Genfinal Stat

         }
      }
      //FIXME outfile << DONE matching to this reco photon

    } //gen loop
    // cout << "BEST MATCH FOUND is " << photon_gen_match->pdgId() << std::endl; //FIXME (would be nice to have a pdgId() map for print outs)
    // // if (minDeltaR < 0.5)  std::cout << minDeltaR << std::endl;
    // if ( minDeltaR < 0.1 ) cout << "MATCH FOUND! minDR: " << minDeltaR
    //                             << "; pt: "   << photon_gen_match->pt()  << " : " << photon_reco_match->pt() << std::endl;
    //                             // << "; eta = " << photon_gen_match->eta() << " : " << photon_reco_match->eta()
    //                             //<< "; phi = " << photon_gen_match->phi() << " : " << photon_reco_match->phi() << std::endl;
   } // pat loop
}



void PhotonAnalyzer::checkPhotonRealness(const reco::GenParticle *photon_gen_realMatch, double deltaR){
 //FIXME: check line
 const reco::GenParticle *genMatchMother = &(*photon_gen_realMatch);
 std::cout << "Check Photon realness.. Status = " << genMatchMother->status()
           << "; ID  = " << genMatchMother->pdgId()
           << "; pt  = " << genMatchMother->pt()
           << "; dR  = " << deltaR << std::endl;
}

auto PhotonAnalyzer::getMother(const reco::GenParticle *gen)
{
  std::cout << "Number of Mothers: " << gen->numberOfMothers() << "; m: " << gen->mother() << std::endl;
  double minMotherMatchDeltaR = 10000;
  int matchMotherIndex = 0;

  // while (gen->mother()){
    for (unsigned int j = 0; j < gen->numberOfMothers(); j++) {
  	  double deltaR = reco::deltaR(gen->eta(),gen->phi(),gen->mother(j)->eta(),gen->mother(j)->phi());
  	    std::cout << "\t    Mother " << j
                  << ": Status = " << gen->mother(j)->status()
                  << "; ID = "     << gen->mother(j)->pdgId()
                  << "; pt = "     << gen->mother(j)->pt()
                  << "; eta = " << gen->mother(j)->eta()
                  << "; phi = " << gen->mother(j)->phi()
                  << "; deltaR = " << deltaR << std::endl;
                  //isHardProcess

  	  if (deltaR < minMotherMatchDeltaR) {
  	    minMotherMatchDeltaR = deltaR;
  	    matchMotherIndex = j;
  	  }
    } //end mother loop
    std::cout << "Sole Mother: " << gen->mother(matchMotherIndex)->pdgId()
              << "; status: " << gen->mother(matchMotherIndex)->status()
              << "; isFromHardInteraction: " << gen->isHardProcess()
              << "; pt: " << gen->mother(matchMotherIndex)->pt()
              << std::endl;

    auto soleMother = gen->mother(matchMotherIndex);
    return soleMother;
}

auto PhotonAnalyzer::getMother(const reco::Candidate *gen)
{
  std::cout << "Number of Mothers: " << gen->numberOfMothers() << "; m: " << gen->mother() << std::endl;
  double minMotherMatchDeltaR = 10000;
  int matchMotherIndex = 0;

  // while (gen->mother()){
    for (unsigned int j = 0; j < gen->numberOfMothers(); j++) {
  	  double deltaR = reco::deltaR(gen->eta(),gen->phi(),gen->mother(j)->eta(),gen->mother(j)->phi());
  	    std::cout << "\t    Mother " << j
                  << ": Status = " << gen->mother(j)->status()
                  << "; ID = "     << gen->mother(j)->pdgId()
                  << "; pt = "     << gen->mother(j)->pt()
                  << "; eta = " << gen->mother(j)->eta()
                  << "; phi = " << gen->mother(j)->phi()
                  << "; deltaR = " << deltaR << std::endl;

  	  if (deltaR < minMotherMatchDeltaR) {
  	    minMotherMatchDeltaR = deltaR;
  	    matchMotherIndex = j;
  	  }
    } //end mother loop
    std::cout << "Sole Mother index, pdgId(): " << matchMotherIndex << ", " << gen->mother(matchMotherIndex)->pdgId()
              << "; status: " << gen->mother(matchMotherIndex)->status()
              // << "; isFromHardInteraction: " << gen->isHardProcess()
              << "; pt: " << gen->mother(matchMotherIndex)->pt()
              << std::endl;

    auto soleMother = gen->mother(matchMotherIndex);
    return soleMother;
}

auto PhotonAnalyzer::getMotherToFile(const reco::GenParticle *gen, bool verbose=false)
{
  outfile << "Number of Mothers: " << gen->numberOfMothers() << "; m: " << gen->mother() << std::endl;
  double minMotherMatchDeltaR = 10000;
  int matchMotherIndex = 0;

  // while (gen->mother()){
    for (unsigned int j = 0; j < gen->numberOfMothers(); j++) {
  	  double deltaR = reco::deltaR(gen->eta(),gen->phi(),gen->mother(j)->eta(),gen->mother(j)->phi());
  	    outfile << "\t    Mother " << j
                  << ": Status = " << gen->mother(j)->status()
                  << "; ID = "     << gen->mother(j)->pdgId()
                  << "; pt = "     << gen->mother(j)->pt()
                  << "; eta = " << gen->mother(j)->eta()
                  << "; phi = " << gen->mother(j)->phi()
                  << "; deltaR = " << deltaR << std::endl;

  	  if (deltaR < minMotherMatchDeltaR) {
  	    minMotherMatchDeltaR = deltaR;
  	    matchMotherIndex = j;
  	  }
    } //end mother loop
    auto soleMother = gen->mother(matchMotherIndex);
    outfile << "Sole Mother: " << soleMother->pdgId()
              << "; status: " << soleMother->status()
              // << "; isFromHardInteraction: " << soleMother->isHardProcess() // mother is a candidate not genParticle
              << "; pt: " << soleMother->pt()
              << std::endl;

    return soleMother;
}

// FIXME: Also get daughters?

auto PhotonAnalyzer::getMotherToFile(const reco::Candidate *gen, bool verbose=false)
{
  outfile << "Number of Mothers: " << gen->numberOfMothers() << "; m: " << gen->mother() << std::endl;
  double minMotherMatchDeltaR = 10000;
  int matchMotherIndex = 0;

  // while (gen->mother()){
    for (unsigned int j = 0; j < gen->numberOfMothers(); j++) {
  	  double deltaR = reco::deltaR(gen->eta(),gen->phi(),gen->mother(j)->eta(),gen->mother(j)->phi());
  	    outfile << "\t    Mother " << j
                  << ": Status = " << gen->mother(j)->status()
                  << "; ID = "     << gen->mother(j)->pdgId()
                  << "; pt = "     << gen->mother(j)->pt()
                  << "; eta = " << gen->mother(j)->eta()
                  << "; phi = " << gen->mother(j)->phi()
                  << "; deltaR = " << deltaR << std::endl;

  	  if (deltaR < minMotherMatchDeltaR) {
  	    minMotherMatchDeltaR = deltaR;
  	    matchMotherIndex = j;
  	  }
    } //end mother loop
    outfile << "Sole Mother: " << gen->mother(matchMotherIndex)->pdgId()
              << "; status: " << gen->mother(matchMotherIndex)->status()
              << "; pt: " << gen->mother(matchMotherIndex)->pt()
              << std::endl;

    auto soleMother = gen->mother(matchMotherIndex);
    return soleMother;
}

void PhotonAnalyzer::digGenAncestryToFile(const reco::GenParticle *gen)
{

  // while (gen->mother()){
  //   auto genMother = getMother(gen);
  //
  //   std::cout << "=== Tracing back to Hard Interaction ===" << std::endl;
  //   if ((matchedMother->pdgId() == 21 || std::abs(matchedMother->pdgId() < 9)) && matchedMother->pt() == 0) photon_check = false;
  // }

  // ====scratch
  auto genMother = getMotherToFile(gen, true);
  bool isfromHardProcess = genMother->status()==3;
  bool isfromPhotonMother = genMother->pdgId()==22;

  if ( !isfromPhotonMother ){

    outfile << "Not from Photon Mother. Checking if from HardProcess proton" << std::endl;

    if (isfromHardProcess) outfile << "\t REAL Photon from Hard Process with pdgId: " << genMother->pdgId()
                                     << "; status: " << genMother->status() << std::endl;

    else outfile << "\t FAKE Photon with photon mother pdgId: " << genMother->pdgId()
                   << "; status: " << genMother->status() << std::endl;

  }

  else outfile << "From Photon. Inspect Mother of Photon Mother pdgId()-> " << getMother(genMother)->pdgId()
                 << "; status ID: " << getMother(genMother)->status()
                 << std::endl;

  //if (p.status()==1 && p.numberOfMothers() && (std::abs(p.mother(0)->pdgId())<=22 || p.mother(0)->pdgId() == 2212))

}

void PhotonAnalyzer::digGenAncestry(const reco::GenParticle *gen)
{

  // while (gen->mother()){
  //   auto genMother = getMother(gen);
  //
  //   std::cout << "=== Tracing back to Hard Interaction ===" << std::endl;
  //   if ((matchedMother->pdgId() == 21 || std::abs(matchedMother->pdgId() < 9)) && matchedMother->pt() == 0) photon_check = false;
  // }

  // ====scratch
  auto genMother = getMother(gen);
  bool isfromHardProcess = genMother->status()==3;
  bool isfromPhotonMother = genMother->pdgId()==22;

  if ( !isfromPhotonMother ){

    std::cout << "Not from Photon Mother. Checking if from HardProcess proton" << std::endl;

    if (isfromHardProcess) std::cout << "\t REAL Photon from Hard Process with pdgId: " << genMother->pdgId()
                                     << "; status: " << genMother->status() << std::endl;

    else std::cout << "\t FAKE Photon with photon mother pdgId: " << genMother->pdgId()
                   << "; status: " << genMother->status() << std::endl;

  }

  else std::cout << "From Photon. Inspect Mother of Photon Mother pdgId()-> " << getMother(genMother)->pdgId()
                 << "; status ID: " << getMother(genMother)->status()
                 << std::endl;

  //if (p.status()==1 && p.numberOfMothers() && (std::abs(p.mother(0)->pdgId())<=22 || p.mother(0)->pdgId() == 2212))

}

// From https://github.com/jainshilpi/aNTGC_ggNtuplizer
enum PROMPT_STATUS_TYPE {
	DIRECTPROMPT, FRAGMENTPROMPT, LEPTONPROMPT, NOPROMPT, INVALID = -99
};

PROMPT_STATUS_TYPE getPromptStatus(const reco::GenParticle& p, const edm::Handle<vector<reco::GenParticle>>& particles) {
	if (p.status()==1 && p.numberOfMothers() && (std::abs(p.mother(0)->pdgId())<=22 || p.mother(0)->pdgId() == 2212)) {
		for (auto& genP : *particles) {
			auto absId = std::abs(genP.pdgId());
			if (genP.status()==23 && ROOT::Math::VectorUtil::DeltaR(p.p4(), genP.p4())<0.4) {
				if (absId==21 || absId<7) return FRAGMENTPROMPT;
				if (absId==11 || absId==13 || absId==15) return LEPTONPROMPT;
			}
		}
		return DIRECTPROMPT;
	}
	return NOPROMPT;
};

void PhotonAnalyzer::dumpPromptStatus(const reco::GenParticle *gen, bool verbose=false){

auto genMother = getMother(gen);
std::string promptType = "PROMPT";
bool isPhotonPrompt    =  gen->pdgId() == 22;
bool isFragmentPrompt  =  ( std::abs(gen->pdgId() ) ==std::abs(21) ) || ( std::abs(gen->pdgId()) < 7 );
bool isLeptonPrompt    =  std::abs(gen->pdgId() ) ==std::abs(11) || std::abs(gen->pdgId() ) == std::abs(11) || std::abs(gen->pdgId())==std::abs(15);
bool isDirectPrompt    =  gen->status()==1 && (std::abs(genMother->pdgId())<=22 || genMother->pdgId() == 2212);


  if (verbose && !isDirectPrompt){
    if ( isPhotonPrompt ) std::cout << "PHOTONPROMPT" << std::endl;
    if ( isFragmentPrompt ) std::cout << "FRAGMENTPROMPT" << std::endl;
    if ( isLeptonPrompt ) std::cout << "LEPTONPROMPT" << std::endl;
  }

  if (isDirectPrompt) {
    if ( isPhotonPrompt ) std::cout << "PHOTONPROMPT" << std::endl;
    if ( isFragmentPrompt ) std::cout << "FRAGMENTPROMPT" << std::endl;
    if ( isLeptonPrompt ) std::cout << "LEPTONPROMPT" << std::endl;
  }

};


void PhotonAnalyzer::dumpPromptStatusToFile(const reco::GenParticle *gen, bool verbose=false){

auto genMother = getMotherToFile(gen, false);
std::string promptType = "PROMPT";
bool isPhotonPrompt    =  gen->pdgId() == 22;
bool isFragmentPrompt  =  ( std::abs(gen->pdgId() ) ==std::abs(21) ) || ( std::abs(gen->pdgId()) < 7 );
bool isLeptonPrompt    =  std::abs(gen->pdgId() ) ==std::abs(11) || std::abs(gen->pdgId() ) == std::abs(11) || std::abs(gen->pdgId())==std::abs(15);
bool isDirectPrompt    =  gen->status()==1 && (std::abs(genMother->pdgId())<=22 || genMother->pdgId() == 2212);


  if (verbose && !isDirectPrompt){
    if ( isPhotonPrompt ) outfile << "PHOTONPROMPT" << std::endl;
    if ( isFragmentPrompt ) outfile << "FRAGMENTPROMPT" << std::endl;
    if ( isLeptonPrompt ) outfile << "LEPTONPROMPT" << std::endl;
  }

  if (isDirectPrompt) {
    if ( isPhotonPrompt ) outfile << "DIRECT PHOTONPROMPT" << std::endl;
    if ( isFragmentPrompt ) outfile << "DIRECT FRAGMENTPROMPT" << std::endl;
    if ( isLeptonPrompt ) outfile << "DIRECT LEPTONPROMPT" << std::endl;
  }

};

//define this as a plug-in
DEFINE_FWK_MODULE(PhotonAnalyzer);
