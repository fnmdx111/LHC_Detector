#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
   ~DetectorConstruction();

  public:
    G4VPhysicalVolume* Construct();

  private:
    G4double expHall_x;
    G4double expHall_y;
    G4double expHall_z;
};

#endif
