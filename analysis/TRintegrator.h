//
// TRintegrator.h
//
// Discrete integrator using trapezoidal method for data analysis
//

#ifndef TRINTEGRATOR_H
#define TRINTEGRATOR_H

#include <iostream>
#include <stdlib.h>

class TRIntegrator {

 public:

  TRIntegrator() { npoints_=1024; }
  
  TRIntegrator(int n) {
    npoints_ = n;
  }

  ~TRIntegrator() {}
  
  void setNPoints( int n ) {
    npoints_ = n;
  }
  
  double integrate( double xlo, double xhi, double *integrand ) {   
    double sum = 0.;
    for(int i=0; i<npoints_; i++) {
      sum += ((xhi-xlo)/npoints_) * (integrand[i] + integrand[i+1])/2;
      std::cout << sum << "  " << i << std::endl;
    }
    return sum;
  }


 private:
  int npoints_;
  
};

#endif
