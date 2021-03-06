#define DataTree_cxx
#include "DataTree.h"
#include <TH1.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TF1.h>
#include <TFitResult.h>

#include "Event.h"

#define TRESHOLD 10000
void DataTree::Loop(std::string filename)
{
    //   In a ROOT session, you can do:
    //      root> .L DataTree.C
    //      root> DataTree t
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
    
    double integral=0;
    double baseline = 0;
    int flag = 0;
    
    TCanvas* c1bis = new TCanvas( "c1bis", "multipads", 1200, 1200 );
    TCanvas* canvcharge = new TCanvas( "canvcharge", "canvcharge", 900, 600 );
    TCanvas* canvDeltaBase = new TCanvas( "canvDeltaBase", "canvDeltaBase", 900, 600 );
    TCanvas* canvDeltaCharge = new TCanvas( "canvDeltaCharge", "", 900, 600 );
    TCanvas* canvBaseCH = new TCanvas( "canvBaseCH", "", 1300, 600 );
    TCanvas* canvPeak = new TCanvas( "canvPeak", "", 1300, 600 );
    
    TH1D* histoBase = new TH1D( "baseline", "Mean Baseline", 18, -0.5, 17.5 );
    TH1D* histoPeak = new TH1D( "peak", "Peak", 18, -0.5, 17.5);
    
    c1bis->Divide(1,4);
    std::vector<TH1D> hchBase, charge, deltaCharge;
    std::vector<TLegend> legend;
    
    double peak[16];
    
    size_t pos = 0;
    std::string prefix;
    if((pos = filename.find("_Ascii")) != std::string::npos) {
        prefix = filename.substr(0, pos);
    }
    std::string plotsDir( Form( "plots/%s", prefix.c_str() ) );
    std::string chargesDir( Form( "plots/%s/charges", prefix.c_str() ) );
    
    system( Form( "mkdir -p %s", plotsDir.c_str() ) );
    system( Form( "mkdir -p %s", chargesDir.c_str() ) );
    
    hchBase.push_back(TH1D( "hchBase1", "" , 100,- 1, 1 ));
    hchBase.push_back(TH1D( "hchBase2", "", 100,- 1, 1 ));
    hchBase.push_back(TH1D( "hchBase3", "", 100,- 1, 1 ));
    hchBase.push_back(TH1D( "hchBase4", "", 100,- 1, 1 ));
    hchBase.push_back(TH1D( "hchBase5", "", 100,- 1, 1 ));
    hchBase.push_back(TH1D( "hchBase6", "", 100,- 1, 1 ));
    hchBase.push_back(TH1D( "hchBase7", "", 100,- 1, 1 ));
    hchBase.push_back(TH1D( "hchBase8", "", 100,- 1, 1 ));
    hchBase.push_back(TH1D( "hchBase9", "", 100,- 1, 1 ));
    hchBase.push_back(TH1D( "hchBase10", "", 100,- 1, 1 ));
    hchBase.push_back(TH1D( "hchBase11", "", 100,- 1, 1 ));
    hchBase.push_back(TH1D( "hchBase12", "", 100,- 1, 1 ));
    hchBase.push_back(TH1D( "hchBase13", "", 100,- 1, 1 ));
    hchBase.push_back(TH1D( "hchBase14", "", 100,- 1, 1 ));
    hchBase.push_back(TH1D( "hchBase15", "", 100,- 1, 1 ));
    hchBase.push_back(TH1D( "hchBase16", "", 100,- 1, 1 ));
    
    charge.push_back(TH1D( "hcharge1", "", 80, 0, 60 ));
    charge.push_back(TH1D( "hcharge2", "", 80, 0, 60 ));
    charge.push_back(TH1D( "hcharge3", "", 80, 0, 60 ));
    charge.push_back(TH1D( "hcharge4", "", 80, 0, 60 ));
    charge.push_back(TH1D( "hcharge5", "", 80, 0, 60 ));
    charge.push_back(TH1D( "hcharge6", "", 80, 0, 60 ));
    charge.push_back(TH1D( "hcharge7", "", 80, 0, 60 ));
    charge.push_back(TH1D( "hcharge8", "", 80, 0, 60 ));
    charge.push_back(TH1D( "hcharge9", "", 80, 0, 60 ));
    charge.push_back(TH1D( "hcharge10", "", 80, 0, 60 ));
    charge.push_back(TH1D( "hcharge11", "", 80, 0, 60 ));
    charge.push_back(TH1D( "hcharge12", "", 80, 0, 60 ));
    charge.push_back(TH1D( "hcharge13", "", 80, 0, 60 ));
    charge.push_back(TH1D( "hcharge14", "", 80, 0, 60 ));
    charge.push_back(TH1D( "hcharge15", "", 80, 0, 60 ));
    charge.push_back(TH1D( "hcharge16", "", 80, 0, 60 ));
    
    deltaCharge.push_back(TH1D( "hch1dc", "", 100, 0.048, 0.058 ));
    deltaCharge.push_back(TH1D( "hch2dc", "", 100, 0.048, 0.058 ));
    deltaCharge.push_back(TH1D( "hch3dc", "", 100, 0.048, 0.058 ));
    deltaCharge.push_back(TH1D( "hch4dc", "", 100, 0.048, 0.058 ));
    deltaCharge.push_back(TH1D( "hch5dc", "", 100, 0.048, 0.058 ));
    deltaCharge.push_back(TH1D( "hch6dc", "", 100, 0.048, 0.058 ));
    deltaCharge.push_back(TH1D( "hch7dc", "", 100, 0.048, 0.058 ));
    deltaCharge.push_back(TH1D( "hch8dc", "", 100, 0.048, 0.058 ));
    deltaCharge.push_back(TH1D( "hch9dc", "", 100, 0.048, 0.058 ));
    deltaCharge.push_back(TH1D( "hch10dc", "", 100, 0.048, 0.058 ));
    deltaCharge.push_back(TH1D( "hch11dc", "", 100, 0.048, 0.058 ));
    deltaCharge.push_back(TH1D( "hch12dc", "", 100, 0.048, 0.058 ));
    deltaCharge.push_back(TH1D( "hch13dc", "", 100, 0.048, 0.058 ));
    deltaCharge.push_back(TH1D( "hch14dc", "", 100, 0.048, 0.058 ));
    deltaCharge.push_back(TH1D( "hch15dc", "", 100, 0.048, 0.058 ));
    deltaCharge.push_back(TH1D( "hch16dc", "", 100, 0.048, 0.058 ));
    
    
    legend.push_back(TLegend(0.83,0.6,0.9,0.8));
    legend.push_back(TLegend(0.83,0.6,0.9,0.8));
    legend.push_back(TLegend(0.83,0.6,0.9,0.8));
    legend.push_back(TLegend(0.83,0.6,0.9,0.8));
    
    TH1D* hDeltaBase = new TH1D( "hDbase", "", 100,- 100, 100 );
    
    gStyle->SetOptStat(1111111);
    
    
    for (Long64_t jentry=0; jentry<nentries;jentry++) { // LOOP OVER EVENTS
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;
        
        for(int i = 0; i < nch; i++){ //LOOP OVER CHANNELS
            Event event(ev, i+1, 1024);
            baseline = event.baseline(pshape[i],2);
            integral = event.trapezIntegrator(0,1024, pshape[i])-(baseline*1024);
            //  std::cout<< "integral : "<< integral << std::endl;
            
            //***************** grafico 1 *******************************
            if(ev == 47 && integral < -2 ){
                event.pShapeHisto(pshape[i], filename.c_str());
            }
            
            //***************** grafico 1 bis *******************************
            hchBase[i].Fill(1000*baseline);
            
            //***************** grafico delta base. *******************************
            
            if (i == 0 ) hDeltaBase->Fill((baseline-base[i])/base[i]);
            
            //***************** grafico 2 *******************************
            if (integral<-2 && integral > -200) deltaCharge[i].Fill(integral/vcharge[i]);
            
            //***************** grafico 3 *******************************
            if (integral<-5 && integral > -200){
                charge[i].Fill((-integral));
                
            }
            
        }
        
        
    }
    
    //PLOT CHARGE
    for(int i=0;i<nch;i++){
        canvcharge->cd();
        
        peak[i]=charge[i].GetMaximumBin();
        
        TFitResultPtr r = charge[i].Fit("gaus","S","",(peak[i]-3)*3./4,(peak[i]+6)*3./4);
        histoPeak->SetBinContent(histoPeak->FindBin(i+1), r->Parameter(1));
        histoPeak->SetBinError(histoPeak->FindBin(i+1), r->Parameter(2));
        
        charge[i].Draw();
        canvcharge->SaveAs( Form( "%s/charge_ch%d.pdf", chargesDir.c_str(), i+1) );
        canvcharge->Clear();
    }
    
    histoPeak->SetMarkerStyle(kFullCircle);
    histoPeak->SetMarkerColor(2);
    
    histoPeak->GetXaxis()->SetNdivisions(32,0,0);
    histoPeak->SetStats(0);
    histoPeak->SetLineColor(4);
    canvPeak->cd();
    canvPeak->SetGridy();
    
    histoPeak->SetXTitle("# of Channel");
    histoPeak->SetYTitle("Peak [V]");//OOOOOOOOOOO UNITà DELLA CARICA????????????????????????????????????????????????????????????
    gStyle->SetErrorX(0);
    gStyle->SetEndErrorSize(3);
    histoPeak->Draw("E1");
    canvPeak->SaveAs( Form( "%s/PeakDistrCH.pdf",plotsDir.c_str()) );
    canvPeak->Clear();
    
    //PLOT DELTA CHARGE
    for(int i=0;i<nch;i++){
        canvDeltaCharge->cd();
        //canvDeltaCharge->SetLogy();
        
        deltaCharge[i].Draw();
        deltaCharge[i].SetTitle(Form("Charge's ratio : Integral/WaveCatcher ch. %d", i+1));
        deltaCharge[i].SetXTitle("(Pshape integr.)/(WC charge) [V/C]"); //OOOOOOOOOOO UNITà DELLA CARICA??????????????????????????????????????????????????????????
        deltaCharge[i].SetYTitle("# of events");
        canvDeltaCharge->SaveAs( Form( "%s/deltaCharge_ch%d.pdf", chargesDir.c_str(), i+1) );
        canvDeltaCharge->Clear();
    }
    
    //PLOT DELTA BASE
    canvDeltaBase->cd();
    canvDeltaBase->SetLogy();
    hDeltaBase->Draw();
    canvDeltaBase->SaveAs( Form( "%s/DeltaBase_ch%d.pdf", plotsDir.c_str(),1 ) );
    
    //PLOT BASELINE CON PUNTI E ERRORI
    for(int i=0;i<nch;i++){
        histoBase->SetBinContent(histoBase->FindBin(i+1), hchBase[i].GetMean());
        histoBase->SetBinError(histoBase->FindBin(i+1), hchBase[i].GetRMS());
    }
    histoBase->SetMarkerStyle(kFullCircle);
    histoBase->SetMarkerColor(2);
    
    histoBase->GetXaxis()->SetNdivisions(32,0,0);
    histoBase->SetStats(0);
    histoBase->SetLineColor(4);
    canvBaseCH->cd();
    canvBaseCH->SetGridy();
    
    histoBase->SetXTitle("# of Channel");
    histoBase->SetYTitle("<Baseline> [mV]");
    gStyle->SetErrorX(0);
    gStyle->SetEndErrorSize(3);
    histoBase->Draw("E1");
    canvBaseCH->SaveAs( Form( "%s/BaseAllCH.pdf",plotsDir.c_str()) );
    
    
    
    //PLOT BASELINE
    int it=1;
    c1bis->SetTitle("Histo. of baselines for every channel");
    
    for(int j = 0; j < 4; j++) {
        c1bis->cd(j+1);
        gPad-> SetLogy();
        int i = 1;
        
        for(std::vector<TH1D>::iterator h = hchBase.begin()+(j*4); h != hchBase.begin()+(j+1)*4; h++) {
            
            legend[j].AddEntry(&hchBase[it-1],Form("ch %d",it), "l");
            h->SetXTitle("Baseline [mV]");
            h->SetStats(0);
            h->GetXaxis()->SetLabelSize(0.09);
            h->GetXaxis()->SetTitleSize(0.09);
            h->GetXaxis()->SetTitleOffset(-0.8);
            
            h->GetYaxis()->SetLabelSize(0.06);
            
            h->Draw("same");
            h->SetLineColor(i);
            it++;
            c1bis->Update();
            i++;
            
        }
        legend[j].SetTextSize(0.06);
        legend[j].Draw();
        
    }
    c1bis->SaveAs( Form( "%s/baseline.pdf", plotsDir.c_str()) );
    delete c1bis;
    delete canvcharge;
    delete canvDeltaBase;
    delete  canvBaseCH;
    delete canvDeltaCharge;
}
