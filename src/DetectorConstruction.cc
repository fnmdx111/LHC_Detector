#include "DetectorConstruction.hh"
#include "G4RotationMatrix.hh"
#include "globals.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4VPhysicalVolume.hh"
#include "G4UserLimits.hh"
#include "G4SDManager.hh"
#include "G4VSensitiveDetector.hh"
#include "G4RunManager.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4ios.hh"
#include "G4NistManager.hh"
#include "G4PVReplica.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpBoundaryProcess.hh"
#include "PMTSD.hh"
#include "PMTHit.hh"

//---------------------------------------------------------
//
DetectorConstruction::DetectorConstruction()
{
	expHall_x = expHall_y = expHall_z = 1000.0*mm;
}

DetectorConstruction::~DetectorConstruction(){;}

//----------------------------------------------------------
//

G4VPhysicalVolume* DetectorConstruction::Construct()
{

	//--------------------------Materials------------------------

	//------------Element----------------
	//
	G4double a;  G4double z;  G4double density;
	G4double weightRatio;  G4String name;
	G4String symbol;  G4int nElem;

	//elements for mixtures and compounds
	G4Element* H  = new G4Element(name="Hydrogen",symbol="H",  z=1.,  a= 1.01*g/mole);
	G4Element* C  = new G4Element(name="Carbon",  symbol="C",  z=6.,  a= 12.01*g/mole);
	G4Element* N  = new G4Element(name="Nitrogen",symbol="N",  z=7.,  a= 14.01*g/mole);
	G4Element* O  = new G4Element(name="Oxygen" , symbol="O",  z=8.,  a= 16.00*g/mole);
	G4Element* Si = new G4Element(name="Silicon", symbol="Si", z=14., a= 28.09*g/mole);


	//-------------Glass------------------
	//
	//type1 for core
	//
	G4int ncomponents;
	G4int natoms;

	G4Material* PTP = new G4Material(name="PTP",density= 1.234*g/cm3, ncomponents=2);
	PTP->AddElement(C, natoms=18);
	PTP->AddElement(H , natoms=14);

	G4double PTPPhotonEnergy[45] =
	{1.0*eV,2.48*eV,2.611*eV,2.756*eV,2.918*eV,2.988*eV,3.024*eV,3.100*eV,3.139*eV,3.179*eV,3.221*eV,3.263*eV,3.307*eV,3.351*eV,3.425*eV,3.543*eV,3.647*eV,3.658*eV,3.680*eV,3.701*eV,3.713*eV,3.758*eV,3.815*eV,3.875*eV,3.974*eV,4.133*eV,4.276*eV,4.429*eV,4.640*eV,4.509*eV,4.559*eV,4.593*eV,4.733*eV,4.844*eV,4.901*eV,4.960*eV,5.082*eV,5.232*eV,5.391*eV,5.511*eV,5.636*eV,5.767*eV,5.905*eV,6.200*eV,10.*eV};

	G4double PTPAbslength[45] =
	{3.0*um,3.0*um,3.0*um,3.0*um,3.0*um,3.0*um,3.0*um,3.0*um,3.0*um,3.0*um,3.0*um,3.0*um,3.0*um,3.0*um,3.0*um,3.0*um,3.0*um,3.0*um,3.0*um,3.0*um,3.0*um,3.0*um,2.995*um,2.756*um,2.512*um,2.122*um,1.488*um,1.146*um,1.0*um,1.0*um,1.146*um,1.341*um,1.634*um,1.976*um,2.268*um,2.439*um,2.634*um,2.707*um,2.634*um,2.234*um,1.488*um,0.805*um,500.0*um,1000.0*um,1000.*um};

	G4double PTPem[45] =
	{0.,0.,0.,0.,0.002,0.12,0.24,0.43,0.095,0.143,0.190,0.238,0.310,0.429,0.738,0.762,0.810,0.976,1.0,0.952,0.810,0.750,0.786,0.524,0.014,0.036,0.024,0.010,0.002,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.};

	G4double PTPRindex[45] ={1.65,1.65,1.65,1.65,1.65,1.65,1.65,1.65,1.65,1.65,1.65,1.65,1.65,1.65,1.65,1.65,1.65,1.65,1.65,1.65,1.65,1.65,1.65,1.65,1.65,1.65,1.65,1.65,1.65,1.65,1.65,1.65,1.65,1.65,1.65,1.65,1.65,1.65,1.65,1.65,1.65,1.65,1.65,1.65,1.65};

	G4MaterialPropertiesTable* PTPMPT = new G4MaterialPropertiesTable();
	PTPMPT->AddProperty("RINDEX",  PTPPhotonEnergy, PTPRindex, 45);
	PTPMPT->AddProperty("ABSLENGTH",  PTPPhotonEnergy, PTPAbslength, 45);
	PTPMPT->AddProperty("SCINTILLATION",  PTPPhotonEnergy, PTPem, 45);					PTPMPT->AddProperty("FASTCOMPONENT",PTPPhotonEnergy, PTPem,45);
	PTPMPT->AddProperty("SLOWCOMPONENT",PTPPhotonEnergy, PTPem,45);
	PTPMPT->AddConstProperty("SCINTILLATIONYIELD",27000./MeV);
	PTPMPT->AddConstProperty("RESOLUTIONSCALE",2.012);
	PTPMPT->AddConstProperty("FASTTIMECONSTANT", 3.3*ns);
	PTPMPT->AddConstProperty("SLOWTIMECONSTANT",3.7*ns);
	PTPMPT->AddConstProperty("YIELDRATIO",0.8);
	PTP->SetMaterialPropertiesTable(PTPMPT);

	//type2 for glass plate
	//type3 for cladding
	//
	//type1 glass is composed of 5 percent Europium and 95 percent Pyrex
	//
	G4NistManager* man = G4NistManager::Instance();
	G4Material* pyrexGlass = man->FindOrBuildMaterial("G4_Pyrex_Glass");
	G4Material* europium = man->FindOrBuildMaterial("G4_Eu");
	G4Material* G01 = new G4Material("eu_glass",2.375*g/cm3,2);
	G01->AddMaterial(pyrexGlass, 70.*perCent);
	G01->AddMaterial(PTP, 30.*perCent);
	//
	//type3 glass is just pyrex
	G4Material* G03 = pyrexGlass;
	//
	//type2 is glass plate
	//
	G4Material* G02 = man->FindOrBuildMaterial("G4_GLASS_PLATE");
	//
	//
	//----------Air-------------------
	//just fill in world
	//
	G4Material* air = man->FindOrBuildMaterial("G4_AIR");
	//
	//-----------Iron----------------
	//just Irons
	//
	G4Material* iron = man->FindOrBuildMaterial("G4_Fe");
	//
	//

	// ------------ Generate & Add Material Properties Table ------------
	//
	const G4int nEntries = 32;

	G4double PhotonEnergy[nEntries] =
	{ 2.000*eV, 2.068*eV, 2.103*eV, 2.139*eV,
		2.177*eV, 2.216*eV, 2.256*eV, 2.298*eV,
		2.341*eV, 2.386*eV, 2.433*eV, 2.481*eV,
		2.532*eV, 2.585*eV, 2.640*eV, 2.697*eV,
		2.757*eV, 2.820*eV, 2.885*eV, 2.954*eV,
		3.026*eV, 3.102*eV, 3.181*eV, 3.265*eV,
		3.353*eV, 3.446*eV, 3.545*eV, 3.649*eV,
		3.760*eV, 3.877*eV, 4.002*eV, 4.136*eV };


	//Air full fill in the world
	G4double AirRefractiveIndex[nEntries] =
	{ 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
		1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
		1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
		1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
		1.00, 1.00, 1.00, 1.00 };
	G4MaterialPropertiesTable* myMPT2 = new G4MaterialPropertiesTable();
	myMPT2->AddProperty("RINDEX", PhotonEnergy,AirRefractiveIndex, nEntries);
	air->SetMaterialPropertiesTable(myMPT2);

	//Glass type 1 using for core
	//
	//glass type 2 using for glass box
	G4double quartzRefractiveIndex[nEntries] =
	{ 1.25, 1.25, 1.25, 1.25, 1.25,
		1.25, 1.25, 1.25, 1.25, 1.25,
		1.25, 1.25, 1.25, 1.25, 1.25,
		1.25, 1.25, 1.25, 1.25, 1.25,
		1.25, 1.25, 1.25, 1.25, 1.25,
		1.25, 1.25, 1.25, 1.25, 1.25,
		1.25, 1.25};
	G4double quartzAbsorption[nEntries] =
	{3.448*m,  4.082*m,  6.329*m,  9.174*m, 12.346*m, 13.889*m,
		15.152*m, 17.241*m, 18.868*m, 20.000*m, 26.316*m, 35.714*m,
		45.455*m, 47.619*m, 52.632*m, 52.632*m, 55.556*m, 52.632*m,
		52.632*m, 47.619*m, 45.455*m, 41.667*m, 37.037*m, 33.333*m,
		30.000*m, 28.500*m, 27.000*m, 24.500*m, 22.000*m, 19.500*m,
		17.500*m, 14.500*m };
	G4MaterialPropertiesTable* quartzMPT = new G4MaterialPropertiesTable();
	quartzMPT->AddProperty("RINDEX",  PhotonEnergy, quartzRefractiveIndex,nEntries);
	quartzMPT->AddProperty("ABSLENGTH", PhotonEnergy, quartzAbsorption, nEntries);
	G02->SetMaterialPropertiesTable(quartzMPT);

	//glass type 3 using for cladding
	G4double quartz2RefractiveIndex[nEntries] =
	{ 1.35, 1.35, 1.35, 1.35, 1.35,
		1.35, 1.35, 1.35, 1.35, 1.35,
		1.35, 1.35, 1.35, 1.35, 1.35,
		1.35, 1.35, 1.35, 1.35, 1.35,
		1.35, 1.35, 1.35, 1.35, 1.35,
		1.35, 1.35, 1.35, 1.35, 1.35,
		1.35, 1.35};
	G4double quartz2Absorption[nEntries] =
	{3.448*m,  4.082*m,  6.329*m,  9.174*m, 12.346*m, 13.889*m,
		15.152*m, 17.241*m, 18.868*m, 20.000*m, 26.316*m, 35.714*m,
		45.455*m, 47.619*m, 52.632*m, 52.632*m, 55.556*m, 52.632*m,
		52.632*m, 47.619*m, 45.455*m, 41.667*m, 37.037*m, 33.333*m,
		30.000*m, 28.500*m, 27.000*m, 24.500*m, 22.000*m, 19.500*m,
		17.500*m, 14.500*m };
	G4MaterialPropertiesTable* quartz2MPT = new G4MaterialPropertiesTable();
	quartz2MPT->AddProperty("RINDEX",  PhotonEnergy, quartz2RefractiveIndex,nEntries);
	quartz2MPT->AddProperty("ABSLENGTH", PhotonEnergy, quartz2Absorption, nEntries);
	G03->SetMaterialPropertiesTable(quartz2MPT);

	//layers
	//
	const G4int NUM = 2;
	G4double Ephoton[NUM] = {2.0*eV, 4.136*eV};
	G4double reflectivity[NUM] = {1, 1};
	G4double efficiency[NUM] = {0.0, 0.0}; 
	G4MaterialPropertiesTable* WrapProperty = new G4MaterialPropertiesTable();
	WrapProperty->AddProperty("REFLECTIVITY",Ephoton,reflectivity,NUM);
	WrapProperty->AddProperty("EFFICIENCY",Ephoton,efficiency,NUM);




	//------------------------------- Volumes ---------------------------

	// The experimental Hall
	//
	G4Box* expHall_box = new G4Box("World",expHall_x,expHall_y,expHall_z);

	G4LogicalVolume* expHall_log
		= new G4LogicalVolume(expHall_box,air,"World",0,0,0);

	G4VPhysicalVolume* expHall_phys
		= new G4PVPlacement(0,G4ThreeVector(),expHall_log,"World",0,false,0);


	//----------------------main loop start------------------
	//Create repeated volumes
	//
	for (G4int copy = 0; copy < 19; copy ++)
	{
		//The glass box 
		//
		G4Box* glassBox = new G4Box("glassBox", 2.5*mm,100.*mm,100.*mm);
		G4LogicalVolume* glassBox_log
			= new G4LogicalVolume(glassBox, G02, "glassBox");

		//set the glass box color
		//
		G4VisAttributes* plateVis = new G4VisAttributes(G4Colour(0, 1.0, 1.0));
		plateVis->SetForceWireframe(true);
		glassBox_log->SetVisAttributes(plateVis);

		//the inter layer
		//
		G4Box* interLayer = new G4Box("ironLayer", 35.*mm, 100.*mm, 100.*mm);
		G4LogicalVolume* layer_log
			= new G4LogicalVolume(interLayer, iron, "ironLayer_log");
		//set inter layer color
		//
		G4VisAttributes* layerVis = new G4VisAttributes(G4Colour(1.0, 1.0, 0.1));
		//G4VisAttributes* layerVis_s = new G4VisAttributes(G4Colour(0.6, 0.6, 0.6));
		//layerVis_s->SetForceSolid(true);
		layerVis->SetForceWireframe(true);
		layer_log->SetVisAttributes(layerVis);
		//layer_log->SetVisAttributes(layerVis_s);

		//PMTSD construction
		//
		G4Box* sdBox = new G4Box("SD_Box", 2.5*mm, 100.*mm, 0*mm);
		G4LogicalVolume* sdBox_log = 
			new G4LogicalVolume(sdBox, G03, "SD_Box_log");
		G4SDManager* SDman = G4SDManager::GetSDMpointer();

		//PMTSD color 
		//
		G4VisAttributes* sdVis = new G4VisAttributes(G4Colour(1.0,0,0));
		sdVis->SetForceWireframe(true);
		sdBox_log->SetVisAttributes(sdVis);


		//The Glass Fiber
		//
		G4Tubs* fiber_core = new G4Tubs("glassFiber_core",0,0.6*mm,105.*mm,0,360);
		G4Tubs* fiber_clad = new G4Tubs("glassFiber_clad",0,1.*mm, 105.*mm,0,360);

		G4LogicalVolume* core_log
			= new G4LogicalVolume(fiber_core, G01, "glassFiber_core_log");

		G4LogicalVolume* clad_log
			= new G4LogicalVolume(fiber_clad, G03, "glassFiber_clad_log");

		G4VPhysicalVolume* fiber_phys
			= new G4PVPlacement(0,G4ThreeVector(),core_log,"fiber_phys",
					clad_log,false,0);


		//set glass fiber color
		//
		G4VisAttributes* fiberVis = new G4VisAttributes(G4Colour(1.0, 0.67, 1));
		fiberVis->SetForceAuxEdgeVisible(true);
		clad_log->SetVisAttributes(fiberVis);
		//

		G4RotationMatrix* rotX90 = new G4RotationMatrix();
		rotX90->rotateX(90*deg);
		//
		G4VPhysicalVolume* fiberPhys;
		G4VPhysicalVolume* fiberPhys2;
		//repeated structure of fibers
		//9 fibers in glass box
		//
		for (G4int index = 0; index < 5; index ++)
		{
			G4double loc_z = -100*mm + 20*mm + 40*mm*index;
			G4ThreeVector loc_fiber(1*mm, 0, loc_z*mm);
			fiberPhys  = new G4PVPlacement(rotX90, loc_fiber, 
					clad_log, "FiberInBox", glassBox_log, false, 0);
		}


		for (G4int index = 0; index < 4; index ++)
		{
			G4double loc_z = -100*mm + 40*mm * (index+1);
			G4ThreeVector loc_fiber(-1*mm,0,loc_z*mm);
			fiberPhys2 = new G4PVPlacement(rotX90, loc_fiber,clad_log, "FiberInBox2", glassBox_log, false,0);
		}

		//set physical variables
		G4VPhysicalVolume* layerPhys;
		G4VPhysicalVolume* sdPhys_up;
		G4VPhysicalVolume* sdPhys_down;
		G4VPhysicalVolume* interPhys;
		PMTSD* sd;
		//repeated struture of layers
		//10 layers connected together
		//
		// sd = new PMTSD("DetectorAwesome", 1);

		G4double loc_z = -500*mm + 70*mm * (copy);
		G4double loc_i = loc_z + 37.5*mm;
		//place of glass plate
		G4ThreeVector loc_fiber(loc_z*mm, 0, 0);
		//place of sd 
		G4ThreeVector loc_sd1(loc_z*mm, 105*mm, 0);
		G4ThreeVector loc_sd2(loc_z*mm, -105*mm,0);
		//place of inter layer
		G4ThreeVector loc_inter(loc_i*mm, 0, 0);
		//set glass plate
		layerPhys = new G4PVPlacement(0, loc_fiber, glassBox_log, "layers", expHall_log, false, 0);
		//set SD on glass plate layer
		char num[5];
		sprintf(num, "%d", copy+1);
		G4String st_num = num;
		G4String PMTSDname = "SD_Layer" + st_num;
		sd = new PMTSD(PMTSDname, copy+1);
		SDman -> AddNewDetector(sd);
		G4OpticalSurface* PMTsurface = new G4OpticalSurface("PMTsurface");
		sdPhys_up = new G4PVPlacement(rotX90, loc_sd1, sdBox_log, "sensitive_detector", expHall_log, false, 0);
		//sdBox_log->SetSensitiveDetector(sd);
		sdPhys_down = new G4PVPlacement(rotX90, loc_sd2, sdBox_log, "sensitive_detector", expHall_log, false, 0);
		//sdBox_log->SetSensitiveDetector(sd);
		core_log->SetSensitiveDetector(sd);
		// core_log->SetSensitiveDetector(sd);
		//G4LogicalBorderSurface* PMTwrap_up = new G4LogicalBorderSurface("PMTsurface", sdPhys_up, fiberPhys, PMTsurface);
		//G4LogicalBorderSurface* PMTwrap_down = new G4LogicalBorderSurface("PMTsurface", sdPhys_down, fiberPhys, PMTsurface);
		//PMTwrap_up->SetSensitiveDetector(sd);
		//PMTwrap_down->SetSensitiveDetector(sd);

		//set inter layer 
		interPhys = new G4PVPlacement(0, loc_inter, layer_log, "inters", expHall_log, false, 0);


		//------------------SurfaceAndSkinProperties-----------------
		//----------------------------------------------------------
		//surface properties for quartz - world
		G4OpticalSurface* Wrap = new G4OpticalSurface("Wrap");
		new G4LogicalBorderSurface("Wrap", layerPhys,expHall_phys,Wrap);
		Wrap->SetType(dielectric_metal);
		Wrap->SetFinish(polished);
		Wrap->SetModel(glisur);
		Wrap->SetMaterialPropertiesTable(WrapProperty);

		// surface properties for quartz - absorber
		G4OpticalSurface* Wrap2 = new G4OpticalSurface("Wrap2");
		new G4LogicalBorderSurface("Wrap2", layerPhys,interPhys,Wrap2);
		Wrap2->SetType(dielectric_metal);
		Wrap2->SetFinish(polished);
		Wrap2->SetModel(glisur);
		Wrap2->SetMaterialPropertiesTable(WrapProperty);
		//optical fibers
		G4OpticalSurface* Wrap3 = new G4OpticalSurface("Wrap3");
		new G4LogicalBorderSurface("Wrap3", fiber_phys, expHall_phys, Wrap3);
		Wrap3 -> SetType(dielectric_metal);
		Wrap3 -> SetFinish(polished);
		Wrap3 -> SetModel(glisur);
		Wrap3 -> SetMaterialPropertiesTable(WrapProperty);

		//optical fibers
		G4OpticalSurface* Wrap4 = new G4OpticalSurface("Wrap4");
		new G4LogicalBorderSurface("Wrap4", fiberPhys, expHall_phys, Wrap4);
		Wrap4 -> SetType(dielectric_metal);
		Wrap4 -> SetFinish(polished);
		Wrap4 -> SetModel(glisur);
		Wrap4 -> SetMaterialPropertiesTable(WrapProperty);

	}//#for

	return expHall_phys;
}
