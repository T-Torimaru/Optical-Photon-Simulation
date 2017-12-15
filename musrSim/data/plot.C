void plot() {
   TFile *flie = new TFile("musr_25.root");
   TCanvas *c1 = new TCanvas("c1", "standard config", 600, 400);
   TH1F *frame1 = (TH1F*)gPad->DrawFrame(-25, 0, 25, 50);
   t1->Draw("nOptPhotDet:det_x","","profile same");
   frame1->SetXTitle("[mm]");
   frame1->SetTitleOffset(0.7, "x");
   frame1->SetTitleSize(0.05, "x");
   frame1->SetYTitle("N_{pe}");
   frame1->SetTitleOffset(0.7, "y");
   frame1->SetTitleSize(0.05, "y");
   c1->SetGridx();
   c1->SetGridy();

   TCanvas *c2 = new TCanvas("c2", "standard config", 600, 400);
   t1->Draw("nOptPhotDet:det_y:det_x>>haho(30,-25,25,5,0,2.5)","","profile");
   haho->SetMaximum(50);
   haho->Draw("lego2z");



   TCanvas *c3 = new TCanvas("c3", "standard config", 800, 600);
   TH1F *frame3 = (TH1F*)gPad->DrawFrame(-25, 0, 25, 50);
   TFile *flie = new TFile("musr_24.root");
   t1->Draw("nOptPhotDet:det_x>>h24","","profile same");
   h24->SetLineColor(kBlack);
   h24->SetLineWidth(2);
   TFile *flie = new TFile("musr_25.root");
   t1->Draw("nOptPhotDet:det_x>>h25","","profile same");
   h25->SetLineColor(kBlue);
   h25->SetLineWidth(2);
   TFile *flie = new TFile("musr_26.root");
   t1->Draw("nOptPhotDet:det_x>>h26","","profile same");
   h26->SetLineColor(kMagenta);
   h26->SetLineWidth(2);
   TFile *flie = new TFile("musr_42.root");
   t1->Draw("nOptPhotDet:det_x>>h42","","profile same");
   h42->SetLineColor(kRed);
   h42->SetLineWidth(2);
   frame3->SetXTitle("[mm]");
   frame3->SetTitleOffset(0.7, "x");
   frame3->SetTitleSize(0.05, "x");
   frame3->SetYTitle("N_{pe}");
   frame3->SetTitleOffset(0.7, "y");
   frame3->SetTitleSize(0.05, "y");
   
   TLegend *leg = new TLegend(0.2, 0.6, 0.5, 0.8);
   leg->AddEntry(h24, "Std config.", "l");
   leg->AddEntry(h26, "MPPC @ bottom", "l");
   leg->AddEntry(h25, "Wedge", "l");
   leg->AddEntry(h42, "Sharp wedge", "l");
   leg->SetFillStyle(0);
   leg->Draw();
   


}
