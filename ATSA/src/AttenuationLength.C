{
  //Results from MC plotxx_double.root  3 < xx < 11
   
  //Full Curve
  Double_t Length[15] = {10,30,50,80,110,150,250,500,750,1000,1600,2000,2600,3500,5000};
  Double_t errLength[15] = {2};
  Double_t MPV[15] = {30.,27.,24.8,22.6,21.0,19.4,16.6,12.1,9.6,8.2,6.0,4.9,3.8,2.9,2.0};
  Double_t errMPV[15] = {0.1,0.1,0.1,0.1,0.2,0.2,0.2,0.4,0.2,0.1,0.1,0.4,0.2,0.7,0.5};
  
 

  // Short Component
  /*
  Double_t Length[8] = {10,30,50,80,110,150,250,500};
  Double_t errLength[8] = {2};
  Double_t MPV[8] = {30.,27.,24.8,22.6,21.0,19.4,16.6,12.1};
  Double_t errMPV[8] = {0.1,0.1,0.1,0.1,0.2,0.2,0.2,0.4};
  */
  /* Long Component
  Double_t Length[6] = {1000,1600,2000,2600,3500,5000};
  Double_t errLength[6] = {2};
  Double_t MPV[6] = {8.2,6.0,4.9,3.8,2.9,2.0};
  Double_t errMPV[6] = {0.1,0.1,0.4,0.2,0.7,0.5};
  */

  for (Int_t i = 0; i<15; i++) {
    MPV[i] = MPV[i]/2.;
  } 


 TGraphErrors *errgr = new TGraphErrors(15,Length,MPV,errLength,errMPV);
  errgr->SetMarkerStyle(20);
  errgr->SetMarkerSize(1);
  errgr->Draw("AP");
  // gr->Fit("expo");

}
