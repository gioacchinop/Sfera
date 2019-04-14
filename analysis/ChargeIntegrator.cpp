//
//  ChargeIntegrator.cpp
//  
//
//  Created by Gioacchino Piazza on 11/04/2019.
//

//#include "ChargeIntegrator.hpp"
#include <iostream>
#include <stdlib.h>

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"

#include "TRintegrator.h"

using namespace std;




int main( int argc, char* argv[] ) {
    
    if( argc!= 4 ) {
        std::cout << "USAGE: ./ChargeIntegrator [rootFileName] [event] [channel]" << std::endl;
        exit(1);
    }
    
    std::string fileName(argv[1]);
    int event  (atoi(argv[2]));
    int channel(atoi(argv[3]));
    
    
    TFile* file = TFile::Open(fileName.c_str());
    TTree* tree = (TTree*)file->Get("tree");
    
    TH1D* h1 = new TH1D("h1", "", 1024, 0., 1024. );
    TCanvas* c1 = new TCanvas("c1", "c1", 600, 600);
    c1->cd();

    if(file) std::cout << "-> Opened file " << fileName.c_str() << std::endl;
    std::cout << "-> Integrate pulse shape of event: " << event << ", channel: " << channel << std::endl;

    int ev;
    int nch;
    double letime[128];
    double tetime[128];
    double pshape[128][1024];
    double vcharge[128];
    
    tree->SetBranchAddress( "ev"    , &ev     );
    tree->SetBranchAddress( "nch"   , &nch    );
    tree->SetBranchAddress( "pshape", &pshape );
    tree->SetBranchAddress( "letime", &letime );
    tree->SetBranchAddress( "tetime", &tetime );
    tree->SetBranchAddress( "vcharge", &vcharge );

    int nentries = tree->GetEntries();
    
    for( unsigned iEntry=0; iEntry<nentries; ++iEntry ) {
        
        tree->GetEntry(iEntry);
        
        if( ev!=event ) continue;
        if( channel>=nch ) {
            std::cout << "Event " << ev << " does not have channel " << channel << " (nch=" << nch << ")." << std::endl;
            exit(11);
        }
        
        for( unsigned i=0; i<1024; ++i ){
            h1->SetBinContent( i+1, pshape[channel][i] );
	    std::cout << pshape[channel][i] << std::endl;
        }
    }
    
    h1->Draw();
    
    size_t pos = 0;
    std::string prefix;
    if((pos = fileName.find(".")) != std::string::npos) {
      prefix = fileName.substr(0, pos);
    }
    
    std::string plotsDir(Form("plots/%s", prefix.c_str()));
    system( Form("mkdir -p %s", plotsDir.c_str()) );
    
    c1->SaveAs(Form("%s/pulseShape_ev%d_ch%d.eps",plotsDir.c_str(),event,channel));
    c1->SaveAs(Form("%s/pulseShape_ev%d_ch%d.pdf",plotsDir.c_str(),event,channel));

    TRIntegrator* TRint = new TRIntegrator(1024);
    double *integrand = pshape[channel];
    
    double integral = TRint->integrate(tetime[channel], letime[channel], integrand);
    std::cout << "Channel:" << channel << std::endl;
    std::cout << "Integral Value:" << integral << std::endl;
    std::cout << "Vcharge by Anal Software:" << vcharge[channel] << std::endl;
    std::cout << "delta t:" << tetime[channel] <<"..." <<letime[channel] << std::endl;

    return 0;
}
