// g++ MakePlot2D-Carlos.cc -o MakePlot2D-Carlos.exe `root-config --cflags --glibs`
//./MakePlot2D-Carlos.exe
//Created by Carlos Magno R da Costa
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
#include "TLine.h"
#include "TText.h"

using namespace std;

// Function to account the number of rows of a file
int count(ifstream &fin)
{

	int rows = 0;

	double val = 0;

	while (fin >> val)
		++rows;

	return (rows);
}

TH1D *fillingHist(ifstream &f)
{

	double E = 0;
	int rows = count(f);
	TH1D *h = new TH1D("", "Main Title", 40, 17, 21);

	f.clear();
	f.seekg(0);

	for (int i = 0; i <= rows; i++)
	{

		f >> E;
		h->Fill(log10(E * pow(10, 18)));
	}

	f.clear();
	f.seekg(0);

	return (h);
}

void saveBins(TH1D *h1,TH1D *h5,TH1D *h10,TH1D *h15,TH1D *h20, TH1D *h40,TH1D *h60,TH1D *h80,char *argv[]){//Function to save bin content in a different directory

	ofstream outputfile(std::string(argv[4])+"spectrum_bins_"+std::string(argv[5])+".txt");
	int j;
	double b1,b5,b10,b15,b20,b40,b60,b80;
	
	outputfile<<"#bin\t"<<"R=1\t"<<"R=5\t"<<"R=10\t"<<"R=15\t"<<"R=20\t"<<"R=40\t"<<"R=60\t"<<"R=80"<<"\n";

    for(int j=1; j<=40;j++){
        
		double b1 = h1->GetBinContent(j);
		double b5 = h5->GetBinContent(j);
		double b10 = h10->GetBinContent(j);
		double b15 = h15->GetBinContent(j);
        double b20 = h20->GetBinContent(j);
        double b40 = h40->GetBinContent(j);
		double b60 = h60->GetBinContent(j);
		double b80 = h80->GetBinContent(j);

    	outputfile<<j<<"\t"<<b1<<"\t"<<b5<<"\t"<<b10<<"\t"<<b15<<"\t"<<b20<<"\t"<<b40<<"\t"<<b60<<"\t"<<b80<<"\n";

    }
	outputfile.close();

}
void criticalEnergy(double lb, double B)//draw a line in the critical energy position 
{

	double Ec;

	Ec = 0.9 * 1 * lb * B;
	Ec = log10(Ec * pow(10, 18));

	if (Ec >= 17.5)
	{
		if(Ec<=18.9){
			TLine *l = new TLine(Ec, 0.0, Ec, 1.0);
			l->SetLineColor(kRed);
			l->SetLineWidth(3);
			l->SetLineStyle(2);
			l->Draw();

			TText *t = new TText((Ec - 0.12), .3, "CE");
			t->SetTextAlign(22);
			t->SetTextColor(kRed);
			t->SetTextFont(10);
			t->SetTextFont(43);
			t->SetTextSize(40);
			t->SetTextAngle(0);
			t->Draw();
		}

		else{
			TLine *l = new TLine(Ec, 0.0, Ec, 1.0);
			l->SetLineColor(kRed);
			l->SetLineWidth(3);
			l->SetLineStyle(2);
			l->Draw();

			TText *t = new TText((Ec - 0.12), .3, "CE");
			t->SetTextAlign(22);
			t->SetTextColor(kRed);
			t->SetTextFont(10);
			t->SetTextFont(43);
			t->SetTextSize(40);
			t->SetTextAngle(0);
			t->Draw();
		}
	}

	else
	{
		Ec = 17.1;
		TLine *l = new TLine(Ec, 0.0, Ec, 1.0);
		l->SetLineColor(kRed);
		l->SetLineWidth(3);
		l->SetLineStyle(2);
		l->Draw();

		TText *t = new TText((Ec + 0.12), .3, "CE");
		t->SetTextAlign(22);
		t->SetTextColor(kRed);
		t->SetTextFont(10);
		t->SetTextFont(43);
		t->SetTextSize(40);
		t->SetTextAngle(0);
		t->Draw();
	}
}

int main(int argc, char *argv[])
{

	//	TRint *rint = new TRint("", &argc, argv);

	// The histograms' objects
	TH1D *hArrive1;
	TH1D *hArrive5;
	TH1D *hArrive10;
	TH1D *hArrive15;
	TH1D *hArrive20;
	TH1D *hArrive40;
	TH1D *hArrive60;
	TH1D *hArrive80;

	// I suppose we don't use these variables anymore
	auto hSaida0 = new TH1D("hSaida0", "Angle 0", 40, 17, 21);
	auto *f = new TF1("f", "pow(x,-1)", 0.1, 1000);

	// file names for the plot and its openings
	const char *filename1 = "../energy_1Mpc.txt";
	const char *filename5 = "../energy_5Mpc.txt";
	const char *filename10 = "../energy_10Mpc.txt";
	const char *filename15 = "../energy_15Mpc.txt";
	const char *filename20 = "../energy_20Mpc.txt";
	const char *filename40 = "../energy_40Mpc.txt";
	const char *filename60 = "../energy_60Mpc.txt";
	const char *filename80 = "../energy_80Mpc.txt";

	ifstream input1(filename1);
	ifstream input5(filename5);
	ifstream input10(filename10);
	ifstream input15(filename15);
	ifstream input20(filename20);
	ifstream input40(filename40);
	ifstream input60(filename60);
	ifstream input80(filename80);

	// Filling the histograms
	// The ideia of this program is make a hist of the Energy difference divided by the initial energy
	hArrive1 = fillingHist(input1);
	hArrive5 = fillingHist(input5);
	hArrive10 = fillingHist(input10);
	hArrive15 = fillingHist(input15);
	hArrive20 = fillingHist(input20);
	hArrive20 = fillingHist(input20);
	hArrive40 = fillingHist(input40);
	hArrive60 = fillingHist(input60);
	hArrive80 = fillingHist(input80);



	// Normalization

	double_t factor = 1.;
	hArrive1->Scale(factor / hArrive1->GetEntries());
	hArrive5->Scale(factor / hArrive5->GetEntries());
	hArrive10->Scale(factor / hArrive10->GetEntries());
	hArrive15->Scale(factor / hArrive15->GetEntries());
	hArrive20->Scale(factor / hArrive20->GetEntries());
	hArrive40->Scale(factor / hArrive40->GetEntries());
	hArrive60->Scale(factor / hArrive60->GetEntries());
	hArrive80->Scale(factor / hArrive80->GetEntries());

	auto *c = new TCanvas("c","ASDJ",1200,1000);
	c->Divide(2,2);

	// Axis, canvas and legends properties
	hArrive1->SetLineColor(kRed);
	hArrive1->SetStats(0);
	hArrive1->GetYaxis()->SetRangeUser(1e-5, 1e0);
	hArrive1->GetYaxis()->SetTitle("Count");
	hArrive1->GetXaxis()->SetTitle("Log(E/eV)");
	hArrive1->Draw("HIST");

	hArrive5->SetLineColor(kRed-6);
	hArrive5->SetStats(0);
	hArrive5->Draw("HIST same");

	
	hArrive10->SetLineColor(kMagenta);
	hArrive10->SetStats(0);
	hArrive10->Draw("HIST same");

	
	hArrive15->SetLineColor(kCyan);
	hArrive15->SetStats(0);
	hArrive15->Draw("HIST same");

	hArrive20->SetLineColor(kBlack);
	hArrive20->SetStats(0);
	hArrive20->Draw("HIST same");

	hArrive40->SetLineColor(kGreen);
	hArrive40->SetStats(0);
	hArrive40->Draw("HIST same");

	hArrive60->SetLineColor(kBlue);
	hArrive60->SetStats(0);
	hArrive60->Draw("Hist same");

	hArrive80->SetLineColor(kOrange);
	hArrive80->SetStats(0);
	hArrive80->Draw("HIST same");

	criticalEnergy(atof(argv[1]), atof(argv[2]));

	saveBins(hArrive1,hArrive5,hArrive10,hArrive15,hArrive20,hArrive40,hArrive60,hArrive80,argv);

	auto leg = new TLegend(0.90,0.1,0.995,0.4);

	char pre1[100] = "R=1 Mpc (N=";
	char su1[100] = ")";
	const char *coun1 = to_string(count(input1)).c_str();
	char result1[100];

	strcpy(result1, pre1);
	strcat(result1, coun1);
	// leg->AddEntry(hArrive20, strcat(result, su), "l");//Para acrescentar o número de eventos
	leg->AddEntry(hArrive1, "R=1 Mpc", "l");

	
	char pre5[100] = "R=5 Mpc (N=";
	char su5[100] = ")";
	const char *coun5 = to_string(count(input5)).c_str();
	char result5[100];

	strcpy(result5, pre5);
	strcat(result5, coun5);
	// leg->AddEntry(hArrive20, strcat(result, su), "l");//Para acrescentar o número de eventos
	leg->AddEntry(hArrive5, "R=5 Mpc", "l");

	
	char pre10[100] = "R=10 Mpc (N=";
	char su10[100] = ")";
	const char *coun10 = to_string(count(input10)).c_str();
	char result10[100];

	strcpy(result10, pre10);
	strcat(result10, coun10);
	// leg->AddEntry(hArrive20, strcat(result, su), "l");//Para acrescentar o número de eventos
	leg->AddEntry(hArrive10, "R=10 Mpc", "l");

	char pre15[100] = "R=15 Mpc (N=";
	char su15[100] = ")";
	const char *coun15 = to_string(count(input15)).c_str();
	char result15[100];

	strcpy(result15, pre15);
	strcat(result15, coun15);
	// leg->AddEntry(hArrive20, strcat(result, su), "l");//Para acrescentar o número de eventos
	leg->AddEntry(hArrive15, "R=15 Mpc", "l");

	char pre20[100] = "R=20 Mpc (N=";
	char su20[100] = ")";
	const char *coun20 = to_string(count(input20)).c_str();
	char result[100];

	strcpy(result, pre20);
	strcat(result, coun20);
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
	c->SetCanvasSize(1200, 600);
	c->SaveAs(argv[3]);
	//	rint->Run(kTRUE);
}
