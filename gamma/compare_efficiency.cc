void compare_efficiency() {

   TFile* ifile[3];
   ifile[0] = new TFile("gr_effi_pb.root");
   ifile[1] = new TFile("gr_effi_bgo.root");
   ifile[2] = new TFile("gr_effi_nai.root");
   TGraph* gr[3];
   gr[0] = (TGraph*)ifile[0]->Get("gr_effi_pb");
   gr[1] = (TGraph*)ifile[1]->Get("gr_effi_bgo");
   gr[2] = (TGraph*)ifile[2]->Get("gr_effi_nai");

   gr[1]->SetLineColor(2);
   gr[2]->SetLineColor(3);
   gr[0]->Draw("AL");
   gr[1]->Draw("L same");
   gr[2]->Draw("L same");
   
}
