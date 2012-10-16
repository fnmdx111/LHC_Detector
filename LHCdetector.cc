#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"
#include "RunAction.hh"
#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif
#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc,char** argv)
{
  // Seed the random number generator manually
  //
  G4long myseed = time(NULL);
  CLHEP::HepRandom::setTheSeed(myseed); 

 
  // Run manager
  //
  G4RunManager* runManager = new G4RunManager;

  // UserInitialization classes - mandatory
  //
  G4VUserPhysicsList* physics = new PhysicsList;
  runManager-> SetUserInitialization(physics);
  //
  G4VUserPrimaryGeneratorAction* gen_action = new PrimaryGeneratorAction;
  runManager->SetUserAction(gen_action);
  //
  G4VUserDetectorConstruction* detector = new DetectorConstruction;
  runManager-> SetUserInitialization(detector);

#ifdef G4VIS_USE
  // visualization manager
  //
 G4VisManager* visManager = new G4VisExecutive;
 visManager->Initialize();
#endif

  // UserAction classes
  //
  G4UserRunAction* run_action = new RunAction;
  runManager->SetUserAction(run_action);
  
  // Initialize G4 kernel
  //
  runManager->Initialize();
    
  // Get the pointer to the User Interface manager
  //
  G4UImanager* UImanager = G4UImanager::GetUIpointer(); 
   
  if (argc==1)   // Define UI session for interactive mode
    {
#ifdef G4UI_USE
      G4UIExecutive * ui = new G4UIExecutive(argc,argv);
#ifdef G4VIS_USE
      UImanager->ApplyCommand("/control/execute vis.mac");     
#endif
      ui->SessionStart();
      delete ui;
#endif
    }
  else         // Batch mode
    {
      G4String command = "/control/execute ";
      G4String fileName = argv[1];
      UImanager->ApplyCommand(command+fileName);
    }

#ifdef G4VIS_USE
  delete visManager;
#endif
  delete runManager;

  return 0;
}
