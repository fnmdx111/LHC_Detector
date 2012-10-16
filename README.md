# LHC Detector with Optical Fiber Scintillator
contributors: Dr. Ugur Akgun, Qiuchen Xie


##Description
(this description is only for update before July 13)
This program is a geant4 simulation of the physical model of LHC detector. The geometry construction contains 9 glass palte, in which 9 optical scintillating fibers inserted, with iron matrial between them aborbing the beam energy and providing a energy difference among multiple layers of glass plate. When electron gun shots high energy electron beam through the glass plate, some photons, produced by Cherenkov radiation from the electron beam, will enter the core of optical fiber and create scintillation process due to the scintillation property of the fiber core. Consequently, the photons that produced by scintillator fiber, will be trapped inside the fiber, and sensitive detector will detect the photons from both the ends of the fibers. 

##Installation

Two complie methods are provided. Here I only introduce compile with CMakeList.txt: 

	$: mkdir build
	$: cd build
	$: cmake ..
	$: make

After compile complete, run:

	$: ./LHCdetector

to execute the program. 

*Geant4 and ROOT set up properly is required; Graphical model requires OpenGL. 

