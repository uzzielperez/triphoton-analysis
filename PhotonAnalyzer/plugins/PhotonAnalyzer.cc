#include "triphoton-analysis/PhotonAnalyzer/interface/PhotonAnalyzer.h"

PhotonAnalyzer::PhotonAnalyzer(const edm::ParameterSet& ps)
{
  usesResource("TFileService");
  edm::Service<TFileService> fs;

  genParticlesToken_        = consumes<edm::View<reco::GenParticle> > (ps.getParameter<InputTag>("genparticles"));
  nEventsSample_            =                                         (ps.getParameter<uint32_t>("nEventsSample"));
  genInfoToken_             = consumes<GenEventInfoProduct>           (ps.getParameter<edm::InputTag>("genInfo"));
  photonsMiniAODToken_      = consumes<edm::View<pat::Photon> >       (ps.getParameter<edm::InputTag>("photonsMiniAOD"));

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

  //-- Actions or Update Structs
  doDeltaRMatching(genParticles, photons, true);
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
  digGenAncestry(genMatch);

  //FIXME: make a function of the
// }





}


void PhotonAnalyzer::doDeltaRMatching(const edm::Handle<edm::View<reco::GenParticle> > genParticles,
                                      const edm::Handle<edm::View<pat::Photon> >& photons, bool debug=true)
{

  const reco::GenParticle *photon_gen_match         = NULL;
  // const reco::GenParticle *photon_gen_realMatch     = NULL;
  // const pat::Photon       *photon_reco_match        = NULL;

  // edm::Ptr<reco::GenParticle> genPhotonMatchDRp1;

  double deltaR_cut  = 0.1;
  // double deltaR_Real = 99999.99;
  //bool   isFake      = true;

  for (size_t i = 0; i < photons->size(); ++i){
    const auto pho = photons->ptrAt(i);
    double minDeltaR   = 99999.99;

    if ( !passPhoID(pho, "cutBasedPhotonID-Fall17-94X-V1-tight") ) return;

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
           if (debug) dumpMatchInfo(photon_gen_match, deltaR);


           if ( isGenFinalState && isGenPhoton ){

             //isFake               = false;
             // deltaR_Real          = deltaR;
             // photon_gen_realMatch = &(*gen);

             std::cout << "isGenFinalState GenPhoton" << std::endl;
             // FixMe: Trace back parentage to check if Real or fake:
             //checkPhotonRealness(photon_gen_realMatch, deltaR_Real); // FixMe Maybe not necessary
             //isGenMatchFromPartonShower(gen, deltaR);
           }
         }

      }
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
    return gen->mother(matchMotherIndex);
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
    std::cout << "Sole Mother: " << gen->mother(matchMotherIndex)->pdgId()
              << "; status: " << gen->mother(matchMotherIndex)->status()
              // << "; isFromHardInteraction: " << gen->isHardProcess()
              << "; pt: " << gen->mother(matchMotherIndex)->pt()
              << std::endl;
    return gen->mother(matchMotherIndex);
}

void PhotonAnalyzer::digGenAncestry(const reco::GenParticle *gen)
{
  auto genMother = getMother(gen);
  bool isfromHardProcess = genMother->status()==3;
  bool isfromPhotonMother = genMother->pdgId()==22;

  if ( !isfromHardProcess ){
    if (!isfromPhotonMother) std::cout << "Not from Photon/HardInteraction." << std::endl;
    else{
      std::cout << "From Photon. Inspect Mother of Mother -> " << getMother(genMother) << std::endl;
    }
  }
  else std::cout << "Is a Photon From Hard Process" << std::endl;
}

// PROMPT_STATUS_TYPE PhotonAnalyzer::getPromptStatus(const reco::GenParticle& p, const edm::Handle<vector<reco::GenParticle>>& particles) {
// 	if (p.status()==1 && p.numberOfMothers() && (std::abs(p.mother(0)->pdgId())<=22 || p.mother(0)->pdgId() == 2212)) {
// 		for (auto& genP : *particles) {
// 			auto absId = std::abs(genP.pdgId());
// 			if (genP.status()==23 && ROOT::Math::VectorUtil::DeltaR(p.p4(), genP.p4())<0.4) {
// 				if (absId==21 || absId<7) return FRAGMENTPROMPT;
// 				if (absId==11 || absId==13 || absId==15) return LEPTONPROMPT;
// 			}
// 		}
// 		return DIRECTPROMPT;
// 	}
// 	return NOPROMPT;
// };

//define this as a plug-in
DEFINE_FWK_MODULE(PhotonAnalyzer);
