//g++ MakePlot2D-Carlos.cc -o MakePlot2D-Carlos.exe `root-config --cflags --glibs`
//./MakePlot2D-Carlos.exe
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <unistd.h>
#include "TGraph.h"
#include <TRandom3.h>
#include "TRandom.h"
#include "TRint.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TF1.h"
#include "TLine.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TStyle.h"
#include "TH2F.h"
#include "TLegend.h"

using namespace std;


//Function to find the number of rows of a file 
int count(ifstream& fin){
		
	int rows=0;	

	double val=0;
	    
	
	while( fin >> val )	
		++rows;
	
		
	return(rows);
}


TH1D* fillingHist( ifstream& f){

	
	double l=0;
	int rows = count(f);
	TH1D *h = new TH1D("","Main Title", 80, -5,5);
	
	f.clear();
	f.seekg(0);
	
	for(int i=0; i <=rows;i++){
		
		f>>l;
		h->Fill(log10(l));
	}

	f.clear();
	f.seekg(0);
	
	return(h);
}

void saveBins(TH1D *h20, TH1D *h40,TH1D *h60,TH1D *h80,char *argv[]){//Function to sabe bin content in a different directory

	ofstream outputfile(std::string(argv[2])+"elongation_bins_"+std::string(argv[3])+".txt");
	int j;
	double b20,b40,b60,b80;
	
	outputfile<<"#bin\t"<<"R=20\t"<<"R=40\t"<<"R=60\t"<<"R=80"<<"\n";

    for(int j=1; j<=80;j++){
        
        double b20 = h20->GetBinContent(j);
        double b40 = h40->GetBinContent(j);
		double b60 = h60->GetBinContent(j);
		double b80 = h80->GetBinContent(j);

    	outputfile<<j<<"\t"<<b20<<"\t"<<b40<<"\t"<<b60<<"\t"<<b80<<"\n";

    }
	outputfile.close();

}



int main(int argc, char* argv[]){
	
//	TRint *rint = new TRint("", &argc, argv);	
	
	//The histograms' objects 
	TH1D* hArrive0;
	TH1D* hArrive20; 
	TH1D* hArrive40; 
	TH1D* hArrive60; 
	TH1D* hArrive80;	
	
	//file names for the plot and its openings
	const char *filename20  ="../elongation_20Mpc.txt";
	const char* filename40 ="../elongation_40Mpc.txt";
	const char* filename60 ="../elongation_60Mpc.txt";
	const char* filename80 ="../elongation_80Mpc.txt";
	
	ifstream input20(filename20);
	ifstream input40(filename40);
	ifstream input60(filename60);
	ifstream input80(filename80);

	//Filling the histograms 
	//The ideia of this program is make a hist of the Energy difference divided by the initial energy 

	hArrive20 = fillingHist(input20);
	hArrive40 = fillingHist(input40);
	hArrive60 = fillingHist(input60);
	hArrive80 = fillingHist(input80);

	//Normalization	
	
	double_t factor =1.;

	hArrive20->Scale(factor/hArrive20->GetEntries());
 	hArrive40->Scale(factor/hArrive40->GetEntries());
	hArrive60->Scale(factor/hArrive60->GetEntries());
	hArrive80->Scale(factor/hArrive80->GetEntries());
	
	auto *c = new TCanvas("c","ASDJ",200,10,600,400);
	
	//Axis, canvas and legends properties
	hArrive20->SetLineColor(kRed);
	hArrive20->SetStats(0);
	hArrive20->GetYaxis()->SetRangeUser(1e-5,1e0);
	hArrive20->GetYaxis()->SetTitle("Count");
	hArrive20->GetXaxis()->SetTitle("Elongation log(l/Mpc)");
	hArrive20->Draw("HIST");
	
	hArrive40->SetLineColor(kGreen);
	hArrive40->SetStats(0);
	hArrive40->Draw("HIST same");
	
	hArrive60->SetLineColor(kBlue);
	hArrive60->SetStats(0);
	hArrive60->Draw("Hist same");
	
	hArrive80->SetLineColor(kOrange);
	hArrive80->SetStats(0);
	hArrive80->Draw("HIST same");

	saveBins(hArrive20,hArrive40,hArrive60,hArrive80,argv);
	
	auto leg = new TLegend(0.9,0.70,0.48,0.9);

	char pre[100] = "R=20 Mpc (N=";
	char su[100] = ")";
	const char *coun = to_string(count(input20)).c_str();
	char result[100];

	strcpy(result, pre);
	strcat(result, coun);
	// leg->AddEntry(hArrive20, strcat(result, su), "l");//Para acrescentar o número de eventos
	leg->AddEntry(hArrive20, "R=20 Mpc", "l");

	char pre40[100] = "R=40 Mpc (N=";
	const char *coun40 = to_string(count(input40)).c_str();
	char result40[100];

	strcpy(result40, pre40);
	strcat(result40, coun40);
	// leg->AddEntry(hArrive40, strcat(result40, su), "l");
	leg->AddEntry(hArrive40, "R=40 Mpc", "l");

	char pre60[100] = "R=60 Mpc (N=";
	const char *coun60 = to_string(count(input60)).c_str();
	char result60[100];

	strcpy(result60, pre60);
	strcat(result60, coun60);
	// leg->AddEntry(hArrive60, strcat(result60, su), "l");
	leg->AddEntry(hArrive60, "R=60 Mpc", "l");

	char pre80[100] = "R=80 Mpc (N=";
	const char *coun80 = to_string(count(input80)).c_str();
	char result80[100];

	strcpy(result80, pre80);
	strcat(result80, coun80);
	// leg->AddEntry(hArrive80, strcat(result80, su), "l");
	leg->AddEntry(hArrive80, "R=80 Mpc", "l");
	leg->SetFillStyle(0);
	leg->Draw();

	c->SetLogy();
	c->SetCanvasSize(1200,600);
	c->SaveAs(argv[1]);
//	rint->Run(kTRUE);

}
