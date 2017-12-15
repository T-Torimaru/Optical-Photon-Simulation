//$Id: ATSAPhysicsList.hh 6 2012-09-06 06:09:50Z degerone $
//$Rev: 6 $

#ifndef ATSAPhysicsList_h
#define ATSAPhysicsList_h 1

#include "G4VUserPhysicsList.hh"
#include "globals.hh"

class G4Scintillation;
class G4OpAbsorption;
class G4OpBoundaryProcess;



class ATSAPhysicsList: public G4VUserPhysicsList
{
  public:
    ATSAPhysicsList();
    ~ATSAPhysicsList();

  protected:
    // Construct particle and physics process
  void ConstructParticle();
  void ConstructBosons();
  void ConstructLeptons();
  void ConstructProcess();
  void SetCuts();

  //construct physics processes
  void ConstructGeneral(); // general process (??)
  void ConstructEM(); // EM processes
  void ConstructOp(); // Optical processes
  void ConstructIon();//IonProcesses  

 G4Scintillation* theScintillationProcess;
 G4OpAbsorption* theAbsorptionProcess;
 G4OpBoundaryProcess* theBoundaryProcess;

  G4double cutForElectron;

private: 
 



};

#endif







