#ifndef PhotonAnalyzer_h
#define PhotonAnalyzer_h

// system include files
#include <memory>
#include <fstream>

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
#include "triphoton-analysis/CommonClasses/interface/JetInfo.h"
// ECAL topology
#include "Geometry/CaloTopology/interface/CaloTopology.h"
#include "Geometry/CaloEventSetup/interface/CaloTopologyRecord.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "DataFormats/EcalDetId/interface/EBDetId.h"
#include "DataFormats/EcalDetId/interface/EEDetId.h"

using namespace std;
using namespace edm;

//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class PhotonAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
  public:
    explicit PhotonAnalyzer(const edm::ParameterSet&);
    ~PhotonAnalyzer();

    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
    bool passPhoID(const edm::Ptr<pat::Photon>, std::string IDtype);
    bool isTriphotonEvent(const edm::Handle<edm::View<pat::Photon> >& photons, std::string IDtype);
    void fillPassPhoID(const edm::Ptr<pat::Photon> pho, ExoDiPhotons::photonInfo_t& photonInfo);
    void dumpMatchInfoToFile(const reco::GenParticle *genMatch, double deltaR, double deltaRcut);
    void dumpMatchInfo(const reco::GenParticle *genMatch, double deltaR, double deltaRcut);
    void doDeltaRMatching(const edm::Handle<edm::View<reco::GenParticle> > genParticles,
                          const edm::Handle<edm::View<pat::Photon> >& photons,
                          std::string IDtype,
                          bool debug);
    void checkPhotonRealness(const reco::GenParticle *photon_gen_realMatch, double deltaR);
    auto getMother(const reco::GenParticle *gen);
    auto getMother(const reco::Candidate *gen);
    auto getMotherToFile(const reco::GenParticle *gen, bool verbose);
    auto getMotherToFile(const reco::Candidate *gen, bool verbose);
    void digGenAncestry(const reco::GenParticle *genMatch);
    void digGenAncestryToFile(const reco::GenParticle *genMatch);
    void dumpPromptStatus(const reco::GenParticle *genMatch, bool verbose);
    void dumpPromptStatusToFile(const reco::GenParticle *genMatch, bool verbose);
    // PROMPT_STATUS_TYPE PhotonAnalyzer::getPromptStatus(const reco::GenParticle& p, const edm::Handle<vector<reco::GenParticle>>& particles);

  private:
    virtual void beginJob() override;
    virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
    virtual void endJob() override;

    edm::Service<TFileService> fs;

    edm::EDGetTokenT<edm::View<reco::GenParticle> > genParticlesToken_;
    edm::EDGetTokenT<edm::View<reco::GenParticle> > genParticlesMiniAODToken_;
    edm::EDGetToken                                 photonsMiniAODToken_;
    edm::EDGetTokenT<GenEventInfoProduct>           genInfoToken_;


    edm::InputTag genParticles_;
    edm::InputTag particles_;

    TTree *fgenTree;
    TTree *fTree;

    // ExoDiPhotons::photonInfo_t fPhotonInfo;
    // ExoDiPhotons::jetInfo_t fJetInfo;
    // ExoDiPhotons::photonInfo_t fPhotonMatchInfo;
    // ExoDiPhotons::genParticleInfo_t fPhotonGenMatchInfo;
    // ExoDiPhotons::genParticleInfo_t fPhotonGenParentInfo;

    ExoDiPhotons::eventInfo_t fEventInfo;
    int is_real_template_photon = 0;
    ExoDiPhotons::genParticleInfo_t   fGenPhotonInfo;
    int fGenPhotonNumber;

    ExoDiPhotons::photonInfo_t        fPhotonInfo;
    int fPhotonNumber;

    uint32_t nEventsSample_;
    TString outputFile_;

    // enum PROMPT_STATUS_TYPE {
    //    DIRECTPROMPT, FRAGMENTPROMPT, LEPTONPROMPT, NOPROMPT, INVALID = -99
    // }; // from https://github.com/jainshilpi/aNTGC_ggNtuplizer/

    // std::vector<double> gen_match_pt;
    // std::vector<double> gen_match_eta;
    // std::vector<double> gen_match_phi;

    std::string logfile = "triphotonGGJetsEventsLog.txt";
    std::ofstream outfile;

};

#endif
