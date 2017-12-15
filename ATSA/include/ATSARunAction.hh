//$Id: ATSARunAction.hh 37 2012-09-08 08:44:04Z degerone $
//$Rev: 37 $


#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;
class ATSAHistoManager;


class ATSARunAction : public G4UserRunAction
   {
     public:
         ATSARunAction(ATSAHistoManager*);
         ~ATSARunAction();

     void AddStoppedSingle(G4int i) {single += i;}
     void AddStoppedArray1(G4int i) {array1 += i;}
     void AddStoppedArray2(G4int i) {array2 += i;}

     
     G4int single;
     G4int array1;
     G4int array2;

     public:
         void BeginOfRunAction(const G4Run*);
         void EndOfRunAction(const G4Run*);


     private:
     ATSAHistoManager* histoManager;

   };


