#include "TF1.h"
#include "TMath.h"
#include "RooLandau.h"
#include "RooPoisson.h"
#include "RooRealVar.h"
#include "RooDataHist.h"
#include "RooPlot.h"
#include "RooNumConvPdf.h"
#include "RooFitResult.h"
#include "RooAbsReal.h"
#include "RooProdPdf.h"
#include "RooFormulaVar.h"
#include "RooGaussian.h"
#include "RooProduct.h"
//#include "RooBinomial.hh"

using namespace RooFit;

void fitphoton(TString infile /*file monte carlo*/){

  ////RooFit functions

  RooRealVar sigma("#sigma","#sigma",0.,10.);
  RooRealVar sigma1("#sigma1","#sigma1",0.,10.);
  //RooRealVar LY("LY","light yield",8000.,0,12000);
  // RooRealVar N("N_{Ph}","N_{ph}",0.,100.); ///Attenzione! Questo è l'osservabile e gli estremi non devono essere troppo diversi dal range in cui misuri o simuli l'osservabile stesso...
  RooRealVar N("N_{Ph}","N_{ph}",0.,500.); ///Attenzione! Questo è l'osservabile e gli estremi non devono essere troppo diversi dal range in cui misuri o simuli l'osservabile stesso...
  RooRealVar MPV("MPV","MPV_{landau}",0.,200.);
  RooRealVar Nphot_exp("Nph_exp","Nph_{exp}",-1.,1.);
  RooLandau Landau("Landau","edep distribution",N,MPV,sigma);
  // RooPoisson Poisson("Poisson","ph distribution",N,Nphot_exp);
  RooGaussian Gauss("Gauss","ph distribution",N,Nphot_exp,sigma1);
  RooFFTConvPdf conv("conv","convolution",N,Landau,Gauss);
  ///


  ///i parametri Nphot_exp e MPV tendono ad essere fortemente correlati, si può mettere un forte constraint su uno dei due 

  TFile* file =TFile::Open(infile);
  TTree* tree=(TTree*)file->Get("FiberTree");
  
  //  TH1F* h=new TH1F("h","edge counter",101,0,100);
  TH1F* h=new TH1F("h","edge counter",501,0,500);

  Int_t nph,nph1;

  //  tree->SetBranchAddress("EdgeCounter",&nph);//numero di fotoni alla fine della fibra...
 tree->SetBranchAddress("EdgeCounter",&nph);//numero di fotoni alla fine della fibra...
 tree->SetBranchAddress("EdgeCounter1",&nph1);//numero di fotoni alla fine della fibra...
  Int_t Nentries=tree->GetEntries();

  for(Int_t k=0;k<Nentries;k++){

    tree->GetEntry(k);

    if(nph>0)h->Fill((Double_t)nph+nph1);


  }

  RooDataHist *PhotHist=new RooDataHist("data2","dataset2",N,Import(*h));

  //  N.setBins(101);
  N.setBins(501);

  MPV.setVal(20.);
  Nphot_exp.setVal(0.);
  
  //Nphot_exp.setConstant();
  //sigma.setVal(1.);
  //sigma1.setVal(0.1);
  sigma.setVal(1.);
  sigma1.setVal(5.);
  

  conv.fitTo(*PhotHist);



  RooPlot* frame=N.frame();
  PhotHist->plotOn(frame);//,Normalization(GenCount->GetEntries(),RooAbsReal::NumEvent));
  conv.plotOn(frame);//,Normalization(GenCount->GetEntries(),RooAbsReal::NumEvent));

  frame->Draw();

}
