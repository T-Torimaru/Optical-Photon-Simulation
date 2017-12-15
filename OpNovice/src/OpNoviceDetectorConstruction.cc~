//////
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "OpNoviceDetectorConstruction.hh"

#include "G4ios.hh"
#include "globals.hh"
#include "G4SDManager.hh"
#include "G4SubtractionSolid.hh"
#include "G4Sphere.hh"
#include "G4VSensitiveDetector.hh"
#include "G4RunManager.hh"
#include "G4VisAttributes.hh"
#include "OpNoviceScintSD.hh"
#include "G4VSolid.hh"

#include "G4Material.hh"
#include "G4Element.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OpNoviceDetectorConstruction::OpNoviceDetectorConstruction()
  : G4VUserDetectorConstruction(),fVisAttributes(),Apd_log(0)
{
  // fExpHall_x = fExpHall_y = fExpHall_z = 10.0*m;
  // fTank_x    = fTank_y    = fTank_z    =  5.0*m;
  // fBubble_x  = fBubble_y  = fBubble_z  =  0.5*m
  fExpHall_x = fExpHall_y = 20*mm;
  fExpHall_z =  1*cm;
  fScinti_x  = fScinti_y               =  15.0*mm;
  fScinti_z                            =  1.50*mm;
  Rmax       = 4.5*mm;
  Rmin       = 0.0*mm;
  startPhi   = 0.*deg;
  endPhi     = 360*deg;
  startTheta = 0.*deg;
  endTheta   = 180*deg;
  center    = 4.8*mm;
  Ax = Ay = 0.65*mm;
  Az = 0.10*mm;
  Epo_x = Epo_y = 1.05*mm;
  Epo_z = 0.25*mm;
  z_epo = -3.55*mm;
  apd_z = 0.15*mm;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OpNoviceDetectorConstruction::~OpNoviceDetectorConstruction(){
    for (G4int i=0; i<G4int(fVisAttributes.size()); ++i) 
    {
      delete fVisAttributes[i];
    }  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* OpNoviceDetectorConstruction::Construct()
{

// ------------- Materials -------------

  G4double a, z, density;
  G4int nelements, natoms;

  G4Element* N  = new G4Element("Nitrogen" , "N", z=7 , a=14.01*g/mole);
  G4Element* O  = new G4Element("Oxygen"   , "O", z=8 , a=16.00*g/mole);
  G4Element* C  = new G4Element("Carbon"   , "C", z=6 , a=12.01*g/mole);
  G4Element* H  = new G4Element("Hydrogen" , "H", z=1 , a=1.01*g/mole);
  G4Element* Si = new G4Element("Silicon"   ,"Si", z=14, a=28.0855*g/mole);
  //  G4Element* Si = new G4Element("Silicon"   ,"Si", z=82, a=207.19*g/mole);

// Air
  G4Material* air = new G4Material("Air", density=1.29*mg/cm3, nelements=2);
  air->AddElement(N, 70.*perCent);
  air->AddElement(O, 30.*perCent);

// Scintillator
  G4Material* Sci = new G4Material("Scintillator", density= 1.032*g/cm3, nelements=2);
  Sci->AddElement(C, natoms=9);
  Sci->AddElement(H, natoms=10);

// Epoxy
  G4Material* epoxy = new G4Material("Epoxy", density= 1.85*g/cm3, nelements=3);
  epoxy->AddElement(C, natoms=18);
  epoxy->AddElement(H, natoms=20);
  epoxy->AddElement(O, natoms=2);

// Si
  G4Material* apd = new G4Material("Si", density= 2.3290*g/cm3, nelements=1);
  apd->AddElement(Si, natoms=1);

  // G4Material* apd = new G4Material("Si", density= 11.34*g/cm3, nelements=1);
  // apd->AddElement(Si, natoms=1);

//
// ------------ Generate & Add Material Properties Table ------------
//
  const G4int nEntries = 32;

  G4double photonwavelength[nEntries]={400.,403.75,407.5,411.25,
				       415.,418.75,422.5,426.25,
				       430.,433.75,437.5,441.25,
				       445.,448.75,452.5,456.25,
				       460.,463.75,467.5,471.25,
				       475.,478.75,482.5,486.25,
				       490.,493.75,497.5,501.25,
				       505.,508.75,512.5,516.25};
  G4double Amplitude_fast[nEntries]={0.07,0.09,0.17,0.22,
				     0.52,0.81,0.95,1.,
				     0.8,0.72,0.71,0.7,
				     0.68,0.63,0.5,0.42,
				     0.37,0.33,0.3,0.28,
				     0.23,0.21,0.19,0.18,
				     0.16,0.15,0.13,0.11,
				     0.1,0.09,0.08,0.07};
  G4double Amplitude_slow[nEntries]={1.,1.,1.,1.,1.,1.,1.,1.,
				     1.,1.,1.,1.,1.,1.,1.,1.,
			             1.,1.,1.,1.,1.,1.,1.,1.,
				     1.,1.,1.,1.,1.,1.,1.,1.};
  G4double photonenergy[nEntries];
  G4double Reflectivity_Si[nEntries];
  G4double Efficiency_Si[nEntries];
  G4double Epoxy_Refractive[nEntries];
  G4double Epoxy_Absorp_leng[nEntries];
  G4double Air_Refractive[nEntries];

  G4double h_planck=6.62606e-34*joule*s;//4.136*eV*s;
  G4double c=3e8*m/s;
  G4double e=1.6021765e-19*joule/eV;

  for(G4int j=0;j<nEntries;j++){
    photonenergy[nEntries-1-j]=(((h_planck*c/(photonwavelength[j]*1e-9))/e)*1e3)*eV;
  }
  //

  //EJ-212 refractive index: fixed at 1.58 (no wavelength dependent)
  //from the Home Page of the ELJEN
  G4double Scinti_Refractive[nEntries];

  //EJ-212 absorption length: fixed at 80cm (no wavelength dependent)
  //from the thesis of Ms. Ieki
  G4double Scinti_Absorp_leng[nEntries];

  //if FAST/SLOW COMPONENTS are not defined, gammas are not generated! (to be understood)
  //from a paper in Ohio
  const  G4int FastSlow = 4;
  G4double FastSlowE[FastSlow]={2.*eV,2.87*eV,2.9*eV,3.47*eV};
  G4double ScintiFast[FastSlow] = {1.,1.,1.,1.};
  G4double ScintiSlow[FastSlow]= {0.,0.,1.,1.};

  for(G4int i=0;i<nEntries;i++){

    Reflectivity_Si[i] = 0.;
    Efficiency_Si[i] = 1.;
    Scinti_Refractive[i] = 1.58; //from ELJEN
    Epoxy_Refractive[i] = 1.55; //from hamamatsu
    Air_Refractive[i] = 1.;
    Scinti_Absorp_leng[i] = 80*cm;
//    Epoxy_Absorp_leng[i] = 70*cm; //arbitrary
    Epoxy_Absorp_leng[i] = 220*cm; //Angela
  }

  //Properties Table for EJ212

  G4MaterialPropertiesTable* EJ212_table = new G4MaterialPropertiesTable();

  EJ212_table->AddProperty("RINDEX", photonenergy, Scinti_Refractive, nEntries);
  EJ212_table->AddProperty("ABSLENGTH", photonenergy, Scinti_Absorp_leng, nEntries);
//  EJ212_table->AddProperty("FASTCOMPONENT", FastSlowE, ScintiFast, FastSlow);
//  EJ212_table->AddProperty("SLOWCOMPONENT", FastSlowE, ScintiSlow, FastSlow);
  EJ212_table->AddProperty("FASTCOMPONENT", photonenergy, Amplitude_fast, nEntries);
  EJ212_table->AddProperty("SLOWCOMPONENT", photonenergy, Amplitude_slow, nEntries);

  G4double LY = 10000./MeV;

  EJ212_table->AddConstProperty("SCINTILLATIONYIELD",LY); //from ELJEN

  EJ212_table->AddConstProperty("RESOLUTIONSCALE",1.);
  EJ212_table->AddConstProperty("FASTTIMECONSTANT", 2.7*ns);
  EJ212_table->AddConstProperty("SLOWTIMECONSTANT",2.7*ns);
  EJ212_table->AddConstProperty("YIELDRATIO",1.);
  Sci->GetIonisation()->SetBirksConstant(0.126*mm/MeV); //constant?
  
  Sci->SetMaterialPropertiesTable(EJ212_table);

  //Properties Table for Air

  G4MaterialPropertiesTable* air_table = new G4MaterialPropertiesTable();

  air_table->AddProperty("RINDEX", photonenergy, Air_Refractive, nEntries);
  
  air->SetMaterialPropertiesTable(air_table);

  //Properties Table for Epoxy

  G4MaterialPropertiesTable* Epo_table = new G4MaterialPropertiesTable();

  Epo_table->AddProperty("RINDEX", photonenergy, Epoxy_Refractive, nEntries);
  Epo_table->AddProperty("ABSLENGTH", photonenergy, Epoxy_Absorp_leng, nEntries);   
  //  Epo_table->AddConstProperty("YIELDRATIO",1.);
  epoxy->SetMaterialPropertiesTable(Epo_table);

  //Properties Table for Silicon

  G4MaterialPropertiesTable* Silicon_table = new G4MaterialPropertiesTable();
  
  Silicon_table->AddProperty("REFLECTIVITY", photonenergy, Reflectivity_Si, nEntries);
  Silicon_table->AddProperty("EFFICIENCY", photonenergy,Efficiency_Si, nEntries);

  apd->SetMaterialPropertiesTable(Silicon_table);


//
// ------------- Volumes --------------

// The experimental Hall
//
  G4VSolid* expHall_box = new G4Box("World",fExpHall_x,fExpHall_y,fExpHall_z);

  G4LogicalVolume* expHall_log
    = new G4LogicalVolume(expHall_box,air,"World_logical");

  G4VPhysicalVolume* expHall_phys
    = new G4PVPlacement(0,G4ThreeVector(),expHall_log,"World",0,false,0);

// The Scintillator
//
  G4VSolid* Scinti_box = new G4Box("Tile",fScinti_x,fScinti_y,fScinti_z);

  G4LogicalVolume* Scinti_log
    = new G4LogicalVolume(Scinti_box,Sci,"Tile_logical");

  G4VPhysicalVolume* Scinti_phys
    = new G4PVPlacement(0,G4ThreeVector(),Scinti_log,"Tile",
			expHall_log,true,0);

// The Sphere
//
  G4Sphere* sphere = new G4Sphere("Sphere",Rmin,Rmax,
				  startPhi,endPhi,startTheta,endTheta);

  G4LogicalVolume* sphere_log
    = new G4LogicalVolume(sphere,air,"Sphere_logical");

  G4VPhysicalVolume* sphere_phys
    = new G4PVPlacement(0,G4ThreeVector(0,0,center),
			sphere_log,"Sphere",expHall_log,true,0);

  
// The Tile Design
//
  G4SubtractionSolid* subtraction 
    = new G4SubtractionSolid("Scintillator-sphere",Scinti_box,sphere);

//Epoxy
//
  G4VSolid* epoxy_box = new G4Box("Epo",Epo_x,Epo_y,Epo_z);

  G4LogicalVolume* Epoxy_log
    = new G4LogicalVolume(epoxy_box,epoxy,"Epo_logical");

  G4VPhysicalVolume* Epoxy_phys
    = new G4PVPlacement(0,G4ThreeVector(0,0,z_epo),Epoxy_log,"Epo",
  			sphere_log,true,0);
  

// APD
//
  G4VSolid* Apd_box = new G4Box("Apd",Ax,Ay,Az);

  //  G4LogicalVolume* Apd_log
  //    = new G4LogicalVolume(Apd_box,apd,"apd_logical",0,0,0);
  Apd_log
    = new G4LogicalVolume(Apd_box,apd,"apd_logical");

  G4VPhysicalVolume* Apd_phys
    = new G4PVPlacement(0,G4ThreeVector(0,0,apd_z),Apd_log,"Apd",
  			Epoxy_log,false,0);

  // G4double fMPPCPolish = 1.;

  // G4OpticalSurface* photonDetSurface = new G4OpticalSurface("APDSurface",
  //                                                      glisur,
  //                                                      ground,
  //                                                      dielectric_metal,
  //                                                      fMPPCPolish);
 
  // G4double p_mppc[2] = {2.00*eV, 3.47*eV};
  // G4double refl_mppc[2] = {fMPPCReflectivity,fMPPCReflectivity};
  // G4double effi_mppc[2] = {1, 1};

  // G4MaterialPropertiesTable* photonDetSurfaceProperty =
  //                                              new G4MaterialPropertiesTable(); 
  // photonDetSurfaceProperty -> AddProperty("REFLECTIVITY",p_mppc,refl_mppc,2);
  // photonDetSurfaceProperty -> AddProperty("EFFICIENCY",p_mppc,effi_mppc,2);

  // photonDetSurface -> SetMaterialPropertiesTable(photonDetSurfaceProperty);

  // new G4LogicalSkinSurface("APDSurface",Apd_log,photonDetSurface); 

// ------------- Surfaces --------------
  
  const G4int num = 2;
  const G4int num2 = 7;
  G4double ephoton[num] = {2.034*eV, 4.136*eV};
  G4double ephoton2[num2] = {2.48*eV, 2.59*eV, 2.70*eV, 2.82*eV, 2.95*eV, 3.11*eV, 3.27*eV};
  G4double refractiveIndex[num] = {1., 1.};
  G4double specularLobe[num]    = {0.9, 0.9};
  G4double specularSpike[num]   = {0., 0.};
  G4double backScatter[num]     = {0., 0.};
  G4double diffuseLobe[num]     = {0.1, 0.1};
  G4double reflectivity1[num]    = {0.95, 0.95};
  G4double reflectivity2[num]    = {1.,1.};  
  G4double reflectivity3[num]    = {0.,0.};  
  G4double efficiency[num]      = {0., 0.};
//  G4double efficiency2[num2] = {0.454, 0.473, 0.485, 0.473, 0.454, 0.419, 0.377};
  G4double efficiency2[num2] = {1., 1., 1., 1., 1., 1., 1.};
  G4double sigma_alpha = 0.1;

  //Scintillator -> Air (-> Reflector)
  //
  G4OpticalSurface* ScintToAir = new G4OpticalSurface("SciSurface1");
  G4LogicalBorderSurface* sciSurface1 =
    new G4LogicalBorderSurface("SciSurface1",Scinti_phys,expHall_phys,ScintToAir);
    
  ScintToAir->SetType(dielectric_dielectric);
  ScintToAir->SetFinish(polishedbackpainted);
  ScintToAir->SetModel(unified);
  ScintToAir->SetSigmaAlpha(sigma_alpha);
  
  G4MaterialPropertiesTable* myST1 = new G4MaterialPropertiesTable();

  myST1->AddProperty("RINDEX",                ephoton, refractiveIndex, num);
  myST1->AddProperty("SPECULARLOBECONSTANT",  ephoton, specularLobe,    num);
  myST1->AddProperty("SPECULARSPIKECONSTANT", ephoton, specularSpike,   num);
  myST1->AddProperty("BACKSCATTERCONSTANT",   ephoton, backScatter,     num);
  myST1->AddProperty("DIFFUSELOBE",           ephoton, diffuseLobe,     num);
  myST1->AddProperty("REFLECTIVITY",          ephoton, reflectivity1,   num);
  myST1->AddProperty("EFFICIENCY",            ephoton, efficiency,      num);

  ScintToAir->SetMaterialPropertiesTable(myST1);

//  //(Reflector) Air -> Scintillator
//  //
//  G4OpticalSurface* AirToScint = new G4OpticalSurface("SciSurface2");
//  G4LogicalBorderSurface* sciSurface2 =
//    new G4LogicalBorderSurface("SciSurface2", expHall_phys, Scinti_phys, AirToScint);
//  
//  AirToScint->SetType(dielectric_dielectric);
//  //  AirToScint->SetFinish(polishedbackpainted);
//  AirToScint->SetFinish(polished);
//  AirToScint->SetModel(unified);
//  //  AirToScint->SetSigmaAlpha(sigma_alpha);


  //Scintillator -> Sphere (Air)
  //
  G4OpticalSurface* ScintToSphere = new G4OpticalSurface("SciSurface3");
  G4LogicalBorderSurface* sciSurface3 =
    new G4LogicalBorderSurface("SciSurface3", Scinti_phys, sphere_phys, ScintToSphere);
  
  ScintToSphere->SetType(dielectric_dielectric);
  ScintToSphere->SetFinish(ground);
  // ScintToSphere->SetModel(unified);
  // ScintToSphere->SetSigmaAlpha(sigma_alpha);

  // G4MaterialPropertiesTable* myST3 = new G4MaterialPropertiesTable();

  // myST3->AddProperty("REFLECTIVITY",          ephoton, reflectivity2,   num);
  // myST3->AddProperty("EFFICIENCY",            ephoton, efficiency,      num);

  // ScintToSphere->SetMaterialPropertiesTable(myST3);

  // //Sphere (Air) -> Scintillator
  // //
  // G4OpticalSurface* SphereToScint = new G4OpticalSurface("SciSurface4");
  // G4LogicalBorderSurface* sciSurface4 =
  //   new G4LogicalBorderSurface("SciSurface4", sphere_phys, Scinti_phys, SphereToScint);
  
  // SphereToScint->SetType(dielectric_dielectric);
  // SphereToScint->SetFinish(polished);
  // SphereToScint->SetModel(unified);

  // G4MaterialPropertiesTable* myST4 = new G4MaterialPropertiesTable();

  // myST4->AddProperty("REFLECTIVITY",          ephoton, reflectivity2,   num);
  // myST4->AddProperty("EFFICIENCY",            ephoton, efficiency,      num);

  // ScintToSphere->SetMaterialPropertiesTable(myST4);

  // //Sphere (Air) -> Epoxy
  // //
  // G4OpticalSurface* SphereToEpoxy = new G4OpticalSurface("EpoSurface");
  // G4LogicalBorderSurface* epoSurface =
  //   new G4LogicalBorderSurface("EpoSurface", sphere_phys, Epoxy_phys, SphereToEpoxy);
  
  // SphereToEpoxy->SetType(dielectric_dielectric);
  // SphereToEpoxy->SetFinish(polished);
  // SphereToEpoxy->SetModel(glisur);
  // SphereToEpoxy->SetPolish(1);

  // G4MaterialPropertiesTable* myST5 = new G4MaterialPropertiesTable();

  // myST5->AddProperty("REFLECTIVITY",          ephoton, reflectivity2,   num);
  // myST5->AddProperty("EFFICIENCY",            ephoton, efficiency,      num);

  // SphereToEpoxy->SetMaterialPropertiesTable(myST5);

  //Epoxy -> Sphere (Air)
  //
  G4OpticalSurface* EpoxyToSphere = new G4OpticalSurface("SphereSurface");
  G4LogicalSkinSurface* sphereSurface =
    new G4LogicalSkinSurface("SphereSurface", Epoxy_log, EpoxyToSphere);
  
  EpoxyToSphere->SetType(dielectric_dielectric);
  EpoxyToSphere->SetFinish(polished);
  EpoxyToSphere->SetModel(unified);
  EpoxyToSphere->SetSigmaAlpha(sigma_alpha);
  //  EpoxyToSphere->SetPolish(1);

  // G4MaterialPropertiesTable* myST6 = new G4MaterialPropertiesTable();

  // myST6->AddProperty("REFLECTIVITY",          ephoton, reflectivity2,   num);
  // myST6->AddProperty("EFFICIENCY",            ephoton, efficiency,      num);

  // EpoxyToSphere->SetMaterialPropertiesTable(myST6);

  //Epoxy -> APD
  //
  G4OpticalSurface* EpoxyToApd = new G4OpticalSurface("ApdSurface");
  G4LogicalBorderSurface* apdSurface =
    new G4LogicalBorderSurface("ApdSurface", Epoxy_phys, Apd_phys, EpoxyToApd);
 
  EpoxyToApd->SetType(dielectric_metal);
  EpoxyToApd->SetFinish(polishedlumirrorair);
  EpoxyToApd->SetModel(LUT);
  

  G4MaterialPropertiesTable* myST7 = new G4MaterialPropertiesTable();

  myST7->AddProperty("REFLECTIVITY",          ephoton, reflectivity3,   num);
  myST7->AddProperty("EFFICIENCY",           ephoton2,   efficiency2,   num);

  EpoxyToApd->SetMaterialPropertiesTable(myST7);

  // //Sphere -> Air
  // //
  // G4OpticalSurface* SphereToAir = new G4OpticalSurface("SpheSurface");
  // G4LogicalBorderSurface* SpheSurface =
  //   new G4LogicalBorderSurface("SpheSurface", sphere_phys, expHall_phys, SphereToAir);
 
  // SphereToAir->SetType(dielectric_dielectric);
  // //  SphereToAir->SetFinish(polishedlumirrorair);
  // SphereToAir->SetModel(glisur);
  // SphereToAir->SetPolish(1);

  // G4MaterialPropertiesTable* myST8 = new G4MaterialPropertiesTable();

  // myST8->AddProperty("REFLECTIVITY",          ephoton, reflectivity3,   num);
  // myST8->AddProperty("EFFICIENCY",           ephoton,   efficiency,   num2);

  // SphereToAir->SetMaterialPropertiesTable(myST8);

    
//---------- visualization attributes ---------------------------------
    
    G4VisAttributes* visAttributes = new G4VisAttributes(G4Colour(1,0,0));
    visAttributes->SetVisibility(false);
    expHall_log->SetVisAttributes(visAttributes);
    fVisAttributes.push_back(visAttributes);
    
    visAttributes = new G4VisAttributes(G4Colour(0,1,1));
    Scinti_log->SetVisAttributes(visAttributes);
    fVisAttributes.push_back(visAttributes);
    
    visAttributes = new G4VisAttributes(G4Colour(0,0,0));
    sphere_log->SetVisAttributes(visAttributes);
    fVisAttributes.push_back(visAttributes);

    visAttributes = new G4VisAttributes(G4Colour(0,1,0));
    Epoxy_log->SetVisAttributes(visAttributes);
    fVisAttributes.push_back(visAttributes);

    visAttributes = new G4VisAttributes(G4Colour(1,1,0));
    Apd_log->SetVisAttributes(visAttributes);
    fVisAttributes.push_back(visAttributes);

//always return the physical World
  return expHall_phys;
}

void OpNoviceDetectorConstruction::ConstructSDandField()
{

  // if (!fmppcSD.Get()) {
  //    G4String mppcSDName = "WLS/Apd";
  //   //     G4String mppcSDName = "/PhotonDetHitCollection";
  //    WLSPhotonDetSD* mppcSD = new WLSPhotonDetSD(mppcSDName);
  //    fmppcSD.Put(mppcSD);
  // }
  // SetSensitiveDetector("apd_logical", fmppcSD.Get(), true);
  
    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    G4String SDname;
    
    G4VSensitiveDetector* MPPCDS
      = new OpNoviceScintSD(SDname="/MPPCDS");
    SDman->AddNewDetector(MPPCDS);
    Apd_log->SetSensitiveDetector(MPPCDS);
  
  
    // G4SDManager* SDman = G4SDManager::GetSDMpointer();
    // G4String SDname;
    
    // G4VSensitiveDetector* MPPCDS
    //   = new OpNoviceScintSD(SDname="/MPPCDS");
    // SDman->AddNewDetector(MPPCDS);
    // SetSensitiveDetector("apd_logical",MPPCDS);
  
}

// // ------------- Materials -------------

//   G4double a, z, density;
//   G4int nelements;

// // Air
// //
//   G4Element* N = new G4Element("Nitrogen", "N", z=7 , a=14.01*g/mole);
//   G4Element* O = new G4Element("Oxygen"  , "O", z=8 , a=16.00*g/mole);

//   G4Material* air = new G4Material("Air", density=1.29*mg/cm3, nelements=2);
//   air->AddElement(N, 70.*perCent);
//   air->AddElement(O, 30.*perCent);

// // Water
// //
//   G4Element* H = new G4Element("Hydrogen", "H", z=1 , a=1.01*g/mole);

//   G4Material* water = new G4Material("Water", density= 1.0*g/cm3, nelements=2);
//   water->AddElement(H, 2);
//   water->AddElement(O, 1);

// //
// // ------------ Generate & Add Material Properties Table ------------
// //
//   const G4int nEntries = 32;

//   G4double photonEnergy[nEntries] =
//             { 2.034*eV, 2.068*eV, 2.103*eV, 2.139*eV,
//               2.177*eV, 2.216*eV, 2.256*eV, 2.298*eV,
//               2.341*eV, 2.386*eV, 2.433*eV, 2.481*eV,
//               2.532*eV, 2.585*eV, 2.640*eV, 2.697*eV,
//               2.757*eV, 2.820*eV, 2.885*eV, 2.954*eV,
//               3.026*eV, 3.102*eV, 3.181*eV, 3.265*eV,
//               3.353*eV, 3.446*eV, 3.545*eV, 3.649*eV,
//               3.760*eV, 3.877*eV, 4.002*eV, 4.136*eV };
// //
// // Water
// //
//   G4double refractiveIndex1[nEntries] =
//             { 1.3435, 1.344,  1.3445, 1.345,  1.3455,
//               1.346,  1.3465, 1.347,  1.3475, 1.348,
//               1.3485, 1.3492, 1.35,   1.3505, 1.351,
//               1.3518, 1.3522, 1.3530, 1.3535, 1.354,
//               1.3545, 1.355,  1.3555, 1.356,  1.3568,
//               1.3572, 1.358,  1.3585, 1.359,  1.3595,
//               1.36,   1.3608};

//   G4double absorption[nEntries] =
//            {3.448*m,  4.082*m,  6.329*m,  9.174*m, 12.346*m, 13.889*m,
//            15.152*m, 17.241*m, 18.868*m, 20.000*m, 26.316*m, 35.714*m,
//            45.455*m, 47.619*m, 52.632*m, 52.632*m, 55.556*m, 52.632*m,
//            52.632*m, 47.619*m, 45.455*m, 41.667*m, 37.037*m, 33.333*m,
//            30.000*m, 28.500*m, 27.000*m, 24.500*m, 22.000*m, 19.500*m,
//            17.500*m, 14.500*m };

//   G4double scintilFast[nEntries] =
//             { 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
//               1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
//               1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
//               1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
//               1.00, 1.00, 1.00, 1.00 };
//   G4double scintilSlow[nEntries] =
//             { 0.01, 1.00, 2.00, 3.00, 4.00, 5.00, 6.00,
//               7.00, 8.00, 9.00, 8.00, 7.00, 6.00, 4.00,
//               3.00, 2.00, 1.00, 0.01, 1.00, 2.00, 3.00,
//               4.00, 5.00, 6.00, 7.00, 8.00, 9.00, 8.00,
//               7.00, 6.00, 5.00, 4.00 };

//   G4MaterialPropertiesTable* myMPT1 = new G4MaterialPropertiesTable();

//   myMPT1->AddProperty("RINDEX",       photonEnergy, refractiveIndex1,nEntries)
//         ->SetSpline(true);
//   myMPT1->AddProperty("ABSLENGTH",    photonEnergy, absorption,     nEntries)
//         ->SetSpline(true);
//   myMPT1->AddProperty("FASTCOMPONENT",photonEnergy, scintilFast,     nEntries)
//         ->SetSpline(true);
//   myMPT1->AddProperty("SLOWCOMPONENT",photonEnergy, scintilSlow,     nEntries)
//         ->SetSpline(true);

//   myMPT1->AddConstProperty("SCINTILLATIONYIELD",50./MeV);
//   myMPT1->AddConstProperty("RESOLUTIONSCALE",1.0);
//   myMPT1->AddConstProperty("FASTTIMECONSTANT", 1.*ns);
//   myMPT1->AddConstProperty("SLOWTIMECONSTANT",10.*ns);
//   myMPT1->AddConstProperty("YIELDRATIO",0.8);

//   const G4int numentries_water = 60;

//   G4double energy_water[numentries_water] = {
//      1.56962*eV, 1.58974*eV, 1.61039*eV, 1.63157*eV,
//      1.65333*eV, 1.67567*eV, 1.69863*eV, 1.72222*eV,
//      1.74647*eV, 1.77142*eV, 1.7971 *eV, 1.82352*eV,
//      1.85074*eV, 1.87878*eV, 1.90769*eV, 1.93749*eV,
//      1.96825*eV, 1.99999*eV, 2.03278*eV, 2.06666*eV,
//      2.10169*eV, 2.13793*eV, 2.17543*eV, 2.21428*eV,
//      2.25454*eV, 2.29629*eV, 2.33962*eV, 2.38461*eV,
//      2.43137*eV, 2.47999*eV, 2.53061*eV, 2.58333*eV,
//      2.63829*eV, 2.69565*eV, 2.75555*eV, 2.81817*eV,
//      2.88371*eV, 2.95237*eV, 3.02438*eV, 3.09999*eV,
//      3.17948*eV, 3.26315*eV, 3.35134*eV, 3.44444*eV,
//      3.54285*eV, 3.64705*eV, 3.75757*eV, 3.87499*eV,
//      3.99999*eV, 4.13332*eV, 4.27585*eV, 4.42856*eV,
//      4.59258*eV, 4.76922*eV, 4.95999*eV, 5.16665*eV,
//      5.39129*eV, 5.63635*eV, 5.90475*eV, 6.19998*eV
//   };

//   //assume 100 times larger than the rayleigh scattering for now.
//   G4double mie_water[numentries_water] = {
//      167024.4*m, 158726.7*m, 150742  *m,
//      143062.5*m, 135680.2*m, 128587.4*m,
//      121776.3*m, 115239.5*m, 108969.5*m,
//      102958.8*m, 97200.35*m, 91686.86*m,
//      86411.33*m, 81366.79*m, 76546.42*m,
//      71943.46*m, 67551.29*m, 63363.36*m,
//      59373.25*m, 55574.61*m, 51961.24*m,
//      48527.00*m, 45265.87*m, 42171.94*m,
//      39239.39*m, 36462.50*m, 33835.68*m,
//      31353.41*m, 29010.30*m, 26801.03*m,
//      24720.42*m, 22763.36*m, 20924.88*m,
//      19200.07*m, 17584.16*m, 16072.45*m,
//      14660.38*m, 13343.46*m, 12117.33*m,
//      10977.70*m, 9920.416*m, 8941.407*m,
//      8036.711*m, 7202.470*m, 6434.927*m,
//      5730.429*m, 5085.425*m, 4496.467*m,
//      3960.210*m, 3473.413*m, 3032.937*m,
//      2635.746*m, 2278.907*m, 1959.588*m,
//      1675.064*m, 1422.710*m, 1200.004*m,
//      1004.528*m, 833.9666*m, 686.1063*m
//   };

//   // gforward, gbackward, forward backward ratio
//   G4double mie_water_const[3]={0.99,0.99,0.8};

//   myMPT1->AddProperty("MIEHG",energy_water,mie_water,numentries_water)
//         ->SetSpline(true);
//   myMPT1->AddConstProperty("MIEHG_FORWARD",mie_water_const[0]);
//   myMPT1->AddConstProperty("MIEHG_BACKWARD",mie_water_const[1]);
//   myMPT1->AddConstProperty("MIEHG_FORWARD_RATIO",mie_water_const[2]);

//   water->SetMaterialPropertiesTable(myMPT1);

//   // Set the Birks Constant for the Water scintillator

//   water->GetIonisation()->SetBirksConstant(0.126*mm/MeV);

// //
// // Air
// //
//   G4double refractiveIndex2[nEntries] =
//             { 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
//               1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
//               1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
//               1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
//               1.00, 1.00, 1.00, 1.00 };

//   G4MaterialPropertiesTable* myMPT2 = new G4MaterialPropertiesTable();
//   myMPT2->AddProperty("RINDEX", photonEnergy, refractiveIndex2, nEntries);

//   air->SetMaterialPropertiesTable(myMPT2);

// //
// // ------------- Volumes --------------

// // The experimental Hall
// //
//   G4Box* expHall_box = new G4Box("World",fExpHall_x,fExpHall_y,fExpHall_z);

//   G4LogicalVolume* expHall_log
//     = new G4LogicalVolume(expHall_box,air,"World",0,0,0);

//   G4VPhysicalVolume* expHall_phys
//     = new G4PVPlacement(0,G4ThreeVector(),expHall_log,"World",0,false,0);

// // The Water Tank
// //
//   G4Box* waterTank_box = new G4Box("Tank",fTank_x,fTank_y,fTank_z);

//   G4LogicalVolume* waterTank_log
//     = new G4LogicalVolume(waterTank_box,water,"Tank",0,0,0);

//   G4VPhysicalVolume* waterTank_phys
//     = new G4PVPlacement(0,G4ThreeVector(),waterTank_log,"Tank",
//                         expHall_log,false,0);

// // The Air Bubble
// //
//   G4Box* bubbleAir_box = new G4Box("Bubble",fBubble_x,fBubble_y,fBubble_z);

//   G4LogicalVolume* bubbleAir_log
//     = new G4LogicalVolume(bubbleAir_box,air,"Bubble",0,0,0);

// //G4VPhysicalVolume* bubbleAir_phys =
//       new G4PVPlacement(0,G4ThreeVector(0,2.5*m,0),bubbleAir_log,"Bubble",
//                         waterTank_log,false,0);

// // ------------- Surfaces --------------
// //
// // Water Tank
// //
//   G4OpticalSurface* opWaterSurface = new G4OpticalSurface("WaterSurface");
//   opWaterSurface->SetType(dielectric_dielectric);
//   opWaterSurface->SetFinish(ground);
//   opWaterSurface->SetModel(unified);

//   new G4LogicalBorderSurface("WaterSurface",
//                                  waterTank_phys,expHall_phys,opWaterSurface);

// // Air Bubble
// //
//   G4OpticalSurface* opAirSurface = new G4OpticalSurface("AirSurface");
//   opAirSurface->SetType(dielectric_dielectric);
//   opAirSurface->SetFinish(polished);
//   opAirSurface->SetModel(glisur);

//   G4LogicalSkinSurface* airSurface =
//           new G4LogicalSkinSurface("AirSurface", bubbleAir_log, opAirSurface);

//   G4OpticalSurface* opticalSurface = dynamic_cast <G4OpticalSurface*>
//         (airSurface->GetSurface(bubbleAir_log)->GetSurfaceProperty());

//   if (opticalSurface) opticalSurface->DumpInfo();

// //
// // Generate & Add Material Properties Table attached to the optical surfaces
// //
//   const G4int num = 2;
//   G4double ephoton[num] = {2.034*eV, 4.136*eV};

//   //OpticalWaterSurface
//   G4double refractiveIndex[num] = {1.35, 1.40};
//   G4double specularLobe[num]    = {0.3, 0.3};
//   G4double specularSpike[num]   = {0.2, 0.2};
//   G4double backScatter[num]     = {0.2, 0.2};

//   G4MaterialPropertiesTable* myST1 = new G4MaterialPropertiesTable();

//   myST1->AddProperty("RINDEX",                ephoton, refractiveIndex, num);
//   myST1->AddProperty("SPECULARLOBECONSTANT",  ephoton, specularLobe,    num);
//   myST1->AddProperty("SPECULARSPIKECONSTANT", ephoton, specularSpike,   num);
//   myST1->AddProperty("BACKSCATTERCONSTANT",   ephoton, backScatter,     num);

//   opWaterSurface->SetMaterialPropertiesTable(myST1);

//   //OpticalAirSurface
//   G4double reflectivity[num] = {0.3, 0.5};
//   G4double efficiency[num]   = {0.8, 1.0};

//   G4MaterialPropertiesTable *myST2 = new G4MaterialPropertiesTable();

//   myST2->AddProperty("REFLECTIVITY", ephoton, reflectivity, num);
//   myST2->AddProperty("EFFICIENCY",   ephoton, efficiency,   num);

//   opAirSurface->SetMaterialPropertiesTable(myST2);

// //always return the physical World
//   return expHall_phys;
// }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
