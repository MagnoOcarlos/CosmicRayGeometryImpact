{
  gROOT->Reset();
	gStyle->SetOptStat(kFALSE);
//   gStyle->SetOptTitle(kFALSE);

  const Int_t NRGBs = 5;
  const Int_t NCont = 510;
  Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };

  gStyle->SetLabelFont(132,"xyz");
  gStyle->SetLabelSize(0.06,"xyz");
  gStyle->SetTitleFont(132,"xyz");
  gStyle->SetTitleSize(0.07,"xyz");
  gStyle->SetPadLeftMargin(0.13);
  gStyle->SetPadBottomMargin(0.14);
  gStyle->SetTitleOffset(0.90,"x");
  gStyle->SetTitleOffset(0.70,"y");
  gStyle->SetTitleOffset(0.70,"z");
  gStyle->SetTextFont(120);
  gStyle->SetLineWidth(2);
  gStyle->SetHistLineWidth(3);
  gStyle->SetFrameLineWidth(2);
  gStyle->SetMarkerStyle(7);


  Double_t red[NRGBs]   = {0.215861, 0.826185, 0.841820, 0.905216, 0.587045 };
  Double_t green[NRGBs] = { 0.551260, 0.891598, 0.833696, 0.486757, 0.291068 };
  Double_t blue[NRGBs]  = { 0.504513, 0.575184, 0.325583, 0.144282, 0.137044 };

  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  gStyle->SetNumberContours(NCont);


  ifstream F1("../energy_20Mpc.txt");
  ifstream F2("../elongation_20Mpc.txt");


  TH2F *h = new TH2F("","",40,17,21,90,-4,5);
  while(!F1.eof()){
      double phi,theta,peso_Phi,peso_Theta;

      F1 >> peso_Phi;
      F2 >> peso_Theta;

    //   cout << peso_Phi << "  " << peso_Theta << "  " << phi << "  " <<theta << endl;
      h->Fill(log10(peso_Phi * pow(10, 18)), log10(peso_Theta));
  }
  TCanvas MyCanvas("EAST","EAST",800,100,1200,800);
     h->GetYaxis()->SetTitle("log(l/Mpc) ");
     h->GetXaxis()->SetTitle("log(E/ev)");
     h->GetZaxis()->SetTitle("count");
	  h->SetTitle("Proton's elongation: #theta=80#circ, B=100 nG, L_{B}=10Mpc, R=20 Mpc #phi=15#circ");
     //h->GetZaxis()->SetRangeUser(0,34);
     gStyle->SetOptStat(0);

    h->Draw("colz");
  MyCanvas.SetRightMargin(0.15);
    MyCanvas.SaveAs("elo_proton_ang_80_B_100nG_Lb_10Mpc_R_20Mpc_phi_15.pdf");

}