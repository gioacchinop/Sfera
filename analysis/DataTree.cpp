#define DataTree_cxx
#include "DataTree.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
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
    //CREATE PLOT FOR NOT-EVENTS CHARGES
    TCanvas *c1 = new TCanvas("c1","c1",900,700);
    TH1D* h1 = new TH1D("h1", "", 150,-5000,20);
    TH1D* h2 = new TH1D("h2", "", 150, 0., 150.);
    TH1D* h3 = new TH1D("h1", "", 1024, 0., 1024. );
    TH1D* h4 = new TH1D("h2", "", 1024, 0., 1024. );
    
    // gStyle->SetOptStat(0);
    // c1->Divide(2,1,0,0);
    
    //CREATE PLOT FOR GOOD EVENTS CHARGES
    TCanvas *c2 = new TCanvas("c2","multipads",900,700);
    TH1D* h5 = new TH1D("h3", "", 1024, 0., 1024. );
    TH1D* h6 = new TH1D("h4", "", 1024, 0., 1024. );
    
    double integral=0;
    int flag=0;
    
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;
        for(int i = 0; i < nch; i++){ //LOOP OVER CHANNELS
            Event event(ev, i+1, 1024);
            integral = event.trapezIntegrator(0,1024, pshape[i]);
            std::cout << "integral: " << integral << std::endl;
            /* h1->Fill(integral);
             h2->SetBinContent(ev, vcharge[2]);
             */
            if(integral<-50  && flag == 0){
                std::cout << "SUCA" << std::endl;
                event.pShapeHisto(pshape[i], filename.c_str());
                flag=1;
            }
        }
        //c1->cd();
        //h1->Draw();
        //c1->Update();
        //h2->Draw();
        size_t pos = filename.find(".") ;
        std::string prefix = filename.substr(0, pos);
        //c1->SaveAs(Form("Analysis_%s", prefix.c_str()));
    }
}
