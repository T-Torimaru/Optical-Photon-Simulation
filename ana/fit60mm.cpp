#include"langaus.C"

void fit60mm() {
  
  int i,j;
  
  char fileName[256];
  char canvasName[256];
  Int_t RunNumber[128] = {12525,12505,12575,12510,125125,10525,10505,10575,10510,105125,17525,17505,17575,17510,175125,11025,11005,11075,11010,110125,112525,112505,112575,112510,1125125};
  
  TCanvas *histoCanvas = new TCanvas("c1","canvas", 696,500);
  
  TH1F *pe;
  pe = new TH1F("#pe","p.e. number distribution",45,0,45);
  pe->SetXTitle("photoelectron number");
  pe->SetYTitle("Event number");
  
  
  Double_t peakP, peakPError;
  TF1 *fitFunc;
  double np, tenergy;
  int nEntries;
  
  TFile * inputFile;
  TTree * inputTree;
  
  sprintf(fileName, "./peak.dat");
  FILE *fp = fopen(fileName,"w");
  
  for (i=0;i<25;i++){
    sprintf(fileName,"rootfile/60mm_%d.root",RunNumber[i]);
      
      pe->Reset();
    
    inputFile = TFile::Open(fileName);
    inputTree = (TTree*) inputFile->Get("photoele");
    
    inputTree->SetBranchAddress("NP",&np);
    inputTree->SetBranchAddress("TEnergy",&tenergy);
    nEntries = inputTree->GetEntries();
  
    for (int j=0;j<nEntries;j++) {
      inputTree->GetEntry(j);
      
      if (tenergy>0)
	pe->Fill(np);
      
    }
    
    inputFile->Close();
    
    langaus(pe, &fitFunc, &peakP, &peakPError);
    
    histoCanvas->cd();
    pe->Draw();
    fitFunc->Draw("same");
    
    sprintf(canvasName,"./png/60mm_%d.png",RunNumber[i]);
    histoCanvas->SaveAs(canvasName);
    
    fprintf(fp,"%6.4f %6.4f\n",peakP,peakPError);
  }
  fclose(fp);
}
