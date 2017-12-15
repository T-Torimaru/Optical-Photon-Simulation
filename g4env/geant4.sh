g4root=/opt/heplib/Geant4

export G4SYSTEM=Linux-g++
export G4INSTALL=$g4root/geant4.9.0.p01
export CLHEP_BASE_DIR=/opt/heplib/CLHEP/2.0.3.1

export G4VIS_USE_OPENGLX=1
export G4UI_USE_TCSH=1
export G4DAWNFILE_PS_VIEWER=gv
export G4VRMLFILE_VIEWER=vrmlview

export G4LEDATA=$g4root/data/G4EMLOW.4.3
export G4NEUTRONHPDATA=$g4root/data/G4NDL.3.11
export G4LEVELGAMMADATA=$g4root/data/G4PhotonEvaporation.2.0
export G4RADIOACTIVEDATA=$g4root/data/G4RadiativeDecay.3.2
export G4ELASTICDATA=$g4root/data/G4ELASTIC.1.1

unset g4root

export PATH=$PATH:/opt/heplib/bin
