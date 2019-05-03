#define DataTree_cxx
#include "DataTree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>

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

    TCanvas* c1bis = new TCanvas( "c1bis", "multipads", 600, 600 );
    TCanvas* canvcharge = new TCanvas( "canvcharge", "canvcharge", 600, 600 );
    TCanvas* canvDeltaBase = new TCanvas( "canvDeltaBase", "canvDeltaBase", 600, 600 );

    TH1D histoBase = new TH1D( "baseline", "baseline", 100, 0, 17 )
    
    c1bis->Divide(1,4);
    std::vector<TH1D> hch, charge;
    std::vector<TLegend> legend;
    
    size_t pos = 0;
    std::string prefix;
    if((pos = filename.find("_Ascii")) != std::string::npos) {
        prefix = filename.substr(0, pos);
    }
    std::string plotsDir( Form( "plots/%s", prefix.c_str() ) );
    std::string chargesDir( Form( "plots/%s/charges", prefix.c_str() ) );

    system( Form( "mkdir -p %s", plotsDir.c_str() ) );
    system( Form( "mkdir -p %s", chargesDir.c_str() ) );

    hch.push_back(TH1D( "hch0", "", 100,- 0.001, 0.001 ));
    hch.push_back(TH1D( "hch1", "", 100,- 0.001, 0.001 ));
    hch.push_back(TH1D( "hch2", "", 100,- 0.001, 0.001 ));
    hch.push_back(TH1D( "hch3", "", 100,- 0.001, 0.001 ));
    hch.push_back(TH1D( "hch4", "", 100,- 0.001, 0.001 ));
    hch.push_back(TH1D( "hch5", "", 100,- 0.001, 0.001 ));
    hch.push_back(TH1D( "hch6", "", 100,- 0.001, 0.001 ));
    hch.push_back(TH1D( "hch7", "", 100,- 0.001, 0.001 ));
    hch.push_back(TH1D( "hch8", "", 100,- 0.001, 0.001 ));
    hch.push_back(TH1D( "hch9", "", 100,- 0.001, 0.001 ));
    hch.push_back(TH1D( "hch10", "", 100,- 0.001, 0.001 ));
    hch.push_back(TH1D( "hch11", "", 100,- 0.001, 0.001 ));
    hch.push_back(TH1D( "hch12", "", 100,- 0.001, 0.001 ));
    hch.push_back(TH1D( "hch13", "", 100,- 0.001, 0.001 ));
    hch.push_back(TH1D( "hch14", "", 100,- 0.001, 0.001 ));
    hch.push_back(TH1D( "hch15", "", 100,- 0.001, 0.001 ));
    
    charge.push_back(TH1D( "hcharge0", "", 100, 0, 60 ));
    charge.push_back(TH1D( "hcharge1", "", 100, 0, 60 ));
    charge.push_back(TH1D( "hcharge2", "", 100, 0, 60 ));
    charge.push_back(TH1D( "hcharge3", "", 100, 0, 60 ));
    charge.push_back(TH1D( "hcharge4", "", 100, 0, 60 ));
    charge.push_back(TH1D( "hcharge5", "", 100, 0, 60 ));
    charge.push_back(TH1D( "hcharge6", "", 100, 0, 60 ));
    charge.push_back(TH1D( "hcharge7", "", 100, 0, 60 ));
    charge.push_back(TH1D( "hcharge8", "", 100, 0, 60 ));
    charge.push_back(TH1D( "hcharge9", "", 100, 0, 60 ));
    charge.push_back(TH1D( "hcharge10", "", 100, 0, 60 ));
    charge.push_back(TH1D( "hcharge11", "", 100, 0, 60 ));
    charge.push_back(TH1D( "hcharge12", "", 100, 0, 60 ));
    charge.push_back(TH1D( "hcharge13", "", 100, 0, 60 ));
    charge.push_back(TH1D( "hcharge14", "", 100, 0, 60 ));
    charge.push_back(TH1D( "hcharge15", "", 100, 0, 60 ));
    
    legend.push_back(TLegend(0.7,0.2,0.9,0.4));
    legend.push_back(TLegend(0.7,0.2,0.9,0.4));
    legend.push_back(TLegend(0.7,0.2,0.9,0.4));
    legend.push_back(TLegend(0.7,0.2,0.9,0.4));

    TH1D* hDeltaBase = new TH1D( "hDbase", "", 100,- 100, 100 );
    
    gStyle->SetOptStat(1111111);
    
    
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;
       
        
        
       
        
        for(int i = 0; i < nch; i++){ //LOOP OVER CHANNELS
            Event event(ev, i+1, 1024);
            integral = event.trapezIntegrator(0,1024, pshape[i])-(baseline*1024.);
            baseline = event.baseline(pshape[i],1);
            //  std::cout<< "integral : "<< integral << std::endl;
            
            //****************+ grafico 1 *******************************
            if(ev == 1 && integral < -2 ){
                event.pShapeHisto(pshape[i], filename.c_str());
            }
            
            //****************+ grafico 1 bis *******************************
            hch[i].Fill(event.baseline(pshape[i],1));
            
            //****************+ grafico delta base. *******************************

            if (i == 0 && integral < -2 && integral > -200 ) hDeltaBase->Fill((baseline-base[i])/base[i]);
            
            //****************+ grafico compt.edge *******************************
           // if (integral<-0.5){
                charge[i].Fill((-integral));
           // }

         //   if (integral < -300) std::cout << "ATT: ev " << ev << "ch " <<i+1<< std::endl;
        }
        
        
    }
    //PLOT CHARGE
    for(int i=0;i<nch;i++){
        canvcharge->cd();
        charge[i].Draw();
        canvcharge->SaveAs( Form( "%s/charge_ch%d.pdf", chargesDir.c_str(), i+1) );
        canvcharge->Clear();
        
    }
    //PLOT DELTA BASE
    canvDeltaBase->cd();
    canvDeltaBase->SetLogy();
    hDeltaBase->Draw();
    canvDeltaBase->SaveAs( Form( "%s/DeltaBase_ch%d.pdf", plotsDir.c_str(),1 ) );

    //PLOT BASELINE
    int it=1;
    for(int j = 0; j < 4; j++) {
        c1bis->cd(j+1);
        c1bis->SetLogy();

        int i = 1;

        for(std::vector<TH1D>::iterator h = hch.begin()+(j*4); h != hch.begin()+(j+1)*4; h++) {
            
            legend[j].AddEntry(&hch[it-1],Form("ch %d",it), "l");
            h->Draw("same");
            h->SetLineColor(i);
            it++;
            c1bis->Update();
            i++;

        }
        legend[j].Draw();

    }
    c1bis->SaveAs( Form( "%s/baseline.pdf", plotsDir.c_str()) );
    delete c1bis;
    delete canvcharge;
    delete canvDeltaBase;
    
}