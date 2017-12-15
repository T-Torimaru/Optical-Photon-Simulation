//$Id$
//$Rev$

#include "globals.hh"
#include "G4UserSteppingAction.hh"

class ATSADetectorConstruction2;
class ATSAEventAction2;
class ATSAHistoManager;
class ATSATrackingAction2;

class ATSASteppingAction2 : public G4UserSteppingAction
{

public:
  ATSASteppingAction2(ATSADetectorConstruction2*, ATSAEventAction2*, ATSAHistoManager*,ATSATrackingAction2*);
  ~ATSASteppingAction2();
  void UserSteppingAction(const G4Step*);
  G4double BirksAttenuation(const G4Step*);
 

private:
  ATSADetectorConstruction2* detector;
  ATSAEventAction2* eventaction;
  ATSAHistoManager* histoManager;
  ATSATrackingAction2* tracking;
  G4double time0;
};

