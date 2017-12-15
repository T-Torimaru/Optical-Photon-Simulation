//$Id: ATSARunAction.cc 37 2012-09-08 08:44:04Z degerone $
//$Rev: 37 $

#include "ATSARunAction.hh"
#include "G4Run.hh"
#include "ATSAHistoManager.hh"
#include "ATSAEventAction2.hh"
#include "TROOT.h"
#include "TH1D.h"



ATSARunAction::ATSARunAction(ATSAHistoManager *histo)
  :histoManager(histo)
{}

ATSARunAction::~ATSARunAction()
{}

void ATSARunAction::BeginOfRunAction(const G4Run* aRun)
{
  G4cout << "THIS IS FROM RUNACTION" << G4endl;
  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
  histoManager->BookHisto();

  array1=0;
  single=0;
  array2=0;

}

void ATSARunAction::EndOfRunAction(const G4Run* aRun)
{


 

  histoManager->Save();

  G4cout<<"@@@@@@@@@@@@@@@@@ stopped @@@@@@@@@@@@@"<<G4endl;

  G4cout<<"stopped in single "<<single<<G4endl;
  G4cout<<"stopped in array1 "<<array1<<G4endl;
  G4cout<<"stopped in array2 "<<array2<<G4endl;


}

