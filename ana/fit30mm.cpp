#include"langaus.C"

void fit30mm() {
  
  int i,j;
  
  char fileName[256];
  char canvasName[256];
  Int_t RunNumber[128] = //{2525,2505,2575,2510,25125,7525,7505,7575,7510,75125,1025,1005,1075,1010,10125,12525,12505,12575,12510,125125};
      {525,505,575,510,5125};
  TCanvas *histoCanvas = new TCanvas("c1","canvas", 696,500);
  
  TH1F *pe;
  pe = new TH1F("#pe","p.e. number distribution",100,0,100);
  pe->SetXTitle("photoelectron number");
  pe->SetYTitle("Event number");
  
  
  Double_t peakP, peakPError;
  TF1 *fitFunc;
  double np, tenergy;
  int nEntries;
  
  TFile * inputFile;
  TTree * inputTree;
  
  sprintf(fileName, "./peak2.dat");
  FILE *fp = fopen(fileName,"w");
  
  for (i=0;i<5;i++){
    sprintf(fileName,"rootfile/30mm_00%d.root",RunNumber[i]);
      
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
    
    sprintf(canvasName,"./png/30mm_00%d.png",RunNumber[i]);
    histoCanvas->SaveAs(canvasName);
    
    fprintf(fp,"%6.4f %6.4f\n",peakP,peakPError);
  }
  fclose(fp);
}
