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
    int flag = 0;
    TLegend* legend = new TLegend(0.7,0.2,0.9,0.4);

    TCanvas* c1bis = new TCanvas( "c1bis", "multipads", 600, 600 );
    c1bis->Divide(1,4);
    std::vector<TH1D> hch, charge;
    
    
    
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
    
    charge.push_back(TH1D( "hch0", "", 10,- 0.001, 0.001 ));
    charge.push_back(TH1D( "hch1", "", 10,- 0.001, 0.001 ));
    charge.push_back(TH1D( "hch2", "", 10,- 0.001, 0.001 ));
    charge.push_back(TH1D( "hch3", "", 10,- 0.001, 0.001 ));
    charge.push_back(TH1D( "hch4", "", 10,- 0.001, 0.001 ));
    charge.push_back(TH1D( "hch5", "", 10,- 0.001, 0.001 ));
    charge.push_back(TH1D( "hch6", "", 10,- 0.001, 0.001 ));
    charge.push_back(TH1D( "hch7", "", 10,- 0.001, 0.001 ));
    charge.push_back(TH1D( "hch8", "", 10,- 0.001, 0.001 ));
    charge.push_back(TH1D( "hch9", "", 10,- 0.001, 0.001 ));
    charge.push_back(TH1D( "hch10", "", 10,- 0.001, 0.001 ));
    charge.push_back(TH1D( "hch11", "", 10,- 0.001, 0.001 ));
    charge.push_back(TH1D( "hch12", "", 10,- 0.001, 0.001 ));
    charge.push_back(TH1D( "hch13", "", 10,- 0.001, 0.001 ));
    charge.push_back(TH1D( "hch14", "", 10,- 0.001, 0.001 ));
    charge.push_back(TH1D( "hch15", "", 10,- 0.001, 0.001 ));
    
    
    gStyle->SetOptStat(1111111);
    
    
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;
        
        for(int i = 0; i < nch; i++){ //LOOP OVER CHANNELS
            Event event(ev, i+1, 1024);
            integral = event.trapezIntegrator(0,1024, pshape[i]);
            //  std::cout<< "integral : "<< integral << std::endl;
            
            //****************+ grafico 1 *******************************
            if(ev == 1 && integral < -2 ){
                event.pShapeHisto(pshape[i], filename.c_str());
            }
            
            //****************+ grafico 1 bis *******************************
            hch[i].Fill(event.baseline(pshape[i],1));
            
        }
        
        
    }
    
    int it=1;
    for(int j = 0; j < 4; j++) {
        c1bis->cd(j+1);
        c1bis->SetLogy();
,
        int i = 1;

        for(std::vector<TH1D>::iterator h = hch.begin()+(j*4); h != hch.begin()+(j+1)*4; h++) {
            
            h->Draw("same");
            h->SetLineColor(i);
            legend->AddEntry(&hch[it-1],Form("ch %d",it), "l");
            it++;
            c1bis->Update();
            i++;

        }
        legend->Draw();

    }
    size_t pos = 0;
    std::string prefix;
    if((pos = filename.find("_Ascii")) != std::string::npos) {
        prefix = filename.substr(0, pos);
    }
    
    std::string plotsDir( Form( "plots/%s", prefix.c_str() ) );
    system( Form( "mkdir -p %s", plotsDir.c_str() ) );
    c1bis->SaveAs( Form( "%s/baseline.pdf", plotsDir.c_str()) );
    delete c1bis;
    delete legend;
}
