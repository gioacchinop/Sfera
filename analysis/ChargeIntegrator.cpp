//
//  ChargeIntegrator.cpp
//  
//
//  Created by Gioacchino Piazza on 11/04/2019.
//

#include "ChargeIntegrator.hpp"
#include <iostream>
#include <stdlib.h>

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TCanvas.h"




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

    if(file) std::cout << "-> Opened file " << fileName.c_str() << std::endl;
    std::cout << "-> Integrate pulse shape of event: " << event << ", channel: " << channel << std::endl;

    int ev;
    int nch;
    float letime[128];
    float tetime[128];
    float pshape[128][1024];
    
    tree->SetBranchAddress( "ev" , &ev     );
    tree->SetBranchAddress( "nch"   , &nch    );
    tree->SetBranchAddress( "pshape", &pshape );
    tree->SetBranchAddress( "letime", &letime );
    tree->SetBranchAddress( "tetime", &tetime );

    int nentries = tree->GetEntries();
    
    for( unsigned iEntry=0; iEntry<nentries; ++iEntry ) {
        
        tree->GetEntry(iEntry);
        
        if( ev!=event ) continue;
        if( channel>=nch ) {
            std::cout << "Event " << ev << " does not have channel " << channel << " (nch=" << nch << ")." << std::endl;
            exit(11);
        }
        
        for( unsigned j=0; j<1024; ++j ){
            h1->SetBinContent( j+1, pshape[channel][j] );
        }
    }
    h1->Draw();
    c1->SaveAs(Form("pulseShape_ev%d_ch%d.pdf",event,channel));

    double integral;
    integral = ((tetime[channel]-letime[channel])/1024)*h1->Integral();
    std::cout << "Integral Value:" << integral << std::endl;
    std::cout << "delta t:" << tetime[channel] <<"..." <<letime[channel] << std::endl;

    return 0;
}
