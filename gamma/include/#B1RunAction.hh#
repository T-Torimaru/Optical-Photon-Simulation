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
// $Id: B1RunAction.hh 69565 2013-05-08 12:35:31Z gcosmo $
//
/// \file B1RunAction.hh
/// \brief Definition of the B1RunAction class

#ifndef B1RunAction_h
#define B1RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

#include <TFile.h>
#include <TTree.h>

class G4Run;
class G4LogicalVolume;

/// Run action class
///
/// In EndOfRunAction(), it calculates the dose in the selected volume 
/// from the energy deposit accumulated via stepping and event actions.
/// The computed dose is then printed on the screen.

class B1RunAction : public G4UserRunAction
{
  public:
    B1RunAction();
    virtual ~B1RunAction();

    virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);
   void SetIntr(Int_t aIntr) {intr = aIntr;};
   void SetVtxZ(Float_t aVtxZ) {vtxZ = aVtxZ;};
   void SetMomP(Float_t amomX, Float_t amomY, Float_t amomZ) {
      momXP = amomX;
      momYP = amomY;
      momZP = amomZ;
   };
   void SetMomM(Float_t amomX, Float_t amomY, Float_t amomZ) {
      momXM = amomX;
      momYM = amomY;
      momZM = amomZ;
   };
   void FillTree();
   void ClearStatus() {
      fill_status = 0;
      intr = -1;
      vtxZ = -1;
      momXP = -1;
      momYP = -1;
      momZP = -1;
      momXM = -1;
      momYM = -1;
      momZM = -1;
   };
   void SetStatus(Int_t aStatus) {fill_status = aStatus;};
   Int_t GetStatus() {return fill_status;};
   Float_t GetVtx () {
      return vtxZ;
   };

   Int_t fill_status;
   TFile* ofile;
   TTree* tree;
   Int_t intr;
   Float_t vtxZ;
   Float_t momXP, momYP, momZP;
   Float_t momXM, momYM, momZM;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

