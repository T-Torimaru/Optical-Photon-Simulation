#include <iostream.h>
#include <Riostream.h>
#include "TH1D.h"
#include "TTree.h"
#include "TString.h"
#include "TMath.h"
#include "TROOT.h"
#include "TF1.h"
#include "TGraphErrors.h"
#include "TGraph.h"
#include "TCanvas.h"



void Attenuation(Int_t nfile){

  
  //  
  //  TFile *file2 =TFile::Open(rootfile2);
  
  
  TFile *file1 =TFile::Open(Form("plot%d_fiber250_nodeposit_param.root",nfile));
  
  //  TTree *tree2=(TTree*)file2->Get("Ttot");
  TTree *tree1=(TTree*)file1->Get("FiberTree");                                         
  //TH1F *h1=(TH1F*)file1->Get("hdata");                                                                                                
  
  tree1->Draw("SiPMCounter>>h1(501,0,500)","EdgeCounter>0");
  tree1->Draw("totphotonsipm_pde>>h2(501,0,500)","EdgeCounter>0");
  tree1->Draw("totphotonsipm>>h3(501,0,500)","EdgeCounter>0");
  tree1->Draw("EdgeCounter>>h4(501,0,500)","EdgeCounter>0");
  

  Int_t norm=tree1->GetEntries("EdgeCounter>0");

  h1->Scale(1./(Double_t)norm);
  h2->Scale(1./(Double_t)norm);
  h3->Scale(1./(Double_t)norm);
  h4->Scale(1./(Double_t)norm);
  

  Int_t a;
  Double_t max1,max2,max3,max4;

  a=h1->GetMaximumBin();
  max1=h1->GetBinCenter(a);
  a=h2->GetMaximumBin();
  max2=h2->GetBinCenter(a);
  a=h3->GetMaximumBin();
  max3=h3->GetBinCenter(a);
  a=h4->GetMaximumBin();
  max4=h4->GetBinCenter(a);

  cout<<"Nphe "<<max1<<endl;
  cout<<"pde "<<max2<<endl;
  cout<<"hit surface "<<max3<<endl;
  cout<<"end fiber counter "<<max4<<endl;

  
  
  h1->SetLineColor(1);
  h2->SetLineColor(2);
  h3->SetLineColor(3);
  h4->SetLineColor(4);


  h1->GetXaxis()->SetTitle("N");
  h2->GetXaxis()->SetTitle("N");
  h3->GetXaxis()->SetTitle("N");
  h4->GetXaxis()->SetTitle("N");

  TCanvas *c1=new TCanvas();


  h1->Draw();
  h2->Draw("same");
  h3->Draw("same");
  h4->Draw("same");

  //  TCanvas *c2=new TCanvas();

  // chain2->Draw("PhotonCounter:EdepFib_muon");

}
