set g4root=/megsrv00/users/torimaru/geant10.0

setenv G4SYSTEM Linux-g++
setenv G4INSTALL ${g4root}/geant4.10.00.p01
setenv CLHEP_BASE_DIR /usr/local/CLHEP

setenv G4VIS_USE_OPENGLX 1
setenv G4UI_USE_TCSH 1
setenv G4DAWNFILE_PS_VIEWER gv
setenv G4VRMLFILE_VIEWER vrmlview

setenv G4LEDATA ${g4root}/data/G4EMLOW.4.3
setenv G4NEUTRONHPDATA ${g4root}/data/G4NDL.3.11
setenv G4LEVELGAMMADATA ${g4root}/data/G4PhotonEvaporation.2.0
setenv G4RADIOACTIVEDATA ${g4root}/data/G4RadiativeDecay.3.2
setenv G4ELASTICDATA ${g4root}/data/G4ELASTIC.1.1

unset g4root

setenv PATH ${PATH}:/opt/heplib/bin
