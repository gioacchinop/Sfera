//
// Event.cpp
//

#include "Event.h"

#include "TH1D.h"
#include "TCanvas.h"

void Event::pShapeHisto( float* pshape, std::string fileName ) {

  TH1D* h1 = new TH1D( "h1", "", npoints_, 0., double(npoints_) );
  TCanvas* c1 = new TCanvas( "c1", "c1", 600, 600 );
  c1->cd();

  for( int i=0; i<npoints_; ++i ){
    h1->SetBinContent( i+1, pshape[i] );
    std::cout << pshape[i] << std::endl;
  }
  
  h1->Draw();

  size_t pos = 0;
  std::string prefix;
  if((pos = fileName.find(".")) != std::string::npos) {
    prefix = fileName.substr(0, pos);
  }
  
  std::string plotsDir( Form( "plots/%s", prefix.c_str() ) );
  system( Form( "mkdir -p %s", plotsDir.c_str() ) );
  
  c1->SaveAs( Form( "%s/pulseShape_ev%d_ch%d.eps", plotsDir.c_str(), event_, channel_ ) );
  c1->SaveAs( Form( "%s/pulseShape_ev%d_ch%d.pdf", plotsDir.c_str(), event_, channel_ ) );
  
}


double Event::TRintegrate( double xlo, double xhi, double *integrand ) {

  std::cout << "-> Integrate pulse shape of event: " << event_ << ", channel: " << channel_ << std::endl;

  double sum = 0.;
  for(int i=0; i<npoints_; i++) {
    sum += ((xhi-xlo)/npoints_) * (integrand[i] + integrand[i+1])/2;
    std::cout << sum << "  " << i << std::endl;
  }
  
  return sum;
  
}
