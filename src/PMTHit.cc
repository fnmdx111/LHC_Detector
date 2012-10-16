#include "PMTHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "RootIO.hh"


G4Allocator<PMTHit> PMTHitAllocator;

PMTHit::PMTHit() {}

PMTHit::~PMTHit() {}

PMTHit::PMTHit(const PMTHit& right)
	: G4VHit()
{
trackID = right.trackID;
pos     = right.pos;
}

const PMTHit& PMTHit::operator=(const PMTHit& right)
{
trackID = right.trackID;
pos     = right.pos;
return *this;
}

G4int PMTHit::operator == (const PMTHit& right) const
{
return (this==&right) ? 1 : 0;
}

void PMTHit::Draw() {}

void PMTHit::Print() 
{
	RootIO::GetInstance()->WriteLayer(GetEn()/eV,GetLayer());
}





















