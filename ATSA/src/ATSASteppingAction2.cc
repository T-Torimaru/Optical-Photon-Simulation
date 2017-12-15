//$Id$
//$Rev$

//#include "globals.hh"
#include "ATSASteppingAction2.hh"
#include "ATSADetectorConstruction2.hh"
#include "ATSAEventAction2.hh"
#include "ATSARunAction.hh"
#include "G4SteppingManager.hh"
#include "G4Step.hh"
#include "ATSAHistoManager.hh"
#include "G4StepPoint.hh"
#include "ATSATrackingAction2.hh"
#include "TRandom3.h"
#include "G4EmSaturation.hh"
#include "G4SystemOfUnits.hh"

ATSASteppingAction2::ATSASteppingAction2(ATSADetectorConstruction2* det,ATSAEventAction2* evt, ATSAHistoManager* histo, ATSATrackingAction2* track)
  :detector(det), eventaction(evt), histoManager(histo), tracking(track)
{ }

ATSASteppingAction2::~ATSASteppingAction2()
{ }

void ATSASteppingAction2::UserSteppingAction(const G4Step* aStep)
{
  //Get volume
  G4VPhysicalVolume* volume = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
  G4VPhysicalVolume* nextvolume = aStep->GetPostStepPoint()->GetTouchableHandle()->GetVolume();
  G4VPhysicalVolume* fiber;
  G4VPhysicalVolume* fiber_0;
  G4VPhysicalVolume* fiber1;
  G4VPhysicalVolume* fiber2;
  G4VPhysicalVolume* cladding1;
  G4VPhysicalVolume* cladding2;
  G4VPhysicalVolume* cladding1_0;
  G4VPhysicalVolume* cladding2_0;
  G4VPhysicalVolume* cladding1_1;
  G4VPhysicalVolume* cladding2_1;
  G4VPhysicalVolume* cladding1_2;
  G4VPhysicalVolume* cladding2_2;
  G4VPhysicalVolume* world;
  G4VPhysicalVolume* SiPM;
  G4VPhysicalVolume* SiPMWin;
  G4VPhysicalVolume* SiPM_1;
  G4VPhysicalVolume* SiPMWin_1;
  G4VPhysicalVolume* groove;
  G4VPhysicalVolume* SiPM1;
  G4VPhysicalVolume* SiPM2;
  G4VPhysicalVolume* MylarWin;
  G4VPhysicalVolume* LightGuide;
  G4VPhysicalVolume* LightGuide1;
  G4VPhysicalVolume* WhiteFiber;
  G4VPhysicalVolume* deposit;
  G4VPhysicalVolume* glue;
  G4VPhysicalVolume* glue_2;
  G4VPhysicalVolume* grease;
  G4VPhysicalVolume* scintillator;
  glue=detector->GetGlue();
  grease=detector->GetGlue_1();
  glue_2=detector->GetGlue_2();
  groove=detector->GetGroove();
  fiber=detector->GetAbsorberCore();
  fiber_0=detector->GetAbsorberCore_0();
  fiber1=detector->GetAbsorberCore_1();
  fiber2=detector->GetAbsorberCore_2();
  cladding1=detector->GetCladding1();
  cladding2=detector->GetCladding2();
  cladding1_1=detector->GetCladding1_1();
  cladding2_1=detector->GetCladding2_1();
  cladding1_2=detector->GetCladding1_2();
  cladding2_2=detector->GetCladding2_2();
  world=detector->GetExpHall();
  SiPM=detector->GetSiPM();
  SiPMWin=detector->GetSiPMWin();
  SiPMWin_1=detector->GetSiPMWin_1();
  SiPM1=detector->GetSiPM_1();
  SiPM2=detector->GetSiPM_2();
  MylarWin=detector->GetMylar();
  LightGuide=detector->GetLightGuide();
  LightGuide1=detector->GetLightGuide1();
  WhiteFiber=detector->GetWhiteFiber();
  deposit=detector->GetDeposit();
  scintillator=detector->GetScintillator();
  

  G4String name;
  G4double SpectrumEnergy;
  G4ThreeVector position;
  G4ThreeVector momdirpre;
  G4ThreeVector momdirpost;
  
  G4EmSaturation *EmSaturation;
  bool muon=detector->GetMuonFlag();
  
  //KILL PHOTON                                                                                                                                                                  
  TRandom3 *gen=eventaction->GetRandomGenerator(); 
  
  
  G4double killphot=eventaction->GetKillPhoton();
  killphot=killphot/100.;
  
  //  G4cout<<killphot<<G4endl;
  
  
  if(volume==LightGuide1 && nextvolume==SiPMWin_1){
    
    Double_t k=gen->Uniform(0.,1.);
    
    if(k>0. && k<killphot)aStep->GetTrack()->SetTrackStatus(fStopAndKill);
    
  }

  if(volume==LightGuide && nextvolume==SiPMWin){
    
    Double_t k=gen->Uniform(0.,1.);
    
    if(k>0. && k<killphot)aStep->GetTrack()->SetTrackStatus(fStopAndKill);
    
  }

  // name=volume->GetName();
  //following line should be changed depending on the created events
  //case Sr90: parentid = 1 / trackid = 4
  //case e- : parentid = 0 / track id = 1
  
  //  if(aStep->GetTrack()->GetTrackID()>1 && aStep->GetTrack()->GetDefinition()->GetParticleName()=="e-")G4cout<<aStep->GetTrack()->GetCreatorProcess()->GetProcessName()<<"  "<<name<<G4endl;
  
  //  if(aStep->GetTrack()->GetDefinition()->GetParticleName()=="e-")G4cout<<aStep->GetTrack()->GetTrackID()<<G4endl; 
  
  G4double steplength=aStep->GetStepLength();
  ///if(volume==cladding2 || volume==cladding1 || volume==fiber)
  
  // aStep->SetStepLength((G4double)aStep->GetStepLength());
  
  //   G4cout<<(aStep->GetStepLength())/mm<<G4endl;
  

  //  if(aStep->GetTrack()->GetCurrentStepNumber()==1)G4cout<<aStep->GetTrack()->GetTrackID()<<G4endl; 
  

 


  
  
  if(aStep->GetTrack()->GetDefinition()->GetParticleName()=="opticalphoton"){
    
    G4double x1,x;
    G4ThreeVector cladpos=aStep->GetPreStepPoint()->GetPosition();
    G4int trackID;
    G4int stepnumber;
    
    trackID=aStep->GetTrack()->GetTrackID();
    
    if(volume==cladding1){
      
      if((cladpos.z()==-0.125 || cladpos.z()==0.125) && nextvolume==fiber)
	
	{
	  tracking->SetX1(1);
	  //	  G4cout<<cladpos.z()<<" "<<cladpos.x()<<G4endl;
	}    
      //  if(cladpos.z()==0.125 && aStep->GetTrack()->GetTrackID()==trackID)tracking->SetX2(1);
      
    }
    
    
  }  
  
  
  if(aStep->GetTrack()->GetParentID()==0 && aStep->GetTrack()->GetDefinition()->GetParticleName()=="e-" && aStep->GetTrack()->GetCurrentStepNumber()==1){
    
    SpectrumEnergy=aStep->GetPreStepPoint()->GetKineticEnergy();


    eventaction->SetSpectrumEnergy(SpectrumEnergy);

  
  }


  if(aStep->GetTrack()->GetParentID()==1 && aStep->GetTrack()->GetDefinition()->GetParticleName()=="e+" && aStep->GetTrack()->GetCurrentStepNumber()==1){
    
    G4double PositronEnergy=aStep->GetPreStepPoint()->GetKineticEnergy();


    eventaction->SetPositronEnergy(PositronEnergy);

  
  }


  if(volume==fiber && nextvolume==world && aStep->GetTrack()->GetDefinition()->GetParticleName()=="opticalphoton"){
    
    momdirpre = aStep->GetPreStepPoint()->GetMomentumDirection();
    momdirpost = aStep->GetPostStepPoint()->GetMomentumDirection();
    

    
    //   G4cout<<57.296*std::acos(momdirpre.z())-90<<G4endl;
    
  }
  
    
    if(aStep->GetTrack()->GetDefinition()->GetParticleName()=="opticalphoton" && aStep->GetTrack()->GetCurrentStepNumber()==1){
      
    //    G4cout<<aStep->GetPreStepPoint()->GetKineticEnergy()<<G4endl;


    G4double h_planck=6.62606e-34*joule*s;//4.136*eV*s;
    G4double c=3e8*m/s;
    G4double e=1.6021765e-19*joule/eV;



    G4ThreeVector Pos;

    Pos=aStep->GetPreStepPoint()->GetPosition();



    //G4cout<<(((h_planck*c/(aStep->GetPreStepPoint()->GetKineticEnergy())*1e-9))/e)*1e15<<G4endl;
  
  }

  if(volume==fiber && aStep->GetTrack()->GetDefinition()->GetParticleName()=="e+" &&  aStep->GetTrack()->GetCurrentStepNumber()==1){
    

    G4ThreeVector Pos;
    Pos=aStep->GetTrack()->GetMomentum();
    eventaction->SetInitialTheta(Pos.theta());
    eventaction->SetInitialPhi(Pos.phi());
   
    G4double momentum=sqrt(pow(Pos.x(),2)+pow(Pos.y(),2)+pow(Pos.z(),2));
   
    eventaction->SetInitialMomentum_pos(momentum);

  }


  if(aStep->GetTrack()->GetDefinition()->GetParticleName()=="mu+" &&  aStep->GetTrack()->GetCurrentStepNumber()==1){

    G4ThreeVector Pos;
    Pos=aStep->GetTrack()->GetMomentum();
    
    G4double momentum=sqrt(pow(Pos.x(),2)+pow(Pos.y(),2)+pow(Pos.z(),2));
    
    //    G4cout<<momentum<<G4endl;

    eventaction->SetInitialMomentum_muon(momentum);

  }


  if(aStep->GetTrack()->GetDefinition()->GetParticleName()=="mu+" &&  aStep->GetPreStepPoint()->GetKineticEnergy()==0.){

    G4ThreeVector Pos;
    Pos=aStep->GetPreStepPoint()->GetPosition();
    

    eventaction->SetZStop_muon(Pos.z());

  }


  if((volume==glue || volume==glue_2) && nextvolume==world && aStep->GetTrack()->GetDefinition()->GetParticleName()=="e+"){
    
    G4ThreeVector Pos;

    Pos=aStep->GetTrack()->GetMomentum();

    eventaction->SetFinalTheta(Pos.theta());
    eventaction->SetFinalPhi(Pos.phi());

  }

  if(volume==scintillator && aStep->GetTrack()->GetDefinition()->GetParticleName()=="e-"){

    G4double edep = aStep->GetTotalEnergyDeposit();

    // G4cout << "e dep " << edep << G4endl;                                                                                                                                   \
                                                                                                                                                                                  
    eventaction->AddEnergyScintillator(edep);

  }



  if((volume == fiber || volume==fiber_0) && aStep->GetTrack()->GetDefinition()->GetParticleName()=="e-" &&  aStep->GetTrack()->GetTrackID()==1)
    {


      G4double edep = aStep->GetTotalEnergyDeposit();
     
      // G4cout << "e dep " << edep << G4endl;                                                                                                                                    

      ////  example of Birk attenuation
       eventaction->AddEnergy(edep);

    }

  if(volume == fiber && aStep->GetTrack()->GetDefinition()->GetParticleName()=="e+" )//&& aStep->GetTrack()->GetParentID()==1)
    {
      G4double edep = aStep->GetTotalEnergyDeposit();

      eventaction->AddEnergy_positron(edep);




    }



  if(volume == fiber && aStep->GetTrack()->GetDefinition()->GetParticleName()=="mu+")
    {
      G4double edep = aStep->GetTotalEnergyDeposit();
      G4double steplength=aStep->GetStepLength();

      eventaction->AddEnergy_muon(edep);

      G4double response = BirksAttenuation(aStep);

      G4double LY_instant=response*(1./edep);

      //      G4cout<<LY_instant<<" "<<edep/steplength<<G4endl;

      //  G4cout<<"edep= "<<edep<<"edep1= "<<response<<"edep2= "<<response2<<G4endl;

      //  G4cout << " Destep: " << edep/keV << " keV"
      //     << " response after Birks: " << response/keV << " keV" << G4endl;

      //     aStep->SetTotalEnergyDeposit(response);

     
      eventaction->AddBirksEnergy_muon(response);
     

    }

  if(volume == fiber && aStep->GetTrack()->GetDefinition()->GetParticleName()=="e-" &&  aStep->GetTrack()->GetTrackID()==1)
    {
      G4double l = aStep->GetStepLength();
      // G4cout << "e dep " << edep << G4endl;                                                                                                                                    
     eventaction->AddTrackLength(l);


    }

  if(aStep->GetTrack()->GetDefinition()->GetParticleName()=="opticalphoton" &&  (volume==fiber || volume==cladding1 || volume==cladding2) )
    {
      G4double l = aStep->GetStepLength();

     G4int i=aStep->GetTrack()->GetTrackID();


     // G4cout << "e dep " << edep << G4endl;                                                                                                                                    
     // G4cout<<l<<" "<<i<<G4endl;
     //     G4cout<<stacking->GetGammaCounter()<<G4endl;
     //     eventaction->AddTrackLength_ph(l,i);


    }


  if(volume == fiber && aStep->GetTrack()->GetDefinition()->GetParticleName()=="e+" )//&& aStep->GetTrack()->GetParentID()==1)
    {
      G4double l = aStep->GetStepLength();
      // G4cout << "e dep " << edep << G4endl;                                                                                                                                    
     eventaction->AddTrackLength_positron(l);


    }

  if(volume == fiber && aStep->GetTrack()->GetDefinition()->GetParticleName()=="mu+")
    {
      G4double l = aStep->GetStepLength();
      // G4cout << "e dep " << edep << G4endl;                                                                                                                                    
     eventaction->AddTrackLength_muon(l);


    }


  //Fiber 1


  if(volume == fiber1 && aStep->GetTrack()->GetDefinition()->GetParticleName()=="e-" &&  aStep->GetTrack()->GetTrackID()==1)
    {


      G4double edep = aStep->GetTotalEnergyDeposit();
     
      // G4cout << "e dep " << edep << G4endl;                                                                                                                                    
      eventaction->AddEnergy1(edep);
     
    }

  if(volume == fiber1 && aStep->GetTrack()->GetDefinition()->GetParticleName()=="e+" && aStep->GetTrack()->GetParentID()==1)
    {
      G4double edep = aStep->GetTotalEnergyDeposit();

      eventaction->AddEnergy1_positron(edep);

    }



  if(volume == fiber1 && aStep->GetTrack()->GetDefinition()->GetParticleName()=="mu+")
    {
      G4double edep = aStep->GetTotalEnergyDeposit();

      eventaction->AddEnergy1_muon(edep);

    }

  if(volume == fiber1 && aStep->GetTrack()->GetDefinition()->GetParticleName()=="e-" &&  aStep->GetTrack()->GetTrackID()==1)
    {
      G4double l = aStep->GetStepLength();
      // G4cout << "e dep " << edep << G4endl;                                                                                                                                    
     eventaction->AddTrackLength1(l);


    }

  if(volume == fiber1 && aStep->GetTrack()->GetDefinition()->GetParticleName()=="e+" && aStep->GetTrack()->GetParentID()==1)
    {
      G4double l = aStep->GetStepLength();
      // G4cout << "e dep " << edep << G4endl;                                                                                                                                    
     eventaction->AddTrackLength1_positron(l);


    }

  if(volume == fiber1 && aStep->GetTrack()->GetDefinition()->GetParticleName()=="mu+")
    {
      G4double l = aStep->GetStepLength();
      // G4cout << "e dep " << edep << G4endl;                                                                                                                                    
     eventaction->AddTrackLength1_muon(l);


    }



  //Fiber 2

  if(volume == fiber2 && aStep->GetTrack()->GetDefinition()->GetParticleName()=="e-" &&  aStep->GetTrack()->GetTrackID()==1)
    {


      G4double edep = aStep->GetTotalEnergyDeposit();
     
      // G4cout << "e dep " << edep << G4endl;                                                                                                                                    
      eventaction->AddEnergy2(edep);
     
    }

  if(volume == fiber2 && aStep->GetTrack()->GetDefinition()->GetParticleName()=="e+" && aStep->GetTrack()->GetParentID()==1)
    {
      G4double edep = aStep->GetTotalEnergyDeposit();

      eventaction->AddEnergy2_positron(edep);

    }



  if(volume == fiber2 && aStep->GetTrack()->GetDefinition()->GetParticleName()=="mu+")
    {
      G4double edep = aStep->GetTotalEnergyDeposit();

      eventaction->AddEnergy2_muon(edep);

    }

  if(volume == fiber2 && aStep->GetTrack()->GetDefinition()->GetParticleName()=="e-" &&  aStep->GetTrack()->GetTrackID()==1)
    {
      G4double l = aStep->GetStepLength();
      // G4cout << "e dep " << edep << G4endl;                                                                                                                                    
     eventaction->AddTrackLength2(l);


    }

  if(volume == fiber2 && aStep->GetTrack()->GetDefinition()->GetParticleName()=="e+" && aStep->GetTrack()->GetParentID()==1)
    {
      G4double l = aStep->GetStepLength();
      // G4cout << "e dep " << edep << G4endl;                                                                                                                                    
     eventaction->AddTrackLength2_positron(l);


    }

  if(volume == fiber2 && aStep->GetTrack()->GetDefinition()->GetParticleName()=="mu+")
    {
      G4double l = aStep->GetStepLength();
      // G4cout << "e dep " << edep << G4endl;                                                                                                                                    
     eventaction->AddTrackLength2_muon(l);


    }






 if(volume==fiber && aStep->GetTrack()->GetDefinition()->GetParticleName()=="opticalphoton"){

   G4ThreeVector Pos=aStep->GetPreStepPoint()->GetPosition();


 }


 // G4cout<<aStep->GetTrack()->GetCreatorProcess()->GetProcessName()<<G4endl;
 //G4cout<< aStep->GetPreStepPoint()->GetProcessDefinedStep()->GetProcessName()<<G4endl;

 /* if( aStep->GetTrack()->GetDefinition()->GetParticleName()=="opticalphoton" && aStep->GetPreStepPoint()->GetProcessDefinedStep()->GetProcessName()=="OpticalAbsorbtion"){

   G4cout<<"deh boia"<<G4endl;

   }*/



 //REFRACTION ANGLE FROM CORE TO CLAD1

if(volume==fiber && nextvolume==cladding1 && aStep->GetTrack()->GetDefinition()->GetParticleName()=="opticalphoton"){

  momdirpre = aStep->GetPreStepPoint()->GetMomentumDirection();
  momdirpost = aStep->GetPostStepPoint()->GetMomentumDirection();
  
  
}



if(volume==cladding1 && nextvolume==fiber && aStep->GetTrack()->GetDefinition()->GetParticleName()=="opticalphoton"){


  momdirpost = aStep->GetPostStepPoint()->GetMomentumDirection();
  

}




//REFRACTION ANGLE FROM CLAD1 TO CLAD2

if(volume==cladding1 && nextvolume==cladding2 && aStep->GetTrack()->GetDefinition()->GetParticleName()=="opticalphoton"){

  momdirpre = aStep->GetPreStepPoint()->GetMomentumDirection();
  momdirpost = aStep->GetPostStepPoint()->GetMomentumDirection();
  
  
}



if(volume==cladding2 && nextvolume==cladding1 && aStep->GetTrack()->GetDefinition()->GetParticleName()=="opticalphoton"){


  momdirpost = aStep->GetPostStepPoint()->GetMomentumDirection();
  
  
}


//REFRACTION ANGLE FROM CLAD2 TO AIR

if(volume==cladding2 && nextvolume==world && aStep->GetTrack()->GetDefinition()->GetParticleName()=="opticalphoton"){

  momdirpre = aStep->GetPreStepPoint()->GetMomentumDirection();
  momdirpost = aStep->GetPostStepPoint()->GetMomentumDirection();
  
  
}



if(volume==world && nextvolume==cladding2 && aStep->GetTrack()->GetDefinition()->GetParticleName()=="opticalphoton"){


  momdirpost = aStep->GetPostStepPoint()->GetMomentumDirection();
  

  
}


  //Get volume name


 // name=nextvolume->GetName();
 
 name=volume->GetName();



 //if( volume==cladding1 &&  aStep->GetTrack()->GetDefinition()->GetParticleName()=="opticalphoton") G4cout<<"dioccà"<<G4endl;



   //defining counter for SiPM IN THIS STEP
 
 G4int counter=0;
 G4int counterpix=0;
 G4int counterpix_pde=0;
 G4int counterpix_1=0;
 G4int counteredge_wf=0;
 G4int counteredge=0;
 G4int counteredge1=0;
 G4int counteredge2=0;
 G4int counteredge_muon=0;
 G4int counteredge1_muon=0;
 G4int counteredge2_muon=0;
 G4int counterwin=0;
 G4int counterair=0;
 G4int counterphoton=0;
 G4int counterphoton_muon=0;
 G4int counterphoton1=0;
 G4int counterphoton1_muon=0;
 G4int counterphoton2=0;
 G4int counterphoton2_muon=0;
 G4int counterMylar=0;
 G4ThreeVector Pos=aStep->GetPreStepPoint()->GetPosition();
   //   G4double x=Pos.x();

       
   //  if(x>0*mm && volume==fiber && nextvolume==world)
 
 G4double ff=detector->GetFillFactor();
 G4double QE=0.35/ff;
 
 if(volume==LightGuide && nextvolume==WhiteFiber){
   
   counteredge_wf++;
   eventaction->SetEdgeCounter_wf(counteredge_wf);
   
 }
 
   if((volume==fiber || volume==cladding1 || volume==cladding2 ) && (nextvolume==LightGuide || nextvolume==SiPMWin)){
     

     
     
     G4double time=aStep->GetPostStepPoint()->GetGlobalTime();
     
     
     
     
     
     if(muon){
       
       if(aStep->GetTrack()->GetParentID()>1){
	 counteredge++;
	 eventaction->SetEdgeCounter(counteredge);

       }
       
       if(aStep->GetTrack()->GetParentID()==1){
	 counteredge_muon++;
	 eventaction->SetEdgeCounter_muon(counteredge_muon); 

       }
       
     }else{
       
       counteredge++;
       eventaction->SetEdgeCounter(counteredge);
       
     }
     
   }
   
   if((volume==fiber || volume==cladding1 || volume==cladding2 || volume==LightGuide) && nextvolume==SiPMWin){
     
     counterwin++;
     
     eventaction->SetSiPMWinCounter(counterwin);
   }
   
   
   
   
   
   
   
   
   
 
   
   G4int Npix=detector->GetNpix();
   
   G4int eventnumber=eventaction->GetEventNumber(); 
   

   
   if(volume==fiber &&  aStep->GetTrack()->GetDefinition()->GetParticleName()=="opticalphoton" && aStep->GetTrack()->GetCurrentStepNumber()==1)time0=aStep->GetPostStepPoint()->GetGlobalTime();

   for(Int_t i=0;i<Npix*Npix;i++){
     
     
     //     if((volume==fiber || volume==cladding1 || volume==cladding2 || volume==SiPMWin) && (nextvolume->GetName().contains(Form("Pixel_pv_%d",i)))){
        if((volume==fiber || volume==cladding1 || volume==cladding2 || volume==SiPMWin) && nextvolume->GetName()==Form("av_1_impr_1_Pixel_pv_%d",i)){
  
	
       
       G4ThreeVector Pos;
       G4double time;
       G4double delta_t;
       G4double delta_l=aStep->GetTrack()->GetTrackLength();

       
       Pos=aStep->GetPostStepPoint()->GetPosition();
       time=aStep->GetPostStepPoint()->GetGlobalTime();
       delta_t=time-time0; 

       
       counterpix++;
       
    Double_t k=gen->Uniform(0.,1.);

    if(k<QE)counterpix_pde++;


    //        G4cout<<counterpix<<" "<<counterpix_pde<<" "<<QE<<G4endl;

       if(muon){
	 
	 
	 
	 if(aStep->GetTrack()->GetParentID()>1)eventaction->SetSiPMinfo(Pos.z(),Pos.y(),time,delta_l,delta_t);
	 if(aStep->GetTrack()->GetParentID()==1)eventaction->SetSiPMinfo_muon(Pos.z(),Pos.y(),time,delta_l,delta_t);
	 
	 eventaction->SetPixelCounter(counterpix,counterpix_pde,i);
	 
       }else{
	 
	 eventaction->SetSiPMinfo(Pos.z(),Pos.y(),time,delta_l,delta_t);
	 eventaction->SetPixelCounter(counterpix,counterpix_pde,i);




	 //       G4cout<<Pos.z()<<" "<<Pos.y()<<" "<<time<<G4endl;	 

	 //	  G4cout<<counterpix<<" "<<i<<G4endl;
	 
       }
       
       
     }
     
     
   }
   
   //other sipm
   

   //   if(volume->GetName().contains("Pixel"))G4cout<<volume->GetName()<<G4endl;



   for(Int_t i=0;i<Npix*Npix;i++){
     
     if((volume==fiber || volume==cladding1 || volume==cladding2 || volume==SiPMWin_1) &&  nextvolume->GetName()==Form("av_2_impr_1_Pixel_1_pv_%d",i)){

       
       G4ThreeVector Pos;
       G4double time;
       G4double delta_t;
       G4double delta_l=aStep->GetTrack()->GetTrackLength();
       
       Pos=aStep->GetPostStepPoint()->GetPosition();
       time=aStep->GetPostStepPoint()->GetGlobalTime();
       delta_t=time-time0;

       //       G4cout<<time<<G4endl;
       
       counterpix_1++;
       
       if(muon){
	 
	 //       G4cout<<Pos.z()<<" "<<Pos.y()<<" "<<time<<G4endl;
	 
	 if(aStep->GetTrack()->GetParentID()>1)eventaction->SetSiPMinfo_1(Pos.z(),Pos.y(),time,delta_l,delta_t);
	 if(aStep->GetTrack()->GetParentID()==1)eventaction->SetSiPMinfo1_muon(Pos.z(),Pos.y(),time,delta_l,delta_t);
	 
	 eventaction->SetPixelCounter_1(counterpix_1,i);
	 
       }else{
	 
	 eventaction->SetSiPMinfo_1(Pos.z(),Pos.y(),time,delta_l,delta_t);
	 
	 eventaction->SetPixelCounter_1(counterpix_1,i);
	 //	   G4cout<<aStep->GetTrack()->GetTrackID()<<G4endl;   
	 // G4cout<<counterpix<<" "<<i<<G4endl;
	 
       }
       
       
     }
     
     ///////////////////
     
     
   }
   
   if(volume==fiber || volume==cladding1 || volume==cladding2){
     
     G4ThreeVector Pos;
     
     Pos=aStep->GetPreStepPoint()->GetPosition();
     
     if(Pos.x()<10.*mm && Pos.x()>9.99*mm){
       
       
     }
     

     
   }
   
      


   //   G4cout<<SiPMWin_1->GetName()<<G4endl;
   
   if((volume==fiber || volume==cladding1 || volume==cladding2 ) && (nextvolume==LightGuide1 || nextvolume==SiPMWin_1)){
     G4double time=aStep->GetPostStepPoint()->GetGlobalTime();
     

     
     if(muon){
       if(aStep->GetTrack()->GetParentID()>1){
	 counteredge1++;
	 eventaction->SetEdgeCounter1(counteredge1);
	 
       }
       
       if(aStep->GetTrack()->GetParentID()==1){
	 counteredge1_muon++;
	 eventaction->SetEdgeCounter1_muon(counteredge1_muon);
	 
	 
       }
     }else{
       
       counteredge1++;
       
       eventaction->SetEdgeCounter1(counteredge1);
       
     }    
   }
   
   /*   if((volume==fiber2 || volume==cladding1_2 || volume==cladding2_2 ) && (nextvolume==LightGuide || nextvolume==SiPMWin)){
     
     G4double time=aStep->GetPostStepPoint()->GetGlobalTime();
     
     if(muon){
       
       if(aStep->GetTrack()->GetParentID()>1){
	 counteredge2++;
	 eventaction->SetEdgeCounter2(counteredge2);
	 
       }
       
       if(aStep->GetTrack()->GetParentID()==1){
	 counteredge2_muon++;
	 eventaction->SetEdgeCounter2_muon(counteredge2_muon);
	 
	 
       }
     }else{
       
       counteredge2++;
       
       eventaction->SetEdgeCounter2(counteredge2);
       
     }
     
   }
   */   
   
   
   
   /*     if(volume==fiber && nextvolume==MylarWin)
	  {
	  counterMylar++;
	  
	  eventaction->SetMylarCounter(counterMylar);
	  
	  }*/
   
   
   //    if( aStep->GetTrack()->GetDefinition()->GetParticleName()=="opticalphoton" && aStep->GetTrack()->GetCreatorProcess()->GetProcessName()=="OpAbsorption")G4cout<<"diocane"<<G4endl;
   
   
   //     G4cout<< aStep->GetPreStepPoint()->GetProcessDefinedStep()->GetProcessName()<<G4endl;
   
   
   if( aStep->GetTrack()->GetDefinition()->GetParticleName()=="opticalphoton"){

       G4double Ekin=aStep->GetPostStepPoint()->GetKineticEnergy();


       //       if(Ekin==0)G4cout<<volume->GetName()<<G4endl;
     }


     if( aStep->GetTrack()->GetDefinition()->GetParticleName()=="opticalphoton" && (volume==glue || volume==glue_2 || volume==grease) && (nextvolume==world || nextvolume==groove))
       {
	 counterair++;
	 
	 eventaction->SetAirCounter(counterair);
	 
       }



     if((volume==fiber || volume==fiber_0) && aStep->GetTrack()->GetDefinition()->GetParticleName()=="opticalphoton" && aStep->GetTrack()->GetCurrentStepNumber()==1)
       {

	 if(muon){
	   
	   if(aStep->GetTrack()->GetParentID()>1){
	     
	     counterphoton++;
	     
	     //	     eventaction->SetPhotonCounter(counterphoton);
	   }
	   
	   
	   
	   
	   
	   if(aStep->GetTrack()->GetParentID()==1){
	     
	     counterphoton_muon++;
	     
	     
	     eventaction->SetPhotonCounter_muon(counterphoton_muon);
	   }	 
	   
	 }else{
	   
	   
	   counterphoton++;
	   
	   //	   G4cout<<counterphoton++<<G4endl;
	  
	   eventaction->SetPhotonCounter(counterphoton);
	   
	 } 
	 
	 
	 
	 
	 
       }
     
     
     if( volume==fiber1 && aStep->GetTrack()->GetDefinition()->GetParticleName()=="opticalphoton" && aStep->GetTrack()->GetCurrentStepNumber()==1)
       {


	 if(muon){
	   
	   if(aStep->GetTrack()->GetParentID()>1){
	     
	     counterphoton1++;
	     
	     eventaction->SetPhotonCounter1(counterphoton1);
	   }
	   
	   
	   if(aStep->GetTrack()->GetParentID()==1){
	     
	     counterphoton1_muon++;
	     
	     eventaction->SetPhotonCounter1_muon(counterphoton1_muon);
	   }	 

	 }else{
	   
	     counterphoton1++;
	     
	     eventaction->SetPhotonCounter1(counterphoton1);
	     
	 } 
     

  }
     


     if( volume==fiber2 && aStep->GetTrack()->GetDefinition()->GetParticleName()=="opticalphoton" && aStep->GetTrack()->GetCurrentStepNumber()==1)
       {


	 if(muon){
	   
	   if(aStep->GetTrack()->GetParentID()>1){
	     
	     counterphoton2++;
	   
	     eventaction->SetPhotonCounter2(counterphoton2);
	   }
	   
	   
	   if(aStep->GetTrack()->GetParentID()==1){
	     
	     counterphoton2_muon++;
	     
	     eventaction->SetPhotonCounter2_muon(counterphoton2_muon);
	   }	 

	 }else{
	   
	   counterphoton2++;
	   
	   eventaction->SetPhotonCounter2(counterphoton2);
	   
	 }     
	 
       }
     
     
}


G4double ATSASteppingAction2::BirksAttenuation(const G4Step* aStep)
{
  //Example of Birk attenuation law in organic scintillators.
  //adapted from Geant3 PHYS337. See MIN 80 (1970) 239-244
  //
  G4Material* material = aStep->GetTrack()->GetMaterial();
  G4double birk1       = material->GetIonisation()->GetBirksConstant();
  //  G4cout<<birk1<<G4endl;
  G4double destep      = aStep->GetTotalEnergyDeposit();
  G4double stepl       = aStep->GetStepLength();  
  G4double charge      = aStep->GetTrack()->GetDefinition()->GetPDGCharge();
  //
  G4double response = destep;
  if (birk1*destep*stepl*charge != 0.)
    {
      response = destep/(1. + birk1*destep/stepl);
    }
  return response;
}

