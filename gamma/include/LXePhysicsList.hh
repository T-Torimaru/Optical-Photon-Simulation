//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef LXePhysicsList_h
#define LXePhysicsList_h 1

#include "globals.hh"
#include "G4VUserPhysicsList.hh"
#include "G4Cerenkov.hh"
#include "G4Scintillation.hh"
#include "G4OpAbsorption.hh"
#include "G4OpRayleigh.hh"
#include "G4OpMieHG.hh"
#include "G4OpBoundaryProcess.hh"

class G4VDecayChannel;
class LXeMuonDecayChannelWithSpin;
class LXeMuonRadiativeDecayChannelWithSpin;
class LXePhysicsListMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class LXePhysicsList : public G4VUserPhysicsList
{
private:
   G4Cerenkov              *theCerenkovProcess;
   G4Scintillation         *theScintillationProcess;
   G4Scintillation         *theScintillationProcessAlpha;
   G4OpAbsorption          *theAbsorptionProcess;
   G4OpRayleigh            *theRayleighScatteringProcess;
   G4OpMieHG               *theMieHGScatteringProcess;
   G4OpBoundaryProcess     *theBoundaryProcess;

   G4VDecayChannel                      *muonMichelChannel;
   LXeMuonDecayChannelWithSpin          *muonChannelWithSpin;
   LXeMuonRadiativeDecayChannelWithSpin *muonRadiativeChannelWithSpin;
   G4VDecayChannel                      *muegammaChannel;

   LXePhysicsListMessenger *pMessenger;

   G4double xeYieldRatioAlpha;
   G4double xeScintillationYieldAlphaGammaRatio;
   G4bool fFiniteRiseTime;
public:
   LXePhysicsList();
   ~LXePhysicsList();

public:
   void ConstructParticle();
   void ConstructProcess();

   void SetCuts();

   //these methods Construct particles
   void ConstructBosons();
   void ConstructLeptons();
   void ConstructMesons();
   void ConstructBaryons();
   void ConstructIons();

   //these methods Construct physics processes and register them
   void ConstructGeneral();
   void ConstructEM();
   void ConstructOp();

   void AddPAIModel(const G4String& modname);
   void NewPAIModel(const G4ParticleDefinition* part, 
                    const G4String& modname,
                    const G4String& procname);

   void Update();

   // Muon decay control
   G4VDecayChannel                      *GetMuonMichelChannel() { return muonMichelChannel; }
   LXeMuonDecayChannelWithSpin          *GetMuonChannelWithSpin()          { return muonChannelWithSpin; }
   LXeMuonRadiativeDecayChannelWithSpin *GetMuonRadiativeChannelWithSpin() { return muonRadiativeChannelWithSpin; }
   G4VDecayChannel                      *GetMuegammaChannel() { return muegammaChannel; }
   void                                  SetMuonDecayBR();

   //for the Messenger 
   void SetVerbose(G4int);
   void SetXeYieldRatioAlpha(G4double v) { xeYieldRatioAlpha = v; }
   void UpdateXeYieldRatioAlpha() {
      if (theScintillationProcessAlpha) {
         theScintillationProcessAlpha->SetScintillationExcitationRatio(xeYieldRatioAlpha);
      }
   }
   void SetXeScintillationYieldAlphaGammaRatio(G4double v) { xeScintillationYieldAlphaGammaRatio = v; }
   void UpdateXeScintillationYieldAlphaGammaRatio() {
      if (theScintillationProcessAlpha) {
         theScintillationProcessAlpha->SetScintillationYieldFactor(xeScintillationYieldAlphaGammaRatio);
      }
   }

   G4double GetXeYieldRatioAlpha()                   const { return xeYieldRatioAlpha; }
   G4double GetXeScintillationYieldAlphaGammaRatio() const { return xeScintillationYieldAlphaGammaRatio; }
   void SetFiniteScintillationRiseTime(G4bool v) { fFiniteRiseTime = v; }
   void UpdateFiniteScintillationRiseTime() {
      if (theScintillationProcess) {
         theScintillationProcess->SetFiniteRiseTime(fFiniteRiseTime);
      }
   }
};

#endif

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
