void direction () {

   // Read input file
   TFile* ifile = new TFile("test1M.root");
   TTree* tree = (TTree*)ifile->Get("tree");
   float vtxZ;
   float momXP, momYP, momZP;
   float momXM, momYM, momZM;
   tree->SetBranchAddress("vtxZ", &vtxZ);
   tree->SetBranchAddress("momXP", &momXP);
   tree->SetBranchAddress("momYP", &momYP);
   tree->SetBranchAddress("momZP", &momZP);
   tree->SetBranchAddress("momXM", &momXM);
   tree->SetBranchAddress("momYM", &momYM);
   tree->SetBranchAddress("momZM", &momZM);

   // Create histograms
   TH1F* h_theta = new TH1F("h_theta", "", 1000, 0, 0.1);
   TH1F* h_mom_max = new TH1F("h_mom_max", "", 100, 0, 60);
   TH1F* h_theta_max = new TH1F("h_theta_max", "", 100, 0, 0.1);
   
   // Loop for events
   for (int ientry=0; ientry<tree->GetEntries(); ientry++) {
      tree->GetEntry(ientry);
      TVector3 vP(momXP, momYP, momZP);
      TVector3 vM(momXM, momYM, momZM);
      TVector3 v_sum = vP + vM;
      h_theta->Fill(v_sum.Theta());
      if (vP.Mag() > vM.Mag() ) {
         h_mom_max->Fill(vP.Mag());
         h_theta_max->Fill(vP.Theta());
      } else {
         h_theta_max->Fill(vM.Theta());
      }
   }   

   // Draw results
   // h_theta->Draw();
   h_mom_max->Draw();
   // h_theta_max->Draw();

   
}
