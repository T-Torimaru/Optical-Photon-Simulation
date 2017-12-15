void plot2() {
  TFile *flie = new TFile("musr_93.root");
  //  TFile *flie = new TFile("Dtprd5_edge_15mm_UairEJ204_0622.root");
  TCanvas *c1 = new TCanvas("c1", "standard config", 600, 400);
  //  TH1F *frame1 = (TH1F*)gPad->DrawFrame(-25, 0, 25, 50);
  TH1F *frame1 = (TH1F*)gPad->DrawFrame(-25, 0, 25, 50);
  t1->Draw("nOptPhotDet:det_x","","profile same");
  //   frame1->
  frame1->SetXTitle("[mm]");
  frame1->SetTitleOffset(0.7, "x");
  frame1->SetTitleSize(0.05, "x");
  frame1->SetYTitle("N_{pe}");
  frame1->SetTitleOffset(0.7, "y");
  frame1->SetTitleSize(0.05, "y");
  
}
