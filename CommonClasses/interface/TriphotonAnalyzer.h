#ifndef TriphotonAnalyzer_h
#define TriphotonAnalyzer_h

#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

// Essentials
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
//#include "RecoEgamma/EgammaTools/interface/EffectiveAreas.h"
#include <vector>
#include "TLorentzVector.h"
#include "TH2D.h"
#include "TTree.h"

// for EGM ID
#include "RecoEgamma/EgammaTools/interface/EffectiveAreas.h"

// Miscellaneous
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/PatCandidates/interface/Photon.h"

// Common Classes
#include "triphoton-analysis/CommonClasses/interface/EventInfo.h"
#include "triphoton-analysis/CommonClasses/interface/GenParticleInfo.h"
#include "triphoton-analysis/CommonClasses/interface/DiPhotonInfo.h"
#include "triphoton-analysis/CommonClasses/interface/TriPhotonInfo.h"
#include "triphoton-analysis/CommonClasses/interface/PhotonInfo.h"
#include "triphoton-analysis/CommonClasses/interface/PhotonID.h"

// ECAL topology
#include "Geometry/CaloTopology/interface/CaloTopology.h"
#include "Geometry/CaloEventSetup/interface/CaloTopologyRecord.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "DataFormats/EcalDetId/interface/EBDetId.h"
#include "DataFormats/EcalDetId/interface/EEDetId.h"

using namespace std;
using namespace edm;

class TriphotonAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>{
  public:
    explicit TriphotonAnalyzer(const edm::ParameterSet&);
    ~TriphotonAnalyzer();

    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
    void fillGenInfo(const edm::Handle<edm::View<reco::GenParticle> > genParticles);
    void fillPhotonInfo(const edm::Handle<edm::View<pat::Photon> >&  photons);
    void fillMatchingInfo(const edm::Handle<edm::View<reco::GenParticle> > genParticles,
                          const edm::Handle<edm::View<pat::Photon> >& photons);
    void fillgenPhoIDInfo( ExoDiPhotons::genParticleInfo_t &genParticleInfo,
                           const reco::GenParticle *genPho,
                           double minDeltaR );
    void fillpatPhoIDInfo( ExoDiPhotons::photonInfo_t& photonInfo,
                           edm::Ptr<pat::Photon> pho  );
    void photonFiller(const std::vector<edm::Ptr<pat::Photon>>& photons);

    private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

      // ----------member data ---------------------------
      // edm::EDGetTokenT<TrackCollection> tracksToken_;  //used to select what tracks to read from configuration file

      edm::Service<TFileService> fs;

      edm::EDGetTokenT<edm::View<reco::GenParticle> > genParticlesToken_;
      edm::EDGetTokenT<edm::View<reco::GenParticle> > genParticlesMiniAODToken_;
      edm::EDGetTokenT<GenEventInfoProduct>           genInfoToken_;
      edm::EDGetTokenT<edm::View<pat::Photon> >       photonsMiniAODToken_;

      edm::InputTag genParticles_;

      TTree *fTree;


      ExoDiPhotons::eventInfo_t         fEventInfo;
      ExoDiPhotons::genParticleInfo_t   fGenPhoton1Info;
      ExoDiPhotons::genParticleInfo_t   fGenPhoton2Info;
      ExoDiPhotons::genParticleInfo_t   fGenPhoton3Info;
      ExoDiPhotons::diphotonInfo_t      fGenDiphotonInfo12;
      ExoDiPhotons::diphotonInfo_t      fGenDiphotonInfo13;
      ExoDiPhotons::diphotonInfo_t      fGenDiphotonInfo23;
      ExoDiPhotons::triphotonInfo_t     fGenTriphotonInfo;
      ExoDiPhotons::photonInfo_t        fPhoton1Info;
      ExoDiPhotons::photonInfo_t        fPhoton2Info;
      ExoDiPhotons::photonInfo_t        fPhoton3Info;
      ExoDiPhotons::diphotonInfo_t      fDiphotonInfo12;
      ExoDiPhotons::diphotonInfo_t      fDiphotonInfo13;
      ExoDiPhotons::diphotonInfo_t      fDiphotonInfo23;
      ExoDiPhotons::triphotonInfo_t     fTriphotonInfo;

      TTree *fSinglePhoTree;
      ExoDiPhotons::eventInfo_t         fSEventInfo;
      ExoDiPhotons::genParticleInfo_t   fGenPhotonInfo;
      ExoDiPhotons::photonInfo_t        fPhotonInfo;
      int fGenPhotonNumber;
      int fPhotonNumber;

      double xsec_;
      uint32_t nEventsSample_;
      TString outputFile_;

      // bool isLooseTriphotons_ ;
      // bool isMediumTriphotons_;
      bool isTightTriphotons_ ;
      // bool hasTriphotons_;

};

#endif
