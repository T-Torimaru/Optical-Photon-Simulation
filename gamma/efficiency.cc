void efficiency () {

   TFile* ifile = new TFile("test_NaI_effi.root");
   // TFile* ifile = new TFile("test_Pb_effi.root");
   // TFile* ifile = new TFile("test_BGO_effi.root");
   TTree* tree = (TTree*)ifile->Get("tree");
   tree->Draw("vtxZ+500>>h_conv(100,0,200)");
   TH1F* h_conv = (TH1F*)gROOT->FindObject("h_conv");
   h_conv->SetXTitle("conversion point [mm]");

   float nevent = 0;
   TGraph* gr_effi = new TGraph();
   for (int ibin=0; ibin<h_conv->GetNbinsX(); ibin++) {
      nevent += h_conv->GetBinContent(ibin);
      gr_effi->SetPoint(gr_effi->GetN(), h_conv->GetXaxis()->GetBinUpEdge(ibin), nevent/tree->GetEntries());;
   }
   gr_effi->SetMarkerStyle(7);
   gr_effi->Draw("APL");
   gr_effi->GetXaxis()->SetTitle("thickness [mm]");
   gr_effi->GetYaxis()->SetTitle("efficiency");
   
}
