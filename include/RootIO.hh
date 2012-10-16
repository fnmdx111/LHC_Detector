#ifndef ROOTIO_H
#define ROOTIO_H

#include "TROOT.h"
#include "TFile.h"
#include "TH2I.h"
#include "TF2.h"
#include "TH1.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TColor.h"
#include "TExec.h"
#include "TCanvas.h"

#include "G4Run.hh"
#include "PMTHit.hh"

//1. print photons[][] to .root and .txt
//2. graph the 2-D histogram

class RootIO
{
	public:	
		virtual ~RootIO();
		static RootIO* GetInstance();
		void SetDirName(G4String name);
		void OpenFile();
		void WriteLayer(G4double energy, int layer);
		void Average(int events);		
		void CloseFile();
		void InPhotons(G4int);
		void WriteEnergy(G4double energy);

	protected:
				RootIO();
	private:
				TFile* fo;
				FILE* xcl;
				char fname[256];
				char fname2[256];
				TH2I* e_histo;
				//TH1F* d_histo;
				//TH1D* e1d_histo;
				long photons[1001][10];
				G4String dirname;
};
#endif // INCLUDE_ROOTIO_HH
