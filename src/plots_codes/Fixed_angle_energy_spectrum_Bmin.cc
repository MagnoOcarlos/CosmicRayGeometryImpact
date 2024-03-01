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

void saveBins(TH1D *h100,TH1D *h120,TH1D *h160,TH1D *h200,TH1D *h240,char *argv[]){//Function to save bin content in a different directory

	ofstream outputfile(std::string(argv[4])+"spectrum_bins_"+std::string(argv[5])+".txt");
	int j;
	double b100,b120,b160,b200,b240;
	
	outputfile<<"#bin\t"<<"R=100\t"<<"R=120\t"<<"R=160\t"<<"R=200\t"<<"R=240"<<"\n";

    for(int j=1; j<=40;j++){
        
		double b100 = h100->GetBinContent(j);
		double b120 = h120->GetBinContent(j);
		double b160 = h160->GetBinContent(j);
		double b200 = h200->GetBinContent(j);
        double b240 = h240->GetBinContent(j);
        
    	outputfile<<j<<"\t"<<b100<<"\t"<<b120<<"\t"<<b160<<"\t"<<b200<<"\t"<<b240<<"\n";

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
	TH1D *hArrive100;
	TH1D *hArrive120;
	TH1D *hArrive160;
	TH1D *hArrive200;
	TH1D *hArrive240;
	

	// file names for the plot and its openings
	const char *filename100 = "../energy_100Mpc.txt";
	const char *filename120 = "../energy_120Mpc.txt";
	const char *filename160 = "../energy_160Mpc.txt";
	const char *filename200 = "../energy_200Mpc.txt";
	const char *filename240 = "../energy_240Mpc.txt";
	

	ifstream input100(filename100);
	ifstream input120(filename120);
	ifstream input160(filename160);
	ifstream input200(filename200);
	ifstream input240(filename240);
	

	// Filling the histograms
	// The ideia of this program is make a hist of the Energy difference divided by the initial energy
	hArrive100 = fillingHist(input100);
	hArrive120 = fillingHist(input120);
	hArrive160 = fillingHist(input160);
	hArrive200 = fillingHist(input200);
	hArrive240 = fillingHist(input240);
	


	// Normalization

	double_t factor = 1.;
	hArrive100->Scale(factor / hArrive100->GetEntries());
	hArrive120->Scale(factor / hArrive120->GetEntries());
	hArrive160->Scale(factor / hArrive160->GetEntries());
	hArrive200->Scale(factor / hArrive200->GetEntries());
	hArrive240->Scale(factor / hArrive240->GetEntries());
	

	auto *c = new TCanvas("c","ASDJ",1200,1000);
	c->Divide(2,2);

	// Axis, canvas and legends properties
	hArrive100->SetLineColor(kRed);
	hArrive100->SetStats(0);
	hArrive100->GetYaxis()->SetRangeUser(1e-5, 1e0);
	hArrive100->GetYaxis()->SetTitle("Count");
	hArrive100->GetXaxis()->SetTitle("Log(E/eV)");
	hArrive100->Draw("HIST");

	hArrive120->SetLineColor(kRed-6);
	hArrive120->SetStats(0);
	hArrive120->Draw("HIST same");

	
	hArrive160->SetLineColor(kMagenta);
	hArrive160->SetStats(0);
	hArrive160->Draw("HIST same");

	
	hArrive200->SetLineColor(kCyan);
	hArrive200->SetStats(0);
	hArrive200->Draw("HIST same");

	hArrive240->SetLineColor(kBlack);
	hArrive240->SetStats(0);
	hArrive240->Draw("HIST same");

	criticalEnergy(atof(argv[1]), atof(argv[2]));

	saveBins(hArrive100,hArrive120,hArrive160,hArrive200,hArrive240,argv);

	auto leg = new TLegend(0.90,0.1,0.995,0.4);

	char pre1[100] = "R=100 Mpc (N=";
	char su1[100] = ")";
	const char *coun1 = to_string(count(input100)).c_str();
	char result1[100];

	strcpy(result1, pre1);
	strcat(result1, coun1);
	// leg->AddEntry(hArrive20, strcat(result, su), "l");//Para acrescentar o número de eventos
	leg->AddEntry(hArrive100, "R=100 Mpc", "l");

	
	char pre5[100] = "R=120 Mpc (N=";
	char su5[100] = ")";
	const char *coun5 = to_string(count(input120)).c_str();
	char result5[100];

	strcpy(result5, pre5);
	strcat(result5, coun5);
	// leg->AddEntry(hArrive20, strcat(result, su), "l");//Para acrescentar o número de eventos
	leg->AddEntry(hArrive120, "R=120 Mpc", "l");

	
	char pre10[100] = "R=160 Mpc (N=";
	char su10[100] = ")";
	const char *coun10 = to_string(count(input160)).c_str();
	char result10[100];

	strcpy(result10, pre10);
	strcat(result10, coun10);
	// leg->AddEntry(hArrive20, strcat(result, su), "l");//Para acrescentar o número de eventos
	leg->AddEntry(hArrive160, "R=160 Mpc", "l");

	char pre15[100] = "R=200 Mpc (N=";
	char su15[100] = ")";
	const char *coun15 = to_string(count(input200)).c_str();
	char result15[100];

	strcpy(result15, pre15);
	strcat(result15, coun15);
	// leg->AddEntry(hArrive20, strcat(result, su), "l");//Para acrescentar o número de eventos
	leg->AddEntry(hArrive200, "R=200 Mpc", "l");

	char pre20[100] = "R=240 Mpc (N=";
	char su20[100] = ")";
	const char *coun20 = to_string(count(input240)).c_str();
	char result[100];

	strcpy(result, pre20);
	strcat(result, coun20);
	// leg->AddEntry(hArrive20, strcat(result, su), "l");//Para acrescentar o número de eventos
	leg->AddEntry(hArrive240, "R=240 Mpc", "l");

	
	leg->SetFillStyle(0);
	leg->Draw();

	c->SetLogy();
	c->SetCanvasSize(1200, 600);
	c->SaveAs(argv[3]);
	//	rint->Run(kTRUE);
}
