#include <sstream>
#include <time.h>
#include "RootIO.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4EventManager.hh"
#include "G4Event.hh"
#include <cmath>

#define Planck 4.135667516e-15
#define Vlight 299792458e+9

const G4double hc = Planck * Vlight;
static RootIO* instance = 0;

RootIO::RootIO()
{}

RootIO::~RootIO()
{}

void RootIO::SetDirName(G4String name)
{
	dirname = name;
}

void RootIO::OpenFile()
{
	G4cout << "start to open file..." << G4endl;
	sprintf(fname,"~/LHC_Detector/data/%s.root", dirname.c_str());
	fo = new TFile(fname,"RECREATE");  //make Root file
	sprintf(fname2,"~/LHC_Detector/data/%s.txt", dirname.c_str());
	//xcl = fopen(fname2,"w");  //make Excel file
	char hist_name[256];
	sprintf(hist_name, "Photon_Counts");
	e_histo = new TH2I(hist_name,hist_name,10,1,10,1000,0,1000);
}

RootIO* RootIO::GetInstance()
{
  if (instance == 0 )
  {
    instance = new RootIO();
  }
  return instance;
}

void RootIO::WriteLayer(G4double energy, int layer)
{
	//transform energy(eV) into WaveLength(nm)
	G4double wavelength = (hc / energy);
	G4int wl = (G4int) wavelength;
	if (wavelength > 1000)
									wl = 1000;
	e_histo->Fill(layer,wl);
	G4cout << layer << ": " << wl << "; ";
	photons[wl][layer] ++;
}

void RootIO::Average(int events)
{
	float scale = 1/((float) events);
	e_histo->Scale(scale);  //Scale histo to represent average over # of events
	
	//write Excel file
	for(int j = 0; j < 10001; j++)
	{
		fprintf(xcl,"%d cm",j+1);
		for(int k = 0; k < 9; k++)
		{
			float count = (float)(photons[j][k])/((float) events);
			fprintf(xcl,"\t%f", count );
		}
		fprintf(xcl,"\n");
	}
}

void RootIO::CloseFile()
{
	e_histo->GetXaxis()->SetTitle("Layer of plate");
	e_histo->GetYaxis()->SetTitle("Wavelength (nm)");
	e_histo->GetZaxis()->SetTitle("Photons");
  Double_t Red[3]    = { 1.00, 0.00, 0.00};
  Double_t Green[3]  = { 0.00, 1.00, 0.00};
  Double_t Blue[3]   = { 1.00, 0.00, 1.00};
  Double_t Length[3] = { 0.00, 0.50, 1.00 };
	Int_t NCont=50;
  Int_t FI = TColor::CreateGradientColorTable(3,Length,Red,Green,Blue,50);
	static Int_t  colors[50];
  for (int i=0; i<50; i++) colors[i] = FI+i; 
  gStyle->SetPalette(50, colors);
	e_histo->SetContour(NCont);
	e_histo->Draw( "surf1");
	fo->Write();
	fo->Close();  //Title, write, and close Root file
	//fclose(xcl);  //close Excel file
}
