#define MeasTreeCo_cxx
#include "MeasTreeCo.h"
#include <TH1.h>
#include <stdio.h>
#include <stdlib.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TF1.h>
#include <TFitResult.h>

#define histoMax 2000
#define histoMin 0
#define NBIN 100
#define minBin 1250     // 510
#define maxBin 1700     // 690

void MeasTreeCo::Loop(std::string filename) {
  
    if (fChain == 0) return;
    
    Long64_t nentries = fChain->GetEntriesFast();
    
    Long64_t nbytes = 0, nb = 0;
    
    int flag = 0;
    
    TCanvas* canvcharge = new TCanvas( "canvcharge", "canvcharge", 1200, 1200 );   
    TCanvas* canvPeak = new TCanvas( "canvPeak", "", 1300, 600 );
    TCanvas* canvDistr = new TCanvas( "canvDistr", "", 1600, 1200);
       
    TH1D* histoPeak = new TH1D( "peak", "Peak", 18, -0.5, 17.5);
    double peak[16];
    
    FILE* fp;
    fp = fopen("Calib.txt", "r");
    if(fp == NULL) {
      std::cout << "File Calib.txt not found. Exit!" << std::endl;
      exit(EXIT_FAILURE);
    }
    char buf[20];
    char *res;
    
    std::vector<double> calib;
    while(1) {
      res = fgets(buf, 20, fp);
      if (res == NULL) break;
      calib.push_back(atof(res));
    }
    
    std::vector<TH1D> charge;
    std::vector<TLegend> legend;

    TH1D chargeTot( "hchargeTot", "", 3*NBIN, histoMin, histoMax );
    TH1D* angleDistr = new TH1D( "angleDistr", "Angular Distribution Noise", 10, -11.25, 213.75);
    TH1D* angleDistrNorm = new TH1D( "angleDistrNorm", "Normalized Angular Distribution Co-60", 10, -11.25, 213.75);
      
    size_t pos = 0;
    std::string prefix;
    if((pos = filename.find(".root")) != std::string::npos) {
        prefix = filename.substr(0, pos);
    }
    std::string plotsDir( Form( "plots/%sCo", prefix.c_str() ) );
    std::string chargesDir( Form( "plots/%sCo/charges", prefix.c_str() ) );
    
    system( Form( "mkdir -p %s", plotsDir.c_str() ) );
    system( Form( "mkdir -p %s", chargesDir.c_str() ) );
    
    charge.push_back(TH1D( "hcharge1", "", NBIN, histoMin, 800));
    charge.push_back(TH1D( "hcharge2", "", NBIN, histoMin, 800));
    charge.push_back(TH1D( "hcharge3", "", NBIN, histoMin, 800));
    charge.push_back(TH1D( "hcharge4", "", NBIN, histoMin, 800));
    charge.push_back(TH1D( "hcharge5", "", NBIN, histoMin, 800));
    charge.push_back(TH1D( "hcharge6", "", NBIN, histoMin, 800));
    charge.push_back(TH1D( "hcharge7", "", NBIN, histoMin, 800));
    charge.push_back(TH1D( "hcharge8", "", NBIN, histoMin, 800));
    charge.push_back(TH1D( "hcharge9", "", NBIN, histoMin, 800));
    charge.push_back(TH1D( "hcharge10", "", NBIN, histoMin, 800));
    charge.push_back(TH1D( "hcharge11", "", NBIN, histoMin, 800));
    charge.push_back(TH1D( "hcharge12", "", NBIN, histoMin, 800));
    charge.push_back(TH1D( "hcharge13", "Charge spectrum Ch 13", NBIN, histoMin, 800));
    charge.push_back(TH1D( "hcharge14", "", NBIN, histoMin, 800));
    charge.push_back(TH1D( "hcharge15", "", NBIN, histoMin, 800));
    charge.push_back(TH1D( "hcharge16", "", NBIN, histoMin, 800));    
    
    gStyle->SetOptStat(1111111);

    double i_angle, j_angle;
    int goodCh;
    std::vector<int> nGoodCh;

    // LOOP OVER EVENTS
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
      
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);
      nbytes += nb;
      
      goodCh = 0;

      //LOOP OVER CHANNELS
      for(int i = 0; i < nch; i++){ 
	
	if ( (-vcharge[i]*calib[i] > minBin) && (-vcharge[i]*calib[i] < maxBin) ){
	  goodCh++;
	  nGoodCh.push_back(i);
	}
	
	// Only back to back	
	if (-vcharge[i]*calib[i] > minBin && -vcharge[i-1+2*((i+1)%2)]*calib[i-1+2*((i+1)%2)] > minBin)
	  charge[i].Fill(-vcharge[i]);//*calib[i]);

	// Loop over all channels coincidence		
	/*for( int j = 0; j < nch; j++){
	  if ((-vcharge[i]*calib[i] > minBin) && (-vcharge[j]*calib[j] > minBin) && j!=i) {
	    charge[i].Fill((-vcharge[i])*calib[i]);
	    chargeTot.Fill((-vcharge[i])*calib[i]);	     
	    break;
	  }
	  }*/


	// Charge histo without coincidence
	/*if ((-vcharge[i]*calib[i] > 50) && (-vcharge[i]*calib[i] < 2000)) {
	  charge[i].Fill((-vcharge[i])*calib[i]);
	  chargeTot.Fill((-vcharge[i])*calib[i]);
	  }*/
	
      }
      
      
      if(goodCh == 2) {
	
	i_angle = (nGoodCh[0]/2)*22.5 + (nGoodCh[0]%2)*180;
	j_angle = (nGoodCh[1]/2)*22.5 + (nGoodCh[1]%2)*180;
	if(abs(j_angle-i_angle)<=180) {
	 angleDistr->Fill(abs(j_angle-i_angle));
	}	      
	else {
	 angleDistr->Fill(360-abs(j_angle-i_angle));
	}
  
      }
      
      nGoodCh.clear();
      
    }

    //PLOT CHARGE
    for(int i=0;i<nch;i++){
      canvcharge->cd();
      
      peak[i]=charge[i].GetMaximumBin();
      
     
      charge[i].GetXaxis()->SetTitle("Charge (pC)");
      charge[i].GetYaxis()->SetTitle("No of events");
      charge[i].Draw();
     
      canvcharge->SaveAs( Form( "%s/chargeCo_ch%d.pdf", chargesDir.c_str(), i+1) );
      canvcharge->Clear();
    }
    
    /*for(int i=0;i<nch;i++){
      canvcharge->cd();      
      charge[i].Draw();
      canvcharge->SaveAs( Form( "%s/chargeCo_ch%d.pdf", chargesDir.c_str(), i+1) );
      canvcharge->Clear();
      }*/

    canvcharge->cd();
    chargeTot.Draw();
    canvcharge->SaveAs( Form( "%s/chargeTot.pdf", chargesDir.c_str() ));
    canvcharge->Clear();

    
    canvDistr->cd();
    for(int i=1; i <= 8; i++){
      angleDistr->SetBinContent(i, angleDistr->GetBinContent(i)/2.);
    }
    angleDistr->GetXaxis()->SetTitle("Angle (#circ)");
    angleDistr->GetYaxis()->SetTitle("No of events");
    //angleDistr->GetXaxis()->SetLimits(0., 202.5);
    angleDistr->GetXaxis()->SetMaxDigits(3);
    angleDistr->GetXaxis()->SetNdivisions(-10, -2, 0);
    //gStyle->SetStatY(0.6);
    //gStyle->SetHistLineColor(3);
    angleDistr->Draw();      
    canvDistr->SaveAs( Form( "%s/angleDistr.pdf", plotsDir.c_str() ));
    canvDistr->Clear();

    for(int i=1; i <= 9; i++) {
      angleDistrNorm->SetBinContent(i, (angleDistr->GetBinContent(i))/double(angleDistr->GetBinContent(5)));
      std::cout << angleDistr->GetBinContent(i) << std::endl;
    }
    TF1* angFunc = new TF1("angDistrTeo", "1 + (cos(x*3.14/180))^2/8 + (cos(x*3.14/180))^4/24", 0, 180);

    canvDistr->cd();
    angleDistrNorm->GetYaxis()->SetRangeUser(0.8, 1.5);
    angleDistrNorm->GetXaxis()->SetTitle("Angle (#circ)");
    angleDistrNorm->GetYaxis()->SetTitle("No of events");
    angleDistrNorm->GetXaxis()->SetMaxDigits(3);    
    angleDistrNorm->Draw();
    angFunc->Draw("SAME");
    canvDistr->SaveAs( Form( "%s/angleDistrNorm.pdf", plotsDir.c_str() ));
    canvDistr->Clear();

    fclose(fp);
    delete canvcharge, canvDistr;

  
}

