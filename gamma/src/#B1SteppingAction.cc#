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
// $Id: B1SteppingAction.cc 74483 2013-10-09 13:37:06Z gcosmo $
//
/// \file B1SteppingAction.cc
/// \brief Implementation of the B1SteppingAction class

#include "B1SteppingAction.hh"
#include "B1EventAction.hh"
#include "B1RunAction.hh"
#include "B1DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1SteppingAction::B1SteppingAction(B1EventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction),
  fScoringVolume(0)
{

   prevID = -1;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1SteppingAction::~B1SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1SteppingAction::UserSteppingAction(const G4Step* step)
{

  if (!fScoringVolume) { 
    const B1DetectorConstruction* detectorConstruction
          = static_cast<const B1DetectorConstruction*>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    fScoringVolume = detectorConstruction->GetScoringVolume();   
  }

  // get volume of the current step
  G4LogicalVolume* volume  = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
      
  // check if we are in scoring volume
  if (volume != fScoringVolume) return;

  // collect energy deposited in this step
  G4double edepStep = step->GetTotalEnergyDeposit();
  fEventAction->AddEdep(edepStep);  

  // Collect information of this step
  G4StepPoint* preStep  = step->GetPreStepPoint();
  G4StepPoint* postStep = step->GetPostStepPoint();
  G4ThreeVector pos_pre  = preStep->GetPosition();
  G4ThreeVector pos_post = postStep->GetPosition();
  G4double x_pre = pos_pre.x();
  G4double y_pre = pos_pre.y();
  G4double z_pre = pos_pre.z();
  G4double x_post = pos_post.x();
  G4double y_post = pos_post.y();
  Float_t z_post = pos_post.z();
  // G4double z_post = pos_post.z();
  G4Track* aTrack = step->GetTrack();
  G4int trackID = aTrack->GetTrackID();
  G4int parentID = aTrack->GetParentID();
  G4int particleID = aTrack->GetParticleDefinition()->GetPDGEncoding();
  G4String particleName = aTrack->GetParticleDefinition()->GetParticleName();
  G4ThreeVector momvec = aTrack->GetMomentum();
  G4double momX = momvec.x();
  G4double momY = momvec.y();
  G4double momZ = momvec.z();
  G4ThreeVector mom_pre = preStep->GetMomentum();
  G4double mom_preX = mom_pre.x();
  G4double mom_preY = mom_pre.y();
  G4double mom_preZ = mom_pre.z();
  G4ThreeVector mom_post = postStep->GetMomentum();
  G4double mom_postX = mom_post.x();
  G4double mom_postY = mom_post.y();
  G4double mom_postZ = mom_post.z();
  const G4VProcess* proc = postStep->GetProcessDefinedStep();
  G4String pname = "";
  if (proc) {
     pname = proc->GetProcessName();
  }
  const G4VProcess* creproc = aTrack->GetCreatorProcess();
  G4String cname = "";
  if (creproc) {
     cname = creproc->GetProcessName();
  }
  // if (trackID==1) {
  // if ((trackID==1 || parentID==1) && prevID != trackID) {
  // if (prevID != trackID) {
     // G4String name = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName();
     // printf("%d-%d: %s(%d) %s %s mom=(%.2f, %.2f, %.2f) (%.2f, %.2f, %.2f)->(%.2f, %.2f, %.2f) pos=(%.2f, %.2f, %.4f)->(%.2f, %.2f, %.4f) Edep=%.2eMeV %s\n", 
     //        trackID, parentID, particleName.data(), particleID, cname.data(), pname.data(), 
     //        momX/MeV, momY/MeV, momZ/MeV, mom_preX, mom_preY, mom_preZ, mom_postX, mom_postY, mom_postZ,
     //        x_pre, y_pre, z_pre, x_post, y_post, z_post, edepStep/MeV, name.data());
  // }
  prevID = trackID;

  if (trackID==1 && pname=="compt") {
     B1RunAction* runAction = (B1RunAction*)(G4RunManager::GetRunManager()->GetUserRunAction());
     runAction->SetIntr(2);
     runAction->SetStatus(runAction->GetStatus() + 8);
  }
  if (trackID==1 && pname=="conv") {
     B1RunAction* runAction = (B1RunAction*)(G4RunManager::GetRunManager()->GetUserRunAction());
     runAction->SetIntr(1);
     runAction->SetVtxZ(z_post);
     runAction->SetStatus(runAction->GetStatus() + 1);
  }
  if (parentID==1 && cname=="conv") {
     B1RunAction* runAction = (B1RunAction*)(G4RunManager::GetRunManager()->GetUserRunAction());
     if (particleID == 11 && (runAction->GetStatus() & 2) != 2) {
        runAction->SetMomM(mom_preX, mom_preY, mom_preZ);
        runAction->SetStatus(runAction->GetStatus() + 2);
     }
     if (particleID == -11 && (runAction->GetStatus() & 4) != 4) {
        runAction->SetMomP(mom_preX, mom_preY, mom_preZ);
        runAction->SetStatus(runAction->GetStatus() + 4);
     }
  }

  // if (trackID == 1) {
  //    B1RunAction* runAction = (B1RunAction*)(G4RunManager::GetRunManager()->GetUserRunAction());
  //    runAction->SetMomM(mom_postX, mom_postY, mom_postZ);
  //    runAction->SetStatus(runAction->GetStatus() + 2);
  // }

  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

