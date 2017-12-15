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
//
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef OpNoviceRunAction_h
#define OpNoviceRunAction_h 1

#include "globals.hh"
#include "G4UserRunAction.hh"

// #include <TFile.h>
// #include <TTree.h>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class G4Timer;
class G4Run;
class OpNoviceEventAction;
class G4LogicalVolume;

class OpNoviceRunAction : public G4UserRunAction
{
  public:
    OpNoviceRunAction();
    virtual ~OpNoviceRunAction();

  public:
  //  virtual G4Run* GenerateRun();
  virtual void BeginOfRunAction(const G4Run*);// aRun);
  virtual void EndOfRunAction(const G4Run* );//aRun);

  // void Setid(Int_t aid) {id = aid;};
  // void SetPhotoEleN(Int_t aPhotoEleN) {PhotoEleN = aPhotoEleN;};
  // void SettriggerEne(Float_t atriggerEne) {triggerEne = atriggerEne;};
  // void SetMomM(Float_t amomX, Float_t amomY, Float_t amomZ) {
  //   momXM = amomX;
  //   momYM = amomY;
  //   momZM = amomZ;
  // };
  // void FillTree();
  // void ClearStatus() {
  //   fill_status = 0;
  //   id = -1;
  //   PhotoEleN = -1;
  //   triggerEne = -1;
  // };
  // void SetStatus(Int_t aStatus) {fill_status = aStatus;};
  // Int_t GetStatus() {return fill_status;};
  // Int_t fill_status;
  // TFile* ofile;
  // TTree* tree;
  // Int_t id;
  // Int_t PhotoEleN;
  // Float_t triggerEne;

  private:
  G4Timer* fTimer;
  OpNoviceEventAction* fEventAction;


};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif /*OpNoviceRunAction_h*/
