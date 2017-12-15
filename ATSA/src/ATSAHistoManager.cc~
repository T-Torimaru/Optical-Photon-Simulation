//$Id: ATSAHistoManager.cc 150 2013-01-22 15:06:08Z ripiccini $
//$Rev: 150 $

#include "ATSAHistoManager.hh"
#include "G4UnitsTable.hh"
#include "TH1D.h"
#include "TString.h"
#include "TH2D.h"
#include "TFile.h"
#include "TTree.h"
#include "ATSAEventAction2.hh"
#include "TObjArray.h"

ATSAHistoManager::ATSAHistoManager(int f, int sf, bool dep)
  :rootFile(0),select(f),selectfiber(sf),deposit(dep)
{
  


  for (G4int k=0; k<MaxTree; k++) ntupledep[k] = 0;
  for (G4int k=0; k<MaxTree; k++) ntuplepos[k] = 0;
  for (G4int k=0; k<MaxTree; k++) ntuplemom[k] = 0;
  



}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ATSAHistoManager::~ATSAHistoManager()
{
  if (rootFile) delete rootFile;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ATSAHistoManager::BookHisto()
{ 

 
  //  G4cout<<select<<"  <--------- "<<G4endl;

  TString conf;

  if(deposit)conf="deposit";
  if(!deposit)conf="nodeposit";


  G4double fibdim=(G4double)selectfiber/2000.;
  G4String fileName;


  fileName = Form("plot%d_double.root",select,selectfiber,conf.Data());



  rootFile = new TFile(fileName, "RECREATE");



  if(!rootFile) 
    {
      G4cout << " HistoManager::book :" 
	     << " problem creating the ROOT TFile "
	     << G4endl;
      return;
    }
  
  // G4cout << "PORCACCIO" << G4endl;




    ntupledep[0]= new TTree("FiberTree","Single Fiber");   
   
    ntupledep[0]->Branch("EdepFib1",&Energy1);
    ntupledep[0]->Branch("EdepFib2",&Energy2);
    ntupledep[0]->Branch("EdepFib",&Energy);
    ntupledep[0]->Branch("EdepFib1_pos",&Energy1_pos);
    ntupledep[0]->Branch("EdepFib2_pos",&Energy2_pos);
    ntupledep[0]->Branch("EdepFib_pos",&Energy_pos);
    ntupledep[0]->Branch("EdepFib1_muon",&Energy1_muon);
    ntupledep[0]->Branch("EdepFib2_muon",&Energy2_muon);
    ntupledep[0]->Branch("EdepFib_muon",&Energy_muon);
    ntupledep[0]->Branch("EdepFibBirks_muon",&EnergyBirks_muon);
    ntupledep[0]->Branch("EdgeCounter1",&EdgeCounter1);
    ntupledep[0]->Branch("EdgeCounter2",&EdgeCounter2);
    ntupledep[0]->Branch("EdgeCounter",&EdgeCounter);
    ntupledep[0]->Branch("WhiteFiberCounter",&EdgeCounter_wf);
    ntupledep[0]->Branch("totphotonsipm",&totphotonsipm);
    ntupledep[0]->Branch("totphotonsipm_pde",&totphotonsipm_pde);
    ntupledep[0]->Branch("EdgeCounter1_muon",&EdgeCounter1_muon);
    ntupledep[0]->Branch("EdgeCounter2_muon",&EdgeCounter2_muon);
    ntupledep[0]->Branch("EdgeCounter_muon",&EdgeCounter_muon);
    ntupledep[0]->Branch("PhotonCounter",&PhotonCounter);
    ntupledep[0]->Branch("PhotonCounter1",&PhotonCounter1);
    ntupledep[0]->Branch("PhotonCounter2",&PhotonCounter2);
    ntupledep[0]->Branch("PhotonCounter_muon",&PhotonCounter_muon);
    ntupledep[0]->Branch("PhotonCounter1_muon",&PhotonCounter1_muon);
    ntupledep[0]->Branch("PhotonCounter2_muon",&PhotonCounter2_muon);
    ntupledep[0]->Branch("SiPMCounter",&SiPMCounter);
    ntupledep[0]->Branch("SiPMWinCounter",&SiPMWinCounter);
    ntupledep[0]->Branch("AirCounter",&AirCounter);
    ntupledep[0]->Branch("EnergyScintillator",&EnergyScintillator);
    ntupledep[0]->Branch("tracklength",&tracklength);
    ntupledep[0]->Branch("tracklength1",&tracklength1);
    ntupledep[0]->Branch("tracklength2",&tracklength2);
    ntupledep[0]->Branch("tracklength_pos",&tracklength_pos);
    ntupledep[0]->Branch("tracklength1_pos",&tracklength1_pos);
    ntupledep[0]->Branch("tracklength2_pos",&tracklength2_pos);
    ntupledep[0]->Branch("tracklength_muon",&tracklength_muon);
    ntupledep[0]->Branch("tracklength1_muon",&tracklength1_muon);
    ntupledep[0]->Branch("tracklength2_muon",&tracklength2_muon);
    ntupledep[0]->Branch("BetaEnergy",&BetaEnergy);
    ntupledep[0]->Branch("PositronEnergy",&PositronEnergy);
    ntupledep[0]->Branch("InitialTheta",&InitialTheta);
    ntupledep[0]->Branch("ZStop",&ZStop);
    ntupledep[0]->Branch("InitialMomentum_pos",&InitialMomentum_pos);
    ntupledep[0]->Branch("InitialMomentum_muon",&InitialMomentum_muon);
    ntupledep[0]->Branch("InitialPhi",&InitialPhi);
    ntupledep[0]->Branch("FinalTheta",&FinalTheta);
    ntupledep[0]->Branch("FinalPhi",&FinalPhi);
    ntupledep[0]->Branch("Nph",&Nph);
    ntupledep[0]->Branch("Nph_muon",&Nph_muon);
    ntupledep[0]->Branch("PosY_sipm",y,"PosY_sipm[Nph]/D");
    ntupledep[0]->Branch("PosZ_sipm",z,"PosZ_sipm[Nph]/D");
    ntupledep[0]->Branch("PosTime_sipm",t,"PosTime_sipm[Nph]/D");
    ntupledep[0]->Branch("DeltaLength_sipm",delta_l,"DeltaLength_sipm[Nph]/D");
    ntupledep[0]->Branch("DeltaTime_sipm",delta_t,"DeltaTime_sipm[Nph]/D");
    ntupledep[0]->Branch("PosYmuon_sipm",y_muon,"PosYmuon_sipm[Nph_muon]/D");
    ntupledep[0]->Branch("PosZmuon_sipm",z_muon,"PosZmuon_sipm[Nph_muon]/D");
    ntupledep[0]->Branch("PosTimemuon_sipm",tph_muon,"PosTimemuon_sipm[Nph_muon]/D");
    ntupledep[0]->Branch("DeltaLengthmuon_sipm",deltamuon_l,"DeltaLengthmuon_sipm[Nph_muon]/D");
    ntupledep[0]->Branch("DeltaTimemuon_sipm",deltamuon_t,"DeltaTimemuon_sipm[Nph_muon]/D");
    ntupledep[0]->Branch("Nph_1",&Nph_1);
    ntupledep[0]->Branch("Nph1_muon",&Nph1_muon);
    ntupledep[0]->Branch("PosY_sipm_1",y_1,"PosY_sipm_1[Nph_1]/D");
    ntupledep[0]->Branch("PosZ_sipm_1",z_1,"PosZ_sipm_1[Nph_1]/D");
    ntupledep[0]->Branch("PosTime_sipm_1",t_1,"PosTime_sipm_1[Nph_1]/D");
    ntupledep[0]->Branch("DeltaLength1_sipm",delta1_l,"DeltaLength1_sipm[Nph_1]/D");
    ntupledep[0]->Branch("DeltaTime1_sipm",delta1_t,"DeltaTime1_sipm[Nph_1]/D");
    ntupledep[0]->Branch("PosYmuon_sipm_1",y1_muon,"PosYmuon_sipm_1[Nph1_muon]/D");
    ntupledep[0]->Branch("PosZmuon_sipm_1",z1_muon,"PosZmuon_sipm_1[Nph1_muon]/D");
    ntupledep[0]->Branch("DeltaLength1muon_sipm",delta1muon_l,"DeltaLength1muon_sipm[Nph1_muon]/D");
    ntupledep[0]->Branch("DeltaTime1muon_sipm",delta1muon_t,"DeltaTime1muon_sipm[Nph1_muon]/D");
    ntupledep[0]->Branch("PosTimemuon_sipm_1",tph1_muon,"PosTimemuon_sipm_1[Nph1_muon]/D");
    ntupledep[0]->Branch("eventnumber",eventnumber); 
   
  
}


void ATSAHistoManager::Save()
{ 
  //#ifdef G4ANALYSIS_USE
    if (rootFile) {
    
      //    histo[0]->Write(); 
      // for(G4int i=0;i<MaxTree;i++)ntupledep[i]->Write(); 
      rootFile->Write();       // Writing the histograms to the file
      rootFile->Close();        // and closing the tree (and the file)
      G4cout << "\n----> Histogram Tree is saved \n" << G4endl;
    }
    //#endif
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



void ATSAHistoManager::FillNtuple(G4int k)
{
  
  
  if (ntupledep[k]){
    
  
   ntupledep[k]->Fill();  
    
    
  }
  
}





//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......




