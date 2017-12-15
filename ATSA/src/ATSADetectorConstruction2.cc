#include "ATSADetectorConstruction2.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Trd.hh"
#include "G4Cons.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "globals.hh"
#include "G4NistManager.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
//following include needed to define optical surface for photon reflection
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4VSensitiveDetector.hh"
#include "G4AssemblyVolume.hh"
#include "G4SDManager.hh"
#include "G4UserLimits.hh"
#include "G4Trap.hh"
#include "G4SystemOfUnits.hh"

ATSADetectorConstruction2::ATSADetectorConstruction2(double dim, bool dep)
:dfib(dim),deposit(dep)
{
  ;}

ATSADetectorConstruction2::~ATSADetectorConstruction2()
{
  ;}

G4VPhysicalVolume* ATSADetectorConstruction2::Construct()
{
  
  //------------------------------------------------------ materials
  
  scintBCF12 = G4NistManager::Instance()->FindOrBuildMaterial("G4_POLYSTYRENE"); //BCF12 fibers
  scintBC404 = G4NistManager::Instance()->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE"); //BC400
  Aluminum= G4NistManager::Instance()->FindOrBuildMaterial("G4_Al");
  Plexiglass= G4NistManager::Instance()->FindOrBuildMaterial("G4_PLEXIGLASS");
  Copper= G4NistManager::Instance()->FindOrBuildMaterial("G4_Cu");
  air = G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR"); 
  iron=G4NistManager::Instance()->FindOrBuildMaterial("G4_Fe"); 
  silicon=G4NistManager::Instance()->FindOrBuildMaterial("G4_Si"); 
  lead=G4NistManager::Instance()->FindOrBuildMaterial("G4_Pb");
  Mylar=G4NistManager::Instance()->FindOrBuildMaterial("G4_MYLAR");
  vacuum=G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic");
  
  
  // Use NIST database for elements and materials wherever possible.
  G4NistManager* man = G4NistManager::Instance();
  man->SetVerbose(1);
  // Define elements from NIST 
  G4Element* C  = man->FindOrBuildElement("C");
  G4Element* Si = man->FindOrBuildElement("Si");
  G4Element* Cr = man->FindOrBuildElement("Cr");
  G4Element* Mn = man->FindOrBuildElement("Mn");
  G4Element* Fe = man->FindOrBuildElement("Fe");
  G4Element* Ni = man->FindOrBuildElement("Ni");
  G4Element* H = man->FindOrBuildElement("H");
  G4Element* O = man->FindOrBuildElement("O");
  G4Element* F = man->FindOrBuildElement("F");
  G4Element* Al = man->FindOrBuildElement("Al");
  
  G4double density;
  G4int ncomponents;
  G4double fractionmass;
  
  G4Material* StainlessSteel = new G4Material("StainlessSteel", density= 8.06*g/cm3, ncomponents=6);
  StainlessSteel->AddElement(C, fractionmass=0.001);
  StainlessSteel->AddElement(Si, fractionmass=0.007);
  StainlessSteel->AddElement(Cr, fractionmass=0.18);
  StainlessSteel->AddElement(Mn, fractionmass=0.01);
  StainlessSteel->AddElement(Fe, fractionmass=0.712);
  StainlessSteel->AddElement(Ni, fractionmass=0.09);
  
  
  //  G4cout<<configuration<<" "<<fibdim<<G4endl;
  
  density= 3.7*g/cm3;
  G4Material* Ceramic = new G4Material("Ceramic", density, ncomponents=2);
  Ceramic->AddElement(Al, 2);
  Ceramic->AddElement(O, 3);
  
  //Epoxy                                                                                                                                                                         
  
  density = 1.2*g/cm3;
  G4int natoms;
  G4Material* Epoxy = new G4Material("Epoxy" , density, ncomponents=2);
  Epoxy->AddElement(H, natoms=2);
  Epoxy->AddElement(C, natoms=2);
  
  
  //Epoxy2 just different optical properties                                                                                                                                                                  
  
  density = 1.2*g/cm3;
  
  G4Material* Epoxy2 = new G4Material("Epoxy2" , density, ncomponents=2);
  Epoxy2->AddElement(H, natoms=2);
  Epoxy2->AddElement(C, natoms=2);
  
  
  
  
  // PMMA C5H8O2 ( Acrylic )
  // -------------
  density = 1.19*g/cm3;
  Acrylic = new G4Material("Acrylic", density,3);
  Acrylic->AddElement(C, 5);
  Acrylic->AddElement(H, 8);
  Acrylic->AddElement(O, 2);
  
  //Fluor Acrylic C7H5F7O2
  
  density = 1.418*g/cm3;
  FluorAcrylic = new G4Material("FluorAcrylic", density,4);
  FluorAcrylic->AddElement(C, 7);
  FluorAcrylic->AddElement(H, 5);
  FluorAcrylic->AddElement(O, 2);
  FluorAcrylic->AddElement(F, 7);
  
  //diamond for test
  
  density=3.520*g/cm3;
  Diamond=new G4Material("Diamond",density,1);
  Diamond->AddElement(C,1);
  
  G4double fibdim=(dfib/2000.)*mm;



  G4double coating_deep,coating2_deep,coredim;
  
  
  ///////ATTENZIONE A IMPOSTARE BENE QUESTI PARAMETRI!!!
  ///CONTROLLARE SELEZIONE PARTICELLE NELLO STEPPING ACTION 2
  G4double lsipm=1.3*mm;
  G4double pixdim=1.3*mm;
  G4double FiberLength=5000.*mm;

 
  Npix=(G4int)(lsipm/pixdim); 

  
  G4bool clad2=true;
  muon_flag=false;
  G4bool fiberflag=true;
  G4bool twosipm=true;
  G4bool degrader_flag=true;
  G4Material* envMaterial=air;
  G4Material* ReflectiveMaterial;
  


  G4Material* GlueMaterial=envMaterial; // this is a volume aruond the fiber, it can be made by epoxy, aluminum or air, epoxy2 (low n)
  G4double shift_z=0.*mm;//-groove_z-fibdim;
  G4double shift_y=0.*mm;
  
  
 
  
  
 
  
  
  coating_deep=2*fibdim*0.04; //lo strato di cladding è il 4% dello spessore della fibra quadrata (dato Saint Gobain) clad 1 thickness
  coating2_deep=2*fibdim*0.02; //secondo strato di cladding clad 2% of the thickness
  
  fibdim=fibdim;//+coating_deep+coating2_deep;
  
  
  
  
  
  
  // ------------ Generate & Add Material Properties Table ------------
  
  //minimum binning for energy dependent variables is 2
  const G4int nEntries = 32;
  
  //defining photon energy for energy dependent variables (420 and 440 nm - arbitrary values)
  //for now all parameters are costant values.
  //in case of energy dependent values, these will be extracted from different energies
  //by means of an order 1 spline
  // G4double PhotonEnergy[nEntries] = {2.818*eV,2.830*eV,2.850*eV,2.87*eV,2.880*eV,2.950*eV};
  
  G4double PhotonWaveLength[nEntries]={387.5,393.75,400.,406.25,
                                       412.5,418.75,425.,433.25,
                                       435.,437.5,443.25,450.,
                                       456.25,462.5,468.75,475.,
				       481.25,487.5,493.75,500.,
				       506.25,512.5,518.75,525.,
				       531.25,537.5,543.75,550.,
				       556.25,562.5,568.75,575.,};
  G4double PhotonEnergy[nEntries];
  G4double Reflectivity_Al[nEntries];
  G4double Transmission_Al[nEntries];
  G4double RIndex_Al[nEntries];
  G4double Reflectivity_Si[nEntries];
  G4double Efficiency_Si[nEntries];
  G4double Efficiency_Al[nEntries];
  G4double RIndexSilicon[nEntries];
  G4double Mylar_RefractiveIdx[nEntries];
  G4double Epoxy_RefractiveIdx[nEntries];
  G4double Plexiglass_RefractiveIdx[nEntries];
  G4double Epoxy2_RefractiveIdx[nEntries];
  
  G4double h_planck=6.62606e-34*joule*s;//4.136*eV*s;
  G4double c=3e8*m/s;
  G4double e=1.6021765e-19*joule/eV;
  
  for(G4int j=0;j<nEntries;j++){
    PhotonEnergy[nEntries-1-j]=(((h_planck*c/(PhotonWaveLength[j]*1e-9))/e)*1e3)*eV;
  }
  // Unit Check: 
  // for(G4int j=0;j<nEntries;j++)G4cout<<PhotonEnergy[j]<<G4endl;
  
  //
  // BCF 12 properties
  //
  
  //BCF 12  refractive index: fixed at 1.49 (no wavelenght dependent)
  G4double pter_RefractiveIdx[nEntries];
  
  //BCF 12 absorption length: fixed at 270cm (no wavelength dependent)
  //Value must be checked!!
  //From Saint Gobain brochure it seems this value was measured on 1mm diameter fibers
  G4double pter_AbsLength[nEntries];
  
  //must be checked!
  //if FAST/SLOW COMPONENTS are not defined, gammas are not generated! (to be understood)
  G4double pter_ScintilFast[nEntries] = {0.0001,0.0002,0.01,0.02,0.03,0.04,0.05,0.08,
					 0.1,0.15,0.19,0.2,0.22,0.27,0.34,0.4,
					 0.46,0.5,0.66,0.78,0.8,0.95,0.97,1.,
					 0.99,0.9,0.8,0.4,0.2,0.1,0.005,0.0001};
  
  //{0.0001,0.1,0.4,0.9,1.,0.98,0.8,0.65,0.45,0.33,0.22,0.2,0.1,0.05,0.03,0.01,0.0001};
  
  // for(G4int i=0;i<nEntries;i++)pter_ScintilFast[i]=pter_ScintilFast[nEntries-1-i];
  G4double pter_ScintilSlow[nEntries]= {1.,1.,1.,1.,1.,1.,1.,1.,
					1.,1.,1.,1.,1.,1.,1.,1.,
					1.,1.,1.,1.,1.,1.,1.,1.,
					1.,1.,1.,1.,1.,1.,1.,1.};
  
  // for(G4int i=0;i<nEntries;i++)pter_ScintilSlow[i]=pter_ScintilSlow[nEntries-1-i];
  G4double AirRefractiveIdx[nEntries];
  G4double abslength_acrylic[nEntries];
  G4double Acrylic_RefractiveIdx[nEntries];
  G4double abslength_Mylar[nEntries];
  G4double abslength_Epoxy[nEntries];
  G4double abslength_Plexiglass[nEntries];
  G4double abslength_Epoxy2[nEntries];
  G4double abslength_fluoracrylic[nEntries];
  G4double FluorAcrylic_RefractiveIdx[nEntries];
  G4double DiamondRefractiveIdx[nEntries];
  

  G4double norm=0.;  
  G4double deltaE[nEntries];

  for(G4int i=0;i<nEntries;i++)deltaE[i]=(((h_planck*c/(6.25*1e-9))/e)*1e3)*eV;
  for(G4int i=0;i<nEntries;i++)norm=norm+(pter_ScintilFast[i]*deltaE[i]*(((h_planck*c/(1e-9))/e)*1e3)*eV)/pow(PhotonEnergy[i],2);
  for(G4int i=0;i<nEntries;i++)pter_ScintilFast[i]=pter_ScintilFast[i]/norm;

  
  for(G4int i=0;i<nEntries;i++){
    
    Reflectivity_Al[i] = 0.925;
    Reflectivity_Si[i] = 0.;
    Efficiency_Si[i] = 1.;
    Efficiency_Al[i] = 0.;
    RIndex_Al[i]=1.;
    pter_RefractiveIdx[i] = 1.6;//1.6
    FluorAcrylic_RefractiveIdx[i]=1.42;//1.42
    Acrylic_RefractiveIdx[i]=1.49;//1.49
    AirRefractiveIdx[i]=1.;
    // pter_ScintilFast[i]=1.;
    Epoxy_RefractiveIdx[i]=1.58;//grasso ottico
    Plexiglass_RefractiveIdx[i]=1.48;
    Epoxy2_RefractiveIdx[i]=1.56;//1.38;//1.56;//1.41
    //RIndexSilicon[i]=3.45;
    pter_AbsLength[i]=270.*cm;
    abslength_Plexiglass[i]=220.*cm;
    abslength_Epoxy[i]=220.*cm;
    abslength_Epoxy2[i]=220.*cm;
    abslength_acrylic[i]=300*cm;
    abslength_fluoracrylic[i]=100*cm;
    abslength_Mylar[i]=0.21*mm;
    DiamondRefractiveIdx[i]=60.42;

    
  }
  
 //Properties Table for BCF12
 //RINDEX must be defined as waveform(energy)-dependent! At least 2 bins must be defined!! 
 //ABSLENGTH, FASTCOMPONENT, SLOWCOMPONENT: same comment as RINDEX 
  G4MaterialPropertiesTable* BCF12_table = new G4MaterialPropertiesTable();
  
  BCF12_table->AddProperty("RINDEX", PhotonEnergy, pter_RefractiveIdx,nEntries);
  BCF12_table->AddProperty("ABSLENGTH", PhotonEnergy, pter_AbsLength, nEntries);
  BCF12_table->AddProperty("FASTCOMPONENT", PhotonEnergy, pter_ScintilFast, nEntries);
  BCF12_table->AddProperty("SLOWCOMPONENT", PhotonEnergy, pter_ScintilSlow, nEntries);
  G4double LY=8000./MeV;
  
  
  BCF12_table->AddConstProperty("SCINTILLATIONYIELD",LY);//to be changed for p-terphenyl 
  
  //  G4double energies[9] = {0.,1*MeV,1.5*MeV,2.5*MeV,3.5*MeV,10*MeV,100*MeV,500*MeV,2500*MeV};
  //  G4double yield[9] = {0.,3300./MeV,3930./MeV,5800./MeV,6200./MeV,7300./MeV,7800./MeV,7900./MeV,8000./MeV};
  
  //  G4double yield[8] = {33./MeV,39./MeV,58./MeV,62./MeV,73./MeV,78./MeV,79./MeV,80./MeV};
  
  //  G4double energies[4]={0,1.*MeV,3.5*MeV,2500.*MeV};
  
  //  G4double yield[4]={0,3300./MeV,6200./MeV,8000./MeV};
  
  //  BCF12_table->AddProperty("ELECTRONSCINTILLATIONYIELD", energies, yield, 9);
  
  BCF12_table->AddConstProperty("RESOLUTIONSCALE",1.);
  BCF12_table->AddConstProperty("FASTTIMECONSTANT", 2.7*ns);
  BCF12_table->AddConstProperty("SLOWTIMECONSTANT",2.7*ns);
  BCF12_table->AddConstProperty("YIELDRATIO",1.);
  scintBCF12->GetIonisation()->SetBirksConstant(0.126*mm/MeV);
  
  scintBCF12->SetMaterialPropertiesTable(BCF12_table);
  
  
  //Properties Table for Al
  G4MaterialPropertiesTable* Aluminum_table = new G4MaterialPropertiesTable();
  //  Aluminum_table->AddProperty("RINDEX", PhotonEnergy, RIndex_Al,nEntries);
  Aluminum_table->AddProperty("REFLECTIVITY", PhotonEnergy, Reflectivity_Al, nEntries);
 
  
  Aluminum->SetMaterialPropertiesTable(Aluminum_table);
  
  //Properties Table for Si
  G4MaterialPropertiesTable* Silicon_table = new G4MaterialPropertiesTable();
  
  Silicon_table->AddProperty("REFLECTIVITY", PhotonEnergy, Reflectivity_Si, nEntries);
  Silicon_table->AddProperty("EFFICIENCY", PhotonEnergy,Efficiency_Si, nEntries);
  //  Silicon_table->AddProperty("RINDEX", PhotonEnergy,RIndexSilicon, nEntries);
  
  silicon->SetMaterialPropertiesTable(Silicon_table);
  
  // Set the Birks Constant for the p-terphenyl
  // Not important for thin scintillator
  // Terphenyl->GetIonisation()->SetBirksConstant(0.126*mm/MeV);
  
  
  //Properties Table for Air 
  G4MaterialPropertiesTable* air_table = new G4MaterialPropertiesTable();
  
  air_table->AddProperty("RINDEX", PhotonEnergy,AirRefractiveIdx, nEntries);
  
  air->SetMaterialPropertiesTable(air_table);
  
  
  //Properties Table for Acrylic Cladding1
  G4MaterialPropertiesTable *MPT_Acrylic = new G4MaterialPropertiesTable();
  
  
  MPT_Acrylic->AddProperty("RINDEX", PhotonEnergy, Acrylic_RefractiveIdx, nEntries);
  MPT_Acrylic->AddProperty("ABSLENGTH", PhotonEnergy, abslength_acrylic,nEntries);
  
  Acrylic->SetMaterialPropertiesTable(MPT_Acrylic);
  
  //Properties Table for Acrylic Cladding2
  G4MaterialPropertiesTable *MPT_FluorAcrylic = new G4MaterialPropertiesTable();
  
  MPT_FluorAcrylic->AddProperty("RINDEX", PhotonEnergy, FluorAcrylic_RefractiveIdx, nEntries);
  MPT_FluorAcrylic->AddProperty("ABSLENGTH", PhotonEnergy, abslength_fluoracrylic,nEntries);
  
  FluorAcrylic->SetMaterialPropertiesTable(MPT_FluorAcrylic);
  
  
  //Properties Table of Mylar
  
  G4MaterialPropertiesTable *MPT_Mylar = new G4MaterialPropertiesTable();
  
  MPT_Mylar->AddProperty("RINDEX", PhotonEnergy, Mylar_RefractiveIdx, nEntries);
  MPT_Mylar->AddProperty("ABSLENGTH", PhotonEnergy, abslength_Mylar,nEntries);
  
  Mylar->SetMaterialPropertiesTable(MPT_Mylar);
  
  
  //Properties Table of Epoxy
  
  G4MaterialPropertiesTable *MPT_Epoxy = new G4MaterialPropertiesTable();
  
  MPT_Epoxy->AddProperty("RINDEX", PhotonEnergy, Epoxy_RefractiveIdx, nEntries);
  MPT_Epoxy->AddProperty("ABSLENGTH", PhotonEnergy, abslength_Epoxy,nEntries);
  
  Epoxy->SetMaterialPropertiesTable(MPT_Epoxy);
  
  
  //Properties Table Plexiglass
  
  G4MaterialPropertiesTable *MPT_Plexiglass = new G4MaterialPropertiesTable();
  
  MPT_Plexiglass->AddProperty("RINDEX", PhotonEnergy, Plexiglass_RefractiveIdx, nEntries);
  MPT_Plexiglass->AddProperty("ABSLENGTH", PhotonEnergy, abslength_Plexiglass,nEntries);
  
  Plexiglass->SetMaterialPropertiesTable(MPT_Plexiglass);
  

  //Properties Table of Epoxy2
  
  G4MaterialPropertiesTable *MPT_Epoxy2 = new G4MaterialPropertiesTable();
  
  MPT_Epoxy2->AddProperty("RINDEX", PhotonEnergy, Epoxy2_RefractiveIdx, nEntries);
  MPT_Epoxy2->AddProperty("ABSLENGTH", PhotonEnergy, abslength_Epoxy2,nEntries);
  
  Epoxy2->SetMaterialPropertiesTable(MPT_Epoxy2);
  
  
  //Properties Table for Diamond
  
  G4MaterialPropertiesTable* Diamond_table = new G4MaterialPropertiesTable();
  
  Diamond_table->AddProperty("RINDEX",PhotonEnergy,DiamondRefractiveIdx,nEntries);
  Diamond->SetMaterialPropertiesTable(Diamond_table);
  
  
  
  //OPTICAL SURFACES
  G4OpticalSurface* optical_surface_fib = new G4OpticalSurface("fib_surface");
  G4OpticalSurface* optical_surface_fibpolished = new G4OpticalSurface("fibpolished_surface");
  G4OpticalSurface* optical_surface_clad1 = new G4OpticalSurface("clad1_surface");
  G4OpticalSurface* optical_surface_clad2 = new G4OpticalSurface("clad2_surface");
  G4OpticalSurface* optical_surface_cladbrocken = new G4OpticalSurface("cladbrocken_surface");
  G4OpticalSurface* optical_surface_air = new G4OpticalSurface("air_surface");
  G4OpticalSurface* optical_surface_groove = new G4OpticalSurface("groove_surface");
  G4OpticalSurface* optical_surface_groove1 = new G4OpticalSurface("groove1_surface");
  G4OpticalSurface* optical_surface_grease = new G4OpticalSurface("grease_surface");
  G4OpticalSurface* optical_surface_deposit = new G4OpticalSurface("deposit_surface");
  G4OpticalSurface* optical_surface_SiPM = new G4OpticalSurface("SiPM_surface");
  G4OpticalSurface* optical_surface_Mylar = new G4OpticalSurface("Mylar_surface");
  G4OpticalSurface* optical_surface_Epoxy = new G4OpticalSurface("Epoxy_surface");
  G4OpticalSurface* optical_surface_Epoxy2 = new G4OpticalSurface("Epoxy2_surface");
  G4OpticalSurface* optical_surface_LightGuide = new G4OpticalSurface("LightGuide_surface");
  G4OpticalSurface* optical_surface_Glue = new G4OpticalSurface("Glue_surface");
  G4OpticalSurface* optical_surface_Glue_0 = new G4OpticalSurface("Glue0_surface");
  
  optical_surface_fib->SetType(dielectric_dielectric);
  optical_surface_fibpolished->SetType(dielectric_dielectric);
  optical_surface_clad1->SetType(dielectric_dielectric);
  optical_surface_clad2->SetType(dielectric_dielectric);
  optical_surface_cladbrocken->SetType(dielectric_dielectric);
  optical_surface_air->SetType(dielectric_dielectric);
  optical_surface_groove->SetType(dielectric_dielectric);
  optical_surface_groove1->SetType(dielectric_dielectric);
  optical_surface_deposit->SetType(dielectric_metal);
  optical_surface_SiPM->SetType(dielectric_dielectric);
  //  optical_surface_SiPM->SetType(dielectric_metal);
  optical_surface_Mylar->SetType(dielectric_dielectric);
  optical_surface_Epoxy->SetType(dielectric_dielectric);
  optical_surface_grease->SetType(dielectric_dielectric);
  optical_surface_Epoxy2->SetType(dielectric_dielectric);
  optical_surface_LightGuide->SetType(dielectric_dielectric);
  
  
  if(GlueMaterial==Aluminum){
    optical_surface_Glue->SetType(dielectric_metal);
    optical_surface_Glue->SetModel(unified);
    // optical_surface_Glue->SetFinish(etchedair);
       optical_surface_Glue->SetFinish(polishedfrontpainted);
     optical_surface_Glue->SetSigmaAlpha(1.0);
  }else{ 

    optical_surface_Glue->SetType(dielectric_dielectric);
    optical_surface_Glue->SetModel(unified);
    optical_surface_Glue->SetFinish(etchedair);
}
  
  
  
  

  
 
  
  optical_surface_fibpolished->SetModel(glisur);
  optical_surface_fibpolished->SetFinish(polishedair);
  optical_surface_fibpolished->SetPolish(0.7);  //only with glisur model
  
  //  optical_surface_clad1->SetModel(unified); //original
  //  optical_surface_clad1->SetFinish(etchedair); //original

  // optical_surface_clad2->SetModel(unified); //original
  //  optical_surface_clad2->SetFinish(etchedair); //original

  // optical_surface_fib->SetModel(glisur);//original
  //  optical_surface_fib->SetFinish(ground);//original
  // optical_surface_fib->SetPolish(0.999); //original


 
  ////default in order to get 7.3% of trapping efficiency/////////
  /*
  optical_surface_fib->SetModel(glisur);
  optical_surface_fib->SetFinish(ground);
  optical_surface_fib->SetPolish(0.985);  //only with glisur model
  
  optical_surface_clad1->SetModel(glisur);
  optical_surface_clad1->SetFinish(ground);
  if(clad2){optical_surface_clad1->SetPolish(0.98);}  //only with glisur model, w/o clad2
  else{optical_surface_clad1->SetPolish(0.5);}  //only with glisur model

  optical_surface_clad2->SetModel(glisur);
  optical_surface_clad2->SetFinish(ground);
  optical_surface_clad2->SetPolish(0.5);  //only with glisur model
  */
  //////////////////
  // Start: Test for checking the effect of the polishing in the attenuation length.
  
  optical_surface_fib->SetModel(glisur);
  optical_surface_fib->SetFinish(polished);
  optical_surface_fib->SetPolish(1);  //only with glisur model
  
  optical_surface_clad1->SetModel(glisur);
  optical_surface_clad1->SetFinish(polished);
  if(clad2){optical_surface_clad1->SetPolish(1);}  //only with glisur model, w/o clad2
  else{optical_surface_clad1->SetPolish(1);}  //only with glisur model

  optical_surface_clad2->SetModel(glisur);
  optical_surface_clad2->SetFinish(polished);
  optical_surface_clad2->SetPolish(1);  //only with glisur model
   
  // End: Test for checking the effect of the polishing in the attenuation length.
  //////////////////
  
  optical_surface_cladbrocken->SetModel(glisur);
  optical_surface_cladbrocken->SetFinish(ground);
  optical_surface_cladbrocken->SetPolish(0.);
  
  optical_surface_air->SetModel(glisur);
  optical_surface_air->SetFinish(polished);
       
  optical_surface_groove->SetModel(unified);
  optical_surface_groove->SetFinish(groundair);
  
  optical_surface_groove1->SetModel(glisur);
  optical_surface_groove1->SetPolish(0.5);
  optical_surface_groove1->SetFinish(groundair);
  
  optical_surface_deposit->SetModel(glisur);
  optical_surface_deposit->SetFinish(ground);
  optical_surface_deposit->SetPolish(0.9);
       
  optical_surface_SiPM->SetModel(unified);
  optical_surface_SiPM->SetFinish(polished);
       
  optical_surface_Mylar->SetModel(unified);
  optical_surface_Mylar->SetFinish(polished);
  optical_surface_Mylar->SetPolish(1);
  
  optical_surface_Epoxy->SetModel(unified);
  optical_surface_Epoxy->SetFinish(etchedair);
  
  optical_surface_grease->SetModel(glisur);
  optical_surface_grease->SetFinish(ground);
  optical_surface_grease->SetPolish(0.);
  
  optical_surface_Epoxy2->SetModel(glisur);
  optical_surface_Epoxy2->SetFinish(polishedair);
  
  optical_surface_LightGuide->SetModel(unified);
  optical_surface_LightGuide->SetFinish(etchedair);
  
  
  

  
  //------------------------------------------------------ volumes
  
  //------------------------------ experimental hall (world volume)
  //------------------------------ beam line along x axis
  
  
  
  //  if(muon_flag)envMaterial=vacuum;
  
  G4double expHall_x = 6.0*m;
  G4double expHall_y = 6.0*m;
  G4double expHall_z = 6.0*m;
  G4Box* experimentalHall_box  = new G4Box("expHall_box",expHall_x,expHall_y,expHall_z);
  experimentalHall_log = new G4LogicalVolume(experimentalHall_box,envMaterial,"expHall_log",0,0,0);
  experimentalHall_phys = new G4PVPlacement(0,G4ThreeVector(),experimentalHall_log,"expHall",0,false,0);
  
  

  
  //-------------------------Fiber
  

  
  G4double fibershift=0.;//2*fibdim;
  
  G4double gluethickness;
  //  if(GlueMaterial==envMaterial)gluethickness=2.*mm;
  if(GlueMaterial==Epoxy || GlueMaterial==envMaterial)gluethickness=0.002*mm;
  if(GlueMaterial==Aluminum)gluethickness=0.0005*mm;
  
  G4double Glue_x=FiberLength;
  G4double Glue1_x=1.0*mm;//2.5mm//optical grease
  G4double Glue2_x=FiberLength-Glue1_x;
  G4double Glue3_x=0.1*mm;// brocken clad
  G4double Glue_y=2*fibdim+gluethickness;//
  G4double Glue_z=2*fibdim+gluethickness;
  G4double GluePos_x=0.;
  G4double GluePos_y=0.;
  G4double GluePos_z=0.;
  G4double Clad2_x = FiberLength;
  G4double Clad2_y = fibdim;
  G4double Clad2_z = fibdim;
  G4double Glue3Pos_x=Glue1_x-Glue3_x;
 
  G4Box* Glue = new G4Box("Glue",Glue_x,Glue_y,Glue_z);
  logicGlue = new G4LogicalVolume( Glue,GlueMaterial,"logGlue");
  if(fiberflag)physGlue = new G4PVPlacement(0,G4ThreeVector(GluePos_x,GluePos_y,GluePos_z), logicGlue,"Glue",experimentalHall_log,false,0);
  
  
  
  
  G4double Clad2Pos_x=0.*cm;//-8.e-3*mm;//0.*cm;
  G4double Clad2Pos_y=0.*mm;
  G4double Clad2Pos_z=0.*mm;//1.525*cm;   
  
  
  
  G4Box* Clad2 = new G4Box("Clad2",Clad2_x,Clad2_y,Clad2_z);

  logicClad2 = new G4LogicalVolume( Clad2,FluorAcrylic,"logClad2");
  logicClad2_1 = new G4LogicalVolume( Clad2,FluorAcrylic,"logClad2_1");
  logicClad2_2 = new G4LogicalVolume( Clad2,FluorAcrylic,"logClad2_2");
  
    
  if(clad2)physClad2 = new G4PVPlacement(0,G4ThreeVector(Clad2Pos_x,Clad2Pos_y,Clad2Pos_z), logicClad2,"Clad2",logicGlue,false,0);
  
  //  physClad2 = new G4PVPlacement(0,G4ThreeVector(Clad2Pos_x,Clad2Pos_y-fibdim-gluethickness,Clad2Pos_z), logicClad2,"Clad2",logicGlue,false,0);
  // physClad2_1 = new G4PVPlacement(0,G4ThreeVector(Clad2Pos_x,Clad2Pos_y+fibdim+gluethickness,Clad2Pos_z+fibdim+gluethickness), logicClad2_1,"Clad2_1",logicGlue,false,0);
  // physClad2_2 = new G4PVPlacement(0,G4ThreeVector(Clad2Pos_x,Clad2Pos_y+fibdim+gluethickness,Clad2Pos_z-(fibdim+gluethickness)), logicClad2_2,"Clad2_2",logicGlue,false,0);
  
  
  
  G4double Clad1_x = FiberLength;
  G4double Clad1_y = fibdim-coating2_deep;
  G4double Clad1_z = fibdim-coating2_deep;
  G4double Clad1Pos_x=0.*cm;
  G4double Clad1Pos_y=0.*mm;
  G4double Clad1Pos_z=0.*mm;//1.525*cm;   
  
  
  
  G4Box* Clad1 = new G4Box("Clad1_box",Clad1_x,Clad1_y,Clad1_z);
  
  logicClad1 = new G4LogicalVolume( Clad1,Acrylic,"logClad1");
  logicClad1_1 = new G4LogicalVolume( Clad1,Acrylic,"logClad1_1");
  logicClad1_2 = new G4LogicalVolume( Clad1,Acrylic,"logClad1_2");
  
  
  
  if(clad2)physClad1 = new G4PVPlacement(0,G4ThreeVector(Clad1Pos_x,Clad1Pos_y,Clad1Pos_z), logicClad1,"Clad1",logicClad2,false,0);
  if(!clad2)physClad1 = new G4PVPlacement(0,G4ThreeVector(Clad1Pos_x,Clad1Pos_y,Clad1Pos_z), logicClad1,"Clad1",logicGlue,false,0);
  physClad1_1 = new G4PVPlacement(0,G4ThreeVector(Clad1Pos_x,Clad1Pos_y,Clad1Pos_z), logicClad1_1,"Clad1_1",logicClad2_1,false,0);
  physClad1_2 = new G4PVPlacement(0,G4ThreeVector(Clad1Pos_x,Clad1Pos_y,Clad1Pos_z), logicClad1_2,"Clad1_2",logicClad2_2,false,0); 
  
  
  
  
  G4double FiberCore_x = FiberLength;
  G4double FiberCore_y = fibdim-coating_deep-coating2_deep;
  G4double FiberCore_z = fibdim-coating_deep-coating2_deep;
  G4double FiberCorePos_x=0.*cm;
  G4double FiberCorePos_y=0.*mm;
  G4double FiberCorePos_z=0.*mm;
  
    
  
  G4Box* FiberCore = new G4Box("FiberCore_box",FiberCore_x,FiberCore_y,FiberCore_z);
  

  logicFiberCore = new G4LogicalVolume( FiberCore,scintBCF12,"logFiberCore");
  logicFiberCore_1 = new G4LogicalVolume( FiberCore,scintBCF12,"logFiberCore_1");
  logicFiberCore_2 = new G4LogicalVolume( FiberCore,scintBCF12,"logFiberCore_2");
  
  physFiberCore = new G4PVPlacement(0,G4ThreeVector(FiberCorePos_x,FiberCorePos_y,FiberCorePos_z), logicFiberCore,"FiberCore",logicClad1,false,0);
  physFiberCore_1 = new G4PVPlacement(0,G4ThreeVector(FiberCorePos_x,FiberCorePos_y,FiberCorePos_z), logicFiberCore_1,"FiberCore_1",logicClad1_1,false,0);
  physFiberCore_2 = new G4PVPlacement(0,G4ThreeVector(FiberCorePos_x,FiberCorePos_y,FiberCorePos_z), logicFiberCore_2,"FiberCore_2",logicClad1_2,false,0);
  
  
  
  /////--------- Degrader

  G4double degrader_x =40.*mm;
  G4double degrader_y =40.*mm;
  G4double degrader_z =0.05*mm;
  G4double maindegrader_z =0.095*mm;
  G4double degraderPos_x=0.*cm;
  G4double degraderPos_y=0.*mm;
  G4double degraderPos_z=-10.*mm;
  
  
    
  G4Box* Degrader = new G4Box("degrader_box",degrader_x,degrader_y,degrader_z);
  logicDegrader = new G4LogicalVolume( Degrader,Mylar,"logDegrader");
  
  if(degrader_flag)physDegrader = new G4PVPlacement(0,G4ThreeVector(degraderPos_x,degraderPos_y,degraderPos_z), logicDegrader,"degrader",experimentalHall_log,false,0);
  
  G4Box* MainDegrader = new G4Box("maindegrader_box",degrader_x,degrader_y,maindegrader_z);
  logicMainDegrader = new G4LogicalVolume( MainDegrader,Mylar,"logMainDegrader");
  
  if(degrader_flag)physMainDegrader = new G4PVPlacement(0,G4ThreeVector(degraderPos_x,degraderPos_y,-140.*mm), logicMainDegrader,"Maindegrader",experimentalHall_log,false,0);
  
  

  
  
  
  
  
  //----------------------------------- Aluminum deposit
  
  if(deposit){
    
    G4double Deposit_x = 0.00025*mm;
    G4double Deposit_y = Clad2_y;
    G4double Deposit_z = Clad2_z;
    G4double DepositPos_x=-(Clad2_x+Clad2Pos_x)-Deposit_x;
    G4double DepositPos_y=0.*mm+shift_y;
    G4double DepositPos_z=shift_z;       
    
    

    G4Box* Deposit = new G4Box("Deposit_box",Deposit_x,Deposit_y,Deposit_z);
    logicDeposit = new G4LogicalVolume( Deposit,Aluminum,"logDeposit");
    logicDeposit_1 = new G4LogicalVolume( Deposit,Aluminum,"logDeposit_1");
    logicDeposit_2 = new G4LogicalVolume( Deposit,Aluminum,"logDeposit_2");

    // physDeposit = new G4PVPlacement(0,G4ThreeVector(DepositPos_x,DepositPos_y,DepositPos_z), logicDeposit,"Deposit",logicFiber,false,0);
    physDeposit = new G4PVPlacement(0,G4ThreeVector(DepositPos_x,DepositPos_y,DepositPos_z), logicDeposit,"Deposit",experimentalHall_log,false,0);
    

      
      physDeposit_1 = new G4PVPlacement(0,G4ThreeVector(DepositPos_x,DepositPos_y-2*fibdim-gluethickness,DepositPos_z+fibershift), logicDeposit_1,"Deposit_1",experimentalHall_log,false,0);
      physDeposit_2 = new G4PVPlacement(0,G4ThreeVector(DepositPos_x,DepositPos_y+2*fibdim+gluethickness,DepositPos_z+fibershift), logicDeposit_2,"Deposit_2",experimentalHall_log,false,0);
      
      visDeposit_1=new G4VisAttributes(G4Colour(0.3,0.3,0.3));
      visDeposit_1->SetVisibility(true);
      visDeposit_1->SetForceSolid(true);
      logicDeposit_1->SetVisAttributes(visDeposit_1);
      
      
      
      visDeposit_2=new G4VisAttributes(G4Colour(0.3,0.3,0.3));
      visDeposit_2->SetVisibility(true);
      visDeposit_2->SetForceSolid(true);
      logicDeposit_2->SetVisAttributes(visDeposit_2);
      

    
    
    
    visDeposit=new G4VisAttributes(G4Colour(0.3,0.3,0.3));
    visDeposit->SetVisibility(true);
    visDeposit->SetForceSolid(true);
    logicDeposit->SetVisAttributes(visDeposit);
    
  }
  




  
  
  //-------------------------SiPM
  
  ff=1;  
  if(pixdim==0.1*mm)ff=0.78;
  if(pixdim==0.05*mm)ff=0.74;
  if(pixdim==0.025*mm)ff=0.65;



  G4double SiPM_shiftx=0.05*mm;
  G4double SiPM_x = 0.5*mm;
  G4double SiPM_y =lsipm/2.;
  G4double SiPM_z =lsipm/2.;
  G4double LightGuide_dx1=fibdim;
  G4double LightGuide_dy1=fibdim;
  G4double LightGuide_dx2=1.*mm;//SiPM_z;
  G4double LightGuide_dy2=1.*mm;//SiPM_y;
  G4double LightGuide_dz=SiPM_shiftx/2.;
  G4double LightGuide_posx=FiberLength+LightGuide_dz;
  G4double SiPMWin_x = 0.25*mm;
  G4double SiPMWin_y =0.9*mm;
  G4double SiPMWin_z =0.9*mm;
  G4double SiPMCase_x=SiPM_x+SiPMWin_x;
  G4double SiPMCase_z=1.*mm;
  G4double SiPMCase_y=1.*mm;
  G4double WhiteFiber_x=75.*cm;
  G4double WhiteFiber_y=0.25*mm;
  G4double WhiteFiber_shiftz=0.15*mm;
  G4double WhiteFiber_z=0.25*mm;
  G4double WhiteFiber_xpos=LightGuide_posx+LightGuide_dz+WhiteFiber_x;
  G4double SiPMCase_xpos=FiberLength+2*LightGuide_dz+SiPM_x+SiPMWin_x;;
  G4double SiPMCase_zpos=0.;
  G4double SiPM_xpos=SiPMCase_x-SiPM_x;
  G4double SiPMWin_xpos=-SiPMCase_x+SiPMWin_x;

  G4RotationMatrix R;
  R.rotateY(90.*deg);




  G4Box* SiPMCase = new G4Box("SiPMCase_box",SiPMCase_x,SiPMCase_y,SiPMCase_z);
  
  logicSiPMCase = new G4LogicalVolume( SiPMCase,Ceramic,"logSiPMCase");
  physSiPMCase = new G4PVPlacement(0,G4ThreeVector(SiPMCase_xpos,0.,SiPMCase_zpos), logicSiPMCase,"SiPMCase",experimentalHall_log,false,0); 
  
  logicSiPMCase_1 = new G4LogicalVolume( SiPMCase,Ceramic,"logSiPMCase_1");
  //  if(!deposit)
  if(twosipm)physSiPMCase_1 = new G4PVPlacement(0,G4ThreeVector(-SiPMCase_xpos,0.,SiPMCase_zpos), logicSiPMCase_1,"SiPMCase_1",experimentalHall_log,false,0); 
  
  
  
  if(SiPMWin_x!=0){
    G4Box* SiPMWin = new G4Box("SiPMWin_box",SiPMWin_x,SiPMWin_y,SiPMWin_z);
    
    logicSiPMWin = new G4LogicalVolume( SiPMWin,Epoxy2,"logSiPMWin");
    physSiPMWin = new G4PVPlacement(0,G4ThreeVector(SiPMWin_xpos,0.,0.), logicSiPMWin,"SiPMWin",logicSiPMCase,false,0); 


    logicSiPMWin_1 = new G4LogicalVolume( SiPMWin,Epoxy2,"logSiPMWin_1");
    physSiPMWin_1 = new G4PVPlacement(0,G4ThreeVector(-SiPMWin_xpos,0.,0.), logicSiPMWin_1,"SiPMWin_1",logicSiPMCase_1,false,0); 
  }
  
  G4Box* SiPM = new G4Box("SiPM_box",SiPM_x,SiPM_y,SiPM_z);
  
  logicSiPM = new G4LogicalVolume( SiPM,silicon,"logSiPM");
  logicSiPM_1 = new G4LogicalVolume( SiPM,silicon,"logSiPM_1");
  logicSiPM_2 = new G4LogicalVolume( SiPM,silicon,"logSiPM_2");
  

  //first SiPM
  physSiPM = new G4PVPlacement(0,G4ThreeVector(SiPM_xpos,0.,0.), logicSiPM,"SiPM",logicSiPMCase,false,0); 
  //second SiPM
  physSiPM_1 = new G4PVPlacement(0,G4ThreeVector(-SiPM_xpos,0.,0.), logicSiPM_1,"SiPM_1",logicSiPMCase_1,false,0); 
  
// physSiPM_2 = new G4PVPlacement(0,G4ThreeVector(40.5,2*fibdim+gluethickness,0.+fibershift), logicSiPM_2,"SiPM_2",experimentalHall_log,false,0); 
  
  



  if(SiPM_shiftx!=0 ){
   
    //    G4Trd* LightGuide_box=new G4Trd("LightGuide",LightGuide_dx1,LightGuide_dx2,LightGuide_dy1,LightGuide_dy2,LightGuide_dz);
    G4Box* LightGuide_box=new G4Box("LightGuide",LightGuide_dx2,LightGuide_dy2,LightGuide_dz);
   
    logicLightGuide=new G4LogicalVolume(LightGuide_box,Epoxy,"logicLightGuide"); 
    physLightGuide=new G4PVPlacement(G4Transform3D(R,G4ThreeVector(LightGuide_posx,0.,0.)),logicLightGuide,"LightGuide",experimentalHall_log,false,0);
    
    logicLightGuide_1=new G4LogicalVolume(LightGuide_box,Epoxy,"logicLightGuide_1"); 
    //    if(!deposit)
    if(twosipm)physLightGuide_1=new G4PVPlacement(G4Transform3D(R,G4ThreeVector(-LightGuide_posx,0.,0.)),logicLightGuide_1,"LightGuide_1",experimentalHall_log,false,1);
    
  
    
  }


 
  G4LogicalSkinSurface *surface_skin_Glue_0 = new G4LogicalSkinSurface("Glue0_surface", logicGlue_0,optical_surface_Glue_0);
  G4LogicalSkinSurface *surface_skin_Glue_01 = new G4LogicalSkinSurface("Glue01_surface", logicGlue_01,optical_surface_Glue_0);
      
  
  int i,j;
  G4double Pixel_x = SiPM_x;
  G4double Pixel_y = (std::sqrt(ff)*SiPM_y/(double)Npix)*mm;
  G4double Pixel_z = (std::sqrt(ff)*SiPM_z/(double)Npix)*mm;
  
  //  G4cout<<"-------------------------------> "<<pixdim<<" "<<lsipm<<G4endl;

  PixelAssembly= new G4AssemblyVolume();
  PixelAssembly_1= new G4AssemblyVolume();
  
  G4Box *Pixel= new G4Box("Pixel",Pixel_x,Pixel_y,Pixel_z);
  G4LogicalVolume *logicPixel= new G4LogicalVolume( Pixel,silicon,"Pixel",0,0,0);
  G4LogicalVolume *logicPixel_1= new G4LogicalVolume( Pixel,silicon,"Pixel_1",0,0,0);
    
  G4double PixelPos_x=0.*mm;
  G4double PixelPos_y;
  G4double PixelPos_z;
  G4ThreeVector pos;


  for(i=0;i<Npix;i++){
    for(j=0;j<Npix;j++){
      
      //    PixelPos_y=-SiPM_y+(Npix/2.-j+Npix)*SiPM_y/(double)Npix;
//	    PixelPos_z=-SiPM_z+(Npix/2.-i+Npix)*SiPM_z/(double)Npix;

      PixelPos_y=-(Npix-(2*i+1))*SiPM_y/Npix;
      PixelPos_z=-(Npix-(2*j+1))*SiPM_z/Npix;

      
      pos.setX(PixelPos_x);
      pos.setY(PixelPos_y);
      pos.setZ(PixelPos_z);
   
      PixelAssembly->AddPlacedVolume(logicPixel,pos,0);
      PixelAssembly_1->AddPlacedVolume(logicPixel_1,pos,0);

    }

}

  pos.setX(0);
  pos.setY(0);
  pos.setZ(0);

  PixelAssembly->MakeImprint(logicSiPM,pos,0,0);
  PixelAssembly_1->MakeImprint(logicSiPM_1,pos,0,0);

       
  //mylar volume between fiber and sipm window (not used now)

  G4double Mylar_x = 0.01*mm;//4.e-3*mm;
  G4double Mylar_y = fibdim;
  G4double Mylar_z = fibdim;
  
  G4Box* Mylar_box = new G4Box("Mylar",Mylar_x,Mylar_y,Mylar_z);
  logicMylar = new G4LogicalVolume( Mylar_box,Mylar,"Mylar");
  // physMylar = new G4PVPlacement(0,G4ThreeVector(Clad2_x-Mylar_x,0.,0.), logicMylar,"Mylar",experimentalHall_log,false,0); 

  //  G4LogicalSkinSurface *surface_skin_Mylar = new G4LogicalSkinSurface("Mylar_surface", logicMylar, optical_surface_Mylar);
  optical_surface_Mylar->SetMaterialPropertiesTable(MPT_Mylar);


  //----------user limits

 
    
    G4double maxStep=0.001*mm;  
    G4double maxStep2=0.0001*mm;  
    G4double maxStep3=0.01*mm;//impostarlo a 1 um per birks effect  
    G4UserLimits *L=new G4UserLimits(maxStep);
    G4UserLimits *L2=new G4UserLimits(maxStep3);
    //   L->SetMaxAllowedStep(maxStep);
 

      logicFiberCore->SetUserLimits(L2);
      logicFiberCore_1->SetUserLimits(L2);
      logicFiberCore_2->SetUserLimits(L2);
 

      logicClad2->SetUserLimits(L);  
      logicClad2_1->SetUserLimits(L);  
      logicClad2_2->SetUserLimits(L);  
      logicClad1->SetUserLimits(L);  
      logicClad1_1->SetUserLimits(L);  
      logicClad1_2->SetUserLimits(L);
      //      logicDegrader->SetUserLimits(L2);
      //      experimentalHall_log->SetUserLimits(L2);
  




          G4UserLimits *L1=new G4UserLimits(maxStep2);
     
	  //      logicGlue->SetUserLimits(L1);
      
	  //      if(deposit)logicDeposit->SetUserLimits(L1);



      
      G4LogicalBorderSurface* surface_in = new G4LogicalBorderSurface("fib_surface_in",physClad1,physFiberCore,optical_surface_fib);
      G4LogicalBorderSurface* surface_out = new G4LogicalBorderSurface("fib_surface_out",physFiberCore,physClad1,optical_surface_fib);
      
      G4LogicalBorderSurface* surface0_in = new G4LogicalBorderSurface("fib0_surface_in",physClad1_0,physFiberCore_0,optical_surface_fib);
      G4LogicalBorderSurface* surface0_out = new G4LogicalBorderSurface("fib0_surface_out",physFiberCore_0,physClad1_0,optical_surface_fib);
      
      G4LogicalBorderSurface* surface_corebrocken_out = new G4LogicalBorderSurface("corebrocken_surface_out",physFiberCore,physGlue_4,optical_surface_cladbrocken);
      G4LogicalBorderSurface* surface_corebrocken_in = new G4LogicalBorderSurface("corebrocken_surface_in",physGlue_4,physFiberCore,optical_surface_cladbrocken);
      
      G4LogicalBorderSurface* surface_clad1brocken_out = new G4LogicalBorderSurface("clad1brocken_surface_out",physClad1,physGlue_4,optical_surface_cladbrocken);
      G4LogicalBorderSurface* surface_clad1brocken_in = new G4LogicalBorderSurface("clad1brocken_surface_in",physGlue_4,physClad1,optical_surface_cladbrocken);
      
      
      
      G4LogicalBorderSurface* surface_clad2brocken_out = new G4LogicalBorderSurface("clad2brocken_surface_out",physClad2,physGlue_3,optical_surface_cladbrocken);
      G4LogicalBorderSurface* surface_clad2brocken_in = new G4LogicalBorderSurface("clad2brocken_surface_in",physGlue_3,physClad2,optical_surface_cladbrocken);

      G4LogicalBorderSurface* surface_reflectivebrocken_out = new G4LogicalBorderSurface("reflective_surface_out",physClad2,physGlue_5,optical_surface_cladbrocken);
      G4LogicalBorderSurface* surface_reflectivebrocken_in = new G4LogicalBorderSurface("reflective_surface_in",physGlue_5,physClad2,optical_surface_cladbrocken);

      G4LogicalBorderSurface* surface_reflectivebrocken1_out = new G4LogicalBorderSurface("reflective_surface1_out",physClad1,physGlue_5,optical_surface_cladbrocken);
      G4LogicalBorderSurface* surface_reflectivebrocken1_in = new G4LogicalBorderSurface("reflective_surface1_in",physGlue_5,physClad1,optical_surface_cladbrocken);

      
      G4LogicalBorderSurface* surface_brocken_out = new G4LogicalBorderSurface("brocken_surface_out",experimentalHall_phys,physGlue_3,optical_surface_cladbrocken);
      G4LogicalBorderSurface* surface_brocken_in = new G4LogicalBorderSurface("brocken_surface_in",physGlue_3,experimentalHall_phys,optical_surface_cladbrocken);
      
	
      G4LogicalBorderSurface* surface_air_out = new G4LogicalBorderSurface("air_surface_out",experimentalHall_phys,physGlue,optical_surface_Glue);
      G4LogicalBorderSurface* surface_air_in = new G4LogicalBorderSurface("air_surface_in",physGlue,experimentalHall_phys,optical_surface_Glue);  
      
      
    
      
      G4LogicalBorderSurface* surface_glue2_out = new G4LogicalBorderSurface("glue2_surface_out",physGlue_2,physGlue_1,optical_surface_groove1);
      G4LogicalBorderSurface* surface_glue2_in = new G4LogicalBorderSurface("glue2_surface_in",physGlue_1,physGlue_2,optical_surface_groove1);
      
      G4LogicalBorderSurface* surface_greaseair_out = new G4LogicalBorderSurface("greaseair_surface_out",physGlue_1,experimentalHall_phys,optical_surface_grease);
      G4LogicalBorderSurface* surface_greaseair_in = new G4LogicalBorderSurface("greaseair_surface_in",experimentalHall_phys,physGlue_1,optical_surface_grease);
      
      
    
      


	if(clad2){

	  if(GlueMaterial==Aluminum){
	    
	    G4LogicalBorderSurface* surface_glue_out = new G4LogicalBorderSurface("glue_surface_out",physClad2,physGlue,optical_surface_Glue);
	    G4LogicalBorderSurface* surface_glue_in = new G4LogicalBorderSurface("glue_surface_in",physGlue,physClad2,optical_surface_Glue);
	  }else{
	    G4LogicalBorderSurface* surface_glue_out = new G4LogicalBorderSurface("glue_surface_out",physClad2,physGlue,optical_surface_clad2);
	    G4LogicalBorderSurface* surface_glue_in = new G4LogicalBorderSurface("glue_surface_in",physGlue,physClad2,optical_surface_clad2);
	  }
	  G4LogicalBorderSurface* surface_clad_out = new G4LogicalBorderSurface("clad_surface_out",physClad1,physClad2,optical_surface_clad1);
	  G4LogicalBorderSurface* surface_clad_in = new G4LogicalBorderSurface("clad_surface_in",physClad2,physClad1,optical_surface_clad1);
	  
	  G4LogicalBorderSurface* surface0_clad_out = new G4LogicalBorderSurface("clad0_surface_out",physClad1_0,physClad2_0,optical_surface_clad1);
	  G4LogicalBorderSurface* surface0_clad_in = new G4LogicalBorderSurface("clad0_surface_in",physClad2_0,physClad1_0,optical_surface_clad1);

	}else{

	  if(GlueMaterial==Aluminum){
	    G4LogicalBorderSurface* surface_glue_out = new G4LogicalBorderSurface("glue_surface_out",physClad1,physGlue,optical_surface_Glue);
	    G4LogicalBorderSurface* surface_glue_in = new G4LogicalBorderSurface("glue_surface_in",physGlue,physClad1,optical_surface_Glue);

	  }else{
	    G4LogicalBorderSurface* surface_glue_out = new G4LogicalBorderSurface("glue_surface_out",physClad1,physGlue,optical_surface_clad1);
	    G4LogicalBorderSurface* surface_glue_in = new G4LogicalBorderSurface("glue_surface_in",physGlue,physClad1,optical_surface_clad1);
	  }
	}

      
    
      G4LogicalBorderSurface* surface_fiblightguide_in = new G4LogicalBorderSurface("fiblightguide_surface_in",physLightGuide,physFiberCore,optical_surface_fibpolished);
      G4LogicalBorderSurface* surface_fiblightguide_out = new G4LogicalBorderSurface("fiblightguide_surface_out",physFiberCore,physLightGuide,optical_surface_fibpolished);

   G4LogicalBorderSurface* surface1_fiblightguide_in = new G4LogicalBorderSurface("fiblightguide1_surface_in",physLightGuide_1,physFiberCore,optical_surface_fibpolished);
      G4LogicalBorderSurface* surface1_fiblightguide_out = new G4LogicalBorderSurface("fiblightguide1_surface_out",physFiberCore_1,physLightGuide,optical_surface_fibpolished);
      
      G4LogicalBorderSurface* surface_whitefiber_in = new G4LogicalBorderSurface("whitefiber_surface_in",physLightGuide,physWhiteFiber,optical_surface_fibpolished);
      G4LogicalBorderSurface* surface_whitefiber_out = new G4LogicalBorderSurface("whitefiber_surface_out",physWhiteFiber,physLightGuide,optical_surface_fibpolished);
      
      
      if(SiPM_shiftx==0){
	
	G4LogicalBorderSurface* surface_fibsipm_in = new G4LogicalBorderSurface("fibsipm_surface_in",physSiPMWin,physFiberCore,optical_surface_fibpolished);
	G4LogicalBorderSurface* surface_fibsipm_out = new G4LogicalBorderSurface("fibsipm_surface_out",physFiberCore,physSiPMWin,optical_surface_fibpolished);
	
      }
      
      G4LogicalBorderSurface* surface_lightguidesipmwin_in = new G4LogicalBorderSurface("sipmwinlightguide_surface_in",physLightGuide,physSiPMWin,optical_surface_Epoxy2);
      G4LogicalBorderSurface* surface_lightguidesipmwin_out = new G4LogicalBorderSurface("sipmwinlightguide_surface_out",physSiPMWin,physLightGuide,optical_surface_Epoxy2);

      G4LogicalBorderSurface* surface1_lightguidesipmwin_in = new G4LogicalBorderSurface("sipmwinlightguide1_surface_in",physLightGuide_1,physSiPMWin_1,optical_surface_Epoxy2);
      G4LogicalBorderSurface* surface1_lightguidesipmwin_out = new G4LogicalBorderSurface("sipmwinlightguide1_surface_out",physSiPMWin_1,physLightGuide_1,optical_surface_Epoxy2);
      
      
    
	
	
	G4LogicalBorderSurface* surface_deposit_in = new G4LogicalBorderSurface("deposit_surface_in",physDeposit,physFiberCore,optical_surface_deposit);
	G4LogicalBorderSurface* surface_deposit_out = new G4LogicalBorderSurface("deposit_surface_out",physFiberCore,physDeposit,optical_surface_deposit);
	
	G4LogicalBorderSurface* surface_depositclad1_in = new G4LogicalBorderSurface("depositclad1_surface_in",physDeposit,physClad1,optical_surface_deposit);
	G4LogicalBorderSurface* surface_depositclad1_out = new G4LogicalBorderSurface("depositclad1_surface_out",physClad1,physDeposit,optical_surface_deposit);
	if(clad2){	
	  G4LogicalBorderSurface* surface_depositclad2_in = new G4LogicalBorderSurface("depositclad2_surface_in",physDeposit,physClad2,optical_surface_deposit);
	  G4LogicalBorderSurface* surface_depositclad2_out = new G4LogicalBorderSurface("depositclad2_surface_out",physClad2,physDeposit,optical_surface_deposit);
	}
      
      
       
   
    
  
      
      G4LogicalBorderSurface* surface_in_1 = new G4LogicalBorderSurface("fib_surface_in_1",physClad1_1,physFiberCore_1,optical_surface_clad1);
      G4LogicalBorderSurface* surface_out_1 = new G4LogicalBorderSurface("fib_surface_out_1",physFiberCore_1,physClad1_1,optical_surface_fib);
      
      G4LogicalBorderSurface* surface_in_2 = new G4LogicalBorderSurface("fib_surface_in_2",physClad1_2,physFiberCore_2,optical_surface_clad1);
      G4LogicalBorderSurface* surface_out_2 = new G4LogicalBorderSurface("fib_surface_out_2",physFiberCore_2,physClad1_2,optical_surface_fib);
      
      
      
      //relative borders
      
  
	
	
	G4LogicalBorderSurface* surface_2_0_out = new G4LogicalBorderSurface("2_0_surface_out",physGlue,physClad2_2,optical_surface_clad2);
	G4LogicalBorderSurface* surface_2_0_in = new G4LogicalBorderSurface("2_0_surface_in",physClad2_2,physGlue,optical_surface_clad2);

	G4LogicalBorderSurface* surface_3_0_out = new G4LogicalBorderSurface("3_0_surface_out",physGlue,physClad2_1,optical_surface_clad2);
	G4LogicalBorderSurface* surface_3_0_in = new G4LogicalBorderSurface("3_0_surface_in",physClad2_1,physGlue,optical_surface_clad2);
	
	G4LogicalBorderSurface* surface_clad_out_1 = new G4LogicalBorderSurface("clad_surface_out_1",physClad1_1,physClad2_1,optical_surface_clad1);
	G4LogicalBorderSurface* surface_clad_in_1 = new G4LogicalBorderSurface("clad_surface_in_1",physClad2_1,physClad1_1,optical_surface_clad2);
	
	G4LogicalBorderSurface* surface_clad_out_2 = new G4LogicalBorderSurface("clad_surface_out_2",physClad1_2,physClad2_2,optical_surface_clad1);
	G4LogicalBorderSurface* surface_clad_in_2 = new G4LogicalBorderSurface("clad_surface_in_2",physClad2_2,physClad1_2,optical_surface_clad2);
	
	
   
  


  //------------Vis attributes
  
  visClad1=new G4VisAttributes();
  //  visClad1->SetColour(99./255.,151./255.,208./255.,0.3);
  visClad1->SetColour(13./255.,223./255.,13./255.,0.7);
  visClad1->SetVisibility(true);
  visClad1->SetForceSolid(true);
  logicClad1->SetVisAttributes(visClad1);

    visClad1_1=new G4VisAttributes();
  visClad1_1->SetColour(99./255.,151./255.,208./255.,0.3);
  visClad1_1->SetVisibility(true);
  visClad1_1->SetForceSolid(true);
  logicClad1_1->SetVisAttributes(visClad1_1);

  visClad1_2=new G4VisAttributes();
  visClad1_2->SetColour(99./255.,151./255.,208./255.,0.3);
  visClad1_2->SetVisibility(true);
  visClad1_2->SetForceSolid(true);
  logicClad1_2->SetVisAttributes(visClad1_2);

  
  visClad2=new G4VisAttributes();
  //  visClad2->SetColour(171./255.,205./255.,239./255.,0.3);
  visClad2->SetColour(2531./255.,8./255.,8./255.,0.7);
  visClad2->SetVisibility(true);
  visClad2->SetForceSolid(true);
  logicClad2->SetVisAttributes(visClad2);


  visClad2_1=new G4VisAttributes();
  visClad2_1->SetColour(171./255.,205./255.,239./255.,0.3);
  visClad2_1->SetVisibility(true);
  visClad2_1->SetForceSolid(true);
  logicClad2_1->SetVisAttributes(visClad2_1);

  visClad2_2=new G4VisAttributes();
  visClad2_2->SetColour(171./255.,205./255.,239./255.,0.3);
  visClad2_2->SetVisibility(true);
  visClad2_2->SetForceSolid(true);
  logicClad2_2->SetVisAttributes(visClad2_2);

 
  
   
  visFiberCore=new G4VisAttributes();
  visFiberCore->SetColour(0.,191./255.,1.,0.3);
  visFiberCore->SetVisibility(true);
  visFiberCore->SetForceSolid(true);
  logicFiberCore->SetVisAttributes(visFiberCore);
  // logicFiberCore_0->SetVisAttributes(visFiberCore);


    visFiberCore_1=new G4VisAttributes();
  visFiberCore_1->SetColour(0.,191./255.,1.,0.3);
  visFiberCore_1->SetVisibility(true);
  visFiberCore_1->SetForceSolid(true);
  logicFiberCore_1->SetVisAttributes(visFiberCore_1);

  visFiberCore_2=new G4VisAttributes();
  visFiberCore_2->SetColour(0.,191./255.,1.,0.3);
  visFiberCore_2->SetVisibility(true);
  visFiberCore_2->SetForceSolid(true);
  logicFiberCore_2->SetVisAttributes(visFiberCore_2);

 
  
    
    if(SiPM_shiftx!=0){
      
      visLightGuide=new G4VisAttributes();
      visLightGuide->SetColour(0.,191./255.,1.,0.1);
      visLightGuide->SetVisibility(true);
      visLightGuide->SetForceSolid(true);
      logicLightGuide->SetVisAttributes(visLightGuide);
      
    }
    
    
    if(SiPMWin_x!=0){
      
      visSiPMWin=new G4VisAttributes();
      visSiPMWin->SetColour(0.,191./255.,1.,0.2);
      visSiPMWin->SetVisibility(true);
      visSiPMWin->SetForceSolid(true);
      logicSiPMWin->SetVisAttributes(visSiPMWin);
      
    }
    
    
    visSiPMCase=new G4VisAttributes();
    visSiPMCase->SetColour(5./255.,4./255.,2./255.,0.4);
    visSiPMCase->SetVisibility(true);
    visSiPMCase->SetForceSolid(true);
    logicSiPMCase->SetVisAttributes(visSiPMCase);

  visSiPM=new G4VisAttributes(G4Colour(47./255.,79./255.,79./255.));;
  visSiPM->SetVisibility(true);
  visSiPM->SetForceSolid(true);
  logicSiPM->SetVisAttributes(visSiPM);


    
  
  visGlue=new G4VisAttributes();
  visGlue->SetColour(0.,191./255.,1.,0.1);
  visGlue->SetVisibility(false);
  visGlue->SetForceSolid(true);
  logicGlue->SetVisAttributes(visGlue);
 

  /*

  visSiPM_1=new G4VisAttributes(G4Colour(47./255.,79./255.,79./255.));;
  visSiPM_1->SetVisibility(true);
  visSiPM_1->SetForceSolid(true);
  logicSiPM_1->SetVisAttributes(visSiPM_1);
  
  visSiPM_2=new G4VisAttributes(G4Colour(47./255.,79./255.,79./255.));;
  visSiPM_2->SetVisibility(true);
  visSiPM_2->SetForceSolid(true);
  logicSiPM_2->SetVisAttributes(visSiPM_2);

 */
  
  /*  G4VisAttributes* visPixel=new G4VisAttributes(G4Colour(47./255.,79./255.,79./255.));;
  visPixel->SetVisibility(true);
  visPixel->SetForceSolid(true);
  logicPixel->SetVisAttributes(visPixel);*/

  
  
  return experimentalHall_phys;

   

    }

