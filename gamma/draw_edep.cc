void draw_edep (char* filename) {

   ifstream ifs(filename);
   double edep;
   TH1F* h = new TH1F("h","",1000,0,5.0);
   while (ifs >> edep) {
//       double edep_smear = gRandom->Gaus(edep,edep*0.1);
//       h->Fill(edep_smear);
      h->Fill(edep);
   }
   h->SetXTitle("E_{dep} [MeV]");
   h->Draw();
   // h->SaveAs("edep_PS_pi_28MeV.root");
   // TF1* flandau = new TF1("flandau","landau",40,46);
   // flandau->SetLineColor(2);
   // h->Fit(flandau,"","",40,48);

}
