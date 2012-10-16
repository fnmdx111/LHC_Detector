#ifndef ExN06PrimaryGeneratorMessenger_h
#define ExN06PrimaryGeneratorMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class PrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;

class PrimaryGeneratorMessenger: public G4UImessenger
{
  public:
    PrimaryGeneratorMessenger(PrimaryGeneratorAction*);
   ~PrimaryGeneratorMessenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
    PrimaryGeneratorAction*      Action;
    G4UIdirectory*               gunDir; 
    G4UIcmdWithADoubleAndUnit*   polarCmd;
};

#endif

