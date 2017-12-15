//$Id: ATSAHistoManager.hh 110 2013-01-08 11:17:30Z ripiccini $
//$Rev: 110 $

#include "globals.hh"
#include "TString.h"

class TFile;
class TTree;
class TH1D;
class TH2D;

const G4int MaxHisto = 180;
const G4int MaxTree = 180;

class ATSAHistoManager
{
public:
  
  ATSAHistoManager(int,int,bool);
  ~ATSAHistoManager();
  
  void BookHisto();
  void Save();  
  void FillNtuple(G4int id);
 
  void SetEventNumber(G4int n){eventnumber=n;}
  void SetEnergyScint1_positron(G4double Edep){EnergyScint1_positron=Edep;}
  void SetEnergyScint2_positron(G4double Edep){EnergyScint2_positron=Edep;}
  void SetEnergyScint3_positron(G4double Edep){EnergyScint3_positron=Edep;}
  void SetEnergyScint4_positron(G4double Edep){EnergyScint4_positron=Edep;}

  void SetStoppedPosition_x(G4double pos) {PosStopped_x=pos;}
  void SetStoppedPosition_y(G4double pos) {PosStopped_y=pos;}
  void SetStoppedPosition_z(G4double pos) {PosStopped_z=pos;}
  void SetEnergyScint1_electron(G4double Edep){EnergyScint1_electron=Edep;}
  void SetEnergyScint2_electron(G4double Edep){EnergyScint2_electron=Edep;}
  void SetEnergyScint3_electron(G4double Edep){EnergyScint3_electron=Edep;}
  void SetEnergyScint4_electron(G4double Edep){EnergyScint4_electron=Edep;}
  void SetEnergyScint1_gamma(G4double Edep){EnergyScint1_gamma=Edep;}
  void SetEnergyScint2_gamma(G4double Edep){EnergyScint2_gamma=Edep;}
  void SetEnergyScint3_gamma(G4double Edep){EnergyScint3_gamma=Edep;}
  void SetEnergyScint4_gamma(G4double Edep){EnergyScint4_gamma=Edep;}
  void SetEnergyScint1_muon(G4double Edep){EnergyScint1_muon=Edep;}
  void SetEnergyScint2_muon(G4double Edep){EnergyScint2_muon=Edep;}
  void SetEnergyScint3_muon(G4double Edep){EnergyScint3_muon=Edep;}
  void SetEnergyScint4_muon(G4double Edep){EnergyScint4_muon=Edep;}
  void SetEnergyScint1(G4double Edep){EnergyScint1=Edep;}
  void SetEnergyScint2(G4double Edep){EnergyScint2=Edep;}
  void SetEnergyScint3(G4double Edep){EnergyScint3=Edep;}
  void SetEnergyScint4(G4double Edep){EnergyScint4=Edep;}


  void SetEnergy_0(G4double Edep){Energy_0=Edep;}
  void SetEnergy_1(G4double Edep){Energy_1=Edep;}
  void SetEnergy_2(G4double Edep){Energy_2=Edep;}
  void SetEnergy_3(G4double Edep){Energy_3=Edep;}
  void SetEnergy_4(G4double Edep){Energy_4=Edep;}
  void SetEnergy_5(G4double Edep){Energy_5=Edep;}
  void SetEnergy_6(G4double Edep){Energy_6=Edep;}
  void SetEnergy_7(G4double Edep){Energy_7=Edep;}


  void SetEnergy_0_muon(G4double Edep){Energy_0_muon=Edep;}
  void SetEnergy_1_muon(G4double Edep){Energy_1_muon=Edep;}
  void SetEnergy_2_muon(G4double Edep){Energy_2_muon=Edep;}
  void SetEnergy_3_muon(G4double Edep){Energy_3_muon=Edep;}
  void SetEnergy_4_muon(G4double Edep){Energy_4_muon=Edep;}
  void SetEnergy_5_muon(G4double Edep){Energy_5_muon=Edep;}
  void SetEnergy_6_muon(G4double Edep){Energy_6_muon=Edep;}
  void SetEnergy_7_muon(G4double Edep){Energy_7_muon=Edep;}

  void SetEnergy_0_positron(G4double Edep){Energy_0_positron=Edep;}
  void SetEnergy_1_positron(G4double Edep){Energy_1_positron=Edep;}
  void SetEnergy_2_positron(G4double Edep){Energy_2_positron=Edep;}
  void SetEnergy_3_positron(G4double Edep){Energy_3_positron=Edep;}
  void SetEnergy_4_positron(G4double Edep){Energy_4_positron=Edep;}
  void SetEnergy_5_positron(G4double Edep){Energy_5_positron=Edep;}
  void SetEnergy_6_positron(G4double Edep){Energy_6_positron=Edep;}
  void SetEnergy_7_positron(G4double Edep){Energy_7_positron=Edep;}


  void SetStopped_muon_0(bool flag){stopped_muon_0=flag;}
  void SetStopped_muon_1(bool flag){stopped_muon_1=flag;}
  void SetStopped_muon_2(bool flag){stopped_muon_2=flag;}
  void SetStopped_muon_3(bool flag){stopped_muon_3=flag;}
  void SetStopped_muon_4(bool flag){stopped_muon_4=flag;}
  void SetStopped_muon_5(bool flag){stopped_muon_5=flag;}
  void SetStopped_muon_6(bool flag){stopped_muon_6=flag;}
  void SetStopped_muon_7(bool flag){stopped_muon_7=flag;}


  void SetFromATAR(bool flag){FromATAR=flag;}
  void SetFromAl1(bool flag){FromAl1=flag;}
  void SetFromAl2(bool flag){FromAl2=flag;}
  void SetFromExpHall(bool flag){FromExpHall=flag;}
  void SetFromColl(bool flag){FromColl=flag;}
  void SetFromScint1(bool flag){FromScint1=flag;}
  void SetFromScint2(bool flag){FromScint2=flag;}
  void SetFromScint3(bool flag){FromScint3=flag;}
  void SetFromScint4(bool flag){FromScint4=flag;}
  void SetFromScintShield(bool flag){FromScintShield=flag;}
  void SetFromFrame(bool flag){FromFrame=flag;}
  void SetElectronFromExpHall(bool flag){ElectronFromExpHall=flag;}
  void SetElectronFromColl(bool flag){ElectronFromColl=flag;}
 
  //void PrintStatistic();
  
  //single fiber

  void SetEnergy(G4double Edep){Energy=Edep;}
  void SetEnergy1(G4double Edep){Energy1=Edep;}
  void SetEnergy2(G4double Edep){Energy2=Edep;}
  void SetEnergy_pos(G4double Edep){Energy_pos=Edep;}
  void SetEnergy1_pos(G4double Edep){Energy1_pos=Edep;}
  void SetEnergy2_pos(G4double Edep){Energy2_pos=Edep;}
  void SetEnergy_muon(G4double Edep){Energy_muon=Edep;}
  void SetEnergyBirks_muon(G4double Edep){EnergyBirks_muon=Edep;}
  void SetEnergy1_muon(G4double Edep){Energy1_muon=Edep;}
  void SetEnergy2_muon(G4double Edep){Energy2_muon=Edep;}
  void SetEnergyScintillator(G4double Edep){EnergyScintillator=Edep;}
  void SetTotPhotonSipm(G4int count){totphotonsipm=count;}
  void SetTotPhotonSipm_pde(G4int count){totphotonsipm_pde=count;}
  void SetEdgeCounter_wf(G4int count){EdgeCounter_wf=count;}
  void SetEdgeCounter(G4int count){EdgeCounter=count;}
  void SetEdgeCounter1(G4int count){EdgeCounter1=count;}
  void SetEdgeCounter2(G4int count){EdgeCounter2=count;}
  void SetEdgeCounter_muon(G4int count){EdgeCounter_muon=count;}
  void SetEdgeCounter1_muon(G4int count){EdgeCounter1_muon=count;}
  void SetEdgeCounter2_muon(G4int count){EdgeCounter2_muon=count;}
  void SetPhotonCounter(G4int count){PhotonCounter=count;}
  void SetPhotonCounter1(G4int count){PhotonCounter1=count;}
  void SetPhotonCounter2(G4int count){PhotonCounter2=count;}
  void SetPhotonCounter_muon(G4int count){PhotonCounter_muon=count;}
  void SetPhotonCounter1_muon(G4int count){PhotonCounter1_muon=count;}
  void SetPhotonCounter2_muon(G4int count){PhotonCounter2_muon=count;}
  void SetSiPMCounter(G4int count){SiPMCounter=count;}
  void SetSiPMWinCounter(G4int count){SiPMWinCounter=count;}
  void SetAirCounter(G4int count){AirCounter=count;}
  void SetTrackLength(G4double l){tracklength=l;}
  void SetTrackLength1(G4double l){tracklength1=l;}
  void SetTrackLength2(G4double l){tracklength2=l;}
  void SetTrackLength_muon(G4double l){tracklength_muon=l;}
  void SetTrackLength1_muon(G4double l){tracklength1_muon=l;}
  void SetTrackLength2_muon(G4double l){tracklength2_muon=l;}
  void SetTrackLength_pos(G4double l){tracklength_pos=l;}
  void SetTrackLength1_pos(G4double l){tracklength1_pos=l;}
  void SetTrackLength2_pos(G4double l){tracklength2_pos=l;}
  void SetBetaEnergy(G4double E){BetaEnergy=E;}
  void SetPositronEnergy(G4double E){PositronEnergy=E;}
  void SetInitialTheta(G4double theta){InitialTheta=theta;}
  void SetZStop_muon(G4double z){ZStop=z;}
  void SetInitialMomentum_pos(G4double mom){InitialMomentum_pos=mom;}
  void SetInitialMomentum_muon(G4double mom){InitialMomentum_muon=mom;}
  void SetInitialPhi(G4double phi){InitialPhi=phi;}
  void SetFinalTheta(G4double theta){FinalTheta=theta;}
  void SetFinalPhi(G4double phi){FinalPhi=phi;}
  void SetPosY_1(G4double ypos, G4int i){y_1[i]=ypos;}
  void SetPosZ_1(G4double zpos, G4int i){z_1[i]=zpos;}
  void SetTime_1(G4double tpos, G4int i){t_1[i]=tpos;}
  void SetDeltaTime1(G4double tpos,G4int i){delta1_t[i]=tpos;}
  void SetDeltaLength1(G4double lpos,G4int i){delta1_l[i]=lpos;}
  void SetPosY_muon_1(G4double ypos, G4int i){y1_muon[i]=ypos;}
  void SetPosZ_muon_1(G4double zpos, G4int i){z1_muon[i]=zpos;}
  void SetTime_muon_1(G4double tpos, G4int i){tph1_muon[i]=tpos;}
  void SetDeltaTime1_muon(G4double tpos,G4int i){delta1muon_t[i]=tpos;}
  void SetDeltaLength1_muon(G4double lpos,G4int i){delta1muon_l[i]=lpos;}
  void SetNph_1(G4int n){Nph_1=n;}
  void SetNph_muon_1(G4int n){Nph1_muon=n;}
  void SetPosY(G4double ypos, G4int i){y[i]=ypos;}
  void SetPosZ(G4double zpos, G4int i){z[i]=zpos;}
  void SetTime(G4double tpos, G4int i){t[i]=tpos;}
  void SetDeltaTime(G4double tpos,G4int i){delta_t[i]=tpos;}
  void SetDeltaLength(G4double lpos,G4int i){delta_l[i]=lpos;}
  void SetPosY_muon(G4double ypos, G4int i){y_muon[i]=ypos;}
  void SetPosZ_muon(G4double zpos, G4int i){z_muon[i]=zpos;}
  void SetTime_muon(G4double tpos, G4int i){tph_muon[i]=tpos;}
  void SetDeltaTime_muon(G4double tpos,G4int i){deltamuon_t[i]=tpos;}
  void SetDeltaLength_muon(G4double lpos,G4int i){deltamuon_l[i]=lpos;}
  void SetNph(G4int n){Nph=n;}
  void SetNph_muon(G4int n){Nph_muon=n;}

private:
  
  int select,selectfiber;
  bool deposit;
  TString colmaterial,detector_choose;
  TFile*   rootFile;
  TH1D*    histo[MaxHisto]; //MaxHisto must be optimized   
  TH2D*    histo2[MaxHisto]; //MaxHisto must be optimized
  TTree*   ntupledep[MaxTree];    
  TTree*   ntuplepos[MaxTree];    
  TTree*   ntuplemom[MaxTree]; 
 
  
  
  G4double EnergyScint1_positron;
  G4double EnergyScint2_positron;
  G4double EnergyScint3_positron;
  G4double EnergyScint4_positron;

  G4double PosStopped_x;
  G4double PosStopped_y;
  G4double PosStopped_z;
  G4int eventnumber;
  bool stopped_muon_0;
  bool stopped_muon_1;
  bool stopped_muon_2;
  bool stopped_muon_3;
  bool stopped_muon_4;
  bool stopped_muon_5;
  bool stopped_muon_6;
  bool stopped_muon_7;
  bool FromATAR;
  bool FromAl1;
  bool FromAl2;
  bool FromColl;
  bool FromExpHall;
  bool FromScint1;
  bool FromScint2;
  bool FromScint3;
  bool FromScint4;
  bool FromScintShield;
  bool FromFrame;
  bool ElectronFromColl;
  bool ElectronFromExpHall;  

  G4double EnergyScint1_electron;
  G4double EnergyScint2_electron;
  G4double EnergyScint3_electron;
  G4double EnergyScint4_electron;
  
  G4double EnergyScint1_gamma;
  G4double EnergyScint2_gamma;
  G4double EnergyScint3_gamma;
  G4double EnergyScint4_gamma;
  
  G4double EnergyScint1_muon;
  G4double EnergyScint2_muon;
  G4double EnergyScint3_muon;
  G4double EnergyScint4_muon;
  
  G4double EnergyScint1;
  G4double EnergyScint2;
  G4double EnergyScint3;
  G4double EnergyScint4;


 
  G4double Energy_0;
  G4double Energy_1;
  G4double Energy_2;
  G4double Energy_3;
  G4double Energy_4;
  G4double Energy_5;
  G4double Energy_6;
  G4double Energy_7;
  
  
  G4double Energy_0_muon;
  G4double Energy_1_muon;
  G4double Energy_2_muon;
  G4double Energy_3_muon;
  G4double Energy_4_muon;
  G4double Energy_5_muon;
  G4double Energy_6_muon;
  G4double Energy_7_muon;
  
  G4double Energy_0_positron;
  G4double Energy_1_positron;
  G4double Energy_2_positron;
  G4double Energy_3_positron;
  G4double Energy_4_positron;
  G4double Energy_5_positron;
  G4double Energy_6_positron;
  G4double Energy_7_positron;


  //single fiber

  G4double Energy;
  G4double Energy1;
  G4double Energy2;
  G4double Energy_pos;
  G4double Energy1_pos;
  G4double Energy2_pos;
  G4double Energy_muon;
  G4double EnergyBirks_muon;
  G4double Energy1_muon;
  G4double Energy2_muon;
  G4int EdgeCounter1;
  G4int EdgeCounter2;
  G4int EdgeCounter;
  G4int EdgeCounter_wf;
  G4int totphotonsipm;
  G4int totphotonsipm_pde;
  G4int EdgeCounter1_muon;
  G4int EdgeCounter2_muon;
  G4int EdgeCounter_muon;
  G4int SiPMCounter;
  G4int SiPMWinCounter;
  G4int PhotonCounter;
  G4int PhotonCounter1;
  G4int PhotonCounter2;
  G4int PhotonCounter_muon;
  G4int PhotonCounter1_muon;
  G4int PhotonCounter2_muon;
  G4int AirCounter;
  G4double EnergyScintillator;
  G4double tracklength;  
  G4double tracklength1;  
  G4double tracklength2;  
  G4double tracklength_pos;  
  G4double tracklength1_pos;  
  G4double tracklength2_pos;  
  G4double tracklength_muon;
  G4double tracklength1_muon;  
  G4double tracklength2_muon;  
  G4double BetaEnergy;
  G4double PositronEnergy;
  G4double InitialTheta;
  G4double ZStop;
  G4double InitialMomentum_pos;
  G4double InitialMomentum_muon;
  G4double InitialPhi;
  G4double FinalTheta;
  G4double FinalPhi;
  G4double y[5000],z[5000],t[5000],y_muon[5000],z_muon[5000],tph_muon[5000],y_1[5000],z_1[5000],t_1[5000],y1_muon[5000],z1_muon[5000],tph1_muon[5000];
  G4double delta1_l[5000];
  G4double delta1_t[5000];
  G4double delta1muon_l[5000];
  G4double delta1muon_t[5000];
  G4double delta_l[5000];
  G4double delta_t[5000];
  G4double deltamuon_l[5000];
  G4double deltamuon_t[5000];
  G4int k,k1,k2,kk1,kk2,kk;
  G4int Nph,Nph_muon,Nph_1,Nph1_muon;

};
