//$Id: ATSAEventAction.hh 150 2013-01-22 15:06:08Z ripiccini $
//$Rev: 150 $

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "TRandom3.h"

class G4Event;
class ATSARunAction;
class ATSAHistoManager;
class ATSASteppingAction2;
class ATSADetectorConstruction2;

class ATSAEventAction2 : public G4UserEventAction
      {
      public:
	ATSAEventAction2(ATSARunAction*, ATSAHistoManager*,ATSADetectorConstruction2*,double);
	~ATSAEventAction2();

      public:



	void BeginOfEventAction(const G4Event*);
	void EndOfEventAction(const G4Event*);
	void AddEnergyScintillator(G4double step_ene) {EnergyScintillator += step_ene;}
	void AddEnergy(G4double step_ene) {Energy += step_ene;}
	void AddEnergy1(G4double step_ene) {Energy1 += step_ene;}
	void AddEnergy2(G4double step_ene) {Energy2 += step_ene;}
	void AddEnergy_positron(G4double step_ene) {Energy_pos += step_ene;}
	void AddEnergy1_positron(G4double step_ene) {Energy1_pos += step_ene;}
	void AddEnergy2_positron(G4double step_ene) {Energy2_pos += step_ene;}
	
	void AddEnergy_muon(G4double step_ene) {Energy_muon += step_ene;}
	void AddBirksEnergy_muon(G4double step_ene) {EnergyBirks_muon += step_ene;}
	void AddEnergy1_muon(G4double step_ene) {Energy1_muon += step_ene;}
	void AddEnergy2_muon(G4double step_ene) {Energy2_muon += step_ene;}

	void SetInitialTheta(G4double ThetaAngle){InitialTheta = ThetaAngle;}
	void SetZStop_muon(G4double z){ZStop = z;}
	void SetInitialPhi(G4double PhiAngle){InitialPhi = PhiAngle;}
	void SetFinalTheta(G4double ThetaAngle){FinalTheta = ThetaAngle;}
	void SetInitialMomentum_pos(G4double momentum){InitialMomentum_pos = momentum;}
	void SetInitialMomentum_muon(G4double momentum){InitialMomentum_muon = momentum;}
	void SetFinalPhi(G4double PhiAngle){FinalPhi = PhiAngle;}
	void SetInitialCosTheta(G4double CosThetaAngle){InitialCosTheta = CosThetaAngle;}
	void SetInitialSinPhi(G4double SinPhiAngle){InitialSinPhi = SinPhiAngle;}
	TRandom3* GetRandomGenerator(){return gen;}
	G4int GetEventNumber(){return eventnumber;}
	G4double GetEnergyDeposit(){return Energy;}
	double GetKillPhoton(){return killphot;}

	void AddTrackLength(G4double step_trackL) {trackLength += step_trackL;}
	void AddTrackLength1(G4double step_trackL) {trackLength1 += step_trackL;}
	void AddTrackLength2(G4double step_trackL) {trackLength2 += step_trackL;}
	void AddTrackLength_positron(G4double step_trackL) {trackLength_pos += step_trackL;}
	void AddTrackLength1_positron(G4double step_trackL) {trackLength1_pos += step_trackL;}
	void AddTrackLength2_positron(G4double step_trackL) {trackLength2_pos += step_trackL;}
	void AddTrackLength_muon(G4double step_trackL) {trackLength_muon += step_trackL;}
	void AddTrackLength1_muon(G4double step_trackL) {trackLength1_muon += step_trackL;}
	void AddTrackLength2_muon(G4double step_trackL) {trackLength2_muon += step_trackL;}
	void SetSpectrumEnergy(G4double SpectrumEnergy) {BetaEnergy=SpectrumEnergy;}
	void SetPositronEnergy(G4double energy){PositronEnergy=energy;}
	void SetPositionX(G4double x_pos){PosX=x_pos;}
	void SetPositionY(G4double y_pos){PosY=y_pos;}
	void SetPositionZ(G4double z_pos){PosZ=z_pos;}


	G4double GetEnergy() {return Energy;}
	G4int GetSiPMCounter() {return SiPMCounter;}
	void SetSiPMCounter(G4int count) {SiPMCounter+=count;}
	void SetSiPMWinCounter(G4int count) {SiPMWinCounter+=count;}
	void SetEdgeCounter_wf(G4int count) {EdgeCounter_wf+=count;}
	void SetEdgeCounter(G4int count) {EdgeCounter+=count;}
	void SetEdgeCounter1(G4int count) {EdgeCounter1+=count;}
	void SetEdgeCounter2(G4int count) {EdgeCounter2+=count;}
	void SetEdgeCounter_muon(G4int count) {EdgeCounter_muon+=count;}
	void SetEdgeCounter1_muon(G4int count) {EdgeCounter1_muon+=count;}
	void SetEdgeCounter2_muon(G4int count) {EdgeCounter2_muon+=count;}
       	void SetPixelCounter(G4int count, G4int countpde, G4int i) {
	  SiPMPixelCounter[i]+=count;
	  SiPMPixelCounter_pde[i]+=countpde;
	  pixelindex=i; 
	}

       	void SetPixelCounter_1(G4int count, G4int i) {
	  SiPMPixelCounter_1[i]+=count;
	  pixelindex_1=i; 
	}
	void SetSiPMinfo_1(G4double posz, G4double posy, G4double time, G4double deltal, G4double deltat){

	  z_1[ll]=posz;
	  y_1[ll]=posy;
	  t_1[ll]=time;
	  delta1_l[ll]=deltal;
	  delta1_t[ll]=deltat;
	  ll++;
	  Nph_1=ll;


	}

	void SetSiPMinfo1_muon(G4double posz, G4double posy, G4double time,G4double deltal, G4double deltat){

	 


	  z1_muon[mm]=posz;
	  y1_muon[mm]=posy;
	  tph1_muon[mm]=time;
	  delta1muon_l[mm]=deltal;
	  delta1muon_t[mm]=deltat;
	  mm++;
	  Nph1_muon=mm;
	}

	void SetSiPMinfo(G4double posz, G4double posy, G4double time,G4double deltal, G4double deltat){

	  z[j]=posz;
	  y[j]=posy;
	  t[j]=time;
	  delta_l[j]=deltal;
	  delta_t[j]=deltat;
	  j++;
	  Nph=j;


	}

	void SetSiPMinfo_muon(G4double posz, G4double posy, G4double time,G4double deltal, G4double deltat){

	 


	  z_muon[jj]=posz;
	  y_muon[jj]=posy;
	  tph_muon[jj]=time;
	  deltamuon_l[jj]=deltal;
	  deltamuon_t[jj]=deltat;
	  jj++;
	  Nph_muon=jj;
	}



	
	void SetMylarCounter(G4int count) {MylarCounter+=count;}
	void SetOutOfFiber(G4int count_out) {OutCounter+=count_out;}
	void SetAirCounter(G4int countair) {AirCounter+=countair;}
	void SetPhotonCounter(G4int count) {PhotonCounter+=count;}
	void SetPhotonCounter1(G4int count) {PhotonCounter1+=count;}
	void SetPhotonCounter2(G4int count) {PhotonCounter2+=count;}
	void SetPhotonCounter_muon(G4int count) {PhotonCounter_muon+=count;}
	void SetPhotonCounter1_muon(G4int count) {PhotonCounter1_muon+=count;}
	void SetPhotonCounter2_muon(G4int count) {PhotonCounter2_muon+=count;}
	

      private:
	double killphot;
	ATSARunAction* runAct;
	ATSAHistoManager* histoManager;
	ATSADetectorConstruction2* detector;
	TRandom3 *gen;
	G4int Npix;
	G4double InitialTheta;
	G4double ZStop;
	G4double InitialMomentum_pos;
	G4double InitialMomentum_muon;
	G4double InitialPhi;
	G4double FinalTheta;
	G4double FinalPhi;
	G4double InitialCosTheta;
	G4double InitialSinPhi;
	G4int eventnumber;
	G4double z[5000];
	G4double y[5000];
	G4double t[5000];
	G4double delta_l[5000];
	G4double delta_t[5000];
	G4double deltamuon_l[500];
	G4double deltamuon_t[500];
	G4double z_muon[800];
	G4double y_muon[800];
	G4double tph_muon[800];
	G4double z_1[5000];
	G4double y_1[5000];
	G4double t_1[5000];
	G4double delta1_l[5000];
	G4double delta1_t[5000];
	G4double delta1muon_l[500];
	G4double delta1muon_t[500];
	G4double z1_muon[800];
	G4double y1_muon[800];
	G4double tph1_muon[800];
	G4int j,jj,Nph,Nph_muon,ll,mm,Nph_1,Nph1_muon;
	G4int k,k1,k2,kk1,kk2,kk;
	G4double Energy;
	G4double Energy_pos;
	G4double Energy_muon;
	G4double EnergyBirks_muon;
	G4double EnergyScintillator;
	G4double Energy1;
	G4double Energy2;
	G4double Energy1_pos;
	G4double Energy2_pos;
	G4double Energy1_muon;
	G4double Energy2_muon;
	G4int SiPMCounter;
	G4int SiPMWinCounter;
	G4int EdgeCounter_wf;
	G4int EdgeCounter;
	G4int EdgeCounter_muon;
	int SiPMPixelCounter[1600];
	int SiPMPixelCounter_pde[1600];
	int SiPMPixelCounter_1[1600];
	G4int pixelindex;
	G4int pixelindex_1;
	G4int EdgeCounter1;
	G4int EdgeCounter2;
	G4int EdgeCounter1_muon;
	G4int EdgeCounter2_muon;
	G4int MylarCounter;
	G4int OutCounter;
	G4int AirCounter;
	G4int PhotonCounter;
	G4int PhotonCounter1;
	G4int PhotonCounter2;
	G4int PhotonCounter_muon;
	G4int PhotonCounter1_muon;
	G4int PhotonCounter2_muon;
	G4double trackLength_pos;
	G4double trackLength1_pos;
	G4double trackLength2_pos;
	G4double trackLength;
	G4double trackLength1;
	G4double trackLength2;
	G4double trackLength_muon;
	G4double trackLength1_muon;
	G4double trackLength2_muon;
	G4double BetaEnergy;
	G4double PositronEnergy;
	G4double PosX;
	G4double PosY;
	G4double PosZ;
	G4int totphotonsipm;
	G4int totphotonsipm_pde;

      

       };
