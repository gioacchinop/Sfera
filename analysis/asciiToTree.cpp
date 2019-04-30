#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"




int main( int argc, char* argv[] ) {
    
    if( argc != 2 ) {
        
        std::cout << "USAGE: ./asciiToTree [filename]" << std::endl;
        exit(1);
        
    }
    
    std::string fileName(argv[1]);
    TString fileName_tstr(fileName);
    
    if( fileName_tstr.BeginsWith("../data/") ) {
        fileName.erase( 0, 8 );
    }
    
    
    std::ifstream fs(Form("../data/%s", fileName.c_str()));
    if( !fs.good() ) {
        std::cout << "-> No file called '" << fileName << "' found in '../data/'. Exiting." << std::endl;
        exit(1);
    }
    
    std::cout << "-> Opened ascii data file: " << fileName << std::endl;
    
    size_t pos = 0;
    std::string outfileName;
    if((pos = fileName.find(".")) != std::string::npos) {
        std::string prefix = fileName.substr(0, pos);
        outfileName = prefix + ".root";
    }
    
    TFile* outfile = TFile::Open( outfileName.c_str(), "recreate" );
    TTree* tree = new TTree( "tree", "" );
    
    
    int ev=-1;
    int nch;
    float base     [128];
    float vamp     [128];
    float vcharge  [128];
    float letime   [128];
    float tetime   [128];
    float ratecount[128];
    float pshape   [128][1024];
    
    tree->Branch( "ev"       , &ev      , "ev/I"            );
    tree->Branch( "nch"      , &nch     , "nch/I"           );
    tree->Branch( "base"     , base     , "base[nch]/F"     );
    tree->Branch( "vamp"     , vamp     , "vamp[nch]/F"     );
    tree->Branch( "vcharge"  , vcharge  , "vcharge[nch]/F"  );
    tree->Branch( "letime"   , letime   , "letime[nch]/F"   );
    tree->Branch( "tetime"   , tetime   , "tetime[nch]/F"   );
    tree->Branch( "ratecount", ratecount, "ratecount[nch]/F");
    tree->Branch( "pshape"   , pshape   , "pshape[nch][1024]/F");
    
    
    std::string line;
    bool wasReadingEvent = false;
    bool readyForPulseShape = false;
    int ch = -1;
    int flag = 0;
    
    if( fs.good() ) {
        
        std::cout << "-> Starting parsing file." << std::endl;
        nch=0;
        
        while( getline(fs,line)  && flag < 90000) {
            
            std::string delimiter = " ";
            size_t pos = 0;
            std::vector<std::string> words;
            std::string word;
            while ((pos = line.find(delimiter)) != std::string::npos) {
                word = line.substr(0, pos);
                line.erase(0, pos + delimiter.length());
                words.push_back(word);
            }
            
            if( words[0]=="===" && words[1]=="EVENT" && wasReadingEvent ) {
                
                if( ev % 100 == 0 ) std::cout << "   ... analyzing event: " << ev << std::endl;
                
                tree->Fill();
                
                nch = 0;
                ch = -1;
                wasReadingEvent = false;
                
            } else if( words[0]=="===" && words[1]=="CH:" ) {
                
                wasReadingEvent = true;
                readyForPulseShape = true;
                
                nch += 1;
                
                ch            = atoi(words[2].c_str());
                base     [ch] = atof(words[8].c_str());
                vamp     [ch] = atof(words[11].c_str());
                vcharge  [ch] = atof(words[14].c_str());
                letime   [ch] = atof(words[17].c_str());
                tetime   [ch] = atof(words[20].c_str());
                ratecount[ch] = atof(words[23].c_str());
                
            } else if( readyForPulseShape && ch>=0 ) {
                
                for( unsigned i=0; i<words.size(); ++i )
                    pshape[ch][i] = atof(words[i].c_str());
                
                readyForPulseShape = false;
                flag++;

            }
            
            if( words[0]=="===" && words[1]=="EVENT" && wasReadingEvent==false) {
                ev = atoi(words[2].c_str());
            }
        } // while get lines
        
    } // if file is good
    
    if( wasReadingEvent )
    {
        std::cout << "   ... analyzing event: " << ev << std::endl;
        tree->Fill();
    }
    
    fs.close();
    
    tree->Write();
    outfile->Close();
    
    std::cout << "-> Tree saved in: " << outfile->GetName() << std::endl;
    
    return 0;
    
}

