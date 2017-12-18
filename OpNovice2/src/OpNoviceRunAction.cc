
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

// Make this appear first!
#include "G4Timer.hh"

#include "OpNoviceRunAction.hh"
// #include "OpNovicePrimaryGeneratorAction.hh"
// #include "OpNoviceDetectorConstruction.hh"
// #include "OpNoviceRun.hh"

// #include "G4RunManager.hh"
// #include "G4LogicalVolumeStore.hh"
//#include "G4LogicalVolume.hh"

#include "G4Run.hh"
#include "OpNoviceAnalysis.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OpNoviceRunAction::OpNoviceRunAction()
  : G4UserRunAction()//, fTimer(0)
{
  //  fTimer = new G4Timer;
  //  fRunMessenger = new WLSRunActionMessenger(this);
   G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  // //    analysisManager->SetNtupleMerging(true);
    analysisManager->SetVerboseLevel(1);
    analysisManager->SetFileName("old30mm25");

   analysisManager->CreateH1("test1","test1 of runaction",50,0.,50);
  //  analysisManager->CreateH1("test2","test2 of runaction",50,0.,50);

  //  if (fEventAction){
    analysisManager->CreateNtuple("photoele","Entry and Energy");
    analysisManager->CreateNtupleDColumn("NP"); // column ID = 
    //    analysisManager->CreateNtupleDColumn("TEnergy"); // column ID = 1
    // analysisManager->SetH1Title(0,"icepp");
    // analysisManager->SetH1XAxisTitle(0,"# p.e.");
    // analysisManager->SetH1YAxisTitle(0,"# hit");
    //    analysisManager->CreateNtupleDColumn("Test2"); // column ID = 1
    analysisManager->FinishNtuple();
    //  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OpNoviceRunAction::~OpNoviceRunAction()
{
  //  delete fTimer;
  //  delete fRunMessenger;
  delete G4AnalysisManager::Instance();

}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// G4Run* OpNoviceRunAction::GenerateRun()
// {
//   return new B1Run;
// }


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void OpNoviceRunAction::BeginOfRunAction(const G4Run* )//aRun)
{
  // G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
  // fTimer->Start();
   G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
   G4String fileName = "OpNovice";
   analysisManager->OpenFile();
  // G4RunManager::GetRunManager()->SetRandomNumberStore(false);
  // ofile = new TFile("test.root","RECREATE");
  // tree = new TTree("tree","tree");
  // tree->Branch("id", &id, "id/I");
  // tree->Branch("PhotoEleN", &PhotoEleN, "PhotoEle/I");
  // tree->Branch("triggerEne", &triggerEne, "triggerEne/F");
  //   G4cout << "okey" << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void OpNoviceRunAction::EndOfRunAction(const G4Run* )//aRun)
{
  // fTimer->Stop();
  // G4cout << "number of event = " << aRun->GetNumberOfEvent()
  //        << " " << *fTimer << G4endl;
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
  //  G4cout << "okey" << G4endl;


  // ofile->cd();
  // tree->Write();
  // ofile->Close();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

// void OpNoviceRunAction::FillTree()
// {
//   tree->Fill();
// }
