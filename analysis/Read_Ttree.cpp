//
//  Read_Ttree.cpp
//
//
//  Created by Gioacchino Piazza on 29/10/2018.
//

#include <stdio.h>
#include <vector>
#include <iostream>

//#include "Datum.h"
#include "DataTree.h"
#include "TTree.h"

int main(int argc, char* argv[]){
    
    if(argc!=2){
        std::cout <<"ERROR in calling app. \t usage ./Read_Ttree.exe name_rootFile.root" << std::endl;
        exit(-1);
    }
    
    
    // ==== Read data from file
    std::string fileName(argv[1]);
    TFile* rootFile = new TFile (fileName.c_str());
    if(!rootFile->IsOpen()){ std::cout <<"ERROR in opening root file" << std::endl; exit(-1); }
    
    std::cout << "Reading data from root file " << fileName.c_str() << std::endl;
    
    
    TTree* tree = (TTree*) rootFile->Get("tree");
    
    if(!tree) { std::cout << "null pointer for TTree! exiting..." << std::endl; exit(-1); }
    
    std::cout << "Reading data from root tree " << std::endl;
    
    DataTree function(tree);
    
    function.Loop();
    
    
    rootFile->Close();
    return 0;
    
}
