//
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
// $Id: B1DetectorConstruction.cc 75117 2013-10-28 09:38:37Z gcosmo $
//
/// \file B1DetectorConstruction.cc
/// \brief Implementation of the B1DetectorConstruction class

#include "B1DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::B1DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::~B1DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B1DetectorConstruction::Construct()
{  
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  
  // Envelope parameters
  //
  G4double env_sizeXY = 20*cm, env_sizeZ = 20*cm;
   
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //     
  // World
  //
  G4double world_sizeXY = 1.2*env_sizeXY;
  G4double world_sizeZ  = 1.2*env_sizeZ;
  G4Box* solidWorld = new G4Box("World", 0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);   
  G4Material* vacuum = new G4Material("Vacuum",	1, 1.008*g/mole, 1.e-25*g/cm3, kStateGas, 2.73*kelvin, 1.e-25*g/cm3);
  G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, vacuum, "World");
  G4VisAttributes *worldVis = new G4VisAttributes(true, G4Colour(0.5, 0.5, 0.5));
  worldVis->SetForceWireframe(true);
  logicWorld->SetVisAttributes(worldVis);
  G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "World", 0, false, 0, checkOverlaps);
                     

  // 
  // Sheet
  //
  G4Box *sheet_solid = new G4Box("Sheet", 10*cm/2, 10*cm/2, 1*mm/2);
  // G4Material* sheet_mat = new G4Material("Pb", 11.34 * g / cm3, 1);
  // G4Element *Pb = G4NistManager::Instance()->FindOrBuildElement("Pb");
  // sheet_mat->AddElement(Pb, 1);
  // G4Material* sheet_mat = new G4Material("NaI", 3.67 *g/cm3, 2);
  // G4Element *Na = G4NistManager::Instance()->FindOrBuildElement("Na");
  // G4Element *I  = G4NistManager::Instance()->FindOrBuildElement("I");
  // sheet_mat-> AddElement(Na, 1);
  // sheet_mat-> AddElement(I,  1);  
  // G4Material* sheet_mat = nist->FindOrBuildMaterial("G4_BGO");
  G4Material* sheet_mat = nist->FindOrBuildMaterial("G4_POLYSTYRENE");
  G4LogicalVolume *sheet_log = new G4LogicalVolume(sheet_solid, sheet_mat, "Sheet");
  G4VisAttributes *sheetVis = new G4VisAttributes(true, G4Colour(0, 0.8, 0.8));
  sheetVis->SetForceWireframe(true);
  sheet_log->SetVisAttributes(sheetVis);
  new G4PVPlacement(0, G4ThreeVector(0, 0, 0*mm), sheet_log, "Sheet", logicWorld, false, 0);
  for (G4int ilayer=0; ilayer<100; ilayer++) {
     new G4PVPlacement(0, G4ThreeVector(0, 0, ilayer*1*mm), sheet_log, "Sheet", logicWorld, false, ilayer);
  }
 
  fScoringVolume = sheet_log;

  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
