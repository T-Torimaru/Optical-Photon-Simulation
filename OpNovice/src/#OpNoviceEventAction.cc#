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
// $Id: B5EventAction.cc 76474 2013-11-11 10:36:34Z gcosmo $
//
/// \file B5EventAction.cc
/// \brief Implementation of the B5EventAction class

#include "OpNoviceEventAction.hh"
#include "OpNoviceScintHit.hh"

#include "OpNoviceAnalysis.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OpNoviceEventAction::OpNoviceEventAction()
: G4UserEventAction(), 
  fmppcID(-1)
  // fHHC1ID(-1),
  // fHHC2ID(-1),
  // fDHC1ID(-1),
  // fDHC2ID(-1),
  // fECHCID(-1),
  // fHCHCID(-1)
{
  fMPPCCollID = 0;
  // set printing per each event
  G4RunManager::GetRunManager()->SetPrintProgress(1);     
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OpNoviceEventAction::~OpNoviceEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void OpNoviceEventAction::BeginOfEventAction(const G4Event*)
{
  //    if (fHHC1ID==-1) {
    // if (fmppcID==-1) {
    //   G4SDManager* sdManager = G4SDManager::GetSDMpointer();
    //   fmppcID = sdManager->GetCollectionID("MPPCSD/mppcColl");
      // fHHC1ID = sdManager->GetCollectionID("hodoscope1/hodoscopeColl");
      // fHHC2ID = sdManager->GetCollectionID("hodoscope2/hodoscopeColl");
      // fDHC1ID = sdManager->GetCollectionID("chamber1/driftChamberColl");
      // fDHC2ID = sdManager->GetCollectionID("chamber2/driftChamberColl");
      // fECHCID = sdManager->GetCollectionID("EMcalorimeter/EMcalorimeterColl");
      // fHCHCID = sdManager->GetCollectionID("HadCalorimeter/HadCalorimeterColl");
  //    }
}     

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void OpNoviceEventAction::EndOfEventAction(const G4Event* event)
{
    if (fmppcID==-1) {
      G4SDManager* sdManager = G4SDManager::GetSDMpointer();
      //      G4String colName = "MPPCDS/mppcColl";
      G4String colName = "mppcColl";
      fMPPCCollID = sdManager->GetCollectionID(colName);
    }
    G4HCofThisEvent* hce = event->GetHCofThisEvent();
    if (!hce) 
    {
        G4ExceptionDescription msg;
        msg << "No hits collection of this event found.\n"; 
        G4Exception("OpNoviceEventAction::EndOfEventAction()",
                    "OpNoviceCode001", JustWarning, msg);
        return;
    }   


    //  OpNoviceScintHitsCollection* mppcHC = 0;

  // Get the hit collections
  //  if (HCE)
  //  {
    //     if (fMPPCCollID>=0)
      OpNoviceScintHitsCollection* mppcHC = (OpNoviceScintHitsCollection*)hce->GetHC(fMPPCCollID);
     if(!mppcHC) return;
     //  }

  // Get hit information about photons that reached the detector in this event
     //  if (mppcHC)
     //  {
    G4int n_hit = mppcHC->entries();
     // for(G4int idx=0;idx<n_hit;idx++){
     //   G4double n_time = (*mppcHC)[idx]->GetTime();
     //   G4cout << "photon arrived time : " << n_time << G4endl;
     // }            
     //     WLSPhotonDetHit* hit = (*mppcHC);
     //     G4int ID = hit->GetID();
    G4double pde = 0.25;
    G4int p_number = pde * n_hit;
     G4cout << "photon arrived : " << n_hit << G4endl;
     G4cout << "The number of Detection :" << p_number << G4endl;
     //  G4cout << "OK" << G4endl;
     //  }

    
    //
    // Fill histograms & ntuple
    // 
    
    // Get analysis manager
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
 
    // Fill histograms
 
    //  for(int i=0;i<mppcHC->entries();i++){
    //  G4double aaa=1000;
    //  G4double bbb=2000;
  //  analysisManager->FillH1(0,n_hit);
  analysisManager->FillNtupleDColumn(0,p_number);
  //  analysisManager->FillNtupleDColumn(0,aaa);
  //  analysisManager->FillNtupleDColumn(1,bbb);
  analysisManager->AddNtupleRow();
  //  }

// // //
//     // // Print    diagnostics
//     // 
    
//     G4int printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
//     if ( printModulo==0 || event->GetEventID() % printModulo != 0) return;
    
//     G4PrimaryParticle* primary = event->GetPrimaryVertex(0)->GetPrimary(0);
//     G4cout << G4endl
//            << ">>> Event " << event->GetEventID() << " >>> Simulation truth : "
//            << primary->GetG4code()->GetParticleName()
//            << " " << primary->GetMomentum() << G4endl;
    
//     // Hodoscope 1
//     n_hit = mppcHC->entries();
//     G4cout << "MPPC has " << n_hit << " hits." << G4endl;
//     for (G4int i=0;i<n_hit;i++)
//     {
//         OpNoviceScintHit* hit = (*mppcHC)[i];
//         hit->Print();
//     }

    // // Hodoscope 2
    // n_hit = hHC2->entries();
    // G4cout << "Hodoscope 2 has " << n_hit << " hits." << G4endl;
    // for (G4int i=0;i<n_hit;i++)
    // {
    //     OpNoviceHodoscopeHit* hit = (*hHC2)[i];
    //     hit->Print();
    // }

    // // Drift chamber 1
    // n_hit = dHC1->entries();
    // G4cout << "Drift Chamber 1 has " << n_hit << " hits." << G4endl;
    // for (G4int i2=0;i2<5;i2++)
    // {
    //     for (G4int i=0;i<n_hit;i++)
    //     {
    //         OpNoviceDriftChamberHit* hit = (*dHC1)[i];
    //         if (hit->GetLayerID()==i2) hit->Print();
    //     }
    // }

    // // Drift chamber 2
    // n_hit = dHC2->entries();
    // G4cout << "Drift Chamber 2 has " << n_hit << " hits." << G4endl;
    // for (G4int i2=0;i2<5;i2++)
    // {
    //     for (G4int i=0;i<n_hit;i++)
    //     {
    //         OpNoviceDriftChamberHit* hit = (*dHC2)[i];
    //         if (hit->GetLayerID()==i2) hit->Print();
    //     }
    // }

    // // EM calorimeter
    // G4cout << "EM Calorimeter has " << totalEmHit << " hits. Total Edep is "
    // << totalEmE/MeV << " (MeV)" << G4endl;

    // // Had calorimeter
    // G4cout << "Hadron Calorimeter has " << totalHadHit << " hits. Total Edep is "
    // << totalHadE/MeV << " (MeV)" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
