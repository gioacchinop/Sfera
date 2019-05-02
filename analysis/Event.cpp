
//
// Event.cpp
//

#include "Event.h"

#include "TH1D.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TLegend.h"
#define DIST 10

void Event::pShapeHisto( float* pshape, std::string fileName ) {
    
    TH1D* histo = new TH1D( "h1", "", npoints_, 0., double(npoints_) );
    histo->SetStats(0);
    TCanvas* c = new TCanvas( "c", "c", 600, 600 );
    c->cd();
    float bsline = baseline(pshape,1);
    TLine* line = new TLine(0, bsline, 1024, bsline);
    line->SetLineColor(kRed);
    for( int i=0; i<npoints_; ++i ){
        histo->SetBinContent( i+1, pshape[i] );
        //  std::cout << pshape[i] << std::endl;
    }
    TLegend* legend = new TLegend(0.7,0.2,0.9,0.4);
    legend->AddEntry(histo,Form("Histogram of event %d, ch %d",event_, channel_), "l");
    legend->AddEntry(line,Form("baseline = %3.2e",bsline),  "l");
    histo->Draw();
    line->Draw();
    legend->Draw();
    
    
    size_t pos = 0;
    std::string prefix;
    if((pos = fileName.find("_Ascii")) != std::string::npos) {
        prefix = fileName.substr(0, pos);
    }
    
    std::string plotsDir( Form( "plots/%s/ev%d", prefix.c_str(), event_ ) );
    system( Form( "mkdir -p %s", plotsDir.c_str() ) );
    
    // c1->SaveAs( Form( "%s/pulseShape_ev%d_ch%d.eps", plotsDir.c_str(), event_, channel_ ) );
    c->SaveAs( Form( "%s/pulseShape_ev%d_ch%d.pdf", plotsDir.c_str(), event_, channel_ ) );
    delete histo;
    delete c;
    delete legend;
    delete line;
}


double Event::trapezIntegrator( double xlo, double xhi, float* integrand ) {
    /*
     std::cout << "-> Integrate pulse shape of event: " << event_ << ", channel: " << channel_ << std::endl;
     */
    double sum = 0.;
    for(int i=0; i<npoints_; i++) {
        sum += ((xhi-xlo)/npoints_) * (integrand[i] + integrand[i+1])/2;
    }
    
    return sum;
    
}

double Event::baseline( float* pshape, int flag){
    float mean=0;
    if(flag==1){
        float sum = 0;
        float stdev = 0;
        int i=0;
        
        TH1D* h2 = new TH1D("h2", "", 50, -0.005, 0.005 );
        
        while((i > 1 && abs((long double) pshape[i] - mean) <= stdev*DIST && i < 1023) || i < 2 ) {
            sum += pshape[i];                                          //sommo i primi i
            mean = sum/(i+1);                                          //media dei primi i
            h2->Fill(pshape[i]);
            stdev = h2->GetStdDev();
            if(stdev<1E-4) stdev = 0.0007;
            
            //      std::cout<<"stdev: "<< stdev << std::endl;
            i++;
        }
        
        //  std::cout << "\n\nbin: " << i << "\n"<< std::endl;
        delete h2;
    }
    if(flag==2){
        float sum = 0;
        int num = 50;
        for(int i=0; i<num; i++){
            sum += pshape[i];
        }
         mean = sum / num;
    }
    return mean;

}


