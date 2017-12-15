#include"langaus.C"

void fitting() {
  
  int i,j;

  char fileName[256];
  char canvasName[256];
  Int_t runNum[128] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};
  double np, tenergy;

  TCanvas *histoCanvas = new TCanvas("c1","canvas", 696,500);

  TH1F *pe;
  pe = new TH1F("#pe","p.e. number distribution",100,0,100);
  pe->SetXTitle("photoelectron number");
  pe->SetYTitle("Event number");

  sprintf(fileName, "./peak.dat");
  FILE *fp = fopen(fileName,"w");
  
  for (j=0;j<1;j++){
    sprintf(fileName,"rootfile/ori13mmx.root");//,runNum[j]);
      
      pe->Reset();
    
    TFile * inputFile = TFile::Open(fileName);
    TTree * inputTree = (TTree*) inputFile->Get("photoele");
    inputTree->SetBranchAddress("NP",&np);
    //  inputTree->SetBranchAddress("TEnergy",&tenergy);
    int nEntries = inputTree->GetEntries();
    
    
    for (int i=0;i<nEntries;i++) {
      inputTree->GetEntry(i);
      
      //  if (tenergy>0)
      pe->Fill(np);
      
    }
    
    pe->Draw();
    Double_t peakP, peakPError;
    TF1 *fitFunc;
    
    langaus(pe, &fitFunc, &peakP, &peakPError);
    
    histoCanvas->cd();
    fitFunc->Draw("same");
    
    sprintf(canvasName,"./png/ori13mmx.png");//,runNum[j]);
    histoCanvas->SaveAs(canvasName);
    
    fprintf(fp,"%6.4f %6.4f\n",peakP,peakPError);
  }
  fclose(fp);
}
