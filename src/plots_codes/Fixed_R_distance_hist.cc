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
	
	double E=0;
	int rows = count(f);
	TH1D *h = new TH1D("","Main Title", 80, 20,180);
	
	f.clear();
	f.seekg(0);
	
	for(int i=0; i <=rows;i++){
		
		f>>E;
		h->Fill(log10(E*pow(10,18)));
	}

	f.clear();
	f.seekg(0);
	
	return(h);
}



int main(int argc, char* argv[]){
	
//	TRint *rint = new TRint("", &argc, argv);	
	
	//The histograms' objects 
	TH1D* hArrive0;
	TH1D* hArrive20; 
	TH1D* hArrive40; 
	TH1D* hArrive60; 
	TH1D* hArrive80;	
	
	//I suppose we don't use these variables anymore 
	auto hSaida0 = new TH1D("hSaida0","Angle 0", 40, 17,21);	
	auto *f = new TF1("f","pow(x,-1)",0.1,1000);

	//file names for the plot and its openings
	const char *filename0  ="../Distance_ang0.txt";
//	const char* filename20 ="../Distance_ang20.txt";
	const char* filename40 ="../Distance_ang40.txt";
//	const char* filename60 ="../Distance_ang60.txt";
	const char* filename80 ="../Distance_ang80.txt";
	
	ifstream input0(filename0);
//	ifstream input20(filename20);
	ifstream input40(filename40);
//	ifstream input60(filename60);
	ifstream input80(filename80);

	//Filling the histograms 
	//The ideia of this program is make a hist of the Energy difference divided by the initial energy 

	hArrive0 = fillingHist(input0);
//	hArrive20 = fillingHist(input20);
	hArrive40 = fillingHist(input40);
//	hArrive60 = fillingHist(input60);
	hArrive80 = fillingHist(input80);

	//Normalization	
	
	double_t factor =1.;

	hArrive0->Scale(factor/hArrive0->GetEntries());
//	hArrive20->Scale(factor/hArrive20->GetEntries());
	hArrive40->Scale(factor/hArrive40->GetEntries());
//	hArrive60->Scale(factor/hArrive60->GetEntries());
	hArrive80->Scale(factor/hArrive80->GetEntries());
	
	auto *c = new TCanvas("c","ASDJ",200,10,600,400);
	
	//Axis, canvas and legends properties
	hArrive0->SetLineColor(kRed);
	hArrive0->SetStats(0);
	hArrive0->GetYaxis()->SetRangeUser(1e-5,1e0);
	hArrive0->GetYaxis()->SetTitle("Count");
	hArrive0->GetXaxis()->SetTitle("Distance (Mpc)");
	hArrive0->Draw("HIST");
/*	
	hArrive20->SetLineColor(kGreen);
	hArrive20->SetStats(0);
	hArrive20->Draw("HIST same");
*/	
	hArrive40->SetLineColor(kBlue);
	hArrive40->SetStats(0);
	hArrive40->Draw("Hist same");
/*	
	hArrive60->SetLineColor(kOrange);
	hArrive60->SetStats(0);
	hArrive60->Draw("HIST same");
*/
	hArrive80->SetLineColor(kBlack);
	hArrive80->SetStats(0);
	hArrive80->Draw("Hist same");
	
	
	auto leg = new TLegend(.84,.6,.5,.8);
		
	char pre[100]= "Angle 0#circ (N=";
	char su[100]=")";
	const char *coun=to_string(count(input0)).c_str();
	char result[100];

	strcpy(result,pre);
	strcat(result,coun);
	leg->AddEntry(hArrive0,strcat(result,su), "l");
/*		
	char pre20[100]= "Angle 20#circ (N=";
	const char *coun20=to_string(count(input20)).c_str();
	char result20[100];

	strcpy(result20,pre20);
	strcat(result20,coun20);
	leg->AddEntry(hArrive20,strcat(result20,su), "l");
*/	

	char pre40[100]= "Angle 40#circ (N=";
	const char *coun40=to_string(count(input40)).c_str();
	char result40[100];

	strcpy(result40,pre40);
	strcat(result40,coun40);
	leg->AddEntry(hArrive40,strcat(result40,su), "l");
/*	
	char pre60[100]= "Angle 60#circ (N=";
	const char *coun60=to_string(count(input60)).c_str();
	char result60[100];

	strcpy(result60,pre60);
	strcat(result60,coun60);
	leg->AddEntry(hArrive60,strcat(result60,su), "l");
*/
	char pre80[100]= "Angle 80#circ (N=";
	const char *coun80=to_string(count(input80)).c_str();
	char result80[100];

	strcpy(result80,pre80);
	strcat(result80,coun80);
	leg->AddEntry(hArrive80,strcat(result80,su), "l");
	
	leg->Draw();

	
	c->SetLogy();
	c->SetCanvasSize(1200,600);
	c->SaveAs("pdfs_saved/Distance.pdf");
//	rint->Run(kTRUE);

}
