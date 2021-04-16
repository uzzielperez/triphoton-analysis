#include "triphoton-analysis/CommonClasses/interface/TriphotonAnalyzer.h"

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
 #include "FWCore/Utilities/interface/InputTag.h"
 #include "DataFormats/TrackReco/interface/Track.h"
 #include "DataFormats/TrackReco/interface/TrackFwd.h"
//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<>
// This will improve performance in multithreaded jobs.


using reco::TrackCollection;

// class TriphotonAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
//    public:
//       explicit TriphotonAnalyzer(const edm::ParameterSet&);
//       ~TriphotonAnalyzer();
//
//       static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
//
//
//    private:
//       virtual void beginJob() override;
//       virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
//       virtual void endJob() override;
//
//       // ----------member data ---------------------------
//       // edm::EDGetTokenT<TrackCollection> tracksToken_;  //used to select what tracks to read from configuration file
// };

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
TriphotonAnalyzer::TriphotonAnalyzer(const edm::ParameterSet& ps)
 //:
  //tracksToken_(consumes<TrackCollection>(iConfig.getUntrackedParameter<edm::InputTag>("tracks")))
{
   //now do what ever initialization is needed
   usesResource("TFileService");

   genParticlesToken_    = consumes<edm::View<reco::GenParticle> > (ps.getParameter<InputTag>("genparticles"));
   genInfoToken_         = consumes<GenEventInfoProduct>           (ps.getParameter<InputTag>("genInfo"));
   photonsMiniAODToken_  = consumes<edm::View<pat::Photon> >       (ps.getParameter<edm::InputTag>("photonsMiniAOD"));
   nEventsSample_        =                                         (ps.getParameter<uint32_t>("nEventsSample"));
   outputFile_           =                                  TString(ps.getParameter<std::string>("outputFile"));

   fTree = fs->make<TTree>("fTree", "TriphotonTree");
   fTree->Branch("Event",         &fEventInfo,         ExoDiPhotons::eventBranchDefString.c_str());
   fTree->Branch("GenPhoton1",    &fGenPhoton1Info,    ExoDiPhotons::genParticleBranchDefString.c_str());
   fTree->Branch("GenPhoton2",    &fGenPhoton2Info,    ExoDiPhotons::genParticleBranchDefString.c_str());
   fTree->Branch("GenPhoton3",    &fGenPhoton3Info,    ExoDiPhotons::genParticleBranchDefString.c_str());
   fTree->Branch("GenDiPhoton12", &fGenDiphotonInfo12, ExoDiPhotons::diphotonBranchDefString.c_str());
   fTree->Branch("GenDiPhoton13", &fGenDiphotonInfo13, ExoDiPhotons::diphotonBranchDefString.c_str());
   fTree->Branch("GenDiPhoton23", &fGenDiphotonInfo23, ExoDiPhotons::diphotonBranchDefString.c_str());
   fTree->Branch("GenTriPhoton",  &fGenTriphotonInfo,  ExoDiPhotons::triphotonBranchDefString.c_str());
   fTree->Branch("Photon1",       &fPhoton1Info,       ExoDiPhotons::photonBranchDefString.c_str());
   fTree->Branch("Photon2",       &fPhoton2Info,       ExoDiPhotons::photonBranchDefString.c_str());
   fTree->Branch("Photon3",       &fPhoton3Info,       ExoDiPhotons::photonBranchDefString.c_str());
   fTree->Branch("DiPhoton12",    &fDiphotonInfo12,    ExoDiPhotons::diphotonBranchDefString.c_str());
   fTree->Branch("DiPhoton13",    &fDiphotonInfo13,    ExoDiPhotons::diphotonBranchDefString.c_str());
   fTree->Branch("DiPhoton23",    &fDiphotonInfo23,    ExoDiPhotons::diphotonBranchDefString.c_str());
   fTree->Branch("TriPhoton",     &fTriphotonInfo,     ExoDiPhotons::triphotonBranchDefString.c_str());

}


TriphotonAnalyzer::~TriphotonAnalyzer()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
TriphotonAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;
   using namespace reco;
   using namespace pat;

   // Handle, getByToken
  edm::Handle<edm::View<reco::GenParticle> > genParticles;
  edm::Handle<GenEventInfoProduct>           genInfo;
  edm::Handle<edm::View<pat::Photon> >       photons;

  iEvent.getByToken(genParticlesToken_,    genParticles);
  iEvent.getByToken(genInfoToken_,         genInfo);
  iEvent.getByToken(photonsMiniAODToken_,  photons);

  // Initialize
  ExoDiPhotons::InitEventInfo(fEventInfo);
  ExoDiPhotons::InitGenParticleInfo(fGenPhoton1Info);
  ExoDiPhotons::InitGenParticleInfo(fGenPhoton2Info);
  ExoDiPhotons::InitGenParticleInfo(fGenPhoton3Info);
  ExoDiPhotons::InitDiphotonInfo(fGenDiphotonInfo12);
  ExoDiPhotons::InitDiphotonInfo(fGenDiphotonInfo13);
  ExoDiPhotons::InitDiphotonInfo(fGenDiphotonInfo23);
  ExoDiPhotons::InitTriphotonInfo(fGenTriphotonInfo);
  ExoDiPhotons::InitPhotonInfo(fPhoton1Info);
  ExoDiPhotons::InitPhotonInfo(fPhoton2Info);
  ExoDiPhotons::InitPhotonInfo(fPhoton3Info);

  // Update
  ExoDiPhotons::FillBasicEventInfo(fEventInfo, iEvent);
  ExoDiPhotons::FillGenEventInfo(fEventInfo, &(*genInfo));

  //FIXME: if local weight = xsec_
  //ExoDiPhotons::FillEventWeights(fEventInfo, xsec_, nEventsSample_);
  ExoDiPhotons::FillEventWeights(fEventInfo, outputFile_, nEventsSample_);
  fillGenInfo(genParticles);
  fillPhotonInfo(photons);
  fTree->Fill();

  // ==== FIXME:
  // Update
  // bool passEGMLooseID;
  // bool passEGMMediumID;
  // bool passEGMTightID;



   // for(const auto& track : iEvent.get(tracksToken_) ) {
   //    // do something with track parameters, e.g, plot the charge.
   //    // int charge = track.charge();
   // }

#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
void
TriphotonAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
TriphotonAnalyzer::endJob()
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TriphotonAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
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

void TriphotonAnalyzer::fillGenInfo(const edm::Handle<edm::View<reco::GenParticle> > genParticles){
  // Store information in these vectors
  vector< edm::Ptr<const reco::GenParticle> > genPhotons;
  vector<int> interactingPartons;

  // Loop over gen particles to store photons
  for (size_t i = 0; i < genParticles->size(); ++i){
    const auto gen = genParticles->ptrAt(i);
    //Pythia8 status 20-30 is Hard interaction
    if (gen->isHardProcess() && gen->pt() == 0) interactingPartons.push_back(gen->pdgId());
    if (gen->isHardProcess() && gen->pdgId()==22){
      genPhotons.push_back(gen);
    }
  }

  sort(genPhotons.begin(), genPhotons.end(), ExoDiPhotons::comparePhotonsByPt);

  if(interactingPartons.size() == 2){
        fEventInfo.interactingParton1PdgId = interactingPartons[0];
        fEventInfo.interactingParton2PdgId = interactingPartons[1];
      }

  else cout << "Exactly two interacting partons not found!" << endl;

  //---- Photon Information
  // Samples with only fakes may have no hard-process photons
  // Samples with one fake may have only one hard-process photon in diphoton pair
  // Samples with fakes may have only one hard-process photon in the triphoton system

  //if (genPhotons.size() > 3) exit(1); //FIXME - what is this for again?
  if(genPhotons.size() < 1) return;
  const reco::GenParticle *genPhoton1 = &(*genPhotons.at(0));
  if (genPhoton1) ExoDiPhotons::FillGenParticleInfo(fGenPhoton1Info, genPhoton1);

  if(genPhotons.size() < 2) return;
  const reco::GenParticle *genPhoton2 = &(*genPhotons.at(1));
  if (genPhoton2) ExoDiPhotons::FillGenParticleInfo(fGenPhoton2Info, genPhoton2);

  if(genPhotons.size() < 3) return;
  const reco::GenParticle *genPhoton3 = &(*genPhotons.at(2));
  if (genPhoton3) ExoDiPhotons::FillGenParticleInfo(fGenPhoton3Info, genPhoton3);

  //---- Diphoton/Triphoton Information
  if (genPhoton1 && genPhoton2) ExoDiPhotons::FillDiphotonInfo(fGenDiphotonInfo12,genPhoton1,genPhoton2);
  if (genPhoton1 && genPhoton3) ExoDiPhotons::FillDiphotonInfo(fGenDiphotonInfo13,genPhoton1,genPhoton3);
  if (genPhoton2 && genPhoton3) ExoDiPhotons::FillDiphotonInfo(fGenDiphotonInfo23,genPhoton2,genPhoton3);
  if (genPhoton1 && genPhoton2 && genPhoton3) ExoDiPhotons::FillTriphotonInfo(fGenTriphotonInfo,genPhoton1,genPhoton2,genPhoton3);
} // end of fillGenInfo

void TriphotonAnalyzer::fillPhotonInfo(const edm::Handle<edm::View<pat::Photon> >&  photons){
  std::vector<edm::Ptr<pat::Photon>> patPhotons;

  for (size_t i = 0; i < photons->size(); ++i){
    const auto pho = photons->ptrAt(i);
    patPhotons.push_back(pho);

    // EGamma ID Standard;
    bool passEGMLooseID  = pho->photonID("cutBasedPhotonID-Fall17-94X-V1-loose");
    bool passEGMMediumID = pho->photonID("cutBasedPhotonID-Fall17-94X-V1-medium");
    bool passEGMTightID  = pho->photonID("cutBasedPhotonID-Fall17-94X-V1-tight");

    std::cout << "Photon pt: "  << pho->pt()
              << "; eta: "      << pho->eta()
              << "; phi: "      << pho->phi()
              << "; LooseID: "  << passEGMLooseID
              << "; MediumID: " << passEGMMediumID
              << "; TightID:  " << passEGMTightID
              << std::endl;
  }

  std::cout << "NPhotons = " << photons->size() << std::endl;

} //end


//define this as a plug-in
DEFINE_FWK_MODULE(TriphotonAnalyzer);
