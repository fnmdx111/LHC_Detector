#include "RootIO.hh"
#include "G4Timer.hh"
#include "RunAction.hh"
#include "G4Run.hh"
#include "G4SDManager.hh"

RunAction::RunAction()
{
  timer = new G4Timer;
}


RunAction::~RunAction()
{
  delete timer;
}

void RunAction::BeginOfRunAction(const G4Run* aRun)
{
  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl; 
  timer->Start();
	RootIO::GetInstance()->SetDirName("data1");
	RootIO::GetInstance()->OpenFile();
}


void RunAction::EndOfRunAction(const G4Run* aRun)
{   
  timer->Stop();
  G4cout << "number of event = " << aRun->GetNumberOfEvent() 
         << " " << *timer << G4endl;
	//RootIO::GetInstance()->Average(5);
	G4cout << "File closed..." << G4endl;
	RootIO::GetInstance()->CloseFile();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
