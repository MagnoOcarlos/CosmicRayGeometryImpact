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
#include "TLine.h"
#include "TText.h"

using namespace std;


//Function to find the number of rows of a file 
int count(ifstream& fin){
		
	int rows=0;	

	double val=0;
	    
	
	while( fin >> val )	
		++rows;
	
		
	return(rows);
}


TH1D *fillingHist(ifstream &f,ifstream &f2,double gamma, double Rcut, int Z)//argv 4 gamma; argv 5 Rcut; argv 6 numero atomico
{

	double E = 0,E_f=0;
	double weight;
	int rows = count(f);
	TH1D *h = new TH1D("", "Main Title", 40, 17, 21);

	f.clear();
	f.seekg(0);


	for (int i = 0; i <= rows; i++)
	{

		f >> E;
		f2 >> E_f;

		weight=pow(E_f,(1-gamma));
	
		if (E_f  > (Z*pow(10,Rcut))/pow(10,18)  ){
			weight=pow(E_f,(1-gamma))*exp(1-(E_f/((Z*pow(10,Rcut))/pow(10,18)) ));	
		
		}
		h->Fill(log10(E*pow(10,18)),weight);
	}

	f.clear();
	f.seekg(0);

	return (h);

}


void criticalEnergy(double lb, double B){
//Colocar energia critica dos dois núcleos
	double Ecp,Ec2, Ec3;
	
	Ecp = 0.9 * 1 * lb * B;
	Ecp = log10(Ecp * pow(10, 18));
	
	Ec2 = (0.9 * (5+3+2) * lb * B)/3;
	Ec2 = log10(Ec2 * pow(10, 18));

	Ec3 = (0.9 *(6+7) * lb * B)*0.5;
	Ec3 = log10(Ecp * pow(10, 18));
	
	if (Ecp >= 17.5)
	{

		TLine *lp = new TLine(Ecp, 0.0, Ecp, 1.0);
		lp->SetLineColor(kGreen);
		lp->SetLineWidth(3);
		lp->SetLineStyle(2);
		lp->Draw();

		TText *tp = new TText((Ecp - 0.12), .3, "Ec");
		tp->SetTextAlign(22);
		tp->SetTextColor(kGreen);
		tp->SetTextFont(43);
		tp->SetTextSize(40);
		tp->SetTextAngle(0);
		tp->Draw();

		
		TLine *l2 = new TLine(Ec2, 0.0, Ec2, 1.0);
		l2->SetLineColor(kBlue);
		l2->SetLineWidth(3);
		l2->SetLineStyle(2);
		l2->Draw();

		TText *t2 = new TText((Ec2 - 0.12), .3, "Ec");
		t2->SetTextAlign(22);
		t2->SetTextColor(kBlue);
		t2->SetTextFont(43);
		t2->SetTextSize(20);
		t2->SetTextAngle(0);
		t2->Draw();

		TLine *l3 = new TLine(Ec3, 0.0, Ec3, 1.0);
		l3->SetLineColor(kYellow);
		l3->SetLineWidth(3);
		l3->SetLineStyle(2);
		l3->Draw();

		TText *t3 = new TText((Ec3 - 0.12), .3, "Ec");
		t3->SetTextAlign(22);
		t3->SetTextColor(kYellow);
		t3->SetTextFont(43);
		t3->SetTextSize(20);
		t3->SetTextAngle(0);
		t3->Draw();
	}

	else
	{
		
		Ecp = 17.1;  
		TLine *lp = new TLine(Ecp, 0.0, Ecp, 1.0);
		lp->SetLineColor(kGreen);
		lp->SetLineWidth(3);
		lp->SetLineStyle(2);
		lp->Draw();

		TText *tp = new TText((Ecp + 0.25), .3, "CE");
		tp->SetTextAlign(22);
		tp->SetTextColor(kGreen);
		tp->SetTextFont(43);
		tp->SetTextSize(40);
		tp->SetTextAngle(0);
		tp->Draw();

		TLine *l2 = new TLine(Ec2, 0.0, Ec2, 1.0);
		l2->SetLineColor(kBlue);
		l2->SetLineWidth(3);
		l2->SetLineStyle(2);
		l2->Draw();

		TText *t2 = new TText((Ec2 + 0.25), .3, "CE");
		t2->SetTextAlign(22);
		t2->SetTextColor(kBlue);
		t2->SetTextFont(43);
		t2->SetTextSize(40);
		t2->SetTextAngle(0);
		t2->Draw();


		TLine *l3 = new TLine(Ec3, 0.0, Ec3, 1.0);
		l3->SetLineColor(kYellow);
		l3->SetLineWidth(3);
		l3->SetLineStyle(2);
		l3->Draw();

		TText *t3 = new TText((Ec3 + 0.25), .3, "CE");
		t3->SetTextAlign(22);
		t3->SetTextColor(kYellow);
		t3->SetTextFont(43);
		t3->SetTextSize(40);
		t3->SetTextAngle(0);
		t3->Draw();
	}

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
	const char *filename0  ="../energy_20Mpc.txt";
	const char* filename20 ="../energy_20Mpc_Z_1.txt";
	const char* filename40 ="../energy_20Mpc_Z_2_Z_5.txt";
	const char* filename80 ="../energy_20Mpc_Z_6_Z_10.txt";

	ifstream input0(filename0);
	ifstream input20(filename20);
	ifstream input40(filename40);
	ifstream input80(filename80);


	const char *E0_all  ="../energy0_20Mpc.txt";
	const char* E0_Z_1 ="../energy0_20Mpc_Z_1.txt";
	const char* E0_Z_2_Z_5 ="../energy0_20Mpc_Z_2_Z_5.txt";
	const char* E0_z_6_z_10 ="../energy0_20Mpc_Z_6_Z_10.txt";


	ifstream input_all(E0_all);
	ifstream input_Z_1(E0_Z_1);
	ifstream input_Z_2_Z_5( E0_Z_2_Z_5);
	ifstream input_Z_6_Z_10(E0_z_6_z_10);

	//Filling the histograms 
	//The ideia of this program is make a hist of the Energy difference divided by the initial energy 

	hArrive0 = fillingHist(input0,input_all,atof(argv[4]),atof(argv[5]),atoi(argv[6]));
	hArrive20 = fillingHist(input20,input_Z_1,atof(argv[4]),atof(argv[5]),atoi(argv[6]));
	hArrive40 = fillingHist(input40,input_Z_2_Z_5,atof(argv[4]),atof(argv[5]),atoi(argv[6]));
	hArrive80 = fillingHist(input80,input_Z_6_Z_10,atof(argv[4]),atof(argv[5]),atoi(argv[6]));


	//Normalization	
	
	double_t factor =1.;
//Change in the normalization, now we normalize by the entries of all events
	hArrive0->Scale(factor/hArrive0->GetEntries());
 	hArrive20->Scale(factor/hArrive0->GetEntries());
	hArrive40->Scale(factor/hArrive0->GetEntries());
	hArrive80->Scale(factor/hArrive0->GetEntries());

	auto *c = new TCanvas("c","ASDJ",1200,1000);
	c->Divide(2,2);
	
	//Axis, canvas and legends properties
	hArrive0->SetLineColor(kRed);
	hArrive0->SetStats(0);
	hArrive0->GetYaxis()->SetRangeUser(1e-5,1e0);
	hArrive0->GetYaxis()->SetTitle("Count");
	hArrive0->GetXaxis()->SetTitle("Log(E/eV)");
	hArrive0->Draw("HIST");
	
	hArrive20->SetLineColor(kGreen);
	hArrive20->SetStats(0);
	hArrive20->Draw("HIST same");
	
	hArrive40->SetLineColor(kBlue);
	hArrive40->SetStats(0);
	hArrive40->Draw("Hist same");

	hArrive80->SetLineColor(kYellow);
	hArrive80->SetStats(0);
	hArrive80->Draw("Hist same");
	

	criticalEnergy(atof(argv[1]), atof(argv[2]) );
	
		
	auto leg = new TLegend(0.90,0.1,0.995,0.4);
	
	
	char pre[100]= "All events (N=";
	char su[100]=")";
	const char *coun=to_string(count(input0)).c_str();
	char result[100];

	strcpy(result,pre);
	strcat(result,coun);
	// leg->AddEntry(hArrive0,strcat(result,su), "L");
	leg->AddEntry(hArrive0,"All events", "L");	
	char pre20[100]= "Z=1 (N=";
	const char *coun20=to_string(count(input20)).c_str();
	char result20[100];

	
	strcpy(result20,pre20);
	strcat(result20,coun20);
	// leg->AddEntry(hArrive20,strcat(result20,su), "L");
	leg->AddEntry(hArrive20,"Z=1", "L");

	char pre40[100]= "2#leq Z #leq 5 (N=";
	const char *coun40=to_string(count(input40)).c_str();
	char result40[100];

	strcpy(result40,pre40);
	strcat(result40,coun40);
	// leg->AddEntry(hArrive40,strcat(result40,su), "L");
	leg->AddEntry(hArrive40,"2#leq Z #leq 5", "L");

	
	char pre80[100]= "6#leq Z #leq 10 (N=";
	const char *coun80=to_string(count(input80)).c_str();
	char result80[100];

	strcpy(result80,pre80);
	strcat(result80,coun80);
	// leg->AddEntry(hArrive80,strcat(result80,su), "L");
	leg->AddEntry(hArrive80,"6#leq Z #leq 10", "L");

	
	leg->Draw();

	c->SetLogy();
	c->SetCanvasSize(1200,600);
	c->SaveAs(argv[3]);
//	rint->Run(kTRUE);

}
