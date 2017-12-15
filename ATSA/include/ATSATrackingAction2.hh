//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
//
// $Id: MuCoolTrackingAction.cc,v 1.4 2002/01/09 17:23:48 ranjard Exp $
// GEANT4 tag $Name: geant4-04-00-patch-02 $
//
// Modified: V.Daniel Elvira (6/23/02) - Kill secondary particles.
//                      
//   GEANT4 tracking action user class. Allows the user to perform actions
//   related with tracks.
//

#ifndef ATSATrackingAction2_h
#define ATSATrackingAction2_h 1

#include "G4UserTrackingAction.hh"
#include "globals.hh"

class ATSAHistoManager;
class ATSADetectorConstruction2;

class ATSATrackingAction2 : public G4UserTrackingAction {

public:

  // Constructor 

  ATSATrackingAction2(ATSAHistoManager*, ATSADetectorConstruction2*);

  // Destructor

  ~ATSATrackingAction2();
   
public:

  // Method for the user to pre-set actions related to tracks.

  void PreUserTrackingAction(const G4Track*);

    bool SetX1(bool x){x1=x;}
    bool SetX2(bool x){x2=x;}



private:

  bool x1,x2; 
  ATSAHistoManager* histoManager;
  ATSADetectorConstruction2* detector;



};

#endif
