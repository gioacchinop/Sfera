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
    canal_ = 0;
  }

  Event(int event, int canal) {
    event_ = event;
    canal_ = canal;
  }

  ~Event() {}

  

  
 private:

  int event_;
  int canal_;

};

#endif
