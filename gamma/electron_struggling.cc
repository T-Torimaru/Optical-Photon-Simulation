void electron_struggling () {

   // Read input file
   TFile* ifile = new TFile("test.root");
   // TFile* ifile = new TFile("test_e50MeV_5mm.root");
   TTree* tree = (TTree*)ifile->Get("tree");
   float momXM, momYM, momZM;
   tree->SetBranchAddress("momXM", &momXM);
   tree->SetBranchAddress("momYM", &momYM);
   tree->SetBranchAddress("momZM", &momZM);
   
   // Create histograms
   TH1F* h_theta = new TH1F("h_theta", "", 100, 0, 0.5);

   // Loop for events
   for (int ientry=0; ientry<tree->GetEntries(); ientry++) {
      tree->GetEntry(ientry);
      TVector3 vM(momXM, momYM, momZM);
      h_theta->Fill(vM.Theta());
   }   

   // Draw results
   h_theta->Draw();

}