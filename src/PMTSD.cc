#include "PMTSD.hh"
#include "PMTHit.hh"
#include "G4Track.hh"
#include "G4ParticleDefinition.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4ParticleTypes.hh"
#include "G4ThreeVector.hh"
#include "G4RunManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"

PMTSD::~PMTSD()
{}

PMTSD::PMTSD(G4String name, G4int layer_in):
			G4VSensitiveDetector(name)
{
	layer = layer_in;
	pCount = 0;
	char num[5];
	sprintf(num,"%d",layer); 
	G4String ly_num = num;
	G4String prefix = "Layer";
	G4String suffix = "_HC";
	G4String HCname = prefix + ly_num + suffix;
	collectionName.insert(HCname);
	totalEnergyOfTheEvent = 0;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void PMTSD::Initialize(G4HCofThisEvent* HCE)
{
  trackerCollection = new PMTHitsCollection
                       (SensitiveDetectorName,collectionName[0]); 
  static G4int HCID = -1;
  if(HCID<0)
  { HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]); }
  HCE->AddHitsCollection( HCID, trackerCollection ); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4bool PMTSD::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
	if (aStep->GetTrack()->GetCurrentStepNumber() == 1) 
{
		//RootIO::GetInstance()->WriteLayer(ke/keV, layer);
		//RootIO::GetInstance()->WriteEnergy(keV);
		//RootIO::GetInstance()->IncPhotons(layer);
		PMTHit* newHit = new PMTHit();
		newHit-> SetTrackID (aStep -> GetTrack() -> GetTrackID());
		newHit->SetPos(aStep->GetPostStepPoint()->GetPosition());
		newHit->SetID(aStep->GetTrack()->GetDynamicParticle()->GetDefinition()->GetParticleName());
		newHit->SetEn(aStep->GetTrack()->GetKineticEnergy());
		newHit->SetLayer(layer);
		trackerCollection->insert(newHit );
	}
	else
	{
		return false;
	}

	return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void PMTSD::EndOfEvent(G4HCofThisEvent*)
{
	G4int NbHits = trackerCollection->entries();
   
	pCount += NbHits;
	
	for (G4int i=0;i<NbHits;i++) 
	{
		(*trackerCollection)[i]->Print();
	}
	std::ofstream fout;
  fout.open("layer_photons_data.txt", std::fstream::app);
	fout << NbHits << " ";
	if (layer == 10) fout << "\n";
  fout.close();
	fout.open("layer_energy_data.txt", std::fstream::app);
	fout << totalEnergyOfTheEvent/eV << " ";
	if (layer == 10) fout << "\n";
	fout.close();
  //if (layer == 10) 
//	{
	//	fout.open("event_data.txt", std::fstream::app);
		//fout << "total Photon/event: " << pCount << "  total Energy/event: "
		//	<<totalEnergyOfTheEvent << "\n";
		//fout.close();
	//}
	//RootIO::GetInstance()->WriteLayer(&hitsVector, layer);
}

