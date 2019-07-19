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

#define minBin 50
#define CAL 600

void MeasTreeCo::Loop(std::string filename)
{
    //   In a ROOT session, you can do:
    //      root> .L MeasTreeCo.C
    //      root> MeasTreeCo t
    //      root> t.GetEntry(12); // Fill t data members with entry number 12
    //      root> t.Show();       // Show values of entry 12
    //      root> t.Show(16);     // Read and show values of entry 16
    //      root> t.Loop();       // Loop on all entries
    //
    
    //     This is the loop skeleton where:
    //    jentry is the global entry number in the chain
    //    ientry is the entry number in the current Tree
    //  Note that the argument to GetEntry must be:
    //    jentry for TChain::GetEntry
    //    ientry for TTree::GetEntry and TBranch::GetEntry
    //
    //       To read only selected branches, Insert statements like:
    // METHOD1:
    //    fChain->SetBranchStatus("*",0);  // disable all branches
    //    fChain->SetBranchStatus("branchname",1);  // activate branchname
    // METHOD2: replace line
    //    fChain->GetEntry(jentry);       //read all branches
    //by  b_branchname->GetEntry(ientry); //read only this branch
    /*  int ev=-1;
     int nch;
     float base     [128];
     float vamp     [128];
     float vcharge  [128];
     float letime   [128];
     float tetime   [128];
     float ratecount[128];
     float pshape   [128][1024]
     */
    if (fChain == 0) return;
    
    Long64_t nentries = fChain->GetEntriesFast();
    
    Long64_t nbytes = 0, nb = 0;
    
    int flag = 0;
    
    TCanvas* canvcharge = new TCanvas( "canvcharge", "canvcharge", 1200, 1200 );
    TCanvas* canvchargetot = new TCanvas( "canvchargetot", "canvchargetot", 1600, 800);
    
    TCanvas* canvPeak = new TCanvas( "canvPeak", "", 1300, 600 );
    
    TH1D* histoPeak = new TH1D( "peak", "Photopeak for Na-22 Back-To-Back", 18, -0.5, 17.5);

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

    std::cout << calib[1] << std::endl;
    
    std::vector<TH1D> charge;
    std::vector<TLegend> legend;

    TH1D chargeTot( "hchargeTot", "Na-22BB charge spectrum before calibration", 200, 0, 900 );
    TH1D chargeTotCal( "hchargeTot", "Na-22BB charge spectrum after calibration", 200, 0, 900 );
      
    double peak[16];
    
    size_t pos = 0;
    std::string prefix;
    if((pos = filename.find(".root")) != std::string::npos) {
        prefix = filename.substr(0, pos);
    }
    std::string plotsDir( Form( "plots/%sCo", prefix.c_str() ) );
    std::string chargesDir( Form( "plots/%sCo/charges", prefix.c_str() ) );
    
    system( Form( "mkdir -p %s", plotsDir.c_str() ) );
    system( Form( "mkdir -p %s", chargesDir.c_str() ) );
    
    charge.push_back(TH1D( "hcharge1", "", 100, 0, 1300));
    charge.push_back(TH1D( "hcharge2", "", 100, 0, 1300));
    charge.push_back(TH1D( "hcharge3", "", 100, 0, 1300));
    charge.push_back(TH1D( "hcharge4", "", 100, 0, 1300));
    charge.push_back(TH1D( "hcharge5", "", 100, 0, 1300));
    charge.push_back(TH1D( "hcharge6", "", 100, 0, 1300));
    charge.push_back(TH1D( "hcharge7", "", 100, 0, 1300));
    charge.push_back(TH1D( "hcharge8", "", 100, 0, 1300));
    charge.push_back(TH1D( "hcharge9", "", 100, 0, 1300));
    charge.push_back(TH1D( "hcharge10", "", 100, 0, 1300));
    charge.push_back(TH1D( "hcharge11", "", 100, 0, 1300));
    charge.push_back(TH1D( "hcharge12", "", 100, 0, 1300));
    charge.push_back(TH1D( "hcharge13", "", 100, 0, 1300));
    charge.push_back(TH1D( "hcharge14", "", 100, 0, 1300));
    charge.push_back(TH1D( "hcharge15", "", 100, 0, 1300));
    charge.push_back(TH1D( "hcharge16", "", 100, 0, 1300));
    
    
    gStyle->SetOptStat(1111111);
    
    
    for (Long64_t jentry=0; jentry<nentries;jentry++) { // LOOP OVER EVENTS
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;
	
	//std::cout << std::endl;
	
        for(int i = 0; i < nch; i++){ //LOOP OVER CHANNELS
	
	  //if(-vcharge[i]*calib[i] > minBin) chargeTot.Fill(-vcharge[i]*calib[i]);
	  //if(-vcharge[i] > minBin) charge[i].Fill(-vcharge[i]);
	 
	  if (-vcharge[i]*calib[i] > 50 && -vcharge[i-1+2*((i+1)%2)]*calib[i-1+2*((i+1)%2)] > 50) {
	    charge[i].Fill(-vcharge[i]);
	    chargeTot.Fill(-vcharge[i]);
	    chargeTotCal.Fill(-vcharge[i]*calib[i]);
	  }
	}
	  
    }
    

    
    //PLOT CHARGE
    for(int i=0;i<nch;i++){
        canvcharge->cd();
        
        peak[i]=charge[i].GetMaximumBin();
        
        TFitResultPtr r = charge[i].Fit("gaus","S","",(peak[i]-3)*13,(peak[i]+6)*13);
        histoPeak->SetBinContent(histoPeak->FindBin(i+1), r->Parameter(1));
        histoPeak->SetBinError(histoPeak->FindBin(i+1), r->Parameter(2));
        
        charge[i].Draw();
        canvcharge->SaveAs( Form( "%s/chargeCo_ch%d.pdf", chargesDir.c_str(), i+1) );
        canvcharge->Clear();
    }

    canvchargetot->Divide(2,1);
    
    canvchargetot->cd(1);
    chargeTot.SetXTitle("Charge (pC)");
    chargeTot.SetYTitle("# of events");
    chargeTot.GetYaxis()->SetRangeUser(0,740);
    chargeTot.Draw();
    
    canvchargetot->cd(2);
    chargeTotCal.SetXTitle("Charge (pC)");
    chargeTotCal.SetYTitle("# of events");
    chargeTotCal.GetYaxis()->SetRangeUser(0,740);
    chargeTotCal.Draw();
    
    canvchargetot->SaveAs( Form( "%s/chargeTotBis.pdf", chargesDir.c_str() ));
    canvchargetot->Clear();
			
    
    histoPeak->SetMarkerStyle(kFullCircle);
    histoPeak->SetMarkerColor(2);
    
    histoPeak->GetXaxis()->SetNdivisions(32,0,0);
    histoPeak->SetStats(0);
    histoPeak->SetLineColor(4);
    canvPeak->cd();
    canvPeak->SetGridy();
    
    histoPeak->SetXTitle("# of Channel");
    histoPeak->SetYTitle("Charge [pC]");
    gStyle->SetErrorX(0);
    gStyle->SetEndErrorSize(3);
    histoPeak->Draw("E1");
    canvPeak->SaveAs( Form( "%s/PeakDistrCH.pdf",plotsDir.c_str()) );

    fclose(fp);
    delete canvcharge, canvchargetot;
    
}

