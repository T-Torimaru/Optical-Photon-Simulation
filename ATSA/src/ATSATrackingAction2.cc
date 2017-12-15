//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
//
// $Id: MuCoolTrackingAction.cc,v 1.4 2002/01/09 17:23:48 ranjard Exp $
// GEANT4 tag $Name: geant4-04-00-patch-02 $
//
// Modified: V.Daniel Elvira (6/23/02) - Kill secondary particles.
//                      
//   GEANT4 tracking action user class. Allows the user to perform actions
//   related with tracks.
//

#include "ATSATrackingAction2.hh"
#include "ATSAHistoManager.hh"
#include "G4TrackingManager.hh"
#include "G4Track.hh"
#include "G4TrackStatus.hh"
#include "ATSADetectorConstruction2.hh"


ATSATrackingAction2::ATSATrackingAction2(ATSAHistoManager* histo, ATSADetectorConstruction2* det)
  :histoManager(histo),detector(det)
{ }


ATSATrackingAction2:: ~ATSATrackingAction2(){}

void ATSATrackingAction2::PreUserTrackingAction(const G4Track* aTrack)
{
  // Create trajectories only for primary particles. In muon cooling studies,
  // the secondary particles are generally irrelevant. The interest is on 
  // the evolution of the muon beam (primary particles). Secondaries may only
  // be of interest when studying radiation effects on magnets or r.f.
  // cavities.


  G4int aircounter=0;

  if(aTrack->GetParentID()==1 && aTrack->GetDefinition()->GetParticleName()=="opticalphoton") // particle ID=0 means primary particle

    { 
      fpTrackingManager->SetStoreTrajectory(true);

      G4VPhysicalVolume *volume=aTrack->GetVolume();

      //  if(volume==detector->GetExpHall())aircounter++;

      G4ThreeVector pos=aTrack->GetPosition();
      G4double xpos1,xpos2;


      //  G4cout<< aTrack->GetCreatorProcess()->GetProcessName()<<G4endl;
      //      G4cout<<pos.x()<<" "<<pos.z()<<" "<<G4endl;

      if(x1)xpos1=pos.x();
      if(x2)xpos2=pos.x();
      if(x1 && x2){

	//	G4cout<<std::abs(xpos1-xpos2)<<G4endl;

      } 
      
      






    }
   
  else
     
    { 
      fpTrackingManager->SetStoreTrajectory(false);

    }


  // G4cout<<aircounter<<G4endl;
      
}
