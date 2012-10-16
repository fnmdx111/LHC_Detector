#ifndef PMTHit_h
#define PMTHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class PMTHit : public G4VHit
{
public:

	PMTHit();
	~PMTHit();
	PMTHit( const PMTHit& right);
	const PMTHit& operator = (const PMTHit&);
	G4int operator == (const PMTHit&) const;
	
	inline void* operator new(size_t);
	inline void operator delete(void*);

	void Draw();
	void Print();

public:

	void SetTrackID (G4int track) { trackID = track; };
	void SetLayer    (int layer) {layerNo = layer; };
	void SetPos     (G4ThreeVector xyz){pos = xyz;};
	 void SetID      (G4String name){ particleID = name; };
   void SetEn    (G4double ke){particleEn = ke;};  
      G4int GetTrackID()    { return trackID; };
      G4int GetLayer()    { return layerNo; };      
      G4ThreeVector GetPos(){ return pos; };
	  G4String GetID(){ return particleID; };
     G4double GetEn() {return particleEn; }; 
  private:
      G4int         trackID;
      G4int         layerNo;
      G4ThreeVector pos;
      G4String	    particleID;
			G4double      particleEn; 

};

typedef G4THitsCollection<PMTHit> PMTHitsCollection;

extern G4Allocator<PMTHit> PMTHitAllocator;

inline void* PMTHit::operator new(size_t)
{
	void* aHit;
	aHit = (void*) PMTHitAllocator.MallocSingle();
	return aHit;
}

inline void PMTHit::operator delete(void* aHit)
{
	PMTHitAllocator.FreeSingle((PMTHit*) aHit);
}

#endif
 
