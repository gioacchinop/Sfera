CC = g++
CFLAGS = -Wall -c -g -fpermissive 


INCLUDES = -I. -I.. -I$(ROOTSYS)/include -I$(ROOFIT_INCLUDE)/ 

ROOTSYS ?= ERROR_RootSysIsNotDefined

ROOTFLAG = `${ROOTSYS}/bin/root-config --cflags --libs`

EXTRALIBS := -L$(ROOTSYS)/lib -L$(ROOFIT_LIBDIR)/ -lHtml -lMathCore -lGenVector -lMinuit -lEG  -lPhysics -lz -lTreePlayer -lRooFitCore -lRooFit


asciiToTree: asciiToTree.cpp 
	$(CC) -Wall $(INCLUDES) -o asciiToTree asciiToTree.cpp $(ROOTFLAG) $(EXTRALIBS)

measToTree: measToTree.cpp 
	$(CC) -Wall $(INCLUDES) -o measToTree measToTree.cpp $(ROOTFLAG) $(EXTRALIBS)

checkPulseShape: checkPulseShape.cpp 
	$(CC) -Wall $(INCLUDES) -o checkPulseShape checkPulseShape.cpp $(ROOTFLAG) $(EXTRALIBS)

makeSpectrum: makeSpectrum.cpp
	$(CC) -Wall $(INCLUDES) -o makeSpectrum makeSpectrum.cpp $(ROOTFLAG) $(EXTRALIBS)

Event: Event.cpp
	$(CC) -Wall $(INCLUDES) -o Event Event.cpp $(ROOTFLAG) $(EXTRALIBS)

DataTree: DataTree.cpp
	$(CC) -Wall $(INCLUDES) -o DataTree DataTree.cpp $(ROOTFLAG) $(EXTRALIBS)

Read_Ttree: Read_Ttree.cpp
	$(CC) -Wall $(INCLUDES) -o Read_Ttree Read_Ttree.cpp $(ROOTFLAG) $(EXTRALIBS) DataTree.cpp 




all: asciiToTree checkPulseShape measToTree makeSpectrum Event DataTree Read_Ttree


clean:
	rm asciiToTree checkPulseShape measToTree makeSpectrum Event DataTree Read_Ttree
 

