void compare_struggling () {

   // Read input files
   char* fnames[3] = {
      // "test_e30MeV_2p5mm.root",
      // "test_e30MeV_5mm.root",
      // "test_e30MeV_10mm.root"
      // "test_e40MeV_2p5mm.root",
      // "test_e40MeV_5mm.root",
      // "test_e40MeV_10mm.root"
      // "test_e50MeV_2p5mm.root",
      // "test_e50MeV_5mm.root",
      // "test_e50MeV_10mm.root"
      "test_e40MeV_BGO_0p1mm.root",
      "test_e40MeV_BGO_0p2mm.root",
      "test_e40MeV_BGO_0p5mm.root"
   };
   TFile* ifile[3];
   TTree* tree[3];
   TH1F* h_theta[3];
   float momXM, momYM, momZM;
   for (int i=0; i<3; i++) {
      ifile[i] = new TFile(fnames[i]);
      tree[i] = (TTree*)ifile[i]->Get("tree");
      tree[i]->SetBranchAddress("momXM", &momXM);
      tree[i]->SetBranchAddress("momYM", &momYM);
      tree[i]->SetBranchAddress("momZM", &momZM);
      h_theta[i] = new TH1F(Form("h_theta%d",i), "", 100, 0, 0.3);
      for (int ientry=0; ientry<tree[i]->GetEntries(); ientry++) {
         tree[i]->GetEntry(ientry);
         TVector3 vM(momXM, momYM, momZM);
         h_theta[i]->Fill(vM.Theta());
      }   
   }
   
   // Draw
   h_theta[0]->SetXTitle("Final-initial angle [rad]");
   h_theta[0]->Draw();
   h_theta[1]->SetLineColor(2);
   h_theta[1]->Draw("sames");
   h_theta[2]->SetLineColor(3);
   h_theta[2]->Draw("sames");
   
}
