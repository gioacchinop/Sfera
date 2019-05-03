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
    int getNpoints() {return npoints_;}
    void pShapeHisto( float* pshape, std::string fileName );  //in input pshape[1024] 1D
    double trapezIntegrator( double xlo, double xhi, float* integrand );
    double baseline( float* pshape, int flag);
    
private: 
    
    int event_;
    int channel_;
    int npoints_;
    
};

#endif
