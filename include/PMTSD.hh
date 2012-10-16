#ifndef PMTSD_h
#define PMTSD_h 1

#include "PMTHit.hh"
#include "G4VSensitiveDetector.hh"
#include <iostream>
#include <fstream>

class G4Step;
class G4HCofThisEvent;

class PMTSD : public G4VSensitiveDetector
{

public:
	PMTSD( G4String, G4int);
	~PMTSD();

	void Initialize(G4HCofThisEvent*);
	G4bool ProcessHits(G4Step*, G4TouchableHistory*);
	void EndOfEvent(G4HCofThisEvent*);

private:
	PMTHitsCollection* trackerCollection;
	int pCount;
	G4int layer;
	G4double totalEnergyOfTheEvent;
}; 

#endif
