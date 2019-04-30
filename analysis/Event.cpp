
//
// Event.cpp
//

#include "Event.h"

#include "TH1D.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TLegend.h"
#define DIST 3.5

void Event::pShapeHisto( float* pshape, std::string fileName ) {
    
    TH1D* h1 = new TH1D( "h1", "", npoints_, 0., double(npoints_) );
    TCanvas* c1 = new TCanvas( "c1", "c1", 600, 600 );
    c1->cd();
    double bsline = baseline(pshape);
    TLine *line = new TLine(0, bsline, getNpoints(), bsline);
    line->SetLineColor(kRed);
    for( int i=0; i<npoints_; ++i ){
        h1->SetBinContent( i+1, pshape[i] );
        //  std::cout << pshape[i] << std::endl;
    }
    TLegend* legend = new TLegend();
    legend->AddEntry(h1,Form("Histogram of event %d, ch %d",event_, channel_), "f");
    legend->AddEntry(line,Form("baseline = %f",bsline),  "l");  
    h1->Draw();
    line->Draw();
    legend->Draw();
    
    
    size_t pos = 0;
    std::string prefix;
    if((pos = fileName.find(".")) != std::string::npos) {
        prefix = fileName.substr(0, pos);
    }
    
    std::string plotsDir( Form( "plots/%s", prefix.c_str() ) );
    system( Form( "mkdir -p %s", plotsDir.c_str() ) );
    
    c1->SaveAs( Form( "%s/pulseShape_ev%d_ch%d.eps", plotsDir.c_str(), event_, channel_ ) );
    c1->SaveAs( Form( "%s/pulseShape_ev%d_ch%d.pdf", plotsDir.c_str(), event_, channel_ ) );
    delete h1;
    delete c1;
}


double Event::trapezIntegrator( double xlo, double xhi, float* integrand ) {
    
    std::cout << "-> Integrate pulse shape of event: " << event_ << ", channel: " << channel_ << std::endl;
    
    double sum = 0.;
    for(int i=0; i<npoints_; i++) {
        sum += ((xhi-xlo)/npoints_) * (integrand[i] + integrand[i+1])/2;
    }
    
    return sum;
    
}

double Event::baseline( float* pshape ){
    float mean = pshape[0];
    float sum = pshape[0];
    float stdev = abs(pshape[1]-pshape[0]); //con N-1=1 a denominatore
    float sqrdsum = 0;
    int i=1;
    while(abs((long double) pshape[i] - mean) < stdev*DIST && i < getNpoints()) {
        sum += pshape[i];                                          //sommo i primi i
        mean = sum/(i+1);                                                   //media dei primi i
        sqrdsum += (mean-pshape[i])*(mean-pshape[i]);     //SUM(xi-x_medio)^2
        if(i>1) stdev = sqrt(sqrdsum/(i-1));                                //sigma sui primi i
    }
    return mean;
}


