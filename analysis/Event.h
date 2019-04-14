//
// Event.h
//
// Class for data analysis of one single event
//

#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <stdlib.h>

class Event {

 public:

  Event() {
    event_ = 0;
    channel_ = 0;
    npoints_ = 1024;
  }

  Event( int event, int channel, int n ) {
    event_ = event;
    channel_ = channel;
    npoints_ = n;
  }

  ~Event() {}

  void setEvent( int event ) { event_   = event; }
  void setChannel( int channel ) { channel_   = channel; }
  void setNPoints(  int n  ) { npoints_ = n;     }
  
  void pShapeHisto( float* pshape, std::string fileName );
  double TRintegrate( double xlo, double xhi, double *integrand );

  
 private:

  int event_;
  int channel_;
  int npoints_;
  
};

#endif
