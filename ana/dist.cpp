void dist(){
  
  Double_t x,y,z,w;
  char canvasName[256];
  
  TCanvas *c1 = new TCanvas("c1","canvas1",700,500);
  TCanvas *c2 = new TCanvas("c2","canvas2",500,500);
  
  TH2F *hist = new TH2F("#pe","LY distribution of 60mm tile",5,0,15,5,0,15);
  hist->SetXTitle("x");
  hist->SetYTitle("y");
  hist->SetZTitle("#p.e.");
  hist->SetStats(0);
  hist->SetMaximum(50.);
  hist->SetMinimum(0.);

  ifstream ifs("./old30mm.dat");
  while(ifs>>x>>y>>z>>w){
    
    hist->Fill(x,y,z);
    //    std::cout << x << " " << y << " " << z << " " << w << std::endl;
  }
  ifs.close();
  
  c1->cd();
  hist->Draw("lego2z");
  c2->cd();
  hist->Draw("text45 colz");
  
  sprintf(canvasName,"./png/old30mm_dist.png");
  c1->SaveAs(canvasName);
  sprintf(canvasName,"./png/old30mm_dist_plate.png");
  c2->SaveAs(canvasName);
} 
