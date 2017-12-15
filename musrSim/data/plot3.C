void plot3() {

  //  TFile *flie = new TFile("std_1mm_0601.root");
  //    TFile *flie = new TFile("musr_60.root");
  //  TFile *flie = new TFile("Dtprd5_edge_1.5mm_EJ204_1.5_0625.root");
  //  TFile *flie = new TFile("wedge5_edge_2mm_Uair_0619.root");
  //  TFile *flie = new TFile("wedge5_edge_15mm_Uair_0622.root");
  TFile *flie = new TFile("Stprd5_edge_15mm_Uair_EJ204_1.5_0622.root");
  TCanvas *c1 = new TCanvas("c1", "standard config", 600, 400);
  TH1F *frame1 = (TH1F*)gPad->DrawFrame(-25, 0, 25, 50);
  t1->Draw("nOptPhotDet:det_x>>h1","","profile same");
  //  h1->SetLineColor(kBlue);
  h1->SetLineColor(kBlack);
  h1->SetLineWidth(2);
  frame1->SetXTitle("[mm]");
  frame1->SetTitleOffset(0.7, "x");
  frame1->SetTitleSize(0.05, "x");
  frame1->SetYTitle("N_{pe}");
  frame1->SetTitleOffset(0.7, "y");
  frame1->SetTitleSize(0.05, "y");
  
  //  TFile *flie2 = new TFile("Dtprd5_edge12_1.5mm_EJ204_0623.root");
  //  TFile *flie2 = new TFile("wedge5_edge_15mm_Uair_0622.root");
  //  TFile *flie2 = new TFile("wedge5_edge_2mm_EJ204_1.0_0630.root");
  //  TFile *flie2 = new TFile("wedge5_edge_1.5mm_EJ204_Uair1.0_0630.root");
  TFile *flie2 = new TFile("Stprd5_edge3_1.5mm_EJ204_0624.root");
  t1->Draw("nOptPhotDet:det_x>>h2","","profile same");
  h2->SetLineColor(kMagenta);
  h2->SetLineWidth(2);
  
  //  TFile *flie3 = new TFile("bttm_1mm_0606.root");
  //  TFile *flie3 = new TFile("wedge5_edge_2mm_EJ204_1.5_0630.root");  
  //  TFile *flie3 = new TFile("wedge5_edge_1.5mm_EJ204_Uair1.5_0630.root");  
  //TFile *flie3 = new TFile("Dtprd5_edge_1mm_UairEJ204_0622.root");
  //  TFile *flie3 = new TFile("bttm_1.5mm_EJ204_0627.root");
  //  t1->Draw("nOptPhotDet:det_x>>h3","","profile same");
  //  h3->SetLineColor(kRed);
  //  h3->SetLineWidth(2);
  /*
  TFile *flie4 = new TFile("Dtprd5_edge12_1.5mm_EJ204_0623.root");
  t1->Draw("nOptPhotDet:det_x>>h4","","profile same");
  h4->SetLineColor(kBlue);
  h4->SetLineWidth(2);

  TFile *flie5 = new TFile("Stprd5_edge3_1.5mm_EJ204_0624.root");
  t1->Draw("nOptPhotDet:det_x>>h5","","profile same");
  h5->SetLineColor(kGreen);
  h5->SetLineWidth(2);
  */
  TLegend *leg = new TLegend(0.2, 0.6, 0.5, 0.8);
    leg->AddEntry(h1,"Stprd5 edge 1.5mm thick","l");
    leg->AddEntry(h2,"Stprd5 edge3 1.5mm thick ","l");
  //  leg->AddEntry(h3,"Dtprd5 edge 1mm thick ","l");
  //  leg->AddEntry(h1,"wedge5, 1.5mm thick, MPPC is edge from 0.5mm, open area is not the same","l");
  //  leg->AddEntry(h2,"wedge5, 1.5mm thick, MPPC is edge from 1.0mm, open area is not the same","l");
  //  leg->AddEntry(h3,"wedge5, 1.5mm thick, MPPC is edge from 1.5mm, open area is not the same","l");
  /*
  leg->AddEntry(h1,"standard","l");
  leg->AddEntry(h2,"wedge 5mm","l");
  leg->AddEntry(h3,"simple bottom","l");
  leg->AddEntry(h4,"double tapered wedge12 5mm","l");
  leg->AddEntry(h5,"single-side tapered wedge3 5mm","l");
  */
  leg->SetFillStyle(0);
  leg->Draw();

}
