//$Id: ATSAPrimaryGeneratorAction.hh 141 2013-01-18 13:31:51Z ripiccini $
//$Rev: 141 $

#ifndef ATSAPrimaryGeneratorAction_h
#define ATSAPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "TRandom3.h"

class G4ParticleGun;
class G4GeneralParticleSource;
class G4Event;


class ATSAPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
  ATSAPrimaryGeneratorAction();
  ~ATSAPrimaryGeneratorAction();
  
public:
  void GeneratePrimaries(G4Event* anEvent);
  

  
private:
  G4ParticleGun* particleGun;
  G4GeneralParticleSource* gps; 
  TRandom3* gen;  
  
};

#endif


